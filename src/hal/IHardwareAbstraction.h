#ifndef CSE_IHARDWARE_ABSTRACTION_H
#define CSE_IHARDWARE_ABSTRACTION_H

#include <cstdint>
#include <cstddef>
#include <functional>

namespace cse {

class IHardwareAbstraction {
public:
    virtual ~IHardwareAbstraction() = default;

    virtual void delay(uint32_t ms) = 0;
    virtual uint64_t getTicks() = 0;
    virtual void reset() = 0;
    virtual void jumpTo(uint32_t address) = 0;

    virtual bool readFlash(uint32_t addr, uint8_t* buffer, size_t len) = 0;
    virtual bool writeFlash(uint32_t addr, const uint8_t* data, size_t len) = 0;
    virtual bool eraseFlash(uint32_t addr, size_t len) = 0;

    virtual int uartWrite(const uint8_t* data, size_t len) = 0;
    virtual int uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) = 0;
    virtual int uartAvailable() = 0;

    virtual uint32_t getFlashSize() = 0;
    virtual uint32_t getSRAMSize() = 0;
    virtual const char* getPlatformName() = 0;
};

}

#endif
