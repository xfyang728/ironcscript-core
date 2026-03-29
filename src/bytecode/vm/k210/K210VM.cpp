#include "K210VM.h"

namespace cse {

K210VM::K210VM()
    : BytecodeVM(VMConfig{
        .stackSize = K210_VM_STACK_SIZE,
        .heapSize = K210_VM_HEAP_SIZE,
        .maxCallDepth = K210_VM_MAX_CALL_DEPTH
    })
{
}

K210VM::~K210VM() {
}

}
