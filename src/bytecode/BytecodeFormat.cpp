#include "bytecode/BytecodeFormat.h"
#include <cstring>

#if defined(USE_STDIO) || !defined(EMBEDDED_BUILD)
#include <fstream>
#include <iostream>
#endif

namespace cse {

#if defined(USE_STDIO) || !defined(EMBEDDED_BUILD)
bool BytecodeModule::saveToFile(const std::string& path) const {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    std::cerr << "[DEBUG BytecodeFormat] saveToFile: header.functionCount=" << header.functionCount
              << " header.totalConstants=" << header.totalConstants
              << " header.stringPoolSize=" << header.stringPoolSize << std::endl;

    file.write(reinterpret_cast<const char*>(&header), sizeof(BytecodeHeader));

    for (const auto& func : functions) {
        file.write(reinterpret_cast<const char*>(&func.nameOffset), sizeof(uint32_t));
        file.write(reinterpret_cast<const char*>(&func.paramCount), sizeof(uint32_t));
        file.write(reinterpret_cast<const char*>(&func.localCount), sizeof(uint32_t));
        file.write(reinterpret_cast<const char*>(&func.maxStackSize), sizeof(uint32_t));

        uint32_t instrCount = func.instructions.size();
        file.write(reinterpret_cast<const char*>(&instrCount), sizeof(uint32_t));
        file.write(reinterpret_cast<const char*>(func.instructions.data()),
                   instrCount * sizeof(BytecodeInstruction));

        uint32_t constCount = func.constants.size();
        file.write(reinterpret_cast<const char*>(&constCount), sizeof(uint32_t));
        for (const auto& c : func.constants) {
            file.write(reinterpret_cast<const char*>(&c.type), sizeof(uint8_t));
            switch (c.type) {
                case ConstantPoolEntry::Type::INTEGER:
                    file.write(reinterpret_cast<const char*>(&c.value.intVal), sizeof(int64_t));
                    break;
                case ConstantPoolEntry::Type::DOUBLE:
                    file.write(reinterpret_cast<const char*>(&c.value.doubleVal), sizeof(double));
                    break;
                case ConstantPoolEntry::Type::STRING:
                case ConstantPoolEntry::Type::FUNCTION:
                case ConstantPoolEntry::Type::NATIVE_FUNC:
                    file.write(reinterpret_cast<const char*>(&c.value.stringOffset), sizeof(uint32_t));
                    break;
            }
        }
    }

    uint32_t globalConstCount = globalConstants.size();
    file.write(reinterpret_cast<const char*>(&globalConstCount), sizeof(uint32_t));
    for (const auto& c : globalConstants) {
        file.write(reinterpret_cast<const char*>(&c.type), sizeof(uint8_t));
        switch (c.type) {
            case ConstantPoolEntry::Type::INTEGER:
                file.write(reinterpret_cast<const char*>(&c.value.intVal), sizeof(int64_t));
                break;
            case ConstantPoolEntry::Type::DOUBLE:
                file.write(reinterpret_cast<const char*>(&c.value.doubleVal), sizeof(double));
                break;
            case ConstantPoolEntry::Type::STRING:
            case ConstantPoolEntry::Type::FUNCTION:
            case ConstantPoolEntry::Type::NATIVE_FUNC:
                file.write(reinterpret_cast<const char*>(&c.value.stringOffset), sizeof(uint32_t));
                break;
        }
    }

    uint32_t stringCount = stringPool.size();
    file.write(reinterpret_cast<const char*>(&stringCount), sizeof(uint32_t));
    for (const auto& s : stringPool) {
        uint32_t len = s.size() + 1;
        file.write(reinterpret_cast<const char*>(&len), sizeof(uint32_t));
        file.write(s.c_str(), len);
    }

    return true;
}

bool BytecodeModule::loadFromFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    if (!file.read(reinterpret_cast<char*>(&header), sizeof(BytecodeHeader))) {
        return false;
    }

    if (!header.isValid()) {
        return false;
    }

    uint32_t funcCount = 0;
    if (!file.read(reinterpret_cast<char*>(&funcCount), sizeof(uint32_t))) {
        return false;
    }

    functions.clear();
    for (uint32_t i = 0; i < funcCount; ++i) {
        BytecodeFunction func;
        file.read(reinterpret_cast<char*>(&func.nameOffset), sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(&func.paramCount), sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(&func.localCount), sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(&func.maxStackSize), sizeof(uint32_t));

        uint32_t instrCount = 0;
        file.read(reinterpret_cast<char*>(&instrCount), sizeof(uint32_t));
        func.instructions.resize(instrCount);
        if (instrCount > 0) {
            file.read(reinterpret_cast<char*>(func.instructions.data()),
                      instrCount * sizeof(BytecodeInstruction));
        }

        uint32_t constCount = 0;
        file.read(reinterpret_cast<char*>(&constCount), sizeof(uint32_t));
        func.constants.resize(constCount);
        for (uint32_t j = 0; j < constCount; ++j) {
            file.read(reinterpret_cast<char*>(&func.constants[j].type), sizeof(uint8_t));
            switch (func.constants[j].type) {
                case ConstantPoolEntry::Type::INTEGER:
                    file.read(reinterpret_cast<char*>(&func.constants[j].value.intVal), sizeof(int64_t));
                    break;
                case ConstantPoolEntry::Type::DOUBLE:
                    file.read(reinterpret_cast<char*>(&func.constants[j].value.doubleVal), sizeof(double));
                    break;
                case ConstantPoolEntry::Type::STRING:
                case ConstantPoolEntry::Type::FUNCTION:
                case ConstantPoolEntry::Type::NATIVE_FUNC:
                    file.read(reinterpret_cast<char*>(&func.constants[j].value.stringOffset), sizeof(uint32_t));
                    break;
            }
        }

        functions.push_back(func);
    }

    uint32_t globalConstCount = 0;
    if (!file.read(reinterpret_cast<char*>(&globalConstCount), sizeof(uint32_t))) {
        return false;
    }

    globalConstants.clear();
    globalConstants.resize(globalConstCount);
    for (uint32_t i = 0; i < globalConstCount; ++i) {
        file.read(reinterpret_cast<char*>(&globalConstants[i].type), sizeof(uint8_t));
        switch (globalConstants[i].type) {
            case ConstantPoolEntry::Type::INTEGER:
                file.read(reinterpret_cast<char*>(&globalConstants[i].value.intVal), sizeof(int64_t));
                break;
            case ConstantPoolEntry::Type::DOUBLE:
                file.read(reinterpret_cast<char*>(&globalConstants[i].value.doubleVal), sizeof(double));
                break;
            case ConstantPoolEntry::Type::STRING:
            case ConstantPoolEntry::Type::FUNCTION:
            case ConstantPoolEntry::Type::NATIVE_FUNC:
                file.read(reinterpret_cast<char*>(&globalConstants[i].value.stringOffset), sizeof(uint32_t));
                break;
        }
    }

    uint32_t stringCount = 0;
    if (!file.read(reinterpret_cast<char*>(&stringCount), sizeof(uint32_t))) {
        return false;
    }

    stringPool.clear();
    for (uint32_t i = 0; i < stringCount; ++i) {
        uint32_t len = 0;
        file.read(reinterpret_cast<char*>(&len), sizeof(uint32_t));
        std::string s(len, '\0');
        if (len > 0) {
            file.read(&s[0], len);
        }
        stringPool.push_back(s);
    }

    return true;
}

bool BytecodeModule::validate() const {
    if (!header.isValid()) {
        return false;
    }

    for (const auto& func : functions) {
        for (const auto& instr : func.instructions) {
            if (instr.op == OpCode::LOAD_CONST ||
                instr.op == OpCode::STORE_VAR ||
                instr.op == OpCode::LOAD_VAR) {
                if (instr.operand >= func.constants.size()) {
                    return false;
                }
            }
        }
    }

    return true;
}

#endif

}
