#include "K210UART.h"
#include "K210HAL.h"
#include "K210GPIO.h"
#include <cstring>

extern "C" {
#include "uart.h"
#include "fpioa.h"
#include "sysctl.h"
}

namespace cse {

K210UART::K210UART(uint32_t uart_id)
    : m_UARTID(uart_id),
      m_FrameTimeout(0),
      m_RS485Mode(false),
      m_RS485DEPin(0),
      m_RS485DEActiveHigh(true),
      m_RxHead(0),
      m_RxTail(0),
      m_Callback(nullptr),
      m_GPIO(nullptr) {
    m_Config.baudrate = 115200;
    m_Config.data_bits = 8;
    m_Config.parity = UARTParity::NONE;
    m_Config.stop_bits = UARTStopBits::ONE;
    memset(m_RxBuffer.data(), 0, UART_BUFFER_SIZE);
}

K210UART::~K210UART() {
}

bool K210UART::configure(const UARTConfig& config) {
    m_Config = config;

    uart_init(uart_device_number_t(m_UARTID));

    uart_stopbit_t stop_bit = (config.stop_bits == UARTStopBits::TWO) ? UART_STOP_2 : UART_STOP_1;
    uart_parity_t parity = (config.parity == UARTParity::EVEN) ? UART_PARITY_EVEN :
                           (config.parity == UARTParity::ODD) ? UART_PARITY_ODD : UART_PARITY_NONE;

    uart_bitwidth_t data_width;
    switch (config.data_bits) {
        case 5: data_width = UART_BITWIDTH_5BIT; break;
        case 6: data_width = UART_BITWIDTH_6BIT; break;
        case 7: data_width = UART_BITWIDTH_7BIT; break;
        default: data_width = UART_BITWIDTH_8BIT; break;
    }

    uart_configure(uart_device_number_t(m_UARTID),
                   config.baudrate,
                   data_width,
                   stop_bit,
                   parity);

    return true;
}

bool K210UART::setBaudrate(uint32_t baud) {
    m_Config.baudrate = baud;
    return configure(m_Config);
}

int K210UART::write(const uint8_t* data, size_t len) {
    if (m_RS485Mode && m_GPIO) {
        m_GPIO->write(m_RS485DEPin, m_RS485DEActiveHigh);
    }

    int written = uart_send_data(uart_device_number_t(m_UARTID), reinterpret_cast<const char*>(data), len);

    if (m_RS485Mode && m_GPIO) {
        m_GPIO->write(m_RS485DEPin, !m_RS485DEActiveHigh);
    }

    return written;
}

int K210UART::read(uint8_t* buffer, size_t len, uint32_t timeout_ms) {
    size_t read_count = 0;
    uint64_t start_time = k210_get_ticks();

    while (read_count < len) {
        if (available() > 0) {
            char c;
            int received = uart_receive_data(uart_device_number_t(m_UARTID), &c, 1);
            if (received > 0) {
                buffer[read_count++] = static_cast<uint8_t>(c);
            }
        }
        if (k210_get_ticks() - start_time > timeout_ms * 1000) {
            break;
        }
    }

    return static_cast<int>(read_count);
}

bool K210UART::enableDMA() {
    return true;
}

bool K210UART::disableDMA() {
    return true;
}

size_t K210UART::available() {
    return uart_receive_data(uart_device_number_t(m_UARTID), nullptr, 0);
}

size_t K210UART::readNonBlocking(uint8_t* buffer, size_t max_len) {
    int received = uart_receive_data(uart_device_number_t(m_UARTID), reinterpret_cast<char*>(buffer), max_len);
    return received > 0 ? received : 0;
}

void K210UART::setRS485Mode(bool enable, uint32_t de_pin,
                           bool de_active_high) {
    m_RS485Mode = enable;
    m_RS485DEPin = de_pin;
    m_RS485DEActiveHigh = de_active_high;
}

void K210UART::setReceiveCallback(DataCallback callback) {
    m_Callback = callback;
}

void K210UART::setGPIO(K210GPIO* gpio) {
    m_GPIO = gpio;
}

uint32_t K210UART::getFrameTimeout() {
    return m_FrameTimeout;
}

void K210UART::setFrameTimeout(uint32_t char_us) {
    m_FrameTimeout = char_us;
}

}