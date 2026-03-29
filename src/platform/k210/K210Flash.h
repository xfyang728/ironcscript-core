#ifndef K210_FLASH_H
#define K210_FLASH_H

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

void k210_uart_init(uint32_t baud);
int k210_uart_putchar(char c);
int k210_uart_write(const char* data, size_t len);
int k210_uart_read(char* data, size_t len, uint32_t timeout_ms);

void k210_spi3_init(void);
int k210_spi3_flash_read(uint32_t addr, uint8_t* buffer, size_t len);
int k210_spi3_flash_write(uint32_t addr, const uint8_t* data, size_t len);
int k210_spi3_flash_erase(uint32_t addr, size_t len);

void k210_delay_ms(uint32_t ms);
uint64_t k210_get_ticks(void);
void k210_jump_to(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif
