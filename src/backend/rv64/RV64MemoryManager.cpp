#include "RV64MemoryManager.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

#ifndef _WIN32
#include <sys/mman.h>
#endif

namespace cse {

RV64MemoryManager::RV64MemoryManager() : MemoryManager(), m_OptimizedForK210(false) {
    pageSize = 4096; // RISC-V 64 标准页大小
}

RV64MemoryManager::~RV64MemoryManager() {
    if (m_MemBase != nullptr) {
        #ifndef _WIN32
        munmap(m_MemBase, MAX_MEMORY_SIZE);
        #else
        VirtualFree(m_MemBase, 0, MEM_RELEASE);
        #endif
        m_MemBase = nullptr;
    }
}

void RV64MemoryManager::initMemory() {
    if (m_MemBase != nullptr) {
        return;
    }
    
    size_t memorySize = m_OptimizedForK210 ? K210_MEMORY_LIMIT : MAX_MEMORY_SIZE;
    
    #ifndef _WIN32
    m_MemBase = (char*)mmap(
        NULL,                   // 起始地址
        memorySize,             // 内存大小
        PROT_READ | PROT_WRITE | PROT_EXEC, // 映射区域权限:读|写|执行
        MAP_ANON | MAP_PRIVATE, // 匿名映射, 私有映射
        -1,                     // 要映射到内存中的文件描述符
        0                       // 文件映射的偏移量
    );
    
    if (m_MemBase == MAP_FAILED) {
        std::cerr << "Failed to allocate memory for RV64" << std::endl;
        m_MemBase = nullptr;
        return;
    }
    #else
    // 在 Windows 平台上，使用 VirtualAlloc 替代 mmap
    m_MemBase = (char*)VirtualAlloc(NULL, memorySize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    if (m_MemBase == nullptr) {
        std::cerr << "Failed to allocate memory for RV64" << std::endl;
        return;
    }
    #endif
    
    std::cout << "RV64 memory allocated successfully. Size: " << memorySize << " bytes" << std::endl;
    m_CurrentOffset = 0;
}

void RV64MemoryManager::setMemoryProtection(void* address, size_t size, int protection) {
    if (m_MemBase == nullptr) {
        std::cerr << "Memory not initialized" << std::endl;
        return;
    }
    
    #ifndef _WIN32
    int prot = 0;
    if (protection & PROT_READ) prot |= PROT_READ;
    if (protection & PROT_WRITE) prot |= PROT_WRITE;
    if (protection & PROT_EXEC) prot |= PROT_EXEC;
    
    if (mprotect(address, size, prot) == -1) {
        std::cerr << "Failed to set memory protection" << std::endl;
    }
    #else
    // 在 Windows 平台上，使用 VirtualProtect 替代 mprotect
    // 定义保护常量
    const int PROT_READ = 1;
    const int PROT_WRITE = 2;
    const int PROT_EXEC = 4;
    
    DWORD newProtect = 0;
    if (protection & PROT_READ) newProtect |= PAGE_READONLY;
    if (protection & PROT_WRITE) newProtect |= PAGE_READWRITE;
    if (protection & PROT_EXEC) newProtect |= PAGE_EXECUTE;
    if ((protection & PROT_READ) && (protection & PROT_EXEC)) newProtect |= PAGE_EXECUTE_READ;
    if ((protection & PROT_READ) && (protection & PROT_WRITE) && (protection & PROT_EXEC)) newProtect |= PAGE_EXECUTE_READWRITE;
    
    DWORD oldProtect;
    if (!VirtualProtect(address, size, newProtect, &oldProtect)) {
        std::cerr << "Failed to set memory protection" << std::endl;
    }
    #endif
}

bool RV64MemoryManager::isMemoryWithinLimit() const {
    size_t memorySize = m_OptimizedForK210 ? K210_MEMORY_LIMIT : MAX_MEMORY_SIZE;
    return m_CurrentOffset < memorySize;
}

void RV64MemoryManager::optimizeForK210() {
    m_OptimizedForK210 = true;
    std::cout << "Optimized memory manager for K210 platform" << std::endl;
    
    // 如果已经分配了内存，重新分配以适应 K210 的内存限制
    if (m_MemBase != nullptr) {
        #ifndef _WIN32
        munmap(m_MemBase, MAX_MEMORY_SIZE);
        #else
        VirtualFree(m_MemBase, 0, MEM_RELEASE);
        #endif
        m_MemBase = nullptr;
        initMemory();
    }
}

} // namespace cse