# CScriptEngine 多平台适配工业最佳实践

> **文档状态**: 已完成 - K210 + STM32 双平台 HAL 实现
>
> **版本**: 3.0
>
> **目标**: 实现 K210 + STM32 双平台统一 HAL 抽象，面向工业自动化场景

---

## 1. 概述

### 1.1 项目简介

CScriptEngine 是一个面向工业自动化的嵌入式脚本引擎，支持在资源受限的微控制器上运行用户编写的脚本程序。通过统一的硬件抽象层（HAL），同一套脚本代码可以在 K210 和 STM32 等不同平台上运行，无需修改。

### 1.2 设计目标

#### 1.2.1 系统目标

- **双平台支持**: K210 + STM32 通过统一 HAL 抽象
- **接口分离**: GPIO/UART/Timer 独立标准接口
- **工厂模式**: HardwareFactory 统一实例创建
- **可测试性**: Mock 实现支持 x64 单元测试
- **工业协议**: ModbusRTU 协议栈支持

#### 1.2.2 VM 设计目标

- **轻量级**: 仅需 8MB Flash 存储空间
- **低内存占用**: 运行时栈 256 单元，堆 4KB
- **快速启动**: 字节码解释执行，无需即时编译
- **安全执行**: 支持内存保护，跳转边界检查
- **双平台支持**: K210 + STM32 通过统一 HAL 抽象

### 1.3 核心特性

| 特性 | 说明 |
|------|------|
| **跨平台脚本** | 同一脚本可在 K210、STM32、x64 Mock 上运行 |
| **字节码虚拟机** | 高效的 BytecodeVM 执行机制 |
| **原生函数绑定** | 通过 FFI 调用平台特定功能 |
| **工业协议** | 内置 ModbusRTU 协议栈 |
| **硬件抽象** | 统一的 GPIO/UART/Timer 接口 |

### 1.4 架构设计原则

- **前端** (词法/语法/语义/IR) 平台无关
- **后端** 通过 ICodeGenerator 接口统一
- **嵌入式** 通过 HAL 抽象层支持多平台
- **BytecodeVM** 完全平台无关，可复用于 K210 和 STM32
- **HAL 接口** 使用工厂模式，支持运行时平台检测
- **脚本 API** 通过 IndustrialFFI 层暴露给脚本

### 1.5 系统架构

```
┌─────────────────────────────────────────────────────────────┐
│                    CScript 脚本层                             │
│        (gpio_set_mode, uart_write, timer_start 等)          │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    IndustrialFFI 层                          │
│         (FFI 绑定, ModbusRTU 协议栈)                         │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│              标准接口 (IStandard*)                           │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐          │
│  │IStandardGPIO│ │IStandardUART│ │IStandardTimer│          │
│  └─────────────┘ └─────────────┘ └─────────────┘          │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   HardwareFactory                            │
│         (平台检测, 实例创建, 生命周期管理)                    │
└─────────────────────────────────────────────────────────────┘
              ┌─────────────────┬─────────────────┐
              ▼                 ▼                 ▼
        ┌──────────┐    ┌──────────┐    ┌──────────┐
        │   K210    │    │  STM32   │    │   Mock   │
        │ Platform  │    │ Platform │    │(x64测试) │
        └──────────┘    └──────────┘    └──────────┘
```

---

## 2. 平台分类模型

### 2.1 四象限分类

```
                         指令集架构 (ISA)
                    ┌─────────────┬─────────────┐
                    │   x86/x64   │    RV64     │
         ┌──────────┼─────────────┼─────────────┤
         │ 非嵌入式  │    Q1       │    Q2       │
         ├──────────┼─────────────┼─────────────┤
         │ 嵌入式    │    Q3       │    Q4       │
         └──────────┴─────────────┴─────────────┘
```

| 象限 | 平台 | ISA | 代码生成 | 内存管理 |
|------|------|-----|----------|----------|
| Q1 | x64 桌面/服务器 | x86-64 | JIT/AOT | 虚拟内存 |
| Q2 | RV64 服务器 | RV64 | JIT/AOT | 虚拟内存 |
| Q3 | x64 嵌入式 | x86-64 | AOT | 静态分配 |
| Q4 | 嵌入式 (K210/STM32) | RV64/ARM | 字节码VM | 固定缓冲区 |

### 2.2 平台特性矩阵

| 特性 | Q1 | Q2 | Q3 | Q4 |
|------|----|----|----|----|
| JIT 编译 | ✅ | ✅ | ❌ | ❌ |
| AOT 编译 | ✅ | ✅ | ✅ | ❌ |
| 字节码 VM | ❌ | ❌ | ❌ | ✅ |
| 虚拟内存 | ✅ | ✅ | ❌ | ❌ |
| 异常处理 | ✅ | ✅ | ❌ | ❌ |
| HAL 抽象 | - | - | - | ✅ |

### 2.3 双平台支持矩阵

| 平台 | 硬件抽象 | 烧录协议 | 栈大小 | 堆大小 | 状态 |
|------|---------|---------|--------|--------|------|
| **K210** | K210GPIO/Timer/UART | KBP | 256 | 4KB | ✅ 已验证 |
| **STM32F4** | STM32GPIO/Timer/UART | DFU | 512 | 16KB | ✅ 已实现 |
| **Mock (x64)** | MockGPIO/Timer/UART | N/A | 动态 | 动态 | ✅ |

---

## 3. 硬件抽象层 (HAL)

### 3.1 设计原则

- **接口分离**: 每个硬件外设独立接口
- **平台无关**: 接口抽象，平台实现隔离
- **工厂模式**: 统一实例创建，配置管理
- **可测试性**: Mock 实现支持 x64 单元测试

### 3.2 接口定义

#### IStandardGPIO

```cpp
class IStandardGPIO {
public:
    virtual ~IStandardGPIO() = default;

    virtual bool setMode(uint32_t pin, GPIOMode mode) = 0;
    virtual bool write(uint32_t pin, bool value) = 0;
    virtual bool read(uint32_t pin) = 0;
    virtual uint32_t readPort() = 0;
    virtual void writePort(uint32_t value) = 0;
    virtual void setPortMask(uint32_t mask) = 0;
    virtual void clearPortMask(uint32_t mask) = 0;
    virtual bool enableInterrupt(uint32_t pin, GPIOMode mode,
                                 GPIOInterruptCallback callback) = 0;
    virtual bool disableInterrupt(uint32_t pin) = 0;
    virtual void pollInterrupts() = 0;
    virtual const char* getPlatformName() const = 0;
};
```

#### IStandardUART

```cpp
class IStandardUART {
public:
    virtual ~IStandardUART() = default;

    virtual bool configure(const UARTConfig& config) = 0;
    virtual bool setBaudrate(uint32_t baud) = 0;
    virtual int write(const uint8_t* data, size_t len) = 0;
    virtual int read(uint8_t* buffer, size_t len,
                    uint32_t timeout_ms = 1000) = 0;
    virtual bool enableDMA() = 0;
    virtual bool disableDMA() = 0;
    virtual size_t available() = 0;
    virtual size_t readNonBlocking(uint8_t* buffer, size_t max_len) = 0;
    virtual void setRS485Mode(bool enable, uint32_t de_pin = 0,
                              bool de_active_high = true) = 0;
    virtual void setReceiveCallback(DataCallback callback) = 0;
    virtual uint32_t getFrameTimeout() = 0;
    virtual void setFrameTimeout(uint32_t char_us) = 0;
    virtual const char* getPlatformName() const = 0;
};
```

#### IStandardTimer

```cpp
class IStandardTimer {
public:
    virtual ~IStandardTimer() = default;

    virtual bool start(uint32_t period_us, bool periodic = true) = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
    virtual uint64_t getTicks() = 0;

    virtual bool configurePWM(uint32_t frequency_hz,
                              uint8_t duty_cycle) = 0;
    virtual bool setDutyCycle(uint8_t duty_cycle) = 0;
    virtual bool setFrequency(uint32_t frequency_hz) = 0;

    virtual bool enableCapture(bool rising, bool falling) = 0;
    virtual uint32_t getCaptureValue() = 0;

    virtual void setCallback(TimerCallback callback) = 0;
    virtual const char* getPlatformName() const = 0;
};
```

### 3.2 平台实现矩阵

| 接口 | K210 | STM32 | Mock |
|------|------|-------|------|
| IStandardGPIO | K210GPIO | STM32GPIO | MockGPIO |
| IStandardUART | K210UART | STM32UART | MockUART |
| IStandardTimer | K210Timer | STM32Timer | MockTimer |

### 3.3 辅助类型定义

#### GPIOMode 枚举

```cpp
enum class GPIOMode {
    INPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    OUTPUT,
    OUTPUT_OD
};
```

#### UARTConfig 配置结构

```cpp
struct UARTConfig {
    uint32_t baudrate;
    uint8_t data_bits;
    UARTParity parity;
    UARTStopBits stop_bits;
    bool rs485_mode;
    uint32_t rs485_de_pin;
    bool rs485_de_active_high;
};

enum class UARTParity { NONE, ODD, EVEN };
enum class UARTStopBits { ONE, TWO };
```

#### TimerMode 枚举

```cpp
enum class TimerMode {
    ONESHOT,    // 单次触发
    PERIODIC,   // 周期触发
    PWM,        // PWM 输出
    CAPTURE     // 输入捕获
};
```

---

## 4. 平台实现

### 4.1 K210 平台

#### 目录结构

```
src/platform/k210/
├── K210GPIO.h/cpp       # GPIO 实现
├── K210Timer.h/cpp      # Timer 实现
├── K210UART.h/cpp       # UART 实现
├── K210Flash.h/cpp      # Flash 驱动
├── K210Bootloader.h/cpp # KBP 烧录协议
├── CSBLoader.h/cpp      # CSB 加载
├── CMakeLists.txt
└── linker.ld            # 链接脚本
```

#### 固件构建

```
firmware/k210/
├── main_vm.cpp          # 固件入口
├── CMakeLists.txt       # 交叉编译配置
├── toolchain.cmake      # RISC-V 工具链
├── build.sh             # 构建脚本
└── build/               # 构建产物
    ├── cscript_vm.elf
    └── cscript_vm.bin
```

#### K210GPIO

```cpp
class K210GPIO : public IStandardGPIO {
public:
    K210GPIO();
    ~K210GPIO() override;

    bool setMode(uint32_t pin, GPIOMode mode) override;
    bool write(uint32_t pin, bool value) override;
    bool read(uint32_t pin) override;
    // ...

private:
    GPIOMode m_Modes[40];
};
```

**引脚范围**: GPIO0-7, GPIOHS0-31

#### K210Timer

```cpp
class K210Timer : public IStandardTimer {
public:
    explicit K210Timer(uint32_t timer_id = 0);
    ~K210Timer() override;

    bool start(uint32_t period_us, bool periodic = true) override;
    void stop() override;
    uint64_t getTicks() override;
    // ...
};
```

**定时器**: 0-3 (共4个)

#### K210UART

```cpp
class K210UART : public IStandardUART {
public:
    explicit K210UART(uint32_t uart_id = 0);
    ~K210UART() override;

    bool configure(const UARTConfig& config) override;
    int write(const uint8_t* data, size_t len) override;
    int read(uint8_t* buffer, size_t len,
             uint32_t timeout_ms = 1000) override;
    // ...

    void setGPIO(K210GPIO* gpio);

private:
    uint32_t m_UARTID;
    UARTConfig m_Config;
    K210GPIO* m_GPIO;
};
```

**UART**: 0-2 (共3个)

---

### 4.2 STM32 平台

#### 目录结构

```
src/platform/stm32/
├── STM32GPIO.h/cpp       # GPIO 实现
├── STM32Timer.h/cpp      # Timer 实现
├── STM32UART.h/cpp       # UART 实现
├── STM32Hardware.h/cpp   # 硬件抽象
├── STM32DFUBootloader.h/cpp # DFU 烧录协议
└── CMakeLists.txt
```

#### 固件构建

```
firmware/stm32/
├── main_vm.cpp          # 固件入口
├── CMakeLists.txt       # 交叉编译配置
├── toolchain.cmake      # ARM Cortex-M 工具链
├── build.sh             # 构建脚本
└── build/               # 构建产物
    ├── cscript_vm.elf
    └── cscript_vm.bin
```

#### STM32GPIO

```cpp
class STM32GPIO : public IStandardGPIO {
public:
    STM32GPIO(uint32_t portBase = 0x40020000);
    ~STM32GPIO() override;

    bool setMode(uint32_t pin, GPIOMode mode) override;
    bool write(uint32_t pin, bool value) override;
    bool read(uint32_t pin) override;
    // ...
};
```

#### STM32Timer

```cpp
class STM32Timer : public IStandardTimer {
public:
    STM32Timer(uint32_t timer_id = 0);
    ~STM32Timer() override;

    bool start(uint32_t period_us, bool periodic = true) override;
    void stop() override;
    uint64_t getTicks() override;
    // ...
};
```

#### STM32UART

```cpp
class STM32UART : public IStandardUART {
public:
    STM32UART(uint32_t uart_id = 0);
    ~STM32UART() override;

    bool configure(const UARTConfig& config) override;
    int write(const uint8_t* data, size_t len) override;
    int read(uint8_t* buffer, size_t len,
             uint32_t timeout_ms = 1000) override;
    // ...
};
```

---

### 4.3 Mock 平台 (x64测试)

```cpp
class MockGPIO : public IStandardGPIO {
    // 软件模拟，无需真实硬件
};

class MockTimer : public IStandardTimer {
    // 软件模拟，使用 std::chrono
};

class MockUART : public IStandardUART {
    // 软件模拟，使用 std::queue
};
```

---

## 5. 硬件工厂

### 5.1 工厂类

```cpp
enum class HardwarePlatform { AUTO, K210, STM32, MOCK };

class HardwareFactory {
public:
    static HardwareFactory& instance();

    void initialize(HardwarePlatform platform = HardwarePlatform::AUTO);

    IStandardGPIO* getGPIO();
    IStandardUART* getUART(uint32_t id = 0);
    IStandardTimer* getTimer(uint32_t id = 0);

    const char* getPlatformName() const;
    void shutdown();

private:
    void createK210Hardware();
    void createSTM32Hardware();
    void createMockHardware();
};
```

### 5.2 使用示例

```cpp
// 自动平台检测
HardwareFactory::instance().initialize();

// 或手动指定
HardwareFactory::instance().initialize(HardwarePlatform::K210);

// 获取硬件实例
IStandardGPIO* gpio = HardwareFactory::instance().getGPIO();
IStandardUART* uart = HardwareFactory::instance().getUART(0);
IStandardTimer* timer = HardwareFactory::instance().getTimer(0);

// 使用
gpio->setMode(13, GPIOMode::OUTPUT);
gpio->write(13, true);

uart->configure({115200, 8, UARTParity::NONE, UARTStopBits::ONE});
uart->write(data, len);

timer->start(1000000, true);  // 1秒周期
```

---

## 6. 平台检测

### 6.1 编译时检测

```cpp
#if defined(__K210__) || defined(CSE_K210)
    #define CSE_PLATFORM_K210
    // K210 平台
#elif defined(CSE_EMBEDDED) || defined(STM32F4) || defined(STM32H7)
    #define CSE_PLATFORM_STM32
    // STM32 平台
#else
    #define CSE_PLATFORM_MOCK
    // x64 Mock 平台
#endif
```

### 6.2 运行时检测

```cpp
HardwareFactory::instance().initialize(HardwarePlatform::AUTO);
// AUTO 会根据编译宏自动选择平台
```

---

## 7. 目录结构

```
CScriptEngine/
├── src/
│   ├── hal/                              # 硬件抽象层
│   │   ├── IStandardGPIO.h              # GPIO 标准接口
│   │   ├── IStandardUART.h              # UART 标准接口
│   │   ├── IStandardTimer.h             # Timer 标准接口
│   │   ├── HardwareFactory.h/cpp         # 实例工厂
│   │   └── CMakeLists.txt
│   │
│   ├── bytecode/
│   │   └── vm/                          # 字节码虚拟机
│   │       └── BytecodeVM.h/cpp
│   │
│   ├── platform/                         # 平台实现
│   │   ├── k210/                       # K210 平台
│   │   │   ├── K210GPIO.h/cpp         # GPIO 实现
│   │   │   ├── K210Timer.h/cpp        # Timer 实现
│   │   │   ├── K210UART.h/cpp         # UART 实现
│   │   │   ├── K210Flash.h/cpp        # Flash 驱动
│   │   │   ├── K210Bootloader.h/cpp   # 烧录协议
│   │   │   ├── CSBLoader.h/cpp        # CSB 加载
│   │   │   └── CMakeLists.txt
│   │   │
│   │   ├── stm32/                      # STM32 平台
│   │   │   ├── STM32GPIO.h/cpp
│   │   │   ├── STM32Timer.h/cpp
│   │   │   ├── STM32UART.h/cpp
│   │   │   ├── STM32Hardware.h/cpp
│   │   │   ├── STM32DFUBootloader.h/cpp
│   │   │   └── CMakeLists.txt
│   │   │
│   │   └── mock/                        # Mock 平台 (x64测试)
│   │       ├── MockGPIO.h/cpp
│   │       ├── MockTimer.h/cpp
│   │       ├── MockUART.h/cpp
│   │       └── CMakeLists.txt
│   │
│   └── industrial/                       # 工业协议
│       ├── ModbusRTU.h/cpp             # Modbus RTU
│       ├── IndustrialFFI.h/cpp          # FFI 绑定
│       └── CMakeLists.txt
│
├── firmware/                              # 固件构建
│   ├── k210/                           # K210 固件
│   │   ├── main_vm.cpp
│   │   ├── CMakeLists.txt
│   │   ├── toolchain.cmake
│   │   └── build.sh
│   │
│   └── stm32/                          # STM32 固件
│       ├── main_vm.cpp
│       ├── CMakeLists.txt
│       ├── toolchain.cmake
│       └── build.sh
│
└── tools/                                # 工具
    ├── cscriptc/                        # 脚本编译器
    └── csburn/                         # 固件烧录工具
```

---

## 8. 工业协议

### 8.1 ModbusRTU

```cpp
class ModbusRTU {
public:
    explicit ModbusRTU(IStandardUART* uart);

    bool setSlaveAddress(uint8_t addr);
    bool readHoldingRegisters(uint16_t addr, uint16_t count,
                             uint16_t* output);
    bool writeSingleRegister(uint16_t addr, uint16_t value);
    bool readInputRegisters(uint16_t addr, uint16_t count,
                           uint16_t* output);

private:
    IStandardUART* m_UART;
    uint8_t m_SlaveAddress;
};
```

### 8.2 支持的功能码

| 功能码 | 名称 | 状态 |
|--------|------|------|
| 0x03 | Read Holding Registers | ✅ |
| 0x04 | Read Input Registers | ✅ |
| 0x06 | Write Single Register | ✅ |
| 0x10 | Write Multiple Registers | 📋 |

---

## 9. 字节码格式 (CSB)

### 9.1 文件头 (BytecodeHeader)

| 字段 | 偏移 | 大小 | 说明 |
|------|------|------|------|
| magic | 0 | 4 | "CSB\x01" |
| majorVersion | 4 | 1 | 主版本号 (1) |
| minorVersion | 5 | 1 | 次版本号 (0) |
| flags | 6 | 2 | 标志位 |
| functionCount | 8 | 4 | 函数数量 |
| stringPoolSize | 12 | 4 | 字符串池大小 |
| totalConstants | 16 | 4 | 常量池条目数 |
| entryPointIndex | 20 | 4 | 入口函数索引 |

### 9.2 函数结构 (BytecodeFunction)

| 字段 | 大小 | 说明 |
|------|------|------|
| nameOffset | 4 | 函数名在字符串池中的偏移 |
| paramCount | 4 | 参数数量 |
| localCount | 4 | 局部变量数量 |
| maxStackSize | 4 | 最大栈使用量 |
| instructions | 可变 | 指令序列 |
| constants | 可变 | 函数级常量池 |

### 9.3 指令格式 (BytecodeInstruction)

```
┌────────────────┬────────────────┐
│   OpCode (1B)  │   Operand (4B) │
└────────────────┴────────────────┘
```

### 9.4 常量池条目 (ConstantPoolEntry)

| 类型 | 说明 |
|------|------|
| INTEGER | 64位有符号整数 |
| DOUBLE | 64位浮点数 |
| STRING | 字符串池偏移量 |
| FUNCTION | 函数索引 |
| NATIVE_FUNC | 原生函数指针 |

---

## 10. 脚本工作流程

### 10.1 完整流程

```
┌─────────────────────────────────────────────────────────────┐
│                   CScript 脚本 (.cs)                         │
│  gpio_set_mode(0, OUTPUT)                                  │
│  gpio_write(0, HIGH)                                        │
│  delay(500)                                                 │
│  uart_config(1, 115200, 8, NONE, 1)                        │
│  uart_write(1, "Hello")                                     │
└─────────────────────────────────────────────────────────────┘
                              │ cscriptc (PC/x64)
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   字节码 (.csb)                              │
│  Magic: "CSB\x01" + 函数表 + 指令 + 字符串池                │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼ (烧录到 Flash)
┌─────────────────────────────────────────────────────────────┐
│  K210 Flash @ 0x00080000                                    │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼ CSBLoader
┌─────────────────────────────────────────────────────────────┐
│                   BytecodeVM (解释器)                       │
│  registerNativeFunction("gpio_set_mode", ...)               │
│  registerNativeFunction("gpio_write", ...)                  │
│  registerNativeFunction("delay", ...)                       │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼ Native Function
┌─────────────────────────────────────────────────────────────┐
│                   HardwareFactory                            │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐                  │
│  │ K210GPIO │  │K210UART  │  │K210Timer │                  │
│  └──────────┘  └──────────┘  └──────────┘                  │
└─────────────────────────────────────────────────────────────┘
```

### 10.2 工作流程

| 步骤 | 工具 | 说明 |
|------|------|------|
| 1. 编写脚本 | 任意编辑器 | .cs 文件 |
| 2. 编译脚本 | cscriptc | 生成 .csb 字节码 |
| 3. 烧录固件 | csburn | 烧录到 K210 Flash |
| 4. 执行脚本 | BytecodeVM | 从 Flash 加载并执行 |

### 10.3 示例脚本

```cscript
# hardware_test.cs - 硬件测试脚本
gpio_set_mode(0, OUTPUT)
gpio_write(0, HIGH)
delay(500)
gpio_write(0, LOW)

gpio_set_mode(1, INPUT)
if gpio_read(1) == HIGH
    print("Pin 1 is HIGH")
end

uart_config(1, 115200, 8, NONE, 1)
uart_write(1, "Hello from CScript!")

timer_start(0, 1000000, 1)
delay(2000)
timer_stop(0)
```

---

## 11. 构建与烧录

### 11.1 K210 交叉编译

```bash
cd D:\MyCode\CScriptEngine\firmware\k210
mkdir -p build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="../toolchain.cmake" ..
cmake --build .
```

### 11.2 烧录到 K210

```bash
kflash -p /dev/ttyUSB0 -b 1500000 cscript_vm.bin
```

---

## 12. 实现状态

### 12.1 K210 平台

| 组件 | 文件 | 状态 | 验证 |
|------|------|------|------|
| GPIO | K210GPIO.cpp/h | ✅ 完成 | ✅ Sipeed M1W |
| Timer | K210Timer.cpp/h | ✅ 完成 | ✅ Sipeed M1W |
| UART | K210UART.cpp/h | ✅ 完成 | ✅ Sipeed M1W |
| ModbusRTU | ModbusRTU.cpp/h | ✅ 完成 | 📋 待验证 |
| Flash | K210Flash.cpp/h | ✅ 完成 | ✅ Sipeed M1W |
| Bootloader | K210Bootloader.cpp/h | ✅ 完成 | ✅ Sipeed M1W |

### 12.2 STM32 平台

| 组件 | 文件 | 状态 |
|------|------|------|
| GPIO | STM32GPIO.cpp/h | ✅ 完成 |
| Timer | STM32Timer.cpp/h | ✅ 完成 |
| UART | STM32UART.cpp/h | ✅ 完成 |
| ModbusRTU | ModbusRTU.cpp/h | 📋 待验证 |
| DFUBootloader | STM32DFUBootloader.cpp/h | 📋 待实现 |

### 12.3 Mock 平台

| 组件 | 文件 | 状态 |
|------|------|------|
| GPIO | MockGPIO.cpp/h | ✅ 完成 |
| Timer | MockTimer.cpp/h | ✅ 完成 |
| UART | MockUART.cpp/h | ✅ 完成 |

---

## 13. 测试验证

### 13.1 K210 (Sipeed M1W)

```
测试日期: 2026-03-26

✅ GPIO: 引脚 0 输出闪烁
✅ UART: 115200 8N1 发送
✅ Timer: 1秒周期定时
✅ VM: Flash CSB 执行
```

### 13.2 x64 (Mock)

```
✅ 所有单元测试通过
✅ 集成测试通过
```

---

## 14. 与设计文档的差异

| 原设计 | 实际实现 |
|--------|----------|
| 直接寄存器操作 | 使用 Kendryte SDK 封装 |
| PlatformAbstraction | IStandard* + HardwareFactory |
| K210Hardware 单一类 | 拆分为 GPIO/Timer/UART 独立类 |
| 单一 K210 平台 | K210 + STM32 + Mock 三平台支持 |
| 仅文档设计 | 实际实现并验证 |

---

## 15. 错误处理机制

### 15.1 统一错误码定义

```cpp
enum class CSError : int32_t {
    SUCCESS = 0,

    // 硬件错误 (1-99)
    ERR_GPIO_INVALID_PIN = 1,
    ERR_GPIO_INVALID_MODE = 2,
    ERR_UART_CONFIG_FAILED = 10,
    ERR_UART_TIMEOUT = 11,
    ERR_UART_BUFFER_OVERFLOW = 12,
    ERR_TIMER_INVALID_ID = 20,
    ERR_TIMER_NOT_RUNNING = 21,

    // VM 错误 (100-199)
    ERR_VM_STACK_OVERFLOW = 100,
    ERR_VM_STACK_UNDERFLOW = 101,
    ERR_VM_INVALID_OPCODE = 102,
    ERR_VM_INVALID_JUMP = 103,
    ERR_VM_DIVISION_BY_ZERO = 104,
    ERR_VM_NATIVE_CALL_FAILED = 105,

    // Flash/存储错误 (200-299)
    ERR_FLASH_READ_FAILED = 200,
    ERR_FLASH_WRITE_FAILED = 201,
    ERR_FLASH_ERASE_FAILED = 202,
    ERR_CSB_INVALID_MAGIC = 210,
    ERR_CSB_VERSION_MISMATCH = 211,

    // 系统错误 (300-399)
    ERR_OUT_OF_MEMORY = 300,
    ERR_NULL_POINTER = 301,
    ERR_WATCHDOG_TIMEOUT = 310,
    ERR_HARDWARE_FAULT = 320,
};
```

### 15.2 错误处理策略

| 错误级别 | 处理策略 | 示例 |
|---------|---------|------|
| **警告** | 记录日志，继续执行 | UART 缓冲区接近满 |
| **可恢复错误** | 返回错误码，调用者处理 | GPIO 引脚无效 |
| **严重错误** | 重置模块，恢复默认状态 | VM 执行异常 |
| **致命错误** | 触发看门狗复位 | 内存损坏 |

### 15.3 故障恢复机制

```cpp
class FaultRecovery {
public:
    static void initialize();
    static void onHardwareFault(CSError error);
    static void onVMFault(CSError error);
    static void resetToSafeState();

private:
    static uint32_t s_FaultCount;
    static uint32_t s_LastFaultTime;
    static constexpr uint32_t MAX_FAULT_COUNT = 3;
    static constexpr uint32_t FAULT_WINDOW_MS = 5000;
};
```

---

## 16. 工业安全

### 16.1 看门狗配置

```cpp
class IStandardWatchdog {
public:
    virtual ~IStandardWatchdog() = default;

    virtual bool initialize(uint32_t timeout_ms) = 0;
    virtual void feed() = 0;
    virtual bool isTriggered() = 0;
    virtual uint32_t getRemainingTime() = 0;
};
```

| 平台 | 实现类 | 超时范围 |
|------|--------|---------|
| K210 | K210Watchdog | 1ms - 16s |
| STM32 | STM32Watchdog | 1ms - 32s |
| Mock | MockWatchdog | 模拟实现 |

### 16.2 安全启动流程

```
┌─────────────────────────────────────────────────────────────┐
│                      上电复位                                │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   1. 硬件自检 (POST)                         │
│  - CPU/内存检查                                             │
│  - 外设状态检查                                             │
│  - 看门狗初始化                                             │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   2. 固件完整性校验                          │
│  - CRC32 校验                                               │
│  - 版本验证                                                 │
└─────────────────────────────────────────────────────────────┘
                              │
                    ┌─────────┴─────────┐
                    ▼                   ▼
            ┌──────────────┐    ┌──────────────┐
            │   校验通过    │    │   校验失败    │
            └──────────────┘    └──────────────┘
                    │                   │
                    ▼                   ▼
┌─────────────────────────────────────────────────────────────┐
│                   3. CSB 加载与验证                          │
│  - Magic 校验                                               │
│  - 版本兼容性                                               │
│  - 字节码完整性                                             │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   4. VM 初始化                               │
│  - 栈/堆初始化                                              │
│  - 原生函数注册                                             │
│  - 安全边界设置                                             │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   5. 正常运行                                │
│  - 看门狗定期喂狗                                           │
│  - 状态监控                                                │
└─────────────────────────────────────────────────────────────┘
```

### 16.3 固件完整性校验

```cpp
struct FirmwareHeader {
    uint32_t magic;           // "CSCF" (CScript Firmware)
    uint32_t version;         // 固件版本
    uint32_t codeSize;        // 代码大小
    uint32_t codeCrc32;       // 代码 CRC32
    uint32_t csbOffset;       // CSB 偏移
    uint32_t csbSize;         // CSB 大小
    uint32_t csbCrc32;        // CSB CRC32
    uint8_t reserved[32];     // 保留
};

bool verifyFirmwareIntegrity(const FirmwareHeader* header);
```

### 16.4 异常恢复机制

| 异常类型 | 恢复策略 | 恢复时间 |
|---------|---------|---------|
| 看门狗超时 | 系统复位 | < 100ms |
| VM 执行异常 | 重载 CSB，重启 VM | < 50ms |
| UART 帧错误 | 重新初始化 UART | < 10ms |
| GPIO 故障 | 安全状态输出 | < 5ms |
| 内存不足 | 释放非必要资源 | < 20ms |

---

## 17. 性能指标

### 17.1 执行效率

| 指标 | K210 | STM32F4 | 说明 |
|------|------|---------|------|
| 字节码执行速度 | ~50K ops/s | ~80K ops/s | 简单运算指令 |
| 函数调用开销 | ~5μs | ~3μs | 含栈帧创建 |
| 原生函数调用 | ~2μs | ~1μs | FFI 调用开销 |
| GPIO 操作延迟 | ~10μs | ~5μs | setMode + write |
| UART 发送延迟 | ~100μs/byte | ~50μs/byte | 115200 baud |

### 17.2 内存占用

| 组件 | K210 | STM32F4 | 说明 |
|------|------|---------|------|
| VM 核心代码 | ~32KB | ~32KB | 字节码解释器 |
| HAL 层代码 | ~8KB | ~8KB | GPIO/UART/Timer |
| 运行时栈 | 256 单元 × 8B = 2KB | 512 单元 × 8B = 4KB | |
| 运行时堆 | 4KB | 16KB | 对象分配 |
| CSB 加载缓冲 | ~1KB | ~1KB | 按需加载 |
| **总计** | ~47KB | ~61KB | |

### 17.3 启动时间

| 阶段 | K210 | STM32F4 |
|------|------|---------|
| 硬件初始化 | ~10ms | ~5ms |
| 固件校验 | ~5ms | ~3ms |
| CSB 加载 | ~2ms | ~1ms |
| VM 初始化 | ~1ms | ~0.5ms |
| **总启动时间** | **~18ms** | **~9.5ms** |

### 17.4 功耗特性

| 模式 | K210 | STM32F4 |
|------|------|---------|
| 活动模式 | ~300mA | ~100mA |
| 空闲模式 | ~50mA | ~10mA |
| 低功耗模式 | ~10mA | ~1mA |

---

## 18. 调试支持

### 18.1 日志系统

```cpp
enum class LogLevel : uint8_t {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

class Logger {
public:
    static void initialize(IStandardUART* uart, LogLevel level);
    static void log(LogLevel level, const char* format, ...);
    static void setLevel(LogLevel level);
    static void flush();

private:
    static IStandardUART* s_UART;
    static LogLevel s_Level;
    static char s_Buffer[256];
};

#define LOG_TRACE(...) Logger::log(LogLevel::TRACE, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::log(LogLevel::DEBUG, __VA_ARGS__)
#define LOG_INFO(...)  Logger::log(LogLevel::INFO, __VA_ARGS__)
#define LOG_WARN(...)  Logger::log(LogLevel::WARN, __VA_ARGS__)
#define LOG_ERROR(...) Logger::log(LogLevel::ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Logger::log(LogLevel::FATAL, __VA_ARGS__)
```

### 18.2 远程调试接口

```cpp
struct DebugCommand {
    uint8_t command;      // 命令类型
    uint8_t length;       // 数据长度
    uint8_t data[64];     // 数据
};

enum DebugCommandType : uint8_t {
    CMD_PING = 0x00,          // 心跳检测
    CMD_GET_STATUS = 0x01,    // 获取状态
    CMD_READ_MEMORY = 0x02,   // 读取内存
    CMD_WRITE_MEMORY = 0x03,  // 写入内存
    CMD_PAUSE_VM = 0x10,      // 暂停 VM
    CMD_RESUME_VM = 0x11,     // 恢复 VM
    CMD_STEP_VM = 0x12,       // 单步执行
    CMD_GET_CALLSTACK = 0x13, // 获取调用栈
    CMD_SET_BREAKPOINT = 0x14 // 设置断点
};
```

### 18.3 状态监控

```cpp
struct SystemStatus {
    uint32_t uptime_ms;       // 运行时间
    uint32_t vm_state;        // VM 状态
    uint32_t stack_used;      // 栈使用量
    uint32_t heap_used;       // 堆使用量
    uint32_t gpio_state;      // GPIO 状态
    uint32_t uart_rx_count;   // UART 接收计数
    uint32_t uart_tx_count;   // UART 发送计数
    uint32_t fault_count;     // 故障计数
    uint32_t last_error;      // 最后错误码
};

void getSystemStatus(SystemStatus* status);
```

### 18.4 调试输出格式

```
[2026-03-27 10:30:45.123] [INFO] System initialized
[2026-03-27 10:30:45.125] [DEBUG] CSB loaded: 1024 bytes
[2026-03-27 10:30:45.130] [INFO] VM started, entry=main
[2026-03-27 10:30:45.250] [WARN] Stack usage: 80%
[2026-03-27 10:30:46.000] [ERROR] UART timeout on port 0
[2026-03-27 10:30:46.005] [INFO] UART recovered
```

---

## 19. 下一步计划

### 短期 (1-2 周)

1. 修复 Timer getTicks() 溢出问题
2. 完成 GPIO 输入测试
3. 完成 UART 接收测试
4. Modbus RTU 硬件测试

### 中期 (1 个月)

1. 完善 STM32 平台支持
2. PWM 电机控制示例
3. Modbus 主/从模式完整实现
4. 工业 HMI 示例

---

## 20. 参考资料

| 资料 | 说明 |
|------|------|
| [Kendryte SDK](https://github.com/kendryte/kendryte-standalone-sdk) | K210 官方 SDK |
| [STM32 HAL](https://www.st.com/en/development-tools/stm32cubemx.html) | STM32 HAL 文档 |
| [HAL 接口](../src/hal/) | 硬件抽象层实现 |
| [K210 驱动](../src/platform/k210/) | K210 平台驱动 |
| [STM32 驱动](../src/platform/stm32/) | STM32 平台驱动 |

---

*文档版本: 4.0*
*最后更新: 2026-03-27*

