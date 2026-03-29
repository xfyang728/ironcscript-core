#include "bytecode/BytecodeCompiler.h"
#include "ir/Quad.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

namespace cse {

BytecodeCompiler::BytecodeCompiler()
    : m_Module(nullptr)
    , m_CurrentFunction(nullptr)
    , m_NextStringOffset(0)
    , m_NextConstantIndex(0)
    , m_NextFunctionIndex(0)
    , m_SymbolTable(nullptr)
{
}

BytecodeCompiler::~BytecodeCompiler() {
}

void BytecodeCompiler::reset() {
    if (m_Module) {
        delete m_Module;
    }
    m_Module = new BytecodeModule();
    m_StringToOffset.clear();
    m_Functions.clear();
    m_FunctionIndices.clear();
    m_CurrentFunction = nullptr;
    m_NextStringOffset = 0;
    m_NextConstantIndex = 0;
    m_NextFunctionIndex = 0;
    m_VariableToSlot.clear();
    m_LocalVariables.clear();
    m_ConstTempValues.clear();
    m_LastStoredTemp.clear();
    m_LastError.clear();
    m_SymbolTable = nullptr;
}

uint32_t BytecodeCompiler::addString(const std::string& str) {
    auto it = m_StringToOffset.find(str);
    if (it != m_StringToOffset.end()) {
        return it->second;
    }
    uint32_t index = m_Module->stringPool.size();
    m_StringToOffset[str] = index;
    m_Module->stringPool.push_back(str);
    return index;
}

uint32_t BytecodeCompiler::addConstant(ConstantPoolEntry entry) {
    uint32_t index = m_NextConstantIndex++;
    m_Module->globalConstants.push_back(entry);
    std::cerr << "[DEBUG BC] addConstant idx=" << index << " type=" << static_cast<int>(entry.type);
    if (entry.type == ConstantPoolEntry::Type::INTEGER) {
        std::cerr << " value=" << entry.value.intVal;
    }
    std::cerr << std::endl;
    return index;
}

uint32_t BytecodeCompiler::addFunction(const BytecodeFunction& func) {
    uint32_t index = m_NextFunctionIndex++;
    m_Functions.push_back(new BytecodeFunction(func));
    m_Module->functions.push_back(func);
    return index;
}

void BytecodeCompiler::emit(OpCode op, uint32_t operand) {
    if (m_CurrentFunction) {
        m_CurrentFunction->instructions.push_back(BytecodeInstruction(op, operand));
        std::cerr << "[DEBUG BC] emit Op:" << static_cast<int>(op) << " operand:" << operand << std::endl;
    }
}

static bool isX64Register(const std::string& name) {
    return name == "rcx" || name == "rdx" || name == "r8" || name == "r9" ||
           name == "rax" || name == "rbx" || name == "rsi" || name == "rdi";
}

void BytecodeCompiler::emitJump(OpCode op, uint32_t target) {
    emit(op, target);
}

void BytecodeCompiler::patchJump(uint32_t jumpPos, uint32_t target) {
    if (jumpPos < m_CurrentFunction->instructions.size()) {
        m_CurrentFunction->instructions[jumpPos].operand = target;
    }
}

uint32_t BytecodeCompiler::getStringOffset(const std::string& str) {
    return addString(str);
}

uint32_t BytecodeCompiler::getVariableSlot(const std::string& name) {
    auto it = m_VariableToSlot.find(name);
    if (it != m_VariableToSlot.end()) {
        std::cerr << "[DEBUG BC] getVariableSlot('" << name << "') -> existing slot " << it->second << std::endl;
        return it->second;
    }
    uint32_t slot = m_LocalVariables.size();
    m_VariableToSlot[name] = slot;
    m_LocalVariables.push_back(name);
    std::cerr << "[DEBUG BC] getVariableSlot('" << name << "') -> new slot " << slot << std::endl;
    return slot;
}

bool BytecodeCompiler::tryAddConstant(const std::string& val) {
    if (val.find('.') != std::string::npos) {
        double d = std::stod(val);
        emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeDouble(d)));
        return true;
    }
    if (val.find_first_not_of("0123456789") == std::string::npos) {
        int64_t i = std::stoll(val);
        emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeInt(i)));
        return true;
    }
    return false;
}

uint32_t BytecodeCompiler::getConstantIndex(const Quad& quad) {
    ConstantPoolEntry entry;
    const std::string& val = quad.getResult();

    if (val.find('.') != std::string::npos) {
        entry = ConstantPoolEntry::makeDouble(std::stod(val));
    } else if (val.find_first_not_of("0123456789") == std::string::npos) {
        entry = ConstantPoolEntry::makeInt(std::stoll(val));
    } else {
        entry = ConstantPoolEntry::makeString(getStringOffset(val));
    }

    return addConstant(entry);
}

OpCode BytecodeCompiler::getBinaryOp(const std::string& op) {
    if (op == "+" || op == "ADD") return OpCode::ADD;
    if (op == "-" || op == "SUB") return OpCode::SUB;
    if (op == "*" || op == "MUL") return OpCode::MUL;
    if (op == "/" || op == "DIV") return OpCode::DIV;
    if (op == "%" || op == "MOD") return OpCode::MOD;
    return OpCode::NOP;
}

OpCode BytecodeCompiler::getUnaryOp(const std::string& op) {
    if (op == "-" || op == "SUB") return OpCode::NEG;
    if (op == "!" || op == "NOT") return OpCode::NOT;
    if (op == "~" || op == "XOR") return OpCode::BITNOT;
    return OpCode::NOP;
}

OpCode BytecodeCompiler::getComparisonOp(const std::string& op) {
    if (op == "==" || op == "EQ") return OpCode::EQ;
    if (op == "!=" || op == "NE") return OpCode::NEQ;
    if (op == "<" || op == "LT") return OpCode::LT;
    if (op == ">" || op == "GT") return OpCode::GT;
    if (op == "<=" || op == "LE") return OpCode::LTE;
    if (op == ">=" || op == "GE") return OpCode::GTE;
    return OpCode::NOP;
}

void BytecodeCompiler::compileFunction(const Quad& funcQuad) {
    const std::string& funcName = funcQuad.getResult();
    BytecodeFunction func;
    func.nameOffset = getStringOffset(funcName);
    func.paramCount = 0;
    func.localCount = 0;
    func.maxStackSize = 16;

    BytecodeFunction* oldFunction = m_CurrentFunction;
    m_CurrentFunction = &func;

    emit(OpCode::NOP, 0);

    m_CurrentFunction = oldFunction;

    uint32_t funcIndex = addFunction(func);
    m_FunctionIndices[funcName] = funcIndex;
    emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeFunction(funcIndex)));
}

void BytecodeCompiler::compileQuad(const Quad& quad) {
    switch (quad.getOp()) {
        case OpEnum::FUNC: {
            compileFunction(quad);
            break;
        }

        case OpEnum::ASSIGN: {
            const std::string& src = quad.getArg1();
            const std::string& dest = quad.getResult();

            if (isX64Register(src)) {
                break;
            }

            bool isTempDest = dest.length() > 1 && dest[0] == 't' &&
                              dest.find_first_not_of("0123456789", 1) == std::string::npos;
            bool isParamDest = dest.substr(0, 6) == "param_";

            if (isParamDest) {
                if (src == m_LastStoredTemp && src.length() > 1 && src[0] == 't' &&
                    src.find_first_not_of("0123456789", 1) == std::string::npos) {
                    m_LastStoredTemp.clear();
                } else if (src.find('$') == 0) {
                    uint32_t srcSlot = std::stoul(src.substr(1));
                    emit(OpCode::LOAD_VAR, srcSlot);
                } else if (!tryAddConstant(src)) {
                    if (src.length() > 1 && src[0] == 't' &&
                        src.find_first_not_of("0123456789", 1) == std::string::npos) {
                        auto it = m_ConstTempValues.find(src);
                        if (it != m_ConstTempValues.end()) {
                            emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeInt(it->second)));
                        } else {
                            uint32_t srcSlot = getVariableSlot(src);
                            emit(OpCode::LOAD_VAR, srcSlot);
                        }
                    } else {
                        uint32_t srcSlot = getVariableSlot(src);
                        if (srcSlot != 0xFFFFFFFF) {
                            emit(OpCode::LOAD_VAR, srcSlot);
                        } else {
                            uint32_t idx = addConstant(ConstantPoolEntry::makeString(getStringOffset(src)));
                            emit(OpCode::LOAD_CONST, idx);
                        }
                    }
                }
                break;
            }

            if (src.find('$') == 0) {
                uint32_t srcSlot = std::stoul(src.substr(1));
                emit(OpCode::LOAD_VAR, srcSlot);
            } else if (!tryAddConstant(src)) {
                if (src.length() > 1 && src[0] == 't' &&
                    src.find_first_not_of("0123456789", 1) == std::string::npos) {
                    auto it = m_ConstTempValues.find(src);
                    if (it != m_ConstTempValues.end()) {
                        emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeInt(it->second)));
                    } else {
                        uint32_t srcSlot = getVariableSlot(src);
                        emit(OpCode::LOAD_VAR, srcSlot);
                    }
                } else {
                    uint32_t idx = addConstant(ConstantPoolEntry::makeString(getStringOffset(src)));
                    emit(OpCode::LOAD_CONST, idx);
                }
            }

            if (!isX64Register(dest)) {
                if (dest.find('$') == 0) {
                    uint32_t destSlot = std::stoul(dest.substr(1));
                    emit(OpCode::STORE_VAR, destSlot);
                } else if (isTempDest) {
                    emit(OpCode::STORE_VAR, getVariableSlot(dest));
                } else {
                    emit(OpCode::STORE_VAR, getVariableSlot(dest));
                }
                if (isTempDest && src.find_first_not_of("0123456789.-") == std::string::npos) {
                    if (src.find('.') != std::string::npos) {
                        m_ConstTempValues[dest] = static_cast<int64_t>(std::stod(src));
                    } else {
                        m_ConstTempValues[dest] = std::stoll(src);
                    }
                }
            }
            break;
        }

        case OpEnum::EXTERN: {
            break;
        }

        case OpEnum::ADD:
        case OpEnum::SUB:
        case OpEnum::MUL:
        case OpEnum::DIV:
        case OpEnum::MOD: {
            OpCode op;
            switch (quad.getOp()) {
                case OpEnum::ADD: op = OpCode::ADD; break;
                case OpEnum::SUB: op = OpCode::SUB; break;
                case OpEnum::MUL: op = OpCode::MUL; break;
                case OpEnum::DIV: op = OpCode::DIV; break;
                case OpEnum::MOD: op = OpCode::MOD; break;
                default: op = OpCode::NOP; break;
            }

            bool isSub = (quad.getOp() == OpEnum::SUB);
            const std::string& firstArg = isSub ? quad.getArg2() : quad.getArg1();
            const std::string& secondArg = isSub ? quad.getArg1() : quad.getArg2();

            if (firstArg.find('$') == 0) {
                emit(OpCode::LOAD_VAR, std::stoul(firstArg.substr(1)));
            } else if (firstArg.length() > 1 && firstArg[0] == 't' &&
                       firstArg.find_first_not_of("0123456789", 1) == std::string::npos) {
                emit(OpCode::LOAD_VAR, getVariableSlot(firstArg));
            } else if (firstArg.find_first_not_of("0123456789.-") == std::string::npos) {
                if (firstArg.find('.') != std::string::npos) {
                    double val = std::stod(firstArg);
                    emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeDouble(val)));
                } else {
                    int64_t val = std::stoll(firstArg);
                    emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeInt(val)));
                }
            } else {
                uint32_t srcSlot = getVariableSlot(firstArg);
                emit(OpCode::LOAD_VAR, srcSlot);
            }

            if (secondArg.find('$') == 0) {
                emit(OpCode::LOAD_VAR, std::stoul(secondArg.substr(1)));
            } else if (secondArg.length() > 1 && secondArg[0] == 't' &&
                       secondArg.find_first_not_of("0123456789", 1) == std::string::npos) {
                emit(OpCode::LOAD_VAR, getVariableSlot(secondArg));
            } else if (secondArg.find_first_not_of("0123456789.-") == std::string::npos) {
                if (secondArg.find('.') != std::string::npos) {
                    double val = std::stod(secondArg);
                    emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeDouble(val)));
                } else {
                    int64_t val = std::stoll(secondArg);
                    emit(OpCode::LOAD_CONST, addConstant(ConstantPoolEntry::makeInt(val)));
                }
            } else {
                uint32_t srcSlot = getVariableSlot(secondArg);
                emit(OpCode::LOAD_VAR, srcSlot);
            }

            emit(op, 0);

            if (!quad.getResult().empty() && quad.getResult() != "_") {
                if (quad.getResult().find('$') == 0) {
                    uint32_t destSlot = std::stoul(quad.getResult().substr(1));
                    emit(OpCode::STORE_VAR, destSlot);
                    m_LastStoredTemp.clear();
                } else if (quad.getResult().length() > 1 && quad.getResult()[0] == 't' &&
                           quad.getResult().find_first_not_of("0123456789", 1) == std::string::npos) {
                    uint32_t destSlot = getVariableSlot(quad.getResult());
                    emit(OpCode::STORE_VAR, destSlot);
                    m_LastStoredTemp = quad.getResult();
                } else {
                    uint32_t destSlot = getVariableSlot(quad.getResult());
                    emit(OpCode::STORE_VAR, destSlot);
                    m_LastStoredTemp.clear();
                }
            }
            break;
        }

        case OpEnum::NOT:
        case OpEnum::LOGICAL_NOT: {
            emit(OpCode::NOT, 0);
            break;
        }

        case OpEnum::AND:
        case OpEnum::LOGICAL_AND: {
            emit(OpCode::AND, 0);
            break;
        }

        case OpEnum::OR:
        case OpEnum::LOGICAL_OR: {
            emit(OpCode::OR, 0);
            break;
        }

        case OpEnum::XOR: {
            emit(OpCode::XOR, 0);
            break;
        }

        case OpEnum::EQ:
        case OpEnum::NE:
        case OpEnum::LT:
        case OpEnum::LE:
        case OpEnum::GT:
        case OpEnum::GE: {
            OpCode op;
            switch (quad.getOp()) {
                case OpEnum::EQ: op = OpCode::EQ; break;
                case OpEnum::NE: op = OpCode::NEQ; break;
                case OpEnum::LT: op = OpCode::LT; break;
                case OpEnum::LE: op = OpCode::LTE; break;
                case OpEnum::GT: op = OpCode::GT; break;
                case OpEnum::GE: op = OpCode::GTE; break;
                default: op = OpCode::NOP; break;
            }
            emit(op, 0);
            if (!quad.getResult().empty() && quad.getResult() != "_" &&
                quad.getResult()[0] == 't') {
                emit(OpCode::STORE_VAR, getVariableSlot(quad.getResult()));
            }
            break;
        }

        case OpEnum::LABEL:
            break;

        case OpEnum::JMP: {
            const std::string& target = quad.getResult();
            if (target.find_first_not_of("0123456789") == std::string::npos) {
                emit(OpCode::JUMP, std::stoul(target));
            } else {
                emit(OpCode::JUMP, 0);
            }
            break;
        }

        case OpEnum::JMPF: {
            const std::string& target = quad.getResult();
            if (target.find_first_not_of("0123456789") == std::string::npos) {
                emit(OpCode::JUMP_IF_FALSE, std::stoul(target));
            } else {
                emit(OpCode::JUMP_IF_FALSE, 0);
            }
            break;
        }

        case OpEnum::JMPT: {
            const std::string& target = quad.getResult();
            if (target.find_first_not_of("0123456789") == std::string::npos) {
                emit(OpCode::JUMP_IF_TRUE, std::stoul(target));
            } else {
                emit(OpCode::JUMP_IF_TRUE, 0);
            }
            break;
        }

        case OpEnum::PARAM: {
            const std::string& arg = quad.getArg1();
            const std::string& dest = quad.getResult();
            if (arg.find("param_") == 0) {
                uint32_t srcSlot = getVariableSlot(arg);
                uint32_t destSlot = getVariableSlot(dest);
                emit(OpCode::LOAD_VAR, srcSlot);
                emit(OpCode::STORE_VAR, destSlot);
            } else if (arg.find("t") == 0) {
                uint32_t srcSlot = getVariableSlot(arg);
                uint32_t destSlot = getVariableSlot(dest);
                emit(OpCode::LOAD_VAR, srcSlot);
                emit(OpCode::STORE_VAR, destSlot);
            } else if (arg.find_first_not_of("0123456789.-") == std::string::npos) {
                uint32_t destSlot = getVariableSlot(dest);
                if (arg.find('.') != std::string::npos) {
                    double val = std::stod(arg);
                    uint32_t idx = addConstant(ConstantPoolEntry::makeDouble(val));
                    emit(OpCode::LOAD_CONST, idx);
                } else {
                    int64_t val = std::stoll(arg);
                    uint32_t idx = addConstant(ConstantPoolEntry::makeInt(val));
                    emit(OpCode::LOAD_CONST, idx);
                }
                emit(OpCode::STORE_VAR, destSlot);
            } else {
                uint32_t srcSlot = getVariableSlot(arg);
                uint32_t destSlot = getVariableSlot(dest);
                emit(OpCode::LOAD_VAR, srcSlot);
                emit(OpCode::STORE_VAR, destSlot);
            }
            break;
        }

        case OpEnum::CALL: {
            const std::string& funcName = quad.getArg1();
            const std::string& arg2 = quad.getArg2();
            int paramCount = 0;
            if (!arg2.empty()) {
                paramCount = std::stoi(arg2);
            }
            auto it = m_FunctionIndices.find(funcName);
            if (it != m_FunctionIndices.end()) {
                uint32_t funcIdx = it->second;
                emit(OpCode::CALL, (paramCount << 16) | funcIdx);
            } else {
                uint32_t nameIdx = addString(funcName);
                emit(OpCode::CALL_NATIVE, (paramCount << 16) | nameIdx);
            }
            break;
        }

        case OpEnum::RET:
        case OpEnum::RETURN: {
            const std::string& result = quad.getResult();
            if (result.find('$') == 0) {
                uint32_t slot = std::stoul(result.substr(1));
                emit(OpCode::LOAD_VAR, slot);
            } else if (result.find_first_not_of("0123456789.-") == std::string::npos) {
                if (result.find('.') != std::string::npos) {
                    double val = std::stod(result);
                    uint32_t idx = addConstant(ConstantPoolEntry::makeDouble(val));
                    emit(OpCode::LOAD_CONST, idx);
                } else {
                    int64_t val = std::stoll(result);
                    uint32_t idx = addConstant(ConstantPoolEntry::makeInt(val));
                    emit(OpCode::LOAD_CONST, idx);
                }
            } else if (!isX64Register(result)) {
                uint32_t slot = getVariableSlot(result);
                emit(OpCode::LOAD_VAR, slot);
            }
            emit(OpCode::RETURN, 0);
            break;
        }

        case OpEnum::ENDFUNC: {
            emit(OpCode::HALT, 0);
            break;
        }

        default:
            break;
    }
}

BytecodeModule* BytecodeCompiler::compile(const std::list<Quad>& quadList, SymbolTable& symbolTable) {
    reset();
    m_SymbolTable = &symbolTable;

    std::cerr << "[DEBUG] Compiling " << quadList.size() << " quads" << std::endl;

    for (const auto& quad : quadList) {
        std::cerr << "[DEBUG] Quad: op=" << static_cast<int>(quad.getOp())
                  << " arg1=" << quad.getArg1()
                  << " arg2=" << quad.getArg2()
                  << " result=" << quad.getResult() << std::endl;
    }

    struct FuncRange {
        std::string name;
        std::list<Quad>::const_iterator start;
        std::list<Quad>::const_iterator end;
    };
    std::vector<FuncRange> userFunctions;
    FuncRange mainRange;

    bool inExternBlock = true;
    for (auto it = quadList.begin(); it != quadList.end(); ++it) {
        const Quad& quad = *it;

        if (quad.getOp() == OpEnum::FUNC) {
            std::string funcName = quad.getResult();
            std::cerr << "[DEBUG] Found FUNC: " << funcName << std::endl;

            if (funcName == "main") {
                mainRange.name = funcName;
                mainRange.start = it;
                auto endIt = findMatchingENDFUNC(it, quadList.end());
                mainRange.end = endIt;
                std::cerr << "[DEBUG] main range: " << std::distance(quadList.begin(), it)
                          << " to " << std::distance(quadList.begin(), endIt) << std::endl;
            } else {
                FuncRange fr;
                fr.name = funcName;
                fr.start = it;
                auto endIt = findMatchingENDFUNC(it, quadList.end());
                fr.end = endIt;
                userFunctions.push_back(fr);
                std::cerr << "[DEBUG] User function " << funcName << " range: "
                          << std::distance(quadList.begin(), it) << " to "
                          << std::distance(quadList.begin(), endIt) << std::endl;
            }
        }
    }

    std::cerr << "[DEBUG] Found " << userFunctions.size() << " user functions + main" << std::endl;

    for (const auto& f : userFunctions) {
        BytecodeFunction func;
        func.nameOffset = getStringOffset(f.name);
        func.paramCount = 0;
        func.localCount = 0;
        func.maxStackSize = 16;

        m_CurrentFunction = &func;
        m_CurrentFunctionName = f.name;

        compileFunctionBody(f.start, f.end);

        emit(OpCode::RETURN, 0);

        uint32_t funcIndex = addFunction(func);
        m_FunctionIndices[f.name] = funcIndex;
        std::cerr << "[DEBUG] Compiled function '" << f.name << "' with " << func.instructions.size() << " instructions, index=" << funcIndex << std::endl;
    }

    BytecodeFunction mainFunc;
    mainFunc.nameOffset = getStringOffset("main");
    mainFunc.paramCount = 0;
    mainFunc.localCount = 0;
    mainFunc.maxStackSize = 16;

    m_CurrentFunction = &mainFunc;
    m_CurrentFunctionName = "main";

    compileFunctionBody(mainRange.start, mainRange.end);

    if (mainFunc.instructions.empty() ||
        mainFunc.instructions.back().op != OpCode::HALT) {
        emit(OpCode::HALT, 0);
    }

    uint32_t mainIndex = addFunction(mainFunc);
    std::cerr << "[DEBUG] Compiled main with " << mainFunc.instructions.size() << " instructions, index=" << mainIndex << std::endl;

    m_Module->header.functionCount = m_Functions.size();
    m_Module->header.totalConstants = m_Module->globalConstants.size();
    m_Module->header.stringPoolSize = m_NextStringOffset;
    m_Module->header.entryPointIndex = mainIndex;

    std::cerr << "[DEBUG BC] Final: functionCount=" << m_Module->header.functionCount
              << " totalConstants=" << m_Module->header.totalConstants
              << " stringPoolSize=" << m_Module->header.stringPoolSize << std::endl;

    return m_Module;
}

std::list<Quad>::const_iterator BytecodeCompiler::findMatchingENDFUNC(
    std::list<Quad>::const_iterator funcIt,
    std::list<Quad>::const_iterator end) {

    std::string funcName = funcIt->getResult();
    int depth = 1;

    for (auto it = std::next(funcIt); it != end; ++it) {
        if (it->getOp() == OpEnum::FUNC) {
            depth++;
        } else if (it->getOp() == OpEnum::ENDFUNC) {
            depth--;
            if (depth == 0) {
                return it;
            }
        }
    }
    return end;
}

void BytecodeCompiler::compileFunctionBody(
    std::list<Quad>::const_iterator start,
    std::list<Quad>::const_iterator end) {

    m_LastStoredTemp.clear();
    int nestedDepth = 0;

    for (auto it = std::next(start); it != end; ++it) {
        const Quad& quad = *it;

        if (quad.getOp() == OpEnum::FUNC) {
            nestedDepth++;
            continue;
        }

        if (quad.getOp() == OpEnum::ENDFUNC) {
            nestedDepth--;
            continue;
        }

        if (nestedDepth == 0) {
            compileQuad(quad);
        }
    }
}

}
