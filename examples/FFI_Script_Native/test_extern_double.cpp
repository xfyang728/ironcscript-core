#include <iostream>
#include <cstdlib>
#include <string>

#include <IronCScript.h>

extern "C" {

double add_double(double a, double b) {
    std::cout << "  [Native] add_double(" << a << ", " << b << ") = " << (a + b) << std::endl;
    return a + b;
}

}

int main() {
    std::cout << "=== Simple FFI Test ===" << std::endl;

    const char* script = R"(
extern double add_double(double a, double b);

int main() {
    double result = add_double(1.5, 2.5);
    return 0;
}
)";

    std::cout << "Script:" << std::endl;
    std::cout << script << std::endl;
    std::cout << std::endl;

    cse::IronCScript engine;
    engine.registerNativeFunction("add_double", add_double);

    std::cout << "Executing..." << std::endl;
    if (engine.execute(script)) {
        std::cout << "[PASS] Script executed successfully" << std::endl;
    } else {
        std::cout << "[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
    }

    return 0;
}