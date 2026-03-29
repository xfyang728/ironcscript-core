#ifndef CSE_K210_SCRIPT_LOADER_H
#define CSE_K210_SCRIPT_LOADER_H

#include "vm/BytecodeVM.h"
#include "bytecode/BytecodeFormat.h"
#include "hal/HardwareFactory.h"
#include <cstdint>
#include <functional>

namespace cse {

class K210ScriptLoader {
public:
    static K210ScriptLoader& instance();

    bool initialize();
    bool loadScriptFromFlash(uint32_t addr);
    bool execute();
    void stop();

    BytecodeVM* getVM() { return m_VM; }

    void registerPrintFunction();
    void registerGPIOFunctions();
    void registerUARTFunctions();
    void registerTimerFunctions();
    void registerSystemFunctions();

private:
    K210ScriptLoader() = default;
    ~K210ScriptLoader() = default;

    BytecodeVM* m_VM = nullptr;
    BytecodeModule m_Module;
    bool m_Initialized = false;
};

}

#endif