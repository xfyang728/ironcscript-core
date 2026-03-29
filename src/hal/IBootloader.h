#ifndef CSE_IBOOTLOADER_H
#define CSE_IBOOTLOADER_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <functional>

namespace cse {

enum class BootloaderStatus : uint8_t {
    OK,
    ERROR,
    TIMEOUT,
    INVALID_COMMAND,
    CRC_ERROR,
    FLASH_ERROR,
};

using ProgressCallback = std::function<void(size_t current, size_t total)>;

class IBootloader {
public:
    virtual ~IBootloader() = default;

    virtual void initialize() = 0;
    virtual void process() = 0;

    virtual bool flash(uint32_t address, const uint8_t* data, size_t len,
                       ProgressCallback callback = nullptr) = 0;
    virtual bool verify(uint32_t address, const uint8_t* data, size_t len) = 0;
    virtual bool boot(uint32_t entryPoint) = 0;

    virtual BootloaderStatus getLastStatus() const = 0;
    virtual const char* getLastError() const = 0;
};

}

#endif
