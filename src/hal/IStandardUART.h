#ifndef CSE_HAL_STANDARD_UART_H
#define CSE_HAL_STANDARD_UART_H

#include <cstdint>
#include <functional>
#include <string>

namespace cse {

enum class UARTParity {
    NONE,
    EVEN,
    ODD,
};

enum class UARTStopBits {
    ONE,
    TWO,
};

struct UARTConfig {
    uint32_t baudrate = 115200;
    uint8_t data_bits = 8;
    UARTParity parity = UARTParity::NONE;
    UARTStopBits stop_bits = UARTStopBits::ONE;
    bool rs485_mode = false;
    uint32_t rs485_de_pin = 0;
    bool rs485_de_active_high = true;
};

constexpr size_t UART_BUFFER_SIZE = 256;

class IStandardUART {
public:
    virtual ~IStandardUART() = default;

    virtual bool configure(const UARTConfig& config) = 0;
    virtual bool setBaudrate(uint32_t baud) = 0;

    virtual int write(const uint8_t* data, size_t len) = 0;
    virtual int read(uint8_t* buffer, size_t len, uint32_t timeout_ms = 1000) = 0;

    virtual bool enableDMA() = 0;
    virtual bool disableDMA() = 0;
    virtual size_t available() = 0;
    virtual size_t readNonBlocking(uint8_t* buffer, size_t max_len) = 0;

    virtual void setRS485Mode(bool enable, uint32_t de_pin = 0,
                             bool de_active_high = true) = 0;

    using DataCallback = std::function<void(const uint8_t*, size_t)>;
    virtual void setReceiveCallback(DataCallback callback) = 0;

    virtual uint32_t getFrameTimeout() = 0;
    virtual void setFrameTimeout(uint32_t char_us) = 0;

    virtual const char* getPlatformName() const = 0;
};

}

#endif
