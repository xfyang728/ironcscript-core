#ifdef _WIN32

#include "WinMemoryManager.h"
#include <iostream>

namespace cse {

WinMemoryManager::WinMemoryManager() : MemoryManager() {
    pageSize = 1024 * 1024; // Windows 默认页大小
}

WinMemoryManager::~WinMemoryManager() {
    if (m_MemBase != nullptr) {
        VirtualFree(m_MemBase, 0, MEM_RELEASE);
        m_MemBase = nullptr;
    }
}

void WinMemoryManager::initMemory() {
    if (m_MemBase != nullptr) {
        return;
    }
    
    m_MemBase = (char*)VirtualAlloc(NULL, pageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    if (m_MemBase == nullptr) {
        std::cerr << "Failed to allocate memory for Windows" << std::endl;
        return;
    }
    
    std::cout << "Windows memory allocated successfully. Size: " << pageSize << " bytes" << std::endl;
    m_CurrentOffset = 0;
}

} // namespace cse

#endif // _WIN32