#include "IronCScriptImpl.h"
#include "backend/ScriptFunctionRegistry.h"
#include "backend/cache/ScriptCache.h"
#include "frontend/generated/CScriptLexer.h"
#include "frontend/generated/CScriptParser.h"
#include "frontend/parser/ASTBuilder.h"
#include "frontend/semantic/SemanticAnalyzer.h"
#include "ir/IRGenerator.h"
#include "ir/Quad.h"
#include "platform/PlatformAbstraction.h"
#include "module/ModuleManager.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <filesystem>
#undef ERROR
#undef CONST
namespace fs = std::filesystem;
#else
#include <sys/mman.h>
#include <unistd.h>
#include <filesystem>
namespace fs = std::filesystem;
#endif

namespace cse {

static void* allocateExecutableMemory(size_t size) {
#ifdef _WIN32
    return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    return mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
}

static void protectMemory(void* addr, size_t size, bool readable, bool executable) {
#ifdef _WIN32
    DWORD oldProtect;
    DWORD newProtect = PAGE_NOACCESS;
    if (readable && executable) newProtect = PAGE_EXECUTE_READ;
    else if (readable) newProtect = PAGE_READONLY;
    else if (executable) newProtect = PAGE_EXECUTE;
    VirtualProtect(addr, size, newProtect, &oldProtect);
#else
    int prot = PROT_NONE;
    if (readable && executable) prot = PROT_READ | PROT_WRITE | PROT_EXEC;
    else if (readable) prot = PROT_READ;
    else if (executable) prot = PROT_READ | PROT_EXEC;
    mprotect(addr, size, prot);
#endif
}

static void freeExecutableMemory(void* addr, size_t size) {
    if (!addr) return;
#ifdef _WIN32
    VirtualFree(addr, 0, MEM_RELEASE);
#else
    munmap(addr, size);
#endif
}

IronCScriptImpl::IronCScriptImpl()
    : m_LastReturnValue(0)
    , m_PlatformName(PLATFORM_X86_64)
    , m_FFIRegistry(FFIRegistry::instance())
    , m_CacheEnabled(false)
    , m_ForceRecompile(false)
{
    m_SymbolTable = std::unique_ptr<SymbolTable>(new SymbolTable());
    m_PlatformAbstraction = std::unique_ptr<PlatformAbstraction>(PlatformFactory::createPlatformAbstraction());
    m_ModuleManager = new ModuleManager();
    m_ModuleManager->setCurrentDirectory(fs::current_path().string());
}

IronCScriptImpl::~IronCScriptImpl() {
    delete m_ModuleManager;
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
    try {
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
    } catch (const std::exception& e) {
        m_LastError = std::string("Parsing exception: ") + e.what();
        return false;
    }
}

bool IronCScriptImpl::analyzeSemantic(NBlock* programBlock) {
    try {
        SemanticAnalyzer semanticAnalyzer(*m_SymbolTable, m_ModuleManager);
        bool result = semanticAnalyzer.analyze(*programBlock);
        if (!result) {
            m_LastError = "Semantic analysis failed";
            return false;
        }
        return true;
    } catch (const std::exception& e) {
        m_LastError = std::string("Semantic analysis exception: ") + e.what();
        return false;
    }
}

bool IronCScriptImpl::generateIR(NBlock* programBlock, std::list<Quad>& quadList) {
    try {
        IRGenerator irGenerator(*m_SymbolTable);
        irGenerator.generateIR(*programBlock);
        quadList = irGenerator.getQuadList();
        return true;
    } catch (const std::exception& e) {
        m_LastError = std::string("IR generation exception: ") + e.what();
        return false;
    }
}

bool IronCScriptImpl::generateAndExecuteCode(const std::list<Quad>& quadList) {
    try {
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

        m_LastReturnValue = m_CodeGenContext->runCode();

        return true;
    } catch (const std::exception& e) {
        m_LastError = std::string("Code execution exception: ") + e.what();
        return false;
    }
}

bool IronCScriptImpl::execute(const std::string& scriptCode) {
    m_LastError.clear();
    m_LastReturnValue = 0;
    m_CurrentSourceCode = scriptCode;

    try {
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

        if (m_CacheEnabled && !m_CompiledFunctions.empty()) {
            std::cout << "[CACHE] Saving cache..." << std::endl;
            saveToCache();
        }

        return true;
    } catch (const BaseException& e) {
        m_LastError = e.toString();
        error("Exception caught: " + e.toString() + "\n");
        StackUnwinder::instance().unwind();
        return false;
    } catch (const std::exception& e) {
        m_LastError = std::string("System exception: ") + e.what();
        error("System exception caught: " + std::string(e.what()) + "\n");
        StackUnwinder::instance().unwind();
        return false;
    } catch (...) {
        m_LastError = "Unknown exception caught";
        error("Unknown exception caught\n");
        StackUnwinder::instance().unwind();
        return false;
    }
}

bool IronCScriptImpl::executeFile(const std::string& filePath) {
    try {
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

        fs::path scriptPath(filePath);
        m_ModuleManager->setScriptDirectory(scriptPath.parent_path().string());

        if (m_CacheEnabled && !m_ForceRecompile && isCacheValid()) {
            std::cout << "[CACHE] Loading from cache: " << CompiledCache::getCachePath(filePath) << std::endl;
            return loadFromCache();
        }

        if (m_ForceRecompile) {
            std::cout << "[CACHE] Force recompile enabled, clearing cache..." << std::endl;
            clearCache(filePath);
        }

        std::cout << "[EXEC] JIT compiling script..." << std::endl;
        return execute(scriptCode);
    } catch (const BaseException& e) {
        m_LastError = e.toString();
        error("Exception caught: " + e.toString() + "\n");
        StackUnwinder::instance().unwind();
        return false;
    } catch (const std::exception& e) {
        m_LastError = std::string("System exception: ") + e.what();
        error("System exception caught: " + std::string(e.what()) + "\n");
        StackUnwinder::instance().unwind();
        return false;
    } catch (...) {
        m_LastError = "Unknown exception caught";
        error("Unknown exception caught\n");
        StackUnwinder::instance().unwind();
        return false;
    }
}

bool IronCScriptImpl::registerNativeFunction(const std::string& name, void* funcPtr) {
    try {
        m_FFIRegistry.registerNative(name, funcPtr);
        if (m_PlatformAbstraction) {
            m_PlatformAbstraction->registerFFIFunction(name, funcPtr);
        }
        ScriptCache::instance().registerSymbol(name, funcPtr);
        return true;
    } catch (const std::exception& e) {
        m_LastError = std::string("Failed to register native function: ") + e.what();
        return false;
    }
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
    std::string cachePath = m_CurrentScriptPath;
    if (cachePath.empty()) {
        cachePath = "default_script";
        std::cout << "[CACHE] No script path set, using default path: " << cachePath << std::endl;
    }

    for (auto& func : m_CompiledFunctions) {
        if (func.allocatedAddress) {
            freeExecutableMemory(func.allocatedAddress, func.machineCode.size());
            func.allocatedAddress = nullptr;
        }
    }
    m_CompiledFunctions.clear();
    ScriptFunctionRegistry::instance().clear();

    std::cout << "[CACHE] Loading from cache: " << ScriptCache::instance().getCachePath(cachePath) << std::endl;

    std::vector<CompiledFunctionV2> cachedFunctions;
    if (!ScriptCache::instance().load(cachePath, m_CurrentSourceCode, cachedFunctions)) {
        m_LastError = "Failed to load from cache: " + ScriptCache::instance().getLastError();
        return false;
    }

    std::cout << "[CACHE] Loaded " << cachedFunctions.size() << " functions from cache" << std::endl;

    for (auto& funcV2 : cachedFunctions) {
        CompiledFunction func;
        func.name = funcV2.name;
        func.returnType = funcV2.returnType;
        func.paramTypes = funcV2.paramTypes;
        func.machineCode = funcV2.machineCode;
        func.allocatedAddress = funcV2.allocatedAddress;

        void* execMem = allocateExecutableMemory(func.machineCode.size());
        if (!execMem) {
            m_LastError = "Failed to allocate executable memory for: " + func.name;
            return false;
        }
        memcpy(execMem, func.machineCode.data(), func.machineCode.size());
        protectMemory(execMem, func.machineCode.size(), true, true);

        func.allocatedAddress = execMem;

        ScriptFunctionRegistry::instance().registerScriptFunction(
            func.name, execMem, func.machineCode.size(),
            func.returnType, func.paramTypes
        );
        std::cout << "[CACHE] Registered function: " << func.name << " at " << execMem << std::endl;

        m_CompiledFunctions.push_back(func);
    }

    return executeFromCache();
}

bool IronCScriptImpl::saveToCache() {
    if (m_CompiledFunctions.empty()) {
        std::cerr << "[CACHE] No compiled functions to save" << std::endl;
        return false;
    }

    std::string cachePath = m_CurrentScriptPath;
    if (cachePath.empty()) {
        cachePath = "default_script";
        std::cout << "[CACHE] No script path set, using default path: " << cachePath << std::endl;
    }

    std::cout << "[CACHE] Saving " << m_CompiledFunctions.size() << " functions to cache" << std::endl;

    std::vector<CompiledFunctionV2> functionsV2;
    for (const auto& func : m_CompiledFunctions) {
        CompiledFunctionV2 funcV2;
        funcV2.name = func.name;
        funcV2.returnType = func.returnType;
        funcV2.paramTypes = func.paramTypes;
        funcV2.machineCode = func.machineCode;
        funcV2.allocatedAddress = func.allocatedAddress;
        functionsV2.push_back(funcV2);
    }

    if (!ScriptCache::instance().save(cachePath, m_CurrentSourceCode, functionsV2)) {
        std::cerr << "[CACHE] Failed to save cache" << std::endl;
        return false;
    }

    return true;
}

bool IronCScriptImpl::precompileAllFunctions(const std::list<Quad>& quadList) {
    return false;
}

bool IronCScriptImpl::executeFromCache() {
    void* mainFunc = ScriptFunctionRegistry::instance().getScriptFunction("main");
    if (!mainFunc) {
        m_LastError = "main function not found in cache";
        return false;
    }

    using MainFunc = int(*)();
    MainFunc main = reinterpret_cast<MainFunc>(mainFunc);

    std::cout << "[CACHE] Executing main from cache at " << mainFunc << std::endl;

    m_LastReturnValue = main();

    return true;
}

} // namespace cse