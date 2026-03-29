#include "K210Timer.h"
#include "K210HAL.h"
#include <cstdio>

extern "C" {
#include "timer.h"
#include "sysctl.h"
}

namespace cse {

K210Timer::K210Timer(uint32_t timer_id)
    : m_TimerID(timer_id), m_Running(false),
      m_Mode(TimerMode::PERIODIC), m_Period(0),
      m_Frequency(1000000), m_Callback(nullptr),
      m_OverflowCount(0), m_LastValue(0), m_FirstRead(true) {
}

K210Timer::~K210Timer() {
    stop();
}

bool K210Timer::start(uint32_t period_us, bool periodic) {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return false;
    }

    m_Period = period_us;
    m_Mode = periodic ? TimerMode::PERIODIC : TimerMode::ONESHOT;

    timer_device_number_t device = static_cast<timer_device_number_t>(m_TimerID);
    timer_init(device);

    size_t period_ns = period_us * 1000ULL;
    timer_set_interval(device, TIMER_CHANNEL_0, period_ns);

    timer_set_enable(device, TIMER_CHANNEL_0, 1);

    m_Running = true;
    return true;
}

void K210Timer::stop() {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return;
    }

    timer_device_number_t device = static_cast<timer_device_number_t>(m_TimerID);
    timer_set_enable(device, TIMER_CHANNEL_0, 0);
    m_Running = false;
    m_OverflowCount = 0;
    m_FirstRead = true;
}

bool K210Timer::isRunning() {
    return m_Running;
}

uint64_t K210Timer::getTicks() {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return 0;
    }

    volatile kendryte_timer_t* timer_reg = timer[m_TimerID];
    if (!timer_reg) return 0;

    uint32_t current_value = timer_reg->channel[0].current_value;
    uint32_t load_count = timer_reg->channel[0].load_count;

    if (m_FirstRead) {
        m_LastValue = current_value;
        m_FirstRead = false;
        return 0;
    }

    if (current_value > m_LastValue && m_LastValue < (load_count / 4)) {
        m_OverflowCount++;
    }

    m_LastValue = current_value;

    uint64_t ticks = m_OverflowCount * static_cast<uint64_t>(load_count) +
                     (load_count - current_value);

    return ticks;
}

bool K210Timer::configurePWM(uint32_t frequency_hz, uint8_t duty_cycle) {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return false;
    }

    m_Frequency = frequency_hz;
    m_Mode = TimerMode::PWM;

    return true;
}

bool K210Timer::setDutyCycle(uint8_t duty_cycle) {
    if (!m_Running || m_Mode != TimerMode::PWM) {
        return false;
    }

    if (m_TimerID >= K210_TIMER_COUNT) {
        return false;
    }

    return true;
}

bool K210Timer::setFrequency(uint32_t frequency_hz) {
    if (m_Mode != TimerMode::PWM) {
        return false;
    }

    uint8_t current_duty = 50;
    return configurePWM(frequency_hz, current_duty);
}

bool K210Timer::enableCapture(bool rising, bool falling) {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return false;
    }

    m_Mode = TimerMode::CAPTURE;
    m_Running = true;

    return true;
}

uint32_t K210Timer::getCaptureValue() {
    if (m_TimerID >= K210_TIMER_COUNT) {
        return 0;
    }

    volatile kendryte_timer_t* timer_reg = timer[m_TimerID];
    if (!timer_reg) return 0;

    return timer_reg->channel[0].current_value;
}

void K210Timer::setCallback(TimerCallback callback) {
    m_Callback = callback;
}

}