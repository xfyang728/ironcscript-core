#include "PlatformAbstraction.h"
#include "StandardLibrary.h"

namespace cse {

bool PlatformAbstraction::isStandardLibraryFunction(const std::string& funcName) const {
    return StandardLibrary::instance().isStandardLib(funcName) ||
           StandardLibrary::instance().isBuiltin(funcName);
}

} // namespace cse
