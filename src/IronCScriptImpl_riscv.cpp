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

#include <sys/mman.h>
#include <unistd.h>
#include <filesystem>
namespace fs = std::filesystem;

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
    // 使用 MemorySandbox 的单例实例
    m_MemorySandbox = &MemorySandbox::instance();
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
    PlatformType platform = CompiledCache::getCurrentPlatform();
    bool result = CompiledCache::removeCache(filePath, platform);
    std::cout << "[CACHE] Cache clear " << (result ? "succeeded" : "failed") << " for " << filePath << std::endl;
    return result;
}

bool IronCScriptImpl::isCacheValid() const {
    std::string cachePath = m_CurrentScriptPath;
    if (cachePath.empty()) {
        cachePath = "default_script";
    }
    PlatformType platform = CompiledCache::getCurrentPlatform();
    return ScriptCache::instance().isValid(cachePath, m_CurrentSourceCode);
}

bool IronCScriptImpl::loadFromCache() {
    PlatformType platform = CompiledCache::getCurrentPlatform();
    std::string cachePath = m_CurrentScriptPath;
    if (cachePath.empty()) {
        cachePath = "default_script";
    }

    if (!ScriptCache::instance().loadFromCache(cachePath, m_CurrentSourceCode, platform)) {
        m_LastError = "Failed to load from cache";
        return false;
    }

    return true;
}

bool IronCScriptImpl::saveToCache() {
    PlatformType platform = CompiledCache::getCurrentPlatform();
    std::string cachePath = m_CurrentScriptPath;
    if (cachePath.empty()) {
        cachePath = "default_script";
    }

    if (!ScriptCache::instance().saveToCache(cachePath, m_CurrentSourceCode, platform)) {
        m_LastError = "Failed to save to cache";
        return false;
    }

    return true;
}

bool IronCScriptImpl::precompileAllFunctions(const std::list<Quad>& quadList) {
    // 预编译所有函数
    for (const auto& quad : quadList) {
        if (quad.getOp() == OpEnum::FUNC) {
            // 这里可以添加函数预编译逻辑
        }
    }
    return true;
}

bool IronCScriptImpl::executeFromCache() {
    // 从缓存执行
    if (!loadFromCache()) {
        return false;
    }

    // 执行缓存的代码
    // 这里需要实现从缓存加载并执行的逻辑
    return true;
}

// 调试器相关方法
void IronCScriptImpl::setDebugEnabled(bool enabled) {
    m_DebugEnabled = enabled;
    m_Debugger->setDebugEnabled(enabled);
}

bool IronCScriptImpl::isDebugEnabled() const {
    return m_DebugEnabled;
}

void IronCScriptImpl::setBreakpoint(int line, const std::string& file) {
    m_Debugger->setBreakpoint(line, file);
}

void IronCScriptImpl::removeBreakpoint(int line, const std::string& file) {
    m_Debugger->removeBreakpoint(line, file);
}

void IronCScriptImpl::stepInto() {
    m_Debugger->stepInto();
}

void IronCScriptImpl::stepOver() {
    m_Debugger->stepOver();
}

void IronCScriptImpl::stepOut() {
    m_Debugger->stepOut();
}

void IronCScriptImpl::continueExecution() {
    m_Debugger->continueExecution();
}

void IronCScriptImpl::pauseExecution() {
    m_Debugger->pauseExecution();
}

std::vector<DebugStackFrame> IronCScriptImpl::getCallStack() {
    return m_Debugger->getCallStack();
}

std::map<std::string, Value> IronCScriptImpl::getLocalVariables() {
    return m_Debugger->getLocalVariables();
}

// 内存沙箱相关方法
void IronCScriptImpl::setExecutionTimeLimit(size_t milliseconds) {
    m_MemorySandbox->setExecutionTimeLimit(milliseconds);
    std::cout << "[SANDBOX] Set execution time limit to " << milliseconds << "ms" << std::endl;
}

void IronCScriptImpl::setMemoryLimit(size_t bytes) {
    m_MemorySandbox->setMemoryLimit(bytes);
    std::cout << "[SANDBOX] Set memory limit to " << bytes << " bytes" << std::endl;
}

size_t IronCScriptImpl::getCurrentMemoryUsage() const {
    return m_MemorySandbox->getCurrentMemoryUsage();
}

} // namespace cse