#ifndef CSE_BASECODEGENERATOR_H
#define CSE_BASECODEGENERATOR_H

#include "ICodeGenerator.h"
#include "MemoryManager.h"
#include "Architecture.h"
#include "../frontend/parser/node.h"
#include <memory>
#include <map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace cse {

class BaseCodeGenerator : public MemoryManager, public ICodeGenerator {
public:
    BaseCodeGenerator(std::unique_ptr<Architecture> arch);
    virtual ~BaseCodeGenerator();
    
    // 实现通用方法
    size_t GetCodeSize() const override;
    const std::vector<unsigned char>& GetCodeBuffer() const;
    const std::vector<unsigned char>& GetDataBuffer() const;
    const std::map<size_t, std::string>& GetCallSites() const { return m_CallSites; }
    Type GetVariableType(const char* name) const override;
    void AllocateVariable(const char* name, Type type) override;
    int GetVariableOffset(const char* name) override;
    int GetVariableAbsoluteOffset(const char* name);
    bool GetConstantValue(const char* name, int& value) const;
    void SetConstantValue(const char* name, int value);
    void ClearConstantValue(const char* name);
    bool IsParamEvalVar(const char* name) const;
    void SetInFunction(bool inFunction) override;
    bool GetInFunction() const override;
    bool VariableExists(const char* name) const override;
    bool IsStandardLibraryFunction(const char* name) override;
    size_t StoreString(const char* str) override;
    size_t StoreDouble(double value) override;
    void AddCode(const std::vector<unsigned char>& code) override;
    void AddCode(std::initializer_list<unsigned char> code) override;
    void AddCode(char buff[]) override;
    
    // 平台抽象层相关方法
    void setPlatformAbstraction(PlatformAbstraction* platform) override;
    PlatformAbstraction* getPlatformAbstraction() const override;
    
    // 获取函数调用记录列表
    const std::vector<FunctionCallSite>& getFunctionCalls() const override;
    
    // 获取函数偏移表
    const std::map<std::string, size_t>& getFunctionOffsets() const { return m_Functions; }
    
    // 纯虚函数，由子类实现
    virtual Value* Create(BinaryOps instr, Value* lhs, Value* rhs, std::string str) = 0;
    virtual Value* CreateDoubleBinaryOp(BinaryOps instr, Value* lhs, Value* rhs, std::string str) = 0;
    virtual Value* Create(UnaryOps instr, Value* operand, std::string str) = 0;
    virtual void Create(ControlFlowOps instr, const char* label) = 0;
    virtual void Create(ControlFlowOps instr) = 0;
    virtual void CreateLabel(const char* label) = 0;
    virtual void StoreVariable(const char* name, Value* value, Type type = Int) = 0;
    virtual Value* LoadVariable(const char* name, Type type = Int) = 0;
    virtual Value* CreateArrayAccess(const char* name, Value* index) = 0;
    virtual void formatCode() = 0;
    virtual void DisassembleCode() const = 0;
    virtual void generateCodeFromIR(const std::list<Quad>& quadList) = 0;
    
    // 异常处理相关方法
    virtual void generateCodeForTryCatch(NBlock* tryBlock, const std::vector<NCatchBlock*>& catchBlocks) = 0;
    virtual void generateCodeForThrow(NExpression* expression) = 0;
    
protected:
    std::unique_ptr<Architecture> m_Architecture;
    std::map<std::string, size_t> m_FunctionLocalVariableSizes; // 存储每个函数的局部变量大小
    std::map<std::string, bool> m_FunctionHasReturn; // 存储每个函数是否有RET操作
    std::string m_CurrentFunction; // 当前函数名
    std::vector<unsigned char> m_CodeBuffer;
    std::vector<unsigned char> m_DataBuffer;
    std::map<std::string, size_t> m_Labels;
    std::map<std::string, size_t> m_Functions;
    std::map<size_t, std::string> m_JumpSites;
    std::map<std::string, int> m_VariableOffsets;
    std::map<std::string, size_t> m_GlobalVariableOffsets;
    std::map<std::string, Type> m_VariableTypes;
    std::map<size_t, std::string> m_CallSites;
    std::map<std::string, int> m_StructOffsets; // 记录结构体变量的偏移
    int m_NextOffset;
    size_t m_NextDataOffset;
    bool m_InFunction;
    int m_ParamIndex;
#ifdef _WIN32
    HMODULE m_MsvcrtDll;
#else
    void* m_MsvcrtDll;
#endif
    int m_LocalVariableSize; // 局部变量总大小
    int m_ParamEvalBase;     // 参数求值区域基址（固定分配）
    int m_ParamEvalOffset;   // 参数求值区域当前偏移
    std::map<std::string, int> m_ConstantValues; // 追踪常量变量的值

    // 平台抽象层
    PlatformAbstraction* m_Platform = nullptr;
    
    // 函数调用记录列表
    std::vector<FunctionCallSite> m_FunctionCalls;
    
#ifdef _WIN32
    HMODULE GetMsvcrt();
#else
    void* GetMsvcrt();
#endif
    static std::string typeToString(Type type);
};

} // namespace cse

#endif // CSE_BASECODEGENERATOR_H