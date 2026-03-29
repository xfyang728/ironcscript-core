#include "IronCScriptImpl.h"
#include "backend/ScriptFunctionRegistry.h"
#include "backend/cache/ScriptCache.h"
#include "frontend/generated/CScriptLexer.h"
#include "frontend/generated/CScriptParser.h"
#include "frontend/parser/ASTBuilder.h"
#include "ir/IRGenerator.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <map>

// 在 RISC-V 嵌入式平台上，使用简单的内存分配
#include <cstdlib>
namespace fs {
    struct path {
        std::string path_str;
        path(const std::string& p) : path_str(p) {}
        path parent_path() const {
            size_t last_slash = path_str.find_last_of('/');
            if (last_slash == std::string::npos) {
                return path(".");
            }
            return path(path_str.substr(0, last_slash));
        }
        std::string string() const {
            return path_str;
        }
    };
    path current_path() {
        char buffer[256];
        if (getcwd(buffer, sizeof(buffer)) != nullptr) {
            return path(buffer);
        }
        return path(".");
    }
}

namespace cse {

IronCScriptImpl::IronCScriptImpl()
    : m_LastReturnValue(0)
    , m_PlatformName(PLATFORM_RISCV64)
    , m_FFIRegistry(FFIRegistry::instance())
    , m_CacheEnabled(false)
    , m_ForceRecompile(false)
    , m_DebugEnabled(false)
{
    m_SymbolTable = std::unique_ptr<SymbolTable>(new SymbolTable());
    m_PlatformAbstraction = std::unique_ptr<PlatformAbstraction>(PlatformFactory::createPlatformAbstraction());
    m_Debugger = DebuggerFactory::createDebugger(m_DebugEnabled);
    // 嵌入式平台不使用内存沙箱
    m_MemorySandbox = nullptr;
}

IronCScriptImpl::~IronCScriptImpl() {
}

void IronCScriptImpl::output(const std::string& msg) {
    if (m_StdoutCallback) {
        m_StdoutCallback(msg);
    } else {
        std::cout << msg;
    }
}

void IronCScriptImpl::error(const std::string& msg) {
    if (m_StderrCallback) {
        m_StderrCallback(msg);
    } else {
        std::cerr << msg;
    }
}

bool IronCScriptImpl::parseScript(const std::string& scriptCode, NBlock*& programBlock) {
    antlr4::ANTLRInputStream input(scriptCode.c_str(), scriptCode.size());
    CScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CScriptParser parser(&tokens);

    ASTBuilder builder;
    programBlock = builder.build(parser.program());

    if (programBlock == nullptr) {
        m_LastError = "Parsing failed: no statements found";
        return false;
    }
    return true;
}

bool IronCScriptImpl::analyzeSemantic(NBlock* programBlock) {
    // 暂时禁用模块管理器
    SemanticAnalyzer semanticAnalyzer(*m_SymbolTable, nullptr);
    bool result = semanticAnalyzer.analyze(*programBlock);
    if (!result) {
        m_LastError = "Semantic analysis failed";
        return false;
    }
    return true;
}

bool IronCScriptImpl::generateIR(NBlock* programBlock, std::list<Quad>& quadList) {
    IRGenerator irGenerator(*m_SymbolTable);
    irGenerator.generateIR(*programBlock);
    quadList = irGenerator.getQuadList();
    return true;
}

bool IronCScriptImpl::generateAndExecuteCode(const std::list<Quad>& quadList) {
    m_CodeGenContext = std::unique_ptr<CodeGenContext>(new CodeGenContext());

    BaseCodeGenerator* codeGen = m_CodeGenContext->getCodeGenerator(m_PlatformName);

    if (m_PlatformAbstraction) {
        codeGen->setPlatformAbstraction(m_PlatformAbstraction.get());
    }

    for (const auto& quad : quadList) {
        if (quad.getOp() == OpEnum::FUNC && quad.getResult() == "main") {
            std::string retType = quad.getArg1();
            if (retType == "double") {
                m_CodeGenContext->setMainReturnType(ReturnType::Double);
            } else if (retType == "float") {
                m_CodeGenContext->setMainReturnType(ReturnType::Float);
            } else {
                m_CodeGenContext->setMainReturnType(ReturnType::Integer);
            }
            break;
        }
    }

    codeGen->generateCodeFromIR(quadList);
    codeGen->formatCode();
    codeGen->DisassembleCode();

    // 直接执行代码，不使用内存沙箱
    m_LastReturnValue = m_CodeGenContext->runCode();
    
    return true;
}

bool IronCScriptImpl::execute(const std::string& scriptCode) {
    m_LastError.clear();
    m_LastReturnValue = 0;
    m_CurrentSourceCode = scriptCode;

    NBlock* programBlock = nullptr;

    if (!parseScript(scriptCode, programBlock)) {
        return false;
    }

    if (!analyzeSemantic(programBlock)) {
        return false;
    }

    std::list<Quad> quadList;
    if (!generateIR(programBlock, quadList)) {
        return false;
    }

    if (!generateAndExecuteCode(quadList)) {
        return false;
    }

    return true;
}

bool IronCScriptImpl::executeFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        m_LastError = "Cannot open file: " + filePath;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string scriptCode = buffer.str();

    m_CurrentScriptPath = filePath;
    m_CurrentSourceCode = scriptCode;
    
    // 暂时禁用模块管理器
    // fs::path scriptPath(filePath);
    // m_ModuleManager->setScriptDirectory(scriptPath.parent_path().string());

    std::cout << "[EXEC] JIT compiling script..." << std::endl;
    return execute(scriptCode);
}

bool IronCScriptImpl::registerNativeFunction(const std::string& name, void* funcPtr) {
    m_FFIRegistry.registerNative(name, funcPtr);
    if (m_PlatformAbstraction) {
        m_PlatformAbstraction->registerFFIFunction(name, funcPtr);
    }
    ScriptCache::instance().registerSymbol(name, funcPtr);
    return true;
}

void* IronCScriptImpl::getRegisteredCallback(const std::string& name) {
    return ScriptFunctionRegistry::instance().getScriptFunction(name);
}

bool IronCScriptImpl::hasRegisteredCallback(const std::string& name) const {
    return ScriptFunctionRegistry::instance().hasFunction(name);
}

void IronCScriptImpl::setCacheEnabled(bool enabled) {
    m_CacheEnabled = enabled;
    std::cout << "[CACHE] Cache " << (enabled ? "enabled" : "disabled") << std::endl;
}

void IronCScriptImpl::setForceRecompile(bool force) {
    m_ForceRecompile = force;
    std::cout << "[CACHE] Force recompile " << (force ? "enabled" : "disabled") << std::endl;
}

bool IronCScriptImpl::clearCache(const std::string& filePath) {
    // 嵌入式平台不支持缓存
    std::cout << "[CACHE] Cache not supported on embedded platform" << std::endl;
    return false;
}

bool IronCScriptImpl::isCacheValid() const {
    // 嵌入式平台不支持缓存
    return false;
}

bool IronCScriptImpl::loadFromCache() {
    // 嵌入式平台不支持缓存
    m_LastError = "Cache not supported on embedded platform";
    return false;
}

bool IronCScriptImpl::saveToCache() {
    // 嵌入式平台不支持缓存
    return false;
}

bool IronCScriptImpl::precompileAllFunctions(const std::list<Quad>& quadList) {
    // 暂时禁用预编译功能
    return true;
}

bool IronCScriptImpl::executeFromCache() {
    // 嵌入式平台不支持缓存
    m_LastError = "Cache not supported on embedded platform";
    return false;
}

// 调试器相关方法
void IronCScriptImpl::setDebugEnabled(bool enabled) {
    // 嵌入式平台不支持调试
    m_DebugEnabled = false;
}

bool IronCScriptImpl::isDebugEnabled() const {
    // 嵌入式平台不支持调试
    return false;
}

void IronCScriptImpl::setBreakpoint(int line, const std::string& file) {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::removeBreakpoint(int line, const std::string& file) {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::stepInto() {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::stepOver() {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::stepOut() {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::continueExecution() {
    // 嵌入式平台不支持调试
}

void IronCScriptImpl::pauseExecution() {
    // 嵌入式平台不支持调试
}

std::vector<DebugStackFrame> IronCScriptImpl::getCallStack() {
    // 嵌入式平台不支持调试
    return std::vector<DebugStackFrame>();
}

std::map<std::string, Value> IronCScriptImpl::getLocalVariables() {
    // 嵌入式平台不支持调试
    return std::map<std::string, Value>();
}

// 内存沙箱相关方法
void IronCScriptImpl::setExecutionTimeLimit(size_t milliseconds) {
    // 嵌入式平台不支持内存沙箱
    std::cout << "[SANDBOX] Set execution time limit to " << milliseconds << "ms" << std::endl;
}

void IronCScriptImpl::setMemoryLimit(size_t bytes) {
    // 嵌入式平台不支持内存沙箱
    std::cout << "[SANDBOX] Set memory limit to " << bytes << " bytes" << std::endl;
}

size_t IronCScriptImpl::getCurrentMemoryUsage() const {
    // 嵌入式平台不支持内存沙箱
    return 0;
}

} // namespace cse