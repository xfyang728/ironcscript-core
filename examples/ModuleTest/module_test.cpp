#include <iostream>
#include <fstream>
#include <filesystem>
#include "IronCScript.h"

namespace fs = std::filesystem;

// 创建临时脚本文件
std::string createTempScriptFile(const std::string& content, const std::string& filename) {
    // 获取当前目录
    std::string currentDir = fs::current_path().string();
    std::string filePath = currentDir + "/" + filename;
    
    // 创建文件并写入内容
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to create temporary script file: " << filePath << std::endl;
        return "";
    }
    
    file << content;
    file.close();
    
    return filePath;
}

// 删除临时脚本文件
void deleteTempScriptFile(const std::string& filePath) {
    if (!filePath.empty()) {
        fs::remove(filePath);
    }
}

int main() {
    // 创建脚本引擎
    cse::IronCScript engine;
    
    // 测试模块系统
    std::cout << "Testing module system..." << std::endl;
    
    // 测试 1: 基本 import 语句
    std::cout << "\nTest 1: Basic import statement" << std::endl;
    std::string script1 = R"(
        // 导入模块
        import "math";
        
        int main() {
            return add(2, 3);
        }
    )";
    
    try {
        std::string scriptPath = createTempScriptFile(script1, "test1.c");
        if (!scriptPath.empty()) {
            engine.executeFile(scriptPath);
            deleteTempScriptFile(scriptPath);
            std::cout << "Test 1 passed!" << std::endl;
        } else {
            std::cerr << "Test 1 failed: Failed to create temporary script file" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Test 1 failed: " << e.what() << std::endl;
    }
    
    // 测试 2: import as 语句
    std::cout << "\nTest 2: Import as statement" << std::endl;
    std::string script2 = R"(
        // 导入模块并指定别名
        import "math" as m;
        
        int main() {
            return m::add(2, 3);
        }
    )";
    
    try {
        std::string scriptPath = createTempScriptFile(script2, "test2.c");
        if (!scriptPath.empty()) {
            engine.executeFile(scriptPath);
            deleteTempScriptFile(scriptPath);
            std::cout << "Test 2 passed!" << std::endl;
        } else {
            std::cerr << "Test 2 failed: Failed to create temporary script file" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Test 2 failed: " << e.what() << std::endl;
    }
    
    // 测试 3: 命名导入
    std::cout << "\nTest 3: Named import" << std::endl;
    std::string script3 = R"(
        // 只导入指定的符号
        import { add, subtract } from "math";
        
        int main() {
            return add(5, subtract(3, 1));
        }
    )";
    
    try {
        std::string scriptPath = createTempScriptFile(script3, "test3.c");
        if (!scriptPath.empty()) {
            engine.executeFile(scriptPath);
            deleteTempScriptFile(scriptPath);
            std::cout << "Test 3 passed!" << std::endl;
        } else {
            std::cerr << "Test 3 failed: Failed to create temporary script file" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Test 3 failed: " << e.what() << std::endl;
    }
    
    // 测试 4: include 语句
    std::cout << "\nTest 4: Include statement" << std::endl;
    std::string script4 = R"(
        // 包含文件
        include "utils.c";
        
        int main() {
            return multiply(2, 3);
        }
    )";
    
    try {
        std::string scriptPath = createTempScriptFile(script4, "test4.c");
        if (!scriptPath.empty()) {
            engine.executeFile(scriptPath);
            deleteTempScriptFile(scriptPath);
            std::cout << "Test 4 passed!" << std::endl;
        } else {
            std::cerr << "Test 4 failed: Failed to create temporary script file" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Test 4 failed: " << e.what() << std::endl;
    }
    
    return 0;
}