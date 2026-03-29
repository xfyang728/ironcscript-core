#pragma once

#include <string>

namespace cse {

struct StackFrame {
    std::string functionName;
    std::string sourceFile;
    int lineNumber;
};

} // namespace cse
