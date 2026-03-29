#ifndef CSE_STM32_TIMER_H
#define CSE_STM32_TIMER_H

#include "hal/IStandardTimer.h"
#include <cstdint>

constexpr uint32_t STM32_TIMER_COUNT = 14;

namespace cse {

class STM32Timer : public IStandardTimer {
public:
    explicit STM32Timer(uint32_t timer_id = 0);
    ~STM32Timer() override;

    bool start(uint32_t period_us, bool periodic = true) override;
    void stop() override;
    bool isRunning() override;
    uint64_t getTicks() override;

    bool configurePWM(uint32_t frequency_hz, uint8_t duty_cycle) override;
    bool setDutyCycle(uint8_t duty_cycle) override;
    bool setFrequency(uint32_t frequency_hz) override;

    bool enableCapture(bool rising, bool falling) override;
    uint32_t getCaptureValue() override;

    void setCallback(TimerCallback callback) override;
    const char* getPlatformName() const override { return "STM32"; }

private:
    uint32_t m_TimerID;
    bool m_Running;
    TimerMode m_Mode;
    uint32_t m_Period;
    uint32_t m_Frequency;
    TimerCallback m_Callback;
};

}

#endif