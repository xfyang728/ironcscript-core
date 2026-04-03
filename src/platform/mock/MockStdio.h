/**
 * @file MockStdio.h
 * @brief Mock平台Stdio实现
 * @note 用于x64测试环境，输出到stdout
 */
#ifndef CSE_PLATFORM_MOCK_STDIO_H
#define CSE_PLATFORM_MOCK_STDIO_H

#include "hal/IStandardStdio.h"
#include <cstdarg>

namespace cse {

class MockStdio : public IStandardStdio {
public:
    MockStdio();
    ~MockStdio() override = default;

    int printf(const char* format, ...) override;
    int vprintf(const char* format, va_list args) override;
    int puts(const char* str) override;
    int putchar(int c) override;
    int scanf(const char* format, ...) override;
    int vscanf(const char* format, va_list args) override;
    int getchar() override;
    const char* getPlatformName() const override;
};

}

#endif
