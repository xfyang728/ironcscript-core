# 语法分析器设计

## 1. 模块概述

语法分析器是CScriptEngine的前端组件，负责将词法分析器生成的词法单元流转换为抽象语法树（AST）。它是编译器的第二个阶段，为后续的语义分析提供输入。

## 2. 设计原理

语法分析器使用上下文无关文法（CFG）来描述语言的语法结构，通过递归下降或LR分析等方法构建抽象语法树。CScriptEngine使用ANTLR4工具生成语法分析器，通过定义语法规则文件（CScript.g4）来描述如何构建抽象语法树。

## 3. 数据结构

### 3.1 抽象语法树（AST）

抽象语法树是语法分析器的输出，由以下节点类型组成：
- **NBlock**：语句块
- **NFunctionDeclaration**：函数声明
- **NVariableDeclaration**：变量声明
- **NAssignment**：赋值语句
- **NReturnStatement**：返回语句
- **NBinaryOperator**：二元运算符
- **NUnaryOperator**：一元运算符
- **NIdentifier**：标识符
- **NInteger**：整数常量
- **NDouble**：浮点数常量
- **NChar**：字符常量
- **NString**：字符串常量
- **NIfStatement**：条件语句
- **NWhileStatement**：while循环
- **NForStatement**：for循环
- **NDoWhileStatement**：do-while循环
- **NSwitchStatement**：switch语句
- **NCaseStatement**：case语句
- **NDefaultStatement**：default语句
- **NBreakStatement**：break语句
- **NContinueStatement**：continue语句
- **NFunctionCall**：函数调用
- **NArrayDeclaration**：数组声明
- **NArrayAccess**：数组访问
- **NPointerType**：指针类型
- **NDereference**：解引用操作
- **NAddressOf**：取地址操作
- **NEnumDeclaration**：枚举声明

### 3.2 语法规则

语法规则定义了语言的语法结构，包括：
- **程序结构**：函数声明、变量声明、语句块
- **表达式**：二元表达式、一元表达式、函数调用、数组访问
- **语句**：赋值语句、返回语句、条件语句、循环语句

## 4. 算法流程

1. **初始化**：创建 ANTLR 语法分析器，准备词法单元流
2. **语法分析**：根据语法规则，递归地构建抽象语法树
3. **错误处理**：当遇到语法错误时，ANTLR4 自动报告错误并尝试恢复
4. **抽象语法树构建**：通过 ASTBuilder 将 Parse Tree 转换为 AST 节点
5. **输出**：返回构建完成的抽象语法树

## 5. 接口设计

### 5.1 输入接口
- **CommonTokenStream**：来自词法分析器的词法单元流

```cpp
// 文件：src/frontend/generated/CScriptParser.h
namespace antlr4 {
    class CommonTokenStream;
}

class CScriptParser {
public:
    CScriptParser(CommonTokenStream* tokens);
    ProgramContext* program();
};
```

### 5.2 输出接口
- **ProgramContext***：ANTLR Parse Tree 根节点

```cpp
// ANTLR 生成的 Parse Tree
class ProgramContext : public antlr4::ParserRuleContext {
public:
    std::vector<Function_declContext*> function_decl();
};
```

### 5.3 AST 构建器接口

```cpp
// 文件：src/frontend/parser/ASTBuilder.h
class ASTBuilder : public CScriptVisitor {
public:
    ASTBuilder();
    NBlock* build(CScriptParser::ProgramContext* ctx);
};
```

### 5.4 错误处理接口
- **语法错误**：当遇到语法错误时，ANTLR4 自动报告语法错误

## 6. 实现细节

### 6.1 语法规则文件

CScriptEngine使用ANTLR4工具生成语法分析器，语法规则文件为`src/frontend/parser/CScript.g4`，包含以下主要规则：

#### 程序结构
```antlr
program
    : (function_decl | var_decl | struct_decl)* EOF
    ;

function_decl
    : type_spec IDENTIFIER LPAREN param_list? RPAREN compound_stmt
    ;

var_decl
    : type_spec IDENTIFIER (ASSIGN expr)? SEMI
    | type_spec IDENTIFIER LBRACKET INTEGER? RBRACKET (ASSIGN LBRACE expr_list? RBRACE)? SEMI
    ;
```

#### 类型说明符
```antlr
type_spec
    : INT
    | DOUBLE
    | CHAR
    | BOOL
    | VOID
    | FLOAT
    | LONG
    | SHORT
    | UNSIGNED
    | IDENTIFIER
    ;
```

#### 语句
```antlr
compound_stmt
    : LBRACE (var_decl | statement)* RBRACE
    ;

statement
    : expr_stmt
    | compound_stmt
    | selection_stmt
    | iteration_stmt
    | jump_stmt
    ;

selection_stmt
    : IF LPAREN expr RPAREN statement (ELSE statement)?
    | SWITCH LPAREN expr RPAREN statement
    ;

iteration_stmt
    : WHILE LPAREN expr RPAREN statement
    | FOR LPAREN expr? SEMI expr? SEMI expr? RPAREN statement
    | DO statement WHILE LPAREN expr RPAREN SEMI
    ;

jump_stmt
    : RETURN expr? SEMI
    | BREAK SEMI
    | CONTINUE SEMI
    | GOTO IDENTIFIER SEMI
    ;
```

#### 表达式
```antlr
expr
    : assignment_expr
    ;

assignment_expr
    : conditional_expr
    | unary_expr ASSIGN assignment_expr
    | unary_expr ADD_ASSIGN assignment_expr
    | unary_expr SUB_ASSIGN assignment_expr
    // ... 其他赋值运算符
    ;

conditional_expr
    : logical_or_expr (QUESTION expr COLON conditional_expr)?
    ;

logical_or_expr
    : logical_and_expr (OR logical_and_expr)*
    ;

logical_and_expr
    : bitwise_or_expr (AND bitwise_or_expr)*
    ;
```

### 6.2 生成的语法分析器

ANTLR4工具根据语法规则文件生成语法分析器代码，主要文件为：
- `src/frontend/generated/CScriptParser.h`：生成的语法分析器头文件
- `src/frontend/generated/CScriptParser.cpp`：生成的语法分析器实现
- `src/frontend/generated/CScriptBaseVisitor.h`：访问者模式基类
- `src/frontend/generated/CScriptVisitor.h`：访问者模式接口

### 6.3 抽象语法树节点

抽象语法树节点定义在`src/frontend/parser/node.h`中，每个节点类型都有对应的类。

```cpp
// 文件：src/frontend/parser/node.h
class NBlock : public Node {
public:
    std::vector<NStatement*> statements;
};

class NFunctionDeclaration : public NStatement {
public:
    NIdentifier type;
    NIdentifier id;
    VariableList arguments;
    NBlock* block;
};

class NVariableDeclaration : public NStatement {
public:
    NIdentifier type;
    NIdentifier id;
    NExpression* assignmentExpr;
};
```

### 6.4 AST 构建器

ASTBuilder 继承自 ANTLR4 的 CScriptVisitor，负责将 Parse Tree 转换为 AST：

```cpp
// 文件：src/frontend/parser/ASTBuilder.h
class ASTBuilder : public CScriptVisitor {
public:
    std::any visitProgram(CScriptParser::ProgramContext* ctx) override;
    std::any visitFunction_decl(CScriptParser::Function_declContext* ctx) override;
    std::any visitVar_decl(CScriptParser::Var_declContext* ctx) override;
    std::any visitStatement(CScriptParser::StatementContext* ctx) override;
    std::any visitExpr(CScriptParser::ExprContext* ctx) override;
    // ... 其他访问方法
};
```

### 6.5 集成到编译器

语法分析器与词法分析器和语义分析器集成：

```cpp
// 文件：src/CScriptEngine.cpp
#ifdef USE_ANTLR
// 1. 创建输入流
antlr4::ANTLRInputStream input(buffer.data(), size);

// 2. 创建词法分析器
CScriptLexer lexer(&input);

// 3. 创建 token 流
antlr4::CommonTokenStream tokens(&lexer);

// 4. 创建语法分析器
CScriptParser parser(&tokens);

// 5. 获取解析树
auto tree = parser.program();

// 6. 构建 AST
ASTBuilder builder;
programBlock = builder.build(tree);
#endif
```

## 7. 测试策略

### 7.1 测试用例

- **函数声明测试**：测试各种函数声明的解析
- **变量声明测试**：测试各种变量声明的解析
- **表达式测试**：测试各种表达式的解析
- **语句测试**：测试条件语句、循环语句的解析
- **嵌套结构测试**：测试嵌套的代码块
- **错误处理测试**：测试语法错误输入的处理

### 7.2 测试方法

- **单元测试**：测试语法分析器的各个组件
- **集成测试**：测试语法分析器与词法分析器、语义分析器的集成
- **回归测试**：确保修改不会破坏现有功能

### 7.3 语法分析测试用例

```c
// 测试函数声明
int add(int a, int b) {
    return a + b;
}

// 测试变量声明
int x = 5;
double arr[10] = {1, 2, 3};

// 测试表达式
x = (a + b) * c - d / e % f;

// 测试条件语句
if (x > 0) {
    x = x - 1;
} else {
    x = x + 1;
}

// 测试循环语句
while (x > 0) {
    x = x - 1;
}

// 测试 for 循环
for (int i = 0; i < 10; i++) {
    sum = sum + i;
}
```

## 8. 迁移历史

### 8.1 Bison 到 ANTLR4 迁移

| 项目 | 旧方案 (Bison) | 新方案 (ANTLR4) |
|------|---------------|-----------------|
| 语法规则 | `pre/parser.y` | `src/frontend/parser/CScript.g4` |
| 生成文件 | `src/flex_bison/*` | `src/frontend/generated/*` |
| AST 构建 | Bison 内置 | `ASTBuilder` 访问者类 |
| 错误处理 | Bison 错误恢复 | ANTLR4 错误处理 |

### 8.2 迁移原因

1. **统一语法描述**：ANTLR4 使用单个语法文件同时定义词法和语法规则
2. **更好的错误处理**：ANTLR4 提供更友好的错误消息
3. **访问者模式**：ANTLR4 内置访问者模式，方便 AST 构建
4. **多语言支持**：ANTLR4 支持生成多种目标语言的代码

## 9. 参考资料

- [ANTLR4 官方文档](https://www.antlr.org/)
- [ANTLR4 语法文件参考](https://github.com/antlr/antlr4/blob/master/doc/index.md)
- [CScriptEngine 语法文件](../frontend/parser/CScript.g4)
- [AST 构建器实现](../frontend/parser/ASTBuilder.h)
