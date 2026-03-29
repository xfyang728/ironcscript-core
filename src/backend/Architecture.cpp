#include "Architecture.h"

namespace cse {

std::string X86Architecture::getRegisterName(int index) const {
    static const char* regNames[] = {"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp"};
    if (index >= 0 && index < 8) {
        return regNames[index];
    }
    return "unknown";
}

std::string X86Architecture::getFloatRegisterName(int index) const {
    static const char* regNames[] = {"st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)"};
    if (index >= 0 && index < 8) {
        return regNames[index];
    }
    return "unknown";
}

std::string X64Architecture::getRegisterName(int index) const {
    static const char* regNames[] = {"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", 
                                   "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
    if (index >= 0 && index < 16) {
        return regNames[index];
    }
    return "unknown";
}

std::string X64Architecture::getFloatRegisterName(int index) const {
    static const char* regNames[] = {"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
                                   "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"};
    if (index >= 0 && index < 16) {
        return regNames[index];
    }
    return "unknown";
}

std::string RISCV64Architecture::getRegisterName(int index) const {
    static const char* regNames[] = {"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", 
                                   "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15",
                                   "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
                                   "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"};
    if (index >= 0 && index < 32) {
        return regNames[index];
    }
    return "unknown";
}

std::string RISCV64Architecture::getFloatRegisterName(int index) const {
    static const char* regNames[] = {"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", 
                                   "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
                                   "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
                                   "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"};
    if (index >= 0 && index < 32) {
        return regNames[index];
    }
    return "unknown";
}

} // namespace cse