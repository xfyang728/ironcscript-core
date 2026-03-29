#ifndef CSE_WINMEMORYMANAGER_H
#define CSE_WINMEMORYMANAGER_H

#ifdef _WIN32

#include "MemoryManager.h"
#include <windows.h>

namespace cse {

class WinMemoryManager : public MemoryManager {
public:
    WinMemoryManager();
    ~WinMemoryManager();
    
    void initMemory();
};

} // namespace cse

#endif // _WIN32

#endif // CSE_WINMEMORYMANAGER_H