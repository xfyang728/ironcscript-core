#ifndef CSE_CACHE_READER_H
#define CSE_CACHE_READER_H

#include "CacheHeader.h"
#include "StringTable.h"
#include "../CompiledCache.h"
#include <string>
#include <vector>
#include <fstream>
#include <memory>

namespace cse {

class CacheReader {
public:
    CacheReader();
    ~CacheReader();

    bool open(const std::string& filePath);
    bool close();
    bool isOpen() const { return m_IsOpen; }

    bool validate(const std::string& sourceCode, PlatformType platform);
    bool loadFunctions(std::vector<CompiledFunctionV2>& functions);

    bool relocateAll(IExternalSymbolResolver* resolver, void* baseAddress);
    bool relocateFunction(CompiledFunctionV2& func, IExternalSymbolResolver* resolver, void* baseAddress);

    const std::string& getLastError() const { return m_LastError; }
    CacheHeaderV2 getHeader() const { return m_Header; }

private:
    bool readHeader();
    bool readStringTable();
    bool readSymbols();

    std::ifstream m_File;
    bool m_IsOpen;
    std::string m_LastError;
    CacheHeaderV2 m_Header;
    StringTable m_StringTable;
    std::vector<SymbolEntry> m_Symbols;
    std::vector<CompiledFunctionV2> m_Functions;
};

} // namespace cse

#endif // CSE_CACHE_READER_H
