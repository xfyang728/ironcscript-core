#include "CScriptEngine.h"
#include "bytecode/vm/k210/K210VM.h"
#include "bytecode/BytecodeFormat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <cstring>

static uint32_t g_UptimeMs = 0;

void nativeDelay(cse::BytecodeVM* vm) {
    int ms = static_cast<int>(vm->getArg(0).value.intVal);
    std::cout << "[STUB] delay(" << ms << ")" << std::endl;
    g_UptimeMs += ms;
}

void nativeMillis(cse::BytecodeVM* vm) {
    vm->getReturnValue() = cse::VMValue::makeInt(g_UptimeMs);
}

void nativePinMode(cse::BytecodeVM* vm) {
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int mode = static_cast<int>(vm->getArg(1).value.intVal);
    std::cout << "[STUB] pinMode(" << pin << ", " << mode << ")" << std::endl;
}

void nativeDigitalWrite(cse::BytecodeVM* vm) {
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int value = static_cast<int>(vm->getArg(1).value.intVal);
    std::cout << "[STUB] digitalWrite(" << pin << ", " << value << ")" << std::endl;
}

void nativeDigitalRead(cse::BytecodeVM* vm) {
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    std::cout << "[STUB] digitalRead(" << pin << ")" << std::endl;
    vm->getReturnValue() = cse::VMValue::makeInt(0);
}

void nativeAnalogWrite(cse::BytecodeVM* vm) {
    int32_t argCount = vm->getArgCount();
    int32_t stackTop = vm->getStackUsed();
    std::cout << "[STUB] analogWrite(argCount=" << argCount << ", stackTop=" << stackTop << ", ";
    for (int i = 0; i < argCount; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << "arg[" << i << "]=" << vm->getArg(i).value.intVal;
    }
    std::cout << ")" << std::endl;
}

void nativeRgbSet(cse::BytecodeVM* vm) {
    int r = static_cast<int>(vm->getArg(0).value.intVal);
    int g = static_cast<int>(vm->getArg(1).value.intVal);
    int b = static_cast<int>(vm->getArg(2).value.intVal);
    std::cout << "[STUB] rgb_set(" << r << ", " << g << ", " << b << ")" << std::endl;
}

void nativeFpioaSetFunc(cse::BytecodeVM* vm) {
    int pin = static_cast<int>(vm->getArg(0).value.intVal);
    int func = static_cast<int>(vm->getArg(1).value.intVal);
    std::cout << "[STUB] fpioa_set_func(" << pin << ", " << func << ")" << std::endl;
}

void nativeSerialPrint(cse::BytecodeVM* vm) {
    std::cout << "[STUB] Serial.print" << std::endl;
}

void nativeSerialPrintln(cse::BytecodeVM* vm) {
    std::cout << "[STUB] Serial.println" << std::endl;
}

void nativeDumpConstants(cse::BytecodeVM* vm) {
    std::cout << "[STUB] dump_constants" << std::endl;
}

void printUsage(const char* programName) {
    std::cout << "K210 CScript Runner v1.0" << std::endl;
    std::cout << "Usage: " << programName << " <bytecode_file>" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  bytecode_file   Path to the .csb bytecode file" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  " << programName << " hello.csb" << std::endl;
}

bool readFile(const std::string& path, std::vector<uint8_t>& outData) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    outData.resize(size);
    file.read(reinterpret_cast<char*>(outData.data()), size);
    return file.good() || file.eof();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string bytecodePath = argv[1];

    std::cout << "K210 CScript Runner" << std::endl;
    std::cout << "Bytecode: " << bytecodePath << std::endl;
    std::cout << std::endl;

    std::vector<uint8_t> fileData;
    if (!readFile(bytecodePath, fileData)) {
        std::cerr << "Error: Cannot read bytecode file: " << bytecodePath << std::endl;
        return 1;
    }

    std::cerr << "[DEBUG] readFile returned " << fileData.size() << " bytes" << std::endl;

    std::istringstream iss(std::string(reinterpret_cast<char*>(fileData.data()), fileData.size()));
    iss.seekg(0, std::ios::end);
    size_t streamSize = iss.tellg();
    iss.seekg(0, std::ios::beg);
    std::cerr << "[DEBUG] stringstream size: " << streamSize << std::endl;

    cse::BytecodeModule module;
    iss.read(reinterpret_cast<char*>(&module.header), sizeof(cse::BytecodeHeader));
    std::cerr << "[DEBUG] header isValid=" << module.header.isValid()
              << " functionCount=" << module.header.functionCount << std::endl;

    if (!module.header.isValid()) {
        std::cerr << "Error: Invalid bytecode format" << std::endl;
        return 1;
    }

    uint32_t funcCount = module.header.functionCount;
    std::cerr << "[DEBUG] Using funcCount from header: " << funcCount << std::endl;

    module.functions.clear();
    for (uint32_t i = 0; i < funcCount; ++i) {
        cse::BytecodeFunction func;
        iss.read(reinterpret_cast<char*>(&func.nameOffset), sizeof(uint32_t));
        iss.read(reinterpret_cast<char*>(&func.paramCount), sizeof(uint32_t));
        iss.read(reinterpret_cast<char*>(&func.localCount), sizeof(uint32_t));
        iss.read(reinterpret_cast<char*>(&func.maxStackSize), sizeof(uint32_t));

        uint32_t instrCount = 0;
        iss.read(reinterpret_cast<char*>(&instrCount), sizeof(uint32_t));
        func.instructions.resize(instrCount);
        if (instrCount > 0) {
            iss.read(reinterpret_cast<char*>(func.instructions.data()),
                     instrCount * sizeof(cse::BytecodeInstruction));
        }

        uint32_t constCount = 0;
        iss.read(reinterpret_cast<char*>(&constCount), sizeof(uint32_t));
        func.constants.resize(constCount);
        for (uint32_t j = 0; j < constCount; ++j) {
            iss.read(reinterpret_cast<char*>(&func.constants[j].type), sizeof(uint8_t));
            switch (func.constants[j].type) {
                case cse::ConstantPoolEntry::Type::INTEGER:
                    iss.read(reinterpret_cast<char*>(&func.constants[j].value.intVal), sizeof(int64_t));
                    break;
                case cse::ConstantPoolEntry::Type::DOUBLE:
                    iss.read(reinterpret_cast<char*>(&func.constants[j].value.doubleVal), sizeof(double));
                    break;
                default:
                    iss.read(reinterpret_cast<char*>(&func.constants[j].value.stringOffset), sizeof(uint32_t));
                    break;
            }
        }
        module.functions.push_back(func);
        std::cerr << "[DEBUG] Loaded func[" << i << "]: instrCount=" << instrCount << " constCount=" << constCount << std::endl;
    }

    uint32_t globalConstCount = 0;
    iss.read(reinterpret_cast<char*>(&globalConstCount), sizeof(uint32_t));
    std::cerr << "[DEBUG] globalConstCount: " << globalConstCount << std::endl;
    module.globalConstants.resize(globalConstCount);
    for (uint32_t i = 0; i < globalConstCount; ++i) {
        iss.read(reinterpret_cast<char*>(&module.globalConstants[i].type), sizeof(uint8_t));
        switch (module.globalConstants[i].type) {
            case cse::ConstantPoolEntry::Type::INTEGER:
                iss.read(reinterpret_cast<char*>(&module.globalConstants[i].value.intVal), sizeof(int64_t));
                break;
            case cse::ConstantPoolEntry::Type::DOUBLE:
                iss.read(reinterpret_cast<char*>(&module.globalConstants[i].value.doubleVal), sizeof(double));
                break;
            default:
                iss.read(reinterpret_cast<char*>(&module.globalConstants[i].value.stringOffset), sizeof(uint32_t));
                break;
        }
    }

    uint32_t stringCount = 0;
    iss.read(reinterpret_cast<char*>(&stringCount), sizeof(uint32_t));
    std::cerr << "[DEBUG] stringCount: " << stringCount << std::endl;
    module.stringPool.clear();
    for (uint32_t i = 0; i < stringCount; ++i) {
        uint32_t len = 0;
        iss.read(reinterpret_cast<char*>(&len), sizeof(uint32_t));
        std::string s(len, '\0');
        if (len > 0) {
            iss.read(&s[0], len);
        }
        if (!s.empty() && s.back() == '\0') {
            s.pop_back();
        }
        module.stringPool.push_back(s);
    }

    std::cerr << "[DEBUG] After manual load: functions.size()=" << module.functions.size()
              << " globalConstants.size()=" << module.globalConstants.size()
              << " stringPool.size()=" << module.stringPool.size() << std::endl;

    cse::K210VM vm;
    vm.registerNativeFunction("delay", nativeDelay);
    vm.registerNativeFunction("millis", nativeMillis);
    vm.registerNativeFunction("pinMode", nativePinMode);
    vm.registerNativeFunction("digitalWrite", nativeDigitalWrite);
    vm.registerNativeFunction("digitalRead", nativeDigitalRead);
    vm.registerNativeFunction("analogWrite", nativeAnalogWrite);
    vm.registerNativeFunction("rgb_set", nativeRgbSet);
    vm.registerNativeFunction("fpioa_set_func", nativeFpioaSetFunc);
    vm.registerNativeFunction("Serial.print", nativeSerialPrint);
    vm.registerNativeFunction("Serial.println", nativeSerialPrintln);
    vm.registerNativeFunction("println", nativeSerialPrintln);
    vm.registerNativeFunction("print", nativeSerialPrint);
    vm.registerNativeFunction("dump_constants", nativeDumpConstants);

    if (!vm.loadModule(&module)) {
        std::cerr << "Error: Failed to load module: " << vm.getLastError() << std::endl;
        return 1;
    }

    std::cout << "[INFO] Functions: " << module.header.functionCount << std::endl;
    std::cout << "[INFO] Entry point: " << module.header.entryPointIndex << std::endl;

    uint32_t entryPoint = (module.header.entryPointIndex > 0) ? module.header.entryPointIndex : 0;
    std::cout << "[INFO] Executing entry point " << entryPoint << "..." << std::endl;
    std::cout << "================================" << std::endl;

    if (!vm.execute(entryPoint)) {
        std::cerr << "Error: Execution failed: " << vm.getLastError() << std::endl;
        return 1;
    }

    std::cout << "================================" << std::endl;

    cse::VMValue& ret = vm.getReturnValue();
    std::cout << "[DEBUG] Return value type: " << static_cast<int>(ret.type) << std::endl;
    if (ret.type == cse::ValueType::INTEGER) {
        std::cout << "[INFO] Return value: " << ret.value.intVal << std::endl;
    } else if (ret.type == cse::ValueType::DOUBLE) {
        std::cout << "[INFO] Return value: " << ret.value.doubleVal << std::endl;
    } else if (ret.type == cse::ValueType::NIL) {
        std::cout << "[INFO] Return value: NIL" << std::endl;
    } else {
        std::cout << "[INFO] Return value: (unknown type)" << std::endl;
    }

    std::cout << "[INFO] Execution completed" << std::endl;
    std::cout << "[INFO] Stack used: " << vm.getStackUsed() << " bytes" << std::endl;

    return 0;
}
