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
#include <memory>
#include <vector>
#include <functional>

namespace cse {

class IronCScriptImpl;

class IronCScript {
public:
    using ExecutionCallback = std::function<void(const std::string&)>;

protected:
    std::unique_ptr<IronCScriptImpl> m_pImpl;

    IronCScriptImpl* getImpl() {
        return m_pImpl.get();
    }

    const IronCScriptImpl* getImpl() const {
        return m_pImpl.get();
    }

public:
    IronCScript();
    ~IronCScript();

    IronCScript(const IronCScript&) = delete;
    IronCScript& operator=(const IronCScript&) = delete;
    IronCScript(IronCScript&&) noexcept;
    IronCScript& operator=(IronCScript&&) noexcept;

    bool execute(const std::string& scriptCode);
    bool executeFile(const std::string& filePath);

    int getLastReturnValue() const;
    std::string getLastError() const;

    void setStandardOutputCallback(ExecutionCallback callback);
    void setStandardErrorCallback(ExecutionCallback callback);

    bool registerNativeFunction(const std::string& name, void* funcPtr);

    template<typename Ret, typename... Args>
    bool registerNativeFunction(const std::string& name, Ret(*func)(Args...)) {
        return registerNativeFunction(name, reinterpret_cast<void*>(func));
    }

    void* getRegisteredCallback(const std::string& name);
    bool hasRegisteredCallback(const std::string& name) const;

    void setCacheEnabled(bool enabled);
    void setForceRecompile(bool force);
    bool clearCache(const std::string& filePath);

    std::string getPlatformName() const;
    void setPlatform(const std::string& platformName);

    static std::string version();
    static std::string supportedPlatforms();
};

} // namespace cse