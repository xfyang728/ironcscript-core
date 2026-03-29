#include "CSBLoader.h"
#include "K210Flash.h"
#include <cstdio>

namespace cse {

bool CSBLoader::readFlash(uint32_t addr, void* buffer, size_t len) {
    int result = k210_spi3_flash_read(addr, static_cast<uint8_t*>(buffer), len);
    printf("[CSB] readFlash addr=0x%X len=%zu result=%d\r\n", addr, len, result);
    fflush(stdout);
    if (result != 0) {
        printf("[CSB] readFlash FAILED\r\n");
        fflush(stdout);
        return false;
    }
    return true;
}

bool CSBLoader::loadFromFlash(uint32_t addr, BytecodeModule& module) {
    printf("[CSB] loadFromFlash addr=0x%X\r\n", addr);
    fflush(stdout);
    BytecodeHeader header;
    if (!readFlash(addr, &header, sizeof(header))) {
        printf("[CSB] ERROR: readFlash header failed\r\n");
        fflush(stdout);
        return false;
    }
    printf("[CSB] header bytes: %02X %02X %02X %02X\r\n",
           header.magic[0], header.magic[1], header.magic[2], header.magic[3]);
    fflush(stdout);

    if (!header.isValid()) {
        printf("[CSB] ERROR: header invalid\r\n");
        fflush(stdout);
        return false;
    }
    printf("[CSB] header valid\r\n");
    fflush(stdout);

    module.header = header;
    module.functions.clear();
    module.stringPool.clear();
    module.globalConstants.clear();

    uint32_t currentAddr = addr + sizeof(BytecodeHeader);

    uint32_t funcCount = header.functionCount;
    printf("[CSB] funcCount=%u, sizeof(BytecodeHeader)=%u, firstFuncAddr=0x%X\r\n",
           funcCount, (unsigned)sizeof(BytecodeHeader), currentAddr);
    fflush(stdout);

    for (uint32_t i = 0; i < funcCount; ++i) {
        printf("[CSB] === Loading func %u ===\r\n", i);
        fflush(stdout);
        BytecodeFunction func;
        func.instructions.clear();
        func.constants.clear();

        uint32_t nameOffset = 0;
        if (!readFlash(currentAddr, &nameOffset, sizeof(uint32_t))) return false;
        func.nameOffset = nameOffset;
        printf("[CSB] func[%u].nameOffset=%u\r\n", i, nameOffset);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        uint32_t paramCount = 0;
        if (!readFlash(currentAddr, &paramCount, sizeof(uint32_t))) return false;
        func.paramCount = paramCount;
        printf("[CSB] func[%u].paramCount=%u\r\n", i, paramCount);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        uint32_t localCount = 0;
        if (!readFlash(currentAddr, &localCount, sizeof(uint32_t))) return false;
        func.localCount = localCount;
        printf("[CSB] func[%u].localCount=%u\r\n", i, localCount);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        uint32_t maxStackSize = 0;
        if (!readFlash(currentAddr, &maxStackSize, sizeof(uint32_t))) return false;
        func.maxStackSize = maxStackSize;
        printf("[CSB] func[%u].maxStackSize=%u\r\n", i, maxStackSize);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        uint32_t instrCount = 0;
        if (!readFlash(currentAddr, &instrCount, sizeof(uint32_t))) return false;
        printf("[CSB] func[%u].instrCount=%u\r\n", i, instrCount);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        printf("[CSB] func[%u] sizeof(BytecodeInstruction)=%u, totalInstrBytes=%u\r\n",
               i, (unsigned)sizeof(cse::BytecodeInstruction),
               (unsigned)(instrCount * sizeof(cse::BytecodeInstruction)));
        fflush(stdout);

        printf("[CSB] func[%u] resizing instructions to %u\r\n", i, instrCount);
        fflush(stdout);
        func.instructions.resize(instrCount);
        printf("[CSB] func[%u] instructions resize done\r\n", i);
        fflush(stdout);

        if (instrCount > 0) {
            size_t totalInstrBytes = instrCount * sizeof(cse::BytecodeInstruction);
            printf("[CSB] func[%u] reading %u bytes instructions from addr 0x%X\r\n",
                   i, (unsigned)totalInstrBytes, currentAddr);
            fflush(stdout);

            std::vector<cse::BytecodeInstruction> tempInstr(instrCount);
            if (!readFlash(currentAddr, tempInstr.data(), totalInstrBytes)) return false;
            for (uint32_t k = 0; k < instrCount; k++) {
                func.instructions[k] = tempInstr[k];
            }
            printf("[CSB] func[%u] instructions read done\r\n", i);
            fflush(stdout);
            currentAddr += totalInstrBytes;
        }

        uint32_t constCount = 0;
        uint8_t constCountRaw[4] = {0};
        if (!readFlash(currentAddr, constCountRaw, sizeof(uint32_t))) return false;
        constCount = *reinterpret_cast<uint32_t*>(constCountRaw);
        printf("[CSB] func[%u].constCount=%u (raw: %02X %02X %02X %02X)\r\n",
               i, constCount, constCountRaw[0], constCountRaw[1], constCountRaw[2], constCountRaw[3]);
        fflush(stdout);
        currentAddr += sizeof(uint32_t);

        if (constCount == 0xFFFFFFFF || constCount > 10000) {
            printf("[CSB] ERROR: constCount invalid (%u), likely flash read failure\r\n", constCount);
            printf("[CSB] currentAddr after constCount read: 0x%X\r\n", currentAddr);
            fflush(stdout);
            return false;
        }

        printf("[CSB] func[%u] resizing constants to %u\r\n", i, constCount);
        fflush(stdout);
        func.constants.resize(constCount);
        printf("[CSB] func[%u] constants resize done\r\n", i);
        fflush(stdout);

        for (uint32_t j = 0; j < constCount; ++j) {
            if (!readFlash(currentAddr, &func.constants[j].type, sizeof(uint8_t))) return false;
            printf("[CSB] func[%u] const[%u].type=%u\r\n", i, j, (unsigned)func.constants[j].type);
            fflush(stdout);
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

        printf("[CSB] func[%u] pushing to module.functions\r\n", i);
        fflush(stdout);
        module.functions.push_back(func);
        printf("[CSB] func[%u] pushed OK\r\n", i);
        fflush(stdout);
    }

    uint32_t globalConstCount = 0;
    if (!readFlash(currentAddr, &globalConstCount, sizeof(uint32_t))) return false;
    printf("[CSB] globalConstCount=%u\r\n", globalConstCount);
    fflush(stdout);
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
    printf("[CSB] stringCount=%u\r\n", stringCount);
    fflush(stdout);
    currentAddr += sizeof(uint32_t);

    module.stringPool.resize(stringCount);
    printf("[CSB] Loading %u strings\r\n", stringCount);
    fflush(stdout);
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
        printf("[CSB] stringPool[%u]: \"%s\" (len=%u)\r\n", i, module.stringPool[i].c_str(), actualLen);
        fflush(stdout);
    }

    printf("[CSB] All loaded successfully!\r\n");
    fflush(stdout);
    return true;
}

}