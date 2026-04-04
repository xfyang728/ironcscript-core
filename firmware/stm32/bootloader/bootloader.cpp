/**
 * @brief STM32 Bootloader for IronCScript VM
 *
 * This bootloader:
 * 1. Initializes SPI for W25Q64 Flash
 * 2. Reads firmware header from SPI Flash
 * 3. Copies firmware to internal SRAM
 * 4. Jumps to firmware entry point
 *
 * Architecture:
 * - Internal Flash (0x08000000-0x08010000): Bootloader (max 64KB)
 * - External SPI Flash: Firmware image with header
 * - Internal SRAM (0x20000000-0x20005000): Firmware execution
 */

#include <cstdint>

extern "C" {

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

#define FLASH_BASE      0x08000000
#define SRAM_BASE       0x20000000
#define SPI_FLASH_BASE  0x00000000

#define W25Q64_SPI_CS_PORT  0
#define W25Q64_SPI_CS_PIN   4

#define FIRMWARE_MAGIC   0x43530000
#define FIRMWARE_OFFSET  0x1000

typedef void (*JumpFunc)(void);

struct FirmwareHeader {
    uint32_t magic;
    uint32_t version;
    uint32_t entry_point;
    uint32_t size;
    uint32_t crc32;
    uint32_t reserved[2];
} __attribute__((packed));

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

static void SPI_Init(void);
static void SPI_CS_LOW(void);
static void SPI_CS_HIGH(void);
static uint8_t SPI_Transfer(uint8_t data);
static void SPI_Flash_ReadID(uint8_t *manufacturer, uint8_t *deviceId);
static void SPI_Flash_ReadData(uint32_t addr, uint8_t *buffer, uint32_t len);
static void LED_Toggle(void);

__attribute__((section(".isr_vector"), used))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))((uint32_t)&_estack),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    SVC_Handler,
    DebugMon_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    PendSV_Handler,
    SysTick_Handler,
};

static void CopyData(void) {
    uint32_t *src = &_sidata;
    uint32_t *dest = &_sdata;
    while (dest < &_edata) {
        *dest++ = *src++;
    }
}

static void ClearBss(void) {
    uint32_t *dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }
}

void Reset_Handler(void) {
    extern void SystemInit(void);
    SystemInit();
    CopyData();
    ClearBss();

    SPI_Init();

    uint8_t manu, devId;
    SPI_Flash_ReadID(&manu, &devId);
    (void)manu;
    (void)devId;

    FirmwareHeader header;
    SPI_Flash_ReadData(FIRMWARE_OFFSET, (uint8_t *)&header, sizeof(FirmwareHeader));

    if (header.magic != FIRMWARE_MAGIC) {
        while (1);
    }

    uint32_t firmware_addr = FIRMWARE_OFFSET + sizeof(FirmwareHeader);
    uint32_t *dest = (uint32_t *)SRAM_BASE;
    uint32_t words = (header.size + 3) / 4;

    for (uint32_t i = 0; i < words; i++) {
        if (i % 256 == 0) {
            LED_Toggle();
            SPI_CS_LOW();
            SPI_Transfer(0x03);
            SPI_Transfer((uint8_t)((firmware_addr >> 16) & 0xFF));
            SPI_Transfer((uint8_t)((firmware_addr >> 8) & 0xFF));
            SPI_Transfer((uint8_t)(firmware_addr & 0xFF));
        }

        uint32_t val = 0;
        val |= ((uint32_t)SPI_Transfer(0xFF)) << 0;
        val |= ((uint32_t)SPI_Transfer(0xFF)) << 8;
        val |= ((uint32_t)SPI_Transfer(0xFF)) << 16;
        val |= ((uint32_t)SPI_Transfer(0xFF)) << 24;

        *dest++ = val;
        firmware_addr += 4;
    }

    LED_Toggle();

    JumpFunc jump = (JumpFunc)header.entry_point;
    jump();

    while (1);
}

void NMI_Handler(void) { while (1); }
void HardFault_Handler(void) { while (1); }
void MemManage_Handler(void) { while (1); }
void BusFault_Handler(void) { while (1); }
void UsageFault_Handler(void) { while (1); }
void SVC_Handler(void) { while (1); }
void DebugMon_Handler(void) { while (1); }
void PendSV_Handler(void) { while (1); }
void SysTick_Handler(void) { while (1); }

static void SPI_Init(void) {
    volatile uint32_t *RCC_CR = (uint32_t *)0x40021000;
    volatile uint32_t *RCC_CFGR = (uint32_t *)0x40021004;
    volatile uint32_t *RCC_AHBENR = (uint32_t *)0x40021014;
    volatile uint32_t *FLASH_ACR = (uint32_t *)0x40022000;
    volatile uint32_t *RCC_APB2ENR = (uint32_t *)0x40021018;

    *RCC_CR = 0x00010000;
    while (!(*RCC_CR & 0x00020000));
    *RCC_CFGR = 0x00000002;
    while ((*RCC_CFGR & 0x0000000C) != 0x00000008);

    *FLASH_ACR = 0x00000010;

    *RCC_AHBENR = 0x00000014;

    *RCC_APB2ENR |= 0x0000000C;

    volatile uint32_t *GPIOB_MODER = (uint32_t *)0x40010C00;
    volatile uint32_t *GPIOB_ODR = (uint32_t *)0x40010C0C;
    *GPIOB_MODER = (*GPIOB_MODER & ~0x00003000) | 0x00001000;
    *GPIOB_ODR |= 0x0010;

    volatile uint32_t *SPI1_CR1 = (uint32_t *)0x40013000;
    volatile uint32_t *SPI1_CR2 = (uint32_t *)0x40013004;

    *SPI1_CR1 = 0x00000000;
    *SPI1_CR2 = 0x00000000;
    *SPI1_CR1 = 0x00000034;
    *SPI1_CR2 = 0x00000004;

    for (volatile int i = 0; i < 100000; i++);
}

static void SPI_CS_LOW(void) {
    volatile uint32_t *GPIOB_ODR = (uint32_t *)0x40010C0C;
    *GPIOB_ODR &= ~0x0010;
    for (volatile int i = 0; i < 10; i++);
}

static void SPI_CS_HIGH(void) {
    volatile uint32_t *GPIOB_ODR = (uint32_t *)0x40010C0C;
    *GPIOB_ODR |= 0x0010;
}

static uint8_t SPI_Transfer(uint8_t data) {
    volatile uint32_t *SPI1_DR = (uint32_t *)0x4001300C;
    volatile uint32_t *SPI1_SR = (uint32_t *)0x40013008;

    *SPI1_DR = data;
    while (!(*SPI1_SR & 0x02));
    return (uint8_t)*SPI1_DR;
}

static void SPI_Flash_ReadID(uint8_t *manufacturer, uint8_t *deviceId) {
    SPI_CS_LOW();
    SPI_Transfer(0x06);
    SPI_CS_HIGH();
    for (volatile int i = 0; i < 100; i++);

    SPI_CS_LOW();
    SPI_Transfer(0x9F);
    *manufacturer = SPI_Transfer(0xFF);
    *deviceId = SPI_Transfer(0xFF);
    SPI_Transfer(0xFF);
    SPI_CS_HIGH();
}

static void SPI_Flash_ReadData(uint32_t addr, uint8_t *buffer, uint32_t len) {
    SPI_CS_LOW();
    SPI_Transfer(0x03);
    SPI_Transfer((uint8_t)((addr >> 16) & 0xFF));
    SPI_Transfer((uint8_t)((addr >> 8) & 0xFF));
    SPI_Transfer((uint8_t)(addr & 0xFF));

    for (uint32_t i = 0; i < len; i++) {
        buffer[i] = SPI_Transfer(0xFF);
    }
    SPI_CS_HIGH();
}

static void LED_Toggle(void) {
    volatile uint32_t *GPIOB_ODR = (uint32_t *)0x40010C0C;
    *GPIOB_ODR ^= 0x0010;
}

}