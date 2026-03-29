#ifndef CSE_STM32_HARDWARE_H
#define CSE_STM32_HARDWARE_H

#include "hal/IHardwareAbstraction.h"

namespace cse {

class STM32Hardware : public IHardwareAbstraction {
public:
    STM32Hardware();
    ~STM32Hardware();

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

    uint32_t getFlashSize() override;
    uint32_t getSRAMSize() override;
    const char* getPlatformName() override { return "STM32"; }

private:
    enum class Model {
        UNKNOWN,
        F1,
        F4,
        H7,
        L4,
    };

    Model detectModel();
    bool initUART();

    Model m_Model;
    uint32_t m_FlashBase;
    uint32_t m_SRAMBase;
    uint32_t m_FlashSize;
    uint32_t m_SRAMSize;
};

}

#endif