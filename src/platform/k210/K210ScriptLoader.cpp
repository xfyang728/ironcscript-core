#include "K210ScriptLoader.h"
#include "K210Flash.h"
#include "CSBLoader.h"
#include "K210GPIO.h"
#include "K210UART.h"
#include "K210Timer.h"
#include "hal/HardwareFactory.h"
#include <cstdio>

namespace cse {

static K210ScriptLoader* g_Instance = nullptr;

K210ScriptLoader& K210ScriptLoader::instance() {
    if (!g_Instance) {
        static K210ScriptLoader inst;
        g_Instance = &inst;
    }
    return *g_Instance;
}

bool K210ScriptLoader::initialize() {
    if (m_Initialized) return true;

    m_VM = new BytecodeVM(VMConfig{
        .stackSize = 512,
        .heapSize = 4096,
        .maxCallDepth = 16
    });

    if (!m_VM) {
        printf("[ScriptLoader] Failed to create VM\r\n");
        return false;
    }

    registerPrintFunction();
    registerGPIOFunctions();
    registerUARTFunctions();
    registerTimerFunctions();
    registerSystemFunctions();

    HardwareFactory::instance().initialize(HardwarePlatform::K210);

    m_Initialized = true;
    printf("[ScriptLoader] Initialized successfully\r\n");
    return true;
}

bool K210ScriptLoader::loadScriptFromFlash(uint32_t addr) {
    if (!m_Initialized) {
        printf("[ScriptLoader] Not initialized\r\n");
        return false;
    }

    if (!CSBLoader::loadFromFlash(addr, m_Module)) {
        printf("[ScriptLoader] Failed to load script from flash\r\n");
        return false;
    }

    if (!m_VM->loadModule(&m_Module)) {
        printf("[ScriptLoader] Failed to load module into VM\r\n");
        return false;
    }

    printf("[ScriptLoader] Script loaded successfully\r\n");
    return true;
}

bool K210ScriptLoader::execute() {
    if (!m_VM) {
        printf("[ScriptLoader] VM not created\r\n");
        return false;
    }

    printf("[ScriptLoader] Starting execution...\r\n");
    bool result = m_VM->execute(0);

    if (!result) {
        printf("[ScriptLoader] Execution failed: %s\r\n", m_VM->getLastError().c_str());
    } else {
        printf("[ScriptLoader] Execution completed\r\n");
    }

    return result;
}

void K210ScriptLoader::stop() {
    if (m_VM) {
        m_VM->stop();
    }
}

void K210ScriptLoader::registerPrintFunction() {
    m_VM->registerNativeFunction("print", [](BytecodeVM* vm) {
        VMValue val = vm->getReturnValue();
        if (val.type == ValueType::INTEGER) {
            printf("%lld", (long long)val.value.intVal);
        } else if (val.type == ValueType::DOUBLE) {
            printf("%f", val.value.doubleVal);
        } else if (val.type == ValueType::STRING) {
            printf("%s", "string");
        }
    });
    printf("[ScriptLoader] Registered: print\r\n");
}

void K210ScriptLoader::registerGPIOFunctions() {
    IStandardGPIO* gpio = HardwareFactory::instance().getGPIO();

    m_VM->registerNativeFunction("gpio_set_mode", [gpio](BytecodeVM* vm) {
        VMValue pin = vm->peek();
        VMValue mode = vm->peek();
        bool result = gpio->setMode(pin.value.intVal, static_cast<GPIOMode>(mode.value.intVal));
        vm->getReturnValue() = VMValue::makeBool(result);
    });

    m_VM->registerNativeFunction("gpio_write", [gpio](BytecodeVM* vm) {
        VMValue pin = vm->peek();
        VMValue value = vm->peek();
        bool result = gpio->write(pin.value.intVal, value.value.intVal != 0);
        vm->getReturnValue() = VMValue::makeBool(result);
    });

    m_VM->registerNativeFunction("gpio_read", [gpio](BytecodeVM* vm) {
        VMValue pin = vm->peek();
        bool result = gpio->read(pin.value.intVal);
        vm->getReturnValue() = VMValue::makeBool(result);
    });

    printf("[ScriptLoader] Registered: gpio_set_mode, gpio_write, gpio_read\r\n");
}

void K210ScriptLoader::registerUARTFunctions() {
    IStandardUART* uart = HardwareFactory::instance().getUART(1);

    m_VM->registerNativeFunction("uart_config", [uart](BytecodeVM* vm) {
        UARTConfig config;
        config.baudrate = vm->peek().value.intVal;
        config.data_bits = 8;
        config.parity = UARTParity::NONE;
        config.stop_bits = UARTStopBits::ONE;
        bool result = uart->configure(config);
        vm->getReturnValue() = VMValue::makeBool(result);
    });

    m_VM->registerNativeFunction("uart_write", [uart](BytecodeVM* vm) {
        const char* data = "Hello";
        int len = vm->peek().value.intVal;
        int written = uart->write(reinterpret_cast<const uint8_t*>(data), len);
        vm->getReturnValue() = VMValue::makeInt(written);
    });

    printf("[ScriptLoader] Registered: uart_config, uart_write\r\n");
}

void K210ScriptLoader::registerTimerFunctions() {
    IStandardTimer* timer = HardwareFactory::instance().getTimer(0);

    m_VM->registerNativeFunction("timer_start", [timer](BytecodeVM* vm) {
        VMValue period = vm->peek();
        VMValue periodic = vm->peek();
        bool result = timer->start(period.value.intVal, periodic.value.intVal != 0);
        vm->getReturnValue() = VMValue::makeBool(result);
    });

    m_VM->registerNativeFunction("timer_stop", [timer](BytecodeVM* vm) {
        timer->stop();
        vm->getReturnValue() = VMValue::makeBool(true);
    });

    m_VM->registerNativeFunction("timer_get_ticks", [timer](BytecodeVM* vm) {
        uint64_t ticks = timer->getTicks();
        vm->getReturnValue() = VMValue::makeInt(static_cast<int64_t>(ticks));
    });

    printf("[ScriptLoader] Registered: timer_start, timer_stop, timer_get_ticks\r\n");
}

void K210ScriptLoader::registerSystemFunctions() {
    m_VM->registerNativeFunction("delay", [](BytecodeVM* vm) {
        VMValue ms = vm->peek();
        uint32_t delay_ms = static_cast<uint32_t>(ms.value.intVal);
        for (volatile uint32_t i = 0; i < delay_ms * 1000; i++) {
            __asm__ volatile ("nop");
        }
        vm->getReturnValue() = VMValue::makeNil();
    });

    m_VM->registerNativeFunction("millis", []() -> uint32_t {
        return 0;
    });

    printf("[ScriptLoader] Registered: delay, millis\r\n");
}

}