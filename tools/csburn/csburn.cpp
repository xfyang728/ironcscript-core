#include "protocol.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#endif

namespace {

#ifdef _WIN32
using SerialHandle = HANDLE;
constexpr DWORD DEFAULT_BAUD = CBR_115200;
#else
using SerialHandle = int;
constexpr speed_t DEFAULT_BAUD = B115200;
#endif

class SerialPort {
public:
    SerialPort() : m_Handle(INVALID_HANDLE_VALUE), m_Timeout(1000) {}

    ~SerialPort() { close(); }

    bool open(const std::string& port, uint32_t baud = DEFAULT_BAUD) {
#ifdef _WIN32
        std::string fullPort = "\\\\.\\" + port;
        m_Handle = CreateFileA(fullPort.c_str(),
                              GENERIC_READ | GENERIC_WRITE,
                              0, nullptr, OPEN_EXISTING,
                              0, nullptr);
        if (m_Handle == INVALID_HANDLE_VALUE) {
            return false;
        }

        DCB dcb = {0};
        dcb.DCBlength = sizeof(dcb);
        if (!BuildCommDCBA("115200,n,8,1", &dcb)) {
            close();
            return false;
        }
        dcb.BaudRate = baud;
        if (!SetCommState(m_Handle, &dcb)) {
            close();
            return false;
        }

        COMMTIMEOUTS timeout = {MAXDWORD, 0, 100, 0, 0};
        SetCommTimeouts(m_Handle, &timeout);
#else
        m_Handle = ::open(port.c_str(), O_RDWR | O_NOCTTY);
        if (m_Handle < 0) return false;

        termios tty;
        cfmakeraw(&tty);
        cfsetispeed(&tty, DEFAULT_BAUD);
        cfsetospeed(&tty, DEFAULT_BAUD);
        tcsetattr(m_Handle, TCSANOW, &tty);
#endif
        return true;
    }

    void close() {
#ifdef _WIN32
        if (m_Handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_Handle);
            m_Handle = INVALID_HANDLE_VALUE;
        }
#else
        if (m_Handle >= 0) {
            ::close(m_Handle);
            m_Handle = -1;
        }
#endif
    }

    bool write(const uint8_t* data, size_t len, uint32_t timeout_ms = 1000) {
#ifdef _WIN32
        DWORD written;
        COMMTIMEOUTS to = {0, 0, timeout_ms, 0, 0};
        SetCommTimeouts(m_Handle, &to);
        return WriteFile(m_Handle, data, len, &written, nullptr) && written == len;
#else
        return ::write(m_Handle, data, len) == len;
#endif
    }

    bool read(uint8_t* data, size_t len, uint32_t timeout_ms = 1000) {
#ifdef _WIN32
        DWORD read;
        COMMTIMEOUTS to = {0, 0, timeout_ms, 0, 0};
        SetCommTimeouts(m_Handle, &to);
        return ReadFile(m_Handle, data, len, &read, nullptr) && read == len;
#else
        fd_set fd;
        FD_ZERO(&fd);
        FD_SET(m_Handle, &fd);
        struct timeval tv = {0, (long)timeout_ms * 1000};
        if (select(m_Handle + 1, &fd, nullptr, nullptr, &tv) <= 0) return false;
        return ::read(m_Handle, data, len) == len;
#endif
    }

    void setTimeout(uint32_t ms) { m_Timeout = ms; }

private:
    SerialHandle m_Handle;
    uint32_t m_Timeout;
};

bool waitForAck(SerialPort& serial, int retries = 10) {
    uint8_t ack[32];
    for (int i = 0; i < retries; ++i) {
        if (serial.read(ack, 16, 500)) {
            if (ack[0] == 0xAA && ack[1] == 0x55 && ack[2] == static_cast<uint8_t>(csburn::KBPCommand::ACK)) {
                return true;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return false;
}

}

void printUsage(const char* prog) {
    std::cout << "CSBurn - IronCS K210 Burn Tool v1.0\n\n"
              << "Usage: " << prog << " [options]\n\n"
              << "Options:\n"
              << "  -p, --port <port>     Serial port (COM3, /dev/ttyUSB0)\n"
              << "  -b, --baud <baud>     Baud rate (115200, 921600)\n"
              << "  -f, --file <file>     .csb file to burn\n"
              << "  -a, --addr <addr>     Flash address (hex, default: 0x8000)\n"
              << "  -e, --erase          Erase before writing\n"
              << "  -v, --verify          Verify after writing\n"
              << "  -t, --timeout <ms>    Timeout in ms (default: 30000)\n"
              << "  -h, --help           Show this help\n\n"
              << "Example:\n"
              << "  " << prog << " -p COM3 -f program.csb\n"
              << "  " << prog << " -p /dev/ttyUSB0 -b 921600 -f program.csb -v\n";
}

int main(int argc, char* argv[]) {
    std::string port;
    std::string filename;
    uint32_t baud = 115200;
    uint32_t flashAddr = 0x8000;
    bool doErase = false;
    bool doVerify = false;
    uint32_t timeout = 30000;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-p" || arg == "--port") {
            if (++i < argc) port = argv[i];
        } else if (arg == "-b" || arg == "--baud") {
            if (++i < argc) baud = std::stoul(argv[i]);
        } else if (arg == "-f" || arg == "--file") {
            if (++i < argc) filename = argv[i];
        } else if (arg == "-a" || arg == "--addr") {
            if (++i < argc) flashAddr = std::stoul(argv[i], nullptr, 16);
        } else if (arg == "-e" || arg == "--erase") {
            doErase = true;
        } else if (arg == "-v" || arg == "--verify") {
            doVerify = true;
        } else if (arg == "-t" || arg == "--timeout") {
            if (++i < argc) timeout = std::stoul(argv[i]);
        } else if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        }
    }

    if (port.empty() || filename.empty()) {
        printUsage(argv[0]);
        return 1;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return 1;
    }
    size_t fileSize = file.tellg();
    file.seekg(0);

    std::vector<uint8_t> fileData(fileSize);
    file.read(reinterpret_cast<char*>(fileData.data()), fileSize);
    file.close();

    std::cout << "CSBurn - IronCS K210 Burn Tool\n";
    std::cout << "================================\n";
    std::cout << "Port:    " << port << "\n";
    std::cout << "Baud:    " << baud << "\n";
    std::cout << "File:    " << filename << " (" << fileSize << " bytes)\n";
    std::cout << "Address: 0x" << std::hex << flashAddr << std::dec << "\n\n";

    SerialPort serial;
    if (!serial.open(port, baud)) {
        std::cerr << "Error: Cannot open serial port: " << port << "\n";
        return 1;
    }
    std::cout << "[OK] Serial port opened\n";

    std::cout << "[...] Searching for device...\n";
    uint8_t syn[16] = {0xAA, 0x55, 0xAA, 0x55, 0x01, 0x01, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t resp[32];

    bool found = false;
    for (int i = 0; i < 5; ++i) {
        serial.write(syn, 16, 500);
        if (serial.read(resp, 32, 1000)) {
            if (resp[0] == 0xAA && resp[1] == 0x55) {
                found = true;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    if (!found) {
        std::cerr << "Error: Device not found or not in boot mode\n";
        std::cerr << "Hint: Press and hold the BOOT button, then press RESET\n";
        return 1;
    }

    csburn::DeviceInfo* info = reinterpret_cast<csburn::DeviceInfo*>(&resp[8]);
    std::cout << "[OK] Device found: " << info->boardName << "\n";
    std::cout << "     Flash: " << (int)info->flashSizeMB << "MB\n";
    std::cout << "     VM:    v" << (int)info->vmVersion[0] << "."
              << (int)info->vmVersion[1] << "."
              << (int)info->vmVersion[2] << "\n\n";

    if (doErase) {
        std::cout << "[...] Erasing flash...\n";
        uint8_t eraseCmd[16] = {0xAA, 0x55, 0x05, 0x00, 0x00, 0x00,
                                 (uint8_t)(flashAddr >> 24),
                                 (uint8_t)(flashAddr >> 16),
                                 (uint8_t)(flashAddr >> 8),
                                 (uint8_t)flashAddr,
                                 (uint8_t)(fileSize >> 24),
                                 (uint8_t)(fileSize >> 16),
                                 (uint8_t)(fileSize >> 8),
                                 (uint8_t)fileSize, 0x00};
        eraseCmd[15] = csburn::calcCRC8(eraseCmd, 15);
        serial.write(eraseCmd, 16);
        if (!waitForAck(serial)) {
            std::cerr << "Error: Erase failed\n";
            return 1;
        }
        std::cout << "[OK] Flash erased\n";
    }

    std::cout << "[...] Writing " << fileSize << " bytes to flash...\n";
    size_t written = 0;
    size_t chunkSize = 256;
    uint32_t addr = flashAddr;

    while (written < fileSize) {
        size_t toWrite = std::min(chunkSize, fileSize - written);
        size_t packetSize = 12 + toWrite + 1;

        std::vector<uint8_t> packet(packetSize);
        packet[0] = 0xAA;
        packet[1] = 0x55;
        packet[2] = 0x04;
        packet[3] = 0x00;
        packet[4] = (uint8_t)((toWrite + 4) >> 8);
        packet[5] = (uint8_t)(toWrite + 4);
        packet[6] = (uint8_t)(addr >> 24);
        packet[7] = (uint8_t)(addr >> 16);
        packet[8] = (uint8_t)(addr >> 8);
        packet[9] = (uint8_t)addr;
        packet[10] = (uint8_t)(toWrite >> 8);
        packet[11] = (uint8_t)toWrite;
        memcpy(&packet[12], &fileData[written], toWrite);
        packet[packetSize - 1] = csburn::calcCRC8(packet.data(), packetSize - 1);

        serial.write(packet.data(), packetSize);
        if (!waitForAck(serial, 20)) {
            std::cerr << "Error: Write failed at offset " << written << "\n";
            return 1;
        }

        written += toWrite;
        addr += (uint32_t)toWrite;

        int progress = (int)(written * 100 / fileSize);
        std::cout << "\r      Progress: " << progress << "% (" << written << "/" << fileSize << " bytes)"
                  << std::flush;
    }
    std::cout << "\n[OK] Write completed\n";

    if (doVerify) {
        std::cout << "[...] Verifying...\n";
        uint8_t verifyCmd[16] = {0xAA, 0x55, 0x06, 0x00, 0x00, 0x00,
                                  (uint8_t)(flashAddr >> 24),
                                  (uint8_t)(flashAddr >> 16),
                                  (uint8_t)(flashAddr >> 8),
                                  (uint8_t)flashAddr,
                                  (uint8_t)(fileSize >> 24),
                                  (uint8_t)(fileSize >> 16),
                                  (uint8_t)(fileSize >> 8),
                                  (uint8_t)fileSize, 0x00};
        verifyCmd[15] = csburn::calcCRC8(verifyCmd, 15);
        serial.write(verifyCmd, 16);
        if (!waitForAck(serial)) {
            std::cerr << "Error: Verify failed\n";
            return 1;
        }
        std::cout << "[OK] Verification passed\n";
    }

    std::cout << "\n[.] Starting program...\n";
    uint8_t bootCmd[12] = {0xAA, 0x55, 0x07, 0x00, 0x00, 0x00,
                           (uint8_t)(flashAddr >> 24),
                           (uint8_t)(flashAddr >> 16),
                           (uint8_t)(flashAddr >> 8),
                           (uint8_t)flashAddr, 0x00, 0x00};
    bootCmd[11] = csburn::calcCRC8(bootCmd, 11);
    serial.write(bootCmd, 12);

    std::cout << "\n================================\n";
    std::cout << "[OK] Burn completed successfully!\n";
    std::cout << "\nProgram is running. Output:\n";
    std::cout << "--------------------------------\n";

    uint8_t buf[256];
    while (serial.read(buf, sizeof(buf), 1000)) {
        for (size_t i = 0; i < 256 && buf[i]; ++i) {
            std::cout << (char)buf[i];
        }
    }

    return 0;
}
