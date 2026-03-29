#include "IronCScript.h"
#include "frontend/parser/ASTBuilder.h"
#include "frontend/semantic/SemanticAnalyzer.h"
#include "frontend/generated/CScriptLexer.h"
#include "frontend/generated/CScriptParser.h"
#include "ir/IRGenerator.h"
#include "bytecode/BytecodeCompiler.h"
#include "bytecode/BytecodeFormat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void printUsage(const char* programName) {
    std::cout << "CScript Compiler (cscriptc) v1.0" << std::endl;
    std::cout << "Usage: " << programName << " <input_file> [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  input_file    Path to the CScript source file (.cs)" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -o <file>     Output bytecode file (.csb)" << std::endl;
    std::cout << "  --platform    Target platform: k210, stm32, or x64 (default: none)" << std::endl;
    std::cout << "  --help        Show this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Platform-specific constants:" << std::endl;
    std::cout << "  --platform k210   Enables K210 constants (GPIO0-7, FUNC_GPIO0-7, etc.)" << std::endl;
    std::cout << "  --platform stm32  Enables STM32 constants (PA0-PG15, PORT_A, etc.)" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  " << programName << " script.cs" << std::endl;
    std::cout << "  " << programName << " script.cs -o output.csb" << std::endl;
    std::cout << "  " << programName << " script.cs --platform k210 -o output.csb" << std::endl;
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool writeFile(const std::string& path, const std::string& content) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file << content;
    return true;
}

bool compileToBytecode(const std::string& sourceCode, cse::BytecodeModule*& outModule, const std::string& platform = "") {
    antlr4::ANTLRInputStream input(sourceCode.c_str(), sourceCode.size());
    CScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CScriptParser parser(&tokens);

    cse::ASTBuilder builder;
    cse::NBlock* ast = builder.build(parser.program());
    if (!ast) {
        std::cerr << "Error: Parsing failed" << std::endl;
        return false;
    }

    cse::SymbolTable symbolTable;
    if (!platform.empty()) {
        std::cout << "Loading platform constants for: " << platform << std::endl;
        symbolTable.registerPlatformConstants(platform);
    }

    cse::SemanticAnalyzer analyzer(symbolTable, nullptr);
    if (!analyzer.analyze(*ast)) {
        std::cerr << "Error: Semantic analysis failed" << std::endl;
        return false;
    }

    cse::IRGenerator irGenerator(symbolTable);
    irGenerator.generateIR(*ast);
    std::list<cse::Quad> quadList = irGenerator.getQuadList();

    cse::BytecodeCompiler compiler;
    outModule = compiler.compile(quadList, symbolTable);
    if (!outModule) {
        std::cerr << "Error: Bytecode compilation failed: " << compiler.getLastError() << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string inputPath;
    std::string outputPath;
    std::string platform;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o" && i + 1 < argc) {
            outputPath = argv[++i];
        } else if (arg == "--platform" && i + 1 < argc) {
            platform = argv[++i];
        } else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
        } else if (arg[0] != '-') {
            if (inputPath.empty()) {
                inputPath = arg;
            } else if (outputPath.empty()) {
                outputPath = arg;
            }
        }
    }

    if (inputPath.empty()) {
        std::cerr << "Error: No input file specified" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    if (outputPath.empty()) {
        size_t dotPos = inputPath.rfind('.');
        if (dotPos != std::string::npos) {
            outputPath = inputPath.substr(0, dotPos) + ".csb";
        } else {
            outputPath = inputPath + ".csb";
        }
    }

    std::cout << "CScript Compiler (cscriptc)" << std::endl;
    std::cout << "Input:  " << inputPath << std::endl;
    std::cout << "Output: " << outputPath << std::endl;
    if (!platform.empty()) {
        std::cout << "Platform: " << platform << std::endl;
    }
    std::cout << std::endl;

    std::string sourceCode = readFile(inputPath);
    if (sourceCode.empty()) {
        std::cerr << "Error: Cannot read input file: " << inputPath << std::endl;
        return 1;
    }

    std::cout << "Parsing..." << std::endl;

    cse::BytecodeModule* module = nullptr;
    if (!compileToBytecode(sourceCode, module, platform)) {
        std::cerr << "Compilation failed" << std::endl;
        return 1;
    }

    std::cout << "Generating bytecode..." << std::endl;

    if (!module->saveToFile(outputPath)) {
        std::cerr << "Error: Cannot write output file: " << outputPath << std::endl;
        delete module;
        return 1;
    }

    std::cout << "Compilation successful!" << std::endl;
    std::cout << "Output: " << outputPath << std::endl;
    std::cout << "Functions: " << module->header.functionCount << std::endl;
    std::cout << "Entry point: " << module->header.entryPointIndex << std::endl;

    delete module;
    return 0;
}