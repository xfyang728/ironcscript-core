#include <bsp.h>
#include <plic.h>
#include <sysctl.h>
#include <fpioa.h>
#include <uarths.h>
#include <spi.h>
#include <gpio.h>
#include <gpiohs.h>
#include <timer.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <vector>

#include "hal/CSError.h"
#include "hal/IStandardGPIO.h"
#include "hal/IStandardUART.h"
#include "hal/IStandardTimer.h"
#include "hal/IStandardWatchdog.h"
#include "hal/Logger.h"
#include "hal/HardwareFactory.h"
#include "platform/k210/K210GPIO.h"
#include "platform/k210/K210Timer.h"
#include "platform/k210/K210UART.h"
#include "platform/k210/K210Flash.h"
#include "platform/k210/K210Bootloader.h"
#include "platform/k210/CSBLoader.h"
#include "platform/PlatformConstants.h"
#include "bytecode/vm/BytecodeVM.h"
#include "bytecode/BytecodeFormat.h"
#include "FirmwareHeader.h"

extern "C" {
extern void k210_spi3_init(void);
extern void k210_delay_ms(uint32_t ms);
}

#define CSB_STORAGE_ADDR 0x00080000
#define WATCHDOG_TIMEOUT_MS 5000

// PLL Frequencies
constexpr uint32_t PLL0_FREQ = 800000000UL;
constexpr uint32_t PLL1_FREQ = 160000000UL;
constexpr uint32_t PLL2_FREQ = 45158400UL;

// UART Configuration
constexpr uint32_t UART_BAUDRATE = 115200;

// VM Configuration
constexpr uint32_t VM_STACK_SIZE = 512;
constexpr uint32_t VM_HEAP_SIZE = 4096;
constexpr uint32_t VM_MAX_CALL_DEPTH = 16;

// LED FPIOA Pins (原理图: IO12/IO13/IO14)
constexpr uint32_t LED_G_FPIOA_PIN = 13;
constexpr uint32_t LED_R_FPIOA_PIN = 14;
constexpr uint32_t LED_B_FPIOA_PIN = 12;

// Timing
constexpr uint32_t INIT_DELAY_MS = 100;
constexpr uint32_t MAIN_LOOP_DELAY_MS = 1000;

namespace {

static cse::IStandardGPIO* g_GPIO = nullptr;
static cse::IStandardUART* g_UART = nullptr;
static cse::IStandardTimer* g_Timer = nullptr;
static cse::BytecodeVM* g_VM = nullptr;
static bool g_Running = false;
static uint32_t g_UptimeMs = 0;

constexpr uint32_t LED_G_PIN = cse::K210Pin::GPIO5;
constexpr uint32_t LED_R_PIN = cse::K210Pin::GPIO4;
constexpr uint32_t LED_B_PIN = cse::K210Pin::GPIO3;

static void led_init(void) {
    cse::K210GPIO* k210gpio = static_cast<cse::K210GPIO*>(g_GPIO);
    if (!k210gpio) return;

    k210gpio->setFPIOAFunction(LED_G_FPIOA_PIN, FUNC_GPIO5);
    k210gpio->setFPIOAFunction(LED_R_FPIOA_PIN, FUNC_GPIO4);
    k210gpio->setFPIOAFunction(LED_B_FPIOA_PIN, FUNC_GPIO3);

    g_GPIO->setMode(LED_R_PIN, cse::GPIOMode::OUTPUT);
    g_GPIO->setMode(LED_G_PIN, cse::GPIOMode::OUTPUT);
    g_GPIO->setMode(LED_B_PIN, cse::GPIOMode::OUTPUT);

    g_GPIO->write(LED_R_PIN, true);
    g_GPIO->write(LED_G_PIN, true);
    g_GPIO->write(LED_B_PIN, true);
}

static void led_rgb_set(int r, int g, int b) {
    if (!g_GPIO) return;
    g_GPIO->write(LED_R_PIN, r == 0);
    g_GPIO->write(LED_G_PIN, g == 0);
    g_GPIO->write(LED_B_PIN, b == 0);
}

class K210Watchdog : public cse::IStandardWatchdog {
public:
    K210Watchdog() : m_Initialized(false), m_TimeoutMs(0) {}

    bool initialize(uint32_t timeout_ms) override {
        m_TimeoutMs = timeout_ms;
        m_Initialized = true;
        return true;
    }

    void feed() override {
    }

    bool isTriggered() override {
        return false;
    }

    uint32_t getRemainingTime() override {
        return m_TimeoutMs;
    }

    const char* getPlatformName() const override {
        return "K210";
    }

private:
    bool m_Initialized;
    uint32_t m_TimeoutMs;
};

static K210Watchdog g_Watchdog;

// ========== C Standard Library Print Functions ==========

/**
 * @brief C标准库 printf 函数 - 格式化打印
 * @param vm 指向BytecodeVM实例的指针
 * @note 支持格式说明符: %d(整数), %s(字符串), %f(浮点), %lld(长整数), %llx(十六进制)
 * @note 使用方式: printf("value=%d, name=%s\n", intVal, strVal)
 */
void nativePrintf(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    if (argCount < 1) return;

    cse::VMValue formatVal = vm->getArg(0);
    if (formatVal.type != cse::ValueType::STRING) {
        printf("[ERROR] printf: first argument must be a string format\r\n");
        return;
    }

    const char* format = vm->getStringFromConstant(formatVal.value.intVal);

    if (argCount == 1) {
        printf("%s", format);
        return;
    }

    std::vector<cse::VMValue> args;
    for (int32_t i = 1; i < argCount; i++) {
        args.push_back(vm->getArg(i));
    }

    char buffer[1024];
    int offset = 0;
    const char* p = format;

    while (*p) {
        if (*p == '%' && *(p + 1)) {
            char fmt[8] = "%";
            int fmtLen = 1;
            p++;

            if (*p == 'l' && *(p + 1) == 'l' && *(p + 2) == 'd') {
                strcat(fmt, "lld");
                fmtLen = 3;
                if (offset < (int)(sizeof(buffer) - 24)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (long long)args[0].value.intVal);
                    args.erase(args.begin());
                }
                p += 2;
            } else if (*p == 'l' && *(p + 1) == 'l' && *(p + 2) == 'x') {
                strcat(fmt, "llx");
                fmtLen = 3;
                if (offset < (int)(sizeof(buffer) - 24)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (unsigned long long)args[0].value.intVal);
                    args.erase(args.begin());
                }
                p += 2;
            } else if (*p == 'l' && *(p + 1) == 'd') {
                strcat(fmt, "ld");
                fmtLen = 2;
                if (offset < (int)(sizeof(buffer) - 24)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (long)args[0].value.intVal);
                    args.erase(args.begin());
                }
                p++;
            } else if (*p == 'd' || *p == 'i') {
                fmt[1] = *p;
                fmt[2] = '\0';
                if (offset < (int)(sizeof(buffer) - 24)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (int)args[0].value.intVal);
                    args.erase(args.begin());
                }
            } else if (*p == 's') {
                fmt[1] = *p;
                fmt[2] = '\0';
                if (args[0].type == cse::ValueType::STRING) {
                    const char* str = vm->getStringFromConstant(args[0].value.intVal);
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt, str);
                } else {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "(null)");
                }
                args.erase(args.begin());
            } else if (*p == 'f' || *p == 'F') {
                fmt[1] = *p;
                fmt[2] = '\0';
                if (offset < (int)(sizeof(buffer) - 64)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     args[0].value.doubleVal);
                    args.erase(args.begin());
                }
            } else if (*p == 'c') {
                fmt[1] = *p;
                fmt[2] = '\0';
                if (offset < (int)(sizeof(buffer) - 4)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (char)args[0].value.intVal);
                    args.erase(args.begin());
                }
            } else if (*p == 'x' || *p == 'X') {
                fmt[1] = *p;
                fmt[2] = '\0';
                if (offset < (int)(sizeof(buffer) - 24)) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, fmt,
                                     (unsigned int)args[0].value.intVal);
                    args.erase(args.begin());
                }
            } else {
                buffer[offset++] = '%';
                buffer[offset++] = *p;
                buffer[offset] = '\0';
            }
            p++;
        } else if (*p == '\\' && *(p + 1) == 'n') {
            buffer[offset++] = '\n';
            buffer[offset] = '\0';
            p += 2;
        } else if (*p == '\\' && *(p + 1) == 'r') {
            buffer[offset++] = '\r';
            buffer[offset] = '\0';
            p += 2;
        } else if (*p == '\\' && *(p + 1) == 't') {
            buffer[offset++] = '\t';
            buffer[offset] = '\0';
            p += 2;
        } else {
            buffer[offset++] = *p++;
            buffer[offset] = '\0';
        }

        if (offset >= (int)(sizeof(buffer) - 1)) break;
    }

    printf("%s", buffer);
}

/**
 * @brief C标准库 puts 函数 - 打印字符串并换行
 * @param vm 指向BytecodeVM实例的指针
 * @note 等同于 printf("%s\n", str)
 */
void nativePuts(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    if (argCount < 1) {
        printf("\r\n");
        return;
    }

    cse::VMValue val = vm->getArg(0);
    if (val.type == cse::ValueType::STRING) {
        const char* str = vm->getStringFromConstant(val.value.intVal);
        printf("%s\r\n", str);
    } else if (val.type == cse::ValueType::INTEGER) {
        printf("%lld\r\n", (long long)val.value.intVal);
    } else {
        printf("(unknown)\r\n");
    }
}

/**
 * @brief Arduino风格引脚模式配置
 * @param vm 指向BytecodeVM实例的指针
 * @note 映射到Arduino的pinMode()函数，用于配置引脚为输入或输出模式
 * @todo 添加对INPUT_PULLUP等更多模式的支持
 */
void nativePinMode(cse::BytecodeVM* vm) {
    if (!g_GPIO) {
        LOG_ERROR("pinMode: GPIO not initialized");
        return;
    }
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int mode = static_cast<int>(vm->getArg(1).value.intVal);
    LOG_DEBUG("pinMode(%d, %d)", pin, mode);
    g_GPIO->setMode(pin, static_cast<cse::GPIOMode>(mode));
}

/**
 * @brief Arduino风格数字写入
 * @param vm 指向BytecodeVM实例的指针
 * @note 映射到Arduino的digitalWrite()函数，写入HIGH(1)或LOW(0)
 */
void nativeDigitalWrite(cse::BytecodeVM* vm) {
    if (!g_GPIO) return;
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int value = static_cast<int>(vm->getArg(1).value.intVal);
    LOG_DEBUG("digitalWrite(%d, %d)", pin, value);
    g_GPIO->write(pin, value != 0);
}

/**
 * @brief Arduino风格数字读取
 * @param vm 指向BytecodeVM实例的指针
 * @return VMValue 读取的引脚值(0或1)
 * @note 映射到Arduino的digitalRead()函数，返回引脚的当前数字电平
 */
void nativeDigitalRead(cse::BytecodeVM* vm) {
    if (!g_GPIO) {
        vm->getReturnValue() = cse::VMValue::makeInt(0);
        return;
    }
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    bool val = g_GPIO->read(pin);
    vm->getReturnValue() = cse::VMValue::makeInt(val ? 1 : 0);
}

/**
 * @brief Arduino风格模拟写入(PWM)
 * @param vm 指向BytecodeVM实例的指针
 * @note 映射到Arduino的analogWrite()函数，使用PWM实现近似模拟输出
 * @todo 实现真正的硬件PWM，使用K210定时器替代当前的简单阈值方法
 */
void nativeAnalogWrite(cse::BytecodeVM* vm) {
    if (!g_GPIO) return;
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int value = static_cast<int>(vm->getArg(1).value.intVal);

    if (value < 0) value = 0;
    if (value > 255) value = 255;

    LOG_DEBUG("analogWrite(%d, %d)", pin, value);

    cse::K210GPIO* k210gpio = static_cast<cse::K210GPIO*>(g_GPIO);
    k210gpio->setPWM(pin, value);
}

// ========== Legacy API ==========

void nativeGpioSetMode(cse::BytecodeVM* vm) {
    if (!g_GPIO) {
        LOG_ERROR("gpio_set_mode: GPIO not initialized");
        return;
    }
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    if (arg0.type != cse::ValueType::INTEGER || arg1.type != cse::ValueType::INTEGER) {
        LOG_ERROR("gpio_set_mode: invalid argument types");
        return;
    }
    int pin = static_cast<int>(arg0.value.intVal);
    int mode = static_cast<int>(arg1.value.intVal);
    LOG_DEBUG("gpio_set_mode(pin=%d, mode=%d)", pin, mode);
    g_GPIO->setMode(pin, static_cast<cse::GPIOMode>(mode));
}

void nativeGpioWrite(cse::BytecodeVM* vm) {
    if (!g_GPIO) return;
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int value = static_cast<int>(vm->getArg(1).value.intVal);
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

void nativeRgbSet(cse::BytecodeVM* vm) {
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    cse::VMValue arg2 = vm->getArg(2);
    int r = static_cast<int>(arg0.value.intVal);
    int g = static_cast<int>(arg1.value.intVal);
    int b = static_cast<int>(arg2.value.intVal);
    LOG_DEBUG("rgb_set(%d, %d, %d)", r, g, b);
    led_rgb_set(r, g, b);
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

void nativeLedInit(cse::BytecodeVM* vm) {
    LOG_DEBUG("led_init()");
    led_init();
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

void nativeFpioaSetFunc(cse::BytecodeVM* vm) {
    if (!g_GPIO) {
        LOG_ERROR("fpioa_set_func: GPIO not initialized");
        vm->getReturnValue() = cse::VMValue::makeInt(-1);
        return;
    }
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    if (arg0.type != cse::ValueType::INTEGER || arg1.type != cse::ValueType::INTEGER) {
        LOG_ERROR("fpioa_set_func: invalid argument types");
        vm->getReturnValue() = cse::VMValue::makeInt(-1);
        return;
    }
    int pin = static_cast<int>(arg0.value.intVal);
    int func = static_cast<int>(arg1.value.intVal);
    LOG_DEBUG("fpioa_set_func(pin=%d, func=%d)", pin, func);
    
    cse::K210GPIO* k210gpio = static_cast<cse::K210GPIO*>(g_GPIO);
    k210gpio->setFPIOAFunction(pin, func);
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

void nativeUartConfig(cse::BytecodeVM* vm) {
    (void)vm;
    if (!g_UART) return;
    cse::UARTConfig config;
    config.baudrate = UART_BAUDRATE;
    config.data_bits = 8;
    config.parity = cse::UARTParity::NONE;
    config.stop_bits = cse::UARTStopBits::ONE;
    g_UART->configure(config);
    LOG_DEBUG("uart_config: 115200 8N1");
}

void nativeUartWrite(cse::BytecodeVM* vm) {
    if (!g_UART) {
        LOG_ERROR("uart_write: UART not initialized");
        return;
    }
    cse::VMValue arg0 = vm->getArg(0);
    cse::VMValue arg1 = vm->getArg(1);
    if (arg0.type != cse::ValueType::INTEGER || arg1.type != cse::ValueType::INTEGER) {
        LOG_ERROR("uart_write: invalid argument types");
        return;
    }
    int ch = static_cast<int>(arg1.value.intVal);
    uint8_t byte = static_cast<uint8_t>(ch & 0xFF);
    g_UART->write(&byte, 1);
}

void nativeUartRead(cse::BytecodeVM* vm) {
    if (!g_UART) {
        vm->getReturnValue() = cse::VMValue::makeInt(-1);
        return;
    }
    uint8_t byte;
    if (g_UART->read(&byte, 1, 100) > 0) {
        vm->getReturnValue() = cse::VMValue::makeInt(byte);
    } else {
        vm->getReturnValue() = cse::VMValue::makeInt(-1);
    }
}

void nativeTimerStart(cse::BytecodeVM* vm) {
    if (!g_Timer) return;
    int period = static_cast<int>(vm->getArg(0).value.intVal);
    int periodic = static_cast<int>(vm->getArg(1).value.intVal);
    g_Timer->start(period, periodic != 0);
    LOG_DEBUG("timer_start(period=%d, periodic=%d)", period, periodic);
}

void nativeTimerStop(cse::BytecodeVM* vm) {
    (void)vm;
    if (!g_Timer) return;
    g_Timer->stop();
    LOG_DEBUG("timer_stop");
}

void nativeDelay(cse::BytecodeVM* vm) {
    cse::VMValue arg = vm->getArg(0);
    int ms = static_cast<int>(arg.value.intVal);
    LOG_TRACE("delay(%d)", ms);
    k210_delay_ms(ms);
    g_UptimeMs += ms;
    cse::Logger::setUptimeMs(g_UptimeMs);
}

void nativeMillis(cse::BytecodeVM* vm) {
    vm->getReturnValue() = cse::VMValue::makeInt(g_UptimeMs);
}

void nativeLogInfo(cse::BytecodeVM* vm) {
    cse::VMValue arg = vm->getArg(0);
    if (arg.type == cse::ValueType::INTEGER) {
        LOG_INFO("script: %lld", (long long)arg.value.intVal);
    } else if (arg.type == cse::ValueType::DOUBLE) {
        LOG_INFO("script: %f", arg.value.doubleVal);
    }
}

void nativeDumpConstants(cse::BytecodeVM* vm) {
    vm->dumpConstants();
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

cse::CSError initializeHardware() {
    LOG_INFO("Initializing hardware...");

    g_GPIO = new cse::K210GPIO();
    if (!g_GPIO) {
        LOG_FATAL("Failed to create GPIO instance");
        return cse::CSError::ERR_OUT_OF_MEMORY;
    }

    g_UART = new cse::K210UART(0);
    if (!g_UART) {
        LOG_FATAL("Failed to create UART instance");
        return cse::CSError::ERR_OUT_OF_MEMORY;
    }

    static_cast<cse::K210UART*>(g_UART)->setGPIO(static_cast<cse::K210GPIO*>(g_GPIO));

    cse::UARTConfig config;
    config.baudrate = 115200;
    config.data_bits = 8;
    config.parity = cse::UARTParity::NONE;
    config.stop_bits = cse::UARTStopBits::ONE;
    g_UART->configure(config);

    cse::Logger::initialize(g_UART, cse::LogLevel::DEBUG);

    g_Timer = new cse::K210Timer(0);
    if (!g_Timer) {
        LOG_FATAL("Failed to create Timer instance");
        return cse::CSError::ERR_OUT_OF_MEMORY;
    }

    if (!g_Watchdog.initialize(WATCHDOG_TIMEOUT_MS)) {
        LOG_WARN("Watchdog initialization failed");
    }

    LOG_INFO("Hardware initialized successfully");
    return cse::CSError::SUCCESS;
}

cse::CSError initializeVM() {
    LOG_INFO("Initializing VM...");

    g_VM = new cse::BytecodeVM(cse::VMConfig{
        .stackSize = VM_STACK_SIZE,
        .heapSize = VM_HEAP_SIZE,
        .maxCallDepth = VM_MAX_CALL_DEPTH
    });
    if (!g_VM) {
        LOG_FATAL("Failed to create VM instance");
        return cse::CSError::ERR_OUT_OF_MEMORY;
    }

    // C Standard Library Print Functions
    g_VM->registerNativeFunction("printf", nativePrintf);
    g_VM->registerNativeFunction("puts", nativePuts);

    // Hardware GPIO API
    g_VM->registerNativeFunction("pinMode", nativePinMode);
    g_VM->registerNativeFunction("digitalWrite", nativeDigitalWrite);
    g_VM->registerNativeFunction("digitalRead", nativeDigitalRead);
    g_VM->registerNativeFunction("analogWrite", nativeAnalogWrite);
    g_VM->registerNativeFunction("rgb_set", nativeRgbSet);
    g_VM->registerNativeFunction("fpioa_set_func", nativeFpioaSetFunc);

    // Legacy GPIO API
    g_VM->registerNativeFunction("gpio_set_mode", nativeGpioSetMode);
    g_VM->registerNativeFunction("gpio_write", nativeGpioWrite);
    g_VM->registerNativeFunction("gpio_read", nativeGpioRead);
    g_VM->registerNativeFunction("uart_config", nativeUartConfig);
    g_VM->registerNativeFunction("uart_write", nativeUartWrite);
    g_VM->registerNativeFunction("uart_read", nativeUartRead);
    g_VM->registerNativeFunction("timer_start", nativeTimerStart);
    g_VM->registerNativeFunction("timer_stop", nativeTimerStop);
    g_VM->registerNativeFunction("delay", nativeDelay);
    g_VM->registerNativeFunction("millis", nativeMillis);
    g_VM->registerNativeFunction("rgb_set", nativeRgbSet);
    g_VM->registerNativeFunction("led_init", nativeLedInit);
    g_VM->registerNativeFunction("fpioa_set_func", nativeFpioaSetFunc);
    g_VM->registerNativeFunction("log_info", nativeLogInfo);
    g_VM->registerNativeFunction("dump_constants", nativeDumpConstants);

    cse::RegisterFunc regFunc = [&g_VM](const char* name, int64_t value) {
        g_VM->registerConstant(name, value);
    };
    cse::K210Constants::registerAll(regFunc);

    LOG_INFO("VM initialized with %d native functions", 20);
    return cse::CSError::SUCCESS;
}

cse::CSError loadAndExecuteCSB(uint32_t addr) {
    LOG_INFO("Loading CSB from 0x%08X", addr);

    cse::BytecodeModule module;
    if (!cse::CSBLoader::loadFromFlash(addr, module)) {
        LOG_ERROR("Failed to load CSB from flash");
        return cse::CSError::ERR_CSB_LOAD_FAILED;
    }

    LOG_INFO("CSB loaded: %u functions, %u strings, %u constants",
             (unsigned)module.functions.size(),
             (unsigned)module.stringPool.size(),
             (unsigned)module.globalConstants.size());

    if (!g_VM->loadModule(&module)) {
        LOG_ERROR("Failed to load module into VM");
        return cse::CSError::ERR_CSB_LOAD_FAILED;
    }

    LOG_INFO("Executing entry point %u...", (unsigned)module.header.entryPointIndex);
    g_Running = true;

    bool success = g_VM->execute(module.header.entryPointIndex);
    g_Running = false;

    if (success) {
        cse::VMValue& ret = g_VM->getReturnValue();
        if (ret.type == cse::ValueType::INTEGER) {
            LOG_INFO("Script completed with result: %lld", (long long)ret.value.intVal);
        } else if (ret.type == cse::ValueType::DOUBLE) {
            LOG_INFO("Script completed with result: %f", ret.value.doubleVal);
        } else {
            LOG_INFO("Script completed successfully");
        }
        return cse::CSError::SUCCESS;
    } else {
        LOG_ERROR("Script execution failed: %s", g_VM->getLastError().c_str());
        return cse::CSError::ERR_VM_NATIVE_CALL_FAILED;
    }
}

void runSafeState() {
    if (g_GPIO) {
        for (uint32_t pin = 0; pin < 32; pin++) {
            g_GPIO->setMode(pin, cse::GPIOMode::INPUT);
        }
    }
    led_rgb_set(0, 0, 0);
    LOG_WARN("System in safe state");
}

}

int main(void) {
    k210_delay_ms(INIT_DELAY_MS);

    sysctl_pll_set_freq(SYSCTL_PLL0, PLL0_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL1, PLL1_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL2, PLL2_FREQ);
    sysctl_set_spi0_dvp_data(1);

    plic_init();
    sysctl_enable_irq();

    uarths_init();
    uarths_config(UART_BAUDRATE, UARTHS_STOP_1);

    printf("\r\n");
    printf("========================================\r\n");
    printf("IronCS K210 VM v4.0\r\n");
    printf("Build: %s %s\r\n", __DATE__, __TIME__);
    printf("========================================\r\n");
    printf("\r\n");

    spi_init(SPI_DEVICE_3, SPI_WORK_MODE_0, SPI_FF_STANDARD, 8, 0);
    k210_spi3_init();

    printf("[SYS] PLL0: %u Hz\r\n", (unsigned)sysctl_pll_get_freq(SYSCTL_PLL0));
    printf("[SYS] PLL1: %u Hz\r\n", (unsigned)sysctl_pll_get_freq(SYSCTL_PLL1));
    printf("[SYS] PLL2: %u Hz\r\n", (unsigned)sysctl_pll_get_freq(SYSCTL_PLL2));

    cse::CSError err = initializeHardware();
    if (cse::isError(err)) {
        printf("[FATAL] Hardware init failed: %s\r\n", cse::getErrorString(err));
        while (1) {
            k210_delay_ms(1000);
        }
        return 1;
    }

    LOG_INFO("LED pins configured by script");
    err = initializeVM();
    if (cse::isError(err)) {
        LOG_FATAL("VM init failed: %s", cse::getErrorString(err));
        runSafeState();
        while (1) {
            k210_delay_ms(1000);
        }
        return 1;
    }

    LOG_INFO("Loading script from flash 0x%X...", CSB_STORAGE_ADDR);

    err = loadAndExecuteCSB(CSB_STORAGE_ADDR);
    if (cse::isError(err)) {
        LOG_ERROR("Script execution failed: %s", cse::getErrorString(err));
        runSafeState();
    }

    LOG_INFO("Entering main loop...");
    while (1) {
        g_Watchdog.feed();
        k210_delay_ms(MAIN_LOOP_DELAY_MS);
        g_UptimeMs += MAIN_LOOP_DELAY_MS;
        cse::Logger::setUptimeMs(g_UptimeMs);
    }

    return 0;
}
