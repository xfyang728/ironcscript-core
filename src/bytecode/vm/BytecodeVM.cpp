#include "BytecodeVM.h"
#include "../BytecodeFormat.h"
#include <cstring>
#include <cmath>

namespace cse {

extern "C" void Serial_SendString(const char* str);
extern "C" void Serial_SendNumber(uint32_t Number, uint8_t Length);

BytecodeVM::BytecodeVM(const VMConfig& config)
    : m_Module(nullptr)
    , m_HeapUsed(0)
    , m_FrameCount(0)
    , m_PC(0)
    , m_Running(false)
    , m_StackSize(config.stackSize)
    , m_MaxCallDepth(config.maxCallDepth)
    , m_NativeFunctions{}
    , m_NativeFunctionNames{}
    , m_NativeFunctionCount(0)
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
        Serial_SendString("[VM] push FAIL: overflow\r\n");
        return false;
    }
    *m_StackTop++ = val;
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
        return false;
    }

    VMFrame& frame = m_Frames[m_FrameCount - 1];
    if (frame.functionIndex >= m_Module->functions.size()) {
        return false;
    }

    const BytecodeFunction& func = m_Module->functions[frame.functionIndex];
    if (frame.pc >= func.instructions.size()) {
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

    int32_t currentStackTop = m_StackTop - m_Stack;

    for (uint32_t i = funcParamCount; i < localCount; i++) {
        push(VMValue::makeInt(0));
    }

    VMFrame frame;
    frame.functionIndex = funcIndex;
    frame.pc = 0;
    frame.localBase = currentStackTop - paramCount;
    frame.localCount = funcParamCount;

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
    if (actualSlot >= (int32_t)m_StackSize || actualSlot < 0) {
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
            if (idx < m_Module->globalConstants.size()) {
                const auto& entry = m_Module->globalConstants[idx];
                switch (entry.type) {
                    case ConstantPoolEntry::Type::INTEGER:
                        push(VMValue::makeInt(entry.value.intVal));
                        break;
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
            } else {
                Serial_SendString("[VM] LOAD_CONST OOR\r\n");
            }
            break;
        }

        case OpCode::LOAD_VAR: {
            VMValue val = getLocal(operand);
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
            if (!callFunction(funcIndex, paramCount)) {
                return false;
            }
            break;
        }

        case OpCode::CALL_NATIVE: {
            uint32_t encoded = operand;
            uint32_t stringPoolIndex = encoded & 0xFFFF;
            uint32_t paramCount = encoded >> 16;
            int32_t currentStackTop = m_StackTop - m_Stack;

            std::string funcName;
            if (stringPoolIndex < m_Module->stringPool.size()) {
                funcName = m_Module->stringPool[stringPoolIndex];
            }

            NativeFunction funcToCall = nullptr;
            for (size_t i = 0; i < m_NativeFunctionCount; i++) {
                if (m_NativeFunctionNames[i] == funcName) {
                    funcToCall = m_NativeFunctions[i];
                    break;
                }
            }
            if (funcToCall) {
                int32_t localBaseForNative = currentStackTop - paramCount;

                int32_t savedLocalBase = -1;
                int savedFrameCount = m_FrameCount;
                if (m_FrameCount > 0) {
                    savedLocalBase = m_Frames[m_FrameCount - 1].localBase;
                }

                uint32_t savedCallerPc = 0;
                if (m_FrameCount > 0 && m_FrameCount < (int)16) {
                    savedCallerPc = m_Frames[m_FrameCount - 1].pc;
                }

                if (m_FrameCount < (int)16) {
                    m_Frames[m_FrameCount].functionIndex = 0xFFFFFFFF;
                    m_Frames[m_FrameCount].pc = 0;
                    m_Frames[m_FrameCount].localBase = localBaseForNative;
                    m_Frames[m_FrameCount].localCount = paramCount;
                    m_FrameCount++;
                }

                funcToCall(this);

                m_FrameCount = savedFrameCount;
                if (savedFrameCount > 0 && savedLocalBase >= 0) {
                    m_Frames[savedFrameCount - 1].localBase = savedLocalBase;
                    m_Frames[savedFrameCount - 1].pc = savedCallerPc;
                }
            } else {
                Serial_SendString("[VM] native not found: ");
                Serial_SendString(funcName.c_str());
                Serial_SendString("\r\n");
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

    Serial_SendString("[VM] execute start\r\n");

    if (entryPoint >= m_Module->functions.size()) {
        m_LastError = "Invalid entry point";
        m_Running = false;
        return false;
    }

    if (!callFunction(entryPoint, 0)) {
        m_Running = false;
        return false;
    }

    bool shouldContinue = true;
    while (m_FrameCount > 0 && shouldContinue && m_Running) {
        OpCode op;
        uint32_t operand;
        if (!fetch(op, operand)) {
            if (m_FrameCount > 0) {
                VMFrame& frame = m_Frames[m_FrameCount - 1];
                const BytecodeFunction& func = m_Module->functions[frame.functionIndex];
                if (frame.pc >= func.instructions.size() && m_FrameCount > 0) {
                    returnFromFunction();
                    if (m_FrameCount == 0) {
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
            VMValue v = pop();
            m_ReturnValue = v;
            if (!returnFromFunction()) {
                shouldContinue = false;
            }
        } else if (op == OpCode::HALT) {
            m_Running = false;
            return true;
        } else {
            if (!executeInstruction(op, operand)) {
                Serial_SendString("[VM] execInstr fail\r\n");
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

void BytecodeVM::registerNativeFunction(const char* name, NativeFunction func) {
    if (m_NativeFunctionCount < MAX_NATIVE_FUNCTIONS) {
        m_NativeFunctions[m_NativeFunctionCount] = func;
        m_NativeFunctionNames[m_NativeFunctionCount] = name;
        m_NativeFunctionCount++;
    }
}

void BytecodeVM::dumpNativeFunctions() const {
    Serial_SendString("[VM] native funcs: ");
    Serial_SendNumber(m_NativeFunctionCount, 10);
    Serial_SendString("\r\n");
    for (size_t i = 0; i < m_NativeFunctionCount; i++) {
        Serial_SendString("  ");
        Serial_SendString(m_NativeFunctionNames[i]);
        Serial_SendString("\r\n");
    }
}

}
