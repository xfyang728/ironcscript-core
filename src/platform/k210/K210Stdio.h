/**
 * @file K210Stdio.h
 * @brief K210平台Stdio实现
 * @note 通过UART0输出到串口
 */
#ifndef CSE_PLATFORM_K210_STDIO_H
#define CSE_PLATFORM_K210_STDIO_H

#include "hal/IStandardStdio.h"
#include <cstdarg>

namespace cse {

class K210Stdio : public IStandardStdio {
public:
    K210Stdio();
    ~K210Stdio() override = default;

    int printf(const char* format, ...) override;
    int vprintf(const char* format, va_list args) override;
    int puts(const char* str) override;
    int putchar(int c) override;
    int scanf(const char* format, ...) override;
    int vscanf(const char* format, va_list args) override;
    int getchar() override;
    const char* getPlatformName() const override;

private:
    int outputChar(char c);
    int outputString(const char* str);
};

}

#endif
