/**
 * @file K210Stdio.cpp
 * @brief K210平台Stdio实现
 * @note 通过UART0进行字符输入输出
 */
#include "K210Stdio.h"
#include "K210UART.h"
#include <cstdio>
#include <cstring>
#include <cstdint>

// K210 UART寄存器地址
#define UART_BASE(n) (0x38000000UL + (n) * 0x1000000UL)
#define UART_REG(offset) (*(volatile uint32_t*)(UART_BASE(0) + (offset)))

// UART寄存器偏移
#define UART_DATA_REG 0x00
#define UART_STAT_REG 0x04
#define UART_CTRL_REG 0x08
#define UART_INTMASK_REG 0x0C
#define UART_INTR_REG 0x10
#define UART_BAUD_REG 0x14

// 状态寄存器位
#define UART_STAT_TXEMPTY (1 << 8)
#define UART_STAT_RXVAL (1 << 0)

// 控制寄存器位
#define UART_CTRL_TXEN (1 << 0)
#define UART_CTRL_RXEN (1 << 1)

namespace cse {

K210Stdio::K210Stdio() {
}

int K210Stdio::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

int K210Stdio::vprintf(const char* format, va_list args) {
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

int K210Stdio::puts(const char* str) {
    outputString(str);
    outputChar('\r');
    outputChar('\n');
    return 0;
}

int K210Stdio::putchar(int c) {
    if (c == '\n') {
        outputChar('\r');
    }
    return outputChar((char)c);
}

int K210Stdio::scanf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vscanf(format, args);
    va_end(args);
    return result;
}

int K210Stdio::vscanf(const char* format, va_list args) {
    (void)format;
    (void)args;
    return 0;
}

int K210Stdio::getchar() {
    volatile uint32_t stat = UART_REG(UART_STAT_REG);
    if (stat & UART_STAT_RXVAL) {
        return (int)(UART_REG(UART_DATA_REG) & 0xFF);
    }
    return -1;
}

const char* K210Stdio::getPlatformName() const {
    return "K210";
}

int K210Stdio::outputChar(char c) {
    volatile uint32_t* uart_ctrl = (volatile uint32_t*)(UART_BASE(0) + UART_CTRL_REG);
    volatile uint32_t* uart_stat = (volatile uint32_t*)(UART_BASE(0) + UART_STAT_REG);
    volatile uint32_t* uart_data = (volatile uint32_t*)(UART_BASE(0) + UART_DATA_REG);

    *uart_ctrl |= UART_CTRL_TXEN;

    while (!(*uart_stat & UART_STAT_TXEMPTY)) {
    }

    *uart_data = (uint32_t)c;

    return (int)(uint8_t)c;
}

int K210Stdio::outputString(const char* str) {
    while (*str) {
        if (*str == '\n') {
            outputChar('\r');
        }
        outputChar(*str++);
    }
    return 0;
}

}
