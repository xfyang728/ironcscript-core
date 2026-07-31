#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "IronCScript.h"

using namespace std;
using namespace cse;

/**
 * @brief 全局输出缓冲区，用于 WASM 环境中捕获脚本输出
 */
static std::string g_OutputBuffer;

/**
 * @brief 全局错误缓冲区，用于 WASM 环境中捕获错误信息
 */
static std::string g_ErrorBuffer;

void printUsage(const char* programName) {
    cout << "Usage: " << programName << " <script_file> [platform]" << endl;
    cout << endl;
    cout << "Arguments:" << endl;
    cout << "  script_file   Path to the IronCS script file" << endl;
    cout << "  platform     Target platform (optional, default: x86-64)" << endl;
    cout << endl;
    cout << "Supported platforms: " << IronCScript::supportedPlatforms() << endl;
    cout << endl;
    cout << "Example:" << endl;
    cout << "  " << programName << " scripts/hello.c" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    string scriptFile = argv[1];
    string platform = "x86-64";
    if (argc > 2) {
        platform = argv[2];
    }

    cout << "IronCScript v" << IronCScript::version() << endl;
    cout << "Platform: " << platform << endl;
    cout << "Script: " << scriptFile << endl;
    cout << endl;

    IronCScript engine;
    engine.setPlatform(platform);

    cout << "Executing script..." << endl;
    if (!engine.executeFile(scriptFile)) {
        cerr << "Error: " << engine.getLastError() << endl;
        return 1;
    }

    cout << endl;
    cout << "Script executed successfully." << endl;
    cout << "Return value: " << engine.getLastReturnValue() << endl;

    return engine.getLastReturnValue();
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

/**
 * @brief 执行 CScript 脚本字符串（WASM 导出函数）
 * @param scriptPtr 指向脚本字符串的指针
 * @return main 函数返回值，-1 表示执行失败
 */
extern "C" int EMSCRIPTEN_KEEPALIVE executeScript(const char* scriptPtr) {
    if (!scriptPtr) return -1;

    g_OutputBuffer.clear();
    g_ErrorBuffer.clear();

    IronCScript engine;
    engine.setPlatform("wasm");
    engine.setStandardOutputCallback([](const std::string& msg) {
        g_OutputBuffer += msg;
    });

    if (!engine.execute(scriptPtr)) {
        g_ErrorBuffer = engine.getLastError();
        return -1;
    }

    return engine.getLastReturnValue();
}

/**
 * @brief 获取脚本输出内容（WASM 导出函数）
 * @return 输出缓冲区指针
 */
extern "C" const char* EMSCRIPTEN_KEEPALIVE getOutput() {
    return g_OutputBuffer.c_str();
}

/**
 * @brief 获取错误信息（WASM 导出函数）
 * @return 错误缓冲区指针
 */
extern "C" const char* EMSCRIPTEN_KEEPALIVE getError() {
    return g_ErrorBuffer.c_str();
}

/**
 * @brief 执行脚本文件（WASM 导出函数）
 * @param filePathPtr 指向文件路径字符串的指针
 * @return main 函数返回值，-1 表示执行失败
 */
extern "C" int EMSCRIPTEN_KEEPALIVE executeFile(const char* filePathPtr) {
    if (!filePathPtr) return -1;

    g_OutputBuffer.clear();
    g_ErrorBuffer.clear();

    IronCScript engine;
    engine.setPlatform("wasm");
    engine.setStandardOutputCallback([](const std::string& msg) {
        g_OutputBuffer += msg;
    });

    if (!engine.executeFile(filePathPtr)) {
        g_ErrorBuffer = engine.getLastError();
        return -1;
    }

    return engine.getLastReturnValue();
}

#endif // __EMSCRIPTEN__
