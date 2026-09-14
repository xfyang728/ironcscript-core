#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "../common/AstPool.h"
#include "../common/AstBuilders.h"
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/frontend/semantic/SymbolTable.h"
#include "../src/frontend/parser/node.h"

using namespace cse;

/// 辅助：构造一个包含 main 函数的顶层 NBlock（main 函数体由 funcBody 提供）
static NBlock* buildProgramWithMain(cse_test::AstPool& pool, NBlock* funcBody) {
    auto* topBlock = pool.make<NBlock>();
    auto* func = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, funcBody);
    topBlock->statements.push_back(func);
    return topBlock;
}

TEST(SemanticAnalyzerTest, SimpleProgram) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, VariableDeclaration) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x");
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, VariableInitialization) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NInteger>(10);
    auto* varDecl = cse_test::makeVarDecl(pool, "int", "x", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, DoubleType) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NDouble>(3.14);
    auto* varDecl = cse_test::makeVarDecl(pool, "double", "x", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, CharType) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NInteger>('A');
    auto* varDecl = cse_test::makeVarDecl(pool, "char", "c", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, BoolType) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    auto* expr = pool.make<NInteger>(1);
    auto* varDecl = cse_test::makeVarDecl(pool, "bool", "flag", expr);
    funcBody->statements.push_back(varDecl);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, FunctionDeclaration) {
    cse_test::AstPool pool;
    auto* topBlock = pool.make<NBlock>();

    // 构造 add(int a, int b) 函数
    auto* addBody = cse_test::makeFuncBody(pool);
    VariableList params;
    params.push_back(cse_test::makeVarDecl(pool, "int", "a"));
    params.push_back(cse_test::makeVarDecl(pool, "int", "b"));
    auto* addFunc = cse_test::makeFuncDecl(pool, "int", "add", params, addBody);
    topBlock->statements.push_back(addFunc);

    // 构造 main 函数
    auto* mainBody = cse_test::makeFuncBody(pool);
    auto* mainFunc = cse_test::makeFuncDecl(pool, "int", "main", VariableList{}, mainBody);
    topBlock->statements.push_back(mainFunc);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);
    EXPECT_TRUE(analyzer.analyze(*topBlock));
}

TEST(SemanticAnalyzerTest, UndefinedVariableError) {
    cse_test::AstPool pool;
    auto* funcBody = cse_test::makeFuncBody(pool);
    // 使用未定义变量 y
    auto& yId = cse_test::makeIdent(pool, "y");
    auto* stmt = pool.make<NExpressionStatement>(yId);
    funcBody->statements.push_back(stmt);
    auto* topBlock = buildProgramWithMain(pool, funcBody);

    SymbolTable symtab;
    SemanticAnalyzer analyzer(symtab);

    testing::internal::CaptureStderr();
    bool result = analyzer.analyze(*topBlock);
    std::string err = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(result);  // 有错误
    // 错误消息应包含未定义变量名 y（具体文案依赖 error() 实现）
    EXPECT_THAT(err, testing::HasSubstr("y"));
}