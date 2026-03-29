#ifndef CSE_CACHE_HEADER_H
#define CSE_CACHE_HEADER_H

#include <cstdint>
#include <string>
#include <vector>

namespace cse {

#define CSEC_MAGIC "CSEC"
#define CSEC_VERSION 2

enum class RelocationType : uint16_t {
    NONE = 0,
    X64_64 = 1,
    X64_32 = 2,
    X64_REL32 = 3,
    RISCV_64 = 10,
    RISCV_32 = 11,
};

struct CacheHeaderV2 {
    char magic[4];
    uint16_t version;
    uint16_t platform;
    uint32_t sourceHash;
    uint32_t sourceSize;
    uint64_t sourceModified;
    uint32_t stringTableSize;
    uint32_t symbolCount;
    uint32_t functionCount;
    uint32_t totalCodeSize;
    uint32_t checksum;
};

struct SymbolEntry {
    uint32_t nameOffset;
    uint32_t addressOffset;
    uint16_t type;
};

struct FunctionHeaderV2 {
    uint32_t nameOffset;
    uint32_t returnTypeOffset;
    uint32_t paramCountOffset;
    uint32_t codeSize;
    uint32_t codeOffset;
    uint32_t relocationCount;
    uint32_t relocationOffset;
};

struct RelocationEntry {
    uint32_t codeOffset;
    RelocationType type;
    uint32_t symbolIndex;
};

struct CompiledFunctionV2 {
    std::string name;
    std::string returnType;
    std::vector<std::string> paramTypes;
    std::vector<unsigned char> machineCode;
    std::vector<RelocationEntry> relocations;
    void* allocatedAddress;
};

class IExternalSymbolResolver {
public:
    virtual ~IExternalSymbolResolver() = default;
    virtual void* resolve(const std::string& symbolName) = 0;
};

} // namespace cse

#endif // CSE_CACHE_HEADER_H
