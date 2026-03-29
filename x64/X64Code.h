#ifndef CSE_X64CODE_H
#define CSE_X64CODE_H

#include "../BaseCodeGenerator.h"
#include "../../platform/PlatformAbstraction.h"
#include "../../platform/StandardLibrary.h"
#include "../ScriptFunctionRegistry.h"

namespace cse {

class Value;

class X64Code : public BaseCodeGenerator {
public:
    X64Code();
    ~X64Code();

    Value* Create(BinaryOps instr, Value* lhs, Value* rhs, std::string str) override;
    Value* CreateDoubleBinaryOp(BinaryOps instr, Value* lhs, Value* rhs, std::string str) override;
    Value* Create(UnaryOps instr, Value* operand, std::string str) override;
    void Create(ControlFlowOps instr, const char* label) override;
    void Create(ControlFlowOps instr) override;
    void CreateLabel(const char* label) override;
    void StoreVariable(const char* name, Value* value, Type type = Int) override;
    Value* LoadVariable(const char* name, Type type = Int) override;
    Value* CreateArrayAccess(const char* name, Value* index) override;
    void formatCode() override;
    void fixJumpOffsets();
    void fixCallOffsets();
    void fixJumpOffsets(size_t codeSize, size_t dataOffset);
    void fixCallOffsets(size_t codeSize, size_t dataOffset);
    void fixJumpOffsetsWithoutDataAdjustment();
    void fixCallOffsetsWithoutDataAdjustment();
    void fixRipRelativeOffsets();
    void CallStandardLibraryFunction(const char* name);
    void AddRipRelativeOffset(size_t instrPos, size_t dataOffset, size_t instrLength = 7);
    void updateFunctionCallOffsets();
    
    void setPlatformAbstraction(PlatformAbstraction* platform) override { BaseCodeGenerator::setPlatformAbstraction(platform); }
    PlatformAbstraction* getPlatformAbstraction() const override { return BaseCodeGenerator::getPlatformAbstraction(); }
    bool IsStandardLibraryFunction(const char* name) const;
    
    const std::vector<FunctionCallSite>& getFunctionCalls() const override { return BaseCodeGenerator::getFunctionCalls(); }
    void DisassembleCode() const override;
    void generateCodeFromIR(const std::list<Quad>& quadList) override;
    void generateFunctionEpilogue();
    
    // 异常处理相关方法
    void generateCodeForTryCatch(NBlock* tryBlock, const std::vector<NCatchBlock*>& catchBlocks) override;
    void generateCodeForThrow(NExpression* expression) override;

private:
    struct RipOffsetInfo {
        size_t instrPos;
        size_t dataOffset;
        size_t instrLength;
    };
    std::vector<RipOffsetInfo> m_RipRelativeOffsets;
    std::vector<bool> m_RegisterUsage;
    std::map<std::string, size_t> m_StackAllocPositions;
    std::map<std::string, std::vector<size_t>> m_FunctionEpiloguePositions;
    int m_StackArgCount = 0;
    int m_XmmRegCount = 0;
    
    // Entry code 相关信息，在 formatCode() 中处理
    std::vector<unsigned char> m_EntryCode;
    size_t m_EntryCodeInsertPos = 0;
    size_t m_MainPos = 0;
    
    struct ArrayInfo {
        std::string name;
        int size;
        int offset;
        int elementsOffset;
        std::string elementType;
        int elementSize;
    };
    std::map<std::string, std::vector<ArrayInfo>> m_FunctionArrays;
    std::unordered_map<std::string, void*> m_RegisteredCallbacks;
    
    int allocateRegister();
    void freeRegister(int reg);
    
    void handleAddOperation(const Quad& quad);
    void handleSubOperation(const Quad& quad);
    void handleMulOperation(const Quad& quad);
    void handleDivOperation(const Quad& quad);
    void handleModOperation(const Quad& quad);
    void handleAndOperation(const Quad& quad);
    void handleOrOperation(const Quad& quad);
    void handleNotOperation(const Quad& quad);
    void handleXorOperation(const Quad& quad);
    void handleShiftLeftOperation(const Quad& quad);
    void handleShiftRightOperation(const Quad& quad);
    void handleSwitchOperation(const Quad& quad);
    void handleCaseOperation(const Quad& quad);
    void handleDefaultOperation(const Quad& quad);
    
    template<typename T>
    void loadIntegerToRegister(T value, int reg);
    void loadVariableToRegister(const std::string& varName, int reg, Type type);
    void storeRegisterToVariable(int reg, const std::string& varName, Type type);
    
    bool performConstantFolding(Quad& quad);
    std::list<Quad> performDeadCodeElimination(const std::list<Quad>& quadList);
    
    std::string disassembleInstruction(size_t& pos) const;
    size_t getInstructionLength(size_t pos) const;
    uint32_t readImm32(size_t pos) const;
    uint64_t readImm64(size_t pos) const;
    std::string toHex(uint8_t value) const;
    std::string toHex32(uint32_t value) const;
    std::string toHex64(uint64_t value) const;
    std::string formatOffset(int8_t offset) const;
};

} // namespace cse

#endif // CSE_X64CODE_H
