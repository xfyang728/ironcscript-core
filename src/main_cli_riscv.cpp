#include "IronCScript.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: IronCScript <script_file>" << std::endl;
        return 1;
    }

    std::string scriptPath = argv[1];
    std::ifstream file(scriptPath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << scriptPath << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string scriptCode = buffer.str();

    cse::IronCScript engine;
    engine.setPlatform("riscv64");

    std::cout << "=== IronCScript RISC-V 64 Non-Embedded ===" << std::endl;
    std::cout << "Executing script: " << scriptPath << std::endl;

    bool success = engine.executeFile(scriptPath);
    if (!success) {
        std::cerr << "Error: " << engine.getLastError() << std::endl;
        return 1;
    }

    std::cout << "Script executed successfully!" << std::endl;
    std::cout << "Return value: " << engine.getLastReturnValue() << std::endl;

    return 0;
}