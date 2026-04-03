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
    std::vector<StdlibFunction> stdioFunctions;
    stdioFunctions.emplace_back("printf", "int", 
        std::vector<std::string>{}, true);  // variadic
    stdioFunctions.emplace_back("puts", "int", 
        std::vector<std::string>{"const char*"}, false);
    headers.emplace_back("stdio.h", stdioFunctions);

    // stdlib.h - Standard library functions (for future extension)
    // std::vector<StdlibFunction> stdlibFunctions;
    // stdlibFunctions.emplace_back("malloc", "void*", std::vector<std::string>{"size_t"}, false);
    // headers.emplace_back("stdlib.h", stdlibFunctions);

    // string.h - String handling functions (for future extension)
    // std::vector<StdlibFunction> stringFunctions;
    // stringFunctions.emplace_back("strlen", "size_t", std::vector<std::string>{"const char*"}, false);
    // headers.emplace_back("string.h", stringFunctions);
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