# 嵌入式平台抽象层重构设计文档

> **文档状态**: 新增
>
> **创建日期**: 2026-03-25
>
> **目标**: 将 K210 嵌入式实现重构为通用的嵌入式平台抽象层，支持 K210 和 STM32

## 1. 背景与目标

### 1.1 当前问题

当前 K210 嵌入式实现存在以下问题：

| 问题 | 说明 |
|------|------|
| **平台耦合** | K210VM 直接依赖 K210 特定的 HAL 和寄存器定义 |
| **难以移植** | STM32 等其他嵌入式平台需要完全重写 |
| **职责不清** | VM 核心逻辑与硬件操作混杂 |
| **烧录协议独占** | KBP 协议与 K210 硬件绑定 |

### 1.2 重构目标

```
┌─────────────────────────────────────────────────────────────────┐
│                     重构前 (K210 独占)                             │
│  ┌─────────┐     ┌─────────┐     ┌─────────┐                    │
│  │ Bytecode│────▶│ K210VM  │────▶│K210HAL  │                    │
│  │Compiler │     │         │     │(硬件耦合) │                    │
│  └─────────┘     └─────────┘     └─────────┘                    │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│                     重构后 (平台抽象)                             │
│  ┌─────────┐     ┌─────────┐     ┌─────────────┐                │
│  │ Bytecode│────▶│ Bytecode│────▶│IHAL抽象层   │                │
│  │Compiler │     │   VM    │     │──────┬──────│                │
│  └─────────┘     └─────────┘     │ K210 │ STM32│                │
│                                   └──────┴──────┘                │
└─────────────────────────────────────────────────────────────────┘
```

## 2. 架构设计

### 2.1 整体架构

```
┌─────────────────────────────────────────────────────────────────┐
│                     PC 端编译工具链                               │
│  ┌──────────────────┐    ┌──────────────────────────────────┐ │
│  │ CScriptEngine    │───▶│ BytecodeCompiler                 │ │
│  │ (前端+IR生成)    │    │ (Quad → 平台无关字节码 CSB)       │ │
│  └──────────────────┘    └──────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
                         CSB 文件 (平台无关)
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────┐
│                     嵌入式设备端                                 │
├─────────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    IBootloader (烧录协议)                 │   │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐  │   │
│  │  │ KBP         │  │ DFU         │  │ CustomProtocol  │  │   │
│  │  │ (K210)      │  │ (STM32)     │  │ (可扩展)        │  │   │
│  │  └─────────────┘  └─────────────┘  └─────────────────┘  │   │
│  └─────────────────────────────────────────────────────────┘   │
│                               │                                 │
│                               ▼                                 │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    IFlash (存储抽象)                      │   │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐  │   │
│  │  │ K210 SPI    │  │ STM32 Flash │  │ External Flash  │  │   │
│  │  │ Flash       │  │ (内置)      │  │ (可扩展)        │  │   │
│  │  └─────────────┘  └─────────────┘  └─────────────────┘  │   │
│  └─────────────────────────────────────────────────────────┘   │
│                               │                                 │
│                               ▼                                 │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    ICommunication (通信)                 │   │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐  │   │
│  │  │ UART        │  │ USB CDC     │  │ SWD             │  │   │
│  │  │ (通用)      │  │ (STM32)     │  │ (调试)          │  │   │
│  │  └─────────────┘  └─────────────┘  └─────────────────┘  │   │
│  └─────────────────────────────────────────────────────────┘   │
│                               │                                 │
│                               ▼                                 │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    BytecodeVM (平台无关核心)              │   │
│  │  - 解释器核心                                              │   │
│  │  - 栈管理                                                  │   │
│  │  - 调用帧                                                  │   │
│  │  - 原生函数注册                                            │   │
│  └─────────────────────────────────────────────────────────┘   │
│                               │                                 │
│                               ▼                                 │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    IHardwareAbstraction (硬件抽象)        │   │
│  │  ┌─────────────┐  ┌─────────────┐                        │   │
│  │  │ K210 Impl   │  │ STM32 Impl  │                        │   │
│  │  └─────────────┘  └─────────────┘                        │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

### 2.2 核心接口设计

#### 2.2.1 硬件抽象接口 (IHardwareAbstraction)

```cpp
#ifndef CSE_HARDWARE_ABSTRACTION_H
#define CSE_HARDWARE_ABSTRACTION_H

#include <cstdint>
#include <cstddef>
#include <functional>

namespace cse {

class IHardwareAbstraction {
public:
    virtual ~IHardwareAbstraction() = default;

    // 系统控制
    virtual void delay(uint32_t ms) = 0;
    virtual uint64_t getTicks() = 0;
    virtual void reset() = 0;
    virtual void jumpTo(uint32_t address) = 0;

    // 内存操作
    virtual bool readFlash(uint32_t addr, uint8_t* buffer, size_t len) = 0;
    virtual bool writeFlash(uint32_t addr, const uint8_t* data, size_t len) = 0;
    virtual bool eraseFlash(uint32_t addr, size_t len) = 0;

    // 通信接口
    virtual int uartWrite(const uint8_t* data, size_t len) = 0;
    virtual int uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) = 0;
    virtual int uartAvailable() = 0;

    // 平台信息
    virtual uint32_t getFlashSize() = 0;
    virtual uint32_t getSRAMSize() = 0;
    virtual const char* getPlatformName() = 0;
};

}
#endif
```

#### 2.2.2 烧录协议接口 (IBootloader)

```cpp
#ifndef CSE_BOOTLOADER_H
#define CSE_BOOTLOADER_H

#include <cstdint>
#include <cstddef>
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
```

#### 2.2.3 字节码虚拟机 (BytecodeVM)

```cpp
#ifndef CSE_BYTE_CODE_VM_H
#define CSE_BYTE_CODE_VM_H

#include "bytecode/BytecodeFormat.h"
#include <cstdint>
#include <string>
#include <vector>

namespace cse {

constexpr size_t DEFAULT_VM_STACK_SIZE = 256;
constexpr size_t DEFAULT_VM_HEAP_SIZE = 4096;
constexpr size_t DEFAULT_VM_MAX_CALL_DEPTH = 32;

struct VMConfig {
    size_t stackSize = DEFAULT_VM_STACK_SIZE;
    size_t heapSize = DEFAULT_VM_HEAP_SIZE;
    size_t maxCallDepth = DEFAULT_VM_MAX_CALL_DEPTH;
};

class BytecodeVM {
public:
    explicit BytecodeVM(const VMConfig& config = VMConfig{});
    ~BytecodeVM();

    bool loadModule(const BytecodeModule* module);
    bool execute(uint32_t entryPoint = 0);
    void stop();

    using NativeFunction = std::function<void(BytecodeVM*)>;
    void registerNativeFunction(const std::string& name, NativeFunction func);

    VMValue& getReturnValue() { return m_ReturnValue; }
    const std::string& getLastError() const { return m_LastError; }
    bool isRunning() const { return m_Running; }

    size_t getStackUsed() const { return m_StackTop - m_Stack; }
    size_t getHeapUsed() const { return m_HeapUsed; }

private:
    void reset();
    bool push(const VMValue& val);
    VMValue pop();
    VMValue& peek();

    bool executeInstruction(OpCode op, uint32_t operand);
    OpCode fetch();
    bool callFunction(uint32_t funcIndex, uint32_t argCount);
    bool returnFromFunction();

    VMValue& getLocal(uint32_t slot);
    VMValue& getGlobal(uint32_t slot);
    VMValue& getConstant(uint32_t index);

    const BytecodeModule* m_Module;
    VMValue* m_Stack;
    VMValue* m_Locals;
    VMValue* m_StackTop;
    VMValue* m_Heap;
    size_t m_HeapUsed;

    VMFrame* m_Frames;
    uint32_t m_FrameCount;
    uint32_t m_PC;

    VMValue m_ReturnValue;
    std::string m_LastError;
    bool m_Running;

    std::vector<NativeFunction> m_NativeFunctions;
};

}
#endif
```

#### 2.2.4 嵌入式运行时 (IEmbeddedRuntime)

```cpp
#ifndef CSE_EMBEDDED_RUNTIME_H
#define CSE_EMBEDDED_RUNTIME_H

#include "BytecodeVM.h"
#include "IHardwareAbstraction.h"
#include "IBootloader.h"

namespace cse {

class IEmbeddedRuntime {
public:
    virtual ~IEmbeddedRuntime() = default;

    virtual bool initialize(IHardwareAbstraction* hal) = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    virtual BytecodeVM* getVM() = 0;
    virtual IHardwareAbstraction* getHAL() = 0;
};

class EmbeddedRuntimeFactory {
public:
    enum class Platform {
        K210,
        STM32,
    };

    static std::unique_ptr<IEmbeddedRuntime> create(Platform platform);
};

}
#endif
```

### 2.3 平台实现

#### 2.3.1 K210 硬件抽象实现

```cpp
#ifndef CSE_K210_HARDWARE_H
#define CSE_K210_HARDWARE_H

#include "IHardwareAbstraction.h"

namespace cse {

class K210Hardware : public IHardwareAbstraction {
public:
    K210Hardware();

    void delay(uint32_t ms) override;
    uint64_t getTicks() override;
    void reset() override;
    void jumpTo(uint32_t address) override;

    bool readFlash(uint32_t addr, uint8_t* buffer, size_t len) override;
    bool writeFlash(uint32_t addr, const uint8_t* data, size_t len) override;
    bool eraseFlash(uint32_t addr, size_t len) override;

    int uartWrite(const uint8_t* data, size_t len) override;
    int uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) override;
    int uartAvailable() override;

    uint32_t getFlashSize() override { return 8 * 1024 * 1024; }
    uint32_t getSRAMSize() override { return 8 * 1024 * 1024; }
    const char* getPlatformName() override { return "K210"; }

private:
    static constexpr uint32_t UART0_BASE = 0x38000000;
    static constexpr uint32_t SPI3_BASE = 0x53100000;
    static constexpr uint32_t FLASH_BASE = 0x00000000;
    static constexpr uint32_t FLASH_SIZE = 8 * 1024 * 1024;
};

}
#endif
```

#### 2.3.2 STM32 硬件抽象实现

```cpp
#ifndef CSE_STM32_HARDWARE_H
#define CSE_STM32_HARDWARE_H

#include "IHardwareAbstraction.h"

namespace cse {

class STM32Hardware : public IHardwareAbstraction {
public:
    STM32Hardware();

    void delay(uint32_t ms) override;
    uint64_t getTicks() override;
    void reset() override;
    void jumpTo(uint32_t address) override;

    bool readFlash(uint32_t addr, uint8_t* buffer, size_t len) override;
    bool writeFlash(uint32_t addr, const uint8_t* data, size_t len) override;
    bool eraseFlash(uint32_t addr, size_t len) override;

    int uartWrite(const uint8_t* data, size_t len) override;
    int uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) override;
    int uartAvailable() override;

    uint32_t getFlashSize() override;
    uint32_t getSRAMSize() override;
    const char* getPlatformName() override { return "STM32"; }

private:
    enum class Model {
        F1,  // STM32F1
        F4,  // STM32F4
        H7,  // STM32H7
        L4,  // STM32L4
    };

    Model m_Model;
    uint32_t m_FlashBase;
    uint32_t m_SramBase;
};

}
#endif
```

#### 2.3.3 K210 烧录协议实现

```cpp
#ifndef CSE_K210_BOOTLOADER_H
#define CSE_K210_BOOTLOADER_H

#include "IBootloader.h"
#include "K210Hardware.h"

namespace cse {

class K210Bootloader : public IBootloader {
public:
    explicit K210Bootloader(K210Hardware* hal);

    void initialize() override;
    void process() override;

    bool flash(uint32_t address, const uint8_t* data, size_t len,
               ProgressCallback callback) override;
    bool verify(uint32_t address, const uint8_t* data, size_t len) override;
    bool boot(uint32_t entryPoint) override;

    BootloaderStatus getLastStatus() const override { return m_LastStatus; }
    const char* getLastError() const override { return m_ErrorMsg.c_str(); }

private:
    bool sendPacket(const uint8_t* data, size_t len);
    bool receivePacket(uint8_t* buffer, size_t* outLen, uint32_t timeout_ms);
    uint8_t calcCRC8(const uint8_t* data, size_t len);

    K210Hardware* m_HAL;
    BootloaderStatus m_LastStatus;
    std::string m_ErrorMsg;

    static constexpr uint32_t SYNC_MAGIC = 0xFFAA55AA;
    static constexpr uint32_t CSB_STORE_ADDR = 0x00080000;
    static constexpr size_t MAX_PKT_SIZE = 256;
};

}
#endif
```

#### 2.3.4 STM32 DFU 烧录协议实现

```cpp
#ifndef CSE_STM32_DFU_BOOTLOADER_H
#define CSE_STM32_DFU_BOOTLOADER_H

#include "IBootloader.h"
#include "STM32Hardware.h"

namespace cse {

class STM32DFUBootloader : public IBootloader {
public:
    explicit STM32DFUBootloader(STM32Hardware* hal);

    void initialize() override;
    void process() override;

    bool flash(uint32_t address, const uint8_t* data, size_t len,
               ProgressCallback callback) override;
    bool verify(uint32_t address, const uint8_t* data, size_t len) override;
    bool boot(uint32_t entryPoint) override;

    BootloaderStatus getLastStatus() const override { return m_LastStatus; }
    const char* getLastError() const override { return m_ErrorMsg.c_str(); }

private:
    bool enterDFU();
    bool erase(uint32_t addr, size_t len);
    bool write(uint32_t addr, const uint8_t* data, size_t len);
    bool readprotect();
    bool jumpToApp(uint32_t addr);

    STM32Hardware* m_HAL;
    BootloaderStatus m_LastStatus;
    std::string m_ErrorMsg;
};

}
#endif
```

## 3. 文件结构

### 3.1 重构后的目录结构

```
src/
├── vm/
│   ├── BytecodeVM.h           # 平台无关字节码虚拟机
│   ├── BytecodeVM.cpp
│   └── CMakeLists.txt
├── hal/                        # 硬件抽象层 (新增)
│   ├── IHardwareAbstraction.h # 抽象接口
│   ├── K210Hardware.h         # K210 实现
│   ├── K210Hardware.cpp
│   ├── STM32Hardware.h        # STM32 实现
│   ├── STM32Hardware.cpp
│   ├── EmbeddedRuntime.h      # 嵌入式运行时
│   ├── EmbeddedRuntime.cpp
│   └── CMakeLists.txt
├── bootloader/                 # 烧录协议 (重构)
│   ├── IBootloader.h          # 抽象接口
│   ├── K210Bootloader.h       # K210 KBP 协议
│   ├── K210Bootloader.cpp
│   ├── STM32DFUBootloader.h   # STM32 DFU 协议
│   ├── STM32DFUBootloader.cpp
│   └── CMakeLists.txt
├── bytecode/
│   ├── BytecodeFormat.h       # 保持不变
│   ├── BytecodeCompiler.h
│   └── BytecodeCompiler.cpp
├── platform/                   # 平台特定代码 (重构)
│   ├── k210/
│   │   ├── K210Main.cpp       # 入口点
│   │   └── CMakeLists.txt
│   └── stm32/
│       ├── STM32Main.cpp       # 新增
│       ├── STM32Startup.cpp    # 新增
│       └── CMakeLists.txt
└── common/
    └── VMConfig.h              # 公共配置
```

### 3.2 条件编译

```cpp
// VMConfig.h
#pragma once

#include <cstddef>

#if defined(CSE_K210)
    constexpr size_t DEFAULT_STACK_SIZE = 256;
    constexpr size_t DEFAULT_HEAP_SIZE = 4096;
    constexpr uint32_t FLASH_LAYOUT = 0x00080000;
#elif defined(CSE_STM32)
    constexpr size_t DEFAULT_STACK_SIZE = 512;
    constexpr size_t DEFAULT_HEAP_SIZE = 16384;
    constexpr uint32_t FLASH_LAYOUT = 0x08000000;
#else
    constexpr size_t DEFAULT_STACK_SIZE = 1024;
    constexpr size_t DEFAULT_HEAP_SIZE = 65536;
#endif

constexpr size_t DEFAULT_MAX_CALL_DEPTH = 32;
```

## 4. 移植指南

### 4.1 移植到新平台 (以 STM32 为例)

#### 步骤 1: 实现 IHardwareAbstraction

```cpp
// STM32Hardware.cpp
#include "STM32Hardware.h"

namespace cse {

STM32Hardware::STM32Hardware() {
    // 检测 STM32 型号
    uint32_t id = *(volatile uint32_t*)0xE0042000;
    if ((id & 0xFFF) == 0x413) {
        m_Model = Model::F4;
        m_FlashBase = 0x08000000;
        m_SramBase = 0x20000000;
    }
}

void STM32Hardware::delay(uint32_t ms) {
    HAL_Delay(ms);
}

uint64_t STM32Hardware::getTicks() {
    return HAL_GetTick();
}

void STM32Hardware::reset() {
    NVIC_SystemReset();
}

void STM32Hardware::jumpTo(uint32_t address) {
    // 设置栈指针和 PC
    typedef void (*ResetHandler)(void);
    volatile uint32_t* vectorTable = (volatile uint32_t*)address;
    SCB->VTOR = address;
    __set_MSP(vectorTable[0]);
    ResetHandler resetHandler = (ResetHandler)vectorTable[1];
    resetHandler();
}

bool STM32Hardware::readFlash(uint32_t addr, uint8_t* buffer, size_t len) {
    // 内部 Flash 读取
    memcpy(buffer, (void*)addr, len);
    return true;
}

bool STM32Hardware::writeFlash(uint32_t addr, const uint8_t* data, size_t len) {
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR);

    for (size_t i = 0; i < len; i += 4) {
        uint32_t word = data[i] | (data[i+1] << 8) | (data[i+2] << 16) | (data[i+3] << 24);
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i, word) != HAL_OK) {
            HAL_FLASH_Lock();
            return false;
        }
    }
    HAL_FLASH_Lock();
    return true;
}

bool STM32Hardware::eraseFlash(uint32_t addr, size_t len) {
    FLASH_EraseInitTypeDef erase;
    erase.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase.Sector = (addr - m_FlashBase) / 2048;  // F4 2KB sectors
    erase.NbSectors = len / 2048;
    erase.Banks = FLASH_BANK_1;

    uint32_t sectorError;
    return HAL_FLASHEx_Erase(&erase, &sectorError) == HAL_OK;
}

int STM32Hardware::uartWrite(const uint8_t* data, size_t len) {
    return HAL_UART_Transmit(&huart1, (uint8_t*)data, len, HAL_MAX_DELAY);
}

int STM32Hardware::uartRead(uint8_t* data, size_t len, uint32_t timeout_ms) {
    return HAL_UART_Receive(&huart1, data, len, timeout_ms);
}

int STM32Hardware::uartAvailable() {
    return __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) ? 1 : 0;
}

uint32_t STM32Hardware::getFlashSize() {
    return *(uint16_t*)0x1FFF7A22;  // F4
}

uint32_t STM32Hardware::getSRAMSize() {
    return *(uint16_t*)0x1FFF7A22 + 0x20000000;  // F4
}

}
```

#### 步骤 2: 实现 IBootloader

```cpp
// STM32DFUBootloader.cpp
#include "STM32DFUBootloader.h"

namespace cse {

STM32DFUBootloader::STM32DFUBootloader(STM32Hardware* hal)
    : m_HAL(hal), m_LastStatus(BootloaderStatus::OK) {}

void STM32DFUBootloader::initialize() {
    m_HAL->uartWrite((const uint8_t*)"CSCRIPT DFU\r\n", 14);
}

bool STM32DFUBootloader::flash(uint32_t addr, const uint8_t* data, size_t len,
                               ProgressCallback callback) {
    // 擦除
    if (!erase(addr, len)) {
        m_ErrorMsg = "Erase failed";
        return false;
    }

    // 写入
    if (!write(addr, data, len)) {
        m_ErrorMsg = "Write failed";
        return false;
    }

    // 验证
    if (!verify(addr, data, len)) {
        m_ErrorMsg = "Verify failed";
        return false;
    }

    return true;
}

bool STM32DFUBootloader::verify(uint32_t addr, const uint8_t* data, size_t len) {
    std::vector<uint8_t> readBuffer(len);
    m_HAL->readFlash(addr, readBuffer.data(), len);
    return memcmp(data, readBuffer.data(), len) == 0;
}

bool STM32DFUBootloader::boot(uint32_t entryPoint) {
    m_HAL->delay(100);
    m_HAL->jumpTo(entryPoint);
    return true;
}

}
```

#### 步骤 3: 创建运行时

```cpp
// STM32Runtime.cpp
#include "EmbeddedRuntime.h"
#include "STM32Hardware.h"
#include "STM32DFUBootloader.h"
#include "BytecodeVM.h"

namespace cse {

class STM32Runtime : public IEmbeddedRuntime {
public:
    bool initialize(IHardwareAbstraction* hal) override {
        m_HAL = hal;
        m_VM = std::make_unique<BytecodeVM>();
        m_Bootloader = std::make_unique<STM32DFUBootloader>(static_cast<STM32Hardware*>(hal));
        m_Bootloader->initialize();
        return true;
    }

    void run() override {
        // 尝试加载 Flash 中的字节码
        // 如果有有效的字节码，执行它
    }

    BytecodeVM* getVM() override { return m_VM.get(); }
    IHardwareAbstraction* getHAL() override { return m_HAL; }

private:
    IHardwareAbstraction* m_HAL;
    std::unique_ptr<BytecodeVM> m_VM;
    std::unique_ptr<IBootloader> m_Bootloader;
};

}
```

## 5. 配置矩阵

### 5.1 平台配置对比

| 配置项 | K210 | STM32F4 | STM32H7 |
|--------|------|---------|---------|
| 栈大小 | 256 | 512 | 512 |
| 堆大小 | 4KB | 16KB | 32KB |
| 最大调用深度 | 32 | 32 | 32 |
| Flash 地址 | 0x00000000 | 0x08000000 | 0x08000000 |
| CSB 存储地址 | 0x00080000 | 0x08020000 | 0x08020000 |
| 通信接口 | UART0 | UART1 | UART1 |
| 烧录协议 | KBP | DFU | DFU |
| 擦除粒度 | 4KB | 2KB | 128KB |

### 5.2 编译开关

```cmake
# CMakeLists.txt
if(K210)
    add_definitions(-DCSE_K210)
    add_subdirectory(vm)
    add_subdirectory(hal)
    add_subdirectory(bootloader)
    add_subdirectory(platform/k210)
elseif(STM32)
    add_definitions(-DCSE_STM32)
    # STM32CubeMX 集成
    include_directories(${STM32_CUBE_IDE_PATH})
    add_subdirectory(vm)
    add_subdirectory(hal)
    add_subdirectory(bootloader)
    add_subdirectory(platform/stm32)
endif()
```

## 6. 迁移策略

### 6.1 阶段一：接口抽象 (1-2 周)

1. 定义 `IHardwareAbstraction` 接口
2. 定义 `IBootloader` 接口
3. 将 `K210VM` 重构为 `BytecodeVM`
4. 保持 K210 实现不变

### 6.2 阶段二：STM32 移植 (2-3 周)

1. 实现 `STM32Hardware`
2. 实现 `STM32DFUBootloader`
3. 创建 `STM32Runtime`
4. 在开发板上验证

### 6.3 阶段三：代码清理 (1 周)

1. 删除旧的 K210 紧耦合代码
2. 更新构建系统
3. 更新文档

## 7. 风险与缓解

| 风险 | 影响 | 缓解措施 |
|------|------|----------|
| 抽象层性能开销 | 低 | 接口内联，核心逻辑不变 |
| STM32 Flash 驱动复杂度 | 中 | 使用 HAL 库 |
| 内存配置不当 | 高 | 提供平台特定默认配置 |
| 调试困难 | 中 | 保留 SWD 调试接口 |

## 8. 参考资料

- [K210 Bytecode VM 设计文档](k210_bytecode_vm_design.md)
- [K210 HAL 实现](../src/platform/k210/K210HAL.h)
- [K210 Bootloader 实现](../src/platform/k210/K210Bootloader.h)
- [STM32 HAL 库文档](https://www.st.com/stm32hal)
- [ARM Cortex-M 编程指南](https://developer.arm.com/documentation/)
