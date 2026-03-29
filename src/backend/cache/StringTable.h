#ifndef CSE_STRING_TABLE_H
#define CSE_STRING_TABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace cse {

class StringTable {
public:
    uint32_t add(const std::string& str);
    uint32_t getOffset(const std::string& str) const;
    bool contains(const std::string& str) const;
    const char* getData() const { return m_Data.data(); }
    size_t getSize() const { return m_Data.size(); }
    const std::string& getStringAt(uint32_t offset) const;
    void clear();
    size_t getCount() const { return m_OffsetMap.size(); }

private:
    std::string m_Data;
    std::unordered_map<std::string, uint32_t> m_OffsetMap;
    std::vector<std::string> m_Strings;
};

} // namespace cse

#endif // CSE_STRING_TABLE_H
