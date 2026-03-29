#ifndef K210_HAL_H
#define K210_HAL_H

#include <cstdint>
#include <cstddef>
#include <cstdbool>

#ifdef __cplusplus
extern "C" {
#endif

#define K210_UART0_BASE    0x38000000
#define K210_SYSCTL_BASE   0x50440000
#define K210_SPI3_BASE      0x53100000
#define K210_FPIOA_BASE     0x502D0000
#define K210_PLIC_BASE      0x0C000000

#define K210_FLASH_BASE     0x00000000
#define K210_FLASH_SIZE     (8 * 1024 * 1024)

typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t STATUS;
    volatile uint32_t CTRL;
    volatile uint32_t INTFLAG;
    volatile uint32_t LINECTRL;
    volatile uint32_t LINECTRL2;
    volatile uint32_t FIFOCFG;
    volatile uint32_t FIFOTRIG;
    volatile uint32_t INTEN;
    volatile uint32_t INTSTAT;
    volatile uint32_t RESERVED[0x33];
} k210_uart_t;

typedef struct {
    volatile uint32_t CLKEN;
    volatile uint32_t CLKTHRESHOLD;
    volatile uint32_t PLLSOC;
    volatile uint32_t PLLGPU;
    volatile uint32_t PLLDISP;
    volatile uint32_t CLKSEL0;
    volatile uint32_t CLKSEL1;
    volatile uint32_t RESERVED0;
    volatile uint32_t PERIPHERAL_CLKEN;
    volatile uint32_t PERIPHERAL_CLKDIV;
    volatile uint32_t SOFTRESET;
    volatile uint32_t RESERVED1[0x3D];
    volatile uint32_t CHIP_ID;
} k210_sysctl_t;

typedef struct {
    volatile uint32_t RESERVED0;
    volatile uint32_t SPI_SSIENR;
    volatile uint32_t SPI_MWCR;
    volatile uint32_t SPI_SSIENR2;
    volatile uint32_t RESERVED1;
    volatile uint32_t SPI_MW_DRv_0;
    volatile uint32_t SPI_MW_DRV_1;
    volatile uint32_t RESERVED2;
    volatile uint32_t SPI_SER;
    volatile uint32_t SPI_Baudr;
    volatile uint32_t SPI_TXFTLR;
    volatile uint32_t SPI_RXFTLR;
    volatile uint32_t SPI_TXFLR;
    volatile uint32_t SPI_RXFLR;
    volatile uint32_t SPI_SR;
    volatile uint32_t SPI_IMR;
    volatile uint32_t SPI_ISR;
    volatile uint32_t SPI_RISR;
    volatile uint32_t SPI_TXOICR;
    volatile uint32_t SPI_RXOICR;
    volatile uint32_t SPI_RXUICR;
    volatile uint32_t SPI_MSTICR;
    volatile uint32_t SPI_ICR;
    volatile uint32_t SPI_DMACR;
    volatile uint32_t SPI_DMATDLR;
    volatile uint32_t SPI_DMARDLR;
    volatile uint32_t SPI_IDR;
    volatile uint32_t SPI_VERSION;
    volatile uint32_t SPI_DR[256];
    volatile uint32_t SPI_RX_SAMPLE_DELAY;
    volatile uint32_t SPI_SPIRXDCR;
    volatile uint32_t SPITXBACR;
    volatile uint32_t SPITXBAHR;
    volatile uint32_t SPIRXBAHR;
    volatile uint32_t SPITXBALR;
    volatile uint32_t SPIRXBALR;
} k210_spi_t;

typedef struct {
    volatile uint32_t PINS[32];
} k210_fpioa_t;

#define UART0 ((k210_uart_t*)K210_UART0_BASE)
#define SYSCTL ((k210_sysctl_t*)K210_SYSCTL_BASE)
#define SPI3 ((k210_spi_t*)K210_SPI3_BASE)
#define FPIOA ((k210_fpioa_t*)K210_FPIOA_BASE)

void k210_uart_init(uint32_t baud);
int k210_uart_putchar(char c);
int k210_uart_getchar(void);
int k210_uart_write(const char* data, size_t len);
int k210_uart_read(char* data, size_t len, uint32_t timeout_ms);

void k210_delay_ms(uint32_t ms);
uint64_t k210_get_ticks(void);

void k210_jump_to(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif
