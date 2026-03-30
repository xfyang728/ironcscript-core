#include "X64Code.h"
#include "../Architecture.h"
#include "../../platform/PlatformAbstraction.h"
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <iomanip>
#include <algorithm>
#include <memory>
#include <set>
#include <cctype>
#include <cstring>
#include <capstone/capstone.h>

namespace cse
{

    X64Code::X64Code() : BaseCodeGenerator(std::make_unique<X64Architecture>())
    {
        m_RegisterUsage.resize(12, false);
        m_Platform = PlatformFactory::createPlatformAbstraction();
    }

    X64Code::~X64Code()
    {
        if (m_Platform) {
            delete m_Platform;
        }
    }

    bool X64Code::IsStandardLibraryFunction(const char* name) const {
        if (m_Platform) {
            return m_Platform->isStandardLibraryFunction(name);
        }
        return false;
    }

    void X64Code::generateFunctionEpilogue()
    {
        m_CodeBuffer.push_back(0x48);
        m_CodeBuffer.push_back(0x81);
        m_CodeBuffer.push_back(0xC4);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x00);
        m_CodeBuffer.push_back(0x5D);
        m_CodeBuffer.push_back(0xC3);
        
        if (!m_CurrentFunction.empty()) {
            m_FunctionEpiloguePositions[m_CurrentFunction].push_back(m_CodeBuffer.size() - 9);
        }
    }

    void X64Code::formatCode()
    {
        size_t originalCodeSize = m_CodeBuffer.size();
        size_t entryCodeSize = m_EntryCode.size();
        size_t dataBufferSize = m_DataBuffer.size();

        std::cout << "[formatCode] START: originalCodeSize=" << originalCodeSize
                  << ", entryCodeSize=" << entryCodeSize
                  << ", dataBufferSize=" << dataBufferSize
                  << ", m_EntryCodeInsertPos=" << m_EntryCodeInsertPos << std::endl;

        // 1. 先插入 entryCode
        if (!m_EntryCode.empty())
        {
            m_CodeBuffer.insert(m_CodeBuffer.begin() + m_EntryCodeInsertPos, m_EntryCode.begin(), m_EntryCode.end());

            for (auto& func : m_Functions)
            {
                if (func.second >= m_EntryCodeInsertPos)
                {
                    func.second += entryCodeSize;
                }
            }

            std::map<size_t, std::string> newJumpSites;
            for (const auto& jumpSite : m_JumpSites)
            {
                if (jumpSite.first >= m_EntryCodeInsertPos)
                {
                    newJumpSites[jumpSite.first + entryCodeSize] = jumpSite.second;
                }
                else
                {
                    newJumpSites[jumpSite.first] = jumpSite.second;
                }
            }
            m_JumpSites = newJumpSites;

            std::map<size_t, std::string> newCallSites;
            for (const auto& callSite : m_CallSites)
            {
                if (callSite.first >= m_EntryCodeInsertPos)
                {
                    newCallSites[callSite.first + entryCodeSize] = callSite.second;
                }
                else
                {
                    newCallSites[callSite.first] = callSite.second;
                }
            }
            m_CallSites = newCallSites;

            std::map<std::string, size_t> newLabels;
            for (const auto& label : m_Labels)
            {
                if (label.second >= m_EntryCodeInsertPos)
                {
                    newLabels[label.first] = label.second + entryCodeSize;
                }
                else
                {
                    newLabels[label.first] = label.second;
                }
            }
            m_Labels = newLabels;

            std::vector<FunctionCallSite> newFunctionCalls;
            for (const auto& callSite : m_FunctionCalls)
            {
                if (callSite.codeOffset >= m_EntryCodeInsertPos)
                {
                    FunctionCallSite newCallSite;
                    newCallSite.codeOffset = callSite.codeOffset + entryCodeSize;
                    newCallSite.funcName = callSite.funcName;
                    newFunctionCalls.push_back(newCallSite);
                } else {
                    newFunctionCalls.push_back(callSite);
                }
            }
            m_FunctionCalls = newFunctionCalls;

            std::vector<RipOffsetInfo> newRipRelativeOffsets;
            std::cout << "[DEBUG] Before updating m_RipRelativeOffsets:" << std::endl;
            for (const auto& rip : m_RipRelativeOffsets)
            {
                std::cout << "[DEBUG]   instrPos=" << rip.instrPos << ", dataOffset=" << rip.dataOffset 
                          << ", instrLength=" << rip.instrLength << std::endl;
            }
            for (const auto& rip : m_RipRelativeOffsets)
            {
                RipOffsetInfo newRip;
                newRip.instrLength = rip.instrLength;
                newRip.dataOffset = rip.dataOffset;
                if (rip.instrPos >= m_EntryCodeInsertPos)
                {
                    newRip.instrPos = rip.instrPos + entryCodeSize;
                }
                else
                {
                    newRip.instrPos = rip.instrPos;
                }
                newRipRelativeOffsets.push_back(newRip);
            }
            m_RipRelativeOffsets = newRipRelativeOffsets;
            std::cout << "[DEBUG] After updating m_RipRelativeOffsets:" << std::endl;
            for (const auto& rip : m_RipRelativeOffsets)
            {
                std::cout << "[DEBUG]   instrPos=" << rip.instrPos << ", dataOffset=" << rip.dataOffset 
                          << ", instrLength=" << rip.instrLength << std::endl;
            }

            std::map<std::string, size_t> newStackAllocPositions;
            for (const auto& stackAlloc : m_StackAllocPositions)
            {
                if (stackAlloc.second >= m_EntryCodeInsertPos)
                {
                    newStackAllocPositions[stackAlloc.first] = stackAlloc.second + entryCodeSize;
                }
                else
                {
                    newStackAllocPositions[stackAlloc.first] = stackAlloc.second;
                }
            }
            m_StackAllocPositions = newStackAllocPositions;
            
            std::map<std::string, std::vector<size_t>> newFunctionEpiloguePositions;
            for (const auto& epilogueEntry : m_FunctionEpiloguePositions)
            {
                const std::string& funcName = epilogueEntry.first;
                const std::vector<size_t>& epiloguePositions = epilogueEntry.second;
                for (size_t epiloguePos : epiloguePositions)
                {
                    if (epiloguePos >= m_EntryCodeInsertPos)
                    {
                        newFunctionEpiloguePositions[funcName].push_back(epiloguePos + entryCodeSize);
                    }
                    else
                    {
                        newFunctionEpiloguePositions[funcName].push_back(epiloguePos);
                    }
                }
            }
            m_FunctionEpiloguePositions = newFunctionEpiloguePositions;

            // 修复 entryCode 中的 call 指令
            size_t callPos = m_EntryCodeInsertPos;
            size_t updatedMainPos = m_MainPos + m_EntryCode.size();
            int offset = static_cast<int>(updatedMainPos - (callPos + 5));
            if (callPos + 1 < m_CodeBuffer.size())
            {
                m_CodeBuffer[callPos + 1] = static_cast<unsigned char>(offset & 0xFF);
                m_CodeBuffer[callPos + 2] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                m_CodeBuffer[callPos + 3] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                m_CodeBuffer[callPos + 4] = static_cast<unsigned char>((offset >> 24) & 0xFF);
            }
        }

        // 2. 计算新的代码段大小
        size_t codeSizeAfterEntry = m_CodeBuffer.size();

        // 3. 插入数据段
        m_CodeBuffer.reserve(m_CodeBuffer.size() + m_DataBuffer.size());
        m_CodeBuffer.insert(m_CodeBuffer.end(), m_DataBuffer.begin(), m_DataBuffer.end());

        // 4. 处理 RIP 相对偏移
        std::cout << "formatCode: originalCodeSize=" << originalCodeSize 
                  << ", entryCodeSize=" << entryCodeSize 
                  << ", codeSizeAfterEntry=" << codeSizeAfterEntry
                  << ", dataSize=" << m_DataBuffer.size() << std::endl;

        // 打印 m_CodeBuffer 的内容
        std::cout << "[DEBUG] Code buffer before writing RIP offsets:" << std::endl;
        for (size_t i = 0; i < m_CodeBuffer.size(); i++)
        {
            if (i % 16 == 0)
            {
                std::cout << std::hex << std::setw(8) << std::setfill('0') << i << ": ";
            }
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_CodeBuffer[i]) << " ";
            if (i % 16 == 15 || i == m_CodeBuffer.size() - 1)
            {
                std::cout << std::endl;
            }
        }

        for (const auto& rip : m_RipRelativeOffsets) {
            size_t instrPos = rip.instrPos;
            size_t dataOffset = rip.dataOffset;
            size_t instrLength = rip.instrLength;

            int32_t offset = static_cast<int32_t>(codeSizeAfterEntry + dataOffset - (instrPos + instrLength));

            std::cout << "  RIP: instrPos=" << instrPos << ", dataOffset=" << dataOffset
                      << ", instrLen=" << instrLength << ", calculated_offset=0x" << std::hex << offset << std::dec << std::endl;

            size_t offsetPos = instrPos + instrLength - 4;
            std::cout << "  Writing offset at position: 0x" << std::hex << offsetPos << std::dec << std::endl;
            if (offsetPos + 4 <= m_CodeBuffer.size()) {
                m_CodeBuffer[offsetPos] = static_cast<unsigned char>(offset & 0xFF);
                m_CodeBuffer[offsetPos + 1] = static_cast<unsigned char>((offset >> 8) & 0xFF);
                m_CodeBuffer[offsetPos + 2] = static_cast<unsigned char>((offset >> 16) & 0xFF);
                m_CodeBuffer[offsetPos + 3] = static_cast<unsigned char>((offset >> 24) & 0xFF);
            }
        }

        // 打印 m_CodeBuffer 的内容
        std::cout << "[DEBUG] Code buffer after writing RIP offsets:" << std::endl;
        for (size_t i = 0; i < m_CodeBuffer.size(); i++)
        {
            if (i % 16 == 0)
            {
                std::cout << std::hex << std::setw(8) << std::setfill('0') << i << ": ";
            }
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_CodeBuffer[i]) << " ";
            if (i % 16 == 15 || i == m_CodeBuffer.size() - 1)
            {
                std::cout << std::endl;
            }
        }

        fixJumpOffsets(codeSizeAfterEntry, m_DataBuffer.size());
        fixCallOffsets(codeSizeAfterEntry, m_DataBuffer.size());

        std::cout << "Formatted code size: " << m_CodeBuffer.size() << " bytes" << std::endl;
    }

    void X64Code::AddRipRelativeOffset(size_t instrPos, size_t dataOffset, size_t instrLength)
    {
        RipOffsetInfo info;
        info.instrPos = instrPos;
        info.dataOffset = dataOffset;
        info.instrLength = instrLength;
        m_RipRelativeOffsets.push_back(info);
    }

    void X64Code::CallStandardLibraryFunction(const char* name)
    {
        FunctionCallSite site;
        site.codeOffset = m_CodeBuffer.size();
        site.funcName = name;
        m_FunctionCalls.push_back(site);
    }
    
    void X64Code::updateFunctionCallOffsets()
    {
        // 注意：这个方法在代码生成阶段被调用，但此时数据还没有被添加到代码缓冲区中
        // 所以这里不应该修改代码，而是由 codegen.cpp 中的 runCode 方法来处理函数调用的修复
    }

    void X64Code::generateCodeFromIR(const std::list<Quad>& quadList)
    {
        std::cout << "Generating code from intermediate representation..." << std::endl;

        m_CodeBuffer.clear();
        m_DataBuffer.clear();
        m_VariableOffsets.clear();
        m_VariableTypes.clear();
        m_Labels.clear();
        m_Functions.clear();
        m_JumpSites.clear();
        m_CallSites.clear();
        m_RipRelativeOffsets.clear();
        m_RegisterUsage.clear();
        m_RegisterUsage.resize(12, false);
        m_RegisteredCallbacks.clear();
        m_NextOffset = m_Architecture->getRegisterSize();
        m_NextDataOffset = 0;
        SetInFunction(false);

        m_CodeBuffer.reserve(4096);
        m_DataBuffer.reserve(1024);

        std::list<Quad> optimizedQuads = performDeadCodeElimination(quadList);

        for (auto& quad : optimizedQuads)
        {
            OpEnum op = quad.getOp();
            std::cout << "Processing quad: " << opToString(op) << " (opcode: " << static_cast<int>(op) << ") " << quad.getArg1() << " " << quad.getArg2() << " " << quad.getResult() << std::endl;
            if (!performConstantFolding(quad))
            {
                switch (op)
                {
                case OpEnum::ADD:
                    handleAddOperation(quad);
                    break;
                case OpEnum::STRING_CONCAT:
                {
                    std::string arg1 = quad.getArg1();
                    std::string arg2 = quad.getArg2();
                    std::string result = quad.getResult();
                    if (!result.empty()) {
                        AllocateVariable(result.c_str(), Int);
                        
                        int reg1 = allocateRegister();
                        loadVariableToRegister(arg1, reg1, Int);
                        if (reg1 != 1) {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(0xC1 + (reg1 << 3));
                        }
                        
                        CallStandardLibraryFunction("strlen");
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC2);
                        
                        int reg2 = allocateRegister();
                        loadVariableToRegister(arg2, reg2, Int);
                        if (reg2 != 1) {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(0xC1 + (reg2 << 3));
                        }
                        
                        CallStandardLibraryFunction("strlen");
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x01);
                        m_CodeBuffer.push_back(0xD0);
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC1);
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x83);
                        m_CodeBuffer.push_back(0xC1);
                        m_CodeBuffer.push_back(0x01);
                        CallStandardLibraryFunction("malloc");
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC3);
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC1);
                        loadVariableToRegister(arg1, 0, Int);
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC2);
                        CallStandardLibraryFunction("strcpy");
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xD8);
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC1);
                        loadVariableToRegister(arg2, 0, Int);
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xC2);
                        CallStandardLibraryFunction("strcat");
                        
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xD8);
                        
                        storeRegisterToVariable(0, result, Int);
                        
                        freeRegister(reg1);
                        freeRegister(reg2);
                    }
                }
                break;
                case OpEnum::SUB:
                    handleSubOperation(quad);
                    break;
                case OpEnum::MUL:
                    handleMulOperation(quad);
                    break;
                case OpEnum::DIV:
                    handleDivOperation(quad);
                    break;
                case OpEnum::MOD:
                    handleModOperation(quad);
                    break;
                case OpEnum::EQ:
                case OpEnum::NE:
                case OpEnum::LT:
                case OpEnum::LE:
                case OpEnum::GT:
                case OpEnum::GE:
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
                    m_CodeBuffer.push_back(0x39);
                    m_CodeBuffer.push_back(0xC0 + (reg2 << 3) + reg1);

                    m_CodeBuffer.push_back(0x0F);
                    switch (quad.getOp())
                    {
                    case OpEnum::LT:
                        m_CodeBuffer.push_back(0x9C);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    case OpEnum::LE:
                        m_CodeBuffer.push_back(0x9E);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    case OpEnum::GT:
                        m_CodeBuffer.push_back(0x9F);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    case OpEnum::GE:
                        m_CodeBuffer.push_back(0x9D);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    case OpEnum::EQ:
                        m_CodeBuffer.push_back(0x94);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    case OpEnum::NE:
                        m_CodeBuffer.push_back(0x95);
                        m_CodeBuffer.push_back(0xC0);
                        break;
                    default:
                        break;
                    }

                    m_CodeBuffer.push_back(0x48);
                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0xBE);
                    m_CodeBuffer.push_back(0xC0);

                    if (!result.empty())
                    {
                        AllocateVariable(result.c_str(), Int);
                        storeRegisterToVariable(0, result, Int);
                    }

                    freeRegister(reg1);
                    freeRegister(reg2);
                }
                break;
                case OpEnum::AND:
                    handleAndOperation(quad);
                    break;
                case OpEnum::OR:
                    handleOrOperation(quad);
                    break;
                case OpEnum::LOGICAL_AND:
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

                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0x95);
                    m_CodeBuffer.push_back(0xC0 + (reg1 << 3) + reg1);

                    if (!result.empty())
                    {
                        AllocateVariable(result.c_str(), Int);
                        storeRegisterToVariable(reg1, result, Int);
                    }

                    freeRegister(reg1);
                    freeRegister(reg2);
                }
                break;
                case OpEnum::LOGICAL_OR:
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

                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0x94);
                    m_CodeBuffer.push_back(0xC0 + (reg1 << 3) + reg1);

                    if (!result.empty())
                    {
                        AllocateVariable(result.c_str(), Int);
                        storeRegisterToVariable(reg1, result, Int);
                    }

                    freeRegister(reg1);
                    freeRegister(reg2);
                }
                break;
                case OpEnum::XOR:
                    handleXorOperation(quad);
                    break;
                case OpEnum::NOT:
                    handleNotOperation(quad);
                    break;
                case OpEnum::LOGICAL_NOT:
                {
                    std::string arg1 = quad.getArg1();
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

                    m_CodeBuffer.push_back(0x48);
                    m_CodeBuffer.push_back(0x85);
                    m_CodeBuffer.push_back(0xC0 + (reg1 << 3) + reg1);

                    m_CodeBuffer.push_back(0x0F);
                    m_CodeBuffer.push_back(0x94);
                    m_CodeBuffer.push_back(0xC0 + (reg1 << 3) + reg1);

                    if (!result.empty())
                    {
                        AllocateVariable(result.c_str(), Int);
                        storeRegisterToVariable(reg1, result, Int);
                    }

                    freeRegister(reg1);
                }
                break;
                case OpEnum::LSHIFT:
                    handleShiftLeftOperation(quad);
                    break;
                case OpEnum::RSHIFT:
                    handleShiftRightOperation(quad);
                    break;
                case OpEnum::SWITCH:
                    handleSwitchOperation(quad);
                    break;
                case OpEnum::CASE:
                    handleCaseOperation(quad);
                    break;
                case OpEnum::DEFAULT:
                    handleDefaultOperation(quad);
                    break;
                case OpEnum::ARRAY:
                {
                    std::string size = quad.getArg1();
                    std::string elementType = quad.getArg2();
                    std::string name = quad.getResult();
                    if (!name.empty()) {
                        int arraySize = 10;

                        if (VariableExists(size.c_str())) {
                        } else if (!size.empty() && (isdigit(size[0]) || (size[0] == '-' && isdigit(size[1])))) {
                            arraySize = std::stoi(size);
                        }

                        int elementSize = sizeof(int);
                        if (elementType == "double" || elementType == "float") {
                            elementSize = sizeof(double);
                        } else if (elementType == "long" || elementType == "int64") {
                            elementSize = sizeof(int64_t);
                        } else if (elementType == "short") {
                            elementSize = sizeof(short);
                        } else if (elementType == "char" || elementType == "byte") {
                            elementSize = sizeof(char);
                        }

                        int totalSize = arraySize * elementSize;

                        int elementsOffset = m_NextOffset;
                        m_VariableOffsets[name] = elementsOffset;
                        m_VariableTypes[name] = Pointer;
                        
                        ArrayInfo arrayInfo;
                        arrayInfo.name = name;
                        arrayInfo.size = arraySize;
                        arrayInfo.offset = elementsOffset;
                        arrayInfo.elementsOffset = elementsOffset;
                        arrayInfo.elementType = elementType;
                        arrayInfo.elementSize = elementSize;
                        
                        m_NextOffset += totalSize;
                        m_LocalVariableSize = m_NextOffset - m_Architecture->getRegisterSize();

                        if (!m_CurrentFunction.empty()) {
                            m_FunctionLocalVariableSizes[m_CurrentFunction] = m_LocalVariableSize;
                            std::cout << "Local variable size for function " << m_CurrentFunction << " updated to: " << m_LocalVariableSize << " bytes" << std::endl;
                        }

                        m_FunctionArrays[m_CurrentFunction].push_back(arrayInfo);
                        std::cout << "Array " << name << " allocated at offset " << elementsOffset 
                                  << " with " << arraySize << " elements of size " << elementSize << std::endl;
                    }
                }
                break;
                case OpEnum::ARRAY_LOAD:
                {
                    std::string arrayName = quad.getArg1();
                    std::string index = quad.getArg2();
                    std::string result = quad.getResult();
                    if (!result.empty()) {
                        int elementSize = sizeof(int);
                        std::string elementType = "int";
                        
                        if (!m_CurrentFunction.empty() && m_FunctionArrays.find(m_CurrentFunction) != m_FunctionArrays.end()) {
                            for (const auto& arrayInfo : m_FunctionArrays[m_CurrentFunction]) {
                                if (arrayInfo.name == arrayName) {
                                    elementSize = arrayInfo.elementSize;
                                    elementType = arrayInfo.elementType;
                                    break;
                                }
                            }
                        }
                        
                        bool isDoubleArray = (elementType == "double" || elementType == "float");
                        Type varType = isDoubleArray ? Double : Int;
                        AllocateVariable(result.c_str(), varType);
                        
                        if (isdigit(index[0]) || (index[0] == '-' && isdigit(index[1]))) {
                            int64_t value = std::stoll(index);
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0xB9);
                            m_CodeBuffer.insert(m_CodeBuffer.end(), reinterpret_cast<const unsigned char*>(&value), reinterpret_cast<const unsigned char*>(&value) + 8);
                        }
                        else if (VariableExists(index.c_str())) {
                            loadVariableToRegister(index, 1, Int);
                        }
                        
                        int varOffset = GetVariableOffset(arrayName.c_str());
                        
                        if (isDoubleArray) {
                            // 计算数组元素地址：rbp + offset - rcx*scale
                            // 栈是向下增长的，数组元素也是向下存储的
                            // 先将索引乘以元素大小
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x03); // shl rcx, 3 (乘以 8)
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x02); // shl rcx, 2 (乘以 4)
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x01); // shl rcx, 1 (乘以 2)
                            }
                            // 然后计算地址：rbp + offset - rcx
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8D);
                            m_CodeBuffer.push_back(0x85); // lea rax, [rbp + offset]
                            m_CodeBuffer.push_back(static_cast<unsigned char>(varOffset & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 24) & 0xFF));
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x29);
                            m_CodeBuffer.push_back(0xC8); // sub rax, rcx
                            // 然后加载数据
                            m_CodeBuffer.push_back(0xF2);
                            m_CodeBuffer.push_back(0x0F);
                            m_CodeBuffer.push_back(0x10);
                            m_CodeBuffer.push_back(0x00); // movsd xmm0, [rax]
                            storeRegisterToVariable(0, result, Double);
                        } else {
                            // 计算数组元素地址：rbp + offset - rcx*scale
                            // 栈是向下增长的，数组元素也是向下存储的
                            // 先将索引乘以元素大小
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x03); // shl rcx, 3 (乘以 8)
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x02); // shl rcx, 2 (乘以 4)
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x01); // shl rcx, 1 (乘以 2)
                            }
                            // 然后计算地址：rbp + offset - rcx
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8D);
                            m_CodeBuffer.push_back(0x85); // lea rax, [rbp + offset]
                            m_CodeBuffer.push_back(static_cast<unsigned char>(varOffset & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 24) & 0xFF));
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x29);
                            m_CodeBuffer.push_back(0xC8); // sub rax, rcx
                            // 然后加载数据
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0x8B);
                                m_CodeBuffer.push_back(0x00); // mov rax, [rax]
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x8B);
                                m_CodeBuffer.push_back(0x00); // mov eax, [rax]
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x66);
                                m_CodeBuffer.push_back(0x8B);
                                m_CodeBuffer.push_back(0x00); // mov ax, [rax]
                            } else if (elementSize == 1) {
                                m_CodeBuffer.push_back(0x8A);
                                m_CodeBuffer.push_back(0x00); // mov al, [rax]
                            }
                            storeRegisterToVariable(0, result, Int);
                        }
                    }
                }
                break;
                case OpEnum::ARRAY_STORE:
                {
                    std::string value = quad.getArg1();
                    std::string index = quad.getArg2();
                    std::string name = quad.getResult();
                    if (!name.empty()) {
                        int elementSize = sizeof(int);
                        std::string elementType = "int";
                        
                        if (!m_CurrentFunction.empty() && m_FunctionArrays.find(m_CurrentFunction) != m_FunctionArrays.end()) {
                            for (const auto& arrayInfo : m_FunctionArrays[m_CurrentFunction]) {
                                if (arrayInfo.name == name) {
                                    elementSize = arrayInfo.elementSize;
                                    elementType = arrayInfo.elementType;
                                    break;
                                }
                            }
                        }
                        
                        bool isDoubleArray = (elementType == "double" || elementType == "float");
                        
                        if (isDoubleArray) {
                            bool isDoubleConst = false;
                            double doubleVal = 0.0;
                            try {
                                size_t pos;
                                doubleVal = std::stod(value, &pos);
                                isDoubleConst = (pos == value.length());
                            } catch (...) {
                                isDoubleConst = false;
                            }
                            
                            if (isDoubleConst) {
                                size_t dataOffset = StoreDouble(doubleVal);
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
                            else if (VariableExists(value.c_str())) {
                                Type varType = GetVariableType(value.c_str());
                                if (varType == Double) {
                                    int offset = GetVariableOffset(value.c_str());
                                    m_CodeBuffer.push_back(0xF2);
                                    m_CodeBuffer.push_back(0x0F);
                                    m_CodeBuffer.push_back(0x10);
                                    m_CodeBuffer.push_back(0x85);
                                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                                } else {
                                    int offset = GetVariableOffset(value.c_str());
                                    m_CodeBuffer.push_back(0x48);
                                    m_CodeBuffer.push_back(0x8B);
                                    m_CodeBuffer.push_back(0x85);
                                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                                }
                            }
                        } else {
                            if (isdigit(value[0]) || (value[0] == '-' && isdigit(value[1]))) {
                                int64_t val = std::stoll(value);
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xBA);
                                m_CodeBuffer.insert(m_CodeBuffer.end(), reinterpret_cast<const unsigned char*>(&val), reinterpret_cast<const unsigned char*>(&val) + 8);
                            }
                            else if (VariableExists(value.c_str())) {
                                loadVariableToRegister(value, 1, Int);
                            }
                        }
                        
                        if (isdigit(index[0]) || (index[0] == '-' && isdigit(index[1]))) {
                            int64_t idx = std::stoll(index);
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0xB9);
                            m_CodeBuffer.insert(m_CodeBuffer.end(), reinterpret_cast<const unsigned char*>(&idx), reinterpret_cast<const unsigned char*>(&idx) + 8);
                        }
                        else if (VariableExists(index.c_str())) {
                            loadVariableToRegister(index, 1, Int);
                        }
                        
                        int varOffset = GetVariableOffset(name.c_str());
                        
                        if (isDoubleArray) {
                            // 计算数组元素地址：rbp + offset - rcx*scale
                            // 栈是向下增长的，数组元素也是向下存储的
                            // 先将索引乘以元素大小
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x03); // shl rcx, 3 (乘以 8)
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x02); // shl rcx, 2 (乘以 4)
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x01); // shl rcx, 1 (乘以 2)
                            }
                            // 然后计算地址：rbp + offset - rcx
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8D);
                            m_CodeBuffer.push_back(0x85); // lea rax, [rbp + offset]
                            m_CodeBuffer.push_back(static_cast<unsigned char>(varOffset & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 24) & 0xFF));
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x29);
                            m_CodeBuffer.push_back(0xC8); // sub rax, rcx
                            // 然后存储数据
                            m_CodeBuffer.push_back(0xF2);
                            m_CodeBuffer.push_back(0x0F);
                            m_CodeBuffer.push_back(0x11);
                            m_CodeBuffer.push_back(0x00); // movsd [rax], xmm0
                        } else {
                            // 计算数组元素地址：rbp + offset - rcx*scale
                            // 栈是向下增长的，数组元素也是向下存储的
                            // 先将索引乘以元素大小
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x03); // shl rcx, 3 (乘以 8)
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x02); // shl rcx, 2 (乘以 4)
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0xC1);
                                m_CodeBuffer.push_back(0xE1);
                                m_CodeBuffer.push_back(0x01); // shl rcx, 1 (乘以 2)
                            }
                            // 然后计算地址：rbp + offset - rcx
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8D);
                            m_CodeBuffer.push_back(0x85); // lea rax, [rbp + offset]
                            m_CodeBuffer.push_back(static_cast<unsigned char>(varOffset & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 24) & 0xFF));
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x29);
                            m_CodeBuffer.push_back(0xC8); // sub rax, rcx
                            // 然后存储数据
                            if (elementSize == 8) {
                                m_CodeBuffer.push_back(0x48);
                                m_CodeBuffer.push_back(0x89);
                                m_CodeBuffer.push_back(0x10); // mov [rax], rdx
                            } else if (elementSize == 4) {
                                m_CodeBuffer.push_back(0x89);
                                m_CodeBuffer.push_back(0x10); // mov [rax], edx
                            } else if (elementSize == 2) {
                                m_CodeBuffer.push_back(0x66);
                                m_CodeBuffer.push_back(0x89);
                                m_CodeBuffer.push_back(0x10); // mov [rax], dx
                            } else if (elementSize == 1) {
                                m_CodeBuffer.push_back(0x88);
                                m_CodeBuffer.push_back(0x10); // mov [rax], dl
                            }
                        }
                    }
                }
                break;
                case OpEnum::ADDRESS_OF:
                {
                    std::string arg1 = quad.getArg1();
                    std::string result = quad.getResult();
                    if (!result.empty()) {
                        AllocateVariable(result.c_str(), Pointer);
                        int reg = allocateRegister();
                        
                        if (!VariableExists(arg1.c_str())) {
                            AllocateVariable(arg1.c_str(), Int);
                        }
                        
                        int offset = GetVariableOffset(arg1.c_str());
                        
                        if (reg >= 8) {
                            m_CodeBuffer.push_back(0x49);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(0xE0 + (reg - 8));
                        } else {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(0xE8 + reg);
                        }
                        
                        if (offset != 0) {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x81);
                            if (reg >= 8) {
                                m_CodeBuffer.push_back(0xC0 + (reg - 8));
                            } else {
                                m_CodeBuffer.push_back(0xC0 + reg);
                            }
                            m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                        }
                        
                        storeRegisterToVariable(reg, result, Pointer);
                        
                        freeRegister(reg);
                    }
                }
                break;
                case OpEnum::DEREFERENCE:
                {
                    std::string arg1 = quad.getArg1();
                    std::string result = quad.getResult();
                    if (!result.empty()) {
                        AllocateVariable(result.c_str(), Int);
                        int reg = allocateRegister();
                        
                        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]))) {
                            int value = std::stoi(arg1);
                            loadIntegerToRegister(value, reg);
                        }
                        else if (VariableExists(arg1.c_str())) {
                            Type argType = GetVariableType(arg1.c_str());
                            loadVariableToRegister(arg1, reg, argType);
                        }
                        
                        if (reg >= 8) {
                            m_CodeBuffer.push_back(0x49);
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x00 + (reg - 8));
                        } else {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x8B);
                            m_CodeBuffer.push_back(0x00 + reg);
                        }
                        
                        storeRegisterToVariable(reg, result, Int);
                        
                        freeRegister(reg);
                    }
                }
                break;
                case OpEnum::MEMBER_STORE:
                {
                    std::string object = quad.getArg1();
                    std::string member = quad.getArg2();
                    std::string value = quad.getResult();
                    if (!object.empty() && !member.empty() && !value.empty()) {
                        int rax = 0;
                        
                        if (isdigit(value[0]) || (value[0] == '-' && isdigit(value[1]))) {
                            int val = std::stoi(value);
                            m_CodeBuffer.push_back(0xB8);
                            m_CodeBuffer.push_back(static_cast<unsigned char>(val & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((val >> 8) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((val >> 16) & 0xFF));
                            m_CodeBuffer.push_back(static_cast<unsigned char>((val >> 24) & 0xFF));
                        }
                        else if (VariableExists(value.c_str())) {
                            loadVariableToRegister(value, rax, Int);
                        }
                        
                        int structBaseOffset = 0;
                        if (m_StructOffsets.find(object) != m_StructOffsets.end()) {
                            structBaseOffset = m_StructOffsets[object];
                        } else {
                            // 为结构体分配足够的空间（至少 16 字节，以容纳常见的结构体成员）
                            structBaseOffset = m_NextOffset;
                            m_VariableOffsets[object] = structBaseOffset;
                            m_VariableTypes[object] = Int;
                            m_NextOffset += 16; // 分配 16 字节空间
                            m_LocalVariableSize = m_NextOffset - m_Architecture->getRegisterSize();
                            if (!m_CurrentFunction.empty()) {
                                m_FunctionLocalVariableSizes[m_CurrentFunction] = m_LocalVariableSize;
                            }
                            m_StructOffsets[object] = structBaseOffset;
                        }
                        
                        int memberOffset = 0;
                        if (member == "x") memberOffset = 0;
                        else if (member == "y") memberOffset = 4;
                        else if (member == "z") memberOffset = 8;
                        else if (member == "w") memberOffset = 12;
                        
                        int totalOffset = structBaseOffset + memberOffset;
                        int displacement = -totalOffset;
                        
                        // 存储数据到结构体成员（使用 4 字节存储，因为 int 是 4 字节）
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0x85);
                        m_CodeBuffer.push_back(static_cast<unsigned char>(displacement & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 8) & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 16) & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 24) & 0xFF));
                        
                        freeRegister(rax);
                    }
                }
                break;
                case OpEnum::MEMBER_ACCESS:
                {
                    std::string object = quad.getArg1();
                    std::string member = quad.getArg2();
                    std::string result = quad.getResult();
                    if (!object.empty() && !member.empty() && !result.empty()) {
                        int structBaseOffset = 0;
                        if (m_StructOffsets.find(object) != m_StructOffsets.end()) {
                            structBaseOffset = m_StructOffsets[object];
                        } else {
                            // 为结构体分配足够的空间（至少 16 字节，以容纳常见的结构体成员）
                            structBaseOffset = m_NextOffset;
                            m_VariableOffsets[object] = structBaseOffset;
                            m_VariableTypes[object] = Int;
                            m_NextOffset += 16; // 分配 16 字节空间
                            m_LocalVariableSize = m_NextOffset - m_Architecture->getRegisterSize();
                            if (!m_CurrentFunction.empty()) {
                                m_FunctionLocalVariableSizes[m_CurrentFunction] = m_LocalVariableSize;
                            }
                            m_StructOffsets[object] = structBaseOffset;
                        }
                        
                        int memberOffset = 0;
                        if (member == "x") memberOffset = 0;
                        else if (member == "y") memberOffset = 4;
                        else if (member == "z") memberOffset = 8;
                        else if (member == "w") memberOffset = 12;
                        
                        int totalOffset = structBaseOffset + memberOffset;
                        int displacement = -totalOffset;
                        
                        // 从结构体成员加载数据
                        m_CodeBuffer.push_back(0x8B);
                        m_CodeBuffer.push_back(0x85);
                        m_CodeBuffer.push_back(static_cast<unsigned char>(displacement & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 8) & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 16) & 0xFF));
                        m_CodeBuffer.push_back(static_cast<unsigned char>((displacement >> 24) & 0xFF));
                        
                        AllocateVariable(result.c_str(), Int);
                        storeRegisterToVariable(0, result, Int);
                    }
                }
                break;
                case OpEnum::STORE_DEREFERENCE:
                {
                    std::string arg1 = quad.getArg1();
                    std::string arg2 = quad.getArg2();
                    if (!arg1.empty() && !arg2.empty()) {
                        int reg1 = allocateRegister();
                        int reg2 = allocateRegister();
                        
                        if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]))) {
                            int value = std::stoi(arg1);
                            loadIntegerToRegister(value, reg1);
                        }
                        else if (VariableExists(arg1.c_str())) {
                            Type argType = GetVariableType(arg1.c_str());
                            loadVariableToRegister(arg1, reg1, argType);
                        }
                        
                        if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1]))) {
                            int value = std::stoi(arg2);
                            loadIntegerToRegister(value, reg2);
                        }
                        else if (VariableExists(arg2.c_str())) {
                            loadVariableToRegister(arg2, reg2, Int);
                        }
                        
                        if (reg1 >= 3 && reg2 >= 3) {
                            m_CodeBuffer.push_back(0x4D);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(((reg2 - 3) << 3) | (reg1 - 3));
                        } else if (reg1 >= 3) {
                            m_CodeBuffer.push_back(0x49);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back((reg2 << 3) | (reg1 - 3));
                        } else if (reg2 >= 3) {
                            m_CodeBuffer.push_back(0x4C);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(((reg2 - 3) << 3) | reg1);
                        } else {
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back((reg2 << 3) | reg1);
                        }
                        
                        freeRegister(reg1);
                        freeRegister(reg2);
                    }
                }
                break;
                case OpEnum::ASSIGN:
                {
                    std::string arg1 = quad.getArg1();
                    std::string result = quad.getResult();
                    if (!result.empty())
                    {
                        if (arg1.empty()) {
                            AllocateVariable(result.c_str(), Int);
                            break;
                        }

                        int paramReg = -1;
                        int xmmReg = -1;
                        std::cout << "[DEBUG] ASSIGN: result=" << result << ", arg1=" << arg1 << std::endl;
                        
                        // 直接检查 result 是否以 "param_" 开头
                        bool isParam = result.rfind("param_", 0) == 0;
                        std::cout << "[DEBUG] ASSIGN: isParam=" << isParam << std::endl;
                        
                        if (isParam) {
                            // 提取参数索引
                            std::string paramIndexStr = result.substr(6);
                            int paramIndex = std::stoi(paramIndexStr);
                            std::cout << "[DEBUG] ASSIGN: paramIndex=" << paramIndex << std::endl;
                            
                            Type varType = Int;
                            if (m_VariableTypes.find(arg1) != m_VariableTypes.end()) {
                                varType = m_VariableTypes[arg1];
                            } else {
                                // 判断是否是数组变量
                                bool isArrayVar = false;
                                if (!m_CurrentFunction.empty() && m_FunctionArrays.find(m_CurrentFunction) != m_FunctionArrays.end()) {
                                    for (const auto& arrayInfo : m_FunctionArrays[m_CurrentFunction]) {
                                        if (arrayInfo.name == arg1) {
                                            isArrayVar = true;
                                            break;
                                        }
                                    }
                                }
                                if (isArrayVar) {
                                    varType = Pointer;
                                }
                            }
                            
                            if (varType == Double) {
                                if (paramIndex == 0) xmmReg = 0;
                                else if (paramIndex == 1) xmmReg = 1;
                                else if (paramIndex == 2) xmmReg = 2;
                                else if (paramIndex == 3) xmmReg = 3;
                            } else {
                                if (paramIndex == 0) paramReg = 1;  // rcx
                                else if (paramIndex == 1) paramReg = 2;  // rdx
                                else if (paramIndex == 2) paramReg = 8;  // r8
                                else if (paramIndex == 3) paramReg = 9;  // r9
                                else paramReg = -1;  // 栈参数
                            }
                            std::cout << "[DEBUG] ASSIGN: paramReg=" << paramReg << ", xmmReg=" << xmmReg << std::endl;
                        } else if (result == "rcx") {
                            paramReg = 1;
                        } else if (result == "rdx") {
                            paramReg = 2;
                        } else if (result == "r8") {
                            paramReg = 8;
                        } else if (result == "r9") {
                            paramReg = 9;
                        }

                        if (paramReg >= 0 || xmmReg >= 0)
                        {
                            std::cout << "[DEBUG] ASSIGN: result=" << result << ", arg1=" << arg1 << ", paramReg=" << paramReg << ", xmmReg=" << xmmReg << std::endl;
                            if (paramReg < 0 && xmmReg < 0) {
                                if (result == "rcx") paramReg = 1;
                                else if (result == "rdx") paramReg = 2;
                                else if (result == "r8") paramReg = 8;
                                else if (result == "r9") paramReg = 9;
                            }

                            if (xmmReg >= 0) {
                                bool isDoubleConst = false;
                                try {
                                    size_t pos;
                                    std::stod(arg1, &pos);
                                    isDoubleConst = (pos == arg1.length());
                                } catch (...) {
                                    isDoubleConst = false;
                                }

                                if (isDoubleConst) {
                                    double value = std::stod(arg1);
                                    size_t dataOffset = StoreDouble(value);
                                    size_t instrPos = m_CodeBuffer.size();
                                    m_CodeBuffer.push_back(0xF2);
                                    m_CodeBuffer.push_back(0x0F);
                                    m_CodeBuffer.push_back(0x10);
                                    m_CodeBuffer.push_back(0x05 + (xmmReg << 3));
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    AddRipRelativeOffset(instrPos, dataOffset, 8);
                                } else if (VariableExists(arg1.c_str())) {
                                    Type varType = GetVariableType(arg1.c_str());
                                    if (varType == Double) {
                                        int offset = GetVariableOffset(arg1.c_str());
                                        m_CodeBuffer.push_back(0xF2);
                                        m_CodeBuffer.push_back(0x0F);
                                        m_CodeBuffer.push_back(0x10);
                                        m_CodeBuffer.push_back(0x85 + (xmmReg << 3));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                                    }
                                }
                            } else if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]))) {
                                int value = std::stoi(arg1);
                                loadIntegerToRegister(value, paramReg);
                            } else if (VariableExists(arg1.c_str())) {
                                int constValue;
                                if (GetConstantValue(arg1.c_str(), constValue)) {
                                    loadIntegerToRegister(constValue, paramReg);
                                } else {
                                    int tempReg = allocateRegister();
                                    Type argType = Int;
                                    if (m_VariableTypes.find(arg1) != m_VariableTypes.end()) {
                                        argType = m_VariableTypes[arg1];
                                    } else {
                                        bool isArrayVar = false;
                                        if (!m_CurrentFunction.empty() && m_FunctionArrays.find(m_CurrentFunction) != m_FunctionArrays.end()) {
                                            for (const auto& arrayInfo : m_FunctionArrays[m_CurrentFunction]) {
                                                if (arrayInfo.name == arg1) {
                                                    isArrayVar = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (isArrayVar) {
                                            argType = Pointer;
                                        }
                                    }
                                    loadVariableToRegister(arg1, tempReg, argType);
                                    if (argType == Pointer || argType == Double) {
                                        if (paramReg >= 8 && tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x4D);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + (paramReg - 8));
                                        } else if (paramReg >= 8) {
                                            m_CodeBuffer.push_back(0x49);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + (paramReg - 8));
                                        } else if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x4C);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + paramReg);
                                        } else {
                                            m_CodeBuffer.push_back(0x48);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + paramReg);
                                        }
                                    } else {
                                        if (paramReg >= 8 && tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x45);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + (paramReg - 8));
                                        } else if (paramReg >= 8) {
                                            m_CodeBuffer.push_back(0x41);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + (paramReg - 8));
                                        } else if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x44);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + paramReg);
                                        } else {
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + paramReg);
                                        }
                                    }
                                    freeRegister(tempReg);
                                }
                            } else {
                                int constValue;
                                if (GetConstantValue(arg1.c_str(), constValue)) {
                                    loadIntegerToRegister(constValue, paramReg);
                                } else {
                                    size_t dataOffset = StoreString(arg1.c_str());
                                    size_t instrPos = m_CodeBuffer.size();
                                    m_CodeBuffer.push_back(0x48);
                                    m_CodeBuffer.push_back(0x8D);
                                    if (paramReg >= 8) {
                                        m_CodeBuffer.push_back(0x45);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                    } else {
                                        m_CodeBuffer.push_back(0x05);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                    }
                                    AddRipRelativeOffset(instrPos, dataOffset);
                                }
                            }
                        }
                        else if (result == "xmm0" || result == "xmm1" || result == "xmm2" || result == "xmm3")
                        {
                            int xmmReg = 0;
                            if (result == "xmm0") xmmReg = 0;
                            else if (result == "xmm1") xmmReg = 1;
                            else if (result == "xmm2") xmmReg = 2;
                            else if (result == "xmm3") xmmReg = 3;
                            
                            if (xmmReg + 1 > m_XmmRegCount) {
                                m_XmmRegCount = xmmReg + 1;
                            }
                            
                            bool isDouble = false;
                            try {
                                size_t pos;
                                std::stod(arg1, &pos);
                                isDouble = (pos == arg1.length());
                            } catch (...) {
                                isDouble = false;
                            }
                            
                            if (isDouble)
                            {
                                double value = std::stod(arg1);
                                size_t dataOffset = StoreDouble(value);
                                size_t instrPos = m_CodeBuffer.size();
                                m_CodeBuffer.push_back(0xF2);
                                m_CodeBuffer.push_back(0x0F);
                                m_CodeBuffer.push_back(0x10);
                                m_CodeBuffer.push_back(0x05 + (xmmReg << 3));
                                m_CodeBuffer.push_back(0x00);
                                m_CodeBuffer.push_back(0x00);
                                m_CodeBuffer.push_back(0x00);
                                m_CodeBuffer.push_back(0x00);
                                AddRipRelativeOffset(instrPos, dataOffset, 8);
                            }
                            else if (VariableExists(arg1.c_str()))
                            {
                                Type varType = GetVariableType(arg1.c_str());
                                if (varType == Double)
                                {
                                    int offset = GetVariableOffset(arg1.c_str());
                                    m_CodeBuffer.push_back(0xF2);
                                    m_CodeBuffer.push_back(0x0F);
                                    m_CodeBuffer.push_back(0x10);
                                    m_CodeBuffer.push_back(0x85 + (xmmReg << 3));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                                }
                                else
                                {
                                    int offset = GetVariableOffset(arg1.c_str());
                                    if (xmmReg >= 8)
                                    {
                                        m_CodeBuffer.push_back(0x4C);
                                        m_CodeBuffer.push_back(0x8B);
                                        m_CodeBuffer.push_back(0x85 + ((xmmReg - 8) << 3));
                                    }
                                    else
                                    {
                                        m_CodeBuffer.push_back(0x48);
                                        m_CodeBuffer.push_back(0x8B);
                                        m_CodeBuffer.push_back(0x85 + (xmmReg << 3));
                                    }
                                    m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                    m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                                }
                            }
                            else
                            {
                                int offset = GetVariableOffset(arg1.c_str());
                                if (xmmReg >= 8)
                                {
                                    m_CodeBuffer.push_back(0x4C);
                                    m_CodeBuffer.push_back(0x8B);
                                    m_CodeBuffer.push_back(0x85 + ((xmmReg - 8) << 3));
                                }
                                else
                                {
                                    m_CodeBuffer.push_back(0x48);
                                    m_CodeBuffer.push_back(0x8B);
                                    m_CodeBuffer.push_back(0x85 + (xmmReg << 3));
                                }
                                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                            }
                        }
                        else if (result == "stack")
                        {
                            if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                            {
                                int value = std::stoi(arg1);
                                loadIntegerToRegister(value, 0);
                            }
                            else if (VariableExists(arg1.c_str()))
                            {
                                Type argType = GetVariableType(arg1.c_str());
                                loadVariableToRegister(arg1, 0, argType);
                            }
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x89);
                            m_CodeBuffer.push_back(0x44);
                            m_CodeBuffer.push_back(0x24);
                            m_CodeBuffer.push_back(0x20 + m_StackArgCount * 8);
                            m_StackArgCount++;
                        }
                        else
                        {
                            bool isDouble = false;
                            if (arg1.find('.') != std::string::npos) {
                                try {
                                    size_t pos;
                                    std::stod(arg1, &pos);
                                    isDouble = (pos == arg1.length());
                                } catch (...) {
                                    isDouble = false;
                                }
                            }
                            
                            Type varType = Int;
                            if (isDouble) {
                                varType = Double;
                            } else if (VariableExists(arg1.c_str())) {
                                varType = GetVariableType(arg1.c_str());
                            } else if (!(isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))) {
                                // 字符串字面量，使用 Pointer 类型
                                varType = Pointer;
                            }
                            
                            AllocateVariable(result.c_str(), varType);
                            
                            if (!GetInFunction() && m_GlobalVariableOffsets.find(result) != m_GlobalVariableOffsets.end()) {
                                size_t globalOffset = m_GlobalVariableOffsets[result];
                                
                                if (isDouble)
                                {
                                    double value = std::stod(arg1);
                                    uint64_t doubleValue;
                                    memcpy(&doubleValue, &value, sizeof(double));
                                    for (int i = 0; i < 8; i++) {
                                        m_DataBuffer[globalOffset + i] = static_cast<unsigned char>((doubleValue >> (i * 8)) & 0xFF);
                                    }
                                }
                                else if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                                {
                                    int value = std::stoi(arg1);
                                    for (int i = 0; i < 4; i++) {
                                        m_DataBuffer[globalOffset + i] = static_cast<unsigned char>((value >> (i * 8)) & 0xFF);
                                    }
                                }
                            } else {
                                if (isDouble)
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
                                    storeRegisterToVariable(0, result, Double);
                                }
                                else if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                                {
                                    int reg = allocateRegister();
                                    int value = std::stoi(arg1);
                                    loadIntegerToRegister(value, reg);
                                    storeRegisterToVariable(reg, result, Int);
                                    freeRegister(reg);
                                    if ((result[0] == 't' && result.size() > 1 && std::isdigit(result[1])) ||
                                        (result[0] == 'p' && result[1] == 'e' && std::isdigit(result[2]))) {
                                        SetConstantValue(result.c_str(), value);
                                    }
                                }
                                else if (VariableExists(arg1.c_str()))
                                {
                                    Type argType = GetVariableType(arg1.c_str());
                                    int reg = allocateRegister();
                                    loadVariableToRegister(arg1, reg, argType);
                                    storeRegisterToVariable(reg, result, argType);
                                    freeRegister(reg);
                                    if ((result[0] == 't' && result.size() > 1 && std::isdigit(result[1])) ||
                                        (result[0] == 'p' && result[1] == 'e' && std::isdigit(result[2]))) {
                                        int srcConst;
                                        if (GetConstantValue(arg1.c_str(), srcConst)) {
                                            SetConstantValue(result.c_str(), srcConst);
                                        } else {
                                            ClearConstantValue(result.c_str());
                                        }
                                    }
                                }
                                else
                                {
                                    int reg = allocateRegister();
                                    size_t dataOffset = StoreString(arg1.c_str());
                                    size_t instrPos = m_CodeBuffer.size();
                                    m_CodeBuffer.push_back(0x48);
                                    m_CodeBuffer.push_back(0x8D);
                                    m_CodeBuffer.push_back(0x05);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    AddRipRelativeOffset(instrPos, dataOffset);
                                    
                                    if (reg != 0)
                                    {
                                        m_CodeBuffer.push_back(0x48);
                                        m_CodeBuffer.push_back(0x89);
                                        m_CodeBuffer.push_back(0xC0 + (0 << 3) + reg);
                                    }
                                    storeRegisterToVariable(reg, result, Pointer);
                                    freeRegister(reg);
                                }
                            }
                        }
                    }
                }
                break;
                case OpEnum::ENDFUNC:
                {
                    SetInFunction(false);
                    m_CurrentFunction.clear();
                    m_StackArgCount = 0;
                }
                break;
                case OpEnum::RET:
                {
                    std::string result = quad.getResult();
                    if (!result.empty())
                    {
                        Type resultType = Type::Int;
                        if (m_VariableTypes.find(result) != m_VariableTypes.end())
                        {
                            resultType = m_VariableTypes[result];
                        }

                        if (resultType == Double) {
                            bool isDoubleConst = false;
                            double doubleVal = 0.0;
                            try {
                                size_t pos;
                                doubleVal = std::stod(result, &pos);
                                isDoubleConst = (pos == result.length());
                            } catch (...) {
                                isDoubleConst = false;
                            }
                            
                            if (isDoubleConst) {
                                size_t dataOffset = StoreDouble(doubleVal);
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
                            else if (VariableExists(result.c_str()))
                            {
                                int offset = GetVariableOffset(result.c_str());
                                m_CodeBuffer.push_back(0xF2);
                                m_CodeBuffer.push_back(0x0F);
                                m_CodeBuffer.push_back(0x10);
                                m_CodeBuffer.push_back(0x85);
                                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                            }
                        } else {
                            if (isdigit(result[0]) || (result[0] == '-' && isdigit(result[1])))
                            {
                                int value = std::stoi(result);
                                loadIntegerToRegister(value, 0);
                            }
                            else if (VariableExists(result.c_str()))
                            {
                                loadVariableToRegister(result, 0, resultType);
                            }
                            else if (result[0] == 't' && std::isdigit(result[1]))
                            {
                            }
                        }
                    }
                    if (!m_CurrentFunction.empty()) {
                        m_FunctionHasReturn[m_CurrentFunction] = true;
                    }
                    generateFunctionEpilogue();
                }
                break;
                case OpEnum::LABEL:
                {
                    std::string label = quad.getResult();
                    if (!label.empty())
                    {
                        CreateLabel(label.c_str());
                        std::cout << "Created label: " << label << " at offset " << m_CodeBuffer.size() << std::endl;
                    }
                }
                break;
                case OpEnum::JMP:
                {
                    std::string label = quad.getResult();
                    if (!label.empty())
                    {
                        m_CodeBuffer.push_back(0xE9);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_JumpSites[m_CodeBuffer.size() - 5] = label;
                    }
                }
                break;
                case OpEnum::JMPT:
                {
                    std::string arg1 = quad.getArg1();
                    std::string label = quad.getResult();
                    if (!label.empty())
                    {
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
                        m_CodeBuffer.push_back(0x85);
                        m_CodeBuffer.push_back(0xC0);
                        m_CodeBuffer.push_back(0x0F);
                        m_CodeBuffer.push_back(0x85);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_JumpSites[m_CodeBuffer.size() - 6] = label;
                    }
                }
                break;
                case OpEnum::JMPF:
                {
                    std::string arg1 = quad.getArg1();
                    std::string label = quad.getResult();
                    if (!label.empty())
                    {
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
                        m_CodeBuffer.push_back(0x85);
                        m_CodeBuffer.push_back(0xC0);
                        m_CodeBuffer.push_back(0x0F);
                        m_CodeBuffer.push_back(0x84);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_JumpSites[m_CodeBuffer.size() - 6] = label;
                    }
                }
                break;
                case OpEnum::FUNC:
                {
                    std::string funcName = quad.getResult();
                    if (!funcName.empty())
                    {
                        SetInFunction(true);
                        m_CurrentFunction = funcName;
                        m_NextOffset = m_Architecture->getRegisterSize();
                        m_LocalVariableSize = 0;
                        m_FunctionHasReturn[funcName] = false;
                        m_FunctionArrays[funcName].clear();
                        m_StackArgCount = 0;
                        m_XmmRegCount = 0;
                        
                        m_Functions[funcName] = m_CodeBuffer.size();
                        std::cout << "Function " << funcName << " starts at offset " << m_CodeBuffer.size() << std::endl;
                        m_CodeBuffer.push_back(0x55);
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x89);
                        m_CodeBuffer.push_back(0xE5);
                        size_t stackAllocPos = m_CodeBuffer.size();
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x81);
                        m_CodeBuffer.push_back(0xEC);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_StackAllocPositions[funcName] = stackAllocPos;
                    }
                }
                break;
                case OpEnum::PARAM:
                {
                    std::string arg1 = quad.getArg1();
                    std::string result = quad.getResult();

                    int paramReg;
                    if (m_StackArgCount == 0) paramReg = 1;  // rcx
                    else if (m_StackArgCount == 1) paramReg = 2;  // rdx
                    else if (m_StackArgCount == 2) paramReg = 8;  // r8
                    else if (m_StackArgCount == 3) paramReg = 9;  // r9
                    else paramReg = -1;  // 栈参数

                    // 检查参数类型，确定使用通用寄存器还是 xmm 寄存器
                    bool isFloatParam = false;
                    if (VariableExists(arg1.c_str())) {
                        Type argType = GetVariableType(arg1.c_str());
                        isFloatParam = (argType == Double);
                    } else if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]))) {
                        // 检查是否是浮点数
                        if (arg1.find('.') != std::string::npos || arg1.find('e') != std::string::npos || arg1.find('E') != std::string::npos) {
                            isFloatParam = true;
                        }
                    }

                    if (isFloatParam) {
                        // 浮点数参数使用 xmm 寄存器，单独计数
                        static int xmmArgCount = 0;
                        int xmmReg = xmmArgCount;
                        if (xmmReg < 8) { // 前 8 个浮点数参数使用 xmm0-xmm7
                            if (!arg1.empty() && arg1 != result) {
                                if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1]))) {
                                    double value = std::stod(arg1);
                                    // 加载双精度浮点数到 xmm 寄存器
                                    size_t dataOffset = StoreDouble(value);
                                    size_t instrPos = m_CodeBuffer.size();
                                    m_CodeBuffer.push_back(0xF2);
                                    m_CodeBuffer.push_back(0x0F);
                                    m_CodeBuffer.push_back(0x10);
                                    m_CodeBuffer.push_back(0x05 + (xmmReg << 3));
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    m_CodeBuffer.push_back(0x00);
                                    AddRipRelativeOffset(instrPos, dataOffset, 8);
                                } else if (VariableExists(arg1.c_str())) {
                                    Type argType = GetVariableType(arg1.c_str());
                                    if (argType == Double) {
                                        // 从内存加载到 xmm 寄存器
                                        int varOffset = GetVariableOffset(arg1.c_str());
                                        m_CodeBuffer.push_back(0xF2);
                                        m_CodeBuffer.push_back(0x0F);
                                        m_CodeBuffer.push_back(0x10);
                                        m_CodeBuffer.push_back(0x85 + (xmmReg << 3));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>(varOffset & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 8) & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 16) & 0xFF));
                                        m_CodeBuffer.push_back(static_cast<unsigned char>((varOffset >> 24) & 0xFF));
                                    }
                                }
                            }
                            xmmArgCount++;
                        } else {
                            // 超过 8 个浮点数参数使用栈
                            if (!arg1.empty() && arg1 != result) {
                                if (VariableExists(arg1.c_str())) {
                                    Type argType = GetVariableType(arg1.c_str());
                                    if (argType == Double) {
                                        // 从内存加载到临时寄存器，再压入栈
                                        int tempReg = allocateRegister();
                                        loadVariableToRegister(arg1, tempReg, argType);
                                        // 分配栈空间并压入
                                        m_CodeBuffer.push_back(0x48);
                                        m_CodeBuffer.push_back(0x83);
                                        m_CodeBuffer.push_back(0xEC);
                                        m_CodeBuffer.push_back(0x08);
                                        if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x41);
                                            m_CodeBuffer.push_back(0x50 + (tempReg - 8));
                                        } else {
                                            m_CodeBuffer.push_back(0x50 + tempReg);
                                        }
                                        freeRegister(tempReg);
                                    }
                                }
                            }
                        }
                    } else {
                        // 整数/指针参数使用通用寄存器
                        if (paramReg != -1) {
                            if (!arg1.empty() && arg1 != result)
                            {
                                bool isParamRef = (arg1.rfind("param_", 0) == 0);
                                if (isParamRef)
                                {
                                    Type varType = Int;
                                    if (!result.empty() && VariableExists(result.c_str())) {
                                        varType = GetVariableType(result.c_str());
                                    }
                                    if (!result.empty()) {
                                        AllocateVariable(result.c_str(), varType);
                                        storeRegisterToVariable(paramReg, result, varType);
                                    }
                                }
                                else if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                                {
                                    int value = std::stoi(arg1);
                                    loadIntegerToRegister(value, paramReg);
                                }
                                else if (VariableExists(arg1.c_str()))
                                {
                                    Type argType = GetVariableType(arg1.c_str());
                                    int tempReg = allocateRegister();
                                    loadVariableToRegister(arg1, tempReg, argType);
                                    if (argType == Pointer || argType == Double) {
                                        if (paramReg >= 8 && tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x4D);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + (paramReg - 8));
                                        } else if (paramReg >= 8) {
                                            m_CodeBuffer.push_back(0x49);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + (paramReg - 8));
                                        } else if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x4C);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + paramReg);
                                        } else {
                                            m_CodeBuffer.push_back(0x48);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + paramReg);
                                        }
                                    } else {
                                        if (paramReg >= 8 && tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x45);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + (paramReg - 8));
                                        } else if (paramReg >= 8) {
                                            m_CodeBuffer.push_back(0x41);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + (paramReg - 8));
                                        } else if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x44);
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + ((tempReg - 8) << 3) + paramReg);
                                        } else {
                                            m_CodeBuffer.push_back(0x89);
                                            m_CodeBuffer.push_back(0xC0 + (tempReg << 3) + paramReg);
                                        }
                                    }
                                    freeRegister(tempReg);
                                }
                                else
                                {
                                    size_t dataOffset = StoreString(arg1.c_str());
                                    size_t instrPos = m_CodeBuffer.size();
                                    m_CodeBuffer.push_back(0x48);
                                    m_CodeBuffer.push_back(0x8D);
                                    if (paramReg >= 8) {
                                        m_CodeBuffer.push_back(0x45);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                    } else {
                                        m_CodeBuffer.push_back(0x05);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                        m_CodeBuffer.push_back(0x00);
                                    }
                                    AddRipRelativeOffset(instrPos, dataOffset);
                                }

                                if (!result.empty() && !isParamRef)
                                {
                                    Type varType = Int;
                                    if (VariableExists(arg1.c_str())) {
                                        varType = GetVariableType(arg1.c_str());
                                    } else if (!(isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))) {
                                        varType = Pointer;
                                    }
                                    AllocateVariable(result.c_str(), varType);
                                    storeRegisterToVariable(paramReg, result, varType);
                                }
                            }
                            else if (!result.empty())
                            {
                                AllocateVariable(result.c_str(), Int);
                                storeRegisterToVariable(paramReg, result, Int);
                            }
                        } else {
                            // 栈参数处理
                            if (!arg1.empty() && arg1 != result)
                            {
                                if (isdigit(arg1[0]) || (arg1[0] == '-' && isdigit(arg1[1])))
                                {
                                    int value = std::stoi(arg1);
                                    // 将参数压入栈
                                    m_CodeBuffer.push_back(0x6A);
                                    m_CodeBuffer.push_back(static_cast<unsigned char>(value & 0xFF));
                                }
                                else if (VariableExists(arg1.c_str()))
                                {
                                    Type argType = GetVariableType(arg1.c_str());
                                    int tempReg = allocateRegister();
                                    loadVariableToRegister(arg1, tempReg, argType);
                                    // 将参数压入栈
                                    if (argType == Pointer || argType == Double || argType == Int) {
                                        m_CodeBuffer.push_back(0x48);
                                        m_CodeBuffer.push_back(0x83);
                                        m_CodeBuffer.push_back(0xEC);
                                        m_CodeBuffer.push_back(0x08);
                                        if (tempReg >= 8) {
                                            m_CodeBuffer.push_back(0x41);
                                            m_CodeBuffer.push_back(0x50 + (tempReg - 8));
                                        } else {
                                            m_CodeBuffer.push_back(0x50 + tempReg);
                                        }
                                    }
                                    freeRegister(tempReg);
                                }
                            }
                        }
                    }

                    m_StackArgCount++;
                }
                break;
                case OpEnum::SET_AL:
                {
                    int xmmCount = std::stoi(quad.getArg1());
                    if (xmmCount > 0) {
                        m_CodeBuffer.push_back(0xB0);
                        m_CodeBuffer.push_back(static_cast<unsigned char>(xmmCount));
                    }
                }
                break;
                case OpEnum::CALL:
                {
                    std::string funcName = quad.getArg1();
                    std::string result = quad.getResult();
                    if (!funcName.empty())
                    {
                        m_StackArgCount = 0;

                        bool returnsDouble = (funcName == "sqrt" || funcName == "pow" || funcName == "sin" ||
                                              funcName == "cos" || funcName == "tan" || funcName == "fabs" ||
                                              funcName == "exp" || funcName == "log" || funcName == "log10" ||
                                              funcName == "asin" || funcName == "acos" || funcName == "atan" ||
                                              funcName == "atan2" || funcName == "floor" || funcName == "ceil" ||
                                              funcName == "round" || funcName == "fmod");
                        bool returnsPointer = (funcName == "malloc" || funcName == "calloc" || funcName == "realloc" ||
                                               funcName == "strcpy" || funcName == "strcat" || funcName == "strstr" ||
                                               funcName == "fopen" || funcName == "freopen" || funcName == "tmpfile" ||
                                               funcName == "memcpy" || funcName == "memmove" || funcName == "memset");



                        if (IsStandardLibraryFunction(funcName.c_str()))
                        {
                            CallStandardLibraryFunction(funcName.c_str());

                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0xB8);
                            for (int i = 0; i < 8; i++) {
                                m_CodeBuffer.push_back(0x00);
                            }
                            m_CodeBuffer.push_back(0xFF);
                            m_CodeBuffer.push_back(0xD0);

                            m_StackArgCount = 0;
                            m_XmmRegCount = 0;
                            if (!result.empty())
                            {
                                Type retType = returnsDouble ? Double : (returnsPointer ? Pointer : Int);
                                AllocateVariable(result.c_str(), retType);
                                storeRegisterToVariable(0, result, retType);
                            }
                            m_StackArgCount = 0;
                            m_XmmRegCount = 0;
                        }
                        else if (m_Functions.find(funcName) != m_Functions.end())
                        {
                            std::cout << "Internal function call: " << funcName << std::endl;

                            // 栈对齐处理：确保栈在函数调用前保持 16 字节对齐
                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0x83);
                            m_CodeBuffer.push_back(0xE4);
                            m_CodeBuffer.push_back(0xF0); // and rsp, 0xFFFFFFFFFFFFFFF0

                            FunctionCallSite site;
                            site.codeOffset = m_CodeBuffer.size();
                            site.funcName = funcName;
                            m_CallSites[m_CodeBuffer.size()] = funcName;

                            m_CodeBuffer.push_back(0xE8);
                            m_CodeBuffer.push_back(0x00);
                            m_CodeBuffer.push_back(0x00);
                            m_CodeBuffer.push_back(0x00);
                            m_CodeBuffer.push_back(0x00);

                            if (!result.empty())
                            {
                                Type retType = returnsDouble ? Double : (returnsPointer ? Pointer : Int);
                                AllocateVariable(result.c_str(), retType);
                                storeRegisterToVariable(0, result, retType);
                            }
                            m_StackArgCount = 0;
                            m_XmmRegCount = 0;
                        }
                        else
                        {
                            std::cout << "External function call: " << funcName << std::endl;

                            FunctionCallSite site;
                            site.codeOffset = m_CodeBuffer.size();
                            site.funcName = funcName;
                            m_FunctionCalls.push_back(site);

                            m_CodeBuffer.push_back(0x48);
                            m_CodeBuffer.push_back(0xB8);
                            for (int i = 0; i < 8; i++) {
                                m_CodeBuffer.push_back(0x00);
                            }
                            m_CodeBuffer.push_back(0xFF);
                            m_CodeBuffer.push_back(0xD0);

                            if (!result.empty())
                            {
                                Type retType = returnsDouble ? Double : (returnsPointer ? Pointer : Int);
                                AllocateVariable(result.c_str(), retType);
                                storeRegisterToVariable(0, result, retType);
                            }
                            m_StackArgCount = 0;
                            m_XmmRegCount = 0;
                        }
                    }
                }
                break;
                case OpEnum::CAST:
                {
                    std::string targetType = quad.getArg1();
                    std::string arg2 = quad.getArg2();
                    std::string result = quad.getResult();
                    if (!arg2.empty() && !result.empty())
                    {
                        Type srcType = Int;
                        if (VariableExists(arg2.c_str())) {
                            srcType = GetVariableType(arg2.c_str());
                        } else if (arg2.find('.') != std::string::npos) {
                            try {
                                size_t pos;
                                std::stod(arg2, &pos);
                                if (pos == arg2.length()) {
                                    srcType = Double;
                                }
                            } catch (...) {}
                        }
                        
                        Type dstType = Int;
                        if (targetType == "double" || targetType == "float") {
                            dstType = Double;
                        } else if (targetType.find('*') != std::string::npos) {
                            // 处理指针类型转换
                            dstType = Pointer;
                        }
                        
                        AllocateVariable(result.c_str(), dstType);
                        
                        if (srcType == Double && dstType == Int) {
                            if (arg2.find('.') != std::string::npos) {
                                try {
                                    size_t pos;
                                    double val = std::stod(arg2, &pos);
                                    if (pos == arg2.length()) {
                                        size_t dataOffset = StoreDouble(val);
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
                                } catch (...) {}
                            }
                            else if (VariableExists(arg2.c_str())) {
                                int offset = GetVariableOffset(arg2.c_str());
                                m_CodeBuffer.push_back(0xF2);
                                m_CodeBuffer.push_back(0x0F);
                                m_CodeBuffer.push_back(0x10);
                                m_CodeBuffer.push_back(0x85);
                                m_CodeBuffer.push_back(static_cast<unsigned char>(offset & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 8) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 16) & 0xFF));
                                m_CodeBuffer.push_back(static_cast<unsigned char>((offset >> 24) & 0xFF));
                            }
                            
                            m_CodeBuffer.push_back(0xF2);
                            m_CodeBuffer.push_back(0x0F);
                            m_CodeBuffer.push_back(0x2C);
                            m_CodeBuffer.push_back(0xC0);
                            
                            storeRegisterToVariable(0, result, Int);
                        }
                        else if (srcType == Int && dstType == Double) {
                            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1]))) {
                                int value = std::stoi(arg2);
                                loadIntegerToRegister(value, 0);
                            }
                            else if (VariableExists(arg2.c_str())) {
                                loadVariableToRegister(arg2, 0, Int);
                            }
                            
                            m_CodeBuffer.push_back(0xF2);
                            m_CodeBuffer.push_back(0x0F);
                            m_CodeBuffer.push_back(0x2A);
                            m_CodeBuffer.push_back(0xC0);
                            
                            storeRegisterToVariable(0, result, Double);
                        }
                        else {
                            if (isdigit(arg2[0]) || (arg2[0] == '-' && isdigit(arg2[1])))
                            {
                                int value = std::stoi(arg2);
                                loadIntegerToRegister(value, 0);
                                storeRegisterToVariable(0, result, Int);
                            }
                            else if (VariableExists(arg2.c_str()))
                            {
                                loadVariableToRegister(arg2, 0, srcType);
                                storeRegisterToVariable(0, result, dstType);
                            }
                        }
                    }
                }
                break;
                case OpEnum::EXTERN:
                {
                    std::string funcName = quad.getResult();
                    std::string retType = quad.getArg1();
                    std::cout << "Extern function declared: " << funcName << " (return type: " << retType << ")" << std::endl;
                }
                break;
                case OpEnum::REGISTER_CALLBACK:
                {
                    std::string callbackName = quad.getResult();
                    std::string targetName = quad.getArg1();
                    std::cout << "Register callback: " << callbackName << " as " << targetName << std::endl;

                    void* scriptFuncPtr = ScriptFunctionRegistry::instance().getScriptFunction(callbackName);
                    if (scriptFuncPtr) {
                        std::cout << "  Found script function at: " << scriptFuncPtr << std::endl;
                        m_RegisteredCallbacks[targetName] = scriptFuncPtr;
                    } else {
                        std::cout << "  Warning: Script function '" << callbackName << "' not found in registry" << std::endl;
                    }
                }
                break;
                case OpEnum::THROW:
                {
                    std::string thrownValue = quad.getArg1();
                    std::cout << "THROW operation: " << thrownValue << std::endl;
                    
                    // 加载抛出的值到RAX寄存器
                    if (isdigit(thrownValue[0]) || (thrownValue[0] == '-' && isdigit(thrownValue[1]))) {
                        int value = std::stoi(thrownValue);
                        loadIntegerToRegister(value, 0);
                    } else if (VariableExists(thrownValue.c_str())) {
                        loadVariableToRegister(thrownValue, 0, Int);
                    } else {
                        // 处理字符串常量
                        size_t dataOffset = StoreString(thrownValue.c_str());
                        size_t instrPos = m_CodeBuffer.size();
                        m_CodeBuffer.push_back(0x48);
                        m_CodeBuffer.push_back(0x8D);
                        m_CodeBuffer.push_back(0x05);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        m_CodeBuffer.push_back(0x00);
                        AddRipRelativeOffset(instrPos, dataOffset);
                    }
                    
                    // 简单的异常处理机制：跳转到当前函数的 catch 块
                    // 对于嵌套的 try-catch，我们需要跳转到当前函数的 catch 块
                    
                    std::cout << "THROW: Exception thrown, will be caught by nearest catch block" << std::endl;
                    
                    // 跳转到当前函数的 catch 块
                    // 根据 IR 生成器的标签命名规则，catch 块的标签是 "t1"
                    // 对于嵌套的 try-catch，我们需要找到正确的 catch 块标签
                    
                    std::string catchLabel = "t1"; // 默认标签
                    
                    // 遍历标签，找到所有 try-catch 相关的标签
                    // 对于 try-catch 语句，标签顺序是：tryLabel < catchLabel < endLabel
                    std::vector<std::pair<size_t, std::string>> labelPositions;
                    for (const auto& label : m_Labels) {
                        const std::string& labelName = label.first;
                        if (labelName.size() > 1 && labelName[0] == 't') {
                            std::string numStr = labelName.substr(1);
                            if (std::all_of(numStr.begin(), numStr.end(), ::isdigit)) {
                                labelPositions.push_back(std::make_pair(label.second, labelName));
                            }
                        }
                    }
                    
                    // 按标签位置排序
                    std::sort(labelPositions.begin(), labelPositions.end());
                    
                    // 找到当前代码位置之前的最内层 try-catch 块
                    size_t currentPos = m_CodeBuffer.size();
                    std::string tryLabel, currentCatchLabel, endLabel;
                    
                    for (size_t i = 0; i < labelPositions.size(); i++) {
                        size_t labelPos = labelPositions[i].first;
                        const std::string& labelName = labelPositions[i].second;
                        
                        // 找到当前位置之前的所有标签
                        if (labelPos < currentPos) {
                            // 检查是否是 try-catch 块的开始
                            if (i + 2 < labelPositions.size()) {
                                tryLabel = labelName;
                                currentCatchLabel = labelPositions[i + 1].second;
                                endLabel = labelPositions[i + 2].second;
                                
                                // 确保这三个标签是连续的 try-catch 块
                                size_t tryPos = labelPos;
                                size_t catchPos = labelPositions[i + 1].first;
                                size_t endPos = labelPositions[i + 2].first;
                                
                                // 检查是否是有效的 try-catch 块结构
                                if (tryPos < catchPos && catchPos < endPos) {
                                    // 检查当前位置是否在 try 块或 catch 块中
                                    if (currentPos > tryPos && currentPos < endPos) {
                                        catchLabel = currentCatchLabel;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                    std::cout << "THROW: Jumping to catch block label: " << catchLabel << std::endl;
                    
                    // 跳转到 catch 块
                    m_CodeBuffer.push_back(0xE9);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_CodeBuffer.push_back(0x00);
                    m_JumpSites[m_CodeBuffer.size() - 5] = catchLabel;
                }
                break;
                default:
                    break;
                }
            }
        }

        // 初始化 entryCode 变量
        m_EntryCode.clear();
        m_MainPos = 0;
        m_EntryCodeInsertPos = 0;
        
        auto mainIt = m_Functions.find("main");
        bool hasMainFunction = (mainIt != m_Functions.end());
        
        if (hasMainFunction)
        {
            m_MainPos = mainIt->second;
            m_EntryCode.push_back(0xE8);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0xC3);
        } else {
            m_CodeBuffer.insert(m_CodeBuffer.begin(), 0x55);
            m_CodeBuffer.insert(m_CodeBuffer.begin() + 1, {0x48, 0x89, 0xE5});
            m_CodeBuffer.insert(m_CodeBuffer.begin() + 4, {0x48, 0x81, 0xEC, 0x20, 0x00, 0x00, 0x00});

            m_MainPos = 0;
            m_EntryCode.push_back(0xE8);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0x00);
            m_EntryCode.push_back(0xC3);

            m_CodeBuffer.push_back(0x48);
            m_CodeBuffer.push_back(0x81);
            m_CodeBuffer.push_back(0xC4);
            m_CodeBuffer.push_back(0x20);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x00);
            m_CodeBuffer.push_back(0x5D);
            m_CodeBuffer.push_back(0xC3);
        }

        for (const auto& func : m_StackAllocPositions)
        {
            std::string funcName = func.first;
            size_t stackAllocPos = func.second;
            size_t localVariableSize = 0;
            auto it = m_FunctionLocalVariableSizes.find(funcName);
            if (it != m_FunctionLocalVariableSizes.end()) {
                localVariableSize = it->second;
            }
            
            size_t totalStackSize = localVariableSize + 32;
            // 确保总栈大小是 16 字节的倍数，以满足 x86-64 调用约定的栈对齐要求
            if (totalStackSize % 16 != 0) {
                totalStackSize += 16 - (totalStackSize % 16);
            }
            
            if (stackAllocPos + 3 < m_CodeBuffer.size())
            {
                m_CodeBuffer[stackAllocPos + 3] = static_cast<unsigned char>(totalStackSize & 0xFF);
                m_CodeBuffer[stackAllocPos + 4] = static_cast<unsigned char>((totalStackSize >> 8) & 0xFF);
                m_CodeBuffer[stackAllocPos + 5] = static_cast<unsigned char>((totalStackSize >> 16) & 0xFF);
                m_CodeBuffer[stackAllocPos + 6] = static_cast<unsigned char>((totalStackSize >> 24) & 0xFF);
                std::cout << "Updated stack allocation for function " << funcName << " to " << totalStackSize << " bytes" << std::endl;
            }
            
            auto epilogueIt = m_FunctionEpiloguePositions.find(funcName);
            if (epilogueIt != m_FunctionEpiloguePositions.end()) {
                const std::vector<size_t>& epiloguePositions = epilogueIt->second;
                for (size_t epiloguePos : epiloguePositions) {
                    if (epiloguePos + 3 < m_CodeBuffer.size()) {
                        m_CodeBuffer[epiloguePos + 3] = static_cast<unsigned char>(totalStackSize & 0xFF);
                        m_CodeBuffer[epiloguePos + 4] = static_cast<unsigned char>((totalStackSize >> 8) & 0xFF);
                        m_CodeBuffer[epiloguePos + 5] = static_cast<unsigned char>((totalStackSize >> 16) & 0xFF);
                        m_CodeBuffer[epiloguePos + 6] = static_cast<unsigned char>((totalStackSize >> 24) & 0xFF);
                        std::cout << "Updated stack deallocation for function " << funcName << " at position " << epiloguePos << " to " << totalStackSize << " bytes" << std::endl;
                    }
                }
            }
        }

        // 计算 entryCodeInsertPos（不插入，只保存）
        if (!m_Functions.empty())
        {
            m_EntryCodeInsertPos = m_CodeBuffer.size();
            for (const auto& func : m_Functions)
            {
                if (func.second < m_EntryCodeInsertPos)
                {
                    m_EntryCodeInsertPos = func.second;
                }
            }
        }

        fixJumpOffsetsWithoutDataAdjustment();
        fixCallOffsetsWithoutDataAdjustment();
        updateFunctionCallOffsets();

        std::cout << "Code generation completed. Total code size: " << m_CodeBuffer.size() << " bytes" << std::endl;
    }

    void X64Code::generateCodeForTryCatch(NBlock* tryBlock, const std::vector<NCatchBlock*>& catchBlocks) {
        std::cout << "[DEBUG] generateCodeForTryCatch: entered" << std::endl;
        
        // 生成try块代码
        std::cout << "[DEBUG] generateCodeForTryCatch: generating try block" << std::endl;
        // 这里需要实现try块的代码生成
        
        // 生成catch块代码
        for (size_t i = 0; i < catchBlocks.size(); i++) {
            std::cout << "[DEBUG] generateCodeForTryCatch: generating catch block " << i << std::endl;
            // 这里需要实现catch块的代码生成
        }
    }

    void X64Code::generateCodeForThrow(NExpression* expression) {
        std::cout << "[DEBUG] generateCodeForThrow: entered" << std::endl;
        
        // 生成抛出异常的代码
        // 这里需要实现throw表达式的代码生成
        
        // 简单实现：抛出一个字符串异常
        std::cout << "[DEBUG] generateCodeForThrow: generating throw code" << std::endl;
        
        // 1. 加载异常信息
        // 2. 调用异常处理函数
        // 3. 跳转到异常处理代码
    }
} // namespace cse
