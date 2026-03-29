#include "CodeGeneratorFactory.h"
#include "../platform/PlatformAbstraction.h"

#ifndef CSE_PLATFORM_EMBEDDED
#include "x64/X64Code.h"
#endif

#ifdef CSE_RISCV64
#include "rv64/RV64Code.h"
#endif

namespace cse {

BaseCodeGenerator* CodeGeneratorFactory::createCodeGenerator(const std::string& platform) {
    BaseCodeGenerator* codeGen = nullptr;

    if (platform == PLATFORM_X86_64) {
#ifndef CSE_PLATFORM_EMBEDDED
        codeGen = new X64Code();
#else
        throw std::runtime_error("X86_64 platform not supported on embedded systems");
#endif
    } else if (platform == PLATFORM_RISCV64) {
#ifdef CSE_RISCV64
        codeGen = new RV64Code();
#else
        throw std::runtime_error("RISC-V 64 platform not supported in this build");
#endif
    } else {
        throw std::runtime_error("Unsupported platform: " + platform);
    }

    PlatformAbstraction* platformAbstraction = PlatformFactory::createPlatformAbstraction();
    codeGen->setPlatformAbstraction(platformAbstraction);

    return codeGen;
}

} // namespace cse