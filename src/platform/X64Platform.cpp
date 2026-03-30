#include "X64Platform.h"
#include "PlatformAbstraction.h"
#include "StandardLibrary.h"
#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#else
#include <dlfcn.h>
#endif

namespace cse {

void X64Platform::callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) {
    // 这里需要实现x64平台的标准库函数调用逻辑
    // 由于这是一个抽象层，具体的调用实现会在代码生成器中完成
}

std::string X64Platform::getPlatformName() const {
    return PLATFORM_X86_64;
}

void* X64Platform::getStandardLibraryFunctionAddress(const std::string& funcName) {
#ifdef _WIN32
    // 只从 msvcrt.dll 中加载标准库函数，这是 Windows 中标准的 C 运行时库
    static HMODULE hModule = nullptr;
    if (!hModule) {
        hModule = GetModuleHandleA("msvcrt.dll");
        if (!hModule) {
            hModule = LoadLibraryA("msvcrt.dll");
        }
    }
    if (hModule) {
        void* addr = reinterpret_cast<void*>(GetProcAddress(hModule, funcName.c_str()));
        if (addr) {
            std::cout << "[X64Platform] Found " << funcName << " in msvcrt.dll at " << addr << std::endl;
            return addr;
        }
    }
#else
    static void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle) {
        void* addr = dlsym(handle, funcName.c_str());
        return addr;
    }
    return nullptr;
#endif
}

void X64Platform::registerFFIFunction(const std::string& name, void* address) {
    m_FFIFunctions[name] = address;
}

void* X64Platform::getFFIFunctionAddress(const std::string& funcName) {
    auto it = m_FFIFunctions.find(funcName);
    if (it != m_FFIFunctions.end()) {
        return it->second;
    }
    return getStandardLibraryFunctionAddress(funcName);
}

bool X64Platform::isFFIFunction(const std::string& funcName) const {
    return m_FFIFunctions.find(funcName) != m_FFIFunctions.end();
}

void* X64Platform::allocateExecutableMemory(size_t size) {
#ifdef _WIN32
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#endif
}

void X64Platform::freeExecutableMemory(void* memory, size_t size) {
#ifdef _WIN32
    VirtualFree(memory, 0, MEM_RELEASE);
#else
    munmap(memory, size);
#endif
}

bool X64Platform::setMemoryProtection(void* memory, size_t size, bool executable) {
#ifdef _WIN32
    DWORD oldProtect;
    return VirtualProtect(memory, size, executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE, &oldProtect);
#else
    int prot = PROT_READ | PROT_WRITE;
    if (executable) {
        prot |= PROT_EXEC;
    }
    return mprotect(memory, size, prot) == 0;
#endif
}

} // namespace cse