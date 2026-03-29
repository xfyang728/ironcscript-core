#include "BaseCodeGenerator.h"
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <iomanip>
#include <algorithm>

namespace cse {

std::string BaseCodeGenerator::typeToString(Type type) {
    switch (type) {
    case Int:
        return "Int";
    case Double:
        return "Double";
    case Char:
        return "Char";
    case Bool:
        return "Bool";
    case String:
        return "String";
    case Pointer:
        return "Pointer";
    default:
        return "Unknown";
    }
}

BaseCodeGenerator::BaseCodeGenerator(std::unique_ptr<Architecture> arch) 
    : MemoryManager(), m_Architecture(std::move(arch)) {
    m_NextOffset = m_Architecture->getRegisterSize();
    m_NextDataOffset = 0;
    m_InFunction = false;
    m_ParamIndex = 0;
    m_MsvcrtDll = nullptr;
    m_LocalVariableSize = 0;
    m_CurrentFunction = "";
    m_Platform = nullptr;
    
    m_CodeBuffer.reserve(4096);
    m_DataBuffer.reserve(1024);
}

BaseCodeGenerator::~BaseCodeGenerator() {
#ifdef _WIN32
    if (m_MsvcrtDll != nullptr) {
        FreeLibrary(m_MsvcrtDll);
        m_MsvcrtDll = nullptr;
    }
#endif
}

size_t BaseCodeGenerator::GetCodeSize() const {
    return m_CodeBuffer.size();
}

const std::vector<unsigned char>& BaseCodeGenerator::GetCodeBuffer() const {
    return m_CodeBuffer;
}

const std::vector<unsigned char>& BaseCodeGenerator::GetDataBuffer() const {
    return m_DataBuffer;
}

cse::ICodeGenerator::Type BaseCodeGenerator::GetVariableType(const char* name) const {
    auto it = m_VariableTypes.find(name);
    if (it != m_VariableTypes.end()) {
        return it->second;
    }
    return cse::ICodeGenerator::Int; // 默认类型
}

void BaseCodeGenerator::AllocateVariable(const char* name, cse::ICodeGenerator::Type type) {
    if (m_GlobalVariableOffsets.find(name) != m_GlobalVariableOffsets.end()) {
        std::cout << "Global variable " << name << " already allocated" << std::endl;
    } else if (m_VariableOffsets.find(name) != m_VariableOffsets.end()) {
        std::cout << "Local variable " << name << " already allocated at offset " << m_VariableOffsets[name] << std::endl;
    } else {
        if (m_InFunction) {
                // 局部变量
                int offset = m_NextOffset;
                m_VariableOffsets[name] = offset;
                m_VariableTypes[name] = type;
                int typeSize = m_Architecture->getRegisterSize();
                if (type == cse::ICodeGenerator::Char || type == cse::ICodeGenerator::Bool) {
                    typeSize = 1;
                } else if (type == cse::ICodeGenerator::Double) {
                    typeSize = sizeof(double);
                } else if (type == cse::ICodeGenerator::Pointer) {
                    typeSize = m_Architecture->getRegisterSize();
                }
                m_NextOffset += typeSize;
                m_LocalVariableSize = m_NextOffset - m_Architecture->getRegisterSize();
                if (!m_CurrentFunction.empty()) {
                    m_FunctionLocalVariableSizes[m_CurrentFunction] = m_LocalVariableSize;
                    std::cout << "Local variable size for function " << m_CurrentFunction << " updated to: " << m_LocalVariableSize << " bytes" << std::endl;
                }
                std::cout << "Allocating new local variable " << name << " (type: " << typeToString(type) << ") at offset " << offset << std::endl;
            } else {
            // 全局变量
            int offset = m_NextDataOffset;
            m_GlobalVariableOffsets[name] = offset;
            m_VariableTypes[name] = type;
            int typeSize = m_Architecture->getRegisterSize();
            if (type == cse::ICodeGenerator::Char || type == cse::ICodeGenerator::Bool) {
                typeSize = 1;
            } else if (type == cse::ICodeGenerator::Double) {
                typeSize = sizeof(double);
            } else if (type == cse::ICodeGenerator::Pointer) {
                typeSize = m_Architecture->getRegisterSize();
            }
            for (int i = 0; i < typeSize; i++) {
                m_DataBuffer.push_back(0);
            }
            m_NextDataOffset += typeSize;
            std::cout << "Allocating new global variable " << name << " (type: " << typeToString(type) << ") at offset " << offset << std::endl;
        }
    }
}

int BaseCodeGenerator::GetVariableOffset(const char* name) {
    auto it = m_VariableOffsets.find(name);
    if (it != m_VariableOffsets.end()) {
        return -(it->second);
    }
    if (m_GlobalVariableOffsets.find(name) != m_GlobalVariableOffsets.end()) {
        return m_GlobalVariableOffsets[name];
    }
    // 变量不存在，返回 0，让调用者处理这种情况
    return 0;
}

int BaseCodeGenerator::GetVariableAbsoluteOffset(const char* name) {
    auto it = m_VariableOffsets.find(name);
    if (it != m_VariableOffsets.end()) {
        return it->second;
    }
    if (m_GlobalVariableOffsets.find(name) != m_GlobalVariableOffsets.end()) {
        return m_GlobalVariableOffsets[name];
    }
    // 变量不存在，返回 0
    return 0;
}

void BaseCodeGenerator::SetInFunction(bool inFunction) {
    m_InFunction = inFunction;
}

bool BaseCodeGenerator::GetInFunction() const {
    return m_InFunction;
}

bool BaseCodeGenerator::VariableExists(const char* name) const {
    return m_VariableOffsets.find(name) != m_VariableOffsets.end() || m_GlobalVariableOffsets.find(name) != m_GlobalVariableOffsets.end();
}

bool BaseCodeGenerator::IsStandardLibraryFunction(const char* name) {
    if (m_Platform) {
        return m_Platform->isStandardLibraryFunction(name);
    }
    return false;
}

size_t BaseCodeGenerator::StoreString(const char* str) {
    size_t offset = m_DataBuffer.size();
    size_t length = strlen(str);
    
    m_DataBuffer.reserve(m_DataBuffer.size() + length + 1 + m_Architecture->getPointerSize());
    
    const char* p = str;
    while (*p) {
        m_DataBuffer.push_back(static_cast<unsigned char>(*p));
        p++;
    }
    
    m_DataBuffer.push_back(0);
    
    while (m_DataBuffer.size() % m_Architecture->getPointerSize() != 0) {
        m_DataBuffer.push_back(0);
    }
    
    m_NextDataOffset = m_DataBuffer.size();
    
    return offset;
}

size_t BaseCodeGenerator::StoreDouble(double value) {
    size_t offset = m_DataBuffer.size();
    
    m_DataBuffer.reserve(m_DataBuffer.size() + 8);
    
    unsigned char* doubleBytes = reinterpret_cast<unsigned char*>(&value);
    for (int i = 0; i < 8; i++) {
        m_DataBuffer.push_back(doubleBytes[i]);
    }
    
    m_NextDataOffset = m_DataBuffer.size();
    
    return offset;
}

#ifdef _WIN32
HMODULE BaseCodeGenerator::GetMsvcrt() {
    if (m_MsvcrtDll == nullptr) {
        m_MsvcrtDll = LoadLibraryA("msvcrt.dll");
        if (m_MsvcrtDll == nullptr) {
            std::cerr << "Failed to load msvcrt.dll" << std::endl;
        }
    }
    return m_MsvcrtDll;
}
#else
void* BaseCodeGenerator::GetMsvcrt() {
    // 在非Windows环境中，直接返回nullptr
    return nullptr;
}
#endif

void BaseCodeGenerator::AddCode(const std::vector<unsigned char>& code) {
    m_CodeBuffer.reserve(m_CodeBuffer.size() + code.size());
    m_CodeBuffer.insert(m_CodeBuffer.end(), code.begin(), code.end());
}

void BaseCodeGenerator::AddCode(std::initializer_list<unsigned char> code) {
    m_CodeBuffer.reserve(m_CodeBuffer.size() + code.size());
    m_CodeBuffer.insert(m_CodeBuffer.end(), code.begin(), code.end());
}

void BaseCodeGenerator::AddCode(char buff[]) {
    int length = 0;
    while (buff[length] != '\0') {
        length++;
    }
    
    m_CodeBuffer.reserve(m_CodeBuffer.size() + length);
    
    for (int i = 0; i < length; i++) {
        m_CodeBuffer.push_back(static_cast<unsigned char>(buff[i]));
    }
}

// 平台抽象层相关方法
void BaseCodeGenerator::setPlatformAbstraction(PlatformAbstraction* platform) {
    m_Platform = platform;
}

PlatformAbstraction* BaseCodeGenerator::getPlatformAbstraction() const {
    return m_Platform;
}

// 获取函数调用记录列表
const std::vector<ICodeGenerator::FunctionCallSite>& BaseCodeGenerator::getFunctionCalls() const {
    return m_FunctionCalls;
}

} // namespace cse