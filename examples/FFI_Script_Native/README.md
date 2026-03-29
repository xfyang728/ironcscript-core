# CScriptEngine FFI 示例

## 概述

本目录展示了 CScriptEngine 的 FFI（外部函数接口）功能：

| 功能 | 描述 | 状态 |
|------|------|------|
| **Script→Native** | 脚本调用 C/C++ 函数（`extern` 声明） | ✅ 已实现 |
| **Native→Script** | C/C++ 调用脚本函数（`register callback`） | ✅ 已实现 |
| **AOT 缓存** | 编译缓存加速启动 | ✅ 已实现 |

## 快速开始

### 构建项目

```bash
cmake --build build
```

### 运行 FFI 示例

```bash
cd build
./FFI_Script_Native.exe
```

## Script→Native 调用

### 语法

```c
extern return_type function_name(arg1_type, arg2_type, ...);

int main() {
    double result = add_double(1.5, 2.5);
    return (int)result;
}
```

### 示例代码 (main.cpp)

```cpp
#include <CScriptEngine.h>

extern "C" {

double add_double(double a, double b) {
    return a + b;
}

int add_int(int a, int b) {
    return a + b;
}

}

int main() {
    cse::CScriptEngine engine;

    // 注册 Native 函数
    engine.registerNativeFunction("add_double", add_double);
    engine.registerNativeFunction("add_int", add_int);

    std::string script = R"(
        extern double add_double(double a, double b);
        extern int add_int(int a, int b);

        void main() {
            double d = add_double(1.5, 2.5);
            int i = add_int(10, 20);
        }
    )";

    engine.execute(script);
}
```

## Native→Script 回调

### 语法

```c
int myCallback(int x) {
    return x + 100;
}

void main() {
    register myCallback as onData;
}
```

### 示例代码

```cpp
// C++ 端注册回调
engine.execute(script);

if (engine.hasRegisteredCallback("onData")) {
    void* callback = engine.getRegisteredCallback("onData");

    // 转换为函数指针并调用
    using CallbackType = int(*)(int);
    CallbackType cb = reinterpret_cast<CallbackType>(callback);
    int result = cb(999);
}
```

## AOT 编译缓存

AOT 编译缓存可以加速频繁执行的脚本启动速度。缓存默认**禁用**。

### 缓存控制 API

```cpp
// 启用缓存（默认禁用）
engine.setCacheEnabled(true);

// 强制重新编译
engine.setForceRecompile(true);

// 清除缓存
engine.clearCache("script.c");
```

### 工作流程

```
首次运行: 脚本 → JIT编译 → 保存到 script.csec.x64
后续运行: script.csec.x64 → 直接加载执行
```

### 跨平台支持

```
script.csec.x64      ← x64 平台缓存
script.csec.riscv64  ← RISC-V 平台缓存
```

## 架构说明

### 关键组件

| 组件 | 文件 | 职责 |
|------|------|------|
| FFIRegistry | src/backend/FFIRegistry.h | Native 函数注册表 |
| ScriptFunctionRegistry | src/backend/ScriptFunctionRegistry.h | 脚本函数注册表 |
| CompiledCache | src/backend/CompiledCache.h | AOT 缓存管理 |
| X64Code | src/backend/x64/X64Code.cpp | x64 机器码生成 |

### Windows x64 调用约定

| 参数位置 | 整数/指针 | 浮点数 |
|---------|----------|--------|
| 第1个参数 | RCX | XMM0 |
| 第2个参数 | RDX | XMM1 |
| 第3个参数 | R8 | XMM2 |
| 第4个参数 | R9 | XMM3 |
| 返回值 | RAX | XMM0 |

## 测试

```bash
cd build
./CScriptEngineTests.exe
```

运行 FFI 相关测试：

```bash
./CScriptEngineTests.exe --gtest_filter=*FFI*
```
