#include "PlatformAbstraction.h"
#include "StandardLibrary.h"
#include "X64Platform.h"

namespace cse {

bool PlatformAbstraction::isStandardLibraryFunction(const std::string& funcName) const {
    return StandardLibrary::instance().isStandardLib(funcName) ||
           StandardLibrary::instance().isBuiltin(funcName);
}

PlatformAbstraction* PlatformFactory::createPlatformAbstraction() {
    // 目前只支持x86-64平台
    return new X64Platform();
}

} // namespace cse