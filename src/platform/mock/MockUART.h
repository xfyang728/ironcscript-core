#ifndef CSE_MOCK_UART_H
#define CSE_MOCK_UART_H

#include "hal/IStandardUART.h"
#include <queue>
#include <mutex>
#include <cstdint>

namespace cse {

class MockUART : public IStandardUART {
public:
    explicit MockUART(uint32_t uart_id = 0);
    ~MockUART() override;

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

    void setReceiveCallback(IStandardUART::DataCallback callback) override;

    uint32_t getFrameTimeout() override;
    void setFrameTimeout(uint32_t char_us) override;

    const char* getPlatformName() const override { return "Mock"; }

    void simualteIncomingData(const uint8_t* data, size_t len);

private:
    uint32_t m_UARTID;
    UARTConfig m_Config;
    std::queue<uint8_t> m_TxQueue;
    std::queue<uint8_t> m_RxQueue;
    std::mutex m_TxMutex;
    std::mutex m_RxMutex;
    IStandardUART::DataCallback m_Callback;
    uint32_t m_FrameTimeout;
};

}

#endif