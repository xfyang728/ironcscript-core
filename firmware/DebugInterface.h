#ifndef CSE_FIRMWARE_DEBUG_INTERFACE_H
#define CSE_FIRMWARE_DEBUG_INTERFACE_H

#include "hal/IStandardUART.h"
#include "hal/CSError.h"
#include <cstdint>

namespace cse {

enum class DebugCommandType : uint8_t {
    CMD_PING = 0x00,
    CMD_GET_STATUS = 0x01,
    CMD_READ_MEMORY = 0x02,
    CMD_WRITE_MEMORY = 0x03,

    CMD_PAUSE_VM = 0x10,
    CMD_RESUME_VM = 0x11,
    CMD_STEP_VM = 0x12,
    CMD_GET_CALLSTACK = 0x13,
    CMD_SET_BREAKPOINT = 0x14,
    CMD_CLEAR_BREAKPOINT = 0x15,

    CMD_RESET_SYSTEM = 0xF0,
    CMD_JUMP_BOOTLOADER = 0xF1,
};

struct DebugCommand {
    DebugCommandType command;
    uint8_t length;
    uint8_t data[64];
};

struct SystemStatus {
    uint32_t uptime_ms;
    uint32_t vm_state;
    uint32_t stack_used;
    uint32_t heap_used;
    uint32_t gpio_state;
    uint32_t uart_rx_count;
    uint32_t uart_tx_count;
    uint32_t fault_count;
    int32_t last_error;
    uint8_t reserved[28];
};

class DebugInterface {
public:
    static void initialize(IStandardUART* uart);
    static void process();
    static void sendResponse(DebugCommandType cmd, const uint8_t* data, uint8_t len);
    static void sendError(CSError error);

    static SystemStatus& getStatus();
    static void updateStatus();

    static void setVMPaused(bool paused);
    static bool isVMPaused();

    static void incrementFaultCount();
    static void setLastError(CSError error);

private:
    static void handleCommand(const DebugCommand& cmd);
    static void handlePing();
    static void handleGetStatus();
    static void handleReadMemory(const DebugCommand& cmd);
    static void handleWriteMemory(const DebugCommand& cmd);
    static void handlePauseVM();
    static void handleResumeVM();
    static void handleStepVM();
    static void handleGetCallstack();
    static void handleSetBreakpoint(const DebugCommand& cmd);
    static void handleClearBreakpoint(const DebugCommand& cmd);
    static void handleResetSystem();
    static void handleJumpBootloader();

    static IStandardUART* s_UART;
    static SystemStatus s_Status;
    static bool s_VMPaused;
    static uint32_t s_Breakpoints[8];
    static uint8_t s_RxBuffer[128];
    static size_t s_RxPos;
};

}

#endif
