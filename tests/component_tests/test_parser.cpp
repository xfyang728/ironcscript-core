#include <gtest/gtest.h>
#include <string>
#include "antlr4-runtime.h"
#include "../src/frontend/generated/CScriptLexer.h"
#include "../src/frontend/generated/CScriptParser.h"

using namespace antlr4;

/// 辅助：解析字符串，返回 parse tree 根节点和语法错误数
struct ParseResult {
    CScriptParser::ProgramContext* ctx;
    size_t syntaxErrors;
};

static ParseResult parseString(const std::string& input) {
    ANTLRInputStream stream(input);
    CScriptLexer lexer(&stream);
    CommonTokenStream tokens(&lexer);
    CScriptParser parser(&tokens);
    auto* ctx = parser.program();
    return {ctx, parser.getNumberOfSyntaxErrors()};
}

TEST(ParserTest, SimpleFunction) {
    auto [ctx, errors] = parseString("int main() { return 1; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, VariableDeclaration) {
    auto [ctx, errors] = parseString("int main() { int x; return 0; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, VariableInitialization) {
    auto [ctx, errors] = parseString("int main() { int x = 10; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, Addition) {
    auto [ctx, errors] = parseString("int main() { int x = 10 + 20; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, Subtraction) {
    auto [ctx, errors] = parseString("int main() { int x = 10 - 20; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, Multiplication) {
    auto [ctx, errors] = parseString("int main() { int x = 10 * 20; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, Division) {
    auto [ctx, errors] = parseString("int main() { int x = 10 / 20; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, Comparison) {
    auto [ctx, errors] = parseString("int main() { int x = 10 < 20; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, IfStatement) {
    auto [ctx, errors] = parseString("int main() { if (1) { return 1; } return 0; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, IfElseStatement) {
    auto [ctx, errors] = parseString("int main() { if (1) { return 1; } else { return 0; } }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, WhileStatement) {
    auto [ctx, errors] = parseString("int main() { while (1) { return 1; } return 0; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, ForStatement) {
    auto [ctx, errors] = parseString("int main() { int i; for (i = 0; i < 10; i = i + 1) { } return i; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, FunctionCall) {
    auto [ctx, errors] = parseString("int add(int a, int b) { return a + b; } int main() { return add(1, 2); }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, NestedExpression) {
    auto [ctx, errors] = parseString("int main() { int x = (10 + 20) * 30; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, DoubleType) {
    auto [ctx, errors] = parseString("int main() { double x = 3.14; return 0; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, CharType) {
    auto [ctx, errors] = parseString("int main() { char x = 'A'; return x; }");
    EXPECT_EQ(errors, 0u);
    ASSERT_NE(ctx, nullptr);
}

TEST(ParserTest, SyntaxError) {
    auto [ctx, errors] = parseString("int main() { return }");
    EXPECT_GT(errors, 0u);  // 语法错误被检测
    (void)ctx;
}