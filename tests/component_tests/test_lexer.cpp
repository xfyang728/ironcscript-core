#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#define TIDENTIFIER 258
#define TINTEGER 259
#define TDOUBLE 260
#define TSTRING 261
#define TCEQ 262
#define TCNE 263
#define TCLT 264
#define TCLE 265
#define TCGT 266
#define TCGE 267
#define TEQUAL 268
#define TLPAREN 269
#define TRPAREN 270
#define TLBRACE 271
#define TRBRACE 272
#define TCOMMA 273
#define TDOT 274
#define TPLUS 275
#define TMINUS 276
#define TMUL 277
#define TDIV 278
#define TRETURN 279
#define TEXTERN 280
#define TIF 281
#define TELSE 282
#define TWHILE 283
#define TFOR 284
#define TDO 285
#define TBRACKETL 286
#define TBRACKETR 287
#define TADDRESS 288
#define TTYPE 289
#define TSCOLON 290

extern int yylex();
extern FILE* yyin;
extern FILE* yyout;
extern void yyerror(const char* s);

class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {
        yyin = nullptr;
        yyout = stdout;
    }
    void TearDown() override {}

    int lexString(const char* input) {
        FILE* tempFile = fopen("temp_test_input.c", "w");
        if (!tempFile) return -1;
        fputs(input, tempFile);
        fclose(tempFile);

        tempFile = fopen("temp_test_input.c", "r");
        if (!tempFile) return -1;

        yyin = tempFile;
        int token = yylex();
        fclose(tempFile);

        remove("temp_test_input.c");
        return token;
    }
};

TEST_F(LexerTest, TestIntegerToken) {
    int token = lexString("123");
    EXPECT_EQ(token, TINTEGER) << "Integer token should be TINTEGER";
}

TEST_F(LexerTest, TestFloatToken) {
    int token = lexString("3.14");
    EXPECT_EQ(token, TDOUBLE) << "Float token should be TDOUBLE";
}

TEST_F(LexerTest, TestIdentifier) {
    int token = lexString("myvar");
    EXPECT_EQ(token, TIDENTIFIER) << "Identifier should be TIDENTIFIER";
}

TEST_F(LexerTest, TestIntKeyword) {
    int token = lexString("int");
    EXPECT_EQ(token, TTYPE) << "int keyword should be TTYPE";
}

TEST_F(LexerTest, TestDoubleKeyword) {
    int token = lexString("double");
    EXPECT_EQ(token, TTYPE) << "double keyword should be TTYPE";
}

TEST_F(LexerTest, TestCharKeyword) {
    int token = lexString("char");
    EXPECT_EQ(token, TTYPE) << "char keyword should be TTYPE";
}

TEST_F(LexerTest, TestIfKeyword) {
    int token = lexString("if");
    EXPECT_EQ(token, TIF) << "if keyword should be TIF";
}

TEST_F(LexerTest, TestElseKeyword) {
    int token = lexString("else");
    EXPECT_EQ(token, TELSE) << "else keyword should be TELSE";
}

TEST_F(LexerTest, TestWhileKeyword) {
    int token = lexString("while");
    EXPECT_EQ(token, TWHILE) << "while keyword should be TWHILE";
}

TEST_F(LexerTest, TestForKeyword) {
    int token = lexString("for");
    EXPECT_EQ(token, TFOR) << "for keyword should be TFOR";
}

TEST_F(LexerTest, TestReturnKeyword) {
    int token = lexString("return");
    EXPECT_EQ(token, TRETURN) << "return keyword should be TRETURN";
}

TEST_F(LexerTest, TestPlusOperator) {
    int token = lexString("+");
    EXPECT_EQ(token, TPLUS) << "Plus operator should be TPLUS";
}

TEST_F(LexerTest, TestMinusOperator) {
    int token = lexString("-");
    EXPECT_EQ(token, TMINUS) << "Minus operator should be TMINUS";
}

TEST_F(LexerTest, TestMultiplyOperator) {
    int token = lexString("*");
    EXPECT_EQ(token, TMUL) << "Multiply operator should be TMUL";
}

TEST_F(LexerTest, TestDivideOperator) {
    int token = lexString("/");
    EXPECT_EQ(token, TDIV) << "Divide operator should be TDIV";
}

TEST_F(LexerTest, TestEqualOperator) {
    int token = lexString("==");
    EXPECT_EQ(token, TEQUAL) << "Equal operator should be TEQUAL";
}

TEST_F(LexerTest, TestLessThanOperator) {
    int token = lexString("<");
    EXPECT_EQ(token, TCLT) << "Less than operator should be TCLT";
}

TEST_F(LexerTest, TestGreaterThanOperator) {
    int token = lexString(">");
    EXPECT_EQ(token, TCGT) << "Greater than operator should be TCGT";
}
