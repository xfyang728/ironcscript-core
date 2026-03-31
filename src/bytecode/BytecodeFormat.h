#ifndef CSE_BYTECODE_FORMAT_H
#define CSE_BYTECODE_FORMAT_H

#include <cstdint>
#include <string>
#include <vector>
#include <cstring>

namespace cse {

#pragma pack(push, 1)

#define CSB_MAGIC "CSB\x01"
#define CSB_VERSION_MAJOR 1
#define CSB_VERSION_MINOR 0

enum class OpCode : uint8_t {
    NOP = 0x00,
    LOAD_CONST,
    LOAD_VAR,
    STORE_VAR,
    PEEK_VAR,
    LOAD_GLOBAL,
    STORE_GLOBAL,

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    NEG,
    NOT,
    BITAND,
    BITOR,
    BITXOR,
    BITNOT,
    SHL,
    SHR,

    AND,
    OR,
    XOR,

    EQ,
    NEQ,
    LT,
    GT,
    LTE,
    GTE,

    JUMP,
    JUMP_IF_FALSE,
    JUMP_IF_TRUE,

    CALL,
    RETURN,
    HALT,

    LOAD_ARRAY,
    STORE_ARRAY,
    LOAD_MEMBER,
    STORE_MEMBER,

    MAKE_ARRAY,
    MAKE_OBJECT,

    PUSH_SCOPE,
    POP_SCOPE,

    PUSH,
    POP,

    YIELD,
    AWAIT,

    CALL_NATIVE,
};

enum class ValueType : uint8_t {
    NIL,
    INTEGER,
    DOUBLE,
    STRING,
    ARRAY,
    OBJECT,
    FUNCTION,
    NATIVE_FUNC,
};

struct VMValue {
    ValueType type;
    union {
        int64_t intVal;
        double doubleVal;
        uint32_t stringOffset;
        void* ptrVal;
    } value;

    VMValue() : type(ValueType::NIL), value({0}) {}

    static VMValue makeInt(int64_t v) {
        VMValue val;
        val.type = ValueType::INTEGER;
        val.value.intVal = v;
        return val;
    }

    static VMValue makeDouble(double v) {
        VMValue val;
        val.type = ValueType::DOUBLE;
        val.value.doubleVal = v;
        return val;
    }

    static VMValue makeString(uint32_t offset) {
        VMValue val;
        val.type = ValueType::STRING;
        val.value.stringOffset = offset;
        return val;
    }

    static VMValue makeNil() {
        return VMValue();
    }

    bool toBool() const {
        switch (type) {
            case ValueType::NIL: return false;
            case ValueType::INTEGER: return value.intVal != 0;
            case ValueType::DOUBLE: return value.doubleVal != 0.0;
            case ValueType::STRING: return value.stringOffset != 0;
            default: return true;
        }
    }

    int64_t toInt() const {
        switch (type) {
            case ValueType::INTEGER: return value.intVal;
            case ValueType::DOUBLE: return static_cast<int64_t>(value.doubleVal);
            case ValueType::STRING: return static_cast<int64_t>(value.stringOffset);
            default: return 0;
        }
    }

    double toDouble() const {
        switch (type) {
            case ValueType::INTEGER: return static_cast<double>(value.intVal);
            case ValueType::DOUBLE: return value.doubleVal;
            case ValueType::STRING: return static_cast<double>(value.stringOffset);
            default: return 0.0;
        }
    }
};

struct VMFrame {
    uint32_t functionIndex;
    uint32_t pc;
    uint32_t localBase;
    uint32_t localCount;
};

struct BytecodeInstruction {
    OpCode op;
    uint32_t operand;

    BytecodeInstruction() : op(OpCode::NOP), operand(0) {}
    BytecodeInstruction(OpCode o, uint32_t p = 0) : op(o), operand(p) {}
};

struct ConstantPoolEntry {
    enum class Type : uint8_t {
        INTEGER,
        DOUBLE,
        STRING,
        FUNCTION,
        NATIVE_FUNC,
    };

    Type type;
    union {
        int64_t intVal;
        double doubleVal;
        uint32_t stringOffset;
        uint32_t functionIndex;
        void* nativeFunc;
    } value;

    static ConstantPoolEntry makeInt(int64_t v) {
        ConstantPoolEntry e;
        e.type = Type::INTEGER;
        e.value.intVal = v;
        return e;
    }

    static ConstantPoolEntry makeDouble(double v) {
        ConstantPoolEntry e;
        e.type = Type::DOUBLE;
        e.value.doubleVal = v;
        return e;
    }

    static ConstantPoolEntry makeString(uint32_t offset) {
        ConstantPoolEntry e;
        e.type = Type::STRING;
        e.value.stringOffset = offset;
        return e;
    }

    static ConstantPoolEntry makeFunction(uint32_t index) {
        ConstantPoolEntry e;
        e.type = Type::FUNCTION;
        e.value.functionIndex = index;
        return e;
    }

    static ConstantPoolEntry makeNativeFunc(void* func) {
        ConstantPoolEntry e;
        e.type = Type::NATIVE_FUNC;
        e.value.nativeFunc = func;
        return e;
    }
};

struct BytecodeFunction {
    uint32_t nameOffset;
    uint32_t paramCount;
    uint32_t localCount;
    uint32_t maxStackSize;
    std::vector<BytecodeInstruction> instructions;
    std::vector<ConstantPoolEntry> constants;
};

struct BytecodeHeader {
    char magic[4];
    uint8_t majorVersion;
    uint8_t minorVersion;
    uint16_t flags;
    uint32_t functionCount;
    uint32_t stringPoolSize;
    uint32_t totalConstants;
    uint32_t entryPointIndex;

    BytecodeHeader() {
        magic[0] = 'C'; magic[1] = 'S'; magic[2] = 'B'; magic[3] = '\x01';
        majorVersion = CSB_VERSION_MAJOR;
        minorVersion = CSB_VERSION_MINOR;
        flags = 0;
        functionCount = 0;
        stringPoolSize = 0;
        totalConstants = 0;
        entryPointIndex = 0;
    }

    bool isValid() const {
        return magic[0] == 'C' && magic[1] == 'S' &&
               magic[2] == 'B' && magic[3] == '\x01';
    }
};

struct BytecodeModule {
    BytecodeHeader header;
    std::vector<BytecodeFunction> functions;
    std::vector<std::string> stringPool;
    std::vector<ConstantPoolEntry> globalConstants;

    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);
    bool validate() const;
};

#pragma pack(pop)

}
#endif
