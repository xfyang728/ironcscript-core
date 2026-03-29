#include "RiscV64EmbeddedPlatform.h"
#include "PlatformAbstraction.h"

namespace cse {

void RiscV64EmbeddedPlatform::callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) {
    // 嵌入式平台的标准库函数调用逻辑
    // 由于这是一个抽象层，具体的调用实现会在代码生成器中完成
}

std::string RiscV64EmbeddedPlatform::getPlatformName() const {
    return PLATFORM_RISCV64;
}

void* RiscV64EmbeddedPlatform::getStandardLibraryFunctionAddress(const std::string& funcName) {
    // 在嵌入式平台上，标准库函数的地址会由代码生成器直接处理
    return nullptr;
}

void RiscV64EmbeddedPlatform::registerFFIFunction(const std::string& name, void* address) {
    m_ffiFunctions[name] = address;
}

void* RiscV64EmbeddedPlatform::getFFIFunctionAddress(const std::string& funcName) {
    auto it = m_ffiFunctions.find(funcName);
    if (it != m_ffiFunctions.end()) {
        return it->second;
    }
    return nullptr;
}

bool RiscV64EmbeddedPlatform::isFFIFunction(const std::string& funcName) const {
    return m_ffiFunctions.find(funcName) != m_ffiFunctions.end();
}

void* RiscV64EmbeddedPlatform::allocateExecutableMemory(size_t size) {
    // 在 K210 平台上，我们使用静态内存区域来模拟可执行内存
    // 注意：这只是一个简单的实现，实际应用中可能需要更复杂的内存管理
    static char memoryBuffer[4096]; // 4KB 内存缓冲区
    return memoryBuffer;
}

void RiscV64EmbeddedPlatform::freeExecutableMemory(void* memory, size_t size) {
    // 在 K210 平台上，我们不需要释放内存，因为使用的是静态缓冲区
}

bool RiscV64EmbeddedPlatform::setMemoryProtection(void* memory, size_t size, bool executable) {
    // 在 K210 平台上，我们假设内存始终是可执行的
    return true;
}

} // namespace cse