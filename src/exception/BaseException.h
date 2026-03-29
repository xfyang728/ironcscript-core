#pragma once

#include <string>
#include <vector>
#include <memory>
#include "common/StackFrame.h"

namespace cse {

class BaseException {
public:
    BaseException(const std::string& message, const std::string& sourceFile = "", int lineNumber = -1);
    virtual ~BaseException();
    
    const std::string& getMessage() const;
    const std::vector<StackFrame>& getStackTrace() const;
    
    virtual std::string getType() const;
    virtual std::string toString() const;
    
    void addStackTrace(const std::string& functionName, const std::string& sourceFile, int lineNumber);
    
protected:
    std::string m_message;
    std::vector<StackFrame> m_stackTrace;
};

class RuntimeException : public BaseException {
public:
    RuntimeException(const std::string& message, const std::string& sourceFile = "", int lineNumber = -1);
    std::string getType() const override;
};

class SyntaxException : public BaseException {
public:
    SyntaxException(const std::string& message, const std::string& sourceFile = "", int lineNumber = -1);
    std::string getType() const override;
};

class IOException : public BaseException {
public:
    IOException(const std::string& message, const std::string& sourceFile = "", int lineNumber = -1);
    std::string getType() const override;
};

} // namespace cse
