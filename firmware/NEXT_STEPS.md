# Firmware 下一步开发方向

> **文档日期**: 2026-04-03
> **基于**: architecture/ 目录下的三个核心架构文档
> **目标**: 指明 ironcscript-core/firmware 的下一步开发方向

---

## 一、现状分析

### 1.1 当前固件结构

```
firmware/
├── k210/
│   ├── main_vm.cpp          # K210 VM 入口
│   ├── CMakeLists.txt
│   └── build.sh
├── stm32/
│   ├── main_vm.cpp          # STM32 VM 入口
│   ├── CMakeLists.txt
│   └── build.sh
├── DebugInterface.h
└── FirmwareHeader.h
```

### 1.2 架构文档映射关系

| 架构文档 | 对应固件实现 |
|---------|-------------|
| **cscript_hardware_api_design.md** | K210GPIO, K210UART, K210Timer |
| **embedded_platform_refactor_design.md** | BytecodeVM, BytecodeFormat |
| **ir_cross_platform_design.md** | BytecodeCompiler (PC端) |

---

## 二、架构差距分析

根据 `ARCHITECTURE_EVALUATION.md` 评估，当前固件存在以下架构差距：

### P0 问题 (必须修复)

| 问题 | 当前实现 | 影响 |
|------|---------|------|
| **裸指针管理** | `static cse::IStandardGPIO* g_GPIO` | 内存安全问题 |
| **缺乏错误传播** | `bool` 返回值无统一处理 | 错误难以追踪 |
| **资源所有权不明确** | 全局静态变量 | 生命周期混乱 |

### P1 问题 (强烈建议)

| 问题 | 当前实现 | 建议 |
|------|---------|------|
| **回调缺乏取消机制** | 直接函数指针 | 添加 CancellationToken |
| **配置缺乏验证** | 硬编码常量 | 添加验证逻辑 |
| **Watchdog 空实现** | `K210Watchdog::feed()` 空 | 需要完整实现 |

---

## 三、下一步开发方向

### 3.1 短期目标 (1-2周)

#### 3.1.1 完成 Watchdog 完整实现

当前 `K210Watchdog` 的 `feed()` 和 `isTriggered()` 是空实现，需要：

```cpp
// 需要实现的 K210 Watchdog
class K210Watchdog : public cse::IStandardWatchdog {
public:
    bool initialize(uint32_t timeout_ms) override;
    void feed() override;                          // 喂狗
    bool isTriggered() override;                     // 检查是否超时
    uint32_t getRemainingTime() override;
    // ...
};
```

#### 3.1.2 添加 IStandardSystem 实现

当前缺失 `IStandardSystem` 接口实现：

```cpp
// 需要实现
class K210System : public cse::IStandardSystem {
public:
    void delay(uint32_t ms) override;
    uint32_t millis() override;
    void reboot() override;
    // ...
};
```

#### 3.1.3 参数验证增强

```cpp
// main_vm.cpp 中的错误处理改进
bool led_init() {
    if (!g_GPIO) {
        log_error("GPIO not initialized");
        return false;  // 使用 std::expected
    }
    // ...
}
```

---

### 3.2 中期目标 (1个月)

#### 3.2.1 重构为智能指针管理

```cpp
// ❌ 当前设计
static cse::IStandardGPIO* g_GPIO = nullptr;

// ✅ 现代设计
class VMContext : public std::enable_shared_from_this<VMContext> {
public:
    std::unique_ptr<cse::IStandardGPIO> gpio;
    std::unique_ptr<cse::IStandardUART> uart;
    std::unique_ptr<cse::BytecodeVM> vm;

    static std::shared_ptr<VMContext> create() {
        auto ctx = std::make_shared<VMContext>();
        ctx->gpio = HardwareFactory::createGPIO(Platform::K210);
        // ...
        return ctx;
    }
};
```

#### 3.2.2 添加错误处理抽象

```cpp
// 使用 std::expected 替代 bool 返回
#include <expected>

std::expected<void, cse::APIError> led_init() {
    if (!m_GPIO) {
        return std::unexpected(cse::APIError::HARDWARE_ERROR);
    }
    // ...
}

// 调用处
if (auto result = led_init(); !result) {
    log_error("LED init failed: {}", magic_enum::enum_name(result.error()));
}
```

#### 3.2.3 实现 STM32 固件

当前 STM32 固件 `main_vm.cpp` 存在但可能不完整，需要：

1. 实现 `STM32GPIO` 平台适配
2. 实现 `STM32UART` 平台适配
3. 实现 `STM32Timer` 平台适配
4. 验证与 K210 的 API 一致性

---

### 3.3 长期目标 (2-3个月)

#### 3.3.1 抽象接口完善

根据 `embedded_platform_refactor_design.md`，需要实现完整的接口继承体系：

```cpp
// 层次结构
IEmbeddedRuntime
    ├── K210Runtime
    └── STM32Runtime

// BytecodeVM 需要支持注入
class BytecodeVM {
public:
    void setHAL(std::shared_ptr<IHardwareAbstraction> hal) {
        m_HAL = std::move(hal);
    }

private:
    std::shared_ptr<IHardwareAbstraction> m_HAL;
};
```

#### 3.3.2 Bootloader 重构

当前 `K210Bootloader` 需要重构为符合 `IBootloader` 接口：

```cpp
// 目标接口
class IBootloader {
public:
    virtual ~IBootloader() = default;
    virtual void initialize() = 0;
    virtual bool flash(uint32_t address, const uint8_t* data, size_t len,
                       ProgressCallback callback) = 0;
    virtual bool boot(uint32_t entryPoint) = 0;
};

// 当前需要适配
class K210Bootloader : public IBootloader {
    // 实现 KBP 协议
};
```

#### 3.3.3 多平台统一构建

```bash
# CMake 平台抽象
if(K210)
    add_platform_sources(k210)
elseif(STM32)
    add_platform_sources(stm32)
endif()

# 统一固件大小目标
- K210: ≤ 2MB Flash
- STM32F4: ≤ 512KB Flash
```

---

## 四、具体任务清单

### 任务 1: Watchdog 完整实现

| 项目 | 内容 |
|------|------|
| **优先级** | P0 |
| **工作量** | 0.5 人天 |
| **文件** | `firmware/k210/main_vm.cpp` |
| **验收标准** | 5秒无喂狗后自动重启 |

### 任务 2: IStandardSystem 实现

| 项目 | 内容 |
|------|------|
| **优先级** | P0 |
| **工作量** | 1 人天 |
| **文件** | `platform/k210/K210System.h/cpp` |
| **验收标准** | `millis()`, `delay()`, `reboot()` 正常工作 |

### 任务 3: 错误处理抽象

| 项目 | 内容 |
|------|------|
| **优先级** | P1 |
| **工作量** | 2 人天 |
| **文件** | `hal/CSError.h` |
| **验收标准** | 所有 HAL 函数返回 `std::expected` |

### 任务 4: 智能指针迁移

| 项目 | 内容 |
|------|------|
| **优先级** | P1 |
| **工作量** | 3 人天 |
| **文件** | `firmware/k210/main_vm.cpp` |
| **验收标准** | 无裸 `new`/`delete`，全局变量改为成员变量 |

### 任务 5: STM32 固件验证

| 项目 | 内容 |
|------|------|
| **优先级** | P2 |
| **工作量** | 5 人天 |
| **文件** | `firmware/stm32/` |
| **验收标准** | 固件能在 STM32F103 上运行 Hello World |

### 任务 6: Bootloader 接口化

| 项目 | 内容 |
|------|------|
| **优先级** | P2 |
| **工作量** | 5 人天 |
| **文件** | `platform/k210/K210Bootloader.*` |
| **验收标准** | 实现 `IBootloader` 接口，支持 ProgressCallback |

---

## 五、技术债务

### 5.1 代码质量问题

| 问题 | 位置 | 修复方式 |
|------|------|---------|
| 硬编码魔数 | `LED_G_PIN = cse::K210Pin::GPIO5` | 移至配置结构体 |
| 1000 行单文件 | `main_vm.cpp` | 拆分为多个文件 |
| 重复日志代码 | 多处 `printf("[ERROR]...")` | 统一使用 Logger |

### 5.2 测试覆盖

| 模块 | 当前测试 | 建议测试 |
|------|---------|---------|
| GPIO | 手动测试 | 单元测试 + Mock |
| UART | 手动测试 | 环形缓冲区测试 |
| Timer | 无 | 计时准确性测试 |
| VM | 集成测试 | 边界条件测试 |

---

## 六、推荐开发顺序

```
Week 1: Watchdog + IStandardSystem
         ↓
Week 2: 代码拆分 (main_vm.cpp → 多文件)
         ↓
Week 3: 错误处理抽象 + 参数验证
         ↓
Week 4: 智能指针迁移 + 单元测试
         ↓
Week 5-6: STM32 固件验证
         ↓
Week 7-8: Bootloader 接口化
```

---

## 七、总结

| 阶段 | 目标 | 产出 |
|------|------|------|
| **短期** | 完成缺失接口实现 | 可工作的 K210 固件 |
| **中期** | 架构现代化 | 符合 C++17 最佳实践 |
| **长期** | 多平台支持 | K210 + STM32 双平台 |

**核心建议**: 优先完成 Watchdog 和 System 接口实现，确保固件基本可用后再进行架构重构。
