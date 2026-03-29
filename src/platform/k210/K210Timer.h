#ifndef CSE_K210_TIMER_H
#define CSE_K210_TIMER_H

#include "hal/IStandardTimer.h"
#include <cstdint>

constexpr uint32_t K210_TIMER_COUNT = 4;

namespace cse {

class K210Timer : public IStandardTimer {
public:
    explicit K210Timer(uint32_t timer_id);
    ~K210Timer() override;

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

    const char* getPlatformName() const override { return "K210"; }

private:
    volatile uint32_t* getTimerReg(uint32_t offset);

    uint32_t m_TimerID;
    bool m_Running;
    TimerMode m_Mode;
    uint32_t m_Period;
    uint32_t m_Frequency;
    TimerCallback m_Callback;
    uint64_t m_OverflowCount;
    uint32_t m_LastValue;
    bool m_FirstRead;
};

}

#endif
