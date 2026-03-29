#include <iomanip>
#include <iostream>
#include <capstone/capstone.h>

#include "CodeGeneratorFactory.h"
#include "codegen.h"
#include "FFIRegistry.h"
#include "../platform/PlatformAbstraction.h"

#ifndef CSE_PLATFORM_EMBEDDED
#include "x64/X64Code.h"
#endif

using namespace std;

namespace cse
{

    template <typename RetType>
    inline RetType invokeAndCast(void *funcPtr)
    {
        using FuncType = RetType (*)();
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func();
    }

    inline int invokeMainFunction(void *funcPtr, ReturnType retType)
    {
        switch (retType)
        {
        case ReturnType::Double:
        {
            double result = invokeAndCast<double>(funcPtr);
            return static_cast<int>(result);
        }
        case ReturnType::Float:
        {
            float result = invokeAndCast<float>(funcPtr);
            return static_cast<int>(result);
        }
        case ReturnType::Integer:
        default:
        {
            int result = invokeAndCast<int>(funcPtr);
            return result;
        }
        }
    }

    CodeGenContext::CodeGenContext()
    {
        m_Code = nullptr;
    }

    BaseCodeGenerator *CodeGenContext::getCodeGenerator(const std::string &platform)
    {
        if (!m_Code)
        {
            m_Code = CodeGeneratorFactory::createCodeGenerator(platform);

            BaseCodeGenerator *baseCodeGen = dynamic_cast<BaseCodeGenerator *>(m_Code);
            if (baseCodeGen)
            {
                PlatformAbstraction *platformAbstraction = PlatformFactory::createPlatformAbstraction();
                baseCodeGen->setPlatformAbstraction(platformAbstraction);
            }
        }
        return m_Code;
    }

#ifndef CSE_PLATFORM_EMBEDDED
    X64Code *CodeGenContext::getX64CodeGenerator()
    {
        return dynamic_cast<X64Code *>(m_Code);
    }
#endif

    static void *allocateExecutableMemory(PlatformAbstraction *platform, size_t size)
    {
        if (platform)
        {
            return platform->allocateExecutableMemory(size);
        }
        
#ifdef _WIN32
        return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
        return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#endif
    }

    static void freeExecutableMemory(PlatformAbstraction *platform, void *memory, size_t size)
    {
        if (platform)
        {
            platform->freeExecutableMemory(memory, size);
            return;
        }
        
#ifdef _WIN32
        VirtualFree(memory, 0, MEM_RELEASE);
#else
        munmap(memory, size);
#endif
    }

    static bool setMemoryProtection(PlatformAbstraction *platform, void *memory, size_t size, bool executable)
    {
        if (platform)
        {
            return platform->setMemoryProtection(memory, size, executable);
        }
        
#ifdef _WIN32
        DWORD oldProtect;
        return VirtualProtect(memory, size, executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE, &oldProtect);
#else
        int prot = PROT_READ | PROT_WRITE;
        if (executable)
        {
            prot |= PROT_EXEC;
        }
        return mprotect(memory, size, prot) == 0;
#endif
    }

    int CodeGenContext::runCode()
    {
        std::cout << "Running code...\n";

        const std::vector<unsigned char> &codeBuffer = m_Code->GetCodeBuffer();
        size_t codeSize = codeBuffer.size();

        if (codeSize == 0)
        {
            std::cout << "No code to run\n";
            return 0;
        }

        BaseCodeGenerator *baseCodeGen = dynamic_cast<BaseCodeGenerator *>(m_Code);
        PlatformAbstraction *platform = nullptr;
        if (baseCodeGen)
        {
            platform = baseCodeGen->getPlatformAbstraction();
        }

        void *executableMemory = allocateExecutableMemory(platform, codeSize);
        if (executableMemory == NULL)
        {
            std::cout << "Failed to allocate executable memory\n";
            return 0;
        }

        std::cout << "Allocated executable memory at: " << executableMemory << std::endl;

        unsigned char *codePtr = (unsigned char *)executableMemory;
        memcpy(codePtr, codeBuffer.data(), codeSize);
        std::cout << "Code copied to executable memory successfully." << std::endl;

        if (baseCodeGen)
        {
            const auto &functionCalls = baseCodeGen->getFunctionCalls();
            std::cout << "Found " << functionCalls.size() << " function call(s) to fix" << std::endl;

            std::string platformType = PLATFORM_X86_64;
            if (platform)
            {
                platformType = platform->getPlatformName();
            }

            bool writable = setMemoryProtection(platform, executableMemory, codeSize, true);
            if (!writable)
            {
                std::cerr << "Warning: Failed to set memory protection to writable" << std::endl;
            }

            for (size_t i = 0; i < functionCalls.size(); i++)
            {
                const auto &callSite = functionCalls[i];
                size_t offset = callSite.codeOffset;
                const std::string &funcName = callSite.funcName;

                if (offset + 11 < codeSize)
                {
                    bool needsFixup = false;
                    bool isNopSequence = false;

                    if (codePtr[offset] == 0x48 && codePtr[offset + 1] == 0xB8)
                    {
                        needsFixup = true;
                    }
                    else
                    {
                        isNopSequence = true;
                        for (int j = 0; j < 12; j++)
                        {
                            if (codePtr[offset + j] != 0x90)
                            {
                                isNopSequence = false;
                                break;
                            }
                        }
                        if (isNopSequence)
                        {
                            needsFixup = true;
                        }
                    }

                    if (needsFixup)
                    {
                        void *funcAddr = nullptr;

                        if (platform)
                        {
                            funcAddr = platform->getFFIFunctionAddress(funcName);
                        }

                        if (!funcAddr && platform)
                        {
                            funcAddr = platform->getStandardLibraryFunctionAddress(funcName);
                            std::cout << "  getStandardLibraryFunctionAddress('" << funcName << "') = " << funcAddr << std::endl;
                        }

                        if (funcAddr != nullptr)
                        {
                            std::cout << "Fixed " << funcName << " call at offset: " << std::hex << offset << std::dec << std::endl;

                            if (platformType == PLATFORM_X86_64)
                            {
                                if (isNopSequence)
                                {
                                    codePtr[offset] = 0x48;
                                    codePtr[offset + 1] = 0xB8;
                                }
                                uint64_t addr = (uint64_t)funcAddr;
                                memcpy(&codePtr[offset + 2], &addr, 8);
                                codePtr[offset + 10] = 0xFF;
                                codePtr[offset + 11] = 0xD0;
                            }
                        }
                        else
                        {
                            std::cerr << "Warning: Could not find function " << funcName << std::endl;
                        }
                    }
                }
            }
        }

        bool executable = setMemoryProtection(platform, executableMemory, codeSize, true);
        if (!executable)
        {
            std::cerr << "Warning: Failed to set memory protection to executable" << std::endl;
        }

        std::cout << "\nDisassembling code after fix..." << std::endl;
        std::cout << "Code size: " << codeSize << " bytes" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        csh handle;
        cs_insn *insn;
        size_t count;

        cs_arch arch = CS_ARCH_X86;
        cs_mode mode = CS_MODE_64;

        std::string platformType = PLATFORM_X86_64;
        BaseCodeGenerator *baseCodeGenForDisasm = dynamic_cast<BaseCodeGenerator *>(m_Code);
        if (baseCodeGenForDisasm && baseCodeGenForDisasm->getPlatformAbstraction())
        {
            platformType = baseCodeGenForDisasm->getPlatformAbstraction()->getPlatformName();
            if (platformType == PLATFORM_RISCV64)
            {
                arch = CS_ARCH_RISCV;
                mode = CS_MODE_RISCV64;
            }
        }

        std::cout << "Initializing Capstone disassembler..." << std::endl;
        std::cout << "Architecture: " << arch << ", Mode: " << mode << std::endl;

        cs_err result = cs_open(arch, mode, &handle);
        if (result == CS_ERR_OK)
        {
            std::cout << "Capstone initialized successfully. Handle: " << handle << std::endl;
            cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

            count = cs_disasm(handle, codePtr, codeSize, 0, 0, &insn);

            if (count > 0)
            {
                std::cout << "Disassembling " << count << " instructions..." << std::endl;
                for (size_t i = 0; i < count; i++)
                {
                    std::ios_base::fmtflags oldFlags = std::cout.flags();
                    std::cout << std::hex << std::setw(8) << std::setfill('0') << insn[i].address << ": ";

                    for (size_t j = 0; j < insn[i].size; j++)
                    {
                        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)insn[i].bytes[j] << " ";
                    }

                    std::cout << "\t" << insn[i].mnemonic << " " << insn[i].op_str << std::endl;
                    std::cout << std::dec;
                }

                cs_free(insn, count);
            }
            else
            {
                std::cout << "Failed to disassemble code. Count: " << count << std::endl;
            }

            std::cout << "Closing Capstone handle..." << std::endl;
            cs_close(&handle);
            std::cout << "Capstone handle closed." << std::endl;
        }

        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Disassembly completed." << std::endl;

        int returnValue = 0;

        std::cout << "Attempting to execute JIT code..." << std::endl;

        std::cout << "Executable memory address: " << executableMemory << std::endl;
        
        // Find main function offset
        size_t mainOffset = 0;
        if (baseCodeGen)
        {
            const auto& funcOffsets = baseCodeGen->getFunctionOffsets();
            auto mainIt = funcOffsets.find("main");
            if (mainIt != funcOffsets.end())
            {
                mainOffset = mainIt->second;
                std::cout << "Found main function at offset: " << mainOffset << std::endl;
            }
        }
        
        void* mainFuncPtr = static_cast<unsigned char*>(executableMemory) + mainOffset;
        std::cout << "JIT function pointer: " << mainFuncPtr << std::endl;

        if (mainFuncPtr == nullptr)
        {
            std::cout << "ERROR: Function pointer is null!" << std::endl;
            returnValue = -1;
        }
        else
        {
            returnValue = invokeMainFunction(mainFuncPtr, m_MainReturnType);
        }

        std::cout << "Code execution completed.\n";
        std::cout << "main() return value: " << returnValue << "\n";

        std::cout << "Freeing executable memory..." << std::endl;
        freeExecutableMemory(platform, executableMemory, codeSize);
        std::cout << "Memory freed successfully." << std::endl;

        // 强制刷新所有输出
        std::cout.flush();
        std::cerr.flush();

        return returnValue;
    }

} // namespace cse
