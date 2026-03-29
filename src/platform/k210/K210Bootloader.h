#ifndef CSE_K210_BOOTLOADER_H
#define CSE_K210_BOOTLOADER_H

#include "hal/IBootloader.h"
#include "platform/k210/K210Hardware.h"
#include <string>

namespace cse {

class K210Bootloader : public IBootloader {
public:
    explicit K210Bootloader(K210Hardware* hal);

    void initialize() override;
    void process() override;

    bool flash(uint32_t address, const uint8_t* data, size_t len,
               ProgressCallback callback) override;
    bool verify(uint32_t address, const uint8_t* data, size_t len) override;
    bool boot(uint32_t entryPoint) override;

    BootloaderStatus getLastStatus() const override { return m_LastStatus; }
    const char* getLastError() const override { return m_ErrorMsg.c_str(); }

private:
    bool sendPacket(const uint8_t* data, size_t len);
    bool receivePacket(uint8_t* buffer, size_t* outLen, uint32_t timeout_ms);
    uint8_t calcCRC8(const uint8_t* data, size_t len);

    K210Hardware* m_HAL;
    BootloaderStatus m_LastStatus;
    std::string m_ErrorMsg;

    static constexpr uint32_t SYNC_MAGIC = 0xFFAA55AA;
    static constexpr uint32_t CSB_STORE_ADDR = 0x00080000;
    static constexpr size_t MAX_PKT_SIZE = 256;
};

}

extern "C" {
void kbp_init(void);
void kbp_process(void);
}

#endif