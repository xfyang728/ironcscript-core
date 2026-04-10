#include "STM32CSBLoader.h"
#include <cstdio>
#include <cstring>

extern "C" void Serial_SendString(const char* str);

namespace cse {

bool STM32CSBLoader::readFlash(uint32_t addr, void* buffer, size_t len) {
    if (addr < 0x08000000 || addr > 0x080FFFFF) {
        Serial_SendString("[CSB] ERR: bad addr\r\n");
        return false;
    }
    memcpy(buffer, reinterpret_cast<const void*>(addr), len);
    return true;
}

bool STM32CSBLoader::isValidHeader(uint32_t addr) {
    char magic[4] = {0};
    if (!readFlash(addr, magic, 4)) {
        return false;
    }
    return (magic[0] == 'C' && magic[1] == 'S' && magic[2] == 'B' && magic[3] == '\x01');
}

bool STM32CSBLoader::loadFromFlash(uint32_t addr, BytecodeModule& module) {
    Serial_SendString("[CSB] loadFromFlash\r\n");

    BytecodeHeader header;
    if (!readFlash(addr, &header, sizeof(header))) {
        Serial_SendString("[CSB] ERR: read header fail\r\n");
        return false;
    }

    if (!header.isValid()) {
        Serial_SendString("[CSB] ERR: header invalid\r\n");
        return false;
    }
    Serial_SendString("[CSB] header valid\r\n");

    module.header = header;
    module.functions.clear();
    module.stringPool.clear();
    module.globalConstants.clear();

    uint32_t currentAddr = addr + sizeof(BytecodeHeader);
    uint32_t funcCount = header.functionCount;

    for (uint32_t i = 0; i < funcCount; ++i) {
        BytecodeFunction func;
        func.instructions.clear();
        func.constants.clear();

        uint32_t nameOffset = 0;
        if (!readFlash(currentAddr, &nameOffset, sizeof(uint32_t))) return false;
        func.nameOffset = nameOffset;
        currentAddr += sizeof(uint32_t);

        uint32_t paramCount = 0;
        if (!readFlash(currentAddr, &paramCount, sizeof(uint32_t))) return false;
        func.paramCount = paramCount;
        currentAddr += sizeof(uint32_t);

        uint32_t localCount = 0;
        if (!readFlash(currentAddr, &localCount, sizeof(uint32_t))) return false;
        func.localCount = localCount;
        currentAddr += sizeof(uint32_t);

        uint32_t maxStackSize = 0;
        if (!readFlash(currentAddr, &maxStackSize, sizeof(uint32_t))) return false;
        func.maxStackSize = maxStackSize;
        currentAddr += sizeof(uint32_t);

        uint32_t instrCount = 0;
        if (!readFlash(currentAddr, &instrCount, sizeof(uint32_t))) return false;
        currentAddr += sizeof(uint32_t);

        func.instructions.resize(instrCount);
        if (instrCount > 0) {
            size_t totalInstrBytes = instrCount * sizeof(BytecodeInstruction);
            std::vector<BytecodeInstruction> tempInstr(instrCount);
            if (!readFlash(currentAddr, tempInstr.data(), totalInstrBytes)) return false;
            for (uint32_t k = 0; k < instrCount; k++) {
                func.instructions[k] = tempInstr[k];
            }
            currentAddr += totalInstrBytes;
        }

        uint32_t constCount = 0;
        if (!readFlash(currentAddr, &constCount, sizeof(uint32_t))) return false;
        currentAddr += sizeof(uint32_t);

        if (constCount == 0xFFFFFFFF || constCount > 10000) {
            Serial_SendString("[CSB] ERR: bad constCount\r\n");
            return false;
        }

        func.constants.resize(constCount);

        for (uint32_t j = 0; j < constCount; ++j) {
            if (!readFlash(currentAddr, &func.constants[j].type, sizeof(uint8_t))) return false;
            currentAddr += sizeof(uint8_t);

            switch (func.constants[j].type) {
                case ConstantPoolEntry::Type::INTEGER:
                    if (!readFlash(currentAddr, &func.constants[j].value.intVal, sizeof(int64_t))) return false;
                    currentAddr += sizeof(int64_t);
                    break;
                case ConstantPoolEntry::Type::DOUBLE:
                    if (!readFlash(currentAddr, &func.constants[j].value.doubleVal, sizeof(double))) return false;
                    currentAddr += sizeof(double);
                    break;
                case ConstantPoolEntry::Type::STRING:
                case ConstantPoolEntry::Type::FUNCTION:
                case ConstantPoolEntry::Type::NATIVE_FUNC:
                    if (!readFlash(currentAddr, &func.constants[j].value.stringOffset, sizeof(uint32_t))) return false;
                    currentAddr += sizeof(uint32_t);
                    break;
            }
        }

        module.functions.push_back(func);
        Serial_SendString("[CSB] func loaded\r\n");
    }

    uint32_t globalConstCount = 0;
    if (!readFlash(currentAddr, &globalConstCount, sizeof(uint32_t))) return false;
    currentAddr += sizeof(uint32_t);

    module.globalConstants.resize(globalConstCount);
    for (uint32_t i = 0; i < globalConstCount; ++i) {
        if (!readFlash(currentAddr, &module.globalConstants[i].type, sizeof(uint8_t))) return false;
        currentAddr += sizeof(uint8_t);

        switch (module.globalConstants[i].type) {
            case ConstantPoolEntry::Type::INTEGER:
                if (!readFlash(currentAddr, &module.globalConstants[i].value.intVal, sizeof(int64_t))) return false;
                currentAddr += sizeof(int64_t);
                break;
            case ConstantPoolEntry::Type::DOUBLE:
                if (!readFlash(currentAddr, &module.globalConstants[i].value.doubleVal, sizeof(double))) return false;
                currentAddr += sizeof(double);
                break;
            case ConstantPoolEntry::Type::STRING:
            case ConstantPoolEntry::Type::FUNCTION:
            case ConstantPoolEntry::Type::NATIVE_FUNC:
                if (!readFlash(currentAddr, &module.globalConstants[i].value.stringOffset, sizeof(uint32_t))) return false;
                currentAddr += sizeof(uint32_t);
                break;
        }
    }

    uint32_t stringCount = 0;
    if (!readFlash(currentAddr, &stringCount, sizeof(uint32_t))) return false;
    currentAddr += sizeof(uint32_t);

    module.stringPool.resize(stringCount);
    for (uint32_t i = 0; i < stringCount; ++i) {
        uint32_t len = 0;
        if (!readFlash(currentAddr, &len, sizeof(uint32_t))) return false;
        currentAddr += sizeof(uint32_t);

        uint32_t actualLen = (len > 0) ? (len - 1) : 0;
        module.stringPool[i].resize(actualLen);
        if (len > 0) {
            if (!readFlash(currentAddr, &module.stringPool[i][0], actualLen)) return false;
            currentAddr += len;
        }
    }

    Serial_SendString("[CSB] load OK\r\n");
    return true;
}

}
