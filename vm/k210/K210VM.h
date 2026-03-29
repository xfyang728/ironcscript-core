#ifndef CSE_K210_VM_H
#define CSE_K210_VM_H

#include "bytecode/vm/BytecodeVM.h"

namespace cse {

constexpr size_t K210_VM_STACK_SIZE = 256;
constexpr size_t K210_VM_HEAP_SIZE = 4096;
constexpr size_t K210_VM_MAX_CALL_DEPTH = 32;

class K210VM : public BytecodeVM {
public:
    K210VM();
    ~K210VM();
};

}

#endif
