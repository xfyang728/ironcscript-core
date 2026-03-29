#include "ScriptCache.h"
#include <iostream>
#include <fstream>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#endif

namespace cse {

ScriptCache& ScriptCache::instance() {
    static ScriptCache cache;
    return cache;
}

void* ScriptCache::resolve(const std::string& symbolName) {
    auto it = m_Symbols.find(symbolName);
    if (it != m_Symbols.end()) {
        return it->second;
    }
    return nullptr;
}

void ScriptCache::registerSymbol(const std::string& name, void* address) {
    m_Symbols[name] = address;
}

void ScriptCache::clearSymbols() {
    m_Symbols.clear();
}

#ifndef CSE_PLATFORM_EMBEDDED
bool ScriptCache::save(const std::string& scriptPath,
                       const std::string& sourceCode,
                       const std::vector<CompiledFunctionV2>& functions) {
#ifdef _WIN32
    std::string cachePath;
    
    // 获取当前工作目录
    char cwdBuffer[MAX_PATH] = {0};
    GetCurrentDirectoryA(MAX_PATH, cwdBuffer);
    std::string currentDir(cwdBuffer);
    std::cout << "[ScriptCache] Current working directory: " << currentDir << std::endl;
    
    // 获取可执行文件路径
    char exeBuffer[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, exeBuffer, MAX_PATH);
    std::string exePath(exeBuffer);
    std::cout << "[ScriptCache] Executable path: " << exePath << std::endl;
    
    // 提取可执行文件所在目录
    size_t lastBackslash = exePath.find_last_of('\\');
    std::string exeDir = lastBackslash != std::string::npos ? exePath.substr(0, lastBackslash) : currentDir;
    std::cout << "[ScriptCache] Executable directory: " << exeDir << std::endl;
    
    if (!scriptPath.empty() && scriptPath != "default_script") {
        cachePath = scriptPath + ".csec.x64";
        std::cout << "[ScriptCache] Using script path: " << cachePath << std::endl;
    } else {
        // 在可执行文件同目录生成缓存文件
        cachePath = exeDir + "\\default_script.csec.x64";
        std::cout << "[ScriptCache] Using default cache path: " << cachePath << std::endl;
    }

    CacheWriter writer;
    if (!writer.open(cachePath)) {
        std::cerr << "[ScriptCache] Failed to open cache for writing: " << cachePath << std::endl;
        return false;
    }

    CacheHeaderV2 header = {};
    std::memcpy(header.magic, CSEC_MAGIC, 4);
    header.version = CSEC_VERSION;
    header.platform = static_cast<uint16_t>(PlatformType::PLATFORM_X64);
    header.sourceHash = X64Relocator::computeHash(sourceCode);
    header.sourceSize = static_cast<uint32_t>(sourceCode.size());
    header.sourceModified = 0;

    writer.addString(scriptPath);
    for (const auto& func : functions) {
        writer.addString(func.name);
        writer.addString(func.returnType);
        for (const auto& param : func.paramTypes) {
            writer.addString(param);
        }
    }

    for (const auto& func : functions) {
        writer.addFunction(func);
    }

    writer.close();

    std::cout << "[ScriptCache] Saved cache: " << cachePath << std::endl;
    std::cout << "[ScriptCache] Full cache path: " << cachePath << std::endl;
    return true;
#else
    // 在非Windows环境中，直接返回false，避免使用Windows特定的函数
    return false;
#endif
}

bool ScriptCache::load(const std::string& scriptPath,
                       std::string& sourceCode,
                       std::vector<CompiledFunctionV2>& functions) {
    std::string cachePath;
    if (!scriptPath.empty()) {
        cachePath = scriptPath + ".csec.x64";
    } else {
        // 直接使用相对路径，确保缓存文件在可执行文件同目录
        cachePath = "default_script.csec.x64";
    }

    CacheReader reader;
    if (!reader.open(cachePath)) {
        m_LastError = reader.getLastError();
        std::cerr << "[ScriptCache] Failed to open cache: " << m_LastError << std::endl;
        return false;
    }

    if (!reader.validate(sourceCode, X64Relocator::getCurrentPlatform())) {
        m_LastError = reader.getLastError();
        std::cerr << "[ScriptCache] Cache validation failed: " << m_LastError << std::endl;
        reader.close();
        return false;
    }

    if (!reader.loadFunctions(functions)) {
        m_LastError = reader.getLastError();
        std::cerr << "[ScriptCache] Failed to load functions: " << m_LastError << std::endl;
        reader.close();
        return false;
    }

    for (auto& func : functions) {
        if (!reader.relocateFunction(func, this, func.allocatedAddress)) {
            m_LastError = reader.getLastError();
            std::cerr << "[ScriptCache] Relocation failed: " << m_LastError << std::endl;
        }
    }

    reader.close();
    std::cout << "[ScriptCache] Loaded cache: " << cachePath << std::endl;
    return true;
}

bool ScriptCache::isValid(const std::string& scriptPath, const std::string& sourceCode) {
    std::string cachePath;
    if (!scriptPath.empty()) {
        cachePath = scriptPath + ".csec.x64";
    } else {
        // 直接使用相对路径，确保缓存文件在可执行文件同目录
        cachePath = "default_script.csec.x64";
    }

    std::ifstream file(cachePath, std::ios::binary);
    if (!file.good()) {
        return false;
    }

    CacheHeaderV2 header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (std::memcmp(header.magic, CSEC_MAGIC, 4) != 0) {
        return false;
    }

    if (header.version != CSEC_VERSION) {
        return false;
    }

    if (header.platform != static_cast<uint16_t>(PlatformType::PLATFORM_X64)) {
        return false;
    }

    uint32_t hash = X64Relocator::computeHash(sourceCode);
    if (header.sourceHash != hash) {
        return false;
    }

    return true;
}

std::string ScriptCache::getCachePath(const std::string& scriptPath) const {
    if (!scriptPath.empty()) {
        return scriptPath + ".csec.x64";
    } else {
        // 直接使用相对路径，确保缓存文件在可执行文件同目录
        return "default_script.csec.x64";
    }
}
#else
// 嵌入式平台上的空实现
bool ScriptCache::save(const std::string& scriptPath,
                       const std::string& sourceCode,
                       const std::vector<CompiledFunctionV2>& functions) {
    return false;
}

bool ScriptCache::load(const std::string& scriptPath,
                       std::string& sourceCode,
                       std::vector<CompiledFunctionV2>& functions) {
    return false;
}

bool ScriptCache::isValid(const std::string& scriptPath, const std::string& sourceCode) {
    return false;
}

std::string ScriptCache::getCachePath(const std::string& scriptPath) const {
    return "";
}
#endif

} // namespace cse
