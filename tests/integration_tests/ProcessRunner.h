#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#endif

class ProcessRunner {
public:
    struct ProcessResult {
        int exitCode;
        int returnValue;
        bool hasOutput;
        std::string output;
        int64_t processId;   // 统一类型（DWORD/pid_t 都容纳）
        bool timedOut;
    };

    static ProcessResult runProcess(const std::string& executable,
                                    const std::string& arguments,
                                    const std::string& outputFile,
                                    int64_t timeoutMs = 10000);

    static ProcessResult runProcessWithInput(const std::string& executable,
                                             const std::string& arguments,
                                             const std::string& inputFile,
                                             const std::string& outputFile,
                                             int64_t timeoutMs = 10000);

private:
    static std::string readOutputFileWithRetry(const std::string& filePath,
                                               int maxRetries,
                                               int retryDelayMs);
    static int extractReturnValue(const std::string& output, int fallbackValue);

#ifdef _WIN32
    /// Windows: 创建子进程并重定向 stdout/stderr 到管道，再写入 outputFile
    static ProcessResult runProcessWindows(const std::string& executable,
                                           const std::string& arguments,
                                           const std::string& outputFile,
                                           int64_t timeoutMs,
                                           const std::string& inputFile = "");
#else
    /// POSIX: 拆分 arguments 为 argv（简单空格分词，不处理引号嵌套）
    static std::vector<char*> buildArgv(const std::string& executable,
                                        const std::string& arguments,
                                        std::vector<std::string>& storage);
#endif
};

// ============================================================================
// Windows 实现
// ============================================================================
#ifdef _WIN32

inline ProcessRunner::ProcessResult ProcessRunner::runProcessWindows(
    const std::string& executable,
    const std::string& arguments,
    const std::string& outputFile,
    int64_t timeoutMs,
    const std::string& inputFile) {

    ProcessResult result{};
    result.timedOut = false;
    result.exitCode = -1;
    result.returnValue = 0;
    result.hasOutput = false;
    result.processId = 0;

    // 1. 创建 stdout 管道
    HANDLE hReadPipe = nullptr, hWritePipe = nullptr;
    SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        std::cerr << "CreatePipe failed: " << GetLastError() << std::endl;
        return result;
    }
    SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0);

    // 2. 如有 inputFile，打开为 stdin
    HANDLE hInputFile = nullptr;
    if (!inputFile.empty()) {
        hInputFile = CreateFileA(inputFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
                                 &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hInputFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to open input file: " << inputFile << std::endl;
            CloseHandle(hReadPipe);
            CloseHandle(hWritePipe);
            return result;
        }
    }

    // 3. 配置 STARTUPINFOA 重定向
    STARTUPINFOA si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.hStdInput = hInputFile ? hInputFile : GetStdHandle(STD_INPUT_HANDLE);

    PROCESS_INFORMATION pi{};

    // 4. 构建命令行（不再用 cmd /c）
    std::string cmdLine = "\"" + executable + "\" " + arguments;

    if (!CreateProcessA(nullptr, const_cast<LPSTR>(cmdLine.c_str()),
                        nullptr, nullptr, TRUE,
                        CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        if (hInputFile) CloseHandle(hInputFile);
        return result;
    }

    result.processId = (int64_t)pi.dwProcessId;

    // 5. 关闭写端，让子进程输出能被读端读到 EOF
    CloseHandle(hWritePipe);
    if (hInputFile) CloseHandle(hInputFile);

    // 6. 等待进程（带超时）
    DWORD waitResult = WaitForSingleObject(pi.hProcess, (DWORD)timeoutMs);
    if (waitResult == WAIT_TIMEOUT) {
        std::cerr << "Process timed out after " << timeoutMs << "ms" << std::endl;
        result.timedOut = true;
        TerminateProcess(pi.hProcess, 1);
    }

    // 7. 读取管道内容
    std::string output;
    char buf[4096];
    DWORD bytesRead = 0;
    while (ReadFile(hReadPipe, buf, sizeof(buf), &bytesRead, nullptr) && bytesRead > 0) {
        output.append(buf, bytesRead);
    }
    CloseHandle(hReadPipe);

    // 8. 获取退出码并清理
    DWORD exitCode = 0;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        result.exitCode = (int)exitCode;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 9. 写入 outputFile（保留原约定：调用方从文件读取）
    if (!outputFile.empty()) {
        std::ofstream ofs(outputFile, std::ios::trunc);
        if (ofs.is_open()) {
            ofs << output;
            ofs.close();
        }
    }

    result.output = output;
    result.hasOutput = !output.empty();
    result.returnValue = extractReturnValue(output, result.exitCode);
    return result;
}

inline ProcessRunner::ProcessResult ProcessRunner::runProcess(
    const std::string& executable,
    const std::string& arguments,
    const std::string& outputFile,
    int64_t timeoutMs) {
    return runProcessWindows(executable, arguments, outputFile, timeoutMs, "");
}

inline ProcessRunner::ProcessResult ProcessRunner::runProcessWithInput(
    const std::string& executable,
    const std::string& arguments,
    const std::string& inputFile,
    const std::string& outputFile,
    int64_t timeoutMs) {
    return runProcessWindows(executable, arguments, outputFile, timeoutMs, inputFile);
}

#else
// ============================================================================
// POSIX 实现
// ============================================================================

static volatile sig_atomic_t g_alarmFired = 0;
static void alarmHandler(int sig) { (void)sig; g_alarmFired = 1; }

inline std::vector<char*> ProcessRunner::buildArgv(
    const std::string& executable,
    const std::string& arguments,
    std::vector<std::string>& storage) {
    storage.clear();
    storage.push_back(executable);
    std::istringstream iss(arguments);
    std::string token;
    while (iss >> token) {
        storage.push_back(token);
    }
    std::vector<char*> argv;
    argv.reserve(storage.size() + 1);
    for (auto& s : storage) {
        argv.push_back(s.data());
    }
    argv.push_back(nullptr);
    return argv;
}

inline ProcessRunner::ProcessResult ProcessRunner::runProcess(
    const std::string& executable,
    const std::string& arguments,
    const std::string& outputFile,
    int64_t timeoutMs) {

    ProcessResult result{};
    result.timedOut = false;
    result.exitCode = -1;
    result.returnValue = 0;
    result.hasOutput = false;
    result.processId = 0;

    int pipefd[2];
    if (pipe(pipefd) != 0) {
        std::cerr << "pipe failed" << std::endl;
        return result;
    }

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "fork failed" << std::endl;
        close(pipefd[0]);
        close(pipefd[1]);
        return result;
    }

    if (pid == 0) {
        // 子进程
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);

        std::vector<std::string> storage;
        auto argv = buildArgv(executable, arguments, storage);
        execvp(executable.c_str(), argv.data());
        _exit(127);
    }

    // 父进程
    close(pipefd[1]);
    result.processId = (int64_t)pid;

    signal(SIGALRM, alarmHandler);
    g_alarmFired = 0;
    alarm((unsigned)(timeoutMs / 1000));

    std::string output;
    char buf[4096];
    ssize_t n;
    while ((n = read(pipefd[0], buf, sizeof(buf))) > 0) {
        output.append(buf, (size_t)n);
    }
    close(pipefd[0]);

    int status = 0;
    waitpid(pid, &status, 0);
    alarm(0);

    if (g_alarmFired) {
        kill(pid, SIGKILL);
        result.timedOut = true;
    }

    result.exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    result.output = output;
    result.hasOutput = !output.empty();

    if (!outputFile.empty()) {
        std::ofstream ofs(outputFile, std::ios::trunc);
        if (ofs.is_open()) ofs << output;
    }

    result.returnValue = extractReturnValue(output, result.exitCode);
    return result;
}

inline ProcessRunner::ProcessResult ProcessRunner::runProcessWithInput(
    const std::string& executable,
    const std::string& arguments,
    const std::string& inputFile,
    const std::string& outputFile,
    int64_t timeoutMs) {

    int stdoutPipe[2];
    int stdinPipe[2];
    if (pipe(stdoutPipe) != 0 || pipe(stdinPipe) != 0) {
        std::cerr << "pipe failed" << std::endl;
        return ProcessResult{};
    }

    pid_t pid = fork();
    if (pid < 0) {
        close(stdoutPipe[0]); close(stdoutPipe[1]);
        close(stdinPipe[0]); close(stdinPipe[1]);
        return ProcessResult{};
    }

    if (pid == 0) {
        close(stdoutPipe[0]);
        close(stdinPipe[1]);
        dup2(stdoutPipe[1], STDOUT_FILENO);
        dup2(stdoutPipe[1], STDERR_FILENO);
        dup2(stdinPipe[0], STDIN_FILENO);
        close(stdoutPipe[1]);
        close(stdinPipe[0]);

        std::vector<std::string> storage;
        auto argv = buildArgv(executable, arguments, storage);
        execvp(executable.c_str(), argv.data());
        _exit(127);
    }

    close(stdoutPipe[1]);
    close(stdinPipe[0]);

    // 写入 stdin
    std::ifstream ifs(inputFile);
    if (ifs.is_open()) {
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());
        ssize_t written = write(stdinPipe[1], content.data(), content.size());
        (void)written;
    }
    close(stdinPipe[1]);

    signal(SIGALRM, alarmHandler);
    g_alarmFired = 0;
    alarm((unsigned)(timeoutMs / 1000));

    std::string output;
    char buf[4096];
    ssize_t n;
    while ((n = read(stdoutPipe[0], buf, sizeof(buf))) > 0) {
        output.append(buf, (size_t)n);
    }
    close(stdoutPipe[0]);

    int status = 0;
    waitpid(pid, &status, 0);
    alarm(0);

    ProcessResult result{};
    result.processId = (int64_t)pid;
    if (g_alarmFired) {
        kill(pid, SIGKILL);
        result.timedOut = true;
    }
    result.exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    result.output = output;
    result.hasOutput = !output.empty();

    if (!outputFile.empty()) {
        std::ofstream ofs(outputFile, std::ios::trunc);
        if (ofs.is_open()) ofs << output;
    }
    result.returnValue = extractReturnValue(output, result.exitCode);
    return result;
}

#endif // _WIN32

// ============================================================================
// 公共辅助函数（跨平台）
// ============================================================================

inline std::string ProcessRunner::readOutputFileWithRetry(const std::string& filePath,
                                                          int maxRetries,
                                                          int retryDelayMs) {
    for (int i = 0; i < maxRetries; ++i) {
        std::ifstream infile(filePath);
        if (infile.is_open()) {
            std::stringstream buffer;
            buffer << infile.rdbuf();
            return buffer.str();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(retryDelayMs));
    }
    std::cerr << "Failed to read output file after " << maxRetries << " retries" << std::endl;
    return "";
}

inline int ProcessRunner::extractReturnValue(const std::string& output, int fallbackValue) {
    // 查找 "main() return value: "
    size_t pos = output.find("main() return value: ");
    if (pos != std::string::npos) {
        pos += 21;
        size_t endPos = output.find("\n", pos);
        if (endPos != std::string::npos) {
            try {
                return std::stoi(output.substr(pos, endPos - pos));
            } catch (const std::exception&) {}
        }
    }
    // 查找 "Return value: "
    pos = output.find("Return value: ");
    if (pos != std::string::npos) {
        pos += 13;
        size_t endPos = output.find("\n", pos);
        if (endPos != std::string::npos) {
            try {
                return std::stoi(output.substr(pos, endPos - pos));
            } catch (const std::exception&) {}
        }
    }
    return fallbackValue;
}

#endif // PROCESS_RUNNER_H