#ifndef CSE_TEST_AST_BUILDERS_H
#define CSE_TEST_AST_BUILDERS_H

#include "AstPool.h"
#include "../src/frontend/parser/node.h"

namespace cse_test {

/// 创建 NIdentifier（pool 持有所有权），返回引用
inline cse::NIdentifier& makeIdent(AstPool& pool, const std::string& name) {
    return *pool.make<cse::NIdentifier>(name);
}

/// 创建 NVariableDeclaration（pool 持有所有权）
/// 用法: makeVarDecl(pool, "int", "x", pool.make<cse::NInteger>(42))
inline cse::NVariableDeclaration* makeVarDecl(AstPool& pool,
                                               const std::string& type,
                                               const std::string& name,
                                               cse::NExpression* expr = nullptr) {
    auto& typeId = makeIdent(pool, type);
    auto& nameId = makeIdent(pool, name);
    return pool.make<cse::NVariableDeclaration>(typeId, nameId, expr);
}

/// 创建 NBlock 作为函数体（pool 不持有所有权，由 NFunctionDeclaration 析构 delete）
inline cse::NBlock* makeFuncBody(AstPool& pool) {
    return pool.makeBorrowed<cse::NBlock>();
}

/// 创建 NFunctionDeclaration（pool 持有 NFunctionDeclaration 本身；
/// block 由 makeFuncBody 创建的 borrowed NBlock 传入，NFunctionDeclaration 析构会 delete 它）
inline cse::NFunctionDeclaration* makeFuncDecl(AstPool& pool,
                                                const std::string& retType,
                                                const std::string& name,
                                                cse::VariableList args,
                                                cse::NBlock* block) {
    auto& typeId = makeIdent(pool, retType);
    auto& nameId = makeIdent(pool, name);
    return pool.make<cse::NFunctionDeclaration>(typeId, nameId, args, block);
}

} // namespace cse_test

#endif // CSE_TEST_AST_BUILDERS_H