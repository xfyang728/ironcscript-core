# 3. 术语定义

## 3.1 项目专用术语

| 术语 | 定义 |
|------|------|
| CScriptEngine | 本项目开发的C语言脚本引擎 |
| JIT | Just-In-Time，即时编译技术，将源代码或中间代码在运行时转换为机器码并立即执行 |
| AST | Abstract Syntax Tree，抽象语法树，表示程序的语法结构 |
| IR | Intermediate Representation，中间表示，编译器在前端和后端之间使用的代码表示形式 |
| Quad | 四元式，CScriptEngine使用的中间代码表示形式 |
| ANTLR4 | Another Tool for Language Recognition，用于生成词法分析器和语法分析器的工具 |
| SDD | Software Design Description，软件设计文档 |
| Symbol | 符号，表示变量、函数等程序元素的数据结构 |
| BuiltinFunction | 内置函数，编译器直接支持的标准库函数 |

## 3.2 技术术语

| 术语 | 定义 |
|------|------|
| 词法分析 | 将源代码文本转换为词法单元（tokens）的过程 |
| 语法分析 | 将词法单元流转换为抽象语法树（AST）的过程 |
| 语义分析 | 对抽象语法树进行分析，检查语义正确性的过程 |
| 中间代码生成 | 将抽象语法树转换为中间表示（IR）的过程 |
| 目标代码生成 | 将中间表示转换为目标平台机器码的过程 |
| 寄存器分配 | 为变量和临时值分配寄存器的过程 |
| 指令选择 | 选择合适的机器指令来实现中间代码的过程 |
| 符号表 | 存储程序中变量、函数等符号信息的数据结构 |
| 作用域 | 变量和函数可见的代码区域 |
| 类型检查 | 检查表达式和语句的类型是否正确的过程 |

## 3.3 缩写词

| 缩写 | 全称 | 定义 |
|------|------|------|
| SDD | Software Design Description | 软件设计文档 |
| JIT | Just-In-Time | 即时编译 |
| AST | Abstract Syntax Tree | 抽象语法树 |
| IR | Intermediate Representation | 中间表示 |
| CPU | Central Processing Unit | 中央处理器 |
| RAM | Random Access Memory | 随机存取存储器 |
| ROM | Read-Only Memory | 只读存储器 |
| API | Application Programming Interface | 应用程序编程接口 |
| ISO | International Organization for Standardization | 国际标准化组织 |
| IEC | International Electrotechnical Commission | 国际电工委员会 |
| IEEE | Institute of Electrical and Electronics Engineers | 电气电子工程师协会