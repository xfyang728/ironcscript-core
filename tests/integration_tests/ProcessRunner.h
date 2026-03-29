#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class ProcessRunner {
public:
    struct ProcessResult {
        int exitCode;
        int returnValue;
        bool hasOutput;
        std::string output;
        DWORD processId;
        bool timedOut;
    };

    static ProcessResult runProcess(const std::string& executable, 
                                   const std::string& arguments, 
                                   const std::string& outputFile,
                                   DWORD timeoutMs = 10000);
    
    static ProcessResult runProcessWithInput(const std::string& executable, 
                                            const std::string& arguments, 
                                            const std::string& inputFile,
                                            const std::string& outputFile,
                                            DWORD timeoutMs = 10000);
    
private:
    static std::string readOutputFileWithRetry(const std::string& filePath, 
                                             int maxRetries, 
                                             int retryDelayMs);
    
    static int extractReturnValue(const std::string& output, int fallbackValue);
};

ProcessRunner::ProcessResult ProcessRunner::runProcess(const std::string& executable, 
                                                      const std::string& arguments, 
                                                      const std::string& outputFile,
                                                      DWORD timeoutMs) {
    ProcessResult result;
    result.timedOut = false;
    
    // 创建进程
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // 构建命令行（不包含重定向，重定向由cmd.exe处理）
    std::string cmdLine = "\"" + executable + "\" " + arguments;
    
    // 使用cmd.exe来处理重定向
    std::string fullCmd = "cmd /c \"" + cmdLine + " > \"" + outputFile + "\" 2>&1\"";
    
    std::cout << "Running process: " << fullCmd << std::endl;
    
    // 创建进程
    if (!CreateProcessA(
        NULL,                   // 应用程序名（使用命令行）
        const_cast<char*>(fullCmd.c_str()), // 命令行
        NULL,                   // 进程句柄不可继承
        NULL,                   // 线程句柄不可继承
        FALSE,                  // 不继承句柄
        CREATE_NO_WINDOW,       // 创建标志（无窗口）
        NULL,                   // 使用父进程环境
        NULL,                   // 使用父进程目录
        &si,                    // 启动信息
        &pi                     // 进程信息
    )) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        result.exitCode = -1;
        return result;
    }
    
    result.processId = pi.dwProcessId;
    
    // 等待进程完成（带超时）
    DWORD waitResult = WaitForSingleObject(pi.hProcess, timeoutMs);
    
    if (waitResult == WAIT_TIMEOUT) {
        std::cerr << "Process timed out after " << timeoutMs << "ms" << std::endl;
        result.timedOut = true;
        
        // 尝试获取进程状态信息
        DWORD exitCode;
        if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
            std::cerr << "Process exit code before termination: " << exitCode << std::endl;
        }
        
        // 强制终止进程树
        TerminateProcess(pi.hProcess, 1);
    } else if (waitResult == WAIT_OBJECT_0) {
        std::cout << "Process completed successfully" << std::endl;
    } else {
        std::cerr << "WaitForSingleObject failed: " << GetLastError() << std::endl;
    }
    
    // 获取退出代码
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        result.exitCode = exitCode;
    } else {
        result.exitCode = -1;
    }
    
    // 关闭句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    // 等待文件写入完成
    Sleep(200);
    
    // 读取输出文件
    result.output = readOutputFileWithRetry(outputFile, 10, 50);
    result.hasOutput = !result.output.empty();
    
    // 提取返回值
    result.returnValue = extractReturnValue(result.output, result.exitCode);
    
    return result;
}

ProcessRunner::ProcessResult ProcessRunner::runProcessWithInput(const std::string& executable, 
                                                                const std::string& arguments, 
                                                                const std::string& inputFile,
                                                                const std::string& outputFile,
                                                                DWORD timeoutMs) {
    ProcessResult result;
    result.timedOut = false;
    
    // 创建临时批处理文件来处理输入重定向
    std::string batchFile = "D:\\MyCode\\IronCScript\\ironcscript-core\\tests\\output\\temp_batch_" + std::to_string(GetCurrentProcessId()) + "_" + std::to_string(GetCurrentThreadId()) + ".bat";
    
    // 创建批处理文件内容
    std::string batchContent = "@echo off\n";
    batchContent += "\"" + executable + "\" " + arguments + " < \"" + inputFile + "\" > \"" + outputFile + "\" 2>&1\n";
    batchContent += "echo Exit code: %errorlevel% >> \"" + outputFile + "\"\n";
    
    // 写入批处理文件
    std::ofstream batchStream(batchFile);
    if (!batchStream.is_open()) {
        std::cerr << "Failed to create batch file: " << batchFile << std::endl;
        result.exitCode = -1;
        return result;
    }
    batchStream << batchContent;
    batchStream.close();
    
    // 创建进程
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // 使用批处理文件执行
    std::string fullCmd = "cmd /c \"" + batchFile + "\"";
    
    std::cout << "Running process with batch file: " << fullCmd << std::endl;
    std::cout << "Batch file content:\n" << batchContent << std::endl;
    
    // 创建进程
    if (!CreateProcessA(
        NULL,                   // 应用程序名（使用命令行）
        const_cast<char*>(fullCmd.c_str()), // 命令行
        NULL,                   // 进程句柄不可继承
        NULL,                   // 线程句柄不可继承
        FALSE,                  // 不继承句柄
        CREATE_NO_WINDOW,       // 创建标志（无窗口）
        NULL,                   // 使用父进程环境
        NULL,                   // 使用父进程目录
        &si,                    // 启动信息
        &pi                     // 进程信息
    )) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        // 删除临时批处理文件
        DeleteFileA(batchFile.c_str());
        result.exitCode = -1;
        return result;
    }
    
    result.processId = pi.dwProcessId;
    
    // 等待进程完成（带超时）
    DWORD waitResult = WaitForSingleObject(pi.hProcess, timeoutMs);
    
    if (waitResult == WAIT_TIMEOUT) {
        std::cerr << "Process timed out after " << timeoutMs << "ms" << std::endl;
        result.timedOut = true;
        
        // 尝试获取进程状态信息
        DWORD exitCode;
        if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
            std::cerr << "Process exit code before termination: " << exitCode << std::endl;
        }
        
        // 强制终止进程树
        TerminateProcess(pi.hProcess, 1);
    } else if (waitResult == WAIT_OBJECT_0) {
        std::cout << "Process completed successfully" << std::endl;
    } else {
        std::cerr << "WaitForSingleObject failed: " << GetLastError() << std::endl;
    }
    
    // 获取退出代码
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        result.exitCode = exitCode;
    } else {
        result.exitCode = -1;
    }
    
    // 关闭句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    // 等待文件写入完成
    Sleep(200);
    
    // 读取输出文件
    result.output = readOutputFileWithRetry(outputFile, 10, 50);
    result.hasOutput = !result.output.empty();
    
    // 提取返回值
    result.returnValue = extractReturnValue(result.output, result.exitCode);
    
    return result;
}

std::string ProcessRunner::readOutputFileWithRetry(const std::string& filePath, 
                                                 int maxRetries, 
                                                 int retryDelayMs) {
    std::ifstream infile;
    int retryCount = 0;
    
    while (retryCount < maxRetries) {
        infile.open(filePath);
        if (infile.is_open()) {
            std::stringstream buffer;
            buffer << infile.rdbuf();
            infile.close();
            return buffer.str();
        }
        retryCount++;
        Sleep(retryDelayMs);
    }
    
    std::cerr << "Failed to read output file after " << maxRetries << " retries" << std::endl;
    return "无法读取输出文件";
}

int ProcessRunner::extractReturnValue(const std::string& output, int fallbackValue) {
    // 查找 "main() return value: "
    size_t pos = output.find("main() return value: ");
    if (pos != std::string::npos) {
        pos += 21; // "main() return value: " 的长度
        size_t endPos = output.find("\n", pos);
        if (endPos != std::string::npos) {
            std::string returnValueStr = output.substr(pos, endPos - pos);
            try {
                return std::stoi(returnValueStr);
            } catch (const std::exception& e) {
                // 转换失败，使用fallback
            }
        }
    }
    
    // 查找 "Return value: "
    pos = output.find("Return value: ");
    if (pos != std::string::npos) {
        pos += 13; // "Return value: " 的长度
        size_t endPos = output.find("\n", pos);
        if (endPos != std::string::npos) {
            std::string returnValueStr = output.substr(pos, endPos - pos);
            try {
                return std::stoi(returnValueStr);
            } catch (const std::exception& e) {
                // 转换失败，使用fallback
            }
        }
    }
    
    return fallbackValue;
}

#endif // PROCESS_RUNNER_H