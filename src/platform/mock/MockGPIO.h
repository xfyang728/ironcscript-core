#ifndef CSE_MOCK_GPIO_H
#define CSE_MOCK_GPIO_H

#include "hal/IStandardGPIO.h"
#include <unordered_map>
#include <mutex>

namespace cse {

class MockGPIO : public IStandardGPIO {
public:
    MockGPIO();
    ~MockGPIO() override;

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

    const char* getPlatformName() const override { return "Mock"; }

private:
    std::mutex m_Mutex;
    std::unordered_map<uint32_t, bool> m_PinValues;
    std::unordered_map<uint32_t, GPIOMode> m_PinModes;
    uint32_t m_PortValue;
    uint32_t m_PortMask;
    uint32_t m_InterruptMask;
    GPIOInterruptCallback m_Callbacks[32];
};

}

#endif