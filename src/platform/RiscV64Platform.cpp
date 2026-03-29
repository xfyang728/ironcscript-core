#include "RiscV64Platform.h"
#include "PlatformAbstraction.h"

#ifndef _WIN32
#include <sys/mman.h>
#include <unistd.h>
#include <dlfcn.h>
#else
#include <windows.h>
#endif

namespace cse {

void RiscV64Platform::callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) {
    // RISC-V 非嵌入式平台的标准库函数调用逻辑
    // 由于这是一个抽象层，具体的调用实现会在代码生成器中完成
}

std::string RiscV64Platform::getPlatformName() const {
    return PLATFORM_RISCV64;
}

void* RiscV64Platform::getStandardLibraryFunctionAddress(const std::string& funcName) {
    // 在非嵌入式 RISC-V 平台上，使用 dlsym 获取标准库函数地址
#ifndef _WIN32
    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle) {
        void* addr = dlsym(handle, funcName.c_str());
        dlclose(handle);
        return addr;
    }
#else
    // Windows 平台上的替代实现
    return nullptr;
#endif
    return nullptr;
}

void RiscV64Platform::registerFFIFunction(const std::string& name, void* address) {
    m_ffiFunctions[name] = address;
}

void* RiscV64Platform::getFFIFunctionAddress(const std::string& funcName) {
    auto it = m_ffiFunctions.find(funcName);
    if (it != m_ffiFunctions.end()) {
        return it->second;
    }
    return nullptr;
}

bool RiscV64Platform::isFFIFunction(const std::string& funcName) const {
    return m_ffiFunctions.find(funcName) != m_ffiFunctions.end();
}

void* RiscV64Platform::allocateExecutableMemory(size_t size) {
    // 在非嵌入式 RISC-V 平台上，使用 mmap 分配可执行内存
#ifndef _WIN32
    return mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#else
    // Windows 平台上的替代实现
    return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#endif
}

void RiscV64Platform::freeExecutableMemory(void* memory, size_t size) {
    // 在非嵌入式 RISC-V 平台上，使用 munmap 释放内存
    if (memory) {
#ifndef _WIN32
        munmap(memory, size);
#else
        // Windows 平台上的替代实现
        VirtualFree(memory, 0, MEM_RELEASE);
#endif
    }
}

bool RiscV64Platform::setMemoryProtection(void* memory, size_t size, bool executable) {
    // 在非嵌入式 RISC-V 平台上，使用 mprotect 设置内存保护
#ifndef _WIN32
    int prot = PROT_READ | PROT_WRITE;
    if (executable) {
        prot |= PROT_EXEC;
    }
    return mprotect(memory, size, prot) == 0;
#else
    // Windows 平台上的替代实现
    DWORD newProtect = executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE;
    DWORD oldProtect;
    return VirtualProtect(memory, size, newProtect, &oldProtect) != 0;
#endif
}

} // namespace cse