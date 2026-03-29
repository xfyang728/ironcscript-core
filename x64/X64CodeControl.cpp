#include "X64Code.h"
#include <iostream>

namespace cse
{

    Value* X64Code::Create(BinaryOps instr, Value* lhs, Value* rhs, std::string str)
    {
        return nullptr;
    }

    Value* X64Code::CreateDoubleBinaryOp(BinaryOps instr, Value* lhs, Value* rhs, std::string str)
    {
        return nullptr;
    }

    Value* X64Code::Create(UnaryOps instr, Value* operand, std::string str)
    {
        return nullptr;
    }

    void X64Code::Create(ControlFlowOps instr, const char* label)
    {
        std::map<std::string, size_t>::iterator funcIt;
        switch (instr)
        {
        case Call:
            if (label)
            {
                funcIt = m_Functions.find(label);
                if (funcIt != m_Functions.end())
                {
                    m_CodeBuffer.push_back(0xE8);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);

                    m_CallSites[m_CodeBuffer.size() - 4] = label;
                }
                else
                {
                    std::cout << "External function call: " << label << std::endl;
                }
            }
            break;
        case Jmp:
            if (label)
            {
                m_CodeBuffer.push_back(0xE9);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Je:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x84);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Jne:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x85);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Jl:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x8C);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Jle:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x8E);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Jg:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x8F);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        case Jge:
            if (label)
            {
                m_CodeBuffer.push_back(0x0F);
                m_CodeBuffer.push_back(0x8D);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_CodeBuffer.push_back(0x00);
                m_JumpSites[m_CodeBuffer.size() - 4] = label;
            }
            break;
        default:
            break;
        }
    }

    void X64Code::Create(ControlFlowOps instr)
    {
        switch (instr)
        {
        case Ret:
            m_CodeBuffer.push_back(0xC3);
            break;
        default:
            break;
        }
    }

    void X64Code::CreateLabel(const char* label)
    {
        m_Labels[label] = m_CodeBuffer.size();
        std::cout << "Created label " << label << " at offset " << m_CodeBuffer.size() << std::endl;
    }

    void X64Code::fixJumpOffsets()
    {
        for (const auto& jumpSite : m_JumpSites)
        {
            size_t jumpPos = jumpSite.first;
            const std::string& label = jumpSite.second;

            auto labelIt = m_Labels.find(label);
            if (labelIt != m_Labels.end())
            {
                size_t labelPos = labelIt->second;
                if (m_CodeBuffer[jumpPos] == 0xE9)
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 5));
                    if (jumpPos + 1 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
                else if (m_CodeBuffer[jumpPos] == 0x0F && (m_CodeBuffer[jumpPos + 1] == 0x84 || m_CodeBuffer[jumpPos + 1] == 0x85))
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 6));
                    if (jumpPos + 2 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 5] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
            }
        }
    }

    void X64Code::fixCallOffsets()
    {
        for (const auto& callSite : m_CallSites)
        {
            size_t callPos = callSite.first;
            const std::string& funcName = callSite.second;

            auto funcIt = m_Functions.find(funcName);
            if (funcIt != m_Functions.end())
            {
                size_t funcPos = funcIt->second;
                int offset = static_cast<int>(funcPos - (callPos + 5));

                if (callPos + 1 < m_CodeBuffer.size())
                {
                    m_CodeBuffer[callPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                    m_CodeBuffer[callPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                    m_CodeBuffer[callPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                    m_CodeBuffer[callPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                }
            }
        }
    }

    void X64Code::fixJumpOffsets(size_t codeSize, size_t dataOffset)
    {
        for (const auto& jumpSite : m_JumpSites)
        {
            size_t jumpPos = jumpSite.first;
            const std::string& label = jumpSite.second;

            auto labelIt = m_Labels.find(label);
            if (labelIt != m_Labels.end())
            {
                size_t labelPos = labelIt->second;
                if (labelPos >= codeSize) {
                    labelPos = labelPos + dataOffset;
                }

                if (m_CodeBuffer[jumpPos] == 0xE9)
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 5));
                    if (jumpPos + 1 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
                else if (m_CodeBuffer[jumpPos] == 0x0F && (m_CodeBuffer[jumpPos + 1] == 0x84 || m_CodeBuffer[jumpPos + 1] == 0x85))
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 6));
                    if (jumpPos + 2 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 5] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
            }
        }
    }

    void X64Code::fixCallOffsets(size_t codeSize, size_t dataOffset)
    {
        for (const auto& callSite : m_CallSites)
        {
            size_t callPos = callSite.first;
            const std::string& funcName = callSite.second;

            auto funcIt = m_Functions.find(funcName);
            if (funcIt != m_Functions.end())
            {
                size_t funcPos = funcIt->second;
                if (funcPos >= codeSize) {
                    funcPos = funcPos + dataOffset;
                }

                int offset = static_cast<int>(funcPos - (callPos + 5));

                if (callPos + 1 < m_CodeBuffer.size())
                {
                    m_CodeBuffer[callPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                    m_CodeBuffer[callPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                    m_CodeBuffer[callPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                    m_CodeBuffer[callPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                }
            }
        }
    }

    void X64Code::fixJumpOffsetsWithoutDataAdjustment()
    {
        for (const auto& jumpSite : m_JumpSites)
        {
            size_t jumpPos = jumpSite.first;
            const std::string& label = jumpSite.second;

            auto labelIt = m_Labels.find(label);
            if (labelIt != m_Labels.end())
            {
                size_t labelPos = labelIt->second;
                if (m_CodeBuffer[jumpPos] == 0xE9)
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 5));
                    if (jumpPos + 1 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
                else if (m_CodeBuffer[jumpPos] == 0x0F && (m_CodeBuffer[jumpPos + 1] == 0x84 || m_CodeBuffer[jumpPos + 1] == 0x85))
                {
                    int offset = static_cast<int>(labelPos - (jumpPos + 6));
                    if (jumpPos + 2 < m_CodeBuffer.size())
                    {
                        m_CodeBuffer[jumpPos + 2] = static_cast<unsigned char>(offset & 0xFF);
                        m_CodeBuffer[jumpPos + 3] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                        m_CodeBuffer[jumpPos + 4] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                        m_CodeBuffer[jumpPos + 5] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                    }
                }
            }
        }
    }

    void X64Code::fixCallOffsetsWithoutDataAdjustment()
    {
        for (const auto& callSite : m_CallSites)
        {
            size_t callPos = callSite.first;
            const std::string& funcName = callSite.second;

            auto funcIt = m_Functions.find(funcName);
            if (funcIt != m_Functions.end())
            {
                size_t funcPos = funcIt->second;
                int offset = static_cast<int>(funcPos - (callPos + 5));

                if (callPos + 1 < m_CodeBuffer.size())
                {
                    m_CodeBuffer[callPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                    m_CodeBuffer[callPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                    m_CodeBuffer[callPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                    m_CodeBuffer[callPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
                }
            }
        }
    }

    void X64Code::fixRipRelativeOffsets()
    {
        for (const auto& rip : m_RipRelativeOffsets)
        {
            size_t instrPos = rip.instrPos;
            size_t dataOffset = rip.dataOffset;
            size_t instrLength = rip.instrLength;
            int offset = static_cast<int>(dataOffset - (instrPos + instrLength));
            size_t offsetPos = instrPos + instrLength - 4;
            if (offsetPos + 4 <= m_CodeBuffer.size())
            {
                m_CodeBuffer[offsetPos] = static_cast<unsigned char>(offset & 0xFF);
                m_CodeBuffer[offsetPos + 1] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                m_CodeBuffer[offsetPos + 2] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                m_CodeBuffer[offsetPos + 3] = static_cast<unsigned char>((offset >> 24) & 0xFF);
            }
        }
    }

    void X64Code::StoreVariable(const char* name, Value* value, Type type)
    {
        int offset = GetVariableOffset(name);
        if (type == Double)
        {
            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x11);
            m_CodeBuffer.push_back(0x85);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
        }
        else
        {
            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x89);
            m_CodeBuffer.push_back(0x85 + (0 << 3));
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
        }
    }

    Value* X64Code::LoadVariable(const char* name, Type type)
    {
        int offset = GetVariableOffset(name);
        if (type == Double)
        {
            m_CodeBuffer.push_back(0xF2);
            m_CodeBuffer.push_back(0x0F);
            m_CodeBuffer.push_back(0x10);
            m_CodeBuffer.push_back(0x85);
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
        }
        else
        {
            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x8B);
            m_CodeBuffer.push_back(0x85 + (0 << 3));
            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
        }
        return nullptr;
    }

    Value* X64Code::CreateArrayAccess(const char* name, Value* index)
    {
        int reg1 = allocateRegister();
        int reg2 = allocateRegister();

        int arrayOffset = GetVariableOffset(name);
        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x8B);
        m_CodeBuffer.push_back(0x45 + (reg1 << 3));
        m_CodeBuffer.push_back(static_cast<unsigned char>(arrayOffset));

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0xC1);
        m_CodeBuffer.push_back(0xE2);
        m_CodeBuffer.push_back(0x03);

        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x01);
        m_CodeBuffer.push_back(0xD0 + (reg2 << 3) + reg1);

        freeRegister(reg1);
        freeRegister(reg2);

        return nullptr;
    }

} // namespace cse
