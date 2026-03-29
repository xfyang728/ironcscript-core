#ifndef CSE_COMPILED_CACHE_H
#define CSE_COMPILED_CACHE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <ctime>

namespace cse {

#define CSEC_MAGIC "CSEC"
#define CSEC_VERSION 2

enum class PlatformType : uint16_t {
    PLATFORM_UNKNOWN = 0,
    PLATFORM_X64 = 1,
    PLATFORM_RISCV64 = 2,
    PLATFORM_RISCV64_EMBEDDED = 3
};

struct CompiledFunction {
    std::string name;
    std::string returnType;
    std::vector<std::string> paramTypes;
    std::vector<unsigned char> machineCode;
    size_t codeOffset;
    void* allocatedAddress;
};

struct CacheHeader {
    char magic[4];
    uint16_t version;
    uint16_t platform;
    uint32_t sourceHash;
    uint32_t sourceSize;
    time_t sourceModified;
    uint32_t functionCount;
    uint32_t totalCodeSize;
    uint32_t headerSize;
};

struct FunctionIndex {
    uint32_t nameLength;
    uint32_t returnTypeLength;
    uint32_t paramCount;
    uint32_t machineCodeSize;
    uint32_t nameOffset;
    uint32_t codeOffset;
};

class CompiledCache {
public:
    static std::string getCachePath(const std::string& scriptPath);

    static bool save(const std::string& scriptPath,
                     const std::string& sourceCode,
                     const std::vector<CompiledFunction>& functions,
                     PlatformType platform);

    static bool load(const std::string& scriptPath,
                     std::vector<CompiledFunction>& functions,
                     PlatformType platform);

    static bool isCacheValid(const std::string& scriptPath,
                             const std::string& sourceCode,
                             PlatformType platform);

    static bool cacheExists(const std::string& scriptPath, PlatformType platform);

    static bool removeCache(const std::string& scriptPath, PlatformType platform);

    static PlatformType getCurrentPlatform();

    static std::string platformToString(PlatformType platform);

    static uint32_t computeHash(const std::string& data);

private:
    static std::string getCacheFileName(const std::string& scriptPath, PlatformType platform);
    static bool writeCacheFile(const std::string& cachePath,
                               const std::string& sourceCode,
                               const std::vector<CompiledFunction>& functions,
                               PlatformType platform);
    static bool readCacheFile(const std::string& cachePath,
                              std::vector<CompiledFunction>& functions);
};

} // namespace cse

#endif // CSE_COMPILED_CACHE_H
