#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <direct.h>
#include <windows.h>
#include "ProcessRunner.h"

struct TestResult {
    int exitCode;
    int returnValue;
    bool hasOutput;
    std::string output;
    bool timedOut;
};

static int testCounter = 0;

TestResult runScript(const char* scriptPath) {
    TestResult result;
    testCounter++;
    std::string outputPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\tests\\output\\test_output_" + std::to_string(testCounter) + ".txt";
    std::string scriptFullPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\tests\\scripts\\" + std::string(scriptPath);
    std::string exeFullPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\build\\IronCScriptCLI.exe";
    
    // 使用新的ProcessRunner
    ProcessRunner::ProcessResult processResult = ProcessRunner::runProcess(
        exeFullPath, 
        "\"" + scriptFullPath + "\"", 
        outputPath,
        15000 // 15秒超时
    );
    
    result.exitCode = processResult.exitCode;
    result.returnValue = processResult.returnValue;
    result.hasOutput = processResult.hasOutput;
    result.output = processResult.output;
    result.timedOut = processResult.timedOut;
    
    std::cout << "Output: " << result.output << std::endl;
    std::cout << "Exit code: " << result.exitCode << std::endl;
    std::cout << "Return value: " << result.returnValue << std::endl;
    if (result.timedOut) {
        std::cout << "Process timed out!" << std::endl;
    }
    
    return result;
}

TestResult runScriptWithInput(const char* scriptPath, const char* inputPath) {
    TestResult result;
    testCounter++;
    std::string outputPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\tests\\output\\test_output_" + std::to_string(testCounter) + ".txt";
    std::string inputFullPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\tests\\inputs\\" + std::string(inputPath);
    std::string scriptFullPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\tests\\scripts\\" + std::string(scriptPath);
    std::string exeFullPath = "D:\\MyCode\\IronCScript\\IronCScript-core\\build\\IronCScriptCLI.exe";
    
    // 使用新的ProcessRunner，正确处理输入重定向
    // 构建命令行参数
    std::string arguments = "\"" + scriptFullPath + "\"";
    
    ProcessRunner::ProcessResult processResult = ProcessRunner::runProcessWithInput(
        exeFullPath, 
        arguments, 
        inputFullPath,
        outputPath,
        15000 // 15秒超时
    );
    
    result.exitCode = processResult.exitCode;
    result.returnValue = processResult.returnValue;
    result.hasOutput = processResult.hasOutput;
    result.output = processResult.output;
    result.timedOut = processResult.timedOut;
    
    std::cout << "Output: " << result.output << std::endl;
    std::cout << "Exit code: " << result.exitCode << std::endl;
    std::cout << "Return value: " << result.returnValue << std::endl;
    if (result.timedOut) {
        std::cout << "Process timed out!" << std::endl;
    }
    
    return result;
}

class IronCScriptTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST(IronCScriptTest, TestChar) {
    TestResult result = runScript("01_basic/test_char.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 65) << "char test should return ASCII value of 'A' (65)";
}

TEST(IronCScriptTest, TestPrintfInt) {
    TestResult result = runScript("09_stdlib/stdio/test_printf_int.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "printf int test should return 1";
}

TEST(IronCScriptTest, TestInt) {
    TestResult result = runScript("01_basic/test_int.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 3) << "int test: x=1, y=2, z=x+y should return 3";
}

TEST(IronCScriptTest, TestSimple) {
    TestResult result = runScript("01_basic/test_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "simple test: return 0";
}

TEST(IronCScriptTest, TestBool) {
    TestResult result = runScript("01_basic/test_bool.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "bool test should return 1 (true)";
}

TEST(IronCScriptTest, TestDouble) {
    TestResult result = runScript("01_basic/test_double.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 3) << "double test should return 3 (1.0+2.0)";
}

TEST(IronCScriptTest, TestFFIDoubleBasic) {
    TestResult result = runScript("10_advanced/test_ffi_double_basic.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 4) << "double basic test should return 4 (1.5+2.5)";
}

TEST(IronCScriptTest, TestFFIDoubleSqrt) {
    TestResult result = runScript("10_advanced/test_ffi_double_sqrt.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 4) << "double sqrt test should return 4 (sqrt(16))";
}

TEST(IronCScriptTest, TestFFIDoublePow) {
    TestResult result = runScript("10_advanced/test_ffi_double_pow.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 256) << "double pow test should return 256 (2^8)";
}

TEST(IronCScriptTest, TestFFIAllArithOps) {
    TestResult result = runScript("10_advanced/test_ffi_all_arith_ops.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    double expected = (5.0 - 3.0) + (5.0 * 3.0) + (5.0 / 3.0) + 2.0;
    EXPECT_EQ(result.returnValue, static_cast<int>(expected)) << "all arith ops test";
}

TEST(IronCScriptTest, TestFloat) {
    TestResult result = runScript("01_basic/test_simple_float.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "float test should return 1 (1.0 cast to int)";
}

TEST(IronCScriptTest, TestFunctionCall) {
    TestResult result = runScript("04_functions/test_function_call.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 8) << "function call test: add(5,3) should return 8";
}

TEST(IronCScriptTest, TestGlobalVariable) {
    TestResult result = runScript("04_functions/test_global_variable.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "global variable test should return 10";
}

TEST(IronCScriptTest, TestSubtraction) {
    TestResult result = runScript("02_operators/test_subtraction.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 3) << "subtraction test: 5-2 should return 3";
}

TEST(IronCScriptTest, TestReturn) {
    TestResult result = runScript("04_functions/test_return.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 42) << "return test should return 42";
}

TEST(IronCScriptTest, TestSimpleFunction) {
    TestResult result = runScript("04_functions/test_simple_function.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 42) << "simple function test should return 42";
}

TEST(IronCScriptTest, TestRecursiveFunction) {
    TestResult result = runScript("04_functions/test_recursive_function.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 120) << "recursive function test should return 120 (5!)";
}

TEST(IronCScriptTest, TestPuts) {
    TestResult result = runScript("09_stdlib/stdio/test_puts.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "puts test should complete";
}

TEST(IronCScriptTest, TestPrintf) {
    TestResult result = runScript("09_stdlib/stdio/test_printf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "printf test should complete";
}

TEST(IronCScriptTest, TestModulo) {
    TestResult result = runScript("02_operators/test_modulo.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "modulo test: 10 % 3 should return 1";
}

TEST(IronCScriptTest, TestMultiplication) {
    TestResult result = runScript("02_operators/test_multiplication.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 24) << "multiplication test: 6 * 4 should return 24";
}

TEST(IronCScriptTest, TestDivision) {
    TestResult result = runScript("02_operators/test_division.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 5) << "division test: 20 / 4 should return 5";
}

TEST(IronCScriptTest, TestLogicalAnd) {
    TestResult result = runScript("02_operators/test_logical_and.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "logical and test should return 1";
}

TEST(IronCScriptTest, TestLogicalOr) {
    TestResult result = runScript("02_operators/test_logical_or.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "logical or test should return 1";
}

TEST(IronCScriptTest, TestLogicalNot) {
    TestResult result = runScript("02_operators/test_logical_not.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "logical not test should return 1";
}

TEST(IronCScriptTest, TestBitwiseAnd) {
    TestResult result = runScript("02_operators/test_bitwise_and.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "bitwise and test: 5 & 3 should return 1";
}

TEST(IronCScriptTest, TestBitwiseOr) {
    TestResult result = runScript("02_operators/test_bitwise_or.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 7) << "bitwise or test: 5 | 3 should return 7";
}

TEST(IronCScriptTest, TestBitwiseXor) {
    TestResult result = runScript("02_operators/test_bitwise_xor.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 6) << "bitwise xor test: 5 ^ 3 should return 6";
}

TEST(IronCScriptTest, TestBitwiseNot) {
    TestResult result = runScript("02_operators/test_bitwise_not.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, -6) << "bitwise not test: ~5 should return -6";
}

TEST(IronCScriptTest, TestShiftLeft) {
    TestResult result = runScript("02_operators/test_shift_left.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 16) << "shift left test: 4 << 2 should return 16";
}

TEST(IronCScriptTest, TestShiftRight) {
    TestResult result = runScript("02_operators/test_shift_right.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 4) << "shift right test: 16 >> 2 should return 4";
}

TEST(IronCScriptTest, TestIf) {
    TestResult result = runScript("03_control_flow/test_if.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "if test should return 1";
}

TEST(IronCScriptTest, TestWhile) {
    TestResult result = runScript("03_control_flow/test_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "while test: sum 0+1+2+3+4 should return 10";
}

TEST(IronCScriptTest, TestInc) {
    TestResult result = runScript("10_advanced/test_inc.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 8) << "inc test: a=5, a++, a++, a++, return a=8";
}

TEST(IronCScriptTest, TestDec) {
    TestResult result = runScript("10_advanced/test_dec.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 2) << "dec test: a=5, a--, a--, a--, return a=2";
}

TEST(IronCScriptTest, TestFor) {
    TestResult result = runScript("03_control_flow/test_for.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "for test: sum 0+1+2+3+4 should return 10";
}

TEST(IronCScriptTest, TestDoWhile) {
    TestResult result = runScript("03_control_flow/test_do_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "do-while test: sum 0+1+2+3+4 should return 10";
}

TEST(IronCScriptTest, TestNestedIf) {
    TestResult result = runScript("03_control_flow/test_nested_if.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "nested if test should return 1";
}

TEST(IronCScriptTest, TestLocalVariable) {
    TestResult result = runScript("04_functions/test_local_variable.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "local variable test: a=10, b=20 should return 30";
}

TEST(IronCScriptTest, TestCompoundAdd) {
    TestResult result = runScript("02_operators/test_compound_add.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 15) << "compound add test: a+=5, a=10 should return 15";
}

TEST(IronCScriptTest, TestCompoundSub) {
    TestResult result = runScript("02_operators/test_compound_sub.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 7) << "compound sub test: a-=3, a=10 should return 7";
}

TEST(IronCScriptTest, TestCompoundMul) {
    TestResult result = runScript("02_operators/test_compound_mul.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 12) << "compound mul test: a*=4, a=3 should return 12";
}

TEST(IronCScriptTest, TestCompoundDiv) {
    TestResult result = runScript("02_operators/test_compound_div.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 5) << "compound div test: a/=4, a=20 should return 5";
}

TEST(IronCScriptTest, TestTernaryOperator) {
    TestResult result = runScript("10_advanced/test_ternary.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 100) << "ternary operator test: (1 > 0) ? 100 : 200 should return 100";
}

TEST(IronCScriptTest, TestTernaryOperatorFalse) {
    TestResult result = runScript("10_advanced/test_ternary2.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 200) << "ternary operator test: (1 > 2) ? 100 : 200 should return 200";
}

TEST(IronCScriptTest, TestArray) {
    TestResult result = runScript("05_arrays/test_array.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "array test should complete";
}

TEST(IronCScriptTest, TestStringManipulation) {
    TestResult result = runScript("09_stdlib/string/test_string_manipulation.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "string manipulation test should complete";
}

// 数组和指针测试
TEST(IronCScriptTest, TestArrayMinimal) {
    TestResult result = runScript("05_arrays/test_array_minimal.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "array minimal test should complete";
}

TEST(IronCScriptTest, TestArraySimple) {
    TestResult result = runScript("05_arrays/test_array_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "array simple test should complete";
}

TEST(IronCScriptTest, TestArrayAssign) {
    TestResult result = runScript("05_arrays/test_array_assign.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "array assign test should complete";
}

TEST(IronCScriptTest, TestArraySingle) {
    TestResult result = runScript("05_arrays/test_array_single.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "array single test should complete";
}

TEST(IronCScriptTest, TestPointer) {
    TestResult result = runScript("06_pointers/test_pointer.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "pointer test should complete";
}

TEST(IronCScriptTest, TestAddressOf) {
    TestResult result = runScript("06_pointers/test_address_of.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 42) << "address of test should return 42";
}

// 控制流测试
TEST(IronCScriptTest, TestBreakWhile) {
    TestResult result = runScript("03_control_flow/test_break_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "break while test should complete";
}

TEST(IronCScriptTest, TestBreakFor) {
    TestResult result = runScript("03_control_flow/test_break_for.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "break for test should complete";
}

TEST(IronCScriptTest, TestBreakDoWhile) {
    TestResult result = runScript("03_control_flow/test_break_dowhile.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "break do-while test should complete";
}

TEST(IronCScriptTest, TestContinue) {
    TestResult result = runScript("03_control_flow/test_continue.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "continue test should complete";
}

TEST(IronCScriptTest, TestContinueWhile) {
    TestResult result = runScript("03_control_flow/test_continue_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "continue while test should complete";
}

TEST(IronCScriptTest, TestContinueFor) {
    TestResult result = runScript("03_control_flow/test_continue_for.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "continue for test should complete";
}

// 类型转换测试
TEST(IronCScriptTest, TestCast) {
    TestResult result = runScript("10_advanced/test_cast_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "cast test should complete";
}

TEST(IronCScriptTest, TestCastSimple) {
    TestResult result = runScript("10_advanced/test_cast_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "cast simple test should complete";
}

// 字符串函数测试
TEST(IronCScriptTest, TestStringFunctions) {
    TestResult result = runScript("09_stdlib/string/test_string_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "string functions test should complete";
}

TEST(IronCScriptTest, TestStrlen) {
    TestResult result = runScript("09_stdlib/string/test_strlen.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "strlen test should complete";
}

TEST(IronCScriptTest, TestStrcpy) {
    TestResult result = runScript("09_stdlib/string/test_strcpy_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "strcpy test should complete";
}

// 内存函数测试
TEST(IronCScriptTest, TestMemoryFunctions) {
    TestResult result = runScript("09_stdlib/memory/test_memory_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "memory functions test should complete";
}

TEST(IronCScriptTest, TestMalloc) {
    TestResult result = runScript("09_stdlib/memory/test_string_malloc.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "malloc test should complete";
}

// 数学函数测试
TEST(IronCScriptTest, TestMathFunctions) {
    TestResult result = runScript("09_stdlib/math/test_math_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "math functions test should complete";
}

TEST(IronCScriptTest, TestAbs) {
    TestResult result = runScript("09_stdlib/math/test_abs_only.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "abs test should complete";
}

// 标准库函数测试
TEST(IronCScriptTest, TestStdlib) {
    TestResult result = runScript("09_stdlib/test_stdlib.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "stdlib test should complete";
}

TEST(IronCScriptTest, TestSystemFunctions) {
    TestResult result = runScript("09_stdlib/test_system_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "system functions test should complete";
}

// 输入输出测试
TEST(IronCScriptTest, TestScanf) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf.c", "test_scanf_default.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 15) << "scanf with input 5 and 10 should return 15";
}

TEST(IronCScriptTest, TestScanfBasic) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf_basic.c", "test_scanf_basic_default.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 35) << "scanf basic with input 25 should return 35";
}

TEST(IronCScriptTest, TestScanfWithInput42) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf_single.c", "test_int_42.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 42) << "scanf with input 42 should return 42";
}

TEST(IronCScriptTest, TestScanfWithInput10_20) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf.c", "test_int_10_20.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "scanf with input 10 and 20 should return 30 (10+20)";
}

TEST(IronCScriptTest, TestScanfWithInput100_200_300) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf.c", "test_int_100_200_300.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 300) << "scanf with input 100,200 should return 300 (100+200)";
}

TEST(IronCScriptTest, TestScanfWithNameInput) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf_string.c", "test_name_input.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "scanf with name input 'John' should return 1 (successful read)";
}

TEST(IronCScriptTest, TestScanfSingleWithInput10) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf_single.c", "test_int_10_20.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "scanf single with input 10 should return 10";
}

TEST(IronCScriptTest, TestScanfSingleWithInput100) {
    TestResult result = runScriptWithInput("09_stdlib/stdio/test_scanf_single.c", "test_int_100_200_300.txt");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 100) << "scanf single with input 100 should return 100";
}

// 复杂功能测试
TEST(IronCScriptTest, TestAllFeatures) {
    TestResult result = runScript("10_advanced/test_all_features.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "all features test should complete";
}

TEST(IronCScriptTest, TestDetailed) {
    TestResult result = runScript("10_advanced/test_detailed.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "detailed test should complete";
}

TEST(IronCScriptTest, TestNewFeatures) {
    TestResult result = runScript("10_advanced/test_new_features.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "new features test should complete";
}

// 边界情况测试
TEST(IronCScriptTest, TestBoundaryCases) {
    TestResult result = runScript("11_edge_cases/test_boundary_cases.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "boundary cases test should complete";
}

TEST(IronCScriptTest, TestErrorHandling) {
    TestResult result = runScript("11_edge_cases/test_error_handling.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "error handling test should complete";
}

// 语法和语义测试
TEST(IronCScriptTest, TestSyntaxError) {
    TestResult result = runScript("11_edge_cases/test_syntax_error.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "syntax error test should complete";
}

TEST(IronCScriptTest, TestSemantic) {
    TestResult result = runScript("11_edge_cases/test_semantic.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "semantic test should complete";
}

// 注释测试
TEST(IronCScriptTest, TestComments) {
    TestResult result = runScript("10_advanced/test_comments.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "comments test should complete";
}

TEST(IronCScriptTest, TestMultiComment) {
    TestResult result = runScript("10_advanced/test_multi_comment.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "multi comment test should complete";
}

// 枚举测试
TEST(IronCScriptTest, TestEnum) {
    TestResult result = runScript("08_enums/test_enum.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 6) << "enum test should return BLUE (6)";
}

TEST(IronCScriptTest, TestEnumBasic) {
    TestResult result = runScript("08_enums/test_enum_basic.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "enum basic test should return A (0)";
}

// 结构体测试
TEST(IronCScriptTest, TestStruct) {
    TestResult result = runScript("07_structs/test_struct.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "struct test should return 30 (10+20)";
}

TEST(IronCScriptTest, TestStruct2) {
    TestResult result = runScript("07_structs/test_struct2.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "struct2 test should return 10";
}

// 文件函数测试
TEST(IronCScriptTest, TestFileFunctions) {
    TestResult result = runScript("09_stdlib/stdio/test_file_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "file functions test should complete";
}

TEST(IronCScriptTest, TestFileWrite) {
    TestResult result = runScript("09_stdlib/stdio/test_file_write.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "file write test should complete";
}

TEST(IronCScriptTest, TestFileRead) {
    TestResult result = runScript("09_stdlib/stdio/test_file_read.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "file read test should complete";
}

TEST(IronCScriptTest, TestFprintf) {
    TestResult result = runScript("09_stdlib/stdio/test_fprintf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "fprintf test should complete";
}

TEST(IronCScriptTest, TestFscanf) {
    TestResult result = runScript("09_stdlib/stdio/test_fscanf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "fscanf test should complete";
}

TEST(IronCScriptTest, TestFileReadSimple) {
    TestResult result = runScript("09_stdlib/stdio/test_file_read_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "file read simple test should complete";
}

// 时间函数测试
TEST(IronCScriptTest, TestTimeFunctions) {
    TestResult result = runScript("09_stdlib/time/test_time_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "time functions test should complete";
}

// 添加更多测试用例...

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}