#ifndef CSE_FFI_REGISTRY_H
#define CSE_FFI_REGISTRY_H

#include <string>
#include <unordered_map>
#include <functional>
#include <optional>
#include <vector>
#include <memory>
#include <stdexcept>
#include "FFI.h"

namespace cse {

struct FunctionMetadata {
    FFIType returnType;
    std::vector<FFIType> paramTypes;
    bool isVariadic = false;
};

class FFIRegistry {
private:
    std::unordered_map<std::string, void*> m_NativeFunctions;
    std::unordered_map<std::string, FunctionMetadata> m_FunctionMetadata;

    FFICallConductor m_Conductor;

    static FFIRegistry* s_Instance;

    FFIRegistry() = default;

public:
    static FFIRegistry& instance() {
        if (!s_Instance) {
            s_Instance = new FFIRegistry();
        }
        return *s_Instance;
    }

    template<typename Ret, typename... Args>
    void registerNative(const std::string& name, Ret(*func)(Args...)) {
        static_assert(std::is_trivially_copyable<Ret>::value, "Return type must be trivially copyable");

        m_NativeFunctions[name] = reinterpret_cast<void*>(func);
        FunctionMetadata metadata;
        metadata.returnType = FFIMypeOf<Ret>::type;
        metadata.paramTypes = {FFIMypeOf<Args>::type...};
        metadata.isVariadic = false;
        m_FunctionMetadata[name] = metadata;
    }

    void registerNative(const std::string& name, void* funcPtr) {
        m_NativeFunctions[name] = funcPtr;
    }

    void* getNativeFunction(const std::string& name) {
        auto it = m_NativeFunctions.find(name);
        if (it != m_NativeFunctions.end()) {
            return it->second;
        }
        return nullptr;
    }

    bool hasFunction(const std::string& name) const {
        return m_NativeFunctions.find(name) != m_NativeFunctions.end();
    }

    const FunctionMetadata* getMetadata(const std::string& name) const {
        auto it = m_FunctionMetadata.find(name);
        if (it != m_FunctionMetadata.end()) {
            return &it->second;
        }
        return nullptr;
    }

    template<typename Ret, typename... Args>
    Ret callNative(const std::string& name, Args... args) {
        void* funcPtr = getNativeFunction(name);
        if (!funcPtr) {
#ifdef CSE_PLATFORM_EMBEDDED
            std::cerr << "Native function not found: " << name << std::endl;
            return Ret();
#else
            throw std::runtime_error("Native function not found: " + name);
#endif
        }
        return m_Conductor.call<Ret, Args...>(funcPtr, args...);
    }

    size_t functionCount() const {
        return m_NativeFunctions.size();
    }

    void clear() {
        m_NativeFunctions.clear();
        m_FunctionMetadata.clear();
    }

    std::vector<std::string> getAllFunctionNames() const {
        std::vector<std::string> names;
        names.reserve(m_NativeFunctions.size());
        for (const auto& pair : m_NativeFunctions) {
            names.push_back(pair.first);
        }
        return names;
    }
};

} // namespace cse

#endif // CSE_FFI_REGISTRY_H