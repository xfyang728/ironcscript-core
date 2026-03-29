#include "platform/k210/K210Bootloader.h"
#include <cstring>
#include <vector>

namespace cse {

K210Bootloader::K210Bootloader(K210Hardware* hal)
    : m_HAL(hal)
    , m_LastStatus(BootloaderStatus::OK)
{
}

void K210Bootloader::initialize() {
    m_LastStatus = BootloaderStatus::OK;
    m_ErrorMsg.clear();
}

void K210Bootloader::process() {
}

bool K210Bootloader::flash(uint32_t address, const uint8_t* data, size_t len,
                           ProgressCallback callback) {
    (void)address;
    (void)data;
    (void)len;
    (void)callback;

    if (!m_HAL->eraseFlash(address, len)) {
        m_ErrorMsg = "Flash erase failed";
        m_LastStatus = BootloaderStatus::FLASH_ERROR;
        return false;
    }

    if (!m_HAL->writeFlash(address, data, len)) {
        m_ErrorMsg = "Flash write failed";
        m_LastStatus = BootloaderStatus::FLASH_ERROR;
        return false;
    }

    if (!verify(address, data, len)) {
        m_ErrorMsg = "Flash verify failed";
        m_LastStatus = BootloaderStatus::CRC_ERROR;
        return false;
    }

    return true;
}

bool K210Bootloader::verify(uint32_t address, const uint8_t* data, size_t len) {
    std::vector<uint8_t> readBuffer(len);
    if (!m_HAL->readFlash(address, readBuffer.data(), len)) {
        return false;
    }
    return std::memcmp(data, readBuffer.data(), len) == 0;
}

bool K210Bootloader::boot(uint32_t entryPoint) {
    m_HAL->delay(100);
    m_HAL->jumpTo(entryPoint);
    return true;
}

bool K210Bootloader::sendPacket(const uint8_t* data, size_t len) {
    (void)data;
    (void)len;
    return false;
}

bool K210Bootloader::receivePacket(uint8_t* buffer, size_t* outLen, uint32_t timeout_ms) {
    (void)buffer;
    (void)outLen;
    (void)timeout_ms;
    return false;
}

uint8_t K210Bootloader::calcCRC8(const uint8_t* data, size_t len) {
    uint8_t crc = 0;
    for (size_t i = 0; i < len; ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

}

extern "C" {

static cse::K210Hardware* g_HAL = nullptr;
static cse::K210Bootloader* g_Bootloader = nullptr;

void kbp_init() {
    if (!g_HAL) {
        g_HAL = new cse::K210Hardware();
    }
    if (!g_Bootloader) {
        g_Bootloader = new cse::K210Bootloader(g_HAL);
    }
    g_Bootloader->initialize();
}

void kbp_process() {
    if (g_Bootloader) {
        g_Bootloader->process();
    }
}

}