# RISC-V 64 代码生成器架构设计

## 1. 架构概述

RISC-V 64 代码生成器是 CScriptEngine 的后端组件，负责将中间代码（四元式）转换为 RISC-V 64 位机器码。它与现有的 x86-64 代码生成器共享相同的接口，确保与系统的其他部分无缝集成。

### 1.1 设计目标

- 与现有 x86-64 代码生成器接口兼容
- 支持 RISC-V 64 指令集
- 实现高效的寄存器分配策略
- 遵循 RISC-V 64 调用约定
- 支持栈帧布局优化

## 2. 接口兼容性设计

### 2.1 继承层次

```
ICodeGenerator (接口)
    ↑
BaseCodeGenerator (基础实现)
    ↑
X64Code (x86-64 实现)  RV64Code (RISC-V 64 实现)
```

### 2.2 接口实现

RV64Code 类将继承自 BaseCodeGenerator，并实现 ICodeGenerator 接口定义的所有方法：

- `Value* Create(BinaryOps instr, Value* lhs, Value* rhs, std::string str)`
- `Value* CreateDoubleBinaryOp(BinaryOps instr, Value* lhs, Value* rhs, std::string str)`
- `Value* Create(UnaryOps instr, Value* operand, std::string str)`
- `void Create(ControlFlowOps instr, const char* label)`
- `void Create(ControlFlowOps instr)`
- `void CreateLabel(const char* label)`
- `void StoreVariable(const char* name, Value* value, Type type = Int)`
- `Value* LoadVariable(const char* name, Type type = Int)`
- `Value* CreateArrayAccess(const char* name, Value* index)`
- `void formatCode()`
- `void DisassembleCode() const`
- `void generateCodeFromIR(const std::list<Quad>& quadList)`

## 3. RISC-V 64 指令集映射

### 3.1 基本指令映射

| 操作类型 | x86-64 指令 | RISC-V 64 指令 |
|---------|-------------|----------------|
| 加法 | add | add |
| 减法 | sub | sub |
| 乘法 | imul | mul |
| 除法 | idiv | div |
| 取模 | idiv | rem |
| 逻辑与 | and | and |
| 逻辑或 | or | or |
| 逻辑非 | not | xor (与全1异或) |
| 异或 | xor | xor |
| 左移 | shl | sll |
| 右移 | shr/sar | srl/sra |
| 比较 | cmp | slt/sltu/sgt/sgtu |
| 跳转 | jmp/je/jne/jl/jle/jg/jge | j/beq/bne/blt/ble/bgt/bge |
| 调用 | call | jal |
| 返回 | ret | jalr |

### 3.2 浮点指令映射

| 操作类型 | x86-64 指令 | RISC-V 64 指令 |
|---------|-------------|----------------|
| 浮点加法 | addsd | fadd.d |
| 浮点减法 | subsd | fsub.d |
| 浮点乘法 | mulsd | fmul.d |
| 浮点除法 | divsd | fdiv.d |
| 浮点比较 | ucomisd | fcmp.d |

## 4. 寄存器分配策略

### 4.1 寄存器模型

RISC-V 64 架构有 32 个通用寄存器（x0-x31）和 32 个浮点寄存器（f0-f31）。

| 寄存器 | 用途 |
|-------|------|
| x0 | 零寄存器（始终为0） |
| x1 | 返回地址（ra） |
| x2 | 栈指针（sp） |
| x3 | 全局指针（gp） |
| x4 | 线程指针（tp） |
| x5-x7 | 临时寄存器（t0-t2） |
| x8 | 保存的寄存器（s0/fp） |
| x9 | 保存的寄存器（s1） |
| x10-x17 | 参数寄存器（a0-a7） |
| x18-x27 | 保存的寄存器（s2-s11） |
| x28-x31 | 临时寄存器（t3-t6） |

### 4.2 分配策略

1. **参数寄存器分配**：
   - 前 8 个整数参数使用 a0-a7（x10-x17）
   - 前 8 个浮点参数使用 f0-f7

2. **临时寄存器分配**：
   - 使用 t0-t6（x5-x7, x28-x31）作为临时寄存器
   - 当临时寄存器不足时，使用栈空间

3. **保存的寄存器分配**：
   - 使用 s0-s11（x8-x9, x18-x27）作为保存的寄存器
   - 函数调用前后需要保存和恢复这些寄存器

4. **寄存器溢出处理**：
   - 当寄存器不足时，将溢出的变量存储到栈中
   - 函数返回前恢复溢出的寄存器

## 5. 栈帧布局

### 5.1 基本布局

```
+------------------------+
| 保存的寄存器（s0-s11）  |
+------------------------+
| 局部变量                |
+------------------------+
| 临时变量/溢出变量       |
+------------------------+
| 函数参数（超过8个）     |
+------------------------+
| 返回地址（ra）          |
+------------------------+
| 栈指针（sp）            |
+------------------------+
```

### 5.2 栈帧大小计算

- 保存的寄存器：12 个 × 8 字节 = 96 字节
- 局部变量：根据变量类型和数量计算
- 临时变量/溢出变量：根据需要动态分配
- 函数参数：超过 8 个的参数，每个 8 字节

### 5.3 栈对齐

RISC-V 64 要求栈对齐到 16 字节边界。在函数入口处，需要调整栈指针以满足对齐要求。

## 6. 调用约定实现

### 6.1 函数调用

1. **参数传递**：
   - 前 8 个整数参数：a0-a7（x10-x17）
   - 前 8 个浮点参数：f0-f7
   - 超过 8 个的参数：通过栈传递

2. **返回值**：
   - 整数返回值：a0（x10）
   - 浮点返回值：f0
   - 结构体返回值：通过内存传递

3. **寄存器保存**：
   - 调用者保存：t0-t6（x5-x7, x28-x31）
   - 被调用者保存：s0-s11（x8-x9, x18-x27）

### 6.2 函数入口/出口

1. **函数入口**：
   - 保存返回地址（ra）
   - 保存被调用者保存的寄存器（s0-s11）
   - 调整栈指针（sp）以分配局部变量空间
   - 确保栈对齐到 16 字节边界

2. **函数出口**：
   - 恢复被调用者保存的寄存器（s0-s11）
   - 恢复栈指针（sp）
   - 通过 jalr 指令返回

## 7. 代码生成流程

### 7.1 初始化

- 设置初始状态
- 初始化寄存器分配器
- 准备代码和数据缓冲区

### 7.2 遍历中间代码

- 遍历四元式序列
- 为每个四元式生成对应的 RISC-V 64 指令
- 处理控制流指令（跳转、调用、返回）
- 处理内存访问（加载、存储）

### 7.3 代码优化

- 常量折叠
- 死代码消除
- 寄存器分配优化
- 指令选择优化

### 7.4 代码格式化

- 修复跳转偏移量
- 修复函数调用偏移量
- 生成数据段
- 确保代码正确对齐

## 8. 实现细节

### 8.1 实现文件

RISC-V 64 代码生成器的实现文件包括：

- **RV64Code.cpp**：核心代码生成逻辑，实现了 `ICodeGenerator` 接口
- **RV64MemoryManager.cpp**：RISC-V 平台的内存管理实现

### 8.2 类结构

```cpp
class RV64Code : public BaseCodeGenerator {
private:
    // 寄存器分配相关
    std::vector<bool> m_RegisterUsage; // 寄存器使用情况
    std::vector<bool> m_FloatRegisterUsage; // 浮点寄存器使用情况
    
    // 栈帧相关
    int m_StackSize; // 当前栈大小
    std::map<std::string, size_t> m_StackAllocPositions; // 栈分配位置
    
    // 辅助方法
    int allocateRegister();
    void freeRegister(int reg);
    int allocateFloatRegister();
    void freeFloatRegister(int reg);
    
    // 四元式处理方法
    void handleAddOperation(const Quad& quad);
    void handleSubOperation(const Quad& quad);
    void handleMulOperation(const Quad& quad);
    void handleDivOperation(const Quad& quad);
    void handleLogicalOperation(const Quad& quad);
    void handleComparisonOperation(const Quad& quad);
    void handleControlFlowOperation(const Quad& quad);
    void handleMemoryOperation(const Quad& quad);
    
    // 指令生成辅助方法
    void generateLoadImmediate(int reg, uint64_t value);
    void generateStoreRegister(int reg, int offset, int base = 2); // base=2 表示 sp
    void generateLoadRegister(int reg, int offset, int base = 2); // base=2 表示 sp
    void generateBranchInstruction(const std::string& condition, const std::string& label);
    void generateFunctionCall(const std::string& funcName, int paramCount);
    
public:
    // 接口实现方法
    Value* Create(BinaryOps instr, Value* lhs, Value* rhs, std::string str) override;
    Value* CreateDoubleBinaryOp(BinaryOps instr, Value* lhs, Value* rhs, std::string str) override;
    Value* Create(UnaryOps instr, Value* operand, std::string str) override;
    void Create(ControlFlowOps instr, const char* label) override;
    void Create(ControlFlowOps instr) override;
    void CreateLabel(const char* label) override;
    void StoreVariable(const char* name, Value* value, Type type = Int) override;
    Value* LoadVariable(const char* name, Type type = Int) override;
    Value* CreateArrayAccess(const char* name, Value* index) override;
    void formatCode() override;
    void DisassembleCode() const override;
    void generateCodeFromIR(const std::list<Quad>& quadList) override;
};
```

### 8.2 寄存器分配实现

```cpp
int RV64Code::allocateRegister() {
    // 优先使用临时寄存器 t0-t6 (x5-x7, x28-x31)
    int tempRegs[] = {5, 6, 7, 28, 29, 30, 31};
    for (int reg : tempRegs) {
        if (!m_RegisterUsage[reg]) {
            m_RegisterUsage[reg] = true;
            return reg;
        }
    }
    
    // 其次使用参数寄存器 a0-a7 (x10-x17)
    for (int reg = 10; reg <= 17; reg++) {
        if (!m_RegisterUsage[reg]) {
            m_RegisterUsage[reg] = true;
            return reg;
        }
    }
    
    // 最后使用保存的寄存器 s0-s11 (x8-x9, x18-x27)
    int savedRegs[] = {8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
    for (int reg : savedRegs) {
        if (!m_RegisterUsage[reg]) {
            m_RegisterUsage[reg] = true;
            return reg;
        }
    }
    
    // 所有寄存器都被使用，返回 -1 表示需要使用栈
    return -1;
}
```

### 8.3 函数调用实现

```cpp
void RV64Code::CallStandardLibraryFunction(const char* name) {
    // 保存临时寄存器
    // 准备参数（使用 a0-a7）
    // 生成 jal 指令调用函数
    // 恢复临时寄存器
}
```

## 9. 测试策略

### 9.1 单元测试

- 测试基本指令生成
- 测试寄存器分配
- 测试栈帧布局
- 测试函数调用

### 9.2 集成测试

- 测试完整的代码生成流程
- 测试与前端和中间代码生成的集成
- 测试在 RISC-V 平台上的执行

### 9.3 性能测试

- 测试代码生成速度
- 测试生成代码的执行效率
- 测试内存使用情况

## 10. 结论

RISC-V 64 代码生成器的设计遵循了 CScriptEngine 的整体架构，与现有的 x86-64 代码生成器保持接口兼容，同时实现了 RISC-V 64 指令集的映射、高效的寄存器分配策略、合理的栈帧布局和符合规范的调用约定。

该设计考虑了 RISC-V 64 架构的特点，充分利用了其寄存器资源，优化了代码生成过程，确保生成的代码高效、正确。同时，该设计也为未来的扩展和优化留下了空间，如添加更多的指令优化、支持更多的 RISC-V 扩展等。

通过实现 RISC-V 64 代码生成器，CScriptEngine 将能够在 RISC-V 平台上运行，为嵌入式系统和物联网设备提供轻量级的 C 语言脚本执行能力。