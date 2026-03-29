#ifndef CSE_CACHE_WRITER_H
#define CSE_CACHE_WRITER_H

#include "CacheHeader.h"
#include "StringTable.h"
#include <string>
#include <vector>
#include <fstream>

namespace cse {

class CacheWriter {
public:
    CacheWriter();
    ~CacheWriter();

    bool open(const std::string& filePath);
    bool close();

    void writeHeader(const CacheHeaderV2& header);
    void addString(const std::string& str);
    void addSymbol(const std::string& name, uint32_t codeOffset, uint16_t type);
    void addFunction(const CompiledFunctionV2& func);
    void addRelocation(uint32_t symbolIndex, const RelocationEntry& reloc);

    const StringTable& getStringTable() const { return m_StringTable; }

private:
    std::ofstream m_File;
    StringTable m_StringTable;
    std::vector<SymbolEntry> m_Symbols;
    std::vector<CompiledFunctionV2> m_Functions;
    std::vector<std::vector<RelocationEntry>> m_Relocations;
    bool m_IsOpen;
};

} // namespace cse

#endif // CSE_CACHE_WRITER_H
