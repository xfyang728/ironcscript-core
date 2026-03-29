#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

extern "C" {
#include "../src/flex_bison/parser.hpp"
}

extern "C" int yyparse();
extern "C" void yyerror(const char* s);

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    bool parseString(const char* input) {
        FILE* tempFile = fopen("temp_test_input.c", "w");
        if (!tempFile) return false;
        fputs(input, tempFile);
        fclose(tempFile);

        tempFile = fopen("temp_test_input.c", "r");
        if (!tempFile) return false;

        yyin = tempFile;
        int result = yyparse();
        fclose(tempFile);

        remove("temp_test_input.c");
        return (result == 0);
    }
};

TEST_F(ParserTest, TestSimpleExpression) {
    bool result = parseString("int main() { return 1; }");
    EXPECT_TRUE(result) << "Simple expression should parse successfully";
}

TEST_F(ParserTest, TestVariableDeclaration) {
    bool result = parseString("int main() { int x; return 0; }");
    EXPECT_TRUE(result) << "Variable declaration should parse successfully";
}

TEST_F(ParserTest, TestVariableInitialization) {
    bool result = parseString("int main() { int x = 10; return x; }");
    EXPECT_TRUE(result) << "Variable initialization should parse successfully";
}

TEST_F(ParserTest, TestAddition) {
    bool result = parseString("int main() { int x = 10 + 20; return x; }");
    EXPECT_TRUE(result) << "Addition should parse successfully";
}

TEST_F(ParserTest, TestSubtraction) {
    bool result = parseString("int main() { int x = 10 - 20; return x; }");
    EXPECT_TRUE(result) << "Subtraction should parse successfully";
}

TEST_F(ParserTest, TestMultiplication) {
    bool result = parseString("int main() { int x = 10 * 20; return x; }");
    EXPECT_TRUE(result) << "Multiplication should parse successfully";
}

TEST_F(ParserTest, TestDivision) {
    bool result = parseString("int main() { int x = 10 / 20; return x; }");
    EXPECT_TRUE(result) << "Division should parse successfully";
}

TEST_F(ParserTest, TestComparison) {
    bool result = parseString("int main() { int x = 10 < 20; return x; }");
    EXPECT_TRUE(result) << "Comparison should parse successfully";
}

TEST_F(ParserTest, TestIfStatement) {
    bool result = parseString("int main() { if (1) { return 1; } return 0; }");
    EXPECT_TRUE(result) << "If statement should parse successfully";
}

TEST_F(ParserTest, TestIfElseStatement) {
    bool result = parseString("int main() { if (1) { return 1; } else { return 0; } }");
    EXPECT_TRUE(result) << "If-else statement should parse successfully";
}

TEST_F(ParserTest, TestWhileStatement) {
    bool result = parseString("int main() { while (1) { return 1; } return 0; }");
    EXPECT_TRUE(result) << "While statement should parse successfully";
}

TEST_F(ParserTest, TestForStatement) {
    bool result = parseString("int main() { int i; for (i = 0; i < 10; i = i + 1) { } return i; }");
    EXPECT_TRUE(result) << "For statement should parse successfully";
}

TEST_F(ParserTest, TestFunctionCall) {
    bool result = parseString("int add(int a, int b) { return a + b; } int main() { return add(1, 2); }");
    EXPECT_TRUE(result) << "Function call should parse successfully";
}

TEST_F(ParserTest, TestNestedExpression) {
    bool result = parseString("int main() { int x = (10 + 20) * 30; return x; }");
    EXPECT_TRUE(result) << "Nested expression should parse successfully";
}

TEST_F(ParserTest, TestDoubleType) {
    bool result = parseString("int main() { double x = 3.14; return 0; }");
    EXPECT_TRUE(result) << "Double type should parse successfully";
}

TEST_F(ParserTest, TestCharType) {
    bool result = parseString("int main() { char x = 'A'; return x; }");
    EXPECT_TRUE(result) << "Char type should parse successfully";
}

TEST_F(ParserTest, TestBoolType) {
    bool result = parseString("int main() { bool x = 1; return x; }");
    EXPECT_TRUE(result) << "Bool type should parse successfully";
}
