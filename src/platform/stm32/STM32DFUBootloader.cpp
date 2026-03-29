#include "platform/stm32/STM32DFUBootloader.h"
#include <cstring>

namespace cse {

STM32DFUBootloader::STM32DFUBootloader(STM32Hardware* hal)
    : m_HAL(hal)
    , m_LastStatus(BootloaderStatus::OK)
    , m_State(BootState::IDLE)
    , m_FlashBase(DEFAULT_CSB_ADDR)
{
}

STM32DFUBootloader::~STM32DFUBootloader() {
}

void STM32DFUBootloader::initialize() {
    m_LastStatus = BootloaderStatus::OK;
    m_ErrorMsg.clear();
    m_State = BootState::IDLE;
}

void STM32DFUBootloader::process() {
    switch (m_State) {
        case BootState::IDLE:
            break;
        case BootState::RECEIVING:
            break;
        case BootState::FLASHING:
            break;
        case BootState::VERIFYING:
            break;
        case BootState::COMPLETE:
            break;
        case BootState::ERROR:
            break;
    }
}

bool STM32DFUBootloader::flash(uint32_t address, const uint8_t* data, size_t len,
                               ProgressCallback callback) {
    if (!m_HAL) {
        m_ErrorMsg = "Hardware abstraction is null";
        m_LastStatus = BootloaderStatus::ERROR;
        return false;
    }

    m_State = BootState::FLASHING;

    if (!m_HAL->eraseFlash(address, len)) {
        m_ErrorMsg = "Flash erase failed";
        m_LastStatus = BootloaderStatus::FLASH_ERROR;
        m_State = BootState::ERROR;
        return false;
    }

    if (!m_HAL->writeFlash(address, data, len)) {
        m_ErrorMsg = "Flash write failed";
        m_LastStatus = BootloaderStatus::FLASH_ERROR;
        m_State = BootState::ERROR;
        return false;
    }

    m_State = BootState::VERIFYING;
    if (!verify(address, data, len)) {
        m_ErrorMsg = "Flash verify failed";
        m_LastStatus = BootloaderStatus::CRC_ERROR;
        m_State = BootState::ERROR;
        return false;
    }

    m_State = BootState::COMPLETE;
    m_LastStatus = BootloaderStatus::OK;
    return true;
}

bool STM32DFUBootloader::verify(uint32_t address, const uint8_t* data, size_t len) {
    if (!m_HAL) {
        return false;
    }

    std::vector<uint8_t> readBuffer(len);
    if (!m_HAL->readFlash(address, readBuffer.data(), len)) {
        return false;
    }

    return std::memcmp(data, readBuffer.data(), len) == 0;
}

bool STM32DFUBootloader::boot(uint32_t entryPoint) {
    if (!m_HAL) {
        return false;
    }

    m_HAL->delay(100);
    m_HAL->jumpTo(entryPoint);
    return true;
}

bool STM32DFUBootloader::enterDFUMode() {
    return true;
}

bool STM32DFUBootloader::erase(uint32_t addr, size_t len) {
    if (!m_HAL) {
        return false;
    }
    return m_HAL->eraseFlash(addr, len);
}

bool STM32DFUBootloader::writePage(uint32_t addr, const uint8_t* data, size_t len) {
    if (!m_HAL) {
        return false;
    }
    return m_HAL->writeFlash(addr, data, len);
}

bool STM32DFUBootloader::readProtect() {
    return true;
}

bool STM32DFUBootloader::jumpToApp(uint32_t addr) {
    if (!m_HAL) {
        return false;
    }
    m_HAL->jumpTo(addr);
    return true;
}

}