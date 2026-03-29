#ifndef CSE_STM32_DFU_BOOTLOADER_H
#define CSE_STM32_DFU_BOOTLOADER_H

#include "hal/IBootloader.h"
#include "platform/stm32/STM32Hardware.h"
#include <string>
#include <vector>

namespace cse {

class STM32DFUBootloader : public IBootloader {
public:
    explicit STM32DFUBootloader(STM32Hardware* hal);
    ~STM32DFUBootloader();

    void initialize() override;
    void process() override;

    bool flash(uint32_t address, const uint8_t* data, size_t len,
               ProgressCallback callback) override;
    bool verify(uint32_t address, const uint8_t* data, size_t len) override;
    bool boot(uint32_t entryPoint) override;

    BootloaderStatus getLastStatus() const override { return m_LastStatus; }
    const char* getLastError() const override { return m_ErrorMsg.c_str(); }

    void setFlashBase(uint32_t base) { m_FlashBase = base; }

private:
    enum class BootState {
        IDLE,
        RECEIVING,
        FLASHING,
        VERIFYING,
        COMPLETE,
        ERROR,
    };

    bool enterDFUMode();
    bool erase(uint32_t addr, size_t len);
    bool writePage(uint32_t addr, const uint8_t* data, size_t len);
    bool readProtect();
    bool jumpToApp(uint32_t addr);

    static constexpr uint32_t DEFAULT_CSB_ADDR = 0x08020000;

    STM32Hardware* m_HAL;
    BootloaderStatus m_LastStatus;
    std::string m_ErrorMsg;
    BootState m_State;
    uint32_t m_FlashBase;
};

}

#endif