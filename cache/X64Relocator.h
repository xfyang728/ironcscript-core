#ifndef CSE_X64_RELOCATOR_H
#define CSE_X64_RELOCATOR_H

#include "CacheHeader.h"
#include "../CompiledCache.h"
#include <string>
#include <unordered_map>

namespace cse {

class X64Relocator : public IExternalSymbolResolver {
public:
    X64Relocator();
    ~X64Relocator() override;

    void* resolve(const std::string& symbolName) override;

    void registerSymbol(const std::string& name, void* address);
    void unregisterSymbol(const std::string& name);

    static PlatformType getCurrentPlatform();
    static uint32_t computeHash(const std::string& data);

private:
    std::unordered_map<std::string, void*> m_Symbols;
};

class X64SymbolResolver : public IExternalSymbolResolver {
public:
    X64SymbolResolver();
    ~X64SymbolResolver() override;

    void* resolve(const std::string& symbolName) override;

    void registerResolver(const std::string& name, void* (*resolver)(const std::string&));

private:
    void* (*m_DefaultResolver)(const std::string&);
    std::unordered_map<std::string, void*> m_Overrides;
};

} // namespace cse

#endif // CSE_X64_RELOCATOR_H
