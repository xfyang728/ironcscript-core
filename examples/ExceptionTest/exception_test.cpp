#include <iostream>
#include <CScriptEngine.h>

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

int main() {
    std::cout << "=== Exception Handling Test ===" << std::endl;

    // 测试1: 基本异常处理
    std::cout << "\nTest 1: Basic Exception Handling" << std::endl;
    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("divide", divide);

        const char* testScript = R"(
            extern int divide(int a, int b);
            
            int main() {
                try {
                    int result = divide(10, 0);
                    return result;
                } catch (const char* e) {
                    print("Caught exception: ", e);
                    return 1;
                }
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    // 测试2: 未捕获的异常
    std::cout << "\nTest 2: Uncaught Exception" << std::endl;
    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("divide", divide);

        const char* testScript = R"(
            extern int divide(int a, int b);
            
            int main() {
                int result = divide(10, 0);
                return result;
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed (expected): " << engine.getLastError() << std::endl;
        }
    }

    // 测试3: 资源清理
    std::cout << "\nTest 3: Resource Cleanup" << std::endl;
    {
        cse::CScriptEngine engine;

        const char* testScript = R"(
            int main() {
                try {
                    print("Allocating resource...");
                    // 模拟资源分配
                    throw "Resource allocation failed";
                } catch (const char* e) {
                    print("Caught exception: ", e);
                    print("Cleaning up resources...");
                    return 1;
                }
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    // 测试4: 嵌套异常
    std::cout << "\nTest 4: Nested Exceptions" << std::endl;
    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("divide", divide);

        const char* testScript = R"(
            extern int divide(int a, int b);
            
            int nested_function() {
                return divide(10, 0);
            }
            
            int main() {
                try {
                    int result = nested_function();
                    return result;
                } catch (const char* e) {
                    print("Caught exception in main: ", e);
                    return 1;
                }
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    std::cout << "\n=== Exception Handling Test Complete ===" << std::endl;
    return 0;
}
