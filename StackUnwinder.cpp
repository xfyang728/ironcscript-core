#include "StackUnwinder.h"

namespace cse {

StackUnwinder::StackUnwinder() {
}

StackUnwinder::~StackUnwinder() {
    // 确保所有清理函数都被执行
    unwind();
}

void StackUnwinder::pushCleanup(const CleanupFunction& cleanup) {
    m_cleanupStack.push_back(cleanup);
}

void StackUnwinder::popCleanup() {
    if (!m_cleanupStack.empty()) {
        m_cleanupStack.pop_back();
    }
}

void StackUnwinder::unwind() {
    while (!m_cleanupStack.empty()) {
        // 执行清理函数（不使用异常处理，因为编译时禁用了异常）
        m_cleanupStack.back()();
        m_cleanupStack.pop_back();
    }
}

StackUnwinder& StackUnwinder::instance() {
    static StackUnwinder instance;
    return instance;
}

} // namespace cse
