# 标准库设计

## 1. 模块概述

标准库是CScriptEngine的重要组成部分，提供了常用的函数和工具，方便用户编写脚本。它包括输入输出、字符串处理、内存管理等功能。标准库函数通过配置表管理，在语义分析阶段进行符号解析，运行时通过内置实现或系统调用执行。

## 2. 设计原理

标准库设计采用模块化设计，将不同功能的函数组织到不同的头文件中。标准库函数的实现方式包括：
- **内置实现**：对于常用函数，提供内置实现，直接生成目标码
- **系统调用**：对于复杂函数，直接调用目标平台的系统库

标准库函数通过 `BUILTIN_FUNCTIONS` 配置表进行管理，包含函数名、返回类型、参数类型等信息。

## 3. 数据结构

### 3.1 内置函数表

内置函数表定义于 `src/frontend/semantic/SymbolTable.h`：

```cpp
struct BuiltinFunction {
    const char* name;              // 函数名称
    const char* returnType;       // 返回类型
    bool isVariadic;               // 是否为可变参数
    std::vector<std::string> paramTypes;  // 参数类型列表
};

static const std::vector<BuiltinFunction> BUILTIN_FUNCTIONS = {
    {"printf", "int", true, {}},
    {"scanf", "int", true, {}},
    {"puts", "int", false, {"string"}},
    {"strlen", "int", false, {"char*"}},
    {"malloc", "char*", false, {"int"}},
    {"free", "void", false, {"char*"}},
    {"strcpy", "char*", false, {"char*", "char*"}},
    {"strcat", "char*", false, {"char*", "char*"}},
    {"strcmp", "int", false, {"char*", "char*"}},
    {"getchar", "int", false, {}},
    {"putchar", "int", false, {"int"}},
};
```

### 3.2 头文件组织

| 头文件 | 功能类别 | 实现状态 |
|--------|---------|---------|
| `stdio.h` | 输入输出 | ✅ 部分实现 |
| `string.h` | 字符串处理 | ✅ 部分实现 |
| `stdlib.h` | 内存管理/工具 | ✅ 部分实现 |
| `ctype.h` | 字符处理 | ❌ 未实现 |
| `math.h` | 数学函数 | ❌ 未实现 |
| `time.h` | 时间日期 | ❌ 未实现 |

## 4. 接口设计

### 4.1 函数查找接口

标准库函数在语义分析阶段通过名称查找：

```cpp
// 查找内置函数
BuiltinFunction* findBuiltinFunction(const std::string& name);

// 检查是否为内置函数
bool isBuiltinFunction(const std::string& name);
```

### 4.2 函数调用接口

内置函数调用通过 `CallStandardLibraryFunction` 方法处理：

```cpp
// IRGenerator.cpp
void IRGenerator::CallStandardLibraryFunction(const std::string& name, ...);
```

## 5. 已实现函数详解

### 5.1 stdio.h

| 函数 | 状态 | 说明 |
|------|------|------|
| `printf` | ✅ 已实现 | 格式化输出，支持可变参数 |
| `puts` | ✅ 已实现 | 输出字符串，自动换行 |
| `getchar` | ✅ 已实现 | 读取单个字符 |
| `putchar` | ✅ 已实现 | 输出单个字符 |
| `scanf` | ✅ 已实现 | 格式化输入 |
| `gets` | ✅ 已实现 | 读取字符串 |
| `fopen` | ✅ 已实现 | 打开文件 |
| `fclose` | ✅ 已实现 | 关闭文件 |
| `fread` | ✅ 已实现 | 从文件读取数据 |
| `fwrite` | ✅ 已实现 | 向文件写入数据 |
| `fprintf` | ✅ 已实现 | 向文件格式化输出 |
| `fscanf` | ✅ 已实现 | 从文件格式化输入 |

**printf 实现**：
```cpp
// 生成的四元式
PARAM format_string
PARAM arg1
PARAM arg2
CALL printf, 3
```

### 5.2 string.h

| 函数 | 状态 | 说明 |
|------|------|------|
| `strlen` | ✅ 已实现 | 返回字符串长度 |
| `strcpy` | ✅ 已实现 | 复制字符串 |
| `strcat` | ✅ 已实现 | 连接字符串 |
| `strcmp` | ✅ 已实现 | 比较字符串 |
| `strstr` | ✅ 已实现 | 查找子字符串 |
| `memset` | ✅ 已实现 | 内存设置 |
| `memcpy` | ✅ 已实现 | 内存复制 |

### 5.3 stdlib.h

| 函数 | 状态 | 说明 |
|------|------|------|
| `malloc` | ✅ 已实现 | 分配内存 |
| `free` | ✅ 已实现 | 释放内存 |
| `realloc` | ✅ 已实现 | 重新分配内存 |
| `system` | ✅ 已实现 | 执行系统命令 |
| `getenv` | ✅ 已实现 | 获取环境变量 |

### 5.4 ctype.h (未实现)

| 函数 | 状态 | 说明 |
|------|------|------|
| `isdigit` | ❌ 未实现 | 检查数字字符 |
| `isalpha` | ❌ 未实现 | 检查字母字符 |
| `isalnum` | ❌ 未实现 | 检查字母数字 |
| `isspace` | ❌ 未实现 | 检查空白字符 |
| `tolower` | ❌ 未实现 | 转换小写 |
| `toupper` | ❌ 未实现 | 转换大写 |

### 5.5 math.h

| 函数 | 状态 | 说明 |
|------|------|------|
| `sqrt` | ✅ 已实现 | 平方根 |
| `pow` | ✅ 已实现 | 幂运算 |
| `sin` | ✅ 已实现 | 正弦函数 |
| `cos` | ✅ 已实现 | 余弦函数 |
| `tan` | ✅ 已实现 | 正切函数 |
| `abs` | ✅ 已实现 | 整数绝对值 |
| `fabs` | ✅ 已实现 | 浮点数绝对值 |

### 5.6 time.h

| 函数 | 状态 | 说明 |
|------|------|------|
| `time` | ✅ 已实现 | 获取当前时间 |
| `clock` | ✅ 已实现 | 时钟计时 |

## 6. 实现细节

### 6.1 内置函数检测

在语义分析阶段检测内置函数：

```cpp
// SemanticAnalyzer.cpp
bool isBuiltinFunction(const std::string& name) {
    for (const auto& func : BUILTIN_FUNCTIONS) {
        if (func.name == name) return true;
    }
    return false;
}
```

### 6.2 函数调用生成

对于内置函数，生成特殊的 CALL 四元式：

```cpp
// IRGenerator.cpp
if (isBuiltinFunction(funcName)) {
    // 生成内置函数调用
    emit(CALL, funcName, ...);
} else {
    // 普通函数调用
    emit(CALL, label, ...);
}
```

### 6.3 标准库函数执行

内置函数通过 X64Code 生成对应的机器码：

```cpp
// X64Code.cpp
void X64Code::CallStandardLibraryFunction(const std::string& name, ...) {
    if (name == "printf") {
        // 生成 printf 调用
    } else if (name == "strlen") {
        // 生成 strlen 调用
    }
    // ...
}
```

## 7. 待实现函数

### 7.1 高优先级

| 函数 | 头文件 | 说明 |
|------|--------|------|
| `atoi` | stdlib.h | 字符串转整数，使用频繁 |
| `atof` | stdlib.h | 字符串转浮点 |
| `memset` | string.h | 内存设置 |
| `memcpy` | string.h | 内存复制 |

### 7.2 中优先级

| 函数 | 头文件 | 说明 |
|------|--------|------|
| `isdigit` | ctype.h | 字符分类 |
| `isalpha` | ctype.h | 字符分类 |
| `sqrt` | math.h | 数学函数 |
| `calloc` | stdlib.h | 内存分配 |

### 7.3 低优先级

| 函数 | 头文件 | 说明 |
|------|--------|------|
| `rand` | stdlib.h | 随机数 |
| `time` | time.h | 时间函数 |

## 8. 测试策略

### 8.1 测试用例

```c
// 测试 printf
printf("Hello, World!\n");
printf("Value: %d\n", 42);
printf("Float: %f\n", 3.14);

// 测试字符串函数
int len = strlen("test");
int cmp = strcmp("abc", "def");
strcpy(dest, "source");
strcat(dest, "append");

// 测试内存函数
char* p = malloc(100);
free(p);
```

### 8.2 测试方法

- **单元测试**：测试每个标准库函数的正确性
- **集成测试**：测试标准库函数与编译器的集成
- **边界测试**：测试空指针、空字符串等边界情况

## 9. 参考资料

- [SymbolTable.h 实现](../src/frontend/semantic/SymbolTable.h)
- [IRGenerator 内置函数调用](../src/ir/IRGenerator.cpp)
- [X64Code 库函数调用](../src/backend/X64Code.cpp)
