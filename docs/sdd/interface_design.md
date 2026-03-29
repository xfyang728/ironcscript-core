# CScriptEngine 接口设计文档

## 1. 模块架构概述

CScriptEngine 采用经典编译器架构，模块间通过清晰定义的接口进行交互。

```
源代码 (.c)
    ↓
┌─────────────────────────────────────────────────────────────┐
│                     前端 (Frontend)                          │
├─────────────────────────────────────────────────────────────┤
│  词法分析器 → 语法分析器 → 语义分析器 → AST                  │
│  (ANTLR4)     (ANTLR4)    (SemanticAnalyzer)                │
└─────────────────────────────────────────────────────────────┘
    ↓ AST (node.h)
┌─────────────────────────────────────────────────────────────┐
│                     中间表示 (IR)                            │
├─────────────────────────────────────────────────────────────┤
│  IRGenerator → 四元式列表 (Quad)                            │
└─────────────────────────────────────────────────────────────┘
    ↓ Quad List
┌─────────────────────────────────────────────────────────────┐
│                     后端 (Backend)                          │
├─────────────────────────────────────────────────────────────┤
│  CodeGenerator → 目标代码 (X64/X86/RISCV)                   │
│  MemoryManager  → 可执行内存                                │
└─────────────────────────────────────────────────────────────┘
    ↓
执行
```

## 2. 核心模块接口

### 2.1 词法分析器接口

**输入**：源代码文本
**输出**：Token 流

```cpp
// 文件：src/frontend/generated/CScriptLexer.h
namespace antlr4 {
    class ANTLRInputStream;
    class Lexer;
    class CommonTokenStream;
}

// 主要接口
class CScriptLexer {
public:
    CScriptLexer(ANTLRInputStream* input);
    CommonTokenStream* getTokens();
};
```

**相关文件**：
- `src/frontend/generated/CScriptLexer.h` - 词法分析器头文件
- `src/frontend/generated/CScriptParser.h` - 语法分析器头文件
- `src/frontend/parser/CScript.g4` - 语法定义文件

### 2.2 语法分析器接口

**输入**：Token 流
**输出**：ANTLR Parse Tree

```cpp
// 文件：src/frontend/generated/CScriptParser.h
class CScriptParser {
public:
    CScriptParser(CommonTokenStream* tokens);
    ProgramContext* program();
};
```

### 2.3 AST 构建器接口

**输入**：Parse Tree
**输出**：NBlock (抽象语法树根节点)

```cpp
// 文件：src/frontend/parser/ASTBuilder.h
namespace cse {
class ASTBuilder : public CScriptVisitor {
public:
    ASTBuilder();
    NBlock* build(CScriptParser::ProgramContext* ctx);
};
}
```

**AST 节点类型** (定义于 `node.h`)：

```cpp
// 表达式节点
class NExpression : public Node {};
class NInteger : public NExpression { int value; };
class NDouble : public NExpression { double value; };
class NIdentifier : public NExpression { std::string name; };
class NBinaryOperator : public NExpression { NExpression& lhs, rhs; int op; };
class NUnaryOperator : public NExpression { NExpression& expr; int op; };
class NAssignment : public NExpression { NExpression& lhs, rhs; };
class NArrayAccess : public NExpression { NIdentifier& id; NExpression& index; };
class NMemberAccess : public NExpression { NExpression& object; NIdentifier& member; };
class NMethodCall : public NExpression { NIdentifier& id; ExpressionList& arguments; };
class NTernaryOperator : public NExpression { NExpression& condition, thenExpr, elseExpr; };

// 语句节点
class NStatement : public Node {};
class NBlock : public NStatement { std::vector<NStatement*> statements; };
class NVariableDeclaration : public NStatement { NIdentifier& type, id; NExpression* assignmentExpr; };
class NArrayDeclaration : public NStatement { NIdentifier& type, id; NExpression* size; ExpressionList* initializer; };
class NFunctionDeclaration : public NStatement { NIdentifier& type, id; VariableList& arguments; NBlock* block; };
class NIfStatement : public NStatement { NExpression* condition; NBlock& thenBlock, *elseBlock; };
class NWhileStatement : public NStatement { NExpression& condition; NBlock& block; };
class NForStatement : public NStatement { NStatement* init; NExpression* condition, *increment; NBlock& block; };
class NReturnStatement : public NStatement { NExpression* expression; };
class NBreakStatement : public NStatement {};
class NContinueStatement : public NStatement {};
```

### 2.4 语义分析器接口

**输入**：AST (NBlock)
**输出**：带符号表的 AST + 错误报告

```cpp
// 文件：src/frontend/semantic/SemanticAnalyzer.h
namespace cse {
class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    bool analyze(NBlock& root);
    bool hasErrors() const;
    void error(const std::string& message, Node* node = nullptr);
};
}
```

### 2.5 IR 生成器接口

**输入**：AST (NBlock)
**输出**：四元式列表

```cpp
// 文件：src/ir/IRGenerator.h
namespace cse {
class IRGenerator {
public:
    IRGenerator();
    void generateIR(NBlock& root);
    const std::list<Quad>& getQuadList() const;
    const std::vector<std::string>& getKnownVariables() const;
};

class Quad {
public:
    OpEnum op;
    std::string arg1, arg2, result;
};
}
```

**四元式操作码** (定义于 `Quad.h`)：

```cpp
enum class OpEnum {
    // 算术运算
    ADD, SUB, MUL, DIV, MOD,
    // 比较运算
    LT, GT, LE, GE, EQ, NE,
    // 逻辑运算
    AND, OR, NOT,
    // 位运算
    BITAND, BITOR, BITXOR, BITNOT, LSHIFT, RSHIFT,
    // 赋值
    ASSIGN, ARRAY_LOAD, ARRAY_STORE,
    // 控制流
    JUMP, JZ, JNZ, LABEL,
    // 函数
    CALL, PARAM, RETURN, FUNC_BEGIN, FUNC_END,
    // 内存
    MALLOC, FREE, MEMCPY, MEMSET,
    // 类型转换
    I2D, D2I, I2D_D, D2I_D,
    // 打印
    PRINT, PRINTLN,
    // 其他
    LOAD, STORE, ADDR, DEREF, NOP
};
```

### 2.6 代码生成器接口

**输入**：四元式列表
**输出**：目标机器码

```cpp
// 文件：src/backend/codegen.h
namespace cse {
class CodeGenerator {
public:
    CodeGenerator(TargetArchitecture arch);
    void generate(IRGenerator& ir, std::vector<uint8_t>& code);
    size_t getCodeSize() const;
};
}
```

**支持的架构**：

```cpp
enum class TargetArchitecture {
    X64,    // x86-64
    X86,    // x86-32
    RISCV64 // RISC-V 64-bit
};
```

### 2.7 内存管理接口

**输入**：生成的机器码
**输出**：可执行内存地址

```cpp
// 文件：src/backend/MemoryManager.h
namespace cse {
class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager();
    
    void* allocateExecutable(size_t size);
    void freeExecutable(void* addr);
    int execute(void* code, int argCount, void** args);
};
}
```

## 3. 模块间数据流

### 3.1 编译流程

```
1. 词法分析
   源代码 → CScriptLexer → TokenStream

2. 语法分析
   TokenStream → CScriptParser → ParseTree

3. AST 构建
   ParseTree → ASTBuilder → NBlock

4. 语义分析
   NBlock → SemanticAnalyzer → (验证后)NBlock + SymbolTable

5. IR 生成
   NBlock → IRGenerator → QuadList

6. 代码生成
   QuadList → CodeGenerator → MachineCode

7. JIT 执行
   MachineCode → MemoryManager → Executable → 执行
```

### 3.2 主要数据传递

| 阶段 | 输入 | 输出 | 关键类型 |
|------|------|------|---------|
| 词法分析 | `char*` | `CommonTokenStream` | ANTLR 类型 |
| 语法分析 | `CommonTokenStream` | `ProgramContext*` | ANTLR 类型 |
| AST 构建 | `ProgramContext*` | `NBlock*` | `node.h` |
| 语义分析 | `NBlock*` | `NBlock*` (验证) | `node.h` |
| IR 生成 | `NBlock*` | `std::list<Quad>` | `Quad.h` |
| 代码生成 | `std::list<Quad>` | `std::vector<uint8_t>` | C++ 标准 |
| JIT | `std::vector<uint8_t>` | `void*` | 原始指针 |

## 4. 公共接口汇总

### 4.1 公开类型

| 文件 | 类型 | 说明 |
|------|------|------|
| `frontend/parser/node.h` | `NBlock`, `NExpression`, `NStatement` 等 | AST 节点类型 |
| `ir/Quad.h` | `Quad`, `OpEnum` | 四元式类型 |
| `backend/Architecture.h` | `TargetArchitecture` | 目标架构枚举 |

### 4.2 公开函数

| 文件 | 函数 | 说明 |
|------|------|------|
| `CScriptEngine.cpp` | `main()` | 程序入口 |
| `ASTBuilder.h` | `ASTBuilder::build()` | AST 构建入口 |
| `SemanticAnalyzer.h` | `SemanticAnalyzer::analyze()` | 语义分析入口 |
| `IRGenerator.h` | `IRGenerator::generateIR()` | IR 生成入口 |
| `codegen.h` | `CodeGenerator::generate()` | 代码生成入口 |
| `MemoryManager.h` | `MemoryManager::execute()` | JIT 执行入口 |

### 4.3 配置接口

| 文件 | 配置项 | 说明 |
|------|------|------|
| `backend/CodeGenConfig.h` | `TargetArchitecture` | 目标架构配置 |
| `frontend/semantic/SymbolTable.h` | `BUILTIN_FUNCTIONS` | 内置函数配置表 |

## 5. 错误处理接口

### 5.1 错误报告

```cpp
// 语义分析错误
class SemanticAnalyzer {
    void error(const std::string& message, Node* node = nullptr);
    bool hasErrors() const;
    const std::vector<std::string>& getErrors() const;
};

// IR 生成错误
class IRGenerator {
    void error(const std::string& message, const Node* node = nullptr);
    bool hasErrors() const;
};
```

### 5.2 错误类型

| 阶段 | 错误类型 | 说明 |
|------|---------|------|
| 词法分析 | 词法错误 | 无法识别的字符 |
| 语法分析 | 语法错误 | 语法规则不匹配 |
| 语义分析 | 语义错误 | 未声明变量、类型不匹配等 |
| IR 生成 | IR 错误 | 无效的四元式操作 |
| 代码生成 | 代码生成错误 | 不支持的操作码 |

## 6. 版本历史

| 版本 | 日期 | 修改内容 |
|------|------|---------|
| 1.0 | 2026-03-19 | 初始版本，定义核心接口 |

## 7. 待完善接口

### 7.1 计划中的接口

- **调试接口**：用于 IDE 集成和调试支持
- **插件接口**：用于扩展语言特性
- **性能分析接口**：用于运行时性能监控

### 7.2 平台特定接口

- **Windows x64**：已完善
- **Windows x86**：待测试
- **RISC-V 64**：待测试
