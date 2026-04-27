/**
 * @file StandardLibraryRegistry.cpp
 * @brief Implementation of standard library registry
 * @author IronCScript Team
 */
#include "StandardLibraryRegistry.h"
#include <cstring>

namespace cse {

bool StandardLibraryRegistry::s_Initialized = false;

std::vector<StdlibHeader>& StandardLibraryRegistry::getMutableHeaders() {
    static std::vector<StdlibHeader> headers;
    return headers;
}

void StandardLibraryRegistry::initialize() {
    if (s_Initialized) return;
    s_Initialized = true;

    auto& headers = getMutableHeaders();

    // stdio.h - Standard I/O functions
    {
        std::vector<StdlibFunction> funcs;
        funcs.emplace_back("printf", "int", std::vector<std::string>{}, true);
        funcs.emplace_back("puts", "int", std::vector<std::string>{"const char*"}, false);
        funcs.emplace_back("sprintf", "int", std::vector<std::string>{"char*", "const char*"}, true);
        funcs.emplace_back("fopen", "void*", std::vector<std::string>{"const char*", "const char*"}, false);
        funcs.emplace_back("fclose", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("fread", "int", std::vector<std::string>{"void*", "int", "int", "void*"}, false);
        funcs.emplace_back("fwrite", "int", std::vector<std::string>{"const void*", "int", "int", "void*"}, false);
        funcs.emplace_back("fprintf", "int", std::vector<std::string>{"void*", "const char*"}, true);
        funcs.emplace_back("fgets", "char*", std::vector<std::string>{"char*", "int", "void*"}, false);
        funcs.emplace_back("fputs", "int", std::vector<std::string>{"const char*", "void*"}, false);
        funcs.emplace_back("fseek", "int", std::vector<std::string>{"void*", "int", "int"}, false);
        funcs.emplace_back("ftell", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("rewind", "void", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("feof", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("ferror", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("clearerr", "void", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("fgetc", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("fputc", "int", std::vector<std::string>{"int", "void*"}, false);
        funcs.emplace_back("fflush", "int", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("remove", "int", std::vector<std::string>{"const char*"}, false);
        funcs.emplace_back("rename", "int", std::vector<std::string>{"const char*", "const char*"}, false);
        headers.emplace_back("stdio.h", funcs);
    }

    // stdlib.h - Standard library functions
    {
        std::vector<StdlibFunction> funcs;
        funcs.emplace_back("malloc", "void*", std::vector<std::string>{"int"}, false);
        funcs.emplace_back("free", "void", std::vector<std::string>{"void*"}, false);
        funcs.emplace_back("atoi", "int", std::vector<std::string>{"const char*"}, false);
        funcs.emplace_back("atof", "double", std::vector<std::string>{"const char*"}, false);
        funcs.emplace_back("rand", "int", std::vector<std::string>{}, false);
        funcs.emplace_back("srand", "void", std::vector<std::string>{"unsigned int"}, false);
        funcs.emplace_back("exit", "void", std::vector<std::string>{"int"}, false);
        funcs.emplace_back("abs", "int", std::vector<std::string>{"int"}, false);
        funcs.emplace_back("system", "int", std::vector<std::string>{"const char*"}, false);
        headers.emplace_back("stdlib.h", funcs);
    }

    // string.h - String handling functions
    {
        std::vector<StdlibFunction> funcs;
        funcs.emplace_back("strlen", "int", std::vector<std::string>{"const char*"}, false);
        funcs.emplace_back("strcpy", "char*", std::vector<std::string>{"char*", "const char*"}, false);
        funcs.emplace_back("strcmp", "int", std::vector<std::string>{"const char*", "const char*"}, false);
        funcs.emplace_back("strcat", "char*", std::vector<std::string>{"char*", "const char*"}, false);
        funcs.emplace_back("memset", "void*", std::vector<std::string>{"void*", "int", "int"}, false);
        funcs.emplace_back("memcpy", "void*", std::vector<std::string>{"void*", "const void*", "int"}, false);
        headers.emplace_back("string.h", funcs);
    }

    // math.h - Math functions
    {
        std::vector<StdlibFunction> funcs;
        funcs.emplace_back("sin", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("cos", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("tan", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("sqrt", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("pow", "double", std::vector<std::string>{"double", "double"}, false);
        funcs.emplace_back("log", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("exp", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("fabs", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("floor", "double", std::vector<std::string>{"double"}, false);
        funcs.emplace_back("ceil", "double", std::vector<std::string>{"double"}, false);
        headers.emplace_back("math.h", funcs);
    }
}

const std::vector<StdlibHeader>& StandardLibraryRegistry::getHeaders() {
    initialize();
    return getMutableHeaders();
}

const StdlibHeader* StandardLibraryRegistry::findHeader(const std::string& name) {
    initialize();
    const auto& headers = getMutableHeaders();
    for (const auto& header : headers) {
        if (header.name == name) {
            return &header;
        }
    }
    return nullptr;
}

const StdlibFunction* StandardLibraryRegistry::findFunction(const std::string& headerName, 
                                                           const std::string& funcName) {
    const StdlibHeader* header = findHeader(headerName);
    if (!header) return nullptr;
    
    for (const auto& func : header->functions) {
        if (func.name == funcName) {
            return &func;
        }
    }
    return nullptr;
}

bool StandardLibraryRegistry::isStandardLibraryHeader(const std::string& name) {
    return findHeader(name) != nullptr;
}

}