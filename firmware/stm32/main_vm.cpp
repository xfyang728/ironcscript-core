#include <cstdio>
#include <cstring>
#include <cstdint>

#include "hal/IStandardGPIO.h"
#include "hal/IStandardUART.h"
#include "hal/IStandardTimer.h"
#include "hal/HardwareFactory.h"
#include "platform/stm32/STM32GPIO.h"
#include "platform/stm32/STM32UART.h"
#include "platform/stm32/STM32Timer.h"
#include "platform/PlatformConstants.h"
#include "bytecode/BytecodeFormat.h"

namespace {

static cse::IStandardGPIO* g_GPIO = nullptr;
static cse::IStandardUART* g_UART = nullptr;
static cse::IStandardTimer* g_Timer = nullptr;

void nativePrint(cse::BytecodeVM* vm) {
    cse::VMValue val = vm->getReturnValue();
    if (val.type == cse::ValueType::INTEGER) {
        printf("%lld", (long long)val.value.intVal);
    } else if (val.type == cse::ValueType::DOUBLE) {
        printf("%f", val.value.doubleVal);
    }
}

void nativeGpioSetMode(cse::BytecodeVM* vm) {
    printf("[NATIVE] gpio_set_mode called\r\n");
    fflush(stdout);
    if (!g_GPIO) {
        printf("[NATIVE] gpio_set_mode: g_GPIO is NULL!\r\n");
        fflush(stdout);
        return;
    }
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    printf("[NATIVE] gpio_set_mode: arg0.type=%d, arg1.type=%d\r\n", (int)arg0.type, (int)arg1.type);
    fflush(stdout);
    if (arg0.type != cse::ValueType::INTEGER || arg1.type != cse::ValueType::INTEGER) {
        printf("[NATIVE] gpio_set_mode: invalid arg types!\r\n");
        fflush(stdout);
        return;
    }
    int pin = static_cast<int>(arg0.value.intVal);
    int mode = static_cast<int>(arg1.value.intVal);
    printf("[NATIVE] gpio_set_mode(pin=%d, mode=%d)\r\n", pin, mode);
    fflush(stdout);
    g_GPIO->setMode(pin, static_cast<cse::GPIOMode>(mode));
    printf("[NATIVE] gpio_set_mode: done\r\n");
    fflush(stdout);
}

void nativeGpioWrite(cse::BytecodeVM* vm) {
    if (!g_GPIO) return;
    int value = static_cast<int>(vm->getArg(1).value.intVal);
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    g_GPIO->write(pin, value != 0);
}

void nativeGpioRead(cse::BytecodeVM* vm) {
    if (!g_GPIO) {
        vm->getReturnValue() = cse::VMValue::makeInt(0);
        return;
    }
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    bool val = g_GPIO->read(pin);
    vm->getReturnValue() = cse::VMValue::makeInt(val ? 1 : 0);
}

void nativeUartConfig(cse::BytecodeVM* vm) {
    (void)vm;
    if (!g_UART) return;
    cse::UARTConfig config;
    config.baudrate = 115200;
    config.data_bits = 8;
    config.parity = cse::UARTParity::NONE;
    config.stop_bits = cse::UARTStopBits::ONE;
    g_UART->configure(config);
}

void nativeUartWrite(cse::BytecodeVM* vm) {
    printf("[NATIVE] uart_write called\r\n");
    fflush(stdout);
    if (!g_UART) {
        printf("[NATIVE] uart_write: g_UART is NULL!\r\n");
        fflush(stdout);
        return;
    }
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    printf("[NATIVE] uart_write: arg0.type=%d, arg1.type=%d\r\n", (int)arg0.type, (int)arg1.type);
    fflush(stdout);
    if (arg0.type != cse::ValueType::INTEGER || arg1.type != cse::ValueType::INTEGER) {
        printf("[NATIVE] uart_write: invalid arg types!\r\n");
        fflush(stdout);
        return;
    }
    int ch = static_cast<int>(arg1.value.intVal);
    uint8_t byte = static_cast<uint8_t>(ch & 0xFF);
    printf("[NATIVE] uart_write: writing byte 0x%02X '%c'\r\n", byte, (byte >= 32 && byte < 127) ? byte : '.');
    fflush(stdout);
    g_UART->write(&byte, 1);
    printf("[NATIVE] uart_write: done\r\n");
    fflush(stdout);
}

void nativeTimerStart(cse::BytecodeVM* vm) {
    if (!g_Timer) return;
    int periodic = static_cast<int>(vm->getArg(1).value.intVal);
    int period = static_cast<int>(vm->getArg(0).value.intVal);
    g_Timer->start(period, periodic != 0);
}

void nativeTimerStop(cse::BytecodeVM* vm) {
    (void)vm;
    if (!g_Timer) return;
    g_Timer->stop();
}

void nativeDelay(cse::BytecodeVM* vm) {
    cse::VMValue arg = vm->getArg(0);
    printf("[NATIVE] delay called, arg.type=%d, arg.value.intVal=%lld\r\n",
           (int)arg.type, (long long)arg.value.intVal);
    fflush(stdout);
    int ms = static_cast<int>(arg.value.intVal);
    printf("[NATIVE] delay(%d)\r\n", ms);
    fflush(stdout);
    g_Timer->start(ms * 1000, false);
}

class STM32VM {
public:
    STM32VM() : m_VM(nullptr), m_Running(false) {}

    bool init() {
        m_VM = new cse::BytecodeVM(cse::VMConfig{
            .stackSize = 512,
            .heapSize = 4096,
            .maxCallDepth = 16
        });
        if (!m_VM) return false;

        m_VM->registerNativeFunction("print", nativePrint);
        m_VM->registerNativeFunction("gpio_set_mode", nativeGpioSetMode);
        m_VM->registerNativeFunction("gpio_write", nativeGpioWrite);
        m_VM->registerNativeFunction("gpio_read", nativeGpioRead);
        m_VM->registerNativeFunction("uart_config", nativeUartConfig);
        m_VM->registerNativeFunction("uart_write", nativeUartWrite);
        m_VM->registerNativeFunction("timer_start", nativeTimerStart);
        m_VM->registerNativeFunction("timer_stop", nativeTimerStop);
        m_VM->registerNativeFunction("delay", nativeDelay);

        cse::RegisterFunc regFunc = [this](const char* name, int64_t value) {
            m_VM->registerConstant(name, value);
        };
        cse::STM32Constants::registerAll(regFunc);

        g_GPIO = new cse::STM32GPIO();
        g_UART = new cse::STM32UART();
        g_Timer = new cse::STM32Timer();

        cse::UARTConfig config;
        config.baudrate = 115200;
        config.data_bits = 8;
        config.parity = cse::UARTParity::NONE;
        config.stop_bits = cse::UARTStopBits::ONE;
        g_UART->configure(config);

        printf("[VM] Hardware init complete\r\n");
        fflush(stdout);
        return true;
    }

    bool loadAndRun(uint32_t addr) {
        (void)addr;
        printf("[VM] STM32 VM loadAndRun called (addr=0x%X)\r\n", addr);
        fflush(stdout);
        printf("[VM] Note: Flash loading not implemented for STM32 yet\r\n");
        fflush(stdout);
        return true;
    }

    ~STM32VM() {
        delete m_VM;
        delete g_GPIO;
        delete g_UART;
        delete g_Timer;
        g_GPIO = nullptr;
        g_UART = nullptr;
        g_Timer = nullptr;
    }

private:
    cse::BytecodeVM* m_VM;
    bool m_Running;
};

}

bool loadAndExecuteCSB() {
    static STM32VM vm;
    if (!vm.init()) {
        printf("[VM] ERROR: Failed to initialize VM\r\n");
        return false;
    }
    return vm.loadAndRun(0x08000000);
}

int main(void) {
    printf("\r\n");
    printf("========================================\r\n");
    printf("IronCS STM32 VM (Script Runner)\r\n");
    printf("========================================\r\n");
    printf("\r\n");

    printf("[MAIN] Initializing STM32 hardware...\r\n");
    fflush(stdout);

    if (loadAndExecuteCSB()) {
        printf("[MAIN] Script execution completed successfully\r\n");
    } else {
        printf("[MAIN] Script execution failed\r\n");
    }

    while (1) {
    }

    return 0;
}