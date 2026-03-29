#ifndef CSE_HAL_STANDARD_GPIO_H
#define CSE_HAL_STANDARD_GPIO_H

#include <cstdint>
#include <functional>
#include <string>

namespace cse {

enum class GPIOMode : uint32_t {
    INPUT = 0,
    INPUT_PULL_DOWN = 1,
    INPUT_PULL_UP = 2,
    OUTPUT = 3,
    OUTPUT_OD = 3,
};

using GPIOInterruptCallback = std::function<void(uint32_t pin)>;

class IStandardGPIO {
public:
    virtual ~IStandardGPIO() = default;

    virtual bool setMode(uint32_t pin, GPIOMode mode) = 0;
    virtual bool write(uint32_t pin, bool value) = 0;
    virtual bool read(uint32_t pin) = 0;

    virtual uint32_t readPort() = 0;
    virtual void writePort(uint32_t value) = 0;
    virtual void setPortMask(uint32_t mask) = 0;
    virtual void clearPortMask(uint32_t mask) = 0;

    virtual bool enableInterrupt(uint32_t pin, GPIOMode mode,
                               GPIOInterruptCallback callback) = 0;
    virtual bool disableInterrupt(uint32_t pin) = 0;
    virtual void pollInterrupts() = 0;

    virtual const char* getPlatformName() const = 0;
};

}

#endif
