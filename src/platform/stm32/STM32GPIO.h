#ifndef CSE_STM32_GPIO_H
#define CSE_STM32_GPIO_H

#include "hal/IStandardGPIO.h"
#include <cstdint>

constexpr uint32_t STM32_GPIO_PIN_COUNT = 16;

namespace cse {

class STM32GPIO : public IStandardGPIO {
public:
    explicit STM32GPIO(uint32_t portBase = 0x40020000);
    ~STM32GPIO() override;

    bool setMode(uint32_t pin, GPIOMode mode) override;
    bool write(uint32_t pin, bool value) override;
    bool read(uint32_t pin) override;

    uint32_t readPort() override;
    void writePort(uint32_t value) override;
    void setPortMask(uint32_t mask) override;
    void clearPortMask(uint32_t mask) override;

    bool enableInterrupt(uint32_t pin, GPIOMode mode,
                        GPIOInterruptCallback callback) override;
    bool disableInterrupt(uint32_t pin) override;
    void pollInterrupts() override;

    const char* getPlatformName() const override { return "STM32"; }

private:
    uint32_t m_PortBase;
    uint32_t m_PortValue;
    uint32_t m_PortMask;
    uint32_t m_InterruptMask;
    GPIOInterruptCallback m_Callbacks[STM32_GPIO_PIN_COUNT];
    GPIOMode m_Modes[STM32_GPIO_PIN_COUNT];
};

}

#endif