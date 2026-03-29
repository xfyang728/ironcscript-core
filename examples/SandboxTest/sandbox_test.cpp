#include <iostream>
#include "CScriptEngine.h"

int main() {
    cse::CScriptEngine engine;
    
    std::cout << "=== Memory Sandbox Test ===" << std::endl;
    
    // 测试 1: 执行时间限制
    std::cout << "\nTest 1: Execution Time Limit" << std::endl;
    {
        // 设置 1 秒的执行时间限制
        engine.setExecutionTimeLimit(1000);
        
        const char* testScript = R"(
            int main() {
                int i = 0;
                // 模拟长时间运行的操作
                for (int j = 0; j < 1000000000; j++) {
                    i++;
                }
                return i;
            }
        )";
        
        std::cout << "Executing long-running script..." << std::endl;
        bool result = engine.execute(testScript);
        
        if (!result) {
            std::cout << "Expected timeout: " << engine.getLastError() << std::endl;
        } else {
            std::cout << "Execution successful, return value: " << engine.getLastReturnValue() << std::endl;
        }
    }
    
    // 测试 2: 正常执行
    std::cout << "\nTest 2: Normal Execution" << std::endl;
    {
        // 设置 5 秒的执行时间限制
        engine.setExecutionTimeLimit(5000);
        
        const char* testScript = R"(
            int main() {
                int sum = 0;
                for (int i = 0; i < 1000000; i++) {
                    sum += i;
                }
                return sum;
            }
        )";
        
        std::cout << "Executing normal script..." << std::endl;
        bool result = engine.execute(testScript);
        
        if (result) {
            std::cout << "Execution successful, return value: " << engine.getLastReturnValue() << std::endl;
        } else {
            std::cout << "Unexpected failure: " << engine.getLastError() << std::endl;
        }
    }
    
    // 测试 3: 内存限制
    std::cout << "\nTest 3: Memory Limit" << std::endl;
    {
        // 设置 1MB 的内存限制
        engine.setMemoryLimit(1024 * 1024);
        
        const char* testScript = R"(
            int main() {
                // 尝试分配大量内存
                char* buffer = (char*)malloc(2 * 1024 * 1024);
                if (buffer) {
                    buffer[0] = 'a';
                    free(buffer);
                }
                return 0;
            }
        )";
        
        std::cout << "Executing memory-intensive script..." << std::endl;
        bool result = engine.execute(testScript);
        
        if (!result) {
            std::cout << "Expected memory limit exceeded: " << engine.getLastError() << std::endl;
        } else {
            std::cout << "Unexpected success, return value: " << engine.getLastReturnValue() << std::endl;
        }
    }
    
    // 测试 4: 获取当前内存使用量
    std::cout << "\nTest 4: Get Current Memory Usage" << std::endl;
    {
        engine.setMemoryLimit(10 * 1024 * 1024);
        
        const char* testScript = R"(
            int main() {
                return 42;
            }
        )";
        
        engine.execute(testScript);
        std::cout << "Current memory usage: " << engine.getCurrentMemoryUsage() << " bytes" << std::endl;
    }
    
    std::cout << "\n=== Sandbox Test Complete ===" << std::endl;
    return 0;
}