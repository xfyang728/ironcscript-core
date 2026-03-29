#ifndef CSE_FIRMWARE_FIRMWARE_HEADER_H
#define CSE_FIRMWARE_FIRMWARE_HEADER_H

#include <cstdint>

namespace cse {

constexpr uint32_t FIRMWARE_MAGIC = 0x46435343;
constexpr uint32_t FIRMWARE_VERSION = 0x00010000;

#pragma pack(push, 1)

struct FirmwareHeader {
    uint32_t magic;
    uint32_t version;
    uint32_t codeSize;
    uint32_t codeCrc32;
    uint32_t csbOffset;
    uint32_t csbSize;
    uint32_t csbCrc32;
    uint8_t reserved[32];
};

#pragma pack(pop)

bool verifyFirmwareHeader(const FirmwareHeader* header);
bool verifyFirmwareIntegrity(const FirmwareHeader* header, const uint8_t* codeData);

}

#endif
