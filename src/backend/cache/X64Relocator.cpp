#include "X64Relocator.h"
#include <cstring>

namespace cse {

X64Relocator::X64Relocator() = default;

X64Relocator::~X64Relocator() = default;

void* X64Relocator::resolve(const std::string& symbolName) {
    auto it = m_Symbols.find(symbolName);
    if (it != m_Symbols.end()) {
        return it->second;
    }
    return nullptr;
}

void X64Relocator::registerSymbol(const std::string& name, void* address) {
    m_Symbols[name] = address;
}

void X64Relocator::unregisterSymbol(const std::string& name) {
    m_Symbols.erase(name);
}

PlatformType X64Relocator::getCurrentPlatform() {
#if defined(__x86_64__) || defined(_M_X64)
    return PlatformType::PLATFORM_X64;
#else
    return PlatformType::PLATFORM_UNKNOWN;
#endif
}

uint32_t X64Relocator::computeHash(const std::string& data) {
    uint32_t hash = 0x12345678;
    for (size_t i = 0; i < data.size(); ++i) {
        hash = (hash << 5) | (hash >> 27);
        hash ^= static_cast<uint32_t>(data[i]);
    }
    return hash;
}

X64SymbolResolver::X64SymbolResolver()
    : m_DefaultResolver(nullptr) {
}

X64SymbolResolver::~X64SymbolResolver() = default;

void* X64SymbolResolver::resolve(const std::string& symbolName) {
    auto it = m_Overrides.find(symbolName);
    if (it != m_Overrides.end()) {
        return it->second;
    }

    if (m_DefaultResolver) {
        return m_DefaultResolver(symbolName);
    }

    return nullptr;
}

void X64SymbolResolver::registerResolver(const std::string& name, void* (*resolver)(const std::string&)) {
    m_Overrides[name] = reinterpret_cast<void*>(resolver);
}

} // namespace cse
