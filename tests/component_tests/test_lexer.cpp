#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "antlr4-runtime.h"
#include "../src/frontend/generated/CScriptLexer.h"
#include "../src/frontend/generated/CScriptParser.h"

using namespace antlr4;

/// 辅助：对输入字符串进行词法分析，返回 token 列表
static std::vector<Token*> lexString(const std::string& input) {
    ANTLRInputStream stream(input);
    CScriptLexer lexer(&stream);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    return tokens.getTokens();
}

TEST(LexerTest, IntegerToken) {
    auto tokens = lexString("123");
    ASSERT_EQ(tokens.size(), 2u);  // INTEGER + EOF
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::INTEGER);
    EXPECT_EQ(tokens[0]->getText(), "123");
}

TEST(LexerTest, DoubleToken) {
    auto tokens = lexString("3.14");
    ASSERT_GE(tokens.size(), 1u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::DOUBLE);
    EXPECT_EQ(tokens[0]->getText(), "3.14");
}

TEST(LexerTest, IdentifierToken) {
    auto tokens = lexString("myVar");
    ASSERT_GE(tokens.size(), 1u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::IDENTIFIER);
    EXPECT_EQ(tokens[0]->getText(), "myVar");
}

TEST(LexerTest, TypeKeywordsAreIdentifiers) {
    // 类型关键字（int/double/char/bool）在 g4 中通过 type 规则定义，
    // lexer 将它们识别为 IDENTIFIER token，由 parser 判断文本
    auto tokens = lexString("int double char bool");
    ASSERT_GE(tokens.size(), 4u);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(tokens[i]->getType(), CScriptParser::IDENTIFIER)
            << "Token " << i << " should be IDENTIFIER";
    }
    EXPECT_EQ(tokens[0]->getText(), "int");
    EXPECT_EQ(tokens[1]->getText(), "double");
    EXPECT_EQ(tokens[2]->getText(), "char");
    EXPECT_EQ(tokens[3]->getText(), "bool");
}

TEST(LexerTest, KeywordTokens) {
    auto tokens = lexString("if else while for return");
    ASSERT_GE(tokens.size(), 5u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::IF);
    EXPECT_EQ(tokens[1]->getType(), CScriptParser::ELSE);
    EXPECT_EQ(tokens[2]->getType(), CScriptParser::WHILE);
    EXPECT_EQ(tokens[3]->getType(), CScriptParser::FOR);
    EXPECT_EQ(tokens[4]->getType(), CScriptParser::RETURN);
}

TEST(LexerTest, ArithmeticOperators) {
    auto tokens = lexString("+ - * /");
    ASSERT_GE(tokens.size(), 4u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::PLUS);
    EXPECT_EQ(tokens[1]->getType(), CScriptParser::MINUS);
    EXPECT_EQ(tokens[2]->getType(), CScriptParser::MUL);
    EXPECT_EQ(tokens[3]->getType(), CScriptParser::DIV);
}

TEST(LexerTest, ComparisonOperators) {
    auto tokens = lexString("== < >");
    ASSERT_GE(tokens.size(), 3u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::EQ);
    EXPECT_EQ(tokens[1]->getType(), CScriptParser::LT);
    EXPECT_EQ(tokens[2]->getType(), CScriptParser::GT);
}

TEST(LexerTest, AssignmentOperator) {
    auto tokens = lexString("=");
    ASSERT_GE(tokens.size(), 1u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::ASSIGN);
}

TEST(LexerTest, StringAndCharLiterals) {
    auto tokens = lexString("\"hello\" 'A'");
    ASSERT_GE(tokens.size(), 2u);
    EXPECT_EQ(tokens[0]->getType(), CScriptParser::STRING);
    EXPECT_EQ(tokens[1]->getType(), CScriptParser::CHAR);
}

TEST(LexerTest, EofToken) {
    auto tokens = lexString("123");
    ASSERT_GE(tokens.size(), 2u);
    EXPECT_EQ(tokens.back()->getType(), Token::EOF);
}