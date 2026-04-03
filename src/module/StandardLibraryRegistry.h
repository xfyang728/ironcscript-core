/**
 * @file StandardLibraryRegistry.h
 * @brief Standard library header file registry for IronCScript
 * @author IronCScript Team
 * @version 1.0
 */
#ifndef CSE_STANDARD_LIBRARY_REGISTRY_H
#define CSE_STANDARD_LIBRARY_REGISTRY_H

#include <string>
#include <vector>
#include <unordered_map>

namespace cse {

/**
 * @brief Standard library function declaration
 */
struct StdlibFunction {
    std::string name;
    std::string returnType;
    std::vector<std::string> paramTypes;
    bool isVariadic;

    StdlibFunction(const std::string& n, const std::string& ret,
                   const std::vector<std::string>& params, bool variadic = false)
        : name(n), returnType(ret), paramTypes(params), isVariadic(variadic) {}
};

/**
 * @brief Standard library header file declaration
 */
struct StdlibHeader {
    std::string name;
    std::vector<StdlibFunction> functions;

    StdlibHeader(const std::string& n, const std::vector<StdlibFunction>& funcs)
        : name(n), functions(funcs) {}
};

/**
 * @brief Registry for standard library header files and their function declarations
 * 
 * This class provides a centralized registry for C standard library functions
 * that can be included via #include <stdio.h> syntax in IronCScript scripts.
 */
class StandardLibraryRegistry {
public:
    static const std::vector<StdlibHeader>& getHeaders();
    static const StdlibHeader* findHeader(const std::string& name);
    static const StdlibFunction* findFunction(const std::string& headerName, const std::string& funcName);
    static bool isStandardLibraryHeader(const std::string& name);

private:
    static std::vector<StdlibHeader>& getMutableHeaders();
    static void initialize();
    static bool s_Initialized;
};

}

#endif // CSE_STANDARD_LIBRARY_REGISTRY_H