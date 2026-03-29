#include "platform/k210/K210Hardware.h"
#include "platform/k210/K210HAL.h"
#include <cstring>

namespace cse {

K210Hardware::K210Hardware() {
    k210_uart_init(115200);
}

void K210Hardware::delay(uint32_t ms) {
    k210_delay_ms(ms);
}

uint64_t K210Hardware::getTicks() {
    return k210_get_ticks();
}

void K210Hardware::reset() {
}

void K210Hardware::jumpTo(uint32_t address) {
    k210_jump_to(address);
}

bool K210Hardware::readFlash(uint32_t addr, uint8_t* buffer, size_t len) {
    if (addr + len > FLASH_SIZE) {
        return false;
    }
    std::memcpy(buffer, reinterpret_cast<const void*>(addr), len);
    return true;
}

bool K210Hardware::writeFlash(uint32_t addr, const uint8_t* data, size_t len) {
    (void)addr;
    (void)data;
    (void)len;
    return false;
}

bool K210Hardware::eraseFlash(uint32_t addr, size_t len) {
    (void)addr;
    (void)len;
    return false;
}

int K210Hardware::uartWrite(const uint8_t* data, size_t len) {
    return k210_uart_write(reinterpret_cast<const char*>(data), len);
}

int K210Hardware::uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) {
    return k210_uart_read(reinterpret_cast<char*>(data), len, timeout_ms);
}

int K210Hardware::uartAvailable() {
    return 0;
}

}