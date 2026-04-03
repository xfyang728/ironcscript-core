#include "BytecodeVM.h"
#include "../BytecodeFormat.h"
#include <cstring>
#include <cmath>

namespace cse {

BytecodeVM::BytecodeVM(const VMConfig& config)
    : m_Module(nullptr)
    , m_HeapUsed(0)
    , m_FrameCount(0)
    , m_PC(0)
    , m_Running(false)
    , m_StackSize(config.stackSize)
    , m_MaxCallDepth(config.maxCallDepth)
{
    m_Stack = new VMValue[m_StackSize];
    m_Locals = new VMValue[m_StackSize];
    m_Heap = new VMValue[config.heapSize];
    m_Frames = new VMFrame[m_MaxCallDepth];
    reset();
}

BytecodeVM::~BytecodeVM() {
    delete[] m_Stack;
    delete[] m_Locals;
    delete[] m_Heap;
    delete[] m_Frames;
}

void BytecodeVM::reset() {
    m_StackTop = m_Stack;
    m_HeapUsed = 0;
    m_FrameCount = 0;
    m_PC = 0;
    m_Running = false;
    m_ReturnValue = VMValue::makeNil();
    m_LastError.clear();
    memset(m_Frames, 0, sizeof(VMFrame) * m_MaxCallDepth);
    memset(m_Locals, 0, sizeof(VMValue) * m_StackSize);
}

bool BytecodeVM::loadModule(const BytecodeModule* module) {
    if (!module || !module->header.isValid()) {
        m_LastError = "Invalid bytecode module";
        return false;
    }
    m_Module = module;
    reset();
    return true;
}

bool BytecodeVM::push(const VMValue& val) {
    if (m_StackTop >= m_Stack + m_StackSize) {
        m_LastError = "Stack overflow";
        printf("[VM] push FAILED: stack overflow! stackTop=%ld, stackSize=%u\r\n",
               (long)(m_StackTop - m_Stack), (unsigned)m_StackSize);
        return false;
    }
    int32_t slot = m_StackTop - m_Stack;
    *m_StackTop++ = val;
    printf("[VM] push: slot=%d, val.type=%d, val.value=%lld\r\n",
           slot, (int)val.type, (long long)val.value.intVal);
    printf("[VM] push:   m_Stack[%d].type=%d, m_Stack[%d].value=%lld\r\n",
           slot, (int)m_Stack[slot].type, slot, (long long)m_Stack[slot].value.intVal);
    return true;
}

VMValue BytecodeVM::pop() {
    if (m_StackTop > m_Stack) {
        --m_StackTop;
        return *m_StackTop;
    }
    return VMValue::makeNil();
}

VMValue& BytecodeVM::peek() {
    static VMValue nil = VMValue::makeNil();
    if (m_StackTop > m_Stack) {
        return m_StackTop[-1];
    }
    return nil;
}

OpCode BytecodeVM::fetch() {
    OpCode op = OpCode::NOP;
    uint32_t operand = 0;
    fetch(op, operand);
    return op;
}

bool BytecodeVM::fetch(OpCode& outOp, uint32_t& outOperand) {
    outOp = OpCode::NOP;
    outOperand = 0;

    if (!m_Module || m_FrameCount == 0) {
        printf("[VM] fetch failed: no module or no frames\r\n");
        fflush(stdout);
        return false;
    }

    VMFrame& frame = m_Frames[m_FrameCount - 1];
    if (frame.functionIndex >= m_Module->functions.size()) {
        printf("[VM] fetch failed: funcIndex %u >= %u\r\n",
               frame.functionIndex, (unsigned)m_Module->functions.size());
        fflush(stdout);
        return false;
    }

    const BytecodeFunction& func = m_Module->functions[frame.functionIndex];
    if (frame.pc >= func.instructions.size()) {
        printf("[VM] fetch failed: pc %u >= instrCount %u\r\n",
               frame.pc, (unsigned)func.instructions.size());
        fflush(stdout);
        return false;
    }

    outOp = func.instructions[frame.pc].op;
    outOperand = func.instructions[frame.pc].operand;
    frame.pc++;
    return true;
}

bool BytecodeVM::callFunction(uint32_t funcIndex, uint32_t paramCount) {
    if (m_FrameCount >= m_MaxCallDepth) {
        m_LastError = "Call stack overflow";
        return false;
    }

    if (!m_Module || funcIndex >= m_Module->functions.size()) {
        m_LastError = "Invalid function index";
        return false;
    }

    const BytecodeFunction& func = m_Module->functions[funcIndex];
    uint32_t localCount = func.localCount;
    uint32_t funcParamCount = func.paramCount;

    printf("[VM] callFunction: funcIndex=%u, paramCount=%u, localCount=%u, funcParamCount=%u\r\n",
           funcIndex, paramCount, localCount, funcParamCount);

    int32_t currentStackTop = m_StackTop - m_Stack;

    for (uint32_t i = funcParamCount; i < localCount; i++) {
        push(VMValue::makeInt(0));
    }

    printf("[VM] callFunction: After push locals, stackTop=%d\r\n", m_StackTop - m_Stack);

    VMFrame frame;
    frame.functionIndex = funcIndex;
    frame.pc = 0;
    frame.localBase = currentStackTop - paramCount;
    frame.localCount = funcParamCount;

    printf("[VM] callFunction: localBase=%d\r\n", frame.localBase);

    m_Frames[m_FrameCount++] = frame;
    return true;
}

bool BytecodeVM::returnFromFunction() {
    if (m_FrameCount == 0) {
        return false;
    }
    --m_FrameCount;
    return m_FrameCount > 0;
}

VMValue& BytecodeVM::getLocal(uint32_t slot) {
    static VMValue nil;
    if (!m_Module || m_FrameCount == 0) {
        return nil;
    }
    VMFrame& frame = m_Frames[m_FrameCount - 1];
    int32_t actualSlot;
    if (slot < frame.localCount) {
        actualSlot = frame.localBase + slot;
    } else {
        actualSlot = frame.localBase + frame.localCount + (slot - frame.localCount);
    }
    if (actualSlot >= m_StackSize || actualSlot < 0) {
        return nil;
    }
    return m_Stack[actualSlot];
}

VMValue& BytecodeVM::getGlobal(uint32_t slot) {
    static VMValue nil;
    (void)slot;
    return nil;
}

VMValue& BytecodeVM::getConstant(uint32_t index) {
    static VMValue nil;
    (void)index;
    return nil;
}

const char* BytecodeVM::getStringFromConstant(uint32_t index) {
    if (!m_Module || index >= m_Module->stringPool.size()) {
        return "";
    }
    return m_Module->stringPool[index].c_str();
}

bool BytecodeVM::executeInstruction(OpCode op, uint32_t operand) {
    switch (op) {
        case OpCode::NOP:
            break;

        case OpCode::LOAD_CONST: {
            uint32_t idx = operand;
            int32_t currentStackTop = m_StackTop - m_Stack;
            printf("[VM] LOAD_CONST idx=%u, globalConstants.size()=%u, stackTop=%d\r\n",
                   idx, (unsigned)m_Module->globalConstants.size(), currentStackTop);
            if (idx < m_Module->globalConstants.size()) {
                const auto& entry = m_Module->globalConstants[idx];
                printf("[VM] LOAD_CONST entry.type=%d, value.intVal=%lld, value.doubleVal=%f\r\n",
                       (int)entry.type, (long long)entry.value.intVal, entry.value.doubleVal);
                switch (entry.type) {
                    case ConstantPoolEntry::Type::INTEGER: {
                        VMValue v = VMValue::makeInt(entry.value.intVal);
                        printf("[VM] LOAD_CONST pushing INTEGER %lld to stack\r\n", (long long)v.value.intVal);
                        push(v);
                        break;
                    }
                    case ConstantPoolEntry::Type::DOUBLE:
                        push(VMValue::makeDouble(entry.value.doubleVal));
                        break;
                    case ConstantPoolEntry::Type::STRING:
                        push(VMValue::makeString(entry.value.stringOffset));
                        break;
                    case ConstantPoolEntry::Type::FUNCTION:
                        push(VMValue::makeInt(entry.value.functionIndex));
                        break;
                    default:
                        push(VMValue::makeNil());
                        break;
                }
                printf("[VM] LOAD_CONST done, new stackTop=%ld\r\n", (long)(m_StackTop - m_Stack));
            } else {
                printf("[VM] LOAD_CONST idx=%u out of range!\r\n", idx);
            }
            break;
        }

        case OpCode::LOAD_VAR: {
            printf("[VM] LOAD_VAR: slot=%u, localBase=%d, actualSlot=%d\r\n",
                   operand, m_Frames[m_FrameCount - 1].localBase,
                   m_Frames[m_FrameCount - 1].localBase + operand);
            VMValue val = getLocal(operand);
            printf("[VM] LOAD_VAR: loaded value=%lld\r\n", (long long)val.value.intVal);
            push(val);
            break;
        }

        case OpCode::STORE_VAR: {
            VMValue val = pop();
            VMFrame& frame = m_Frames[m_FrameCount - 1];
            int32_t actualSlot;
            if (operand < frame.localCount) {
                actualSlot = frame.localBase + operand;
            } else {
                actualSlot = frame.localBase + frame.localCount + (operand - frame.localCount);
            }
            printf("[VM] STORE_VAR: slot=%u, localBase=%d, localCount=%u, actualSlot=%d, value=%lld\r\n",
                   operand, frame.localBase, frame.localCount, actualSlot, (long long)val.value.intVal);
            if (actualSlot >= 0 && actualSlot < (int32_t)m_StackSize) {
                m_Stack[actualSlot] = val;
            }
            break;
        }

        case OpCode::PEEK_VAR: {
            VMValue val = peek();
            VMFrame& frame = m_Frames[m_FrameCount - 1];
            int32_t actualSlot = frame.localBase + operand;
            if (actualSlot >= 0 && actualSlot < (int32_t)m_StackSize) {
                m_Stack[actualSlot] = val;
            }
            break;
        }

        case OpCode::ADD: {
            VMValue b = pop();
            VMValue a = pop();
            if (a.type == ValueType::INTEGER && b.type == ValueType::INTEGER) {
                push(VMValue::makeInt(a.value.intVal + b.value.intVal));
            } else {
                push(VMValue::makeDouble(a.toDouble() + b.toDouble()));
            }
            break;
        }

        case OpCode::SUB: {
            VMValue b = pop();
            VMValue a = pop();
            printf("[VM] SUB: a=%lld, b=%lld, result=%lld\r\n", 
                   (long long)a.value.intVal, (long long)b.value.intVal, 
                   (long long)(a.value.intVal - b.value.intVal));
            if (a.type == ValueType::INTEGER && b.type == ValueType::INTEGER) {
                push(VMValue::makeInt(a.value.intVal - b.value.intVal));
            } else {
                push(VMValue::makeDouble(a.toDouble() - b.toDouble()));
            }
            break;
        }

        case OpCode::MUL: {
            VMValue b = pop();
            VMValue a = pop();
            if (a.type == ValueType::INTEGER && b.type == ValueType::INTEGER) {
                push(VMValue::makeInt(a.value.intVal * b.value.intVal));
            } else {
                push(VMValue::makeDouble(a.toDouble() * b.toDouble()));
            }
            break;
        }

        case OpCode::DIV: {
            VMValue b = pop();
            VMValue a = pop();
            if (b.value.intVal == 0) {
                m_LastError = "Division by zero";
                return false;
            }
            if (a.type == ValueType::INTEGER && b.type == ValueType::INTEGER) {
                push(VMValue::makeInt(a.value.intVal / b.value.intVal));
            } else {
                push(VMValue::makeDouble(a.toDouble() / b.toDouble()));
            }
            break;
        }

        case OpCode::MOD: {
            VMValue b = pop();
            VMValue a = pop();
            if (b.value.intVal == 0) {
                m_LastError = "Division by zero";
                return false;
            }
            push(VMValue::makeInt(a.value.intVal % b.value.intVal));
            break;
        }

        case OpCode::NEG: {
            VMValue a = pop();
            if (a.type == ValueType::INTEGER) {
                push(VMValue::makeInt(-a.value.intVal));
            } else {
                push(VMValue::makeDouble(-a.toDouble()));
            }
            break;
        }

        case OpCode::NOT: {
            VMValue a = pop();
            push(VMValue::makeInt(a.toBool() ? 0 : 1));
            break;
        }

        case OpCode::EQ: {
            VMValue b = pop();
            VMValue a = pop();
            bool result = (a.type == b.type && a.value.intVal == b.value.intVal);
            push(VMValue::makeInt(result ? 1 : 0));
            break;
        }

        case OpCode::NEQ: {
            VMValue b = pop();
            VMValue a = pop();
            bool result = (a.type != b.type || a.value.intVal != b.value.intVal);
            push(VMValue::makeInt(result ? 1 : 0));
            break;
        }

        case OpCode::LT: {
            VMValue b = pop();
            VMValue a = pop();
            push(VMValue::makeInt(a.toDouble() < b.toDouble() ? 1 : 0));
            break;
        }

        case OpCode::GT: {
            VMValue b = pop();
            VMValue a = pop();
            push(VMValue::makeInt(a.toDouble() > b.toDouble() ? 1 : 0));
            break;
        }

        case OpCode::LTE: {
            VMValue b = pop();
            VMValue a = pop();
            push(VMValue::makeInt(a.toDouble() <= b.toDouble() ? 1 : 0));
            break;
        }

        case OpCode::GTE: {
            VMValue b = pop();
            VMValue a = pop();
            push(VMValue::makeInt(a.toDouble() >= b.toDouble() ? 1 : 0));
            break;
        }

        case OpCode::JUMP: {
            VMFrame& frame = m_Frames[m_FrameCount - 1];
            if (operand < m_Module->functions[frame.functionIndex].instructions.size()) {
                frame.pc = operand;
            }
            break;
        }

        case OpCode::JUMP_IF_FALSE: {
            VMValue cond = pop();
            if (!cond.toBool()) {
                VMFrame& frame = m_Frames[m_FrameCount - 1];
                if (operand < m_Module->functions[frame.functionIndex].instructions.size()) {
                    frame.pc = operand;
                }
            }
            break;
        }

        case OpCode::JUMP_IF_TRUE: {
            VMValue cond = pop();
            if (cond.toBool()) {
                VMFrame& frame = m_Frames[m_FrameCount - 1];
                if (operand < m_Module->functions[frame.functionIndex].instructions.size()) {
                    frame.pc = operand;
                }
            }
            break;
        }

        case OpCode::CALL: {
            uint32_t encoded = operand;
            uint32_t funcIndex = encoded & 0xFFFF;
            uint32_t paramCount = encoded >> 16;
            int32_t currentStackTop = m_StackTop - m_Stack;
            printf("[VM] CALL: funcIndex=%u, paramCount=%u, stackTop=%d\r\n",
                   funcIndex, paramCount, currentStackTop);
            printf("[VM] CALL: Stack before call: ");
            for (int i = 0; i < currentStackTop && i < 20; i++) {
                printf("[%d]=%lld ", i, (long long)m_Stack[i].value.intVal);
            }
            printf("\r\n");
            if (!callFunction(funcIndex, paramCount)) {
                return false;
            }
            printf("[VM] CALL: After setup frame, localBase=%d\r\n",
                   m_Frames[m_FrameCount - 1].localBase);
            break;
        }

        case OpCode::CALL_NATIVE: {
            uint32_t encoded = operand;
            uint32_t stringPoolIndex = encoded & 0xFFFF;
            uint32_t paramCount = encoded >> 16;
            int32_t currentStackTop = m_StackTop - m_Stack;
            printf("[VM] CALL_NATIVE: stringPoolIndex=%u, paramCount=%u, stackTop=%d\r\n",
                   stringPoolIndex, paramCount, currentStackTop);
            printf("[VM] Stack contents: ");
            for (int i = 0; i < currentStackTop && i < 16; i++) {
                printf("[%d]=%lld ", i, (long long)m_Stack[i].value.intVal);
            }
            printf("\r\n");

            std::string funcName;
            if (stringPoolIndex < m_Module->stringPool.size()) {
                funcName = m_Module->stringPool[stringPoolIndex];
            }
            printf("[VM] Calling native function: '%s'\r\n", funcName.c_str());
            dumpNativeFunctions();

            auto it = m_NativeFunctionMap.find(funcName);
            if (it != m_NativeFunctionMap.end()) {
                printf("[VM] Native function found\r\n");

                int32_t localBaseForNative = currentStackTop - paramCount;
                printf("[VM] Argument calculation: stackTop=%d - paramCount=%u = localBase=%d\r\n",
                       currentStackTop, paramCount, localBaseForNative);

                for (uint32_t i = 0; i < paramCount; i++) {
                    int32_t argIndex = localBaseForNative + i;
                    if (argIndex >= 0 && argIndex < currentStackTop) {
                        printf("[VM]   arg[%u] -> stack[%d] = %lld\r\n",
                               i, argIndex, (long long)m_Stack[argIndex].value.intVal);
                    } else {
                        printf("[VM]   arg[%u] -> stack[%d] = OUT_OF_RANGE\r\n", i, argIndex);
                    }
                }

                int32_t savedLocalBase = -1;
                int savedFrameCount = m_FrameCount;
                if (m_FrameCount > 0) {
                    savedLocalBase = m_Frames[m_FrameCount - 1].localBase;
                }

                uint32_t savedCallerPc = 0;
                if (m_FrameCount > 0 && m_FrameCount < (int)16) {
                    savedCallerPc = m_Frames[m_FrameCount - 1].pc;
                    printf("[VM] Saving caller pc=%u before native call\r\n", savedCallerPc);
                }

                if (m_FrameCount < (int)16) {
                    m_Frames[m_FrameCount].functionIndex = 0xFFFFFFFF;
                    m_Frames[m_FrameCount].pc = 0;
                    m_Frames[m_FrameCount].localBase = localBaseForNative;
                    m_Frames[m_FrameCount].localCount = paramCount;
                    m_FrameCount++;
                }

                NativeFunction func = it->second;
                func(this);

                m_FrameCount = savedFrameCount;
                if (savedFrameCount > 0 && savedLocalBase >= 0) {
                    m_Frames[savedFrameCount - 1].localBase = savedLocalBase;
                    m_Frames[savedFrameCount - 1].pc = savedCallerPc;
                    printf("[VM] Restored caller pc to %u after native call\r\n", savedCallerPc);
                }
            } else {
                printf("[VM] ERROR: Native function '%s' not found\r\n", funcName.c_str());
                fflush(stdout);
            }
            break;
        }

        case OpCode::RETURN: {
            m_ReturnValue = pop();
            if (!returnFromFunction()) {
                return false;
            }
            break;
        }

        case OpCode::HALT:
            return false;

        case OpCode::PUSH: {
            VMValue top = peek();
            push(top);
            break;
        }

        case OpCode::POP: {
            pop();
            break;
        }

        case OpCode::PUSH_RETURN: {
            push(m_ReturnValue);
            break;
        }

        default:
            break;
    }

    return true;
}

bool BytecodeVM::execute(uint32_t entryPoint) {
    if (!m_Module) {
        m_LastError = "No module loaded";
        return false;
    }

    reset();
    m_Running = true;

    printf("[VM] execute entryPoint=%u, functions=%u\r\n",
           entryPoint, (unsigned)m_Module->functions.size());
    fflush(stdout);

    if (entryPoint >= m_Module->functions.size()) {
        m_LastError = "Invalid entry point";
        m_Running = false;
        return false;
    }

    const auto& entryFunc = m_Module->functions[entryPoint];
    printf("[VM] entryFunc: instrCount=%u, constCount=%u\r\n",
           (unsigned)entryFunc.instructions.size(), (unsigned)entryFunc.constants.size());
    fflush(stdout);

    if (!callFunction(entryPoint, 0)) {
        m_Running = false;
        return false;
    }

    bool shouldContinue = true;
    while (m_FrameCount > 0 && shouldContinue && m_Running) {
        OpCode op;
        uint32_t operand;
        if (!fetch(op, operand)) {
            printf("[VM] fetch failed, checking if function ended normally\r\n");
            fflush(stdout);
            if (m_FrameCount > 0) {
                VMFrame& frame = m_Frames[m_FrameCount - 1];
                const BytecodeFunction& func = m_Module->functions[frame.functionIndex];
                if (frame.pc >= func.instructions.size() && m_FrameCount > 0) {
                    printf("[VM] function ended, returning\r\n");
                    fflush(stdout);
                    returnFromFunction();
                    if (m_FrameCount == 0) {
                        printf("[VM] no more frames, execution complete\r\n");
                        fflush(stdout);
                        m_Running = false;
                        return true;
                    }
                    continue;
                }
            }
            m_Running = false;
            return false;
        }

        if (op == OpCode::RETURN) {
            printf("[VM] RETURN\r\n");
            VMValue v = pop();
            m_ReturnValue = v;
            if (!returnFromFunction()) {
                shouldContinue = false;
            }
        } else if (op == OpCode::HALT) {
            printf("[VM] HALT\r\n");
            m_Running = false;
            return true;
        } else {
            printf("[VM] opcode=%d operand=%u\r\n", (int)op, operand);
            if (!executeInstruction(op, operand)) {
                m_Running = false;
                return false;
            }
        }
    }

    m_Running = false;
    return true;
}

void BytecodeVM::stop() {
    m_Running = false;
}

void BytecodeVM::registerNativeFunction(const std::string& name, NativeFunction func) {
    printf("[VM] registerNativeFunction: %s\r\n", name.c_str());
    fflush(stdout);
    m_NativeFunctions.push_back(func);
    m_NativeFunctionMap[name] = func;
    m_NativeFunctionNames.push_back(name);
}

void BytecodeVM::registerConstant(const std::string& name, int64_t value) {
    printf("[VM] registerConstant: %s = %lld\r\n", name.c_str(), (long long)value);
    fflush(stdout);
    m_RegisteredConstants[name] = value;
}

bool BytecodeVM::findRegisteredConstant(const std::string& name, int64_t& outValue) const {
    auto it = m_RegisteredConstants.find(name);
    if (it != m_RegisteredConstants.end()) {
        outValue = it->second;
        return true;
    }
    return false;
}

void BytecodeVM::dumpConstants() const {
    printf("=== VM Registered Constants (%zu) ===\r\n", m_RegisteredConstants.size());
    for (const auto& pair : m_RegisteredConstants) {
        printf("  %s = %lld\r\n", pair.first.c_str(), (long long)pair.second);
    }
    printf("======================================\r\n");
    fflush(stdout);
}

}
