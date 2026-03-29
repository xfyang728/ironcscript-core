#include "StringTable.h"
#include <cstring>

namespace cse {

uint32_t StringTable::add(const std::string& str) {
    if (str.empty()) {
        return 0;
    }

    auto it = m_OffsetMap.find(str);
    if (it != m_OffsetMap.end()) {
        return it->second;
    }

    uint32_t offset = static_cast<uint32_t>(m_Data.size());
    m_Data.append(str);
    m_Data.push_back('\0');
    m_OffsetMap[str] = offset;
    m_Strings.push_back(str);
    return offset;
}

uint32_t StringTable::getOffset(const std::string& str) const {
    auto it = m_OffsetMap.find(str);
    if (it != m_OffsetMap.end()) {
        return it->second;
    }
    return 0xFFFFFFFF;
}

bool StringTable::contains(const std::string& str) const {
    return m_OffsetMap.find(str) != m_OffsetMap.end();
}

const std::string& StringTable::getStringAt(uint32_t offset) const {
    static const std::string empty;
    if (offset >= m_Data.size()) {
        return empty;
    }
    const char* ptr = m_Data.data() + offset;
    static std::string result;
    result = ptr;
    return result;
}

void StringTable::clear() {
    m_Data.clear();
    m_OffsetMap.clear();
    m_Strings.clear();
}

} // namespace cse
