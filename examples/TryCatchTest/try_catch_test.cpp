#include <iostream>
#include <CScriptEngine.h>

int divide(int a, int b) {
    if (b == 0) {
        // 直接返回 -1 而不是抛出异常，因为 FFI 会捕获异常并返回 -1
        return -1;
    }
    return a / b;
}

int main() {
    std::cout << "=== Try-Catch Test ===" << std::endl;

    // 测试1: 基本的try-catch
    std::cout << "\nTest 1: Basic Try-Catch" << std::endl;
    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("divide", divide);

        const char* testScript = R"(
            extern int divide(int a, int b);
            
            int main() {
                try {
                    int result = divide(10, 0);
                    if (result == -1) {
                        throw "Division by zero";
                    }
                    return result;
                } catch (char* e) {
                    printf("Caught exception: %s\n", e);
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

    // 测试2: 嵌套的try-catch
    std::cout << "\nTest 2: Nested Try-Catch" << std::endl;
    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("divide", divide);

        const char* testScript = R"(
            extern int divide(int a, int b);
            
            int nested_function() {
                try {
                    int result = divide(10, 0);
                    if (result == -1) {
                        throw "Division by zero";
                    }
                    return result;
                } catch (char* e) {
                    printf("Nested catch: %s\n", e);
                    throw e;
                }
            }
            
            int main() {
                try {
                    int result = nested_function();
                    return result;
                } catch (char* e) {
                    printf("Outer catch: %s\n", e);
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

    // 测试3: 多个catch块
    std::cout << "\nTest 3: Multiple Catch Blocks" << std::endl;
    {
        cse::CScriptEngine engine;

        const char* testScript = R"(
            int main() {
                try {
                    int choice = 2;
                    if (choice == 1) {
                        throw "String exception";
                    } else if (choice == 2) {
                        throw 42;
                    } else {
                        throw 3.14;
                    }
                } catch (char* e) {
                    printf("Caught string: %s\n", e);
                } catch (int i) {
                    printf("Caught int: %d\n", i);
                } catch (...) {
                    printf("Caught unknown exception\n");
                }
                return 0;
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    // 测试4: 手动throw表达式
    std::cout << "\nTest 4: Manual Throw Expression" << std::endl;
    {
        cse::CScriptEngine engine;

        const char* testScript = R"(
            int main() {
                try {
                    printf("Before throw\n");
                    throw "Manual exception";
                    printf("After throw\n");
                } catch (char* e) {
                    printf("Caught: %s\n", e);
                }
                return 0;
            }
        )";

        if (engine.execute(testScript)) {
            std::cout << "Script executed successfully, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    std::cout << "\n=== Try-Catch Test Complete ===" << std::endl;
    return 0;
}
