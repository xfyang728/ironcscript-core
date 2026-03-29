#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>

#include <CScriptEngine.h>

extern "C" {

int nativeCallback(int value) {
    std::cout << "  [Native] nativeCallback received: " << value << std::endl;
    return value * 2;
}

}

int main() {
    std::cout << "=== Native->Script Callback Demo ===" << std::endl;
    std::cout << std::endl;

    {
        cse::CScriptEngine engine;

        std::string testScriptPath = "test_script.c";

        std::cout << "=== Test 1: Cache Disabled ===" << std::endl;
        engine.setCacheEnabled(false);
        engine.registerNativeFunction("nativeCallback", nativeCallback);

        std::string script1 = R"(
            int myCallback(int x) {
                printf("Script callback received: %d\n", x);
                return x + 100;
            }

            extern int nativeCallback(int value);

            void main() {
                printf("Testing extern call to nativeCallback(42)\n");
                int result = nativeCallback(42);
                printf("nativeCallback returned: %d\n", result);
                register myCallback as onData;
                printf("myCallback registered as onData\n");
            }
        )";

        std::cout << "Executing script with cache disabled..." << std::endl;
        if (engine.execute(testScriptPath)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    std::cout << std::endl;

    {
        cse::CScriptEngine engine;

        std::string testScriptPath = "test_script.c";

        std::cout << "=== Test 2: Cache Enabled (First Run - Will Save) ===" << std::endl;
        engine.setCacheEnabled(true);
        engine.setForceRecompile(true);
        engine.registerNativeFunction("nativeCallback", nativeCallback);

        std::string script2 = R"(
            int myCallback(int x) {
                printf("Script callback received: %d\n", x);
                return x + 100;
            }

            extern int nativeCallback(int value);

            void main() {
                printf("Testing extern call to nativeCallback(42)\n");
                int result = nativeCallback(42);
                printf("nativeCallback returned: %d\n", result);
                register myCallback as onData;
                printf("myCallback registered as onData\n");
            }
        )";

        std::cout << "Executing script (will save cache)..." << std::endl;
        if (engine.execute(testScriptPath)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }

        std::cout << std::endl;
        std::cout << "=== Test 3: Cache Enabled (Second Run - Will Load) ===" << std::endl;
        engine.setForceRecompile(false);
        std::cout << "Executing script (will load from cache)..." << std::endl;
        if (engine.execute(testScriptPath)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "=== Checking Script Function Retrieval ===" << std::endl;

    {
        cse::CScriptEngine engine;
        engine.registerNativeFunction("nativeCallback", nativeCallback);

        std::string script = R"(
            int myCallback(int x) {
                return x + 100;
            }

            void main() {
                register myCallback as onData;
            }
        )";

        if (engine.execute(script)) {
            std::cout << "[PASS] Script executed successfully" << std::endl;
        } else {
            std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
        }

        if (engine.hasRegisteredCallback("onData")) {
            std::cout << "[PASS] Found script function registered as 'onData'" << std::endl;
            void* ptr = engine.getRegisteredCallback("onData");
            std::cout << "[INFO] Function pointer: " << ptr << std::endl;
        } else {
            std::cout << "[INFO] 'onData' not found" << std::endl;
        }

        if (engine.hasRegisteredCallback("myCallback")) {
            std::cout << "[PASS] Found script function 'myCallback'" << std::endl;
            void* ptr = engine.getRegisteredCallback("myCallback");
            std::cout << "[INFO] Function pointer: " << ptr << std::endl;
        } else {
            std::cout << "[INFO] 'myCallback' not found" << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "=== Demo Complete ===" << std::endl;

    return 0;
}
