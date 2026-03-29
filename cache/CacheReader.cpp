#include "CacheReader.h"
#include <iostream>
#include <cstring>

#ifndef CSE_PLATFORM_EMBEDDED
#include "X64Relocator.h"
#endif

namespace cse {

CacheReader::CacheReader()
    : m_IsOpen(false) {
}

CacheReader::~CacheReader() {
    if (m_IsOpen) {
        close();
    }
}

bool CacheReader::open(const std::string& filePath) {
    m_File.open(filePath, std::ios::binary);
    if (!m_File.is_open()) {
        m_LastError = "Failed to open file: " + filePath;
        return false;
    }
    m_IsOpen = true;

    if (!readHeader()) {
        close();
        return false;
    }

    if (!readStringTable()) {
        close();
        return false;
    }

    if (!readSymbols()) {
        close();
        return false;
    }

    return true;
}

bool CacheReader::close() {
    if (m_File.is_open()) {
        m_File.close();
    }
    m_IsOpen = false;
    m_StringTable.clear();
    m_Symbols.clear();
    m_Functions.clear();
    return true;
}

bool CacheReader::readHeader() {
    m_File.read(reinterpret_cast<char*>(&m_Header), sizeof(m_Header));

    if (std::memcmp(m_Header.magic, CSEC_MAGIC, 4) != 0) {
        m_LastError = "Invalid cache file magic";
        return false;
    }

    if (m_Header.version != CSEC_VERSION) {
        char buffer[100];
        sprintf(buffer, "Cache version mismatch: %d != %d", m_Header.version, CSEC_VERSION);
        m_LastError = buffer;
        return false;
    }

    return true;
}

bool CacheReader::readStringTable() {
    std::vector<char> stringData(m_Header.stringTableSize);
    m_File.read(stringData.data(), m_Header.stringTableSize);

    for (size_t i = 0; i < stringData.size();) {
        std::string str(&stringData[i]);
        m_StringTable.add(str);
        i += str.length() + 1;
    }

    return true;
}

bool CacheReader::readSymbols() {
    m_Symbols.resize(m_Header.symbolCount);
    for (uint32_t i = 0; i < m_Header.symbolCount; ++i) {
        m_File.read(reinterpret_cast<char*>(&m_Symbols[i]), sizeof(SymbolEntry));
    }
    return true;
}

bool CacheReader::validate(const std::string& sourceCode, PlatformType platform) {
    if (!m_IsOpen) {
        m_LastError = "Cache file not open";
        return false;
    }

    if (m_Header.platform != static_cast<uint16_t>(platform)) {
        m_LastError = "Platform mismatch";
        return false;
    }

    uint32_t hash = 0x12345678;
    for (size_t i = 0; i < sourceCode.size(); ++i) {
        hash = (hash << 5) | (hash >> 27);
        hash ^= static_cast<uint32_t>(sourceCode[i]);
    }

    if (m_Header.sourceHash != hash) {
        m_LastError = "Source hash mismatch";
        return false;
    }

    return true;
}

bool CacheReader::loadFunctions(std::vector<CompiledFunctionV2>& functions) {
    functions.clear();
    functions.reserve(m_Header.functionCount);

    for (uint32_t i = 0; i < m_Header.functionCount; ++i) {
        CompiledFunctionV2 func;

        FunctionHeaderV2 funcHeader;
        m_File.read(reinterpret_cast<char*>(&funcHeader), sizeof(funcHeader));

        func.name = m_StringTable.getStringAt(funcHeader.nameOffset);
        func.returnType = m_StringTable.getStringAt(funcHeader.returnTypeOffset);

        func.paramTypes.resize(funcHeader.paramCountOffset);
        for (uint32_t j = 0; j < funcHeader.paramCountOffset; ++j) {
            uint32_t paramOffset;
            m_File.read(reinterpret_cast<char*>(&paramOffset), sizeof(paramOffset));
            func.paramTypes[j] = m_StringTable.getStringAt(paramOffset);
        }

        func.machineCode.resize(funcHeader.codeSize);
        m_File.read(reinterpret_cast<char*>(func.machineCode.data()), funcHeader.codeSize);

        std::vector<RelocationEntry> relocs(funcHeader.relocationCount);
        for (uint32_t j = 0; j < funcHeader.relocationCount; ++j) {
            m_File.read(reinterpret_cast<char*>(&relocs[j]), sizeof(RelocationEntry));
        }
        func.relocations = std::move(relocs);

        functions.push_back(std::move(func));
    }

    m_Functions = functions;
    return true;
}

bool CacheReader::relocateAll(IExternalSymbolResolver* resolver, void* baseAddress) {
    if (!resolver) {
        m_LastError = "No symbol resolver provided";
        return false;
    }

    for (auto& func : m_Functions) {
        if (!relocateFunction(func, resolver, baseAddress)) {
            return false;
        }
    }

    return true;
}

#ifndef CSE_PLATFORM_EMBEDDED
bool CacheReader::relocateFunction(CompiledFunctionV2& func, IExternalSymbolResolver* resolver, void* baseAddress) {
    for (const auto& reloc : func.relocations) {
        if (reloc.symbolIndex >= m_Symbols.size()) {
            char buffer[100];
            sprintf(buffer, "Invalid symbol index: %d", reloc.symbolIndex);
            m_LastError = buffer;
            return false;
        }

        const auto& symbol = m_Symbols[reloc.symbolIndex];
        std::string symbolName = m_StringTable.getStringAt(symbol.nameOffset);

        void* targetAddr = resolver->resolve(symbolName);
        if (!targetAddr) {
            m_LastError = "Failed to resolve symbol: " + symbolName;
            return false;
        }

        char* codeBase = reinterpret_cast<char*>(baseAddress) + symbol.addressOffset;

        switch (reloc.type) {
            case RelocationType::X64_64: {
                codeBase[0] = 0x48;
                codeBase[1] = 0xb8;
                std::memcpy(codeBase + 2, &targetAddr, 8);
                break;
            }
            case RelocationType::X64_REL32: {
                int32_t offset = static_cast<int32_t>(reinterpret_cast<uintptr_t>(targetAddr) -
                                    (reinterpret_cast<uintptr_t>(baseAddress) + reloc.codeOffset + 5));
                std::memcpy(codeBase, &offset, 4);
                break;
            }
            default:
                m_LastError = "Unsupported relocation type";
                return false;
        }
    }

    return true;
}
#else
// 嵌入式平台上的空实现
bool CacheReader::relocateFunction(CompiledFunctionV2& func, IExternalSymbolResolver* resolver, void* baseAddress) {
    m_LastError = "Relocation not supported on embedded platforms";
    return false;
}
#endif

} // namespace cse
