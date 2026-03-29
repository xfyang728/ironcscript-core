# 中间代码生成设计

## 1. 模块概述

中间代码生成器是CScriptEngine的后端组件，负责将经过语义分析的抽象语法树转换为中间代码（四元式）。它是编译器的第四个阶段，为后续的目标代码生成提供输入。

## 2. 设计原理

中间代码生成器通过遍历抽象语法树，为每个节点生成对应的中间代码（四元式）。中间代码是一种与目标平台无关的代码表示形式，便于后续的优化和目标代码生成。

## 3. 数据结构

### 3.1 四元式（Quad）

四元式是CScriptEngine使用的中间代码表示形式，包含以下字段：
- **操作码**：操作类型
- **操作数1**：第一个操作数
- **操作数2**：第二个操作数
- **结果**：操作结果

#### 3.1.1 操作码列表

| 操作码 | 描述 | 示例 |
|--------|------|------|
| ADD | 加法 | `ADD a b t0` |
| SUB | 减法 | `SUB a b t0` |
| MUL | 乘法 | `MUL a b t0` |
| DIV | 除法 | `DIV a b t0` |
| MOD | 取模 | `MOD a b t0` |
| EQ | 等于 | `EQ a b t0` |
| NE | 不等于 | `NE a b t0` |
| LT | 小于 | `LT a b t0` |
| LE | 小于等于 | `LE a b t0` |
| GT | 大于 | `GT a b t0` |
| GE | 大于等于 | `GE a b t0` |
| ASSIGN | 赋值 | `ASSIGN a b t0` |
| JMP | 无条件跳转 | `JMP label` |
| JMPF | 条件假跳转 | `JMPF t0 label` |
| JMPT | 条件真跳转 | `JMPT t0 label` |
| CALL | 函数调用 | `CALL func n` |
| PARAM | 参数传递 | `PARAM arg` |
| RET | 返回 | `RET` |
| RETURN | 返回值 | `RETURN t0` |
| LABEL | 标签定义 | `LABEL label` |
| FUNC | 函数定义 | `FUNC main` |
| ENDFUNC | 函数结束 | `ENDFUNC main` |
| XOR | 异或 | `XOR a b t0` |
| AND | 与 | `AND a b t0` |
| OR | 或 | `OR a b t0` |
| NOT | 非 | `NOT a t0` |
| LSHIFT | 左移 | `LSHIFT a b t0` |
| RSHIFT | 右移 | `RSHIFT a b t0` |
| LOGICAL_AND | 逻辑与 | `LOGICAL_AND a b t0` |
| LOGICAL_OR | 逻辑或 | `LOGICAL_OR a b t0` |
| LOGICAL_NOT | 逻辑非 | `LOGICAL_NOT a t0` |
| SWITCH | 开关语句 | `SWITCH t0` |
| CASE |  case 语句 | `CASE 1 label` |
| DEFAULT | 默认 case | `DEFAULT label` |
| ARRAY | 数组定义 | `ARRAY arr size` |
| ARRAY_LOAD | 数组加载 | `ARRAY_LOAD arr idx t0` |
| ARRAY_STORE | 数组存储 | `ARRAY_STORE arr idx val` |
| ADDRESS_OF | 取地址 | `ADDRESS_OF var t0` |
| DEREFERENCE | 解引用 | `DEREFERENCE ptr t0` |
| STORE_DEREFERENCE | 存储解引用 | `STORE_DEREFERENCE ptr val` |
| CAST | 类型转换 | `CAST t0 t1` |
| SET_AL | 设置 AL 寄存器 | `SET_AL t0` |
| STRING_CONCAT | 字符串连接 | `STRING_CONCAT s1 s2 t0` |
| MEMBER_ACCESS | 成员访问 | `MEMBER_ACCESS struct member t0` |
| MEMBER_STORE | 成员存储 | `MEMBER_STORE struct member val`

### 3.2 临时变量

临时变量用于存储中间计算结果，由中间代码生成器自动生成。

### 3.3 标签

标签用于控制流语句（如if、while、for等）的跳转目标。

## 4. 算法流程

1. **初始化**：准备抽象语法树，设置初始状态
2. **遍历抽象语法树**：递归遍历抽象语法树的每个节点
3. **生成四元式**：为每个节点生成对应的四元式
4. **临时变量管理**：生成和管理临时变量
5. **标签管理**：生成和管理控制流标签
6. **输出**：返回生成的中间代码

## 5. 接口设计

### 5.1 输入接口
- **经过语义分析的抽象语法树**：来自语义分析器的输出

### 5.2 输出接口
- **中间代码（四元式）**：作为目标代码生成器的输入

### 5.3 错误处理接口
- **生成错误**：当遇到无法生成中间代码的情况时，报告错误

## 6. 实现细节

### 6.1 四元式生成

四元式生成包括：
- **表达式四元式**：为表达式生成对应的四元式
- **语句四元式**：为语句生成对应的四元式
- **控制流四元式**：为控制流语句生成对应的四元式
- **函数调用四元式**：为函数调用生成对应的四元式

### 6.2 临时变量管理

临时变量管理包括：
- **临时变量生成**：生成唯一的临时变量名
- **临时变量分配**：为临时变量分配存储空间
- **临时变量释放**：在不需要时释放临时变量

### 6.3 标签管理

标签管理包括：
- **标签生成**：生成唯一的标签名
- **标签使用**：在控制流语句中使用标签
- **标签解析**：解析标签的跳转目标

### 6.4 集成到编译器

中间代码生成器与语义分析器和目标代码生成器集成，接收经过语义分析的抽象语法树，生成中间代码后传递给目标代码生成器。

## 7. 测试策略

### 7.1 测试用例

- **表达式测试**：测试表达式的中间代码生成
- **语句测试**：测试语句的中间代码生成
- **控制流测试**：测试控制流语句的中间代码生成
- **函数调用测试**：测试函数调用的中间代码生成
- **集成测试**：测试中间代码生成器与其他组件的集成

### 7.2 测试方法

- **单元测试**：测试中间代码生成器的各个组件
- **集成测试**：测试中间代码生成器与其他组件的集成
- **回归测试**：确保修改不会破坏现有功能