/**
 * @file IStandardStdio.h
 * @brief C标准库stdio抽象接口定义
 * @note 提供跨平台的printf/puts/scanf等函数支持，用于字节码脚本
 */
#ifndef CSE_HAL_STANDARD_STDIO_H
#define CSE_HAL_STANDARD_STDIO_H

#include <cstdarg>
#include <cstdint>

namespace cse {

/**
 * @brief C标准库stdio抽象接口
 * @details 提供跨平台的格式化输入输出功能，支持K210、STM32等嵌入式平台
 */
class IStandardStdio {
public:
    virtual ~IStandardStdio() = default;

    /**
     * @brief 格式化打印函数
     * @param format 格式字符串
     * @param ... 可变参数列表
     * @return 打印的字符数（不含终止符），错误时返回负数
     */
    virtual int printf(const char* format, ...) = 0;

    /**
     * @brief 可变参数版格式化打印
     * @param format 格式字符串
     * @param args 可变参数列表
     * @return 打印的字符数（不含终止符），错误时返回负数
     */
    virtual int vprintf(const char* format, va_list args) = 0;

    /**
     * @brief 打印字符串并换行
     * @param str 要打印的字符串
     * @return 非负数表示成功，EOF表示错误
     * @note 等同于 printf("%s\n", str)
     */
    virtual int puts(const char* str) = 0;

    /**
     * @brief 打印单个字符
     * @param c 要打印的字符
     * @return 打印的字符，错误时返回EOF
     */
    virtual int putchar(int c) = 0;

    /**
     * @brief 格式化扫描函数
     * @param format 格式字符串
     * @param ... 可变参数列表
     * @return 成功匹配和赋值的项数
     */
    virtual int scanf(const char* format, ...) = 0;

    /**
     * @brief 可变参数版格式化扫描
     * @param format 格式字符串
     * @param args 可变参数列表
     * @return 成功匹配和赋值的项数
     */
    virtual int vscanf(const char* format, va_list args) = 0;

    /**
     * @brief 获取单个字符
     * @return 读取的字符，错误或到达文件末尾时返回EOF
     */
    virtual int getchar() = 0;

    /**
     * @brief 获取平台名称
     * @return 平台名称字符串
     */
    virtual const char* getPlatformName() const = 0;
};

}

#endif
