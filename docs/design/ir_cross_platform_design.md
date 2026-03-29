# IR 跨平台架构设计

> **版本**: 1.3
> **最后更新**: 2026-03-27
> **测试状态**: 119/119 通过

## 1. 当前架构

### 1.1 组件关系

```
AST (抽象语法树)
    │
    ▼
IRGenerator (IR 生成器)
    │
    ▼
Quad 列表 (四元式)
    │
    ▼
┌─────────────────────────────────────────┐
│      BaseCodeGenerator (抽象基类)         │
├─────────────┬─────────────┬─────────────┤
│   X64Code   │  RV64Code  │ BytecodeCompiler │
│  (x64 JIT)  │ (RISC-V)   │  (字节码)    │
└─────────────┴─────────────┴─────────────┘
```

### 1.2 文件结构

```
src/
├── backend/
│   ├── BaseCodeGenerator.h/cpp   (抽象基类)
│   ├── codegen.cpp              (代码生成入口)
│   ├── x64/
│   │   ├── X64Code.h/cpp       (x64 JIT 代码生成)
│   │   ├── X64CodeControl.cpp  (跳转/调用偏移修复)
│   │   ├── X64CodeMemory.cpp   (内存管理)
│   │   ├── X64CodeOps.cpp      (操作码生成)
│   │   └── X64CodeUtils.cpp    (工具函数)
│   ├── rv64/
│   │   └── RV64Code.h/cpp      (RISC-V JIT)
│   └── bytecode/
│       └── BytecodeCompiler.cpp (字节码编译器)
├── ir/
│   ├── IRGenerator.h/cpp        (IR 生成)
│   └── Quad.h/cpp               (四元式定义)
└── vm/
    ├── BytecodeVM.cpp           (字节码解释器)
    └── k210/
        └── K210VM.cpp          (K210 专用 VM)
```

## 2. 已完成的重构

### 2.1 x64 JIT 修复 ✅

**问题**: 代码和数据混合存储，formatCode() 将数据追加到代码缓冲区后，绝对地址未更新。

**解决方案**: 使用 RIP-relative 寻址 + 数据区域偏移修复

**关键修复**:
1. `m_RipRelativeOffsets` 从 `std::map` 改为 `std::vector`，避免同一 instrPos 的偏移被覆盖
2. `formatCode()` 中修复 RIP 偏移时使用 `codeSize + dataOffset`
3. `fixJumpOffsets()` 和 `fixCallOffsets()` 正确处理数据追加后的标签位置

### 2.2 PARAM 处理重构 ✅

**问题**: IRGenerator 生成的 PARAM 四元式使用物理寄存器名（如 "rcx"），硬编码平台相关。

**解决方案**: IRGenerator 生成抽象参数名，X64Code 负责映射到物理寄存器。

```cpp
// IRGenerator.cpp - 当前实现
std::string varName = param->id.name;
quadList.push_back(Quad(OpEnum::PARAM, varName, "", varName));

// X64Code.cpp - PARAM 处理
case OpEnum::PARAM: {
    int paramReg = mapParameterToRegister(m_StackArgCount);
    // RCX=1, RDX=2, R8=8, R9=9, stack for others
    ...
}
```

### 2.3 死代码消除保留 PARAM 赋值 ✅

```cpp
// X64CodeUtils.cpp
bool isParam = (result.substr(0, 6) == "param_");
if (usedVariables.find(result) != usedVariables.end() || result == "rcx" || ... || isParam)
```

## 3. 当前架构细节

### 3.1 BaseCodeGenerator

```cpp
class BaseCodeGenerator {
protected:
    std::vector<unsigned char> m_CodeBuffer;     // 机器码
    std::vector<unsigned char> m_DataBuffer;    // 数据
    std::map<std::string, int> m_VariableOffsets; // 变量偏移
    std::vector<size_t> m_LocalVariableSizes;   // 局部变量大小
    Architecture* m_Architecture;                 // 架构信息
    PlatformAbstraction* m_Platform;              // 平台抽象
};
```

### 3.2 X64Code

```cpp
class X64Code : public BaseCodeGenerator {
private:
    struct RipOffsetInfo {
        size_t instrPos;      // 指令位置
        size_t dataOffset;    // 数据偏移
        size_t instrLength;   // 指令长度
    };
    std::vector<RipOffsetInfo> m_RipRelativeOffsets;

    std::map<std::string, size_t> m_Functions;    // 函数位置
    std::vector<std::pair<size_t, std::string>> m_CallSites;    // 调用位置
    std::vector<std::pair<size_t, std::string>> m_JumpSites;    // 跳转位置
    std::map<std::string, size_t> m_Labels;       // 标签位置
};
```

### 3.3 BytecodeCompiler

```cpp
// BytecodeCompiler.cpp - CALL 处理
case OpEnum::CALL: {
    const std::string& funcName = quad.getArg1();
    const std::string& arg2 = quad.getArg2();
    int paramCount = 0;
    if (!arg2.empty()) {  // 空值检查修复
        paramCount = std::stoi(arg2);
    }
    ...
}
```

## 4. 测试状态

### 4.1 x64 JIT 测试

| 测试类别 | 通过/总数 | 状态 |
|---------|----------|------|
| 文件函数 | 5/5 | ✅ |
| 时间函数 | 1/1 | ✅ |
| 算术运算 | 10/10 | ✅ |
| 控制流 | 5/5 | ✅ |
| 数组 | 3/3 | ✅ |
| 指针 | 3/3 | ✅ |
| 字符串 | 4/4 | ✅ |
| 标准库 | 15/15 | ✅ |

**总计**: 119/119 通过

## 5. 待优化项

### 5.1 短期目标

1. **entry code 优化**: 当前使用 `call 6` + `ret`，可以考虑使用 `jmp` 直接跳转
2. **浮点参数传递**: 使用 XMM 寄存器处理浮点参数

### 5.2 中期目标

1. **RV64Code 重构**: 清理 RISC-V 后端代码
2. **IR 平台无关性**: 进一步解耦 IR 和目标代码生成

## 6. 参考

- [System V AMD64 ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)
- [Windows x64 ABI](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture)
- [RISC-V Calling Convention](https://github.com/riscv-non-isa/riscv-elf-psabi-doc)
