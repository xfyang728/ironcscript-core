#ifndef CSE_MEMORYMANAGER_H
#define CSE_MEMORYMANAGER_H

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef ERROR
#undef CONST
#endif

#include <vector>
#include <initializer_list>

namespace cse {

class MemoryManager {
public:
    MemoryManager();
    virtual ~MemoryManager();
    
    void initMemory();
    void AddCode(const std::vector<unsigned char>& code);
    void AddCode(std::initializer_list<unsigned char> code);
    void AddCode(char buff[]);
    
    char* getMemoryBase() const;
    int getPageSize() const;
    
protected:
    int pageSize;
    char* m_MemBase;
    size_t m_CurrentOffset;
};

} // namespace cse

#endif // CSE_MEMORYMANAGER_H