#include "RV64Code.h"
#include "backend/Architecture.h"
#include "ir/Quad.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <set>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <map>

namespace cse
{

// 兼容的stoi函数
static int stoi_compat(const std::string& str) {
    return atoi(str.c_str());
}

// 兼容的to_string函数
static std::string to_string_compat(int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    return std::string(buffer);
}


    static std::string typeToString(RV64Code::Type type)
    {
        switch (type)
        {
        case RV64Code::Int:
            return "Int";
        case RV64Code::Double:
            return "Double";
        case RV64Code::Char:
            return "Char";
        case RV64Code::Bool:
            return "Bool";
        case RV64Code::String:
            return "String";
        default:
            return "Unknown";
        }
    }

    RV64Code::RV64Code() : BaseCodeGenerator(std::make_unique<RISCV64Architecture>())
    {
        m_RegisterUsage.resize(32, false);
        // 保留 x0（零寄存器）、x2（sp）、x3（gp）、x4（tp）
        m_RegisterUsage[0] = true;
        m_RegisterUsage[2] = true;
        m_RegisterUsage[3] = true;
        m_RegisterUsage[4] = true;
        m_OptimizedForK210 = false;
    }

    void RV64Code::optimizeForK210()
    {
        m_OptimizedForK210 = true;
        std::cout << "Optimized code generator for K210 platform" << std::endl;
    }

    RV64Code::~RV64Code()
    {
    }

    int RV64Code::allocateRegister()
    {
        // 从 x5 开始分配，跳过保留寄存器
        for (int i = 5; i < m_RegisterUsage.size(); i++)
        {
            if (!m_RegisterUsage[i])
            {
                m_RegisterUsage[i] = true;
                return i;
            }
        }
        std::cerr << "Warning: All registers are in use, returning x5" << std::endl;
        return 5;
    }

    void RV64Code::freeRegister(int reg)
    {
        if (reg >= 5 && reg < m_RegisterUsage.size())
        {
            m_RegisterUsage[reg] = false;
        }
    }

    template <typename T>
    void RV64Code::loadIntegerToRegister(T value, int reg)
    {
        if (value == 0)
        {
            // 使用 x0 寄存器进行零值加载
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
        }
        else if (value >= -2048 && value < 2048)
        {
            // 使用 lui + addi 或直接 addi
            if (value < 0)
            {
                value += 4096;
            }
            // addi rd, x0, imm
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(value & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((value >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x13);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg);
        }
        else
        {
            // 使用 lui + addi
            uint32_t upper = (static_cast<uint32_t>(value) >> 12) & 0xFFFFF;
            uint32_t lower = static_cast<uint32_t>(value) & 0xFFF;
            
            // lui rd, upper
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x37);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg);
            
            // addi rd, rd, lower
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x13);
            m_CodeBuffer.push_back(reg);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg);
        }
    }

    void RV64Code::loadVariableToRegister(const std::string &varName, int reg, Type type)
    {
        if (!VariableExists(varName.c_str()))
        {
            std::cerr << "Error: Variable " << varName << " does not exist" << std::endl;
            loadIntegerToRegister(0, reg);
            return;
        }

        // 检查是否是全局变量
        if (m_GlobalVariableOffsets.find(varName) != m_GlobalVariableOffsets.end()) {
            // 全局变量，从数据段加载
            size_t globalOffset = m_GlobalVariableOffsets[varName];
            // 使用 lui + lw/lb/ld 加载
            uint32_t upper = (static_cast<uint32_t>(globalOffset) >> 12) & 0xFFFFF;
            uint32_t lower = static_cast<uint32_t>(globalOffset) & 0xFFF;
            
            // lui t0, upper
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x37);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(5); // t0
            
            // ld rd, lower(t0)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(5); // t0
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg);
        } else {
            // 局部变量，从栈上加载
            int offset = GetVariableOffset(varName.c_str());
            // ld rd, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg);
        }
    }

    void RV64Code::storeRegisterToVariable(int reg, const std::string &varName, Type type)
    {
        if (!VariableExists(varName.c_str()))
        {
            std::cerr << "Error: Variable " << varName << " does not exist" << std::endl;
            AllocateVariable(varName.c_str(), type);
        }

        // 检查是否是全局变量
        if (m_GlobalVariableOffsets.find(varName) != m_GlobalVariableOffsets.end()) {
            // 全局变量，存储到数据段
            size_t globalOffset = m_GlobalVariableOffsets[varName];
            // 使用 lui + sd/sw/sb 存储
            uint32_t upper = (static_cast<uint32_t>(globalOffset) >> 12) & 0xFFFFF;
            uint32_t lower = static_cast<uint32_t>(globalOffset) & 0xFFF;
            
            // lui t0, upper
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x37);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(5); // t0
            
            // sd rd, lower(t0)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(5); // t0
            m_CodeBuffer.push_back(reg);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
        } else {
            // 局部变量，存储到栈上
            int offset = GetVariableOffset(varName.c_str());
            // sd rd, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(reg);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
        }
    }

    void RV64Code::handleAddOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        bool isFloat = false;
        if (arg1.find('.') != std::string::npos || arg2.find('.') != std::string::npos ||
            (VariableExists(arg1.c_str()) && GetVariableType(arg1.c_str()) == Double) ||
            (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
        {
            isFloat = true;
        }

        if (isFloat)
        {
            // 浮点数加法
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft0, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }
            else if (VariableExists(arg1.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg1.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft1, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }
            else if (VariableExists(arg2.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg2.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }

            // fadd.d ft0, ft0, ft1
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x09);
            m_CodeBuffer.push_back(0x08);
            m_CodeBuffer.push_back(0x53);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                int offset = GetVariableOffset(result.c_str());
                // fsd ft0, offset(sp)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(8); // ft0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            // add reg1, reg1, reg2
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg2);
            m_CodeBuffer.push_back(reg1);
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void RV64Code::handleSubOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        bool isFloat = false;
        if (arg1.find('.') != std::string::npos || arg2.find('.') != std::string::npos ||
            (VariableExists(arg1.c_str()) && GetVariableType(arg1.c_str()) == Double) ||
            (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
        {
            isFloat = true;
        }

        if (isFloat)
        {
            // 浮点数减法
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft0, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }
            else if (VariableExists(arg1.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg1.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft1, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }
            else if (VariableExists(arg2.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg2.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }

            // fsub.d ft0, ft0, ft1
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x09);
            m_CodeBuffer.push_back(0x08);
            m_CodeBuffer.push_back(0x53);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x10);
            m_CodeBuffer.push_back(0x00);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                int offset = GetVariableOffset(result.c_str());
                // fsd ft0, offset(sp)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(8); // ft0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            // sub reg1, reg1, reg2
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg2);
            m_CodeBuffer.push_back(reg1);
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x40);
            m_CodeBuffer.push_back(reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void RV64Code::handleMulOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        bool isFloat = false;
        if (arg1.find('.') != std::string::npos || arg2.find('.') != std::string::npos ||
            (VariableExists(arg1.c_str()) && GetVariableType(arg1.c_str()) == Double) ||
            (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
        {
            isFloat = true;
        }

        if (isFloat)
        {
            // 浮点数乘法
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft0, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }
            else if (VariableExists(arg1.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg1.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft1, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }
            else if (VariableExists(arg2.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg2.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }

            // fmul.d ft0, ft0, ft1
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x09);
            m_CodeBuffer.push_back(0x08);
            m_CodeBuffer.push_back(0x53);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x20);
            m_CodeBuffer.push_back(0x00);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                int offset = GetVariableOffset(result.c_str());
                // fsd ft0, offset(sp)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(8); // ft0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            // mul reg1, reg1, reg2
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg2);
            m_CodeBuffer.push_back(reg1);
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x20);
            m_CodeBuffer.push_back(reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void RV64Code::handleDivOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        bool isFloat = false;
        if (arg1.find('.') != std::string::npos || arg2.find('.') != std::string::npos ||
            (VariableExists(arg1.c_str()) && GetVariableType(arg1.c_str()) == Double) ||
            (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
        {
            isFloat = true;
        }

        if (isFloat)
        {
            // 浮点数除法
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft0, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }
            else if (VariableExists(arg1.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg1.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(8); // ft0
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                // 加载浮点数
                uint32_t upper = (static_cast<uint32_t>(dataOffset) >> 12) & 0xFFFFF;
                uint32_t lower = static_cast<uint32_t>(dataOffset) & 0xFFF;
                
                // lui t0, upper
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(upper & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((upper >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(5); // t0
                
                // fld ft1, lower(t0)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(lower & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((lower >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(5); // t0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }
            else if (VariableExists(arg2.c_str()))
            {
                // 加载变量到浮点寄存器
                int offset = GetVariableOffset(arg2.c_str());
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(9); // ft1
            }

            // fdiv.d ft0, ft0, ft1
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x09);
            m_CodeBuffer.push_back(0x08);
            m_CodeBuffer.push_back(0x53);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x30);
            m_CodeBuffer.push_back(0x00);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                int offset = GetVariableOffset(result.c_str());
                // fsd ft0, offset(sp)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
                m_CodeBuffer.push_back(0x37);
                m_CodeBuffer.push_back(2); // sp
                m_CodeBuffer.push_back(8); // ft0
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            // div reg1, reg1, reg2
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(reg2);
            m_CodeBuffer.push_back(reg1);
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x30);
            m_CodeBuffer.push_back(reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void RV64Code::handleModOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // rem reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x38);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleAndOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // and reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x70);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleOrOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // or reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x60);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleNotOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();

        // For NOT operation, the correct operand might be in arg2
        if (!arg2.empty())
        {
            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
            {
                int value = stoi_compat(arg2);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg1, Int);
            }
        }
        else
        {
            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = stoi_compat(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }
        }

        // xori reg1, reg1, -1
        m_CodeBuffer.push_back(0xFF);
        m_CodeBuffer.push_back(0xFF);
        m_CodeBuffer.push_back(0x0F);
        m_CodeBuffer.push_back(0x13);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
    }

    void RV64Code::handleXorOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // xor reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x40);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleShiftLeftOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2) & 0x3F; // 位移量限制在0-63之间
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // sll reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x10);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleShiftRightOperation(const Quad &quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
        {
            int value = stoi_compat(arg2) & 0x3F; // 位移量限制在0-63之间
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        // sra reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x50);
        m_CodeBuffer.push_back(reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void RV64Code::handleSwitchOperation(const Quad &quad)
    {
        std::string condition = quad.getArg1();
        std::string defaultLabel = quad.getArg2();
        std::string endLabel = quad.getResult();

        // 加载switch表达式的值到寄存器
        int reg1 = allocateRegister();
        if (isdigit(condition[0]) || (condition[0] == '-' && isdigit(condition[1])))
        {
            int value = stoi_compat(condition);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(condition.c_str()))
        {
            loadVariableToRegister(condition, reg1, Int);
        }

        // 这里需要生成跳转到各个case的代码
        // 实际的case比较和跳转将在处理case语句时生成
        // 暂时跳转到default标签
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x6F);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_JumpSites[m_CodeBuffer.size() - 8] = defaultLabel;

        freeRegister(reg1);
    }

    void RV64Code::handleCaseOperation(const Quad &quad)
    {
        std::string value = quad.getArg1();
        std::string caseLabel = quad.getResult();

        // 创建case标签
        CreateLabel(caseLabel.c_str());

        // 这里不需要生成额外的代码，因为case标签已经被创建
        // 实际的比较和跳转逻辑在switch语句处理时生成
    }

    void RV64Code::handleDefaultOperation(const Quad &quad)
    {
        std::string defaultLabel = quad.getResult();

        // 创建default标签
        CreateLabel(defaultLabel.c_str());

        // 这里不需要生成额外的代码，因为default标签已经被创建
    }

    Value *RV64Code::Create(BinaryOps instr, Value *lhs, Value *rhs, std::string str)
    {
        return nullptr;
    }

    Value *RV64Code::CreateDoubleBinaryOp(BinaryOps instr, Value *lhs, Value *rhs, std::string str)
    {
        return nullptr;
    }

    Value *RV64Code::Create(UnaryOps instr, Value *operand, std::string str)
    {
        return nullptr;
    }

    void RV64Code::Create(ControlFlowOps instr, const char *label)
    {
        std::map<std::string, size_t>::iterator funcIt;
        switch (instr)
        {
        case Call:
            if (label)
            {
                // 函数调用
                funcIt = m_Functions.find(label);
                if (funcIt != m_Functions.end())
                {
                    // 调用函数
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x6F);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);

                    // 保存调用站点
                    m_CallSites[m_CodeBuffer.size() - 8] = label;
                }
                else
                {
                    // 处理外部函数调用（如 printf、puts 等）
                    std::cout << "External function call: " << label << std::endl;
                    // 对于外部函数，我们暂时不做处理，因为需要动态链接
                }
            }
            break;
        case Jmp:
            if (label)
            {
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x6F);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Je:
            if (label)
            {
                // beq x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Jne:
            if (label)
            {
                // bne x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x01);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Jl:
            if (label)
            {
                // blt x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x04);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Jle:
            if (label)
            {
                // ble x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x06);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Jg:
            if (label)
            {
                // bgt x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        case Jge:
            if (label)
            {
                // bge x0, x0, label (暂时使用x0作为比较寄存器)
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x07);
                m_CodeBuffer.push_back(0x63);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 8] = label;
            }
            break;
        default:
            break;
        }
    }

    void RV64Code::Create(ControlFlowOps instr)
    {
        switch (instr)
        {
        case Ret:
            // ret
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x80);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            break;
        default:
            break;
        }
    }

    void RV64Code::CreateLabel(const char *label)
    {
        m_Labels[label] = m_CodeBuffer.size();
        std::cout << "Created label " << label << " at offset " << m_CodeBuffer.size() << std::endl;
    }

    void RV64Code::StoreVariable(const char *name, Value *value, Type type)
    {
        int offset = GetVariableOffset(name);
        if (type == Double)
        {
            // fsd ft0, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x37);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(8); // ft0
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
        }
        else
        {
            // sd rax, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(1); // rax
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
        }
    }

    Value *RV64Code::LoadVariable(const char *name, Type type)
    {
        int offset = GetVariableOffset(name);
        if (type == Double)
        {
            // fld ft0, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x37);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(8); // ft0
        }
        else
        {
            // ld rax, offset(sp)
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0x7F));
            m_CodeBuffer.push_back(0x33);
            m_CodeBuffer.push_back(2); // sp
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(1); // rax
        }
        return nullptr;
    }

    Value *RV64Code::CreateArrayAccess(const char *name, Value *index)
    {
        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        int arrayOffset = GetVariableOffset(name);
        // ld reg1, arrayOffset(sp)
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(static_cast<unsigned char>(arrayOffset & 0xFF));
        m_CodeBuffer.push_back(static_cast<unsigned char>((arrayOffset >> 8) & 0x7F));
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(2); // sp
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg1);

        // slli reg2, index, 3 (假设每个元素8字节)
        m_CodeBuffer.push_back(0x03);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x13);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);

        // add reg1, reg1, reg2
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg2);
        m_CodeBuffer.push_back(reg1);
        m_CodeBuffer.push_back(0x33);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(reg1);

        freeRegister(reg1);
        freeRegister(reg2);

        return nullptr;
    }

    void RV64Code::formatCode()
    {
        // 保存代码段的大小，用于计算偏移量
        size_t codeSize = m_CodeBuffer.size();
        
        // 将数据段添加到代码缓冲区末尾
        m_CodeBuffer.reserve(m_CodeBuffer.size() + m_DataBuffer.size());
        m_CodeBuffer.insert(m_CodeBuffer.end(), m_DataBuffer.begin(), m_DataBuffer.end());
        
        // 修正跳转偏移量
        fixJumpOffsets();
        
        // 修正调用偏移量
        fixCallOffsets();
        
        // 更新函数调用偏移量
        updateFunctionCallOffsets();
        
        std::cout << "Formatted code size: " << m_CodeBuffer.size() << " bytes" << std::endl;
    }

    void RV64Code::fixJumpOffsets()
    {
        for (const auto &jumpSite : m_JumpSites)
        {
            size_t jumpPos = jumpSite.first;
            const std::string &label = jumpSite.second;

            auto labelIt = m_Labels.find(label);
            if (labelIt != m_Labels.end())
            {
                size_t labelPos = labelIt->second;
                // 计算偏移量
                int32_t offset = static_cast<int32_t>(labelPos - (jumpPos + 4));
                // 写入偏移量
                if (jumpPos + 1 < m_CodeBuffer.size())
                {
                    m_CodeBuffer[jumpPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                    m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>((offset >> 8) & 0x7F);
                    // 设置最高位为符号位
                    if (offset < 0)
                    {
                        m_CodeBuffer[jumpPos + 2] |= 0x80;
                    }
                }
            }
        }
    }

    void RV64Code::fixCallOffsets()
    {
        for (const auto &callSite : m_CallSites)
        {
            size_t callPos = callSite.first;
            const std::string &funcName = callSite.second;

            auto funcIt = m_Functions.find(funcName);
            if (funcIt != m_Functions.end())
            {
                size_t funcPos = funcIt->second;
                int32_t offset = static_cast<int32_t>(funcPos - (callPos + 4));
                // 写入偏移量
                if (callPos + 1 < m_CodeBuffer.size())
                {
                    m_CodeBuffer[callPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                    m_CodeBuffer[callPos + 2] = static_cast<unsigned char>((offset >> 8) & 0x7F);
                    // 设置最高位为符号位
                    if (offset < 0)
                    {
                        m_CodeBuffer[callPos + 2] |= 0x80;
                    }
                }
            }
        }
    }

    void RV64Code::CallStandardLibraryFunction(const char *name)
    {
        // 记录函数调用信息（临时偏移量，将在formatCode后更新）
        FunctionCallSite site;
        site.codeOffset = m_CodeBuffer.size();
        site.funcName = name;
        m_FunctionCalls.push_back(site);
        
        // 对于 RISC-V 64，我们需要生成函数调用指令
        // 这里我们使用间接调用的方式，通过 ra 寄存器保存函数地址
        // auipc ra, 0x00000
        // 格式：00000000000000000000 00001 0010111
        m_CodeBuffer.push_back(0x00); // 7-0 bits
        m_CodeBuffer.push_back(0x00); // 15-8 bits
        m_CodeBuffer.push_back(0x00); // 23-16 bits
        m_CodeBuffer.push_back(0x17); // 31-24 bits
        m_CodeBuffer.push_back(0x00); // 39-32 bits
        m_CodeBuffer.push_back(0x00); // 47-40 bits
        m_CodeBuffer.push_back(0x00); // 55-48 bits
        m_CodeBuffer.push_back(0x01); // 63-56 bits
        
        // jalr ra, 0(ra)
        // 格式：000000000000 00001 000 00001 1100111
        m_CodeBuffer.push_back(0x00); // 7-0 bits
        m_CodeBuffer.push_back(0x00); // 15-8 bits
        m_CodeBuffer.push_back(0x00); // 23-16 bits
        m_CodeBuffer.push_back(0x67); // 31-24 bits
        m_CodeBuffer.push_back(0x00); // 39-32 bits
        m_CodeBuffer.push_back(0x00); // 47-40 bits
        m_CodeBuffer.push_back(0x01); // 55-48 bits
        m_CodeBuffer.push_back(0x00); // 63-56 bits
    }
    
    void RV64Code::updateFunctionCallOffsets()
    {
        // 在formatCode之后更新函数调用记录的偏移量
        // 因为formatCode可能会添加数据段，改变代码的偏移量
        
        // 计算代码段大小（不包括数据段）
        size_t codeSize = m_CodeBuffer.size();
        if (!m_DataBuffer.empty()) {
            codeSize -= m_DataBuffer.size();
        }
        
        // K210平台不支持动态加载库，使用静态链接的方式
        // 这里不需要更新函数调用偏移量，因为我们使用的是静态链接
        for (auto& site : m_FunctionCalls) {
            if (site.codeOffset < m_CodeBuffer.size()) {
                // 在K210平台上，函数地址是静态的，不需要动态获取
                // 这里可以添加平台特定的处理逻辑
                std::cout << "Function call site: " << site.funcName << " at offset " << site.codeOffset << std::endl;
            }
        }
    }

    void RV64Code::DisassembleCode() const
    {
        std::cout << "Disassembling RV64 code..." << std::endl;
        size_t pos = 0;
        while (pos < m_CodeBuffer.size())
        {
            std::string instr = disassembleInstruction(const_cast<size_t &>(pos));
            std::cout << std::hex << pos << ": " << instr << std::endl;
        }
    }

    void RV64Code::generateCodeFromIR(const std::list<Quad> &quadList)
    {
        for (const Quad &quad : quadList)
        {
            OpEnum opCode = quad.getOp();
            switch (opCode)
            {
            case ADD:
                handleAddOperation(quad);
                break;
            case SUB:
                handleSubOperation(quad);
                break;
            case MUL:
                handleMulOperation(quad);
                break;
            case DIV:
                handleDivOperation(quad);
                break;
            case MOD:
                handleModOperation(quad);
                break;
            case AND:
                handleAndOperation(quad);
                break;
            case OR:
                handleOrOperation(quad);
                break;
            case NOT:
                handleNotOperation(quad);
                break;
            case XOR:
                handleXorOperation(quad);
                break;
            case LSHIFT:
                handleShiftLeftOperation(quad);
                break;
            case RSHIFT:
                handleShiftRightOperation(quad);
                break;
            case SWITCH:
                handleSwitchOperation(quad);
                break;
            case CASE:
                handleCaseOperation(quad);
                break;
            case DEFAULT:
                handleDefaultOperation(quad);
                break;
            case ASSIGN:
                {
                    std::string arg1 = quad.getArg1();
                    std::string result = quad.getResult();
                    
                    // 加载 arg1 到寄存器
                    int reg = allocateRegister();
                    if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                    {
                        int value = stoi_compat(arg1);
                        loadIntegerToRegister(value, reg);
                    }
                    else if (VariableExists(arg1.c_str()))
                    {
                        loadVariableToRegister(arg1, reg, Int);
                    }
                    
                    // 存储到变量
                    AllocateVariable(result.c_str(), Int);
                    storeRegisterToVariable(reg, result, Int);
                    
                    freeRegister(reg);
                }
                break;
            case RETURN:
                {
                    std::string arg1 = quad.getArg1();
                    
                    // 加载返回值到 rax 寄存器
                    if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                    {
                        int value = stoi_compat(arg1);
                        loadIntegerToRegister(value, 1); // rax
                    }
                    else if (VariableExists(arg1.c_str()))
                    {
                        loadVariableToRegister(arg1, 1, Int); // rax
                    }
                    
                    // 生成函数结语
                    generateFunctionEpilogue();
                }
                break;
            default:
                break;
            }
        }

        // 修复跳转偏移量
        fixJumpOffsets();
        fixCallOffsets();
    }

    void RV64Code::generateFunctionEpilogue()
    {
        // 生成函数结语
        // 恢复栈指针
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x13);
        m_CodeBuffer.push_back(2); // sp
        m_CodeBuffer.push_back(2); // sp
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(2); // sp
        
        // ret
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x80);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
    }

    bool RV64Code::performConstantFolding(Quad &quad)
    {
        // 常量折叠优化
        return false;
    }

    std::list<Quad> RV64Code::performDeadCodeElimination(const std::list<Quad> &quadList)
    {
        // 死代码消除优化
        return quadList;
    }

    std::string RV64Code::disassembleInstruction(size_t &pos) const
    {
        // 简单的指令反汇编
        if (pos >= m_CodeBuffer.size())
            return "<invalid>";

        uint8_t opcode = m_CodeBuffer[pos];
        pos++;
        return "<instruction>";
    }

    size_t RV64Code::getInstructionLength(size_t pos) const
    {
        // 获取指令长度
        return 4;
    }

    uint32_t RV64Code::readImm32(size_t pos) const
    {
        // 读取32位立即数
        return 0;
    }

    uint64_t RV64Code::readImm64(size_t pos) const
    {
        // 读取64位立即数
        return 0;
    }

    std::string RV64Code::toHex(uint8_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
        return ss.str();
    }

    std::string RV64Code::toHex32(uint32_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << value;
        return ss.str();
    }

    std::string RV64Code::toHex64(uint64_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << value;
        return ss.str();
    }

    std::string RV64Code::formatOffset(int32_t offset) const
    {
        std::stringstream ss;
        ss << std::hex << offset;
        return ss.str();
    }

    // 异常处理相关方法
    void RV64Code::generateCodeForTryCatch(NBlock* tryBlock, const std::vector<NCatchBlock*>& catchBlocks)
    {
        // 简单实现，不做任何操作
    }

    void RV64Code::generateCodeForThrow(NExpression* expression)
    {
        // 简单实现，不做任何操作
    }

} // namespace cse