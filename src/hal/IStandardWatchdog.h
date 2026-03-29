#ifndef CSE_HAL_ISTANDARD_WATCHDOG_H
#define CSE_HAL_ISTANDARD_WATCHDOG_H

#include <cstdint>

namespace cse {

class IStandardWatchdog {
public:
    virtual ~IStandardWatchdog() = default;

    virtual bool initialize(uint32_t timeout_ms) = 0;
    virtual void feed() = 0;
    virtual bool isTriggered() = 0;
    virtual uint32_t getRemainingTime() = 0;
    virtual const char* getPlatformName() const = 0;
};

}

#endif
