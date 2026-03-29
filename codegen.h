#ifndef CSE_CODEGEN_H
#define CSE_CODEGEN_H

#include <string>
#include "BaseCodeGenerator.h"

namespace cse {

#ifndef CSE_PLATFORM_EMBEDDED
class X64Code;
#endif

enum class ReturnType {
    Integer,
    Float,
    Double
};

class CodeGenContext {
	BaseCodeGenerator* m_Code;
	ReturnType m_MainReturnType = ReturnType::Integer;

public:
	CodeGenContext();

	void setMainReturnType(ReturnType type) { m_MainReturnType = type; }
	ReturnType getMainReturnType() const { return m_MainReturnType; }

	int runCode();
	BaseCodeGenerator* getCodeGenerator(const std::string& platform = PLATFORM_X86_64);

#ifndef CSE_PLATFORM_EMBEDDED
	X64Code* getX64CodeGenerator();
#endif
};

} // namespace cse

#endif // CSE_CODEGEN_H
