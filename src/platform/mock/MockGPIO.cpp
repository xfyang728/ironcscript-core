#include "platform/mock/MockGPIO.h"
#include <iostream>

namespace cse {

MockGPIO::MockGPIO()
    : m_PortValue(0), m_PortMask(0xFFFFFFFF), m_InterruptMask(0) {
    for (int i = 0; i < 32; i++) {
        m_Callbacks[i] = nullptr;
    }
}

MockGPIO::~MockGPIO() = default;

bool MockGPIO::setMode(uint32_t pin, GPIOMode mode) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (pin >= 32) return false;
    m_PinModes[pin] = mode;
    return true;
}

bool MockGPIO::write(uint32_t pin, bool value) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (pin >= 32) return false;
    m_PinValues[pin] = value;
    if (m_PortMask & (1 << pin)) {
        if (value) {
            m_PortValue |= (1 << pin);
        } else {
            m_PortValue &= ~(1 << pin);
        }
    }
    return true;
}

bool MockGPIO::read(uint32_t pin) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (pin >= 32) return false;
    return m_PinValues.count(pin) ? m_PinValues[pin] : false;
}

uint32_t MockGPIO::readPort() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    return m_PortValue & m_PortMask;
}

void MockGPIO::writePort(uint32_t value) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PortValue = (value & m_PortMask) | (m_PortValue & ~m_PortMask);
    for (uint32_t pin = 0; pin < 32; pin++) {
        if (m_PortMask & (1 << pin)) {
            m_PinValues[pin] = (m_PortValue >> pin) & 1;
        }
    }
}

void MockGPIO::setPortMask(uint32_t mask) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PortMask = mask;
}

void MockGPIO::clearPortMask(uint32_t mask) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_PortMask &= ~mask;
}

bool MockGPIO::enableInterrupt(uint32_t pin, GPIOMode mode,
                              GPIOInterruptCallback callback) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (pin >= 32) return false;
    m_Callbacks[pin] = callback;
    m_InterruptMask |= (1 << pin);
    return true;
}

bool MockGPIO::disableInterrupt(uint32_t pin) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (pin >= 32) return false;
    m_Callbacks[pin] = nullptr;
    m_InterruptMask &= ~(1 << pin);
    return true;
}

void MockGPIO::pollInterrupts() {
}

}