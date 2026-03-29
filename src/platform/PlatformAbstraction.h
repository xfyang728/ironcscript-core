#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace cse {

// 平台类型常量定义
const std::string PLATFORM_X86_64 = "x86-64";
const std::string PLATFORM_RISCV64 = "riscv64";

class PlatformAbstraction {
public:
    virtual ~PlatformAbstraction() = default;

    // 标准库函数调用
    virtual void callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) = 0;

    // 获取平台名称
    virtual std::string getPlatformName() const = 0;

    // 检查是否为标准库函数
    virtual bool isStandardLibraryFunction(const std::string& funcName) const;

    // 获取标准库函数地址
    virtual void* getStandardLibraryFunctionAddress(const std::string& funcName) = 0;

    // FFI 函数注册表集成
    virtual void registerFFIFunction(const std::string& name, void* address) = 0;
    virtual void* getFFIFunctionAddress(const std::string& funcName) = 0;
    virtual bool isFFIFunction(const std::string& funcName) const = 0;

    // 内存管理函数
    virtual void* allocateExecutableMemory(size_t size) = 0;
    virtual void freeExecutableMemory(void* memory, size_t size) = 0;
    virtual bool setMemoryProtection(void* memory, size_t size, bool executable) = 0;
};

// 平台工厂类
class PlatformFactory {
public:
    static PlatformAbstraction* createPlatformAbstraction();
};

} // namespace cse