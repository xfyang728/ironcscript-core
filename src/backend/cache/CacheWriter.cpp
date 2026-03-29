#include "CacheWriter.h"
#include <iostream>
#include <cstring>

namespace cse {

CacheWriter::CacheWriter()
    : m_IsOpen(false) {
}

CacheWriter::~CacheWriter() {
    if (m_IsOpen) {
        close();
    }
}

bool CacheWriter::open(const std::string& filePath) {
    m_File.open(filePath, std::ios::binary | std::ios::trunc);
    if (!m_File.is_open()) {
        std::cerr << "[CacheWriter] Failed to open file: " << filePath << std::endl;
        return false;
    }
    m_IsOpen = true;
    m_StringTable.clear();
    m_Symbols.clear();
    m_Functions.clear();
    m_Relocations.clear();
    return true;
}

bool CacheWriter::close() {
    if (!m_IsOpen) {
        return true;
    }

    CacheHeaderV2 header = {};
    std::memcpy(header.magic, CSEC_MAGIC, 4);
    header.version = CSEC_VERSION;
    header.stringTableSize = static_cast<uint32_t>(m_StringTable.getSize());
    header.symbolCount = static_cast<uint32_t>(m_Symbols.size());
    header.functionCount = static_cast<uint32_t>(m_Functions.size());

    uint32_t totalCodeSize = 0;
    for (const auto& func : m_Functions) {
        totalCodeSize += static_cast<uint32_t>(func.machineCode.size());
    }
    header.totalCodeSize = totalCodeSize;

    uint32_t dataOffset = sizeof(CacheHeaderV2);
    uint32_t stringTableOffset = dataOffset;
    uint32_t symbolTableOffset = stringTableOffset + header.stringTableSize;

    std::streampos currentPos = m_File.tellp();
    m_File.seekp(0, std::ios::beg);
    m_File.write(reinterpret_cast<const char*>(&header), sizeof(header));
    m_File.seekp(0, std::ios::end);

    m_File.write(m_StringTable.getData(), m_StringTable.getSize());

    for (const auto& symbol : m_Symbols) {
        m_File.write(reinterpret_cast<const char*>(&symbol), sizeof(symbol));
    }

    for (size_t i = 0; i < m_Functions.size(); ++i) {
        const auto& func = m_Functions[i];
        const auto& relocs = m_Relocations[i];

        FunctionHeaderV2 funcHeader = {};
        funcHeader.nameOffset = m_StringTable.getOffset(func.name);
        funcHeader.returnTypeOffset = m_StringTable.getOffset(func.returnType);
        funcHeader.codeSize = static_cast<uint32_t>(func.machineCode.size());
        funcHeader.relocationCount = static_cast<uint32_t>(relocs.size());

        funcHeader.paramCountOffset = 0;
        for (const auto& param : func.paramTypes) {
            uint32_t paramOffset = m_StringTable.add(param);
            m_File.write(reinterpret_cast<const char*>(&paramOffset), sizeof(paramOffset));
        }

        m_File.write(reinterpret_cast<const char*>(&funcHeader), sizeof(funcHeader));
        m_File.write(reinterpret_cast<const char*>(func.machineCode.data()), func.machineCode.size());

        for (const auto& reloc : relocs) {
            m_File.write(reinterpret_cast<const char*>(&reloc), sizeof(reloc));
        }
    }

    m_File.close();
    m_IsOpen = false;

    std::cout << "[CacheWriter] Saved: " << m_Symbols.size() << " symbols, "
              << m_Functions.size() << " functions, "
              << totalCodeSize << " bytes" << std::endl;
    return true;
}

void CacheWriter::addString(const std::string& str) {
    m_StringTable.add(str);
}

void CacheWriter::addSymbol(const std::string& name, uint32_t codeOffset, uint16_t type) {
    SymbolEntry entry = {};
    entry.nameOffset = m_StringTable.add(name);
    entry.addressOffset = codeOffset;
    entry.type = type;
    m_Symbols.push_back(entry);
}

void CacheWriter::addFunction(const CompiledFunctionV2& func) {
    m_Functions.push_back(func);
    m_Relocations.push_back({});
}

void CacheWriter::addRelocation(uint32_t symbolIndex, const RelocationEntry& reloc) {
    if (m_Relocations.empty()) {
        m_Relocations.push_back({});
    }
    if (symbolIndex < m_Relocations.size()) {
        m_Relocations[symbolIndex].push_back(reloc);
    }
}

} // namespace cse
