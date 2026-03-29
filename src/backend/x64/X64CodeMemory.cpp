#include "X64Code.h"
#include <iostream>

namespace cse
{

    int X64Code::allocateRegister()
    {
        for (int i = 0; i < m_RegisterUsage.size(); i++)
        {
            if (i == 4 || i == 5) continue;
            
            if (!m_RegisterUsage[i])
            {
                m_RegisterUsage[i] = true;
                return i;
            }
        }
        std::cerr << "Warning: All registers are in use, returning rax" << std::endl;
        return 0;
    }

    void X64Code::freeRegister(int reg)
    {
        if (reg >= 0 && reg < m_RegisterUsage.size())
        {
            m_RegisterUsage[reg] = false;
        }
    }

    template <typename T>
    void X64Code::loadIntegerToRegister(T value, int reg)
    {
        if (reg >= 8)
        {
            m_CodeBuffer.push_back(0x49);
            m_CodeBuffer.push_back(0xB8 + (reg - 8));
        }
        else
        {
            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0xB8 + reg);
        }

        uint64_t uvalue = static_cast<uint64_t>(value);
        for (int i = 0; i < 8; i++)
        {
            m_CodeBuffer.push_back(static_cast<unsigned char>(uvalue & 0xFF));
            uvalue >>= 8;
        }
    }

    void X64Code::loadVariableToRegister(const std::string& varName, int reg, Type type)
    {
        if (!VariableExists(varName.c_str()))
        {
            std::cerr << "Error: Variable " << varName << " does not exist" << std::endl;
            loadIntegerToRegister(0, reg);
            return;
        }

        bool isArray = false;
        int arrayElementsOffset = 0;
        if (!m_CurrentFunction.empty() && m_FunctionArrays.find(m_CurrentFunction) != m_FunctionArrays.end()) {
            for (const auto& arrayInfo : m_FunctionArrays[m_CurrentFunction]) {
                if (arrayInfo.name == varName) {
                    isArray = true;
                    arrayElementsOffset = arrayInfo.elementsOffset;
                    break;
                }
            }
        }

        if (m_GlobalVariableOffsets.find(varName) != m_GlobalVariableOffsets.end()) {
            size_t globalOffset = m_GlobalVariableOffsets[varName];
            if (type == Double)
            {
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x10);
                m_CodeBuffer.push_back(0x05 + (reg << 3));
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, globalOffset, 8);
            }
            else
            {
                size_t instrPos = m_CodeBuffer.size();
                if (type == Pointer) {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x49);
                        m_CodeBuffer.push_back(0x8B);
                        m_CodeBuffer.push_back(0x05 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x8B);
                        m_CodeBuffer.push_back(0x05 + (reg << 3));
                    }
                } else {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x41);
                        m_CodeBuffer.push_back(0x8B);
                        m_CodeBuffer.push_back(0x05 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x8B);
                        m_CodeBuffer.push_back(0x05 + (reg << 3));
                    }
                }
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                size_t instrLen = (reg >= 8 || type == Pointer) ? 7 : 6;
                AddRipRelativeOffset(instrPos, globalOffset, instrLen);
            }
        } else {
            if (isArray) {
                int offset = -arrayElementsOffset;
                if (reg >= 8)
                {
                    m_CodeBuffer.push_back(0x4C);
                    m_CodeBuffer.push_back(0x8D);
                    m_CodeBuffer.push_back(0x85 + ((reg - 8) << 3));
                }
                else
                {
                    m_CodeBuffer.push_back(0x48);
                    m_CodeBuffer.push_back(0x8D);
                    m_CodeBuffer.push_back(0x85 + (reg << 3));
                }
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
            } else {
                int offset = GetVariableOffset(varName.c_str());
                if (type == Double)
                {
                    m_CodeBuffer.push_back(0xF2);
                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0x10);
                    m_CodeBuffer.push_back(0x85 + (reg << 3));
                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                }
                else
                {
                    if (type == Pointer) {
                        if (reg >= 8)
                        {
                            m_CodeBuffer.push_back(0x49);
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x85 + ((reg - 8) << 3));
                        }
                        else
                        {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x85 + (reg << 3));
                        }
                    } else {
                        if (reg >= 8)
                        {
                            m_CodeBuffer.push_back(0x41);
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x85 + ((reg - 8) << 3));
                        }
                        else
                        {
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x85 + (reg << 3));
                        }
                    }
                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                }
            }
        }
    }

    void X64Code::storeRegisterToVariable(int reg, const std::string& varName, Type type)
    {
        if (!VariableExists(varName.c_str()))
        {
            std::cerr << "Error: Variable " << varName << " does not exist" << std::endl;
            AllocateVariable(varName.c_str(), type);
        }

        if (m_GlobalVariableOffsets.find(varName) != m_GlobalVariableOffsets.end()) {
            size_t globalOffset = m_GlobalVariableOffsets[varName];
            if (type == Double)
            {
                size_t instrPos = m_CodeBuffer.size();
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x11);
                m_CodeBuffer.push_back(0x05 + (reg << 3));
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                AddRipRelativeOffset(instrPos, globalOffset, 8);
            }
            else
            {
                size_t instrPos = m_CodeBuffer.size();
                if (type == Pointer) {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x49);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x05 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x05 + (reg << 3));
                    }
                } else {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x41);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x05 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x05 + (reg << 3));
                    }
                }
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                size_t instrLen = (reg >= 8 || type == Pointer) ? 7 : 6;
                AddRipRelativeOffset(instrPos, globalOffset, instrLen);
            }
        } else {
            int offset = GetVariableOffset(varName.c_str());
            if (type == Double)
            {
                m_CodeBuffer.push_back(0xF2);
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x11);
                m_CodeBuffer.push_back(0x85 + (reg << 3));
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
            }
            else
            {
                if (type == Pointer) {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x49);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x85 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x85 + (reg << 3));
                    }
                } else {
                    if (reg >= 8)
                    {
                        m_CodeBuffer.push_back(0x41);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x85 + ((reg - 8) << 3));
                    }
                    else
                    {
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x85 + (reg << 3));
                    }
                }
                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
            }
        }
    }

    template void X64Code::loadIntegerToRegister<int>(int value, int reg);
    template void X64Code::loadIntegerToRegister<int64_t>(int64_t value, int reg);
    template void X64Code::loadIntegerToRegister<uint64_t>(uint64_t value, int reg);

} // namespace cse
