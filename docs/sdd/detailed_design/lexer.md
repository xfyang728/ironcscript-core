# 词法分析器设计

## 1. 模块概述

词法分析器是CScriptEngine的前端组件，负责将源代码文本转换为词法单元（tokens）流。它是编译器的第一个阶段，为后续的语法分析提供输入。

## 2. 设计原理

词法分析器使用状态机原理，根据预定义的词法规则，将输入的字符流转换为词法单元。CScriptEngine使用ANTLR4工具生成词法分析器，通过定义词法规则文件（CScript.g4）来描述如何识别不同的词法单元。

## 3. 数据结构

### 3.1 词法单元（Token）

词法单元是词法分析器的输出，包含以下信息：
- **类型**：词法单元的类型（如关键字、标识符、常量、运算符等）
- **值**：词法单元的具体值（如标识符的名称、常量的值等）
- **位置**：词法单元在源代码中的位置（行号、列号）

### 3.2 状态机

词法分析器使用有限状态机来识别词法单元，状态包括：
- **初始状态**：开始识别新的词法单元
- **标识符状态**：识别标识符和关键字
- **数字状态**：识别整数和浮点数常量
- **字符串状态**：识别字符串常量
- **注释状态**：识别注释
- **运算符状态**：识别运算符

### 3.3 ANTLR4 Token 类型

```cpp
// 生成的文件：src/frontend/generated/CScriptLexer.h
namespace antlr4 {
    class Token {
    public:
        virtual size_t getType() = 0;
        virtual std::string getText() = 0;
        virtual size_t getLine() = 0;
        virtual size_t getCharPositionInLine() = 0;
    };

    class CommonToken : public Token {
    public:
        size_t type;
        std::string text;
        size_t line;
        size_t charPositionInLine;
    };
}
```

## 4. 算法流程

1. **初始化**：创建 ANTLR 输入流，准备词法分析器
2. **词法分析**：ANTLR4 词法分析器根据语法规则自动进行状态转换
3. **Token 生成**：当识别到完整的词法单元时，生成 Token
4. **Token 流输出**：将 Token 添加到 token 流
5. **重复**：继续处理下一个字符，直到到达输入流末尾

## 5. 接口设计

### 5.1 输入接口
- **ANTLRInputStream**：ANTLR 输入流，包含源代码文本

```cpp
// 文件：src/frontend/generated/CScriptLexer.h
namespace antlr4 {
    class ANTLRInputStream {
    public:
        ANTLRInputStream(const char* data, size_t length);
    };
}
```

### 5.2 输出接口
- **CommonTokenStream**：词法单元流，作为语法分析器的输入

```cpp
// 文件：src/frontend/generated/CScriptLexer.h
namespace antlr4 {
    class CommonTokenStream {
    public:
        CommonTokenStream(Lexer* lexer);
        Token* nextToken();
    };
}
```

### 5.3 错误处理接口
- **词法错误**：当遇到无法识别的字符时，ANTLR4 自动报告词法错误

## 6. 实现细节

### 6.1 词法规则文件

CScriptEngine使用ANTLR4工具生成词法分析器，词法规则文件为`src/frontend/parser/CScript.g4`，包含以下主要规则：

#### 关键字
```antlr
// 关键字
INT:    'int';
DOUBLE: 'double';
CHAR:   'char';
BOOL:   'bool';
VOID:   'void';
IF:     'if';
ELSE:   'else';
WHILE:  'while';
FOR:    'for';
DO:     'do';
RETURN: 'return';
EXTERN: 'extern';
STRUCT: 'struct';
ENUM:   'enum';
UNION:  'union';
TYPEDEF:'typedef';
CONST:  'const';
VOLATILE: 'volatile';
SIZEOF: 'sizeof';
SWITCH: 'switch';
CASE:   'case';
DEFAULT:'default';
BREAK:  'break';
CONTINUE:'continue';
GOTO:   'goto';
STATIC: 'static';
REGISTER:'register';
AUTO:   'auto';
EXTERN: 'extern';
INLINE: 'inline';
```

#### 标识符
```antlr
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
```

#### 常量
```antlr
// 整数常量：十进制、八进制、十六进制
INTEGER: [0-9]+ | '0'[0-7]+ | '0'[xX][0-9a-fA-F]+;

// 浮点数常量：小数形式、科学计数法
DOUBLE: [0-9]*'.'[0-9]+ ([eE][+-]?[0-9]+)?;

// 字符常量：单引号包围的单个字符
CHARACTER: '\'' (~["'\\"] | '\\' .) '\'';

// 字符串常量：双引号包围的字符序列
STRING: '"' (~["\\"] | '\\' .)* '"';
```

#### 运算符
```antlr
// 算术运算符
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';

// 关系运算符
EQ: '==';
NE: '!=';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';

// 逻辑运算符
AND: '&&';
OR: '||';
NOT: '!';

// 位运算符
BITAND: '&';
BITOR: '|';
BITXOR: '^';
BITNOT: '~';
LSHIFT: '<<';
RSHIFT: '>>';

// 赋值运算符
ASSIGN: '=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';

// 自增自减
INC: '++';
DEC: '--';

// 条件运算符
QUESTION: '?';
COLON: ':';
```

#### 标点符号
```antlr
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COMMA: ',';
SEMI: ';';
DOT: '.';
ARROW: '->';
```

#### 注释
```antlr
// 单行注释
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);

// 多行注释
MULTILINE_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
```

### 6.2 生成的词法分析器

ANTLR4工具根据语法规则文件生成词法分析器代码，主要文件为：
- `src/frontend/generated/CScriptLexer.h`：生成的词法分析器头文件
- `src/frontend/generated/CScriptLexer.cpp`：生成的词法分析器实现
- `src/frontend/generated/CScriptParser.h`：生成的语法分析器头文件
- `src/frontend/generated/CScriptParser.cpp`：生成的语法分析器实现

### 6.3 集成到编译器

词法分析器与语法分析器集成，使用流程如下：

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
#endif
```

## 7. 测试策略

### 7.1 测试用例

- **关键字测试**：测试所有关键字的识别
- **标识符测试**：测试各种合法标识符的识别
- **常量测试**：测试各种类型常量的识别（整数、浮点、字符、字符串）
- **运算符测试**：测试各种运算符的识别
- **注释测试**：测试注释的正确处理
- **错误测试**：测试错误输入的处理

### 7.2 测试方法

- **单元测试**：测试词法分析器的各个组件
- **集成测试**：测试词法分析器与语法分析器的集成
- **回归测试**：确保修改不会破坏现有功能

### 7.3 词法分析测试用例

```c
// 测试关键字
int x = 5;
double y = 3.14;
char c = 'a';
while (x > 0) { x--; }

// 测试数字常量
int a = 42;        // 十进制
int b = 052;       // 八进制
int c = 0x2A;      // 十六进制
double d = 3.14e-5; // 科学计数法

// 测试字符串
char* s = "Hello, World!";

// 测试注释
// 这是一个单行注释
/* 这是一个
   多行注释 */
```

## 8. 迁移历史

### 8.1 Flex/Bison 到 ANTLR4 迁移

| 项目 | 旧方案 (Flex/Bison) | 新方案 (ANTLR4) |
|------|---------------------|-----------------|
| 词法规则 | `pre/tokens.l` | `src/frontend/parser/CScript.g4` |
| 语法规则 | `pre/parser.y` | `src/frontend/parser/CScript.g4` |
| 生成文件 | `src/flex_bison/*` | `src/frontend/generated/*` |
| 词法分析器 | `tokens.cpp` | `CScriptLexer.cpp` |
| 语法分析器 | `parser.cpp` | `CScriptParser.cpp` |

### 8.2 迁移原因

1. **统一语法描述**：ANTLR4 使用单个语法文件同时定义词法和语法规则
2. **更好的错误处理**：ANTLR4 提供更友好的错误消息
3. **多语言支持**：ANTLR4 支持生成多种目标语言的代码
4. **现代特性**：ANTLR4 支持更现代的语法描述方式

## 9. 参考资料

- [ANTLR4 官方文档](https://www.antlr.org/)
- [ANTLR4 语法文件参考](https://github.com/antlr/antlr4/blob/master/doc/index.md)
- [CScriptEngine 语法文件](../frontend/parser/CScript.g4)
