#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <memory>

using namespace testing;

class MockX64Code {
public:
    MOCK_METHOD(void, AllocateVariable, (const char* name, int type), ());
    MOCK_METHOD(int, GetVariableOffset, (const char* name), ());
    MOCK_METHOD(bool, VariableExists, (const char* name), ());
    MOCK_METHOD(size_t, GetCodeSize, (), (const));
    MOCK_METHOD(void, SetInFunction, (bool value), ());
    MOCK_METHOD(bool, GetInFunction, (), (const));
};

TEST(X64CodeMockTest, TestMockAllocation) {
    MockX64Code mock;

    EXPECT_CALL(mock, AllocateVariable("x", 0))
        .Times(1);
    EXPECT_CALL(mock, GetVariableOffset("x"))
        .WillOnce(Return(0));

    mock.AllocateVariable("x", 0);
    int offset = mock.GetVariableOffset("x");

    EXPECT_EQ(offset, 0);
}

TEST(X64CodeMockTest, TestMockMultipleVariables) {
    MockX64Code mock;

    EXPECT_CALL(mock, AllocateVariable("a", 0))
        .Times(1);
    EXPECT_CALL(mock, AllocateVariable("b", 0))
        .Times(1);
    EXPECT_CALL(mock, GetVariableOffset("a"))
        .WillOnce(Return(0));
    EXPECT_CALL(mock, GetVariableOffset("b"))
        .WillOnce(Return(8));

    mock.AllocateVariable("a", 0);
    mock.AllocateVariable("b", 0);

    EXPECT_EQ(mock.GetVariableOffset("a"), 0);
    EXPECT_EQ(mock.GetVariableOffset("b"), 8);
}

TEST(X64CodeMockTest, TestMockVariableExists) {
    MockX64Code mock;

    EXPECT_CALL(mock, VariableExists("existing"))
        .WillOnce(Return(true));
    EXPECT_CALL(mock, VariableExists("nonexistent"))
        .WillOnce(Return(false));

    EXPECT_TRUE(mock.VariableExists("existing"));
    EXPECT_FALSE(mock.VariableExists("nonexistent"));
}

TEST(X64CodeMockTest, TestMockFunctionContext) {
    MockX64Code mock;

    EXPECT_CALL(mock, GetInFunction())
        .WillRepeatedly(Return(false));

    EXPECT_FALSE(mock.GetInFunction());
    EXPECT_FALSE(mock.GetInFunction());
}

TEST(X64CodeMockTest, TestMockCodeSize) {
    MockX64Code mock;

    EXPECT_CALL(mock, GetCodeSize())
        .WillOnce(Return(0));

    EXPECT_EQ(mock.GetCodeSize(), 0);
}
