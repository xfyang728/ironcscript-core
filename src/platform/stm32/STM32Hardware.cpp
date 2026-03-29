#include "platform/stm32/STM32Hardware.h"
#include <cstring>

namespace cse {

STM32Hardware::STM32Hardware()
    : m_Model(Model::UNKNOWN)
    , m_FlashBase(0x08000000)
    , m_SRAMBase(0x20000000)
    , m_FlashSize(1024 * 1024)
    , m_SRAMSize(192 * 1024)
{
    m_Model = detectModel();
    initUART();
}

STM32Hardware::~STM32Hardware() {
}

STM32Hardware::Model STM32Hardware::detectModel() {
#if defined(CSE_STM32_F1)
    return Model::F1;
#elif defined(CSE_STM32_F4)
    return Model::F4;
#elif defined(CSE_STM32_H7)
    return Model::H7;
#elif defined(CSE_STM32_L4)
    return Model::L4;
#else
    return Model::F4;
#endif
}

bool STM32Hardware::initUART() {
    return true;
}

void STM32Hardware::delay(uint32_t ms) {
#ifdef CSE_STM32_HAL
    HAL_Delay(ms);
#else
    volatile uint32_t count = ms * 10000;
    while (count--) { __asm__("nop"); }
#endif
}

uint64_t STM32Hardware::getTicks() {
#ifdef CSE_STM32_HAL
    return HAL_GetTick();
#else
    return 0;
#endif
}

void STM32Hardware::reset() {
#ifdef CSE_STM32_HAL
    HAL_NVIC_SystemReset();
#else
#endif
}

void STM32Hardware::jumpTo(uint32_t address) {
#ifdef CSE_STM32_HAL
    typedef void (*ResetHandler)(void);
    volatile uint32_t* vectorTable = reinterpret_cast<volatile uint32_t*>(address);

    SCB->VTOR = address;
    __set_MSP(vectorTable[0]);

    ResetHandler resetHandler = reinterpret_cast<ResetHandler>(vectorTable[1]);
    resetHandler();
#else
    (void)address;
#endif
}

bool STM32Hardware::readFlash(uint32_t addr, uint8_t* buffer, size_t len) {
    if (addr < m_FlashBase || addr + len > m_FlashBase + m_FlashSize) {
        return false;
    }
    std::memcpy(buffer, reinterpret_cast<const void*>(addr), len);
    return true;
}

bool STM32Hardware::writeFlash(uint32_t addr, const uint8_t* data, size_t len) {
#ifdef CSE_STM32_HAL
    HAL_FLASH_Unlock();

    uint32_t pageError = 0;
    FLASH_EraseInitTypeDef eraseInit;
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = (addr - m_FlashBase) / 2048;
    eraseInit.NbSectors = 1;
    eraseInit.Banks = FLASH_BANK_1;

    if (HAL_FLASHEx_Erase(&eraseInit, &pageError) != HAL_OK) {
        HAL_FLASH_Lock();
        return false;
    }

    for (size_t i = 0; i < len; i += 4) {
        uint32_t word = data[i] | (data[i+1] << 8) | (data[i+2] << 16) | (data[i+3] << 24);
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i, word) != HAL_OK) {
            HAL_FLASH_Lock();
            return false;
        }
    }

    HAL_FLASH_Lock();
    return true;
#else
    (void)addr;
    (void)data;
    (void)len;
    return false;
#endif
}

bool STM32Hardware::eraseFlash(uint32_t addr, size_t len) {
#ifdef CSE_STM32_HAL
    HAL_FLASH_Unlock();

    uint32_t pageError = 0;
    FLASH_EraseInitTypeDef eraseInit;
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = (addr - m_FlashBase) / 2048;
    eraseInit.NbSectors = (len + 2047) / 2048;
    eraseInit.Banks = FLASH_BANK_1;

    bool result = (HAL_FLASHEx_Erase(&eraseInit, &pageError) == HAL_OK);
    HAL_FLASH_Lock();
    return result;
#else
    (void)addr;
    (void)len;
    return false;
#endif
}

int STM32Hardware::uartWrite(const uint8_t* data, size_t len) {
#ifdef CSE_STM32_HAL
    if (HAL_UART_Transmit(&huart1, const_cast<uint8_t*>(data), len, HAL_MAX_DELAY) != HAL_OK) {
        return -1;
    }
    return len;
#else
    (void)data;
    (void)len;
    return -1;
#endif
}

int STM32Hardware::uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) {
#ifdef CSE_STM32_HAL
    if (HAL_UART_Receive(&huart1, data, len, timeout_ms) != HAL_OK) {
        return -1;
    }
    return len;
#else
    (void)data;
    (void)len;
    (void)timeout_ms;
    return -1;
#endif
}

int STM32Hardware::uartAvailable() {
#ifdef CSE_STM32_HAL
    return (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET) ? 1 : 0;
#else
    return 0;
#endif
}

uint32_t STM32Hardware::getFlashSize() {
#ifdef CSE_STM32_HAL
    return *(reinterpret_cast<uint16_t*>(0x1FFF7A22));
#else
    return m_FlashSize;
#endif
}

uint32_t STM32Hardware::getSRAMSize() {
#ifdef CSE_STM32_HAL
    return *(reinterpret_cast<uint16_t*>(0x1FFF7A22)) * 1024;
#else
    return m_SRAMSize;
#endif
}

}