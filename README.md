# IronCScript

一个轻量级、高性能的 C 风格脚本语言引擎，支持 JIT 编译和嵌入式平台。

## 特性

- **C 风格语法**: 熟悉的 C 语言语法，易于学习和使用
- **JIT 编译**: 支持即时编译，提供接近原生的执行性能
- **跨平台支持**: 支持 x64 和 RISC-V 64 架构
- **嵌入式友好**: 可运行于 K210、STM32 等嵌入式平台
- **字节码虚拟机**: 提供字节码编译和解释执行模式
- **FFI 支持**: 原生函数注册和调用
- **异常处理**: 完整的 try-catch 异常处理机制
- **模块系统**: 支持模块导入和代码复用
- **脚本缓存**: 编译结果缓存，加速重复执行

## 项目结构

```
ironcscript-core/
├── src/
│   ├── frontend/          # 前端：词法分析、语法分析、语义分析
│   │   ├── parser/        # ANTLR4 语法定义
│   │   ├── generated/     # ANTLR4 生成的解析器代码
│   │   └── semantic/      # 语义分析器和符号表
│   ├── ir/                # 中间表示（四元式）
│   ├── backend/           # 后端：代码生成和执行
│   │   ├── x64/           # x64 架构代码生成
│   │   ├── rv64/          # RISC-V 64 架构代码生成
│   │   └── cache/         # 编译缓存系统
│   ├── bytecode/          # 字节码编译器和虚拟机
│   ├── platform/          # 平台抽象层
│   ├── gc/                # 垃圾回收
│   ├── exception/         # 异常处理
│   └── module/            # 模块管理
├── extern/                # 外部依赖
├── tests/                 # 测试用例
└── examples/              # 示例代码
```

## 依赖

- **CMake** >= 3.8
- **C++17** 兼容编译器 (MSVC / GCC / Clang)
- **ANTLR4** 运行时
- **Capstone** 反汇编库
- **Google Test** (用于测试)

## 构建

### Windows (MSVC)

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Windows (MinGW)

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
```

### RISC-V 64 交叉编译

```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/riscv64-toolchain.cmake -DRISCV64=ON ..
cmake --build .
```

## 快速开始

```cpp
#include "IronCScript.h"
#include <iostream>

int main() {
    cse::IronCScript engine;
    
    engine.setStandardOutputCallback([](const std::string& msg) {
        std::cout << msg;
    });
    
    const char* script = R"(
        int factorial(int n) {
            if (n <= 1) return 1;
            return n * factorial(n - 1);
        }
        
        printf("Factorial of 10: %d\n", factorial(10));
    )";
    
    if (engine.execute(script)) {
        std::cout << "Execution succeeded" << std::endl;
    } else {
        std::cerr << "Error: " << engine.getLastError() << std::endl;
    }
    
    return 0;
}
```

## 语法示例

```c
// 变量声明
int a = 10;
double b = 3.14;
string name = "IronCScript";

// 函数定义
int add(int a, int b) {
    return a + b;
}

// 控制流
if (a > 5) {
    printf("a is greater than 5\n");
} else {
    printf("a is not greater than 5\n");
}

// 循环
for (int i = 0; i < 10; i++) {
    printf("i = %d\n", i);
}

// 异常处理
try {
    throw "Something went wrong";
} catch (string msg) {
    printf("Caught: %s\n", msg);
}
```

## API 参考

### IronCScript 类

| 方法 | 描述 |
|------|------|
| `execute(code)` | 执行脚本代码字符串 |
| `executeFile(path)` | 执行脚本文件 |
| `getLastReturnValue()` | 获取最后返回值 |
| `getLastError()` | 获取最后错误信息 |
| `registerNativeFunction(name, func)` | 注册原生函数 |
| `setCacheEnabled(enabled)` | 启用/禁用缓存 |
| `setPlatform(name)` | 设置目标平台 |
| `version()` | 获取版本信息 |

## 运行测试

```bash
cd build
ctest --output-on-failure
```

## 许可证

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

## 贡献

欢迎提交 Issue 和 Pull Request！
