#include <gtest/gtest.h>
#include <string>
#include "../common/AstPool.h"
#include "../common/AstBuilders.h"
#include "../src/frontend/parser/node.h"

using namespace cse;

TEST(LexerParserIntegrationTest, IntegerTokenParsing) {
    cse_test::AstPool pool;
    auto* intLit = pool.make<NInteger>(123);
    EXPECT_EQ(intLit->value, 123);
}

TEST(LexerParserIntegrationTest, FloatTokenParsing) {
    cse_test::AstPool pool;
    auto* doubleLit = pool.make<NDouble>(3.14);
    EXPECT_DOUBLE_EQ(doubleLit->value, 3.14);
}

TEST(LexerParserIntegrationTest, IdentifierParsing) {
    cse_test::AstPool pool;
    auto& id = cse_test::makeIdent(pool, "myVar");
    EXPECT_EQ(id.name, "myVar");
}

TEST(LexerParserIntegrationTest, BinaryOperatorParsing) {
    cse_test::AstPool pool;
    auto* lhs = pool.make<NInteger>(10);
    auto* rhs = pool.make<NInteger>(20);
    // NBinaryOperator 引用成员，必须用构造函数
    auto* addOp = pool.make<NBinaryOperator>(*lhs, '+', *rhs);
    EXPECT_EQ(addOp->op, '+');
}

TEST(LexerParserIntegrationTest, VariableDeclarationParsing) {
    cse_test::AstPool pool;
    auto* expr = pool.make<NInteger>(42);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x", expr);
    // NVariableDeclaration.id 是引用，访问 .id.name
    EXPECT_EQ(varDecl->id.name, "x");
    EXPECT_EQ(varDecl->type.name, "int");
    EXPECT_NE(varDecl->assignmentExpr, nullptr);
}

TEST(LexerParserIntegrationTest, FunctionDeclarationParsing) {
    cse_test::AstPool pool;
    auto* block = cse_test::makeFuncBody(pool);
    auto* funcDecl = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, block);
    EXPECT_EQ(funcDecl->id.name, "main");
    EXPECT_EQ(funcDecl->type.name, "int");
}

TEST(LexerParserIntegrationTest, ReturnStatementParsing) {
    cse_test::AstPool pool;
    auto* expr = pool.make<NInteger>(42);
    auto* retStmt = pool.make<NReturnStatement>(*expr);
    EXPECT_NE(&retStmt->expression, nullptr);
}

TEST(LexerParserIntegrationTest, NestedExpressionParsing) {
    cse_test::AstPool pool;
    auto* lhs = pool.make<NInteger>(10);
    auto* innerLhs = pool.make<NInteger>(2);
    auto* innerRhs = pool.make<NInteger>(3);
    auto* innerMul = pool.make<NBinaryOperator>(*innerLhs, '*', *innerRhs);
    auto* outerAdd = pool.make<NBinaryOperator>(*lhs, '+', *innerMul);
    EXPECT_EQ(outerAdd->op, '+');
    EXPECT_EQ(innerMul->op, '*');
}

TEST(LexerParserIntegrationTest, BlockParsing) {
    cse_test::AstPool pool;
    auto* block = pool.make<NBlock>();
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x", pool.make<NInteger>(10));
    block->statements.push_back(varDecl);
    auto& retId = cse_test::makeIdent(pool, "x");
    auto* retStmt = pool.make<NReturnStatement>(retId);
    block->statements.push_back(retStmt);
    EXPECT_EQ(block->statements.size(), 2u);
}

TEST(LexerParserIntegrationTest, FunctionCallParsing) {
    // NFunctionCall 不存在，改用 NMethodCall
    cse_test::AstPool pool;
    auto& callee = cse_test::makeIdent(pool, "printf");
    ExpressionList args;
    args.push_back(pool.make<NInteger>(42));
    auto* methodCall = pool.make<NMethodCall>(callee, args);
    EXPECT_EQ(methodCall->id.name, "printf");
    EXPECT_EQ(methodCall->arguments.size(), 1u);
}