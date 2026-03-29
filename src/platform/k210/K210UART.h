#ifndef CSE_K210_UART_H
#define CSE_K210_UART_H

#include "hal/IStandardUART.h"
#include <array>
#include <cstdint>

constexpr uint32_t K210_UART_COUNT = 3;

namespace cse {

class K210GPIO;

class K210UART : public IStandardUART {
public:
    explicit K210UART(uint32_t uart_id);
    ~K210UART() override;

    bool configure(const UARTConfig& config) override;
    bool setBaudrate(uint32_t baud) override;

    int write(const uint8_t* data, size_t len) override;
    int read(uint8_t* buffer, size_t len, uint32_t timeout_ms = 1000) override;

    bool enableDMA() override;
    bool disableDMA() override;
    size_t available() override;
    size_t readNonBlocking(uint8_t* buffer, size_t max_len) override;

    void setRS485Mode(bool enable, uint32_t de_pin = 0,
                     bool de_active_high = true) override;

    void setReceiveCallback(DataCallback callback) override;

    uint32_t getFrameTimeout() override;
    void setFrameTimeout(uint32_t char_us) override;

    const char* getPlatformName() const override { return "K210"; }

    void setGPIO(K210GPIO* gpio);

private:
    volatile uint32_t* getUARTReg(uint32_t offset);
    uint32_t calculateDivisor(uint32_t baud);
    void configFPIOA();

    uint32_t m_UARTID;
    UARTConfig m_Config;
    uint32_t m_FrameTimeout;
    bool m_RS485Mode;
    uint32_t m_RS485DEPin;
    bool m_RS485DEActiveHigh;

    std::array<uint8_t, UART_BUFFER_SIZE> m_RxBuffer;
    size_t m_RxHead;
    size_t m_RxTail;

    DataCallback m_Callback;
    K210GPIO* m_GPIO;
};

}

#endif
