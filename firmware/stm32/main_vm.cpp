#include "stm32f10x.h"
#include "hardware/OLED.h"
#include "hardware/Serial.h"
#include "platform/stm32/STM32CSBLoader.h"
#include "bytecode/vm/BytecodeVM.h"
#include "bytecode/BytecodeFormat.h"
#include <new>

extern void SystemInit(void);

extern "C" {
    #define HEAP_SIZE 8192
    static uint8_t s_Heap[HEAP_SIZE] __attribute__((used));
    static uint8_t* s_HeapCur = s_Heap;
    static uint32_t s_HeapUsed = 0;

    void* malloc(size_t size) {
        if (size == 0) return nullptr;
        size = (size + 3) & ~3;
        if (s_HeapUsed + size > HEAP_SIZE) {
            Serial_SendString("[MALLOC] FAIL\r\n");
            return nullptr;
        }
        void* ptr = s_HeapCur;
        s_HeapUsed += size;
        s_HeapCur += size;
        Serial_SendString("[MALLOC] OK ptr=");
        Serial_SendNumber((uint32_t)(uintptr_t)ptr, 16);
        Serial_SendString("\r\n");
        return ptr;
    }

    void free(void* ptr) {
    }
}

void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) {
}

void operator delete[](void* ptr) {
}

#define VM_STACK_SIZE 64
#define VM_HEAP_SIZE 128
#define VM_MAX_CALL_DEPTH 8

namespace {
    cse::BytecodeVM* g_VM = nullptr;
    uint32_t g_UptimeMs = 0;
}

void Delay_ms(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 7200; j++);
    }
}

extern "C" void __aeabi_assert(const char* expr, const char* file, int line) {
    (void)expr; (void)file; (void)line;
    Serial_SendString("ASSERT FAIL\r\n");
    while (1);
}

static void nativeDelay(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    if (argCount < 1) return;
    cse::VMValue arg = vm->getArg(0);
    if (arg.type == cse::ValueType::INTEGER) {
        int32_t ms = static_cast<int32_t>(arg.value.intVal);
        Delay_ms(ms);
        g_UptimeMs += ms;
    }
}

static void nativeMillis(cse::BytecodeVM* vm) {
    vm->getReturnValue() = cse::VMValue::makeInt(g_UptimeMs);
}

static void nativeDigitalWrite(cse::BytecodeVM* vm) {
    (void)vm;
}

static void nativeDigitalRead(cse::BytecodeVM* vm) {
    (void)vm;
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

static void nativePinMode(cse::BytecodeVM* vm) {
    (void)vm;
}

static void nativeLogInfo(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    if (argCount < 1) return;
    cse::VMValue arg = vm->getArg(0);
    if (arg.type == cse::ValueType::INTEGER) {
        Serial_SendString("INFO: ");
        Serial_SendNumber(static_cast<uint32_t>(arg.value.intVal), 10);
        Serial_SendString("\r\n");
    }
}

static void nativePrintf(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    if (argCount < 1) return;
    cse::VMValue arg = vm->getArg(0);
    if (arg.type == cse::ValueType::STRING) {
        const char* str = vm->getStringFromConstant(arg.value.stringOffset);
        Serial_SendString(str);
    } else if (arg.type == cse::ValueType::INTEGER) {
        Serial_SendNumber(static_cast<uint32_t>(arg.value.intVal), 10);
    }
    (void)argCount;
}

static bool initializeVM() {
    Serial_SendString("[VM] init start\r\n");

    Serial_SendString("[VM] creating instance\r\n");

    cse::VMConfig config;
    config.stackSize = VM_STACK_SIZE;
    config.heapSize = VM_HEAP_SIZE;
    config.maxCallDepth = VM_MAX_CALL_DEPTH;

    Serial_SendString("[VM] config set\r\n");
    Serial_SendString("[VM] calling new BytecodeVM\r\n");
    void* vmPtr = operator new(sizeof(cse::BytecodeVM));
    Serial_SendString("[VM] operator new returned\r\n");
    Serial_SendString("[VM] ptr=");
    Serial_SendNumber((uint32_t)(uintptr_t)vmPtr, 16);
    Serial_SendString("\r\n");
    g_VM = new (vmPtr) cse::BytecodeVM(config);
    Serial_SendString("[VM] cast done\r\n");
    Serial_SendString("[VM] instance created\r\n");

    if (!g_VM) {
        Serial_SendString("[VM] allocation failed\r\n");
        return false;
    }

    Serial_SendString("[VM] registering functions\r\n");

    g_VM->registerNativeFunction("delay", nativeDelay);
    g_VM->registerNativeFunction("millis", nativeMillis);
    g_VM->registerNativeFunction("digitalWrite", nativeDigitalWrite);
    g_VM->registerNativeFunction("digitalRead", nativeDigitalRead);
    g_VM->registerNativeFunction("pinMode", nativePinMode);
    g_VM->registerNativeFunction("log_info", nativeLogInfo);
    g_VM->registerNativeFunction("printf", nativePrintf);

    Serial_SendString("[VM] init complete\r\n");
    return true;
}

static void executeScript() {
    Serial_SendString("[SCRIPT] loading from 0x0800E000...\r\n");

    constexpr uint32_t SCRIPT_ADDR = 0x0800E000;

    Serial_SendString("[SCRIPT] creating module...\r\n");
    cse::BytecodeModule module;
    Serial_SendString("[SCRIPT] calling loadFromFlash...\r\n");
    if (!cse::STM32CSBLoader::loadFromFlash(SCRIPT_ADDR, module)) {
        Serial_SendString("[SCRIPT] load failed\r\n");
        OLED_ShowString(3, 1, "Load Failed");
        return;
    }

    Serial_SendString("[SCRIPT] loaded, entering VM\r\n");

    if (!g_VM->loadModule(&module)) {
        Serial_SendString("[SCRIPT] VM load failed\r\n");
        OLED_ShowString(3, 1, "VM Failed");
        return;
    }

    Serial_SendString("[SCRIPT] executing...\r\n");
    OLED_ShowString(3, 1, "Running");

    bool success = g_VM->execute(module.header.entryPointIndex);

    if (success) {
        cse::VMValue& ret = g_VM->getReturnValue();
        Serial_SendString("[SCRIPT] done, ret=");
        Serial_SendNumber(ret.value.intVal, 10);
        Serial_SendString("\r\n");
        OLED_ShowString(3, 1, "Done");
    } else {
        Serial_SendString("[SCRIPT] error\r\n");
        OLED_ShowString(3, 1, "Error");
    }
}

int main(void) {
    Serial_Init();
    Serial_SendString("\r\n");
    Serial_SendString("========================\r\n");
    Serial_SendString("[MAIN] IronCS STM32\r\n");
    Serial_SendString("========================\r\n");

    Serial_SendString("[MAIN] 1. Serial init done\r\n");

    s_HeapCur = s_Heap;
    s_HeapUsed = 0;
    Serial_SendString("[MAIN] Heap init done\r\n");

    Serial_SendString("[TEST] Testing malloc...\r\n");
    void* testPtr = malloc(16);
    if (testPtr) {
        Serial_SendString("[TEST] malloc(16) OK\r\n");
        free(testPtr);
        Serial_SendString("[TEST] free() OK\r\n");
    } else {
        Serial_SendString("[TEST] malloc(16) FAILED\r\n");
    }

    SystemInit();
    Serial_SendString("[MAIN] 2. SystemInit done\r\n");

    OLED_Init();
    Serial_SendString("[MAIN] 3. OLED init done\r\n");

    OLED_ShowString(1, 1, "IronCScript");
    Serial_SendString("[MAIN] 4. OLED strings set\r\n");

    if (!initializeVM()) {
        Serial_SendString("[MAIN] VM init FAILED\r\n");
        OLED_ShowString(3, 1, "VM Failed");
        while (1) {
            Delay_ms(1000);
        }
    }

    Serial_SendString("[MAIN] 5. VM initialized\r\n");
    OLED_ShowString(3, 1, "VM OK");

    executeScript();

    Serial_SendString("[MAIN] 6. Script executed\r\n");

    Serial_SendString("[MAIN] entering loop\r\n");

    int counter = 0;
    while (1) {
        counter++;
        g_UptimeMs += 1000;

        char buf[32];
        uint8_t i = 0;
        buf[i++] = 'C';
        buf[i++] = ':';
        buf[i++] = ' ';
        int temp = counter;
        if (temp == 0) {
            buf[i++] = '0';
        } else {
            char rev[12];
            uint8_t len = 0;
            while (temp > 0) {
                rev[len++] = '0' + (temp % 10);
                temp /= 10;
            }
            while (len > 0) {
                buf[i++] = rev[--len];
            }
        }
        buf[i++] = '\r';
        buf[i++] = '\n';
        Serial_SendString(buf);

        Delay_ms(1000);
    }

    return 0;
}