#ifndef CSE_STM32_CSB_LOADER_H
#define CSE_STM32_CSB_LOADER_H

#include "bytecode/BytecodeFormat.h"
#include <cstdint>

namespace cse {

class STM32CSBLoader {
public:
    static bool loadFromFlash(uint32_t addr, BytecodeModule& module);
    static bool isValidHeader(uint32_t addr);

private:
    static bool readFlash(uint32_t addr, void* buffer, size_t len);
};

}

#endif