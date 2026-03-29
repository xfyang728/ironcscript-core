#ifndef CSBURN_PROTOCOL_H
#define CSBURN_PROTOCOL_H

#include <cstdint>
#include <cstddef>

namespace csburn {

constexpr uint32_t KBP_MAGIC = 0xFFAA55AA;
constexpr uint8_t  KBP_VERSION = 0x01;

constexpr size_t KBP_MAX_PACKET_SIZE = 4096;
constexpr uint32_t KBP_FLASH_BASE = 0x00000000;
constexpr uint32_t KBP_CSB_STORE_ADDR = 0x00080000;

enum class KBPCommand : uint8_t {
    SYN         = 0x01,
    ACK         = 0x02,
    NACK        = 0x03,
    WRITE       = 0x04,
    ERASE       = 0x05,
    VERIFY      = 0x06,
    BOOT        = 0x07,
    INFO        = 0x08,
    RESET       = 0x09,
    GET_STATUS  = 0x0A,
    WRITE_DONE  = 0x0B,
};

enum class KBPStatus : uint8_t {
    OK          = 0x00,
    ERROR       = 0x01,
    TIMEOUT     = 0x02,
    INVALID_CMD = 0x03,
    CRC_ERROR   = 0x04,
    FLASH_ERROR = 0x05,
};

enum class KBPPhase : uint8_t {
    BOOT        = 0x00,
    RECEIVING   = 0x01,
    VERIFYING   = 0x02,
    RUNNING     = 0x03,
};

struct KBPHeader {
    uint32_t magic;
    uint8_t  version;
    KBPCommand command;
    uint8_t  flags;
    uint16_t payloadLen;
    uint32_t address;
    uint32_t reserved;
};

struct KBPPacket {
    KBPHeader header;
    uint8_t   payload[KBP_MAX_PACKET_SIZE];
    uint8_t   crc8;
};

struct DeviceInfo {
    uint8_t  boardName[16];
    uint8_t  flashSizeMB;
    uint8_t  vmVersion[4];
    uint32_t vmBuildDate;
    uint8_t  reserved[6];
};

struct WriteStatus {
    uint32_t bytesWritten;
    uint32_t bytesTotal;
    uint8_t  progress;
    KBPPhase phase;
    uint8_t  lastError;
};

uint8_t calcCRC8(const uint8_t* data, size_t len);
uint16_t calcCRC16(const uint8_t* data, size_t len);

}

#endif
