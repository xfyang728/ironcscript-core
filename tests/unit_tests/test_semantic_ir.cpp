#include <gtest/gtest.h>
#include <string>
#include <list>
#include "../common/AstPool.h"
#include "../common/AstBuilders.h"
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/frontend/semantic/SymbolTable.h"
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/frontend/parser/node.h"

using namespace cse;

/// 辅助：检查 quad 列表中是否存在指定 OpEnum
static bool hasOp(const std::list<Quad>& quads, OpEnum op) {
    for (const auto& q : quads) {
        if (q.getOp() == op) return true;
    }
    return false;
}

/// 辅助：构造包含 main 函数的顶层 NBlock，main 函数体由 funcBody 提供
static NBlock* buildProgramWithMain(cse_test::AstPool& pool, NBlock* funcBody) {
    auto* topBlock = pool.make<NBlock>();
    auto* func = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, funcBody);
    topBlock->statements.push_back(func);
    return topBlock;
}

/// 辅助：对顶层 NBlock 执行 semantic.analyze + ir.generateIR，返回 quad 列表引用
static const std::list<Quad>& analyzeAndGenerate(cse_test::AstPool& pool, NBlock* topBlock,
                                                  SymbolTable& symtab,
                                                  SemanticAnalyzer& analyzer,
                                                  IRGenerator& ir) {
    analyzer.analyze(*topBlock);
    ir.generateIR(*topBlock);
    return ir.getQuadList();
}

TEST(SemanticIRIntegrationTest, SymbolTableToQuad) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x", pool.make<NInteger>(10));
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_GT(quads.size(), 0u);
}

TEST(SemanticIRIntegrationTest, VariableAssignmentToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NInteger>(100);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_TRUE(hasOp(quads, OpEnum::ASSIGN));
}

TEST(SemanticIRIntegrationTest, FunctionReturnToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* retExpr = pool.make<NInteger>(42);
    auto* retStmt = pool.make<NReturnStatement>(*retExpr);
    funcBody->statements.push_back(retStmt);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_TRUE(hasOp(quads, OpEnum::RET));
}

TEST(SemanticIRIntegrationTest, BinaryOperationToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* lhs = pool.make<NInteger>(10);
    auto* rhs = pool.make<NInteger>(20);
    auto* addOp = pool.make<NBinaryOperator>(*lhs, '+', *rhs);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "result", addOp);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_TRUE(hasOp(quads, OpEnum::ADD));
}

TEST(SemanticIRIntegrationTest, ComparisonToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* lhs = pool.make<NInteger>(5);
    auto* rhs = pool.make<NInteger>(10);
    auto* compOp = pool.make<NBinaryOperator>(*lhs, '<', *rhs);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "result", compOp);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_TRUE(hasOp(quads, OpEnum::LT));
}

TEST(SemanticIRIntegrationTest, MultipleStatementsToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* var1 = cse_test::makeVarDecl(pool, "int", "a", pool.make<NInteger>(5));
    auto* var2 = cse_test::makeVarDecl(pool, "int", "b", pool.make<NInteger>(10));
    funcBody->statements.push_back(var1);
    funcBody->statements.push_back(var2);

    auto& aId = cse_test::makeIdent(pool, "a");
    auto& bId = cse_test::makeIdent(pool, "b");
    auto* addOp = pool.make<NBinaryOperator>(aId, '+', bId);
    auto* retStmt = pool.make<NReturnStatement>(*addOp);
    funcBody->statements.push_back(retStmt);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_GE(quads.size(), 3u);
}

TEST(SemanticIRIntegrationTest, FunctionCallToIR) {
    cse_test::AstPool pool;
    auto* topBlock = pool.make<NBlock>();

    // add 函数
    auto* addBody = cse_test::makeFuncBody(pool);
    VariableList params;
    params.push_back(cse_test::makeVarDecl(pool, "int", "a"));
    params.push_back(cse_test::makeVarDecl(pool, "int", "b"));
    auto* addFunc = cse_test::makeFuncDecl(pool, "int", "add", params, addBody);
    topBlock->statements.push_back(addFunc);

    // main 函数：return add(5, 3)
    auto* mainBody = cse_test::makeFuncBody(pool);
    auto& callee = cse_test::makeIdent(pool, "add");
    ExpressionList args;
    args.push_back(pool.make<NInteger>(5));
    args.push_back(pool.make<NInteger>(3));
    auto* methodCall = pool.make<NMethodCall>(callee, args);
    auto* retStmt = pool.make<NReturnStatement>(*methodCall);
    mainBody->statements.push_back(retStmt);
    auto* mainFunc = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, mainBody);
    topBlock->statements.push_back(mainFunc);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_TRUE(hasOp(quads, OpEnum::CALL));
}

TEST(SemanticIRIntegrationTest, DoubleTypeToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NDouble>(3.14159);
    auto* varDecl = cse_test::makeVarDecl(pool, "double", "pi", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_GT(quads.size(), 0u);
}

TEST(SemanticIRIntegrationTest, CharTypeToIR) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NInteger>('A');
    auto* varDecl = cse_test::makeVarDecl(pool, "char", "c", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    const auto& quads = analyzeAndGenerate(pool, topBlock, symtab, analyzer, ir);
    EXPECT_GT(quads.size(), 0u);
}