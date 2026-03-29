#include "hal/CSError.h"

namespace cse {

const char* getErrorString(CSError err) {
    switch (err) {
        case CSError::SUCCESS:
            return "Success";

        case CSError::ERR_GPIO_INVALID_PIN:
            return "GPIO: Invalid pin number";
        case CSError::ERR_GPIO_INVALID_MODE:
            return "GPIO: Invalid mode";
        case CSError::ERR_GPIO_INTERRUPT_FAILED:
            return "GPIO: Failed to enable interrupt";

        case CSError::ERR_UART_CONFIG_FAILED:
            return "UART: Configuration failed";
        case CSError::ERR_UART_TIMEOUT:
            return "UART: Read timeout";
        case CSError::ERR_UART_BUFFER_OVERFLOW:
            return "UART: Buffer overflow";
        case CSError::ERR_UART_BUFFER_EMPTY:
            return "UART: Buffer empty";
        case CSError::ERR_UART_INVALID_ID:
            return "UART: Invalid UART ID";

        case CSError::ERR_TIMER_INVALID_ID:
            return "Timer: Invalid timer ID";
        case CSError::ERR_TIMER_NOT_RUNNING:
            return "Timer: Not running";
        case CSError::ERR_TIMER_CONFIG_FAILED:
            return "Timer: Configuration failed";

        case CSError::ERR_WATCHDOG_TIMEOUT:
            return "Watchdog: Timeout triggered";
        case CSError::ERR_WATCHDOG_INIT_FAILED:
            return "Watchdog: Initialization failed";

        case CSError::ERR_VM_STACK_OVERFLOW:
            return "VM: Stack overflow";
        case CSError::ERR_VM_STACK_UNDERFLOW:
            return "VM: Stack underflow";
        case CSError::ERR_VM_INVALID_OPCODE:
            return "VM: Invalid opcode";
        case CSError::ERR_VM_INVALID_JUMP:
            return "VM: Invalid jump address";
        case CSError::ERR_VM_DIVISION_BY_ZERO:
            return "VM: Division by zero";
        case CSError::ERR_VM_NATIVE_CALL_FAILED:
            return "VM: Native function call failed";
        case CSError::ERR_VM_CALL_DEPTH_EXCEEDED:
            return "VM: Call depth exceeded";
        case CSError::ERR_VM_INVALID_FUNCTION:
            return "VM: Invalid function";
        case CSError::ERR_VM_TYPE_MISMATCH:
            return "VM: Type mismatch";

        case CSError::ERR_FLASH_READ_FAILED:
            return "Flash: Read failed";
        case CSError::ERR_FLASH_WRITE_FAILED:
            return "Flash: Write failed";
        case CSError::ERR_FLASH_ERASE_FAILED:
            return "Flash: Erase failed";
        case CSError::ERR_CSB_INVALID_MAGIC:
            return "CSB: Invalid magic number";
        case CSError::ERR_CSB_VERSION_MISMATCH:
            return "CSB: Version mismatch";
        case CSError::ERR_CSB_INVALID_FUNCTION:
            return "CSB: Invalid function";
        case CSError::ERR_CSB_LOAD_FAILED:
            return "CSB: Load failed";

        case CSError::ERR_OUT_OF_MEMORY:
            return "System: Out of memory";
        case CSError::ERR_NULL_POINTER:
            return "System: Null pointer";
        case CSError::ERR_HARDWARE_FAULT:
            return "System: Hardware fault";
        case CSError::ERR_INVALID_STATE:
            return "System: Invalid state";

        case CSError::ERR_FIRMWARE_CRC_FAILED:
            return "Firmware: CRC check failed";
        case CSError::ERR_FIRMWARE_INVALID_HEADER:
            return "Firmware: Invalid header";

        default:
            return "Unknown error";
    }
}

}
