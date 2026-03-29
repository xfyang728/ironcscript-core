#pragma once

#include "BaseException.h"
#include <functional>
#include <vector>

namespace cse {

class ExceptionHandler {
public:
    using ExceptionCallback = std::function<void(const BaseException&)>;
    using ExceptionFilter = std::function<bool(const BaseException&)>;
    
    struct CatchBlock {
        ExceptionFilter filter;
        ExceptionCallback callback;
    };
    
    ExceptionHandler();
    ~ExceptionHandler();
    
    // 注册异常处理器
    void registerHandler(const ExceptionFilter& filter, const ExceptionCallback& callback);
    
    // 捕获异常
    bool catchException(const BaseException& exception);
    
    // 处理未捕获的异常
    void handleUncaughtException(const BaseException& exception);
    
    // 全局异常处理器
    static ExceptionHandler& instance();
    
private:
    std::vector<CatchBlock> m_handlers;
};

} // namespace cse
