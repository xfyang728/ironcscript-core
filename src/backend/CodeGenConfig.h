#ifndef CSE_CODEGENCONFIG_H
#define CSE_CODEGENCONFIG_H

#include "Architecture.h"

namespace cse {

struct CodeGenConfig {
    Architecture::Type archType;
    bool enableOptimizations;
    bool enableDebugInfo;
    bool enableDisassembly;
    int optimizationLevel;
    
    CodeGenConfig() 
        : archType(Architecture::Type::X64),
          enableOptimizations(false),
          enableDebugInfo(true),
          enableDisassembly(false),
          optimizationLevel(0) {}
};

} // namespace cse

#endif // CSE_CODEGENCONFIG_H