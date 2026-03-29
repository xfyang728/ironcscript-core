#ifndef CSE_MOCK_TIMER_H
#define CSE_MOCK_TIMER_H

#include "hal/IStandardTimer.h"
#include <chrono>
#include <mutex>
#include <cstdint>

namespace cse {

class MockTimer : public IStandardTimer {
public:
    explicit MockTimer(uint32_t timer_id = 0);
    ~MockTimer() override;

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

    const char* getPlatformName() const override { return "Mock"; }

private:
    uint32_t m_TimerID;
    bool m_Running;
    uint32_t m_PeriodUs;
    bool m_Periodic;
    uint64_t m_Ticks;
    std::chrono::high_resolution_clock::time_point m_StartTime;
    TimerCallback m_Callback;
    std::mutex m_Mutex;
};

}

#endif