#pragma once

#include "BaseCodeGenerator.h"

#ifndef CSE_PLATFORM_EMBEDDED
#include "x64/X64Code.h"
#endif

namespace cse {

class CodeGeneratorFactory {
public:
    static BaseCodeGenerator* createCodeGenerator(const std::string& platform);
};

} // namespace cse