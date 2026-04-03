/**
 * @file STM32Stdio.cpp
 * @brief STM32平台Stdio实现
 * @note 通过USART1进行字符输入输出
 */
#include "STM32Stdio.h"
#include <cstdio>
#include <cstdarg>

#if defined(STM32F4) || defined(STM32H7)
#include "stm32xx_hal.h"
extern UART_HandleTypeDef huart1;
#endif

namespace cse {

STM32Stdio::STM32Stdio() {
}

int STM32Stdio::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

int STM32Stdio::vprintf(const char* format, va_list args) {
    char buffer[256];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    for (int i = 0; i < len && i < (int)sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            outputChar('\r');
        }
        outputChar(buffer[i]);
    }

    return len;
}

int STM32Stdio::puts(const char* str) {
    outputString(str);
    outputChar('\r');
    outputChar('\n');
    return 0;
}

int STM32Stdio::putchar(int c) {
    if (c == '\n') {
        outputChar('\r');
    }
    return outputChar((char)c);
}

int STM32Stdio::scanf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vscanf(format, args);
    va_end(args);
    return result;
}

int STM32Stdio::vscanf(const char* format, va_list args) {
    (void)format;
    (void)args;
    return 0;
}

int STM32Stdio::getchar() {
#if defined(STM32F4) || defined(STM32H7)
    uint8_t ch;
    if (HAL_UART_Receive(&huart1, &ch, 1, 0) == HAL_OK) {
        return (int)ch;
    }
#endif
    return -1;
}

const char* STM32Stdio::getPlatformName() const {
    return "STM32";
}

int STM32Stdio::outputChar(char c) {
#if defined(STM32F4) || defined(STM32H7)
    HAL_UART_Transmit(&huart1, (uint8_t*)&c, 1, HAL_MAX_DELAY);
#endif
    return (int)(uint8_t)c;
}

int STM32Stdio::outputString(const char* str) {
    while (*str) {
        if (*str == '\n') {
            outputChar('\r');
        }
        outputChar(*str++);
    }
    return 0;
}

}
