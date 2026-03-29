#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#undef CONST
#undef ERROR
#endif

#include <string>
#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <unordered_map>

// 包含必要的头文件
#include "common/Value.h"
#include "common/StackFrame.h"
#include "frontend/parser/node.h"
#include "frontend/semantic/SymbolTable.h"
#include "ir/Quad.h"
#include "backend/codegen.h"
#include "backend/FFIRegistry.h"
#include "backend/CompiledCache.h"
#include "platform/PlatformAbstraction.h"
#include "exception/BaseException.h"
#include "exception/ExceptionHandler.h"
#include "exception/StackUnwinder.h"
#include "module/ModuleManager.h"

// 添加必要的using声明，确保类型名称正确
using cse::FFIRegistry;
using cse::PlatformAbstraction;
using cse::SymbolTable;
using cse::CodeGenContext;
using cse::CompiledFunction;
using cse::ModuleManager;
using cse::Value;
using cse::StackFrame;
using cse::NBlock;
using cse::Quad;

namespace antlr4 {
    class ANTLRInputStream;
    class CommonTokenStream;
}

namespace cse {

class IronCScriptImpl {
public:
    using ExecutionCallback = std::function<void(const std::string&)>;

private:
    int m_LastReturnValue;
    std::string m_LastError;
    std::string m_PlatformName;
    std::string m_CurrentScriptPath;
    std::string m_CurrentSourceCode;
    ExecutionCallback m_StdoutCallback;
    ExecutionCallback m_StderrCallback;
    FFIRegistry& m_FFIRegistry;
    std::unique_ptr<PlatformAbstraction> m_PlatformAbstraction;

    std::unique_ptr<SymbolTable> m_SymbolTable;
    std::unique_ptr<CodeGenContext> m_CodeGenContext;
    std::vector<CompiledFunction> m_CompiledFunctions;

    bool m_CacheEnabled;
    bool m_ForceRecompile;

    // 模块管理器
    ModuleManager* m_ModuleManager;

public:
    IronCScriptImpl();
    ~IronCScriptImpl();

    bool execute(const std::string& scriptCode);
    bool executeFile(const std::string& filePath);

    int getLastReturnValue() const { return m_LastReturnValue; }
    std::string getLastError() const { return m_LastError; }

    void setStandardOutputCallback(ExecutionCallback callback) { m_StdoutCallback = std::move(callback); }
    void setStandardErrorCallback(ExecutionCallback callback) { m_StderrCallback = std::move(callback); }

    bool registerNativeFunction(const std::string& name, void* funcPtr);

    std::string getPlatformName() const { return m_PlatformName; }
    void setPlatform(const std::string& platformName) { m_PlatformName = platformName; }

    PlatformAbstraction* getPlatformAbstraction() { return m_PlatformAbstraction.get(); }

    void* getRegisteredCallback(const std::string& name);
    bool hasRegisteredCallback(const std::string& name) const;

    void setCacheEnabled(bool enabled);
    void setForceRecompile(bool force);
    bool clearCache(const std::string& filePath);
    bool loadFromCache();
    bool saveToCache();
    bool isCacheValid() const;

public:
    bool parseScript(const std::string& scriptCode, NBlock*& programBlock);
    bool analyzeSemantic(NBlock* programBlock);
    bool generateIR(NBlock* programBlock, std::list<Quad>& quadList);
    bool generateAndExecuteCode(const std::list<Quad>& quadList);

    bool precompileAllFunctions(const std::list<Quad>& quadList);
    bool executeFromCache();

    void output(const std::string& msg);
    void error(const std::string& msg);
};

} // namespace cse