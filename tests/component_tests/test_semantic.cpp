#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/flex_bison/node.h"

using namespace cse;

class SemanticAnalyzerTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(SemanticAnalyzerTest, TestSimpleProgram) {
    NBlock* block = new NBlock();
    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Simple program should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestVariableDeclaration) {
    NBlock* block = new NBlock();
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Variable declaration should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestVariableInitialization) {
    NBlock* block = new NBlock();
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NInteger{10};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Variable initialization should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestScopeManagement) {
    SemanticAnalyzer analyzer;
    analyzer.enterScope();

    Symbol symbol;
    symbol.name = "test_var";
    symbol.type = "int";
    symbol.isFunction = false;
    symbol.isGlobal = false;

    Scope* scope = analyzer.getCurrentScope();
    EXPECT_NE(scope, nullptr) << "Should have a current scope after entering";

    analyzer.exitScope();
}

TEST_F(SemanticAnalyzerTest, TestTypeInference) {
    NInteger* intLiteral = new NInteger{42};

    SemanticAnalyzer analyzer;
    std::string inferredType = analyzer.inferType(intLiteral);

    EXPECT_EQ(inferredType, "int") << "Integer literal should be inferred as int type";
}

TEST_F(SemanticAnalyzerTest, TestTypeCompatibility) {
    SemanticAnalyzer analyzer;

    bool compatible = analyzer.checkTypeCompatibility("int", "int");
    EXPECT_TRUE(compatible) << "int should be compatible with int";

    compatible = analyzer.checkTypeCompatibility("int", "double");
    EXPECT_FALSE(compatible) << "int should not be compatible with double";
}

TEST_F(SemanticAnalyzerTest, TestAssignmentCompatibility) {
    SemanticAnalyzer analyzer;

    bool compatible = analyzer.checkAssignmentCompatibility("int", "int");
    EXPECT_TRUE(compatible) << "int = int should be compatible";

    compatible = analyzer.checkAssignmentCompatibility("int", "double");
    EXPECT_FALSE(compatible) << "int = double should not be compatible";
}

TEST_F(SemanticAnalyzerTest, TestBinaryOperatorType) {
    NBinaryOperator* addOp = new NBinaryOperator();
    addOp->op = '+';
    addOp->lhs = new NInteger{10};
    addOp->rhs = new NInteger{20};

    SemanticAnalyzer analyzer;
    std::string resultType = analyzer.inferType(addOp);

    EXPECT_EQ(resultType, "int") << "Addition of two ints should return int";
}

TEST_F(SemanticAnalyzerTest, TestFunctionDeclaration) {
    NBlock* block = new NBlock();

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"add"};

    NVariableDeclaration* param1 = new NVariableDeclaration();
    param1->type = NIdentifier{"int"};
    param1->name = NIdentifier{"a"};
    func->parameters.push_back(param1);

    NVariableDeclaration* param2 = new NVariableDeclaration();
    param2->type = NIdentifier{"int"};
    param2->name = NIdentifier{"b"};
    func->parameters.push_back(param2);

    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Function declaration should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestDoubleType) {
    NBlock* block = new NBlock();
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"double"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NDouble{3.14};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Double type should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestCharType) {
    NBlock* block = new NBlock();
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"char"};
    varDecl->name = NIdentifier{"c"};
    varDecl->assignmentExpr = new NInteger{'A'};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Char type should pass semantic analysis";
}

TEST_F(SemanticAnalyzerTest, TestBoolType) {
    NBlock* block = new NBlock();
    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"bool"};
    varDecl->name = NIdentifier{"flag"};
    varDecl->assignmentExpr = new NInteger{1};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer analyzer;
    bool result = analyzer.analyze(*func);

    EXPECT_TRUE(result) << "Bool type should pass semantic analysis";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
