#ifndef CSE_BYTECODE_COMPILER_H
#define CSE_BYTECODE_COMPILER_H

#include "ir/Quad.h"
#include "frontend/semantic/SymbolTable.h"
#include "bytecode/BytecodeFormat.h"
#include <map>
#include <vector>
#include <string>
#include <list>
#include <set>

namespace cse {

class BytecodeCompiler {
public:
    BytecodeCompiler();
    ~BytecodeCompiler();

    BytecodeModule* compile(const std::list<Quad>& quadList, SymbolTable& symbolTable);

    const std::string& getLastError() const { return m_LastError; }

private:
    void reset();
    uint32_t addString(const std::string& str);
    uint32_t addConstant(ConstantPoolEntry entry);
    uint32_t addFunction(const BytecodeFunction& func);

    void emit(OpCode op, uint32_t operand = 0);
    void emitJump(OpCode op, uint32_t target);
    void patchJump(uint32_t jumpPos, uint32_t target);

    uint32_t getStringOffset(const std::string& str);
    uint32_t getConstantIndex(const Quad& quad);
    uint32_t getVariableSlot(const std::string& name);
    bool tryAddConstant(const std::string& val);

    void compileQuad(const Quad& quad);
    void compileFunction(const Quad& funcQuad);

    std::list<Quad>::const_iterator findMatchingENDFUNC(
        std::list<Quad>::const_iterator funcIt,
        std::list<Quad>::const_iterator end);

    void compileFunctionBody(
        std::list<Quad>::const_iterator start,
        std::list<Quad>::const_iterator end);

    OpCode getBinaryOp(const std::string& op);
    OpCode getUnaryOp(const std::string& op);
    OpCode getComparisonOp(const std::string& op);

    std::string m_LastError;
    BytecodeModule* m_Module;

    std::map<std::string, uint32_t> m_StringToOffset;
    std::vector<BytecodeFunction*> m_Functions;
    BytecodeFunction* m_CurrentFunction;
    std::string m_CurrentFunctionName;
    std::map<std::string, uint32_t> m_FunctionIndices;

    uint32_t m_NextConstantIndex;
    uint32_t m_NextFunctionIndex;

    std::map<std::string, uint32_t> m_VariableToSlot;
    std::vector<std::string> m_LocalVariables;
    std::map<std::string, int64_t> m_ConstTempValues;
    std::set<std::string> m_StringTempVariables;
    std::string m_LastStoredTemp;
    SymbolTable* m_SymbolTable;
};

}

#endif
