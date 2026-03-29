#include "IronCScript.h"
#include <iostream>

int main() {
    cse::IronCScript engine;
    
    // 测试简单脚本执行
    std::cout << "=== 测试1: 简单加法运算 ===" << std::endl;
    const char* script1 = R"(
        int main() {
            int a = 10;
            int b = 20;
            int c = a + b;
            return c;
        }
    )";
    
    int result1 = engine.executeString(script1);
    std::cout << "结果: " << result1 << " (预期: 30)" << std::endl;
    if (result1 == 30) {
        std::cout << "✅ 测试通过!" << std::endl;
    } else {
        std::cout << "❌ 测试失败!" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试函数调用
    std::cout << "=== 测试2: 函数调用 ===" << std::endl;
    const char* script2 = R"(
        int add(int a, int b) {
            return a + b;
        }
        
        int main() {
            return add(15, 25);
        }
    )";
    
    int result2 = engine.executeString(script2);
    std::cout << "结果: " << result2 << " (预期: 40)" << std::endl;
    if (result2 == 40) {
        std::cout << "✅ 测试通过!" << std::endl;
    } else {
        std::cout << "❌ 测试失败!" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试控制流
    std::cout << "=== 测试3: 控制流（for循环） ===" << std::endl;
    const char* script3 = R"(
        int main() {
            int sum = 0;
            for (int i = 1; i <= 5; i++) {
                sum += i;
            }
            return sum;
        }
    )";
    
    int result3 = engine.executeString(script3);
    std::cout << "结果: " << result3 << " (预期: 15)" << std::endl;
    if (result3 == 15) {
        std::cout << "✅ 测试通过!" << std::endl;
    } else {
        std::cout << "❌ 测试失败!" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试递归函数
    std::cout << "=== 测试4: 递归函数 ===" << std::endl;
    const char* script4 = R"(
        int factorial(int n) {
            if (n <= 1) {
                return 1;
            } else {
                return n * factorial(n - 1);
            }
        }
        
        int main() {
            return factorial(5);
        }
    )";
    
    int result4 = engine.executeString(script4);
    std::cout << "结果: " << result4 << " (预期: 120)" << std::endl;
    if (result4 == 120) {
        std::cout << "✅ 测试通过!" << std::endl;
    } else {
        std::cout << "❌ 测试失败!" << std::endl;
    }
    std::cout << std::endl;
    
    // 测试浮点数
    std::cout << "=== 测试5: 浮点数运算 ===" << std::endl;
    const char* script5 = R"(
        int main() {
            double a = 10.5;
            double b = 20.5;
            double c = a + b;
            return (int)c;
        }
    )";
    
    int result5 = engine.executeString(script5);
    std::cout << "结果: " << result5 << " (预期: 31)" << std::endl;
    if (result5 == 31) {
        std::cout << "✅ 测试通过!" << std::endl;
    } else {
        std::cout << "❌ 测试失败!" << std::endl;
    }
    
    return 0;
}