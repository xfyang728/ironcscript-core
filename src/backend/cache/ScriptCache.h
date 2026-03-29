#ifndef CSE_SCRIPT_CACHE_H
#define CSE_SCRIPT_CACHE_H

#include "CacheHeader.h"
#include "CacheWriter.h"
#include "CacheReader.h"
#include <string>
#include <vector>
#include <unordered_map>

#ifndef CSE_PLATFORM_EMBEDDED
#include "X64Relocator.h"
#endif

namespace cse {

class ScriptCache : public IExternalSymbolResolver {
public:
    static ScriptCache& instance();

    void* resolve(const std::string& symbolName) override;

    void registerSymbol(const std::string& name, void* address);
    void clearSymbols();

    bool save(const std::string& scriptPath,
              const std::string& sourceCode,
              const std::vector<CompiledFunctionV2>& functions);

    bool load(const std::string& scriptPath,
              std::string& sourceCode,
              std::vector<CompiledFunctionV2>& functions);

    bool isValid(const std::string& scriptPath, const std::string& sourceCode);

    std::string getCachePath(const std::string& scriptPath) const;
    const std::string& getLastError() const { return m_LastError; }

private:
    ScriptCache() = default;
    ~ScriptCache() = default;

    ScriptCache(const ScriptCache&) = delete;
    ScriptCache& operator=(const ScriptCache&) = delete;

    std::unordered_map<std::string, void*> m_Symbols;
    std::string m_LastError;
};

} // namespace cse

#endif // CSE_SCRIPT_CACHE_H
