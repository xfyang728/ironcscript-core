#ifndef CSE_ICODEGENERATOR_H
#define CSE_ICODEGENERATOR_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include "../common/Value.h"
#include "../ir/Quad.h"
#include "../platform/PlatformAbstraction.h"

namespace cse {

class Value;

class ICodeGenerator {
public:
    enum BinaryOps { Add, Sub, Mul, SDiv, Eq, Ne, Lt, Le, Gt, Ge };
    enum UnaryOps { Neg, Not };
    enum ControlFlowOps { Jmp, Je, Jne, Jl, Jle, Jg, Jge, Call, Ret };
    enum Type { Int, Double, Char, Bool, String, Pointer };
    
    // 函数调用记录结构
    struct FunctionCallSite {
        size_t codeOffset;  // 代码中的位置
        std::string funcName; // 函数名
    };
    
    virtual ~ICodeGenerator() = default;
    
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
    
    virtual size_t GetCodeSize() const = 0;
    virtual const std::vector<unsigned char>& GetCodeBuffer() const = 0;
    virtual const std::vector<unsigned char>& GetDataBuffer() const = 0;
    virtual const std::map<size_t, std::string>& GetCallSites() const = 0;
    virtual Type GetVariableType(const char* name) const = 0;
    virtual void AllocateVariable(const char* name, Type type) = 0;
    virtual int GetVariableOffset(const char* name) = 0;
    virtual void SetInFunction(bool inFunction) = 0;
    virtual bool GetInFunction() const = 0;
    virtual bool VariableExists(const char* name) const = 0;
    virtual bool IsStandardLibraryFunction(const char* name) = 0;
    virtual size_t StoreString(const char* str) = 0;
    virtual size_t StoreDouble(double value) = 0;
    virtual void AddCode(const std::vector<unsigned char>& code) = 0;
    virtual void AddCode(std::initializer_list<unsigned char> code) = 0;
    virtual void AddCode(char buff[]) = 0;
    
    // 平台抽象层相关方法
    virtual void setPlatformAbstraction(PlatformAbstraction* platform) = 0;
    virtual PlatformAbstraction* getPlatformAbstraction() const = 0;
    
    // 获取函数调用记录列表
    virtual const std::vector<FunctionCallSite>& getFunctionCalls() const = 0;
};

} // namespace cse

#endif // CSE_ICODEGENERATOR_H