#include "BaseException.h"
#include <sstream>

namespace cse {

BaseException::BaseException(const std::string& message, const std::string& sourceFile, int lineNumber) 
    : m_message(message) {
    if (!sourceFile.empty() && lineNumber > 0) {
        addStackTrace("<unknown>", sourceFile, lineNumber);
    }
}

BaseException::~BaseException() {
}

const std::string& BaseException::getMessage() const {
    return m_message;
}

const std::vector<StackFrame>& BaseException::getStackTrace() const {
    return m_stackTrace;
}

std::string BaseException::getType() const {
    return "BaseException";
}

std::string BaseException::toString() const {
    std::ostringstream oss;
    oss << getType() << ": " << m_message;
    
    if (!m_stackTrace.empty()) {
        oss << "\nStack trace:";
        for (const auto& frame : m_stackTrace) {
            oss << "\n  at " << frame.functionName 
                << " (" << frame.sourceFile << ":" << frame.lineNumber << ")";
        }
    }
    
    return oss.str();
}

void BaseException::addStackTrace(const std::string& functionName, const std::string& sourceFile, int lineNumber) {
    StackFrame frame;
    frame.functionName = functionName;
    frame.sourceFile = sourceFile;
    frame.lineNumber = lineNumber;
    m_stackTrace.push_back(frame);
}

// 派生类实现
RuntimeException::RuntimeException(const std::string& message, const std::string& sourceFile, int lineNumber) 
    : BaseException(message, sourceFile, lineNumber) {
}

std::string RuntimeException::getType() const {
    return "RuntimeException";
}

SyntaxException::SyntaxException(const std::string& message, const std::string& sourceFile, int lineNumber) 
    : BaseException(message, sourceFile, lineNumber) {
}

std::string SyntaxException::getType() const {
    return "SyntaxException";
}

IOException::IOException(const std::string& message, const std::string& sourceFile, int lineNumber) 
    : BaseException(message, sourceFile, lineNumber) {
}

std::string IOException::getType() const {
    return "IOException";
}

} // namespace cse
