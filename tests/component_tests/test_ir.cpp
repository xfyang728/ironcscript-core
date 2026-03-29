#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/ir/IRGenerator.h"
#include "../src/ir/Quad.h"
#include "../src/frontend/semantic/SymbolTable.h"

using namespace cse;

class IRGeneratorTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(IRGeneratorTest, TestCreateIRGenerator) {
    SymbolTable symbolTable;
    IRGenerator generator(symbolTable);
    EXPECT_TRUE(true) << "IRGenerator should be created successfully";
}

TEST_F(IRGeneratorTest, TestEmptyQuadList) {
    SymbolTable symbolTable;
    IRGenerator generator(symbolTable);
    const std::list<Quad>& quads = generator.getQuadList();
    EXPECT_EQ(quads.size(), 0) << "Empty IR should have no quads";
}

TEST_F(IRGeneratorTest, TestQuadOpEnum) {
    Quad quad1(OpEnum::ADD, "a", "b", "result");
    Quad quad2(OpEnum::SUB, "x", "y", "result");
    Quad quad3(OpEnum::MUL, "a", "b", "result");
    Quad quad4(OpEnum::DIV, "a", "b", "result");

    EXPECT_EQ(quad1.getOp(), OpEnum::ADD);
    EXPECT_EQ(quad2.getOp(), OpEnum::SUB);
    EXPECT_EQ(quad3.getOp(), OpEnum::MUL);
    EXPECT_EQ(quad4.getOp(), OpEnum::DIV);
}

TEST_F(IRGeneratorTest, TestQuadArguments) {
    Quad quad(OpEnum::ADD, "arg1", "arg2", "result");

    EXPECT_EQ(quad.getArg1(), "arg1");
    EXPECT_EQ(quad.getArg2(), "arg2");
    EXPECT_EQ(quad.getResult(), "result");
}

TEST_F(IRGeneratorTest, TestQuadOperations) {
    Quad addQuad(OpEnum::ADD, "1", "2", "t0");
    Quad subQuad(OpEnum::SUB, "t0", "3", "t1");
    Quad mulQuad(OpEnum::MUL, "t1", "4", "t2");
    Quad divQuad(OpEnum::DIV, "t2", "2", "t3");

    EXPECT_EQ(addQuad.getOp(), OpEnum::ADD);
    EXPECT_EQ(subQuad.getOp(), OpEnum::SUB);
    EXPECT_EQ(mulQuad.getOp(), OpEnum::MUL);
    EXPECT_EQ(divQuad.getOp(), OpEnum::DIV);
}

TEST_F(IRGeneratorTest, TestQuadLabel) {
    Quad labelQuad(OpEnum::LABEL, "", "", "L1");
    EXPECT_EQ(labelQuad.getOp(), OpEnum::LABEL);
    EXPECT_EQ(labelQuad.getResult(), "L1");
}

TEST_F(IRGeneratorTest, TestQuadJump) {
    Quad jmpQuad(OpEnum::JMP, "", "", "L5");
    Quad jmpfQuad(OpEnum::JMPF, "condition", "", "L10");

    EXPECT_EQ(jmpQuad.getOp(), OpEnum::JMP);
    EXPECT_EQ(jmpfQuad.getOp(), OpEnum::JMPF);
}

TEST_F(IRGeneratorTest, TestQuadAssign) {
    Quad assignQuad(OpEnum::ASSIGN, "5", "", "x");
    EXPECT_EQ(assignQuad.getOp(), OpEnum::ASSIGN);
    EXPECT_EQ(assignQuad.getArg1(), "5");
    EXPECT_EQ(assignQuad.getResult(), "x");
}

TEST_F(IRGeneratorTest, TestQuadFunc) {
    Quad funcQuad(OpEnum::FUNC, "", "", "main");
    Quad endfuncQuad(OpEnum::ENDFUNC, "", "", "main");

    EXPECT_EQ(funcQuad.getOp(), OpEnum::FUNC);
    EXPECT_EQ(funcQuad.getResult(), "main");
    EXPECT_EQ(endfuncQuad.getOp(), OpEnum::ENDFUNC);
}

TEST_F(IRGeneratorTest, TestQuadParam) {
    Quad paramQuad(OpEnum::PARAM, "rcx", "", "arg1");
    EXPECT_EQ(paramQuad.getOp(), OpEnum::PARAM);
    EXPECT_EQ(paramQuad.getArg1(), "rcx");
    EXPECT_EQ(paramQuad.getResult(), "arg1");
}

TEST_F(IRGeneratorTest, TestQuadReturn) {
    Quad retQuad(OpEnum::RET, "", "", "result");
    EXPECT_EQ(retQuad.getOp(), OpEnum::RET);
    EXPECT_EQ(retQuad.getResult(), "result");
}
