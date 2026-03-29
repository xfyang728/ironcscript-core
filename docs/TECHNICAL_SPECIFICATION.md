# CScriptEngine 技术规范文档

## 1. API设计规范

### 1.1 设计原则

- **模块化**：每个模块应具有单一职责，接口清晰
- **可扩展性**：设计应支持未来功能扩展
- **向后兼容**：API变更应保持向后兼容
- **性能优先**：API设计应考虑执行效率
- **类型安全**：使用强类型接口，避免隐式类型转换

### 1.2 命名约定

| 元素 | 命名规则 | 示例 |
|------|----------|------|
| 类名 | PascalCase | `X64Code`, `SemanticAnalyzer` |
| 方法名 | PascalCase | `GenerateCode`, `AnalyzeExpression` |
| 成员变量 | m_前缀 + camelCase | `m_CodeBuffer`, `m_VariableOffsets` |
| 局部变量 | camelCase | `quadList`, `byteOffset` |
| 常量 | ALL_CAPS | `MAX_CODE_SIZE`, `PAGE_SIZE` |
| 枚举 | PascalCase | `ControlFlowOps`, `OpEnum` |
| 命名空间 | lowercase | `cse` |

### 1.3 接口设计

#### 1.3.1 类接口

- **构造函数**：应提供默认构造函数和必要的参数构造函数
- **析构函数**：对于资源管理类，应实现析构函数或使用智能指针
- **方法参数**：
  - 输入参数：使用const引用或值传递
  - 输出参数：使用引用或指针
  - 可选参数：使用默认值

#### 1.3.2 错误处理

- **异常**：使用异常处理错误情况
- **错误码**：对于性能敏感代码，可使用错误码
- **错误消息**：提供清晰的错误消息

### 1.4 API文档

- 每个类和方法应提供Doxygen风格的文档
- 文档应包括：
  - 功能描述
  - 参数说明
  - 返回值说明
  - 异常说明
  - 示例代码

## 2. 编码风格指南

### 2.1 缩进和空格

- **缩进**：4个空格（不使用Tab）
- **行宽**：每行不超过100个字符
- **空格**：
  - 操作符两侧使用空格：`a + b` 而非 `a+b`
  - 逗号后使用空格：`func(a, b)` 而非 `func(a,b)`
  - 大括号前使用空格：`if (condition) {` 而非 `if (condition){`

### 2.2 代码组织

- **文件结构**：
  - 头文件（.h）：声明和接口定义
  - 源文件（.cpp）：实现
- **包含顺序**：
  1. 系统头文件（#include <...>）
  2. 第三方库头文件
  3. 项目头文件（#include "..."）
- **命名空间**：使用命名空间组织代码，避免全局命名冲突

### 2.3 注释规范

- **文件头部**：每个文件应包含版权和功能描述
- **类注释**：每个类应说明其功能和使用方法
- **方法注释**：每个方法应说明其功能、参数和返回值
- **行内注释**：复杂逻辑应添加行内注释
- **注释风格**：使用 `//` 进行单行注释，`/* */` 进行多行注释

### 2.4 代码风格示例

```cpp
// 文件头部注释
/**
 * @file X64Code.cpp
 * @brief x64机器码生成器实现
 */

namespace cse {

/**
 * @class X64Code
 * @brief x64平台机器码生成器
 */
class X64Code : public Code {
private:
    std::vector<unsigned char> m_CodeBuffer;  // 代码缓冲区
    std::map<std::string, int> m_VariableOffsets;  // 变量偏移量

public:
    /**
     * @brief 生成IR代码
     * @param quadList 四元式列表
     */
    void generateCodeFromIR(const std::list<Quad>& quadList) {
        // 实现代码
        for (const auto& quad : quadList) {
            // 处理每个四元式
        }
    }
};

}
```

### 2.5 性能优化

- **内存管理**：使用智能指针和RAII原则
- **避免重复计算**：缓存计算结果
- **算法选择**：选择适当的算法和数据结构
- **内联函数**：对于频繁调用的小函数使用inline
- **避免虚函数**：性能敏感代码应避免虚函数开销

### 2.6 安全规范

- **内存安全**：避免内存泄漏和缓冲区溢出
- **类型安全**：使用强类型，避免类型转换错误
- **异常安全**：确保异常情况下资源正确释放
- **输入验证**：验证所有外部输入

## 3. 测试标准

### 3.1 测试类型

| 测试类型 | 描述 | 示例 |
|----------|------|------|
| 单元测试 | 测试单个函数或类 | `test_add_function` |
| 集成测试 | 测试模块间交互 | `test_parser_ir_integration` |
| 功能测试 | 测试完整功能 | `test_factorial_function` |
| 性能测试 | 测试性能指标 | `test_execution_speed` |
| 回归测试 | 测试修复后的问题 | `test_bug_fix_123` |

### 3.2 测试覆盖范围

- **语句覆盖**：至少80%的代码行被测试
- **分支覆盖**：至少70%的分支被测试
- **路径覆盖**：关键路径应被测试
- **异常覆盖**：异常处理应被测试

### 3.3 测试命名规范

- **测试文件**：`test_<module>.<extension>`
- **测试函数**：`test_<feature>_<scenario>`
- **测试类**：`Test<Module>`

### 3.4 测试框架

- 使用Google Test或Catch2测试框架
- 测试应独立运行，无依赖关系
- 测试应可重复执行，结果一致

### 3.5 测试执行

- **自动化测试**：集成到CI/CD流程
- **测试报告**：生成详细的测试报告
- **测试覆盖率**：使用工具测量测试覆盖率

### 3.6 测试用例示例

```cpp
// test_arithmetic.cpp
#include "gtest/gtest.h"
#include "CScriptEngine.h"

TEST(ArithmeticTest, AddFunction) {
    // 测试加法函数
    const char* script = R"(
        int add(int a, int b) {
            return a + b;
        }
        int main() {
            return add(10, 20);
        }
    )";
    
    CScriptEngine engine;
    int result = engine.executeString(script);
    EXPECT_EQ(result, 30);
}

TEST(ArithmeticTest, SubtractFunction) {
    // 测试减法函数
    const char* script = R"(
        int subtract(int a, int b) {
            return a - b;
        }
        int main() {
            return subtract(20, 10);
        }
    )";
    
    CScriptEngine engine;
    int result = engine.executeString(script);
    EXPECT_EQ(result, 10);
}
```

## 4. 代码审查标准

### 4.1 审查要点

- **代码质量**：代码是否清晰、简洁、可维护
- **功能正确性**：代码是否实现预期功能
- **性能**：代码是否高效
- **安全性**：代码是否安全，无漏洞
- **一致性**：代码是否符合编码规范

### 4.2 审查流程

1. **提交前检查**：开发者自我检查
2. **代码审查**：团队成员审查
3. **测试验证**：运行测试确保无回归
4. **合并**：通过审查后合并代码

### 4.3 审查工具

- **静态分析**：使用静态分析工具检查代码
- **代码风格检查**：使用工具检查编码风格
- **测试覆盖率**：检查测试覆盖情况

## 5. 版本控制规范

### 5.1 分支管理

- **main**：稳定版本分支
- **develop**：开发分支
- **feature/**：功能分支
- **bugfix/**：bug修复分支
- **release/**：发布分支

### 5.2 提交规范

- **提交消息**：清晰描述变更内容
- **提交粒度**：每个提交应专注于一个功能或修复
- **提交频率**：频繁提交，保持提交体积小

### 5.3 版本号规范

- 使用语义化版本号：`MAJOR.MINOR.PATCH`
- **MAJOR**：不兼容的API变更
- **MINOR**：向后兼容的功能添加
- **PATCH**：向后兼容的bug修复

## 6. 文档规范

### 6.1 架构文档

- **ARCHITECTURE.md**：系统架构设计
- **README.md**：项目说明和使用指南
- **CHANGELOG.md**：版本变更记录

### 6.2 API文档

- 使用Doxygen生成API文档
- 文档应包括：
  - 模块说明
  - 类和方法说明
  - 示例代码
  - 常见问题

### 6.3 开发文档

- **CONTRIBUTING.md**：贡献指南
- **CODE_OF_CONDUCT.md**：行为准则
- **STYLE_GUIDE.md**：编码风格指南

## 7. 执行流程

### 7.1 开发流程

1. **需求分析**：分析功能需求
2. **架构设计**：设计系统架构
3. **详细设计**：设计模块和接口
4. **代码实现**：按照规范实现代码
5. **测试**：编写和运行测试
6. **代码审查**：团队审查代码
7. **集成**：集成到主分支
8. **发布**：发布版本

### 7.2 AI辅助开发流程

1. **架构设计**：使用AI辅助设计架构
2. **代码生成**：基于架构生成代码
3. **代码审查**：审查AI生成的代码
4. **测试**：运行测试验证功能
5. **优化**：优化生成的代码

## 8. 结论

本技术规范旨在为CScriptEngine项目提供统一的开发标准，确保代码质量和可维护性。所有开发人员应遵循本规范进行开发，以保持代码的一致性和高质量。

规范应根据项目发展和技术进步定期更新，确保其与项目需求和最佳实践保持一致。