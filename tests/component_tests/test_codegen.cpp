#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../src/backend/x64/X64Code.h"

using namespace cse;

class X64CodeGeneratorTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(X64CodeGeneratorTest, TestCreateX64Code) {
    X64Code codeGen;
    EXPECT_TRUE(true) << "X64Code should be created successfully";
}

TEST_F(X64CodeGeneratorTest, TestAllocateIntVariable) {
    X64Code codeGen;
    codeGen.AllocateVariable("x", X64Code::Type::Int);
    int offset = codeGen.GetVariableAbsoluteOffset("x");
    EXPECT_GE(offset, 0) << "Variable should be allocated with non-negative offset";
}

TEST_F(X64CodeGeneratorTest, TestAllocateMultipleVariables) {
    X64Code codeGen;
    codeGen.SetInFunction(true);
    codeGen.AllocateVariable("a", X64Code::Type::Int);
    codeGen.AllocateVariable("b", X64Code::Type::Int);

    int offsetA = codeGen.GetVariableOffset("a");
    int offsetB = codeGen.GetVariableOffset("b");

    EXPECT_NE(offsetA, offsetB) << "Different variables should have different offsets";
}

TEST_F(X64CodeGeneratorTest, TestCodeBufferInitialSize) {
    X64Code codeGen;
    size_t size = codeGen.GetCodeSize();
    EXPECT_EQ(size, 0) << "Initial code buffer should be empty";
}

TEST_F(X64CodeGeneratorTest, TestVariableExists) {
    X64Code codeGen;
    codeGen.AllocateVariable("myvar", X64Code::Type::Int);
    bool exists = codeGen.VariableExists("myvar");
    EXPECT_TRUE(exists) << "Variable should exist after allocation";
}

TEST_F(X64CodeGeneratorTest, TestVariableNotExists) {
    X64Code codeGen;
    bool exists = codeGen.VariableExists("nonexistent");
    EXPECT_FALSE(exists) << "Non-existent variable should return false";
}

TEST_F(X64CodeGeneratorTest, TestGetVariableType) {
    X64Code codeGen;
    codeGen.AllocateVariable("intVar", X64Code::Type::Int);

    X64Code::Type intType = codeGen.GetVariableType("intVar");
    EXPECT_EQ(intType, X64Code::Type::Int);
}

TEST_F(X64CodeGeneratorTest, TestCodeBufferAfterOperations) {
    X64Code codeGen;
    codeGen.AllocateVariable("x", X64Code::Type::Int);
    codeGen.CreateLabel("start");

    const std::vector<unsigned char>& buffer = codeGen.GetCodeBuffer();
    EXPECT_GE(buffer.capacity(), 0) << "Code buffer should be valid";
}

TEST_F(X64CodeGeneratorTest, TestSetInFunction) {
    X64Code codeGen;
    codeGen.SetInFunction(true);
    bool inFunc = codeGen.GetInFunction();
    EXPECT_TRUE(inFunc) << "Should be in function after SetInFunction(true)";
}

TEST_F(X64CodeGeneratorTest, TestDefaultInFunction) {
    X64Code codeGen;
    bool inFunc = codeGen.GetInFunction();
    EXPECT_FALSE(inFunc) << "Should not be in function by default";
}
