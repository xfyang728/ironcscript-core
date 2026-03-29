#include "platform/mock/MockTimer.h"
#include <iostream>

namespace cse {

MockTimer::MockTimer(uint32_t timer_id)
    : m_TimerID(timer_id), m_Running(false), m_PeriodUs(0),
      m_Periodic(true), m_Ticks(0) {
}

MockTimer::~MockTimer() {
    stop();
}

bool MockTimer::start(uint32_t period_us, bool periodic) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PeriodUs = period_us;
    m_Periodic = periodic;
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_Running = true;
    return true;
}

void MockTimer::stop() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Running = false;
}

bool MockTimer::isRunning() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    return m_Running;
}

uint64_t MockTimer::getTicks() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (!m_Running) return m_Ticks;

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
        now - m_StartTime).count();

    if (m_Periodic && m_PeriodUs > 0) {
        m_Ticks = elapsed / m_PeriodUs;
    } else {
        m_Ticks = elapsed;
    }
    return m_Ticks;
}

bool MockTimer::configurePWM(uint32_t frequency_hz, uint8_t duty_cycle) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PeriodUs = 1000000 / frequency_hz;
    m_Periodic = true;
    return true;
}

bool MockTimer::setDutyCycle(uint8_t duty_cycle) {
    return true;
}

bool MockTimer::setFrequency(uint32_t frequency_hz) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PeriodUs = 1000000 / frequency_hz;
    return true;
}

bool MockTimer::enableCapture(bool rising, bool falling) {
    return true;
}

uint32_t MockTimer::getCaptureValue() {
    return 0;
}

void MockTimer::setCallback(TimerCallback callback) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Callback = callback;
}

}