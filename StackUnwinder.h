#pragma once

#include <vector>
#include <functional>

namespace cse {

class StackUnwinder {
public:
    using CleanupFunction = std::function<void()>;
    
    StackUnwinder();
    ~StackUnwinder();
    
    // 注册清理函数
    void pushCleanup(const CleanupFunction& cleanup);
    
    // 弹出清理函数
    void popCleanup();
    
    // 展开栈并执行清理
    void unwind();
    
    // 全局栈展开器
    static StackUnwinder& instance();
    
private:
    std::vector<CleanupFunction> m_cleanupStack;
};

} // namespace cse
