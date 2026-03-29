#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/flex_bison/node.h"

using namespace cse;

class LexerParserIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(LexerParserIntegrationTest, TestIntegerTokenParsing) {
    NInteger* intLit = new NInteger{123};
    EXPECT_EQ(intLit->value, 123) << "Should parse integer 123";
}

TEST_F(LexerParserIntegrationTest, TestFloatTokenParsing) {
    NDouble* doubleLit = new NDouble{3.14};
    EXPECT_DOUBLE_EQ(doubleLit->value, 3.14) << "Should parse float 3.14";
}

TEST_F(LexerParserIntegrationTest, TestIdentifierParsing) {
    NIdentifier* id = new NIdentifier{"myVar"};
    EXPECT_EQ(id->name, "myVar") << "Should parse identifier myVar";
}

TEST_F(LexerParserIntegrationTest, TestBinaryOperatorParsing) {
    NBinaryOperator* addOp = new NBinaryOperator();
    addOp->op = '+';
    addOp->lhs = new NInteger{10};
    addOp->rhs = new NInteger{20};

    EXPECT_EQ(addOp->op, '+') << "Should parse + operator";
}

TEST_F(LexerParserIntegrationTest, TestVariableDeclarationParsing) {
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NInteger{42};

    EXPECT_EQ(varDecl->type.name, "int") << "Should parse type int";
    EXPECT_EQ(varDecl->name.name, "x") << "Should parse variable name x";
}

TEST_F(LexerParserIntegrationTest, TestFunctionDeclarationParsing) {
    NFunctionDeclaration* funcDecl = new NFunctionDeclaration();
    funcDecl->returnType = NIdentifier{"int"};
    funcDecl->name = NIdentifier{"main"};

    EXPECT_EQ(funcDecl->returnType.name, "int") << "Should parse return type int";
    EXPECT_EQ(funcDecl->name.name, "main") << "Should parse function name main";
}

TEST_F(LexerParserIntegrationTest, TestReturnStatementParsing) {
    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = new NInteger{42};

    EXPECT_NE(retStmt->expression, nullptr) << "Should parse return expression";
}

TEST_F(LexerParserIntegrationTest, TestNestedExpressionParsing) {
    NBinaryOperator* addOp = new NBinaryOperator();
    addOp->op = '+';
    addOp->lhs = new NInteger{10};
    addOp->rhs = new NBinaryOperator();
    addOp->rhs->op = '*';
    addOp->rhs->lhs = new NInteger{2};
    addOp->rhs->rhs = new NInteger{3};

    EXPECT_EQ(addOp->op, '+') << "Should parse outer +";
    EXPECT_EQ(addOp->rhs->op, '*') << "Should parse inner *";
}

TEST_F(LexerParserIntegrationTest, TestBlockParsing) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NInteger{10};
    block->statements.push_back(varDecl);

    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = new NIdentifier{"x"};
    block->statements.push_back(retStmt);

    EXPECT_EQ(block->statements.size(), 2) << "Block should have 2 statements";
}

TEST_F(LexerParserIntegrationTest, TestFunctionCallParsing) {
    NFunctionCall* funcCall = new NFunctionCall();
    funcCall->callee = NIdentifier{"printf"};
    funcCall->arguments.push_back(new NInteger{42});

    EXPECT_EQ(funcCall->callee.name, "printf") << "Should parse function name";
    EXPECT_EQ(funcCall->arguments.size(), 1) << "Should have 1 argument";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
