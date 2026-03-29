#ifndef CSE_ARCHITECTURE_H
#define CSE_ARCHITECTURE_H

#include <string>

namespace cse {

class Architecture {
public:
    enum class Type { X86, X64, RISCV64 };
    
    virtual ~Architecture() = default;
    
    virtual Type getType() const = 0;
    virtual size_t getRegisterSize() const = 0;
    virtual size_t getStackAlignment() const = 0;
    virtual size_t getPointerSize() const = 0;
    virtual std::string getRegisterName(int index) const = 0;
    virtual std::string getFloatRegisterName(int index) const = 0;
};

class X86Architecture : public Architecture {
public:
    Type getType() const override { return Type::X86; }
    size_t getRegisterSize() const override { return 4; }
    size_t getStackAlignment() const override { return 4; }
    size_t getPointerSize() const override { return 4; }
    std::string getRegisterName(int index) const override;
    std::string getFloatRegisterName(int index) const override;
};

class X64Architecture : public Architecture {
public:
    Type getType() const override { return Type::X64; }
    size_t getRegisterSize() const override { return 8; }
    size_t getStackAlignment() const override { return 16; }
    size_t getPointerSize() const override { return 8; }
    std::string getRegisterName(int index) const override;
    std::string getFloatRegisterName(int index) const override;
};

class RISCV64Architecture : public Architecture {
public:
    Type getType() const override { return Type::RISCV64; }
    size_t getRegisterSize() const override { return 8; }
    size_t getStackAlignment() const override { return 16; }
    size_t getPointerSize() const override { return 8; }
    std::string getRegisterName(int index) const override;
    std::string getFloatRegisterName(int index) const override;
};

} // namespace cse

#endif // CSE_ARCHITECTURE_H