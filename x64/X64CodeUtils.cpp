#include "X64Code.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>
#include <capstone/capstone.h>
#include <cstdlib>

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


    bool X64Code::performConstantFolding(Quad& quad)
    {
        OpEnum op = quad.getOp();
        std::string arg1 = quad.getArg1();
        std::string arg2 = quad.getArg2();
        std::string result = quad.getResult();

        if (op == OpEnum::ADD || op == OpEnum::SUB || op == OpEnum::MUL || op == OpEnum::DIV ||
            op == OpEnum::AND || op == OpEnum::OR || op == OpEnum::XOR || op == OpEnum::LSHIFT || op == OpEnum::RSHIFT)
        {
            if (arg1.empty() || arg2.empty())
            {
                return false;
            }

            bool arg1IsConst = isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]));
            bool arg2IsConst = isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1]));

            if (arg1IsConst && arg2IsConst)
            {
                int val1 = stoi_compat(arg1);
                int val2 = stoi_compat(arg2);
                int foldedResult = 0;

                switch (op)
                {
                case OpEnum::ADD:
                    foldedResult = val1 + val2;
                    break;
                case OpEnum::SUB:
                    foldedResult = val1 - val2;
                    break;
                case OpEnum::MUL:
                    foldedResult = val1 * val2;
                    break;
                case OpEnum::DIV:
                    if (val2 != 0)
                        foldedResult = val1 / val2;
                    else
                        return false;
                    break;
                case OpEnum::AND:
                    foldedResult = val1 & val2;
                    break;
                case OpEnum::OR:
                    foldedResult = val1 | val2;
                    break;
                case OpEnum::XOR:
                    foldedResult = val1 ^ val2;
                    break;
                case OpEnum::LSHIFT:
                    foldedResult = val1 << val2;
                    break;
                case OpEnum::RSHIFT:
                    foldedResult = val1 >> val2;
                    break;
                default:
                    return false;
                }

                quad = Quad(op, to_string_compat(foldedResult), "", result);
                std::cout << "Constant folding: " << val1 << " " << opToString(op) << " " << val2 << " = " << foldedResult << std::endl;
                return true;
            }
        }

        return false;
    }

    std::list<Quad> X64Code::performDeadCodeElimination(const std::list<Quad>& quadList)
    {
        std::set<std::string> usedVariables;
        std::set<OpEnum> alwaysUsedOps = {OpEnum::RET, OpEnum::CALL, OpEnum::JMP, OpEnum::JMPT,
                                           OpEnum::JMPF, OpEnum::LABEL, OpEnum::FUNC, OpEnum::PARAM,
                                           OpEnum::MEMBER_STORE};

        bool changed = true;
        int iterations = 0;
        const int maxIterations = 100;

        while (changed && iterations < maxIterations)
        {
            changed = false;
            iterations++;

            for (auto it = quadList.rbegin(); it != quadList.rend(); ++it)
            {
                const Quad& quad = *it;
                OpEnum op = quad.getOp();
                std::string arg1 = quad.getArg1();
                std::string arg2 = quad.getArg2();
                std::string result = quad.getResult();

                bool isUsed = false;

                if (alwaysUsedOps.find(op) != alwaysUsedOps.end())
                {
                    isUsed = true;
                }
                else if (!result.empty())
                {
                    bool isParam = (result.substr(0, 6) == "param_");
                    if (usedVariables.find(result) != usedVariables.end() || result == "rcx" || result == "rdx" || result == "r8" || result == "r9" || result == "stack" ||
                        result == "xmm0" || result == "xmm1" || result == "xmm2" || result == "xmm3" || isParam)
                    {
                        isUsed = true;
                    }
                }
                else
                {
                    isUsed = true;
                }

                if (isUsed)
                {
                    auto insertIfNew = [&changed](std::set<std::string>& s, const std::string& v) {
                        if (!v.empty() && !isdigit(v[0]) && !(v[0] == '-' && isdigit(v[1])) && v != "rcx" && v != "rdx" && v != "r8" && v != "r9" && v != "stack" &&
                            v != "xmm0" && v != "xmm1" && v != "xmm2" && v != "xmm3" && v.substr(0, 6) != "param_")
                        {
                            auto result = s.insert(v);
                            if (result.second)
                            {
                                changed = true;
                            }
                        }
                    };

                    insertIfNew(usedVariables, arg1);
                    insertIfNew(usedVariables, arg2);
                    insertIfNew(usedVariables, result);
                }
            }
        }

        std::list<Quad> optimizedQuads;
        for (const auto& quad : quadList)
        {
            OpEnum op = quad.getOp();
            std::string arg1 = quad.getArg1();
            std::string arg2 = quad.getArg2();
            std::string result = quad.getResult();

            bool isUsed = false;

            if (alwaysUsedOps.find(op) != alwaysUsedOps.end())
            {
                isUsed = true;
            }
            else if (!result.empty())
                {
                    bool isParam = (result.substr(0, 6) == "param_");
                    if (usedVariables.find(result) != usedVariables.end() || result == "rcx" || result == "rdx" || result == "r8" || result == "r9" || result == "stack" ||
                        result == "xmm0" || result == "xmm1" || result == "xmm2" || result == "xmm3" || isParam)
                    {
                        isUsed = true;
                    }
                }
            else
            {
                isUsed = true;
            }

            if (isUsed)
            {
                optimizedQuads.push_back(quad);
            }
            else
            {
                std::cout << "Dead code eliminated: " << opToString(op) << " " << arg1 << " " << arg2 << " " << result << std::endl;
            }
        }

        return optimizedQuads;
    }

    std::string X64Code::disassembleInstruction(size_t& pos) const
    {
        if (pos >= m_CodeBuffer.size())
        {
            return "";
        }

        csh handle;
        cs_insn* insn;
        size_t count;

        if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
        {
            return "Error: Failed to initialize Capstone";
        }

        cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

        size_t remaining = m_CodeBuffer.size() - pos;
        const uint8_t* code = reinterpret_cast<const uint8_t*>(m_CodeBuffer.data() + pos);
        count = cs_disasm(handle, code, remaining, pos, 1, &insn);

        std::string result;
        if (count > 0)
        {
            std::stringstream ss;
            ss << std::hex << std::setw(8) << std::setfill('0') << insn[0].address << ": ";
            for (int i = 0; i < insn[0].size; i++)
            {
                ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(insn[0].bytes[i]) << " ";
            }
            for (int i = insn[0].size; i < 15; i++)
            {
                ss << "   ";
            }
            ss << insn[0].mnemonic << "\t" << insn[0].op_str;
            result = ss.str();
            pos += insn[0].size;
            cs_free(insn, count);
        }
        else
        {
            result = "Error: Failed to disassemble instruction";
            pos++;
        }

        cs_close(&handle);
        return result;
    }

    size_t X64Code::getInstructionLength(size_t pos) const
    {
        if (pos >= m_CodeBuffer.size())
        {
            return 0;
        }

        csh handle;
        cs_insn* insn;
        size_t count;

        if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
        {
            return 1;
        }

        size_t remaining = m_CodeBuffer.size() - pos;
        const uint8_t* code = reinterpret_cast<const uint8_t*>(m_CodeBuffer.data() + pos);
        count = cs_disasm(handle, code, remaining, pos, 1, &insn);

        size_t length = 1;
        if (count > 0)
        {
            length = insn[0].size;
            cs_free(insn, count);
        }

        cs_close(&handle);
        return length;
    }

    uint32_t X64Code::readImm32(size_t pos) const
    {
        if (pos + 4 > m_CodeBuffer.size())
        {
            return 0;
        }

        uint32_t value = 0;
        for (int i = 0; i < 4; i++)
        {
            value |= static_cast<uint32_t>(m_CodeBuffer[pos + i]) << (i * 8);
        }
        return value;
    }

    uint64_t X64Code::readImm64(size_t pos) const
    {
        if (pos + 8 > m_CodeBuffer.size())
        {
            return 0;
        }

        uint64_t value = 0;
        for (int i = 0; i < 8; i++)
        {
            value |= static_cast<uint64_t>(m_CodeBuffer[pos + i]) << (i * 8);
        }
        return value;
    }

    std::string X64Code::toHex(uint8_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
        return ss.str();
    }

    std::string X64Code::toHex32(uint32_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << value;
        return ss.str();
    }

    std::string X64Code::toHex64(uint64_t value) const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << value;
        return ss.str();
    }

    std::string X64Code::formatOffset(int8_t offset) const
    {
        std::stringstream ss;
        if (offset >= 0)
        {
            ss << "+" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(offset);
        }
        else
        {
            ss << "-" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(-offset);
        }
        return ss.str();
    }

    void X64Code::DisassembleCode() const
    {
        std::cout << "Disassembling code (" << m_CodeBuffer.size() << " bytes):" << std::endl;

        csh handle;
        cs_insn* insn;
        size_t count;

        if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
        {
            std::cerr << "Error: Failed to initialize Capstone" << std::endl;
            return;
        }

        cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

        const uint8_t* code = reinterpret_cast<const uint8_t*>(m_CodeBuffer.data());
        size_t codeSize = m_CodeBuffer.size();

        count = cs_disasm(handle, code, codeSize, 0, 0, &insn);

        if (count > 0)
        {
            for (size_t i = 0; i < count; i++)
            {
                std::cout << std::hex << std::setw(8) << std::setfill('0') << insn[i].address << ": ";
                for (int j = 0; j < insn[i].size; j++)
                {
                    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(insn[i].bytes[j]) << " ";
                }
                for (int j = insn[i].size; j < 15; j++)
                {
                    std::cout << "   ";
                }
                std::cout << insn[i].mnemonic << "\t" << insn[i].op_str << std::endl;
            }
            cs_free(insn, count);
        }
        else
        {
            std::cerr << "Error: Failed to disassemble code" << std::endl;
        }

        cs_close(&handle);
    }

} // namespace cse
