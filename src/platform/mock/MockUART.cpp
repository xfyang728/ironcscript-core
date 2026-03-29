#include "platform/mock/MockUART.h"
#include <iostream>
#include <cstring>

namespace cse {

MockUART::MockUART(uint32_t uart_id)
    : m_UARTID(uart_id), m_FrameTimeout(0) {
    m_Config.baudrate = 115200;
    m_Config.data_bits = 8;
    m_Config.parity = UARTParity::NONE;
    m_Config.stop_bits = UARTStopBits::ONE;
}

MockUART::~MockUART() = default;

bool MockUART::configure(const UARTConfig& config) {
    std::lock_guard<std::mutex> lock(m_TxMutex);
    m_Config = config;
    return true;
}

bool MockUART::setBaudrate(uint32_t baud) {
    std::lock_guard<std::mutex> lock(m_TxMutex);
    m_Config.baudrate = baud;
    return true;
}

int MockUART::write(const uint8_t* data, size_t len) {
    if (!data || len == 0) return -1;

    std::lock_guard<std::mutex> lock(m_TxMutex);
    for (size_t i = 0; i < len; i++) {
        m_TxQueue.push(data[i]);
    }
    return static_cast<int>(len);
}

int MockUART::read(uint8_t* buffer, size_t len, uint32_t timeout_ms) {
    if (!buffer || len == 0) return -1;

    std::lock_guard<std::mutex> lock(m_RxMutex);
    size_t read_count = 0;
    while (read_count < len && !m_RxQueue.empty()) {
        buffer[read_count++] = m_RxQueue.front();
        m_RxQueue.pop();
    }
    return static_cast<int>(read_count);
}

bool MockUART::enableDMA() {
    return true;
}

bool MockUART::disableDMA() {
    return true;
}

size_t MockUART::available() {
    std::lock_guard<std::mutex> lock(m_RxMutex);
    return m_RxQueue.size();
}

size_t MockUART::readNonBlocking(uint8_t* buffer, size_t max_len) {
    if (!buffer || max_len == 0) return 0;

    std::lock_guard<std::mutex> lock(m_RxMutex);
    size_t read_count = 0;
    while (read_count < max_len && !m_RxQueue.empty()) {
        buffer[read_count++] = m_RxQueue.front();
        m_RxQueue.pop();
    }
    return read_count;
}

void MockUART::setRS485Mode(bool enable, uint32_t de_pin,
                           bool de_active_high) {
    m_Config.rs485_mode = enable;
    m_Config.rs485_de_pin = de_pin;
    m_Config.rs485_de_active_high = de_active_high;
}

void MockUART::setReceiveCallback(IStandardUART::DataCallback callback) {
    m_Callback = callback;
}

uint32_t MockUART::getFrameTimeout() {
    return m_FrameTimeout;
}

void MockUART::setFrameTimeout(uint32_t char_us) {
    m_FrameTimeout = char_us;
}

void MockUART::simualteIncomingData(const uint8_t* data, size_t len) {
    if (!data || len == 0) return;

    std::lock_guard<std::mutex> lock(m_RxMutex);
    for (size_t i = 0; i < len; i++) {
        m_RxQueue.push(data[i]);
    }

    if (m_Callback) {
        m_Callback(data, len);
    }
}

}