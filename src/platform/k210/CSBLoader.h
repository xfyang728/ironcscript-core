#ifndef CSE_K210_CSB_LOADER_H
#define CSE_K210_CSB_LOADER_H

#include "bytecode/BytecodeFormat.h"
#include <cstdint>

namespace cse {

class CSBLoader {
public:
    static bool loadFromFlash(uint32_t addr, BytecodeModule& module);

private:
    static bool readFlash(uint32_t addr, void* buffer, size_t len);
};

}

#endif