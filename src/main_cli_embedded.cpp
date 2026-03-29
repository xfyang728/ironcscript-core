#include "IronCScript.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <script_file>" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  script_file   Path to the IronCS script file" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  " << programName << " scripts/hello.c" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string scriptPath = argv[1];
    std::ifstream file(scriptPath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << scriptPath << std::endl;
        return 1;
    }

    cse::IronCScript engine;
    engine.setPlatform("riscv64");

    std::cout << "IronCScript v" << cse::IronCScript::version() << std::endl;
    std::cout << "Platform: riscv64" << std::endl;
    std::cout << "Script: " << scriptPath << std::endl;
    std::cout << std::endl;

    std::cout << "Executing script..." << std::endl;
    bool success = engine.executeFile(scriptPath);
    if (!success) {
        std::cerr << "Error: " << engine.getLastError() << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "Script executed successfully." << std::endl;
    std::cout << "Return value: " << engine.getLastReturnValue() << std::endl;

    return engine.getLastReturnValue();
}