/**
 * @file MockStdio.cpp
 * @brief Mock平台Stdio实现
 * @note 用于x64测试环境，直接使用标准stdio库
 */
#include "MockStdio.h"
#include <cstdio>
#include <cstdarg>
#include <iostream>

namespace cse {

MockStdio::MockStdio() {
}

int MockStdio::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = ::vprintf(format, args);
    va_end(args);
    return result;
}

int MockStdio::vprintf(const char* format, va_list args) {
    return ::vprintf(format, args);
}

int MockStdio::puts(const char* str) {
    return ::puts(str);
}

int MockStdio::putchar(int c) {
    return ::putchar(c);
}

int MockStdio::scanf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = ::vscanf(format, args);
    va_end(args);
    return result;
}

int MockStdio::vscanf(const char* format, va_list args) {
    return ::vscanf(format, args);
}

int MockStdio::getchar() {
    return ::getchar();
}

const char* MockStdio::getPlatformName() const {
    return "Mock";
}

}
