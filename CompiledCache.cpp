#include "CompiledCache.h"
#include "PlatformAbstraction.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <cstring>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif defined(__riscv) || defined(__riscv64)
// 在RISC-V平台上，不需要这些头文件
#else
#include <unistd.h>
#include <dlfcn.h>
#endif

namespace cse {

std::string CompiledCache::getCacheFileName(const std::string& scriptPath, PlatformType platform) {
    std::ostringstream oss;
    oss << scriptPath << ".csec." << platformToString(platform);
    return oss.str();
}

std::string CompiledCache::getCachePath(const std::string& scriptPath) {
    PlatformType currentPlatform = getCurrentPlatform();
    return getCacheFileName(scriptPath, currentPlatform);
}

std::string CompiledCache::platformToString(PlatformType platform) {
    switch (platform) {
        case PlatformType::PLATFORM_X64: return "x64";
        case PlatformType::PLATFORM_RISCV64: return "riscv64";
        case PlatformType::PLATFORM_RISCV64_EMBEDDED: return "riscv64_embedded";
        default: return "unknown";
    }
}

PlatformType CompiledCache::getCurrentPlatform() {
#ifdef _WIN32
    return PlatformType::PLATFORM_X64;
#elif defined(__x86_64__) || defined(_M_X64)
    return PlatformType::PLATFORM_X64;
#elif defined(__riscv) || defined(__riscv64) || defined(_M_RISCV64)
#ifdef CSE_PLATFORM_EMBEDDED
    return PlatformType::PLATFORM_RISCV64_EMBEDDED;
#else
    return PlatformType::PLATFORM_RISCV64;
#endif
#elif defined(__aarch64__) || defined(_M_ARM64)
    return PlatformType::PLATFORM_RISCV64;
#else
    return PlatformType::PLATFORM_UNKNOWN;
#endif
}

uint32_t CompiledCache::computeHash(const std::string& data) {
    uint32_t hash = 0x12345678;
    for (size_t i = 0; i < data.size(); ++i) {
        hash = (hash << 5) | (hash >> 27);
        hash ^= static_cast<uint32_t>(data[i]);
    }
    return hash;
}

bool CompiledCache::cacheExists(const std::string& scriptPath, PlatformType platform) {
    std::string cachePath = getCacheFileName(scriptPath, platform);
    std::ifstream file(cachePath, std::ios::binary);
    return file.good();
}

bool CompiledCache::writeCacheFile(const std::string& cachePath,
                                   const std::string& sourceCode,
                                   const std::vector<CompiledFunction>& functions,
                                   PlatformType platform) {
    std::ofstream file(cachePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open cache file for writing: " << cachePath << std::endl;
        return false;
    }

    CacheHeader header;
    std::memcpy(header.magic, CSEC_MAGIC, 4);
    header.version = CSEC_VERSION;
    header.platform = static_cast<uint16_t>(platform);
    header.sourceHash = computeHash(sourceCode);
    header.sourceSize = static_cast<uint32_t>(sourceCode.size());
    header.sourceModified = 0;
    header.functionCount = static_cast<uint32_t>(functions.size());

    uint32_t totalCodeSize = 0;
    for (const auto& func : functions) {
        totalCodeSize += static_cast<uint32_t>(func.machineCode.size());
    }
    header.totalCodeSize = totalCodeSize;

    header.headerSize = sizeof(CacheHeader);
    file.write(reinterpret_cast<const char*>(&header), sizeof(CacheHeader));

    std::streampos dataStart = file.tellp();

    for (const auto& func : functions) {
        uint32_t nameLen = static_cast<uint32_t>(func.name.size());
        uint32_t returnTypeLen = static_cast<uint32_t>(func.returnType.size());
        uint32_t paramCount = static_cast<uint32_t>(func.paramTypes.size());
        uint32_t codeSize = static_cast<uint32_t>(func.machineCode.size());

        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        file.write(reinterpret_cast<const char*>(&returnTypeLen), sizeof(returnTypeLen));
        file.write(reinterpret_cast<const char*>(&paramCount), sizeof(paramCount));
        file.write(reinterpret_cast<const char*>(&codeSize), sizeof(codeSize));
        file.write(func.name.c_str(), nameLen);
        file.write(func.returnType.c_str(), returnTypeLen);
        for (const auto& param : func.paramTypes) {
            uint32_t paramLen = static_cast<uint32_t>(param.size());
            file.write(reinterpret_cast<const char*>(&paramLen), sizeof(paramLen));
            file.write(param.c_str(), paramLen);
        }
        file.write(reinterpret_cast<const char*>(func.machineCode.data()), codeSize);
    }

    file.close();
    std::cout << "Cache saved: " << cachePath << " (" << functions.size() << " functions, "
              << totalCodeSize << " bytes)" << std::endl;
    return true;
}

bool CompiledCache::readCacheFile(const std::string& cachePath,
                                  std::vector<CompiledFunction>& functions) {
    std::ifstream file(cachePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open cache file for reading: " << cachePath << std::endl;
        return false;
    }

    CacheHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(CacheHeader));

    if (std::memcmp(header.magic, CSEC_MAGIC, 4) != 0) {
        std::cerr << "Invalid cache file: " << cachePath << std::endl;
        file.close();
        return false;
    }

    if (header.version != CSEC_VERSION) {
        std::cerr << "Cache version mismatch: " << header.version << " != " << CSEC_VERSION << std::endl;
        file.close();
        return false;
    }

    functions.clear();
    functions.reserve(header.functionCount);

    for (uint32_t i = 0; i < header.functionCount; ++i) {
        CompiledFunction func;

        uint32_t nameLen, returnTypeLen, paramCount, codeSize;
        file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        file.read(reinterpret_cast<char*>(&returnTypeLen), sizeof(returnTypeLen));
        file.read(reinterpret_cast<char*>(&paramCount), sizeof(paramCount));
        file.read(reinterpret_cast<char*>(&codeSize), sizeof(codeSize));

        func.name.resize(nameLen);
        func.returnType.resize(returnTypeLen);
        file.read(func.name.data(), nameLen);
        file.read(func.returnType.data(), returnTypeLen);

        func.paramTypes.resize(paramCount);
        for (uint32_t j = 0; j < paramCount; ++j) {
            uint32_t paramLen;
            file.read(reinterpret_cast<char*>(&paramLen), sizeof(paramLen));
            func.paramTypes[j].resize(paramLen);
            file.read(func.paramTypes[j].data(), paramLen);
        }

        func.machineCode.resize(codeSize);
        file.read(reinterpret_cast<char*>(func.machineCode.data()), codeSize);

        functions.push_back(std::move(func));
    }

    file.close();
    std::cout << "Cache loaded: " << cachePath << " (" << functions.size() << " functions)" << std::endl;
    return true;
}

bool CompiledCache::save(const std::string& scriptPath,
                         const std::string& sourceCode,
                         const std::vector<CompiledFunction>& functions,
                         PlatformType platform) {
    if (functions.empty()) {
        std::cerr << "No functions to cache" << std::endl;
        return false;
    }

    std::string cachePath = getCacheFileName(scriptPath, platform);
    return writeCacheFile(cachePath, sourceCode, functions, platform);
}

bool CompiledCache::load(const std::string& scriptPath,
                        std::vector<CompiledFunction>& functions,
                        PlatformType platform) {
    std::string cachePath = getCacheFileName(scriptPath, platform);
    return readCacheFile(cachePath, functions);
}

bool CompiledCache::isCacheValid(const std::string& scriptPath,
                                 const std::string& sourceCode,
                                 PlatformType platform) {
    std::string cachePath = getCacheFileName(scriptPath, platform);
    std::ifstream file(cachePath, std::ios::binary);
    if (!file.good()) {
        return false;
    }

    CacheHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(CacheHeader));

    if (std::memcmp(header.magic, CSEC_MAGIC, 4) != 0) {
        return false;
    }

    if (header.version != CSEC_VERSION) {
        return false;
    }

    if (header.platform != static_cast<uint16_t>(platform)) {
        return false;
    }

    if (header.sourceHash != computeHash(sourceCode)) {
        return false;
    }

    return true;
}

bool CompiledCache::removeCache(const std::string& scriptPath, PlatformType platform) {
    std::string cachePath = getCacheFileName(scriptPath, platform);
    std::error_code ec;
    if (std::filesystem::exists(cachePath, ec)) {
        std::filesystem::remove(cachePath, ec);
        return !ec;
    }
    return true;
}

} // namespace cse
