#ifndef CSE_BYTE_CODE_VM_H
#define CSE_BYTE_CODE_VM_H

#include "bytecode/BytecodeFormat.h"
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace cse {

constexpr size_t DEFAULT_VM_STACK_SIZE = 256;
constexpr size_t DEFAULT_VM_HEAP_SIZE = 4096;
constexpr size_t DEFAULT_VM_MAX_CALL_DEPTH = 32;

struct VMConfig {
    size_t stackSize = DEFAULT_VM_STACK_SIZE;
    size_t heapSize = DEFAULT_VM_HEAP_SIZE;
    size_t maxCallDepth = DEFAULT_VM_MAX_CALL_DEPTH;
};

class BytecodeVM {
public:
    explicit BytecodeVM(const VMConfig& config = VMConfig{});
    ~BytecodeVM();

    bool loadModule(const BytecodeModule* module);
    bool execute(uint32_t entryPoint = 0);
    void stop();

    using NativeFunction = void (*)(BytecodeVM*);
    void registerNativeFunction(const std::string& name, NativeFunction func);
    bool hasNativeFunction(const std::string& name) const {
        return m_NativeFunctionMap.find(name) != m_NativeFunctionMap.end();
    }
    void dumpNativeFunctions() const {
        printf("[VM] Dumping m_NativeFunctionMap (%zu entries):\r\n", m_NativeFunctionMap.size());
        for (const auto& pair : m_NativeFunctionMap) {
            printf("[VM]   Entry: len=%zu, hex=[", pair.first.size());
            for (size_t j = 0; j < pair.first.size(); j++) {
                printf("%02X", (unsigned char)pair.first[j]);
            }
            printf("]\r\n");
        }
        fflush(stdout);
    }

    VMValue& getReturnValue() { return m_ReturnValue; }
    const std::string& getLastError() const { return m_LastError; }
    bool isRunning() const { return m_Running; }

    VMValue getArg(int32_t index) {
        if (index < 0 || m_FrameCount == 0) return VMValue::makeNil();
        VMFrame& frame = m_Frames[m_FrameCount - 1];
        int32_t stackIndex = frame.localBase + (frame.localCount - 1 - index);
        if (stackIndex < 0 || stackIndex >= (int32_t)m_StackSize) return VMValue::makeNil();
        return m_Stack[stackIndex];
    }

    int32_t getArgCount() const {
        if (m_FrameCount == 0) return 0;
        const VMFrame& frame = m_Frames[m_FrameCount - 1];
        return static_cast<int32_t>(frame.localCount);
    }

    size_t getStackUsed() const { return m_StackTop - m_Stack; }
    size_t getHeapUsed() const { return m_HeapUsed; }

    VMValue& getLocal(uint32_t slot);
    VMValue& getGlobal(uint32_t slot);
    VMValue& getConstant(uint32_t index);
    const char* getStringFromConstant(uint32_t index);
    uint32_t getStringPoolSize() const { return m_Module ? static_cast<uint32_t>(m_Module->stringPool.size()) : 0; }

    void registerConstant(const std::string& name, int64_t value);
    bool findRegisteredConstant(const std::string& name, int64_t& outValue) const;
    const std::map<std::string, int64_t>& getRegisteredConstants() const { return m_RegisteredConstants; }
    void dumpConstants() const;

private:
    void reset();
    bool push(const VMValue& val);
    VMValue pop();
    VMValue& peek();
    bool executeInstruction(OpCode op, uint32_t operand);
    OpCode fetch();
    bool fetch(OpCode& outOp, uint32_t& outOperand);
    bool callFunction(uint32_t funcIndex, uint32_t argCount);
    bool returnFromFunction();

    const BytecodeModule* m_Module;
    VMValue* m_Stack;
    VMValue* m_Locals;
    VMValue* m_StackTop;
    VMValue* m_Heap;
    size_t m_HeapUsed;
    size_t m_StackSize;
    size_t m_MaxCallDepth;

    VMFrame* m_Frames;
    uint32_t m_FrameCount;
    uint32_t m_PC;

    VMValue m_ReturnValue;
    std::string m_LastError;
    bool m_Running;

    std::vector<NativeFunction> m_NativeFunctions;
    std::map<std::string, NativeFunction> m_NativeFunctionMap;
    std::vector<std::string> m_NativeFunctionNames;
    std::map<std::string, int64_t> m_RegisteredConstants;
};

}

#endif
