#include "STM32UART.h"
#include "STM32GPIO.h"
#include <cstring>

#ifdef STM32_HAL_UART_H
#include "stm32f4xx_hal.h"
#endif

namespace cse {

STM32UART::STM32UART(uint32_t uart_id)
    : m_UARTID(uart_id), m_GPIO(nullptr),
      m_RS485Mode(false), m_RS485DEPin(0), m_RS485DEActiveHigh(true),
      m_DataCallback(nullptr), m_RxHead(0), m_RxTail(0) {
    m_Config.baudrate = 115200;
    m_Config.data_bits = 8;
    m_Config.parity = UARTParity::NONE;
    m_Config.stop_bits = UARTStopBits::ONE;
    m_RxBuffer.fill(0);
}

STM32UART::~STM32UART() {
}

bool STM32UART::configure(const UARTConfig& config) {
    m_Config = config;

#ifdef STM32_HAL_UART_H
    UART_HandleTypeDef huart = {};
    huart.Instance = reinterpret_cast<USART_TypeDef*>(0x40011000 + m_UARTID * 0x400);
    huart.Init.BaudRate = config.baudrate;
    huart.Init.WordLength = (config.data_bits == 9) ? UART_WORDLENGTH_9B : UART_WORDLENGTH_8B;
    huart.Init.StopBits = (config.stop_bits == UARTStopBits::TWO) ? UART_STOPBITS_2 : UART_STOPBITS_1;
    huart.Init.Parity = (config.parity == UARTParity::EVEN) ? UART_PARITY_EVEN :
                        (config.parity == UARTParity::ODD) ? UART_PARITY_ODD : UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart);
#endif

    return true;
}

bool STM32UART::setBaudrate(uint32_t baud) {
    m_Config.baudrate = baud;
    return configure(m_Config);
}

int STM32UART::write(const uint8_t* data, size_t len) {
    if (m_RS485Mode && m_GPIO) {
        m_GPIO->write(m_RS485DEPin, m_RS485DEActiveHigh);
    }

#ifdef STM32_HAL_UART_H
    UART_HandleTypeDef huart = {};
    huart.Instance = reinterpret_cast<USART_TypeDef*>(0x40011000 + m_UARTID * 0x400);
    HAL_UART_Transmit(&huart, const_cast<uint8_t*>(data), len, 1000);
#else
    (void)data;
    (void)len;
#endif

    if (m_RS485Mode && m_GPIO) {
        m_GPIO->write(m_RS485DEPin, !m_RS485DEActiveHigh);
    }

    return static_cast<int>(len);
}

int STM32UART::read(uint8_t* buffer, size_t len, uint32_t timeout_ms) {
#ifdef STM32_HAL_UART_H
    UART_HandleTypeDef huart = {};
    huart.Instance = reinterpret_cast<USART_TypeDef*>(0x40011000 + m_UARTID * 0x400);
    HAL_UART_Receive(&huart, buffer, len, timeout_ms);
#else
    (void)buffer;
    (void)len;
    (void)timeout_ms;
#endif
    return 0;
}

bool STM32UART::enableDMA() {
#ifdef STM32_HAL_UART_H
    UART_HandleTypeDef huart = {};
    huart.Instance = reinterpret_cast<USART_TypeDef*>(0x40011000 + m_UARTID * 0x400);
    HAL_UART_Receive_DMA(&huart, m_RxBuffer.data(), STM32_UART_BUFFER_SIZE);
#endif
    return true;
}

bool STM32UART::disableDMA() {
    return true;
}

size_t STM32UART::available() {
    if (m_RxHead >= m_RxTail) {
        return m_RxHead - m_RxTail;
    } else {
        return STM32_UART_BUFFER_SIZE - m_RxTail + m_RxHead;
    }
}

size_t STM32UART::readNonBlocking(uint8_t* buffer, size_t max_len) {
    size_t count = 0;
    while (available() > 0 && count < max_len) {
        buffer[count++] = m_RxBuffer[m_RxTail];
        m_RxTail = (m_RxTail + 1) % STM32_UART_BUFFER_SIZE;
    }
    return count;
}

void STM32UART::setRS485Mode(bool enable, uint32_t de_pin, bool de_active_high) {
    m_RS485Mode = enable;
    m_RS485DEPin = de_pin;
    m_RS485DEActiveHigh = de_active_high;
}

void STM32UART::setReceiveCallback(DataCallback callback) {
    m_DataCallback = callback;
}

uint32_t STM32UART::getFrameTimeout() {
    uint32_t bits_per_char = m_Config.data_bits +
                             (m_Config.parity != UARTParity::NONE ? 1 : 0) +
                             static_cast<uint32_t>(m_Config.stop_bits) + 1;
    return bits_per_char * 3.5 * 1000000 / m_Config.baudrate;
}

void STM32UART::setFrameTimeout(uint32_t char_us) {
    (void)char_us;
}

void STM32UART::setGPIO(STM32GPIO* gpio) {
    m_GPIO = gpio;
}

}