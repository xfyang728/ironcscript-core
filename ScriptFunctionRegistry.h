#ifndef CSE_SCRIPT_FUNCTION_REGISTRY_H
#define CSE_SCRIPT_FUNCTION_REGISTRY_H

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <functional>

namespace cse {

struct ScriptFunctionInfo {
    void* machineCode;
    size_t codeSize;
    std::string returnType;
    std::vector<std::string> paramTypes;
};

class ScriptFunctionRegistry {
private:
    std::unordered_map<std::string, ScriptFunctionInfo> m_ScriptFunctions;
    std::unordered_map<void*, std::string> m_AddressToName;

    static ScriptFunctionRegistry* s_Instance;

    ScriptFunctionRegistry() = default;

public:
    static ScriptFunctionRegistry& instance() {
        if (!s_Instance) {
            s_Instance = new ScriptFunctionRegistry();
        }
        return *s_Instance;
    }

    void registerScriptFunction(const std::string& name, void* machineCode, size_t codeSize,
                                 const std::string& returnType,
                                 const std::vector<std::string>& paramTypes = {}) {
        m_ScriptFunctions[name] = ScriptFunctionInfo{
            .machineCode = machineCode,
            .codeSize = codeSize,
            .returnType = returnType,
            .paramTypes = paramTypes
        };
        m_AddressToName[machineCode] = name;
    }

    void* getScriptFunction(const std::string& name) {
        auto it = m_ScriptFunctions.find(name);
        if (it != m_ScriptFunctions.end()) {
            return it->second.machineCode;
        }
        return nullptr;
    }

    bool hasFunction(const std::string& name) const {
        return m_ScriptFunctions.find(name) != m_ScriptFunctions.end();
    }

    const ScriptFunctionInfo* getFunctionInfo(const std::string& name) const {
        auto it = m_ScriptFunctions.find(name);
        if (it != m_ScriptFunctions.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const std::string* getFunctionName(void* address) const {
        auto it = m_AddressToName.find(address);
        if (it != m_AddressToName.end()) {
            return &it->second;
        }
        return nullptr;
    }

    size_t functionCount() const {
        return m_ScriptFunctions.size();
    }

    void unregister(const std::string& name) {
        auto it = m_ScriptFunctions.find(name);
        if (it != m_ScriptFunctions.end()) {
            m_AddressToName.erase(it->second.machineCode);
            m_ScriptFunctions.erase(it);
        }
    }

    void clear() {
        m_ScriptFunctions.clear();
        m_AddressToName.clear();
    }

    std::vector<std::string> getAllFunctionNames() const {
        std::vector<std::string> names;
        names.reserve(m_ScriptFunctions.size());
        for (const auto& pair : m_ScriptFunctions) {
            names.push_back(pair.first);
        }
        return names;
    }
};

} // namespace cse

#endif // CSE_SCRIPT_FUNCTION_REGISTRY_H