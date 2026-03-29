#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/backend/x64/X64Code.h"

using namespace cse;

class IRCodegenIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(IRCodegenIntegrationTest, TestQuadToCodeGeneration) {
    NBlock* block = new NBlock();

    NReturnStatement* retStmt = new NReturnStatement();
    retStmt->expression = new NInteger{42};
    block->statements.push_back(retStmt);

    NFunctionDeclaration* func = new NFunctionDeclaration();
    func->returnType = NIdentifier{"int"};
    func->name = NIdentifier{"main"};
    func->body = block;

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    EXPECT_GT(quads.size(), 0) << "Should generate IR quads";
}

TEST_F(IRCodegenIntegrationTest, TestAdditionQuadToCode) {
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

    IRGenerator ir;
    ir.generateIR(*func);

    const std::list<Quad>& quads = ir.getQuadList();
    X64Code codeGen;

    for (const auto& quad : quads) {
        codeGen.generateCodeFromIR(quads);
    }

    const std::vector<unsigned char>& code = codeGen.GetCodeBuffer();
    EXPECT_GT(code.size(), 0) << "Should generate machine code from IR";
}

TEST_F(IRCodegenIntegrationTest, TestVariableAllocationInCodeGen) {
    X64Code codeGen;
    codeGen.AllocateVariable("x", X64Code::Type::Int);
    codeGen.AllocateVariable("y", X64Code::Type::Int);
    codeGen.AllocateVariable("z", X64Code::Type::Int);

    int offsetX = codeGen.GetVariableOffset("x");
    int offsetY = codeGen.GetVariableOffset("y");
    int offsetZ = codeGen.GetVariableOffset("z");

    EXPECT_NE(offsetX, offsetY) << "Each variable should have unique offset";
    EXPECT_NE(offsetY, offsetZ) << "Each variable should have unique offset";
}

TEST_F(IRCodegenIntegrationTest, TestIntegerLiteralCodeGen) {
    X64Code codeGen;
    codeGen.AllocateVariable("x", X64Code::Type::Int);

    Value* val = new Value("42", X64Code::Type::Int);
    codeGen.StoreVariable("x", val, X64Code::Type::Int);

    Value* loaded = codeGen.LoadVariable("x", X64Code::Type::Int);
    EXPECT_NE(loaded, nullptr) << "Should load stored value";
}

TEST_F(IRCodegenIntegrationTest, TestDoubleStorageCodeGen) {
    X64Code codeGen;
    size_t offset = codeGen.StoreDouble(3.14159);

    EXPECT_GT(offset, 0) << "Should store double in data section";
}

TEST_F(IRCodegenIntegrationTest, TestStringStorageCodeGen) {
    X64Code codeGen;
    size_t offset = codeGen.StoreString("Hello World");

    EXPECT_GT(offset, 0) << "Should store string in data section";
}

TEST_F(IRCodegenIntegrationTest, TestCodeBufferGrowth) {
    X64Code codeGen;
    size_t initialSize = codeGen.GetCodeSize();

    codeGen.AllocateVariable("a", X64Code::Type::Int);
    codeGen.CreateLabel("start");

    size_t newSize = codeGen.GetCodeSize();
    EXPECT_GE(newSize, initialSize) << "Code buffer should grow or stay same";
}

TEST_F(IRCodegenIntegrationTest, TestVariableTypeTracking) {
    X64Code codeGen;
    codeGen.AllocateVariable("intVar", X64Code::Type::Int);
    codeGen.AllocateVariable("doubleVar", X64Code::Type::Double);
    codeGen.AllocateVariable("charVar", X64Code::Type::Char);

    X64Code::Type intType = codeGen.GetVariableType("intVar");
    X64Code::Type doubleType = codeGen.GetVariableType("doubleVar");
    X64Code::Type charType = codeGen.GetVariableType("charVar");

    EXPECT_EQ(intType, X64Code::Type::Int);
    EXPECT_EQ(doubleType, X64Code::Type::Double);
    EXPECT_EQ(charType, X64Code::Type::Char);
}

TEST_F(IRCodegenIntegrationTest, TestControlFlowLabelGeneration) {
    X64Code codeGen;
    codeGen.CreateLabel("loop_start");
    codeGen.CreateLabel("loop_end");

    size_t codeSize = codeGen.GetCodeSize();
    EXPECT_GT(codeSize, 0) << "Labels should generate code";
}

TEST_F(IRCodegenIntegrationTest, TestFunctionContextManagement) {
    X64Code codeGen;

    EXPECT_FALSE(codeGen.GetInFunction()) << "Should start not in function";

    codeGen.SetInFunction(true);
    EXPECT_TRUE(codeGen.GetInFunction()) << "Should be in function after setting";

    codeGen.SetInFunction(false);
    EXPECT_FALSE(codeGen.GetInFunction()) << "Should exit function context";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
