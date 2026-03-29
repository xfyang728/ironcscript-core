#include "ExceptionHandler.h"
#include <iostream>

namespace cse {

ExceptionHandler::ExceptionHandler() {
}

ExceptionHandler::~ExceptionHandler() {
}

void ExceptionHandler::registerHandler(const ExceptionFilter& filter, const ExceptionCallback& callback) {
    CatchBlock block;
    block.filter = filter;
    block.callback = callback;
    m_handlers.push_back(block);
}

bool ExceptionHandler::catchException(const BaseException& exception) {
    for (const auto& block : m_handlers) {
        if (block.filter(exception)) {
            block.callback(exception);
            return true;
        }
    }
    return false;
}

void ExceptionHandler::handleUncaughtException(const BaseException& exception) {
    std::cerr << "Uncaught exception: " << exception.toString() << std::endl;
    // 这里可以添加更多处理逻辑，比如记录日志、生成崩溃报告等
}

ExceptionHandler& ExceptionHandler::instance() {
    static ExceptionHandler instance;
    return instance;
}

} // namespace cse
