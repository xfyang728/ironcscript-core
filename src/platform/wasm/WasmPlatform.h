#pragma once

#include "../PlatformAbstraction.h"
#include <unordered_map>

namespace cse {

/**
 * @brief WASM 平台抽象层实现
 * @details 为 Emscripten WASM 编译目标提供平台抽象，包括：
 *          - 标准库函数调用（通过 Emscripten 的 libc 实现）
 *          - FFI 函数注册表
 *          - 内存管理（WASM 线性内存）
 *          - 标准输出桥接
 */
class WasmPlatform : public PlatformAbstraction {
private:
    std::unordered_map<std::string, void*> m_FFIFunctions;

public:
    WasmPlatform();
    ~WasmPlatform() override;

    /**
     * @brief 调用标准库函数
     * @param funcName 函数名
     * @param args 参数列表
     */
    void callStandardLibraryFunction(const std::string& funcName, const std::vector<void*>& args) override;

    /**
     * @brief 获取平台名称
     * @return 平台标识字符串
     */
    std::string getPlatformName() const override;

    /**
     * @brief 获取标准库函数地址
     * @param funcName 函数名
     * @return 函数地址，找不到返回 nullptr
     */
    void* getStandardLibraryFunctionAddress(const std::string& funcName) override;

    /**
     * @brief 注册 FFI 函数
     * @param name 函数名
     * @param address 函数地址
     */
    void registerFFIFunction(const std::string& name, void* address) override;

    /**
     * @brief 获取 FFI 函数地址
     * @param funcName 函数名
     * @return 函数地址
     */
    void* getFFIFunctionAddress(const std::string& funcName) override;

    /**
     * @brief 检查是否为 FFI 函数
     * @param funcName 函数名
     * @return 是否已注册
     */
    bool isFFIFunction(const std::string& funcName) const override;

    /**
     * @brief 分配可执行内存
     * @param size 内存大小
     * @return 内存指针
     * @note WASM 不支持真正的可执行内存，使用普通内存模拟
     */
    void* allocateExecutableMemory(size_t size) override;

    /**
     * @brief 释放可执行内存
     * @param memory 内存指针
     * @param size 内存大小
     */
    void freeExecutableMemory(void* memory, size_t size) override;

    /**
     * @brief 设置内存保护属性
     * @param memory 内存指针
     * @param size 内存大小
     * @param executable 是否可执行
     * @return 是否成功
     * @note WASM 中此操作无实际效果
     */
    bool setMemoryProtection(void* memory, size_t size, bool executable) override;
};

} // namespace cse
