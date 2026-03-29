#ifndef CSE_HAL_STANDARD_TIMER_H
#define CSE_HAL_STANDARD_TIMER_H

#include <cstdint>
#include <functional>

namespace cse {

enum class TimerMode {
    ONESHOT,
    PERIODIC,
    PWM,
    CAPTURE,
};

class IStandardTimer {
public:
    virtual ~IStandardTimer() = default;

    virtual bool start(uint32_t period_us, bool periodic = true) = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
    virtual uint64_t getTicks() = 0;

    virtual bool configurePWM(uint32_t frequency_hz, uint8_t duty_cycle) = 0;
    virtual bool setDutyCycle(uint8_t duty_cycle) = 0;
    virtual bool setFrequency(uint32_t frequency_hz) = 0;

    virtual bool enableCapture(bool rising, bool falling) = 0;
    virtual uint32_t getCaptureValue() = 0;

    using TimerCallback = std::function<void()>;
    virtual void setCallback(TimerCallback callback) = 0;

    virtual const char* getPlatformName() const = 0;
};

}

#endif
