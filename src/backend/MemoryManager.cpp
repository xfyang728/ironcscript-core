#include "MemoryManager.h"
#include <malloc.h> 
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif
#include <iostream>
#include <vector>

namespace cse {

MemoryManager::MemoryManager() {
    pageSize = 1024*1024;
    m_MemBase = nullptr;
    m_CurrentOffset = 0;
}

MemoryManager::~MemoryManager() {
    if (m_MemBase != nullptr) {
#ifdef _WIN32
        VirtualFree(m_MemBase, 0, MEM_RELEASE);
#else
        munmap(m_MemBase, pageSize);
#endif
        m_MemBase = nullptr;
    }
}

void MemoryManager::initMemory() {
    if (m_MemBase != nullptr) {
        return;
    }
#ifdef _WIN32
    m_MemBase = (char*)VirtualAlloc(NULL, pageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    m_MemBase = (char*)mmap(
        NULL,                   //起始地址
        pageSize,          //内存大小(一般为页的整数倍, 32位1页=4k)
        PROT_READ | PROT_WRITE | PROT_EXEC, //映射区域权限:读|写|执行
        MAP_ANON | MAP_PRIVATE,  //匿名映射(非文件io), 私有映射
        -1,                      //要映射到内存中的文件描述符
        0                       //文件映射的偏移量,通常设为0,代表从页边界开始
    );
    if (m_MemBase == MAP_FAILED) {
        std::cerr << "Failed to allocate memory" << std::endl;
        m_MemBase = nullptr;
        return;
    }
#endif
    m_CurrentOffset = 0;
}

void MemoryManager::AddCode(const std::vector<unsigned char>& code) {
    // 默认实现，将代码复制到可执行内存
    if (m_MemBase != nullptr && !code.empty()) {
        size_t codeSize = code.size();
        memcpy(m_MemBase + m_CurrentOffset, code.data(), codeSize);
        std::cout << "Code added to memory. Size: " << codeSize << " bytes, Offset: " << m_CurrentOffset << std::endl;
        m_CurrentOffset += codeSize;
    }
}

void MemoryManager::AddCode(std::initializer_list<unsigned char> code) {
    // 将初始化列表转换为 vector，然后调用现有的 AddCode 方法
    std::vector<unsigned char> codeVector(code);
    AddCode(codeVector);
}

void MemoryManager::AddCode(char buff[]) {
    // 将字符数组转换为vector，然后调用现有的AddCode方法
    std::vector<unsigned char> codeVector;
    int i = 0;
    while (buff[i] != '\0') {
        codeVector.push_back(static_cast<unsigned char>(buff[i]));
        i++;
    }
    AddCode(codeVector);
}

char* MemoryManager::getMemoryBase() const {
    return m_MemBase;
}

int MemoryManager::getPageSize() const {
    return pageSize;
}

} // namespace cse