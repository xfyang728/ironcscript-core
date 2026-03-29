#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/flex_bison/node.h"

using namespace cse;

class SemanticIRIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(SemanticIRIntegrationTest, TestSymbolTableToQuad) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NInteger{10};
    block->statements.push_back(varDecl);

    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = new NIdentifier{"x"};
    block->statements.push_back(retStmt);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    EXPECT_GT(quads.size(), 0) << "Should generate IR quads from semantic analysis";
}

TEST_F(SemanticIRIntegrationTest, TestTypeInferenceToIR) {
    NInteger* intLit = new NInteger{42};

    IRGenerator ir;
    std::string result = ir.analyzeExpression(intLit);

    EXPECT_EQ(result, "42") << "Should generate IR for integer expression";
}

TEST_F(SemanticIRIntegrationTest, TestVariableAssignmentToIR) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"x"};
    varDecl->assignmentExpr = new NInteger{100};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    bool hasAssign = false;
    for (const auto& quad : quads) {
        if (quad.getOp() == OpEnum::ASSIGN) {
            hasAssign = true;
            break;
        }
    }
    EXPECT_TRUE(hasAssign) << "Should generate ASSIGN quad for variable";
}

TEST_F(SemanticIRIntegrationTest, TestFunctionReturnToIR) {
    NBlock* block = new NBlock();

    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = new NInteger{42};
    block->statements.push_back(retStmt);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    bool hasReturn = false;
    for (const auto& quad : quads) {
        if (quad.getOp() == OpEnum::RET) {
            hasReturn = true;
            break;
        }
    }
    EXPECT_TRUE(hasReturn) << "Should generate RET quad for return statement";
}

TEST_F(SemanticIRIntegrationTest, TestBinaryOperationToIR) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"result"};
    NBinaryOperator* addOp = new NBinaryOperator();
    addOp->op = '+';
    addOp->lhs = new NInteger{10};
    addOp->rhs = new NInteger{20};
    varDecl->assignmentExpr = addOp;
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    bool hasAdd = false;
    for (const auto& quad : quads) {
        if (quad.getOp() == OpEnum::ADD) {
            hasAdd = true;
            break;
        }
    }
    EXPECT_TRUE(hasAdd) << "Should generate ADD quad for binary operation";
}

TEST_F(SemanticIRIntegrationTest, TestComparisonToIR) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"int"};
    varDecl->name = NIdentifier{"result"};
    NBinaryOperator* compOp = new NBinaryOperator();
    compOp->op = '<';
    compOp->lhs = new NInteger{5};
    compOp->rhs = new NInteger{10};
    varDecl->assignmentExpr = compOp;
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    bool hasLT = false;
    for (const auto& quad : quads) {
        if (quad.getOp() == OpEnum::LT) {
            hasLT = true;
            break;
        }
    }
    EXPECT_TRUE(hasLT) << "Should generate LT quad for comparison";
}

TEST_F(SemanticIRIntegrationTest, TestMultipleStatementsToIR) {
    NBlock* block = new NBlock();

    NVariableDeclaration* var1 = new NVariableDeclaration();
    var1->type = NIdentifier{"int"};
    var1->name = NIdentifier{"a"};
    var1->assignmentExpr = new NInteger{5};
    block->statements.push_back(var1);

    NVariableDeclaration* var2 = new NVariableDeclaration();
    var2->type = NIdentifier{"int"};
    var2->name = NIdentifier{"b"};
    var2->assignmentExpr = new NInteger{10};
    block->statements.push_back(var2);

    NReturnStatement* retStmt = new NReturnStatement();
    NBinaryOperator* addOp = new NBinaryOperator();
    addOp->op = '+';
    addOp->lhs = new NIdentifier{"a"};
    addOp->rhs = new NIdentifier{"b"};
    retStmt->expression = addOp;
    block->statements.push_back(retStmt);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    EXPECT_GE(quads.size(), 3) << "Should generate at least 3 quads";
}

TEST_F(SemanticIRIntegrationTest, TestFunctionCallToIR) {
    NBlock* block = new NBlock();

    NFunctionCall* funcCall = new NFunctionCall();
    funcCall->callee = NIdentifier{"add"};
    funcCall->arguments.push_back(new NInteger{5});
    funcCall->arguments.push_back(new NInteger{3});

    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = funcCall;
    block->statements.push_back(retStmt);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    bool hasCall = false;
    for (const auto& quad : quads) {
        if (quad.getOp() == OpEnum::CALL) {
            hasCall = true;
            break;
        }
    }
    EXPECT_TRUE(hasCall) << "Should generate CALL quad for function call";
}

TEST_F(SemanticIRIntegrationTest, TestDoubleTypeToIR) {
    NBlock* block = new NBlock();

    NVariableDeclaration* varDecl = new NVariableDeclaration();
    varDecl->type = NIdentifier{"double"};
    varDecl->name = NIdentifier{"pi"};
    varDecl->assignmentExpr = new NDouble{3.14159};
    block->statements.push_back(varDecl);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    EXPECT_GT(quads.size(), 0) << "Should generate quads for double type";
}

TEST_F(SemanticIRIntegrationTest, TestCharTypeToIR) {
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

    SemanticAnalyzer semantic;
    semantic.analyze(func);

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    EXPECT_GT(quads.size(), 0) << "Should generate quads for char type";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
