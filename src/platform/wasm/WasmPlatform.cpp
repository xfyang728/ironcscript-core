#include "WasmPlatform.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

namespace cse {

WasmPlatform::WasmPlatform() {
    std::cout << "[WasmPlatform] WASM platform initialized" << std::endl;
}

WasmPlatform::~WasmPlatform() {
    std::cout << "[WasmPlatform] WASM platform destroyed" << std::endl;
}

void WasmPlatform::callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) {
    // WASM 平台的标准库调用由代码生成器通过 import 实现
    // 这里仅作为抽象层接口保留
    std::cout << "[WasmPlatform] callStandardLibraryFunction: " << funcName << std::endl;
}

std::string WasmPlatform::getPlatformName() const {
    return PLATFORM_WASM;
}

void* WasmPlatform::getStandardLibraryFunctionAddress(const std::string& funcName) {
    // WASM 平台的标准库函数通过 Emscripten 的 libc 提供
    // 在 JIT 执行模式下，这些函数地址由 Emscripten 运行时提供
    // 返回 nullptr 表示需要由运行时解析
    std::cout << "[WasmPlatform] getStandardLibraryFunctionAddress: " << funcName << std::endl;

    // 对于 WASM 平台，标准库函数已经由 Emscripten 链接
    // 尝试从 dlsym 获取（Emscripten 支持有限的 dlsym）
    // 实际上在 WASM 中，这些函数在编译时已经链接
    return nullptr;
}

void WasmPlatform::registerFFIFunction(const std::string& name, void* address) {
    m_FFIFunctions[name] = address;
}

void* WasmPlatform::getFFIFunctionAddress(const std::string& funcName) {
    auto it = m_FFIFunctions.find(funcName);
    if (it != m_FFIFunctions.end()) {
        return it->second;
    }
    return nullptr;
}

bool WasmPlatform::isFFIFunction(const std::string& funcName) const {
    return m_FFIFunctions.find(funcName) != m_FFIFunctions.end();
}

void* WasmPlatform::allocateExecutableMemory(size_t size) {
    // WASM 不支持真正的可执行内存分配
    // 使用 malloc 分配普通内存，JIT 代码将在此内存中模拟执行
    void* memory = std::malloc(size);
    if (memory) {
        std::memset(memory, 0, size);
    }
    std::cout << "[WasmPlatform] allocateExecutableMemory: " << size << " bytes at " << memory << std::endl;
    return memory;
}

void WasmPlatform::freeExecutableMemory(void* memory, size_t size) {
    (void)size;
    std::cout << "[WasmPlatform] freeExecutableMemory: " << memory << std::endl;
    std::free(memory);
}

bool WasmPlatform::setMemoryProtection(void* memory, size_t size, bool executable) {
    (void)memory;
    (void)size;
    (void)executable;
    // WASM 不支持内存保护属性修改
    // 总是返回 true，表示操作"成功"（无实际效果）
    return true;
}

} // namespace cse
