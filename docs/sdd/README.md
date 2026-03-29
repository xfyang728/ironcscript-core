# CScriptEngine 规范驱动开发(SDD)文档

## 文档结构

本目录包含CScriptEngine项目的规范驱动开发(SDD)文档，按照标准SDD结构组织：

1. **简介** (`introduction.md`)
2. **引用文档** (`references.md`)
3. **术语定义** (`terminology.md`)
4. **AI代码生成规范宪章** (`ai_codegen_charter.md`)
5. **详细设计** (`detailed_design/`)
   - 词法分析器设计 (`detailed_design/lexer.md`)
   - 语法分析器设计 (`detailed_design/parser.md`)
   - 语义分析器设计 (`detailed_design/semantic.md`)
   - 中间代码生成设计 (`detailed_design/ir.md`)
   - 目标代码生成设计 (`detailed_design/codegen.md`)
   - JIT执行设计 (`detailed_design/jit.md`)
   - 标准库设计 (`detailed_design/stdlib.md`)
6. **接口设计** (`interface_design.md`)
7. **数据结构设计** (`data_structures.md`)
8. **算法设计** (`algorithms.md`)
9. **测试设计** (`test_design.md`)
10. **实现计划** (`implementation_plan.md`)
11. **质量保证** (`quality_assurance.md`)

## 文档维护

- 文档应与代码保持同步
- 文档更新应遵循既定的更新流程
- 文档版本应与代码版本对应

## 文档索引

- [差距分析报告](../sdd_gap_analysis.md)
- [简介](introduction.md)
- [引用文档](references.md)
- [术语定义](terminology.md)
- [AI代码生成规范宪章](ai_codegen_charter.md)
- [架构设计](architecture_design.md)
- [详细设计](detailed_design/)
- [接口设计](interface_design.md)
- [数据结构设计](data_structures.md)
- [算法设计](algorithms.md)
- [测试设计](test_design.md)
- [实现计划](implementation_plan.md)
- [质量保证](quality_assurance.md)