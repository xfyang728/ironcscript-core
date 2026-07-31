#ifndef CSE_TEST_AST_POOL_H
#define CSE_TEST_AST_POOL_H

#include <memory>
#include <vector>
#include "../src/frontend/parser/node.h"

namespace cse_test {

/**
 * @brief AST 节点所有权池，用于测试中统一管理节点生命周期
 *
 * - make<T>: 池持有所有权，测试结束统一释放
 * - makeBorrowed<T>: 释放所有权给调用方（如 NFunctionDeclaration 的 block，
 *   会被 NFunctionDeclaration 析构 delete，pool 不再持有避免 double free）
 */
class AstPool {
    std::vector<std::unique_ptr<cse::Node>> owned_;
public:
    AstPool() = default;
    AstPool(const AstPool&) = delete;
    AstPool& operator=(const AstPool&) = delete;

    /// 池持有所有权，测试结束统一释放
    template<typename T, typename... Args>
    T* make(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        auto* raw = ptr.get();
        owned_.push_back(std::move(ptr));
        return raw;
    }

    /// 释放所有权给调用方（用于会被其他节点析构 delete 的对象）
    template<typename T, typename... Args>
    T* makeBorrowed(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        auto* raw = ptr.get();
        ptr.release();  // 不持有所有权，交给持有节点管理
        return raw;
    }

    ~AstPool() = default;  // owned_ 自动释放，borrowed 的由持有节点析构
};

} // namespace cse_test

#endif // CSE_TEST_AST_POOL_H