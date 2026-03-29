#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

#include <IronCScript.h>

extern "C" {

// ============================================================================
// 基础数学函数 - 演示 Script → Native 调用
// ============================================================================

double add_double(double a, double b) {
    std::cout << "  [Native] add_double(" << a << ", " << b << ") = " << (a + b) << std::endl;
    return a + b;
}

double add_double_per(double a, double b) {
    return a + b;
}

double subtract_double(double a, double b) {
    std::cout << "  [Native] subtract_double(" << a << ", " << b << ") = " << (a - b) << std::endl;
    return a - b;
}

double multiply_double(double a, double b) {
    std::cout << "  [Native] multiply_double(" << a << ", " << b << ") = " << (a * b) << std::endl;
    return a * b;
}

double divide_double(double a, double b) {
    if (b == 0.0) {
        std::cout << "  [Native] divide_double: ERROR - division by zero!" << std::endl;
        return 0.0;
    }
    std::cout << "  [Native] divide_double(" << a << ", " << b << ") = " << (a / b) << std::endl;
    return a / b;
}

int add_int(int a, int b) {
    std::cout << "  [Native] add_int(" << a << ", " << b << ") = " << (a + b) << std::endl;
    return a + b;
}

int multiply_int(int a, int b) {
    std::cout << "  [Native] multiply_int(" << a << ", " << b << ") = " << (a * b) << std::endl;
    return a * b;
}

double sqrt_double(double x) {
    if (x < 0.0) {
        std::cout << "  [Native] sqrt_double: ERROR - negative input!" << std::endl;
        return 0.0;
    }
    double result = std::sqrt(x);
    std::cout << "  [Native] sqrt_double(" << x << ") = " << result << std::endl;
    return result;
}

double pow_double(double base, double exp) {
    double result = std::pow(base, exp);
    std::cout << "  [Native] pow_double(" << base << ", " << exp << ") = " << result << std::endl;
    return result;
}

// ============================================================================
// 字符串处理函数 - 演示字符串参数传递
// ============================================================================

int string_length(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    std::cout << "  [Native] string_length(\"" << str << "\") = " << len << std::endl;
    return len;
}

int string_compare(const char* s1, const char* s2) {
    int result = strcmp(s1, s2);
    std::cout << "  [Native] string_compare(\"" << s1 << "\", \"" << s2 << "\") = " << result << std::endl;
    return result;
}

void print_string(const char* str) {
    std::cout << "  [Native] print_string: \"" << str << "\"" << std::endl;
}

// ============================================================================
// 数组处理函数 - 演示数组指针传递
// ============================================================================

double array_sum(double* arr, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    std::cout << "  [Native] array_sum(size=" << size << ") = " << sum << std::endl;
    return sum;
}

double array_average(double* arr, int size) {
    if (size == 0) return 0.0;
    double sum = array_sum(arr, size);
    return sum / size;
}

double array_max(double* arr, int size) {
    if (size == 0) return 0.0;
    double maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    std::cout << "  [Native] array_max(size=" << size << ") = " << maxVal << std::endl;
    return maxVal;
}

// ============================================================================
// 结构体处理函数 - 演示结构体指针传递
// ============================================================================

struct Point {
    int x;
    int y;
};

int process_point(void* ptr) {
    Point* p = static_cast<Point*>(ptr);
    std::cout << "  [Native] process_point(ptr=" << ptr << ", x=" << p->x << ", y=" << p->y << ")" << std::endl;
    return p->x + p->y;
}

// ============================================================================
// 回调机制 - 演示 Native → Script 调用
// ============================================================================

using ScriptCallback = int(*)(int);

static ScriptCallback g_intCallback = nullptr;
static ScriptCallback g_transformCallback = nullptr;

void registerIntCallback(ScriptCallback cb) {
    std::cout << "  [Native] registerIntCallback(0x" << std::hex << reinterpret_cast<void*>(cb) << std::dec << ")" << std::endl;
    g_intCallback = cb;
}

void registerTransformCallback(ScriptCallback cb) {
    std::cout << "  [Native] registerTransformCallback(0x" << std::hex << reinterpret_cast<void*>(cb) << std::dec << ")" << std::endl;
    g_transformCallback = cb;
}

int callScriptCallback(int value) {
    std::cout << "  [Native] callScriptCallback(" << value << ")";
    if (g_intCallback) {
        int result = g_intCallback(value);
        std::cout << " -> script returned " << result << std::endl;
        return result;
    }
    std::cout << " -> NO CALLBACK REGISTERED!" << std::endl;
    return -1;
}

int callTransformCallback(int value) {
    std::cout << "  [Native] callTransformCallback(" << value << ")";
    if (g_transformCallback) {
        int result = g_transformCallback(value);
        std::cout << " -> script returned " << result << std::endl;
        return result;
    }
    std::cout << " -> NO CALLBACK REGISTERED!" << std::endl;
    return -1;
}

}

// ============================================================================
// 辅助函数
// ============================================================================

void printSeparator(const std::string& title) {
    std::cout << std::endl;
    std::cout << "=============================================================================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "=============================================================================" << std::endl;
}

void printSection(const std::string& title) {
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    std::cout << title << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
}

void waitForEnter() {
    std::cout << std::endl << "Press Enter to continue..." << std::endl;
    std::cin.get();
}

// ============================================================================
// 测试脚本内容
// ============================================================================

const char* testBasicMathScript = R"(
extern double add_double(double a, double b);
extern double multiply_double(double a, double b);
extern int add_int(int a, int b);

int main() {
    double d1 = add_double(1.5, 2.5);
    double d2 = multiply_double(3.0, 4.0);
    int i1 = add_int(10, 20);
    return i1;
}
)";

const char* testCallbackScript = R"(
extern void registerIntCallback(int(*)(int));
extern int callScriptCallback(int);

int my_callback(int x) {
    return x * 2;
}

int main() {
    registerIntCallback(my_callback);
    int result = callScriptCallback(5);
    return result;
}
)";

const char* testStringScript = R"(
extern int string_length(const char* str);
extern void print_string(const char* str);

int main() {
    print_string("Hello from IronCScript!");
    int len = string_length("IronCS");
    return len;
}
)";

const char* testArrayScript = R"(
extern double array_sum(double* arr, int size);
extern double array_average(double* arr, int size);

int main() {
    double arr[5];
    arr[0] = 1.0;
    arr[1] = 2.0;
    arr[2] = 3.0;
    arr[3] = 4.0;
    arr[4] = 5.0;
    double sum = array_sum(arr, 5);
    double avg = array_average(arr, 5);
    return (int)avg;
}
)";

const char* testStructScript = R"(
extern int process_point(void* ptr);

int main() {
    struct Point {
        int x;
        int y;
    };
    struct Point p;
    p.x = 10;
    p.y = 20;
    int result = process_point(&p);
    return result;
}
)";

// ============================================================================
// 主程序
// ============================================================================

int main() {
    std::cout << R"(
    ____             __        ____                 __        ____
   / __ \_________ _/ /_____ _/ / /     _____  ____/ /______/ / /
  / /_/ / ___/ / / / __/ __ `/ / / | | | / / / / / __/ ___/ / /
 / ____/ /  / /_/ / /_/ /_/ / / /| |_| |/ / /_/ / /_/ /  / / /
/_/    /_/   \__,_/\__/\__,_/_/_/ |___/|___/\__,_/\__/_/  /_/_/

    )" << std::endl;

    std::cout << "FFI (Foreign Function Interface) Demo - Bidirectional Script/Native Calling" << std::endl;
    std::cout << "Version 1.0 - " << __DATE__ << std::endl;
    std::cout << std::endl;

    // =========================================================================
    // 第一部分：直接 C++ 测试
    // =========================================================================
    printSeparator("Part 1: Direct C++ Function Calls (Baseline)");

    printSection("1.1 Basic Math Functions");
    add_double(1.5, 2.5);
    multiply_double(3.0, 4.0);
    divide_double(10.0, 2.0);
    sqrt_double(16.0);

    printSection("1.2 Integer Functions");
    add_int(10, 20);
    multiply_int(6, 7);

    printSection("1.3 String Functions");
    string_length("Hello");
    string_compare("abc", "abc");
    print_string("Test string");

    printSection("1.4 Array Functions");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    array_sum(arr, 5);
    array_average(arr, 5);
    array_max(arr, 5);

    printSection("1.5 Struct Functions");
    Point p = {10, 20};
    process_point(&p);

    // =========================================================================
    // 第二部分：Script → Native 调用
    // =========================================================================
    printSeparator("Part 2: Script -> Native Calls (extern declarations)");

    printSection("2.1 Basic Math Script");
    std::cout << "Script:" << std::endl;
    std::cout << testBasicMathScript << std::endl;
    std::cout << "Expected: add_double(1.5, 2.5) + multiply_double(3.0, 4.0) + add_int(10, 20)" << std::endl;

    {
        cse::IronCScript engine;
        engine.registerNativeFunction("add_double", add_double);
        engine.registerNativeFunction("multiply_double", multiply_double);
        engine.registerNativeFunction("add_int", add_int);

        if (engine.execute(testBasicMathScript)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    printSection("2.2 String Script");
    std::cout << "Script:" << std::endl;
    std::cout << testStringScript << std::endl;

    {
        cse::IronCScript engine;
        engine.registerNativeFunction("string_length", string_length);
        engine.registerNativeFunction("print_string", print_string);

        if (engine.execute(testStringScript)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    printSection("2.3 Array Script");
    std::cout << "Script:" << std::endl;
    std::cout << testArrayScript << std::endl;

    {
        cse::IronCScript engine;
        engine.registerNativeFunction("array_sum", array_sum);
        engine.registerNativeFunction("array_average", array_average);

        if (engine.execute(testArrayScript)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    printSection("2.4 Struct Script");
    std::cout << "Script:" << std::endl;
    std::cout << testStructScript << std::endl;

    {
        cse::IronCScript engine;
        engine.registerNativeFunction("process_point", process_point);

        if (engine.execute(testStructScript)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    // =========================================================================
    // 第三部分：Native → Script 回调
    // =========================================================================
    printSeparator("Part 3: Native -> Script Callbacks (register mechanism)");

    printSection("3.1 Callback Script");
    std::cout << "Script:" << std::endl;
    std::cout << testCallbackScript << std::endl;
    std::cout << "Flow: Script defines my_callback -> registers with Native -> Native calls it back" << std::endl;

    {
        cse::IronCScript engine;
        engine.registerNativeFunction("registerIntCallback", registerIntCallback);
        engine.registerNativeFunction("callScriptCallback", callScriptCallback);

        if (engine.execute(testCallbackScript)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    // =========================================================================
    // 第四部分：性能测试
    // =========================================================================
    printSeparator("Part 4: Performance Benchmark");

    printSection("4.1 Native Call Overhead (Pure C++ Direct Call)");
    {
        const int iterations = 1000000;
        volatile double a = 1.0, b = 2.0;
        volatile double result;

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            result = a + b;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Pure C++ arithmetic (" << iterations << " iterations): " << duration.count() << " us" << std::endl;
        std::cout << "Average per iteration: " << (double)duration.count() / iterations << " us" << std::endl;

        double (*fp)(double, double) = add_double_per;
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            result = fp(1.0, 2.0);
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Direct function pointer call (" << iterations << " iterations): " << duration.count() << " us" << std::endl;
        std::cout << "Average per call: " << (double)duration.count() / iterations << " us" << std::endl;
    }

    printSection("4.2 Script to Native Call Overhead (with Cache - First Run)");
    {
        const char* perfScript = R"(
            extern double add_double_per(double a, double b);
            int main() {
                double result = 0.0;
                int i = 0;
                while (i < 1000000) {
                    result = add_double_per(result, 1.0);
                    i = i + 1;
                }
                return (int)result;
            }
        )";

        cse::IronCScript engine;
        engine.registerNativeFunction("add_double_per", add_double_per);
        engine.setCacheEnabled(true);

        auto start = std::chrono::high_resolution_clock::now();
        if (!engine.execute(perfScript)) {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        const int iterations = 1000000;
        std::cout << "Script->Native call (" << iterations << " extern calls): " << duration.count() << " us" << std::endl;
        std::cout << "Average per call: " << (double)duration.count() / iterations << " us" << std::endl;
        std::cout << "vs Direct C++ call: ~0.001557 us" << std::endl;
        std::cout << "Overhead ratio: " << (double)duration.count() / iterations / 0.001557 << "x slower" << std::endl;
    }

    printSection("4.3 Script to Native Call Overhead (with Cache - Load from Cache)");
    {
        const char* perfScript = R"(
            extern double add_double_per(double a, double b);
            int main() {
                double result = 0.0;
                int i = 0;
                while (i < 1000000) {
                    result = add_double_per(result, 1.0);
                    i = i + 1;
                }
                return (int)result;
            }
        )";

        cse::IronCScript engine;
        engine.registerNativeFunction("add_double_per", add_double_per);
        engine.setCacheEnabled(true);

        auto start = std::chrono::high_resolution_clock::now();
        if (!engine.execute(perfScript)) {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        const int iterations = 1000000;
        std::cout << "Script->Native call (" << iterations << " extern calls): " << duration.count() << " us" << std::endl;
        std::cout << "Average per call: " << (double)duration.count() / iterations << " us" << std::endl;
        std::cout << "vs Direct C++ call: ~0.001557 us" << std::endl;
        std::cout << "Overhead ratio: " << (double)duration.count() / iterations / 0.001557 << "x slower" << std::endl;
    }

    // =========================================================================
    // 完成
    // =========================================================================
    printSeparator("Demo Complete");

    std::cout << R"(
    Summary:
    --------
    This demo showed two-way communication between IronCScript scripts
    and Native C++ code:

    1. Script -> Native (extern):
       - Scripts declare external functions with 'extern' keyword
       - Native functions are registered with the engine
       - Functions are linked at runtime by name

    2. Native -> Script (callbacks):
       - Scripts register callback functions with Native
       - Native can invoke these callbacks by function pointer
       - Enables event-driven and reverse-calling patterns

    Key Files:
    ----------
    - src/backend/FFIRegistry.h      : Native function registration
    - src/backend/ScriptFunctionRegistry.h : Script function registration
    - src/frontend/parser/IronCS.g4  : Grammar with extern/register support
    - docs/design/ffi_best_practices.md : Complete FFI design documentation

    Next Steps:
    -----------
    - Implement JIT compilation for callback performance
    - Add more FFI type support (structs, pointers)
    - Create FFI binding generator for automatic wrapper creation
    )" << std::endl;

    return 0;
}