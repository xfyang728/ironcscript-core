#include <iostream>
#include <CScriptEngine.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "=== Debugger Test ===" << std::endl;

    const char* testScript = R"(
        extern int add(int a, int b);
        
        int main() {
            int x = 10;
            int y = 20;
            int result = add(x, y);
            return result;
        }
    )";

    cse::CScriptEngine engine;
    engine.registerNativeFunction("add", add);
    
    // 启用调试模式
    engine.setDebugEnabled(true);
    std::cout << "Debug mode enabled: " << (engine.isDebugEnabled() ? "yes" : "no") << std::endl;

    // 设置断点
    engine.setBreakpoint(5, "test_script.c"); // 在 int x = 10; 行设置断点
    engine.setBreakpoint(7, "test_script.c"); // 在 int result = add(x, y); 行设置断点

    std::cout << "Breakpoints set" << std::endl;

    // 执行脚本
    std::cout << "Executing script..." << std::endl;
    if (engine.execute(testScript)) {
        std::cout << "Script executed successfully" << std::endl;
        std::cout << "Return value: " << engine.getLastReturnValue() << std::endl;
    } else {
        std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
    }

    // 移除断点
    engine.removeBreakpoint(5, "test_script.c");
    engine.removeBreakpoint(7, "test_script.c");
    std::cout << "Breakpoints removed" << std::endl;

    // 禁用调试模式
    engine.setDebugEnabled(false);
    std::cout << "Debug mode enabled: " << (engine.isDebugEnabled() ? "yes" : "no") << std::endl;

    // 再次执行脚本（无调试）
    std::cout << "Executing script without debug..." << std::endl;
    if (engine.execute(testScript)) {
        std::cout << "Script executed successfully" << std::endl;
        std::cout << "Return value: " << engine.getLastReturnValue() << std::endl;
    } else {
        std::cout << "Script execution failed: " << engine.getLastError() << std::endl;
    }

    std::cout << "=== Debugger Test Complete ===" << std::endl;
    return 0;
}
