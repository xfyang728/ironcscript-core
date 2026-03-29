#ifndef CSE_STM32_UART_H
#define CSE_STM32_UART_H

#include "hal/IStandardUART.h"
#include <cstdint>
#include <array>

constexpr size_t STM32_UART_BUFFER_SIZE = 256;

namespace cse {

class STM32UART : public IStandardUART {
public:
    explicit STM32UART(uint32_t uart_id = 0);
    ~STM32UART() override;

    bool configure(const UARTConfig& config) override;
    bool setBaudrate(uint32_t baud) override;
    int write(const uint8_t* data, size_t len) override;
    int read(uint8_t* buffer, size_t len,
            uint32_t timeout_ms = 1000) override;

    bool enableDMA() override;
    bool disableDMA() override;
    size_t available() override;
    size_t readNonBlocking(uint8_t* buffer, size_t max_len) override;

    void setRS485Mode(bool enable, uint32_t de_pin = 0,
                      bool de_active_high = true) override;
    void setReceiveCallback(DataCallback callback) override;

    uint32_t getFrameTimeout() override;
    void setFrameTimeout(uint32_t char_us) override;
    const char* getPlatformName() const override { return "STM32"; }

    void setGPIO(STM32GPIO* gpio);

private:
    uint32_t m_UARTID;
    UARTConfig m_Config;
    STM32GPIO* m_GPIO;
    bool m_RS485Mode;
    uint32_t m_RS485DEPin;
    bool m_RS485DEActiveHigh;
    DataCallback m_DataCallback;
    std::array<uint8_t, STM32_UART_BUFFER_SIZE> m_RxBuffer;
    size_t m_RxHead;
    size_t m_RxTail;
};

}

#endif