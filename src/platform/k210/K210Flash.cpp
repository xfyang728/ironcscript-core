#include "K210Flash.h"
#include <spi.h>
#include <dmac.h>
#include <cstdio>

void k210_uart_init(uint32_t baud) {
    (void)baud;
}

int k210_uart_putchar(char c) {
    putchar(c);
    return c;
}

int k210_uart_write(const char* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        putchar(data[i]);
    }
    return len;
}

int k210_uart_read(char* data, size_t len, uint32_t timeout_ms) {
    (void)timeout_ms;
    size_t i = 0;
    while (i < len) {
        int c = getchar();
        if (c == EOF) break;
        data[i++] = (char)c;
    }
    return i;
}

void k210_spi3_init(void) {
    spi_init(SPI_DEVICE_3, SPI_WORK_MODE_0, SPI_FF_STANDARD, 8, 0);
    spi_set_clk_rate(SPI_DEVICE_3, 5000000);
}

int k210_spi3_flash_read(uint32_t addr, uint8_t* buffer, size_t len) {
    if (!buffer || len == 0) {
        return -1;
    }

    uint8_t cmd[4] = {0x03, (uint8_t)(addr >> 16), (uint8_t)(addr >> 8), (uint8_t)addr};

    spi_receive_data_standard(SPI_DEVICE_3, SPI_CHIP_SELECT_0, cmd, 4, buffer, len);

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
    for (volatile uint32_t i = 0; i < ms * 10000; i++) {
        __asm__ volatile ("nop");
    }
}

uint64_t k210_get_ticks(void) {
    return 0;
}

void k210_jump_to(uint32_t addr) {
    ((void (*)(void))addr)();
}
