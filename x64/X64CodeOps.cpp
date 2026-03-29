#include "X64Code.h"
#include <iostream>
#include <cctype>

namespace cse
{

    void X64Code::handleAddOperation(const Quad& quad)
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
            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, 0, Double);
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x0D);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, 1, Double);
            }

            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x58);
            m_CodeBuffer.push_back(0xC1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                storeRegisterToVariable(0, result, Double);
            }
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();
            
            if (reg1 == -1) reg1 = 0;
            if (reg2 == -1) reg2 = 3;

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x01);
            m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void X64Code::handleSubOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        if (arg1.empty() && !arg2.empty())
        {
            bool isFloat = false;
            if (arg2.find('.') != std::string::npos ||
                (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
            {
                isFloat = true;
            }

            if (isFloat)
            {
                if (arg2.find('.') != std::string::npos)
                {
                    double value = std::stod(arg2);
                    size_t dataOffset = StoreDouble(value);
                    size_t instrPos = m_CodeBuffer.size();
                    m_CodeBuffer.push_back(0xF2);
                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0x10);
                    m_CodeBuffer.push_back(0x05);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    AddRipRelativeOffset(instrPos, dataOffset, 8);
                }
                else if (VariableExists(arg2.c_str()))
                {
                    loadVariableToRegister(arg2, 0, Double);
                }

                size_t signMaskOffset = StoreDouble(-0.0);
                size_t signInstrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0x66);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x57);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(signInstrPos, signMaskOffset, 8);

                if (!result.empty())
                {
                    AllocateVariable(result.c_str(), Double);
                    storeRegisterToVariable(0, result, Double);
                }
            }
            else
            {
                int reg1 = allocateRegister();
                if (reg1 == -1) reg1 = 0;

                if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
                {
                    int value = std::stoi(arg2);
                    loadIntegerToRegister(value, reg1);
                }
                else if (VariableExists(arg2.c_str()))
                {
                    loadVariableToRegister(arg2, reg1, Int);
                }

                m_CodeBuffer.push_back(0x48);
                m_CodeBuffer.push_back(0xF7);
                m_CodeBuffer.push_back(0xD8 + reg1);

                if (!result.empty())
                {
                    AllocateVariable(result.c_str(), Int);
                    storeRegisterToVariable(reg1, result, Int);
                }

                freeRegister(reg1);
            }
            return;
        }

        bool isFloat = false;
        if (arg1.find('.') != std::string::npos || arg2.find('.') != std::string::npos ||
            (VariableExists(arg1.c_str()) && GetVariableType(arg1.c_str()) == Double) ||
            (VariableExists(arg2.c_str()) && GetVariableType(arg2.c_str()) == Double))
        {
            isFloat = true;
        }

        if (isFloat)
        {
            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, 0, Double);
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x0D);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, 1, Double);
            }

            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x5C);
            m_CodeBuffer.push_back(0xC1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                storeRegisterToVariable(0, result, Double);
            }
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();
            
            if (reg1 == -1) reg1 = 0;
            if (reg2 == -1) reg2 = 3;

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x29);
            m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void X64Code::handleMulOperation(const Quad& quad)
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
            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, 0, Double);
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x0D);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, 1, Double);
            }

            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x59);
            m_CodeBuffer.push_back(0xC1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                storeRegisterToVariable(0, result, Double);
            }
        }
        else
        {
            int reg1 = allocateRegister();
            int reg2 = allocateRegister();
            
            if (reg1 == -1) reg1 = 0;
            if (reg2 == -1) reg2 = 3;

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0xAF);
            m_CodeBuffer.push_back(0xC0 + (reg1 << 3) + reg2);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            freeRegister(reg1);
            freeRegister(reg2);
        }
    }

    void X64Code::handleDivOperation(const Quad& quad)
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
            if (arg1.find('.') != std::string::npos)
            {
                double value = std::stod(arg1);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x05);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, 0, Double);
            }

            if (arg2.find('.') != std::string::npos)
            {
                double value = std::stod(arg2);
                size_t dataOffset = StoreDouble(value);
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x0D);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, dataOffset, 8);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, 1, Double);
            }

            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x5E);
            m_CodeBuffer.push_back(0xC1);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Double);
                storeRegisterToVariable(0, result, Double);
            }
        }
        else
        {
            int reg1 = 0;
            int reg2 = 3;

            m_CodeBuffer.push_back(0x53);

            m_RegisterUsage[reg1] = true;
            m_RegisterUsage[reg2] = true;

            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg1);
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                loadVariableToRegister(arg1, reg1, Int);
            }

            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
            {
                int value = std::stoi(arg2);
                loadIntegerToRegister(value, reg2);
            }
            else if (VariableExists(arg2.c_str()))
            {
                loadVariableToRegister(arg2, reg2, Int);
            }

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x99);

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0xF7);
            m_CodeBuffer.push_back(0xFB);

            if (!result.empty())
            {
                AllocateVariable(result.c_str(), Int);
                storeRegisterToVariable(reg1, result, Int);
            }

            m_CodeBuffer.push_back(0x5B);

            m_RegisterUsage[reg1] = false;
            m_RegisterUsage[reg2] = false;
        }
    }

    void X64Code::handleModOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        m_RegisterUsage[0] = true;
        m_RegisterUsage[2] = true;

        int divisorReg = allocateRegister();
        
        if (divisorReg == -1 || divisorReg == 0 || divisorReg == 2) divisorReg = 3;

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2);
            loadIntegerToRegister(value, divisorReg);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, divisorReg, Int);
        }

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, 0);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, 0, Int);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x83);
        m_CodeBuffer.push_back(0xF8 + divisorReg);
        m_CodeBuffer.push_back(0x00);

        m_CodeBuffer.push_back(0x0F);
        m_CodeBuffer.push_back(0x84);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x99);

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0xF7);
        m_CodeBuffer.push_back(0xF0 + divisorReg);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(2, result, Int);
        }

        freeRegister(divisorReg);
        m_RegisterUsage[0] = false;
        m_RegisterUsage[2] = false;
    }

    void X64Code::handleAndOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x21);
        m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void X64Code::handleOrOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x09);
        m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void X64Code::handleNotOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        std::cout << "Handling NOT operation: arg1=" << arg1 << ", arg2=" << arg2 << ", result=" << result << std::endl;

        int reg1 = 0;
        std::cout << "Using register: " << reg1 << std::endl;

        if (arg2.empty() == false)
        {
            std::cout << "Using arg2 as operand: " << arg2 << std::endl;
            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
            {
                int value = std::stoi(arg2);
                std::cout << "Loading integer value: " << value << " into register " << reg1 << std::endl;
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg2.c_str()))
            {
                std::cout << "Loading variable: " << arg2 << " into register " << reg1 << std::endl;
                loadVariableToRegister(arg2, reg1, Int);
            }
        }
        else
        {
            std::cout << "Using arg1 as operand: " << arg1 << std::endl;
            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
            {
                int value = std::stoi(arg1);
                std::cout << "Loading integer value: " << value << " into register " << reg1 << std::endl;
                loadIntegerToRegister(value, reg1);
            }
            else if (VariableExists(arg1.c_str()))
            {
                std::cout << "Loading variable: " << arg1 << " into register " << reg1 << std::endl;
                loadVariableToRegister(arg1, reg1, Int);
            }
        }

        std::cout << "Generating NOT instruction for register " << reg1 << std::endl;
        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0xF7);
        m_CodeBuffer.push_back(0xD0);

        if (result.empty() == false)
        {
            std::cout << "Storing result into variable: " << result << std::endl;
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        std::cout << "NOT operation handling completed" << std::endl;
    }

    void X64Code::handleXorOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2);
            loadIntegerToRegister(value, reg2);
        }
        else if (VariableExists(arg2.c_str()))
        {
            loadVariableToRegister(arg2, reg2, Int);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x31);
        m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
        freeRegister(reg2);
    }

    void X64Code::handleShiftLeftOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2) & 0x3F;
            m_CodeBuffer.push_back(0xB1);
            m_CodeBuffer.push_back(static_cast<unsigned char>(value));
        }
        else if (VariableExists(arg2.c_str()))
        {
            int reg2 = allocateRegister();
            loadVariableToRegister(arg2, reg2, Int);
            m_CodeBuffer.push_back(0x8A);
            m_CodeBuffer.push_back(0xC8 + reg2);
            freeRegister(reg2);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0xD3);
        m_CodeBuffer.push_back(0xE0 + reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
    }

    void X64Code::handleShiftRightOperation(const Quad& quad)
    {
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        int reg1 = allocateRegister();

        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
        {
            int value = std::stoi(arg1);
            loadIntegerToRegister(value, reg1);
        }
        else if (VariableExists(arg1.c_str()))
        {
            loadVariableToRegister(arg1, reg1, Int);
        }

        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
        {
            int value = std::stoi(arg2) & 0x3F;
            m_CodeBuffer.push_back(0xB1);
            m_CodeBuffer.push_back(static_cast<unsigned char>(value));
        }
        else if (VariableExists(arg2.c_str()))
        {
            int reg2 = allocateRegister();
            loadVariableToRegister(arg2, reg2, Int);
            m_CodeBuffer.push_back(0x8A);
            m_CodeBuffer.push_back(0xC8 + reg2);
            freeRegister(reg2);
        }

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0xD3);
        m_CodeBuffer.push_back(0xF8 + reg1);

        if (!result.empty())
        {
            AllocateVariable(result.c_str(), Int);
            storeRegisterToVariable(reg1, result, Int);
        }

        freeRegister(reg1);
    }

    void X64Code::handleSwitchOperation(const Quad& quad)
    {
        std::string condition = quad.getArg1();
        std::string defaultLabel = quad.getArg2();
        std::string endLabel = quad.getResult();

        if (isdigit(condition[0]) || (condition[0] == '-' && isdigit(condition[1])))
        {
            int value = std::stoi(condition);
            loadIntegerToRegister(value, 0);
        }
        else if (VariableExists(condition.c_str()))
        {
            loadVariableToRegister(condition, 0, Int);
        }

        m_CodeBuffer.push_back(0xE9);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_JumpSites[m_CodeBuffer.size() - 5] = defaultLabel;
    }

    void X64Code::handleCaseOperation(const Quad& quad)
    {
        std::string value = quad.getArg1();
        std::string caseLabel = quad.getResult();

        CreateLabel(caseLabel.c_str());
    }

    void X64Code::handleDefaultOperation(const Quad& quad)
    {
        std::string defaultLabel = quad.getResult();

        CreateLabel(defaultLabel.c_str());
    }

} // namespace cse
