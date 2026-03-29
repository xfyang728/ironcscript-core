#ifndef CSE_K210_HARDWARE_H
#define CSE_K210_HARDWARE_H

#include "hal/IHardwareAbstraction.h"

namespace cse {

class K210Hardware : public IHardwareAbstraction {
public:
    K210Hardware();

    void delay(uint32_t ms) override;
    uint64_t getTicks() override;
    void reset() override;
    void jumpTo(uint32_t address) override;

    bool readFlash(uint32_t addr, uint8_t* buffer, size_t len) override;
    bool writeFlash(uint32_t addr, const uint8_t* data, size_t len) override;
    bool eraseFlash(uint32_t addr, size_t len) override;

    int uartWrite(const uint8_t* data, size_t len) override;
    int uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) override;
    int uartAvailable() override;

    uint32_t getFlashSize() override { return 8 * 1024 * 1024; }
    uint32_t getSRAMSize() override { return 8 * 1024 * 1024; }
    const char* getPlatformName() override { return "K210"; }

private:
    static constexpr uint32_t UART0_BASE = 0x38000000;
    static constexpr uint32_t SPI3_BASE = 0x53100000;
    static constexpr uint32_t FLASH_BASE = 0x00000000;
    static constexpr uint32_t FLASH_SIZE = 8 * 1024 * 1024;

    void uartInit(uint32_t baud);
};

}

#endif