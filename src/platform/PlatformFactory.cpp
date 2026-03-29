#include "PlatformAbstraction.h"
#include "X64Platform.h"
#include "RiscV64Platform.h"
#include "RiscV64EmbeddedPlatform.h"

namespace cse {

PlatformAbstraction* PlatformFactory::createPlatformAbstraction() {
#ifdef CSE_EMBEDDED
    // RISC-V 嵌入式平台（如 K210）
    return new RiscV64EmbeddedPlatform();
#elif defined(CSE_RISCV64) || defined(__riscv) || defined(__riscv64)
    // RISC-V 非嵌入式平台
    return new RiscV64Platform();
#elif defined(__x86_64__)
    // x64 平台
    return new X64Platform();
#else
    #error "Unsupported platform"
#endif
}

} // namespace cse