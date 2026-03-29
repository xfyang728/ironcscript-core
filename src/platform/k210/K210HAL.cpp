#include "K210HAL.h"

#define FPIOA_UART0_TX 17
#define FUNC_UART0_TX 3

static volatile uint64_t g_ticks = 0;

void k210_uart_init(uint32_t baud) {
    (void)baud;
}

int k210_uart_putchar(char c) {
    (void)c;
    return c;
}

int k210_uart_getchar(void) {
    return -1;
}

int k210_uart_write(const char* data, size_t len) {
    (void)data;
    return len;
}

int k210_uart_read(char* data, size_t len, uint32_t timeout_ms) {
    (void)data;
    (void)len;
    (void)timeout_ms;
    return 0;
}

void k210_spi3_init(void) {
}

int k210_spi3_flash_read(uint32_t addr, uint8_t* buffer, size_t len) {
    (void)addr;
    (void)buffer;
    (void)len;
    return 0;
}

int k210_spi3_flash_write(uint32_t addr, const uint8_t* data, size_t len) {
    (void)addr;
    (void)data;
    (void)len;
    return 0;
}

int k210_spi3_flash_erase(uint32_t addr, size_t len) {
    (void)addr;
    (void)len;
    return 0;
}

void k210_delay_ms(uint32_t ms) {
    (void)ms;
}

uint64_t k210_get_ticks(void) {
    return g_ticks++;
}

void k210_jump_to(uint32_t addr) {
    typedef void (*Entry)(void);
    Entry entry = (Entry)(uintptr_t)addr;
    (void)entry;
}
