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

void cleanupTestOutput() {
    std::string outputDir = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output";
    std::string searchPattern = outputDir + "\\test_output_*.txt";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string fullPath = outputDir + "\\" + findData.cFileName;
            DeleteFileA(fullPath.c_str());
        } while (FindNextFileA(hFind, &findData));
        FindClose(hFind);
    }
}

bool findOutputLine(const std::string& outputPath, const std::string& searchText) {
    std::ifstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(outputFile, line)) {
        if (line.find(searchText) != std::string::npos &&
            line.find("[DEBUG]") == std::string::npos) {
            outputFile.close();
            return true;
        }
    }
    outputFile.close();
    return false;
}

std::string readFullOutput(const std::string& outputPath) {
    std::string fullOutput;
    std::ifstream outputFile(outputPath);
    if (outputFile.is_open()) {
        std::string line;
        while (std::getline(outputFile, line)) {
            fullOutput += line;
            fullOutput += "\n";
        }
        outputFile.close();
    }
    return fullOutput;
}

TestResult runScript(const char* scriptPath) {
    TestResult result;
    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    std::string scriptFullPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\scripts\\" + std::string(scriptPath);
    std::string exeFullPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\build\\IronCScriptCLI.exe";

    ProcessRunner::ProcessResult processResult = ProcessRunner::runProcess(
        exeFullPath,
        "\"" + scriptFullPath + "\"",
        outputPath,
        15000
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
    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    std::string inputFullPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\inputs\\" + std::string(inputPath);
    std::string scriptFullPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\scripts\\" + std::string(scriptPath);
    std::string exeFullPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\build\\IronCScriptCLI.exe";

    std::string arguments = "\"" + scriptFullPath + "\"";

    ProcessRunner::ProcessResult processResult = ProcessRunner::runProcessWithInput(
        exeFullPath,
        arguments,
        inputFullPath,
        outputPath,
        15000
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

// ==================== 01_basic ====================

TEST(IronCScriptTest, TestChar) {
    TestResult result = runScript("01_basic/test_char.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 65) << "char test should return ASCII value of 'A' (65)";
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

TEST(IronCScriptTest, TestFloat) {
    TestResult result = runScript("01_basic/test_simple_float.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "float test should return 1 (1.0 cast to int)";
}

// ==================== 02_operators ====================

TEST(IronCScriptTest, TestSubtraction) {
    TestResult result = runScript("02_operators/test_subtraction.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 3) << "subtraction test: 5-2 should return 3";
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

TEST(IronCScriptTest, TestDoubleBasic) {
    TestResult result = runScript("02_operators/test_double_basic.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 4) << "double basic test should return 4 (1.5+2.5)";
}

TEST(IronCScriptTest, TestDoubleArithOps) {
    TestResult result = runScript("02_operators/test_double_arith_ops.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    double expected = (5.0 - 3.0) + (5.0 * 3.0) + (5.0 / 3.0) + 2.0;
    EXPECT_EQ(result.returnValue, static_cast<int>(expected)) << "double arith ops test";
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

TEST(IronCScriptTest, TestInc) {
    TestResult result = runScript("02_operators/test_inc.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 8) << "inc test: a=5, a++, a++, a++, return a=8";
}

TEST(IronCScriptTest, TestDec) {
    TestResult result = runScript("02_operators/test_dec.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 2) << "dec test: a=5, a--, a--, a--, return a=2";
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
    TestResult result = runScript("02_operators/test_ternary.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 100) << "ternary operator test: (1 > 0) ? 100 : 200 should return 100";
}

TEST(IronCScriptTest, TestTernaryOperatorFalse) {
    TestResult result = runScript("02_operators/test_ternary2.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 200) << "ternary operator test: (1 > 2) ? 100 : 200 should return 200";
}

TEST(IronCScriptTest, TestNewFeatures) {
    TestResult result = runScript("02_operators/test_new_features.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 24) << "new features test should return 24";
}

// ==================== 03_control_flow ====================

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

TEST(IronCScriptTest, TestBreakWhile) {
    TestResult result = runScript("03_control_flow/test_break_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "break while test should return 10";
}

TEST(IronCScriptTest, TestBreakFor) {
    TestResult result = runScript("03_control_flow/test_break_for.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "break for test should return 10";
}

TEST(IronCScriptTest, TestBreakDoWhile) {
    TestResult result = runScript("03_control_flow/test_break_dowhile.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "break do-while test should return 10";
}

TEST(IronCScriptTest, TestContinue) {
    TestResult result = runScript("03_control_flow/test_continue.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 40) << "continue test should return 40";
}

TEST(IronCScriptTest, TestContinueWhile) {
    TestResult result = runScript("03_control_flow/test_continue_while.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 8) << "continue while test should return 8";
}

TEST(IronCScriptTest, TestContinueFor) {
    TestResult result = runScript("03_control_flow/test_continue_for.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 25) << "continue for test should return 25";
}

// ==================== 04_functions ====================

TEST(IronCScriptTest, TestFunctionCall) {
    TestResult result = runScript("04_functions/test_function_call.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 8) << "function call test: add(5,3) should return 8";
}

TEST(IronCScriptTest, TestSubExpressionParam) {
    TestResult result = runScript("04_functions/test_sub_expression_param.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 18) << "sub expression param test: sub(4, a-b, a+b) should return 18";
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

TEST(IronCScriptTest, TestGlobalVariable) {
    TestResult result = runScript("04_functions/test_global_variable.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "global variable test should return 10";
}

TEST(IronCScriptTest, TestLocalVariable) {
    TestResult result = runScript("04_functions/test_local_variable.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "local variable test: a=10, b=20 should return 30";
}

// ==================== 05_arrays ====================

TEST(IronCScriptTest, TestArray) {
    TestResult result = runScript("05_arrays/test_array.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 15) << "array test should return 15";
}

TEST(IronCScriptTest, TestArrayMinimal) {
    TestResult result = runScript("05_arrays/test_array_minimal.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "array minimal test should return 0";
}

TEST(IronCScriptTest, TestArraySimple) {
    TestResult result = runScript("05_arrays/test_array_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 15) << "array simple test should return 15";
}

TEST(IronCScriptTest, TestArrayAssign) {
    TestResult result = runScript("05_arrays/test_array_assign.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 60) << "array assign test should return 60";
}

TEST(IronCScriptTest, TestArraySingle) {
    TestResult result = runScript("05_arrays/test_array_single.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "array single test should return 1";
}

// ==================== 06_pointers ====================

TEST(IronCScriptTest, TestPointer) {
    TestResult result = runScript("06_pointers/test_pointer.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 20) << "pointer test should return 20";
}

TEST(IronCScriptTest, TestAddressOf) {
    TestResult result = runScript("06_pointers/test_address_of.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 42) << "address of test should return 42";
}

TEST(IronCScriptTest, TestCast) {
    TestResult result = runScript("06_pointers/test_cast.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "cast test should return 0";
}

TEST(IronCScriptTest, TestCastSimple) {
    TestResult result = runScript("06_pointers/test_cast_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "cast simple test should return 0";
}

// ==================== 07_structs ====================

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

// ==================== 08_enums ====================

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

// ==================== 09_stdlib ====================

TEST(IronCScriptTest, TestPrintfInt) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_printf_int.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 1) << "printf int test should return 1";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "x = 1"))
        << "Output should contain 'x = 1' from printf, got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestDoublePow) {
    TestResult result = runScript("09_stdlib/math/test_pow.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 256) << "double pow test should return 256 (2^8)";
}

TEST(IronCScriptTest, TestPuts) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_puts.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "puts test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "Hello, World!"))
        << "Output should contain 'Hello, World!' from puts, got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestPrintf) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_printf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "printf test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "Hello, World!"))
        << "Output should contain 'Hello, World!' from printf, got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestStringFunctions) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/string/test_string_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "string functions test should complete";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "strlen"))
        << "Output should contain 'strlen', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestStrlen) {
    TestResult result = runScript("09_stdlib/string/test_strlen.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "strlen test should complete";
}

TEST(IronCScriptTest, TestStrcpy) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/string/test_strcpy_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_GE(result.returnValue, 0) << "strcpy test should complete";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "Hello"))
        << "Output should contain 'Hello', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestMemoryFunctions) {
    TestResult result = runScript("09_stdlib/memory/test_memory_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "memory functions test should return 0";
}

TEST(IronCScriptTest, TestMalloc) {
    TestResult result = runScript("09_stdlib/memory/test_string_malloc.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "malloc test should return 0";
}

TEST(IronCScriptTest, TestMathFunctions) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/math/test_math_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "math functions test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "sqrt"))
        << "Output should contain 'sqrt', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestAbs) {
    TestResult result = runScript("09_stdlib/math/test_abs_only.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "abs test should return 0";
}

TEST(IronCScriptTest, TestSystemFunctions) {
    TestResult result = runScript("09_stdlib/system/test_system_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "system functions test should complete";
}

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

TEST(IronCScriptTest, TestFileFunctions) {
    TestResult result = runScript("09_stdlib/stdio/test_file_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "file functions test should return 0";
}

TEST(IronCScriptTest, TestFileWrite) {
    TestResult result = runScript("09_stdlib/stdio/test_file_write.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "file write test should return 0";
}

TEST(IronCScriptTest, TestFileRead) {
    TestResult result = runScript("09_stdlib/stdio/test_file_read.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "file read test should return 0";
}

TEST(IronCScriptTest, TestFprintf) {
    TestResult result = runScript("09_stdlib/stdio/test_fprintf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fprintf test should return 0";
}

TEST(IronCScriptTest, TestFscanf) {
    TestResult result = runScript("09_stdlib/stdio/test_fscanf.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fscanf test should return 0";
}

TEST(IronCScriptTest, TestFileReadSimple) {
    TestResult result = runScript("09_stdlib/stdio/test_file_read_simple.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "file read simple test should return 0";
}

TEST(IronCScriptTest, TestTimeFunctions) {
    TestResult result = runScript("09_stdlib/time/test_time_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "time functions test should complete";
}

TEST(IronCScriptTest, TestStringExtraFunctions) {
    TestResult result = runScript("09_stdlib/string/test_string_extra_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "string extra functions test should complete";
}

TEST(IronCScriptTest, TestCharClassification) {
    TestResult result = runScript("09_stdlib/string/test_char_classification.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "char classification test should complete";
}

TEST(IronCScriptTest, TestCaseConversion) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/string/test_case_conversion.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "case conversion test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "a"))  // toupper('a') = 'A'
        << "Output should contain 'a' (tolower result), got: " << readFullOutput(outputPath);
    EXPECT_TRUE(findOutputLine(outputPath, "A"))  // toupper('a') = 'A'
        << "Output should contain 'A' (toupper result), got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestMemoryAllocFunctions) {
    TestResult result = runScript("09_stdlib/memory/test_memory_alloc_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "memory alloc functions test should complete";
}

TEST(IronCScriptTest, TestMallocSimple) {
    TestResult result = runScript("09_stdlib/memory/test_malloc.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "malloc simple test should return 0";
}

TEST(IronCScriptTest, TestMathExtraFunctions) {
    TestResult result = runScript("09_stdlib/math/test_math_extra_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "math extra functions test should return 0";
}

TEST(IronCScriptTest, TestSqrt) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/math/test_sqrt_only.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 2) << "sqrt test should return 2 (sqrt(4.0))";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "4.0"))
        << "Output should contain '4.0' (sqrt input), got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestPowDebug) {
    TestResult result = runScript("09_stdlib/math/test_pow_debug.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 256) << "pow debug test should return 256 (2^8)";
}

TEST(IronCScriptTest, TestOtherFunctions) {
    TestResult result = runScript("09_stdlib/other/test_other_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "other functions test should complete";
}

TEST(IronCScriptTest, TestSystemFunctionsDetailed) {
    TestResult result = runScript("09_stdlib/system/test_system_functions.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "system functions detailed test should complete";
}

TEST(IronCScriptTest, TestFileOperations) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_file_operations.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "file operations test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fopen/fclose test"))
        << "Output should contain 'fopen/fclose test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFread) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fread.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fread test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fread test"))
        << "Output should contain 'fread test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFwrite) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fwrite.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fwrite test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fwrite test"))
        << "Output should contain 'fwrite test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFseek) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fseek.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fseek test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fseek test"))
        << "Output should contain 'fseek test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFtell) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_ftell.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "ftell test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "ftell test"))
        << "Output should contain 'ftell test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestRewind) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_rewind.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "rewind test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "rewind test"))
        << "Output should contain 'rewind test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFeof) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_feof.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "feof test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "feof test"))
        << "Output should contain 'feof test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFerror) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_ferror.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "ferror test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "ferror test"))
        << "Output should contain 'ferror test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestClearerr) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_clearerr.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "clearerr test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "clearerr test"))
        << "Output should contain 'clearerr test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFgets) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fgets.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fgets test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fgets test"))
        << "Output should contain 'fgets test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFputs) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fputs.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fputs test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fputs test"))
        << "Output should contain 'fputs test', got: " << readFullOutput(outputPath);
}

TEST(IronCScriptTest, TestFflush) {
    cleanupTestOutput();
    TestResult result = runScript("09_stdlib/stdio/test_fflush.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "fflush test should return 0";

    std::string outputPath = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\test_output.txt";
    EXPECT_TRUE(findOutputLine(outputPath, "fflush test"))
        << "Output should contain 'fflush test', got: " << readFullOutput(outputPath);
}

// ==================== 11_edge_cases ====================

TEST(IronCScriptTest, TestBoundaryCases) {
    TestResult result = runScript("11_edge_cases/test_boundary_cases.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 102) << "boundary cases test should return 102";
}

TEST(IronCScriptTest, TestErrorHandling) {
    TestResult result = runScript("11_edge_cases/test_error_handling.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "error handling test should complete";
}

TEST(IronCScriptTest, TestSyntaxError) {
    TestResult result = runScript("11_edge_cases/test_syntax_error.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "syntax error test should return 30";
}

TEST(IronCScriptTest, TestSemantic) {
    TestResult result = runScript("11_edge_cases/test_semantic.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 0) << "semantic test should return 0";
}

// ==================== 12_comments ====================

TEST(IronCScriptTest, TestComments) {
    TestResult result = runScript("12_comments/test_comments.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 10) << "comments test should return 10";
}

TEST(IronCScriptTest, TestMultiComment) {
    TestResult result = runScript("12_comments/test_multi_comment.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 30) << "multi comment test should return 30";
}

// ==================== 13_comprehensive ====================

TEST(IronCScriptTest, TestAllFeatures) {
    TestResult result = runScript("13_comprehensive/test_all_features.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_EQ(result.returnValue, 171) << "all features test should return 171";
}

TEST(IronCScriptTest, TestDetailed) {
    TestResult result = runScript("13_comprehensive/test_detailed.c");
    EXPECT_FALSE(result.timedOut) << "Test should not time out";
    EXPECT_NE(result.returnValue, -1) << "detailed test should complete";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
