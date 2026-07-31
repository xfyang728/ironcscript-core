#include <gtest/gtest.h>
#include <string>
#include <list>
#include <vector>
#include "../common/AstPool.h"
#include "../common/AstBuilders.h"
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/frontend/semantic/SymbolTable.h"
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/backend/x64/X64Code.h"
#include "../src/frontend/parser/node.h"

using namespace cse;

/// 辅助：构造包含 main 函数的顶层 NBlock
static NBlock* buildProgramWithMain(cse_test::AstPool& pool, NBlock* funcBody) {
    auto* topBlock = pool.make<NBlock>();
    auto* func = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, funcBody);
    topBlock->statements.push_back(func);
    return topBlock;
}

TEST(IRCodegenIntegrationTest, QuadToCodeGeneration) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* retExpr = pool.make<NInteger>(42);
    auto* retStmt = pool.make<NReturnStatement>(*retExpr);
    funcBody->statements.push_back(retStmt);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    IRGenerator ir(symtab);
    analyzer.analyze(*topBlock);
    ir.generateIR(*topBlock);

    const auto& quads = ir.getQuadList();
    EXPECT_GT(quads.size(), 0u);
}

TEST(IRCodegenIntegrationTest, AdditionQuadToCode) {
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
    analyzer.analyze(*topBlock);
    ir.generateIR(*topBlock);

    const auto& quads = ir.getQuadList();
    X64Code codeGen;
    // generateCodeFromIR 接收整个 list，调用一次即可（不要在循环中调用）
    codeGen.generateCodeFromIR(quads);

    const std::vector<unsigned char>& code = codeGen.GetCodeBuffer();
    EXPECT_GT(code.size(), 0u);
}

TEST(IRCodegenIntegrationTest, VariableAllocationInCodeGen) {
    X64Code codeGen;
    codeGen.AllocateVariable("x", X64Code::Type::Int);
    codeGen.AllocateVariable("y", X64Code::Type::Int);
    codeGen.AllocateVariable("z", X64Code::Type::Int);

    int offsetX = codeGen.GetVariableOffset("x");
    int offsetY = codeGen.GetVariableOffset("y");
    int offsetZ = codeGen.GetVariableOffset("z");

    EXPECT_NE(offsetX, offsetY);
    EXPECT_NE(offsetY, offsetZ);
    EXPECT_NE(offsetX, offsetZ);
}

TEST(IRCodegenIntegrationTest, DoubleStorageCodeGen) {
    X64Code codeGen;
    size_t offset = codeGen.StoreDouble(3.14159);
    EXPECT_GT(offset, 0u);
}

TEST(IRCodegenIntegrationTest, StringStorageCodeGen) {
    X64Code codeGen;
    size_t offset = codeGen.StoreString("Hello World");
    EXPECT_GT(offset, 0u);
}

TEST(IRCodegenIntegrationTest, CodeBufferGrowth) {
    X64Code codeGen;
    size_t initialSize = codeGen.GetCodeSize();

    codeGen.AllocateVariable("a", X64Code::Type::Int);
    codeGen.CreateLabel("start");

    size_t newSize = codeGen.GetCodeSize();
    EXPECT_GE(newSize, initialSize);
}

TEST(IRCodegenIntegrationTest, VariableTypeTracking) {
    X64Code codeGen;
    codeGen.AllocateVariable("intVar", X64Code::Type::Int);
    codeGen.AllocateVariable("doubleVar", X64Code::Type::Double);
    codeGen.AllocateVariable("charVar", X64Code::Type::Char);

    EXPECT_EQ(codeGen.GetVariableType("intVar"), X64Code::Type::Int);
    EXPECT_EQ(codeGen.GetVariableType("doubleVar"), X64Code::Type::Double);
    EXPECT_EQ(codeGen.GetVariableType("charVar"), X64Code::Type::Char);
}

TEST(IRCodegenIntegrationTest, ControlFlowLabelGeneration) {
    X64Code codeGen;
    codeGen.CreateLabel("loop_start");
    codeGen.CreateLabel("loop_end");

    size_t codeSize = codeGen.GetCodeSize();
    EXPECT_GT(codeSize, 0u);
}

TEST(IRCodegenIntegrationTest, FunctionContextManagement) {
    X64Code codeGen;

    EXPECT_FALSE(codeGen.GetInFunction());

    codeGen.SetInFunction(true);
    EXPECT_TRUE(codeGen.GetInFunction());

    codeGen.SetInFunction(false);
    EXPECT_FALSE(codeGen.GetInFunction());
}