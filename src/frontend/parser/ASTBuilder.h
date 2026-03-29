#ifndef CSE_AST_BUILDER_H
#define CSE_AST_BUILDER_H

#include "frontend/parser/node.h"
#include "frontend/generated/CScriptParser.h"
#include "frontend/generated/CScriptVisitor.h"
#include "frontend/parser/tokens.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cstdlib>

namespace cse {

template<typename T>
T* safe_any_cast(const antlrcpp::Any& anyVal) {
    try {
        if (anyVal.type() == typeid(T*)) {
            return std::any_cast<T*>(anyVal);
        }
        if (anyVal.type() == typeid(NIdentifier*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NIdentifier*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NInteger*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NInteger*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NDouble*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NDouble*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NString*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NString*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NBinaryOperator*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NBinaryOperator*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NTernaryOperator*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NTernaryOperator*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NUnaryOperator*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NUnaryOperator*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NAssignment*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NAssignment*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NMethodCall*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NMethodCall*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NArrayAccess*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NArrayAccess*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NMemberAccess*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NMemberAccess*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NCastOperator*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NCastOperator*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NBlock*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NBlock*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NVariableDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NVariableDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NArrayDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NArrayDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NPointerDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NPointerDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NExpressionStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NExpressionStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NReturnStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NReturnStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NExternDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NExternDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NBreakStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NBreakStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NContinueStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NContinueStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NIfStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NIfStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NFunctionDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NFunctionDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NWhileStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NWhileStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NForStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NForStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NDoWhileStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NDoWhileStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NCaseStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NCaseStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NDefaultStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NDefaultStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NSwitchStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NSwitchStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NEnumDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NEnumDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NStructDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NStructDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NUnionDeclaration*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NUnionDeclaration*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NRegisterCallbackStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NRegisterCallbackStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NTryCatchStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NTryCatchStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NThrowExpression*)) {
            if constexpr (std::is_base_of_v<NExpression, T>) {
                return dynamic_cast<T*>(std::any_cast<NThrowExpression*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NEnumItem*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NEnumItem*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NImportStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NImportStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NIncludeStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NIncludeStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NCatchBlock*)) {
            return dynamic_cast<T*>(std::any_cast<NCatchBlock*>(anyVal));
        }
        return nullptr;
    } catch(...) {
        return nullptr;
    }
}

template<typename T>
T safe_any_cast_value(const antlrcpp::Any& anyVal) {
    try {
        if (!anyVal.has_value()) {
            return T();
        }
        void* ptr = std::any_cast<T>(&const_cast<antlrcpp::Any&>(anyVal));
        return ptr ? *static_cast<T*>(ptr) : T();
    } catch(...) {
        return T();
    }
}

class ASTBuilder : public CScriptVisitor {
public:
    ASTBuilder() {}
    ~ASTBuilder() {}

    NBlock* build(CScriptParser::ProgramContext* ctx) {
        auto result = visitProgram(ctx);
        NBlock* block = safe_any_cast<NBlock>(result);
        return block;
    }

    antlrcpp::Any visitProgram(CScriptParser::ProgramContext* ctx) override {
        NBlock* block = new NBlock();
        auto stmts = ctx->stmt();
        std::cout << "[DEBUG] visitProgram: found " << stmts.size() << " statements" << std::endl;
        for (auto stmt : stmts) {
            std::cout << "[DEBUG] visitProgram: processing statement" << std::endl;
            auto result = visitStmt(stmt);
            std::cout << "[DEBUG] visitProgram: result has value: " << result.has_value() << std::endl;
            if (result.has_value()) {
                NStatement* s = safe_any_cast<NStatement>(result);
                std::cout << "[DEBUG] visitProgram: s is null: " << (s == nullptr) << std::endl;
                if (s) {
                    block->statements.push_back(s);
                    std::cout << "[DEBUG] visitProgram: added statement to block" << std::endl;
                }
            }
        }
        std::cout << "[DEBUG] visitProgram: block has " << block->statements.size() << " statements" << std::endl;
        return antlrcpp::Any(block);
    }

    antlrcpp::Any visitStmt(CScriptParser::StmtContext* ctx) override {
        std::cout << "[DEBUG] visitStmt: entered" << std::endl;
        if (ctx->var_decl()) {
            std::cout << "[DEBUG] visitStmt: found var_decl" << std::endl;
            return visitVar_decl(ctx->var_decl());
        }
        if (ctx->func_decl()) {
            std::cout << "[DEBUG] visitStmt: found func_decl" << std::endl;
            return visitFunc_decl(ctx->func_decl());
        }
        if (ctx->extern_decl()) {
            std::cout << "[DEBUG] visitStmt: found extern_decl" << std::endl;
            return visitExtern_decl(ctx->extern_decl());
        }
        if (ctx->struct_decl()) {
            std::cout << "[DEBUG] visitStmt: found struct_decl" << std::endl;
            return visitStruct_decl(ctx->struct_decl());
        }
        if (ctx->enum_decl()) {
            std::cout << "[DEBUG] visitStmt: found enum_decl" << std::endl;
            return visitEnum_decl(ctx->enum_decl());
        }
        if (ctx->if_stmt()) {
            std::cout << "[DEBUG] visitStmt: found if_stmt" << std::endl;
            return visitIf_stmt(ctx->if_stmt());
        }
        if (ctx->while_stmt()) {
            std::cout << "[DEBUG] visitStmt: found while_stmt" << std::endl;
            return visitWhile_stmt(ctx->while_stmt());
        }
        if (ctx->for_stmt()) {
            std::cout << "[DEBUG] visitStmt: found for_stmt" << std::endl;
            return visitFor_stmt(ctx->for_stmt());
        }
        if (ctx->switch_stmt()) {
            std::cout << "[DEBUG] visitStmt: found switch_stmt" << std::endl;
            return visitSwitch_stmt(ctx->switch_stmt());
        }
        if (ctx->do_while_stmt()) {
            std::cout << "[DEBUG] visitStmt: found do_while_stmt" << std::endl;
            return visitDo_while_stmt(ctx->do_while_stmt());
        }
        if (ctx->try_catch_stmt()) {
            std::cout << "[DEBUG] visitStmt: found try_catch_stmt" << std::endl;
            return visitTry_catch_stmt(ctx->try_catch_stmt());
        }
        if (ctx->register_callback_stmt()) {
            std::cout << "[DEBUG] visitStmt: found register_callback_stmt" << std::endl;
            return visitRegister_callback_stmt(ctx->register_callback_stmt());
        }
        if (ctx->import_stmt()) {
            std::cout << "[DEBUG] visitStmt: found import_stmt" << std::endl;
            return visitImport_stmt(ctx->import_stmt());
        }
        if (ctx->include_stmt()) {
            std::cout << "[DEBUG] visitStmt: found include_stmt" << std::endl;
            return visitInclude_stmt(ctx->include_stmt());
        }
        if (ctx->RETURN() && ctx->expr()) {
            std::cout << "[DEBUG] visitStmt: found return statement" << std::endl;
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NReturnStatement(*expr));
            }
        }
        if (ctx->BREAK()) {
            std::cout << "[DEBUG] visitStmt: found break statement" << std::endl;
            return antlrcpp::Any(new NBreakStatement());
        }
        if (ctx->CONTINUE()) {
            std::cout << "[DEBUG] visitStmt: found continue statement" << std::endl;
            return antlrcpp::Any(new NContinueStatement());
        }
        if (ctx->MUL() && ctx->ident() && ctx->expr()) {
            std::cout << "[DEBUG] visitStmt: found pointer assignment" << std::endl;
            auto* id = new NIdentifier(ctx->ident()->getText());
            auto result = visitExpr(ctx->expr());
            NExpression* val = safe_any_cast<NExpression>(result);
            if (val) {
                return antlrcpp::Any(new NExpressionStatement(*new NAssignment(*new NUnaryOperator(CScriptParser::MUL, *id), *val)));
            }
        }
        if (ctx->expr()) {
            std::cout << "[DEBUG] visitStmt: found expression statement" << std::endl;
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NExpressionStatement(*expr));
            }
        }
        std::cout << "[DEBUG] visitStmt: returning nullptr" << std::endl;
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitVar_decl(CScriptParser::Var_declContext* ctx) override {
        std::string typeStr;
        if (ctx->type() && ctx->type()->ENUM_KW()) {
            typeStr = ctx->type()->IDENTIFIER()->getText();
        } else if (ctx->type()) {
            typeStr = ctx->type()->getText();
        }

        if (ctx->LBRACKET()) {
            std::string name;
            if (ctx->ident().size() > 0 && ctx->ident(0)->IDENTIFIER()) {
                name = ctx->ident(0)->IDENTIFIER()->getText();
            }

            NExpression* sizeExpr = nullptr;
            if (ctx->expr()) {
                auto sizeResult = visitExpr(ctx->expr());
                sizeExpr = safe_any_cast<NExpression>(sizeResult);
            }

            auto* typeIdPtr = new NIdentifier(typeStr);
            auto* nameIdPtr = new NIdentifier(name);

            ExpressionList* initList = nullptr;
            if (ctx->init_list()) {
                initList = new ExpressionList();
                for (auto initCtx : ctx->init_list()->expr()) {
                    auto initResult = visitExpr(initCtx);
                    NExpression* initExpr = safe_any_cast<NExpression>(initResult);
                    if (initExpr) {
                        initList->push_back(initExpr);
                    }
                }
            }

            auto* arrayDecl = new NArrayDeclaration(*typeIdPtr, *nameIdPtr, sizeExpr, initList);
            return antlrcpp::Any(arrayDecl);
        }

        if (ctx->STRUCT_KW()) {
            std::string structName, varName;
            if (ctx->ident().size() >= 2) {
                if (ctx->ident(0) && ctx->ident(0)->IDENTIFIER()) {
                    structName = ctx->ident(0)->IDENTIFIER()->getText();
                }
                if (ctx->ident(1) && ctx->ident(1)->IDENTIFIER()) {
                    varName = ctx->ident(1)->IDENTIFIER()->getText();
                }
            }

            auto* typeIdPtr = new NIdentifier("struct " + structName);
            auto* nameIdPtr = new NIdentifier(varName);

            NExpression* initExpr = nullptr;
            if (ctx->expr()) {
                auto result = visitExpr(ctx->expr());
                initExpr = safe_any_cast<NExpression>(result);
            }

            auto* varDecl = new NVariableDeclaration(*typeIdPtr, *nameIdPtr, initExpr);
            if (ctx->CONST_KW()) {
                varDecl->isConst = true;
            }
            return antlrcpp::Any(varDecl);
        }

        if (typeStr.find('*') != std::string::npos || ctx->MUL()) {
            std::string name;
            if (ctx->ident().size() > 0 && ctx->ident(0)->IDENTIFIER()) {
                name = ctx->ident(0)->IDENTIFIER()->getText();
            }

            std::string baseType = typeStr;
            if (ctx->MUL()) {
                baseType = typeStr + "*";
            }

            auto* typeIdPtr = new NIdentifier(baseType);
            auto* nameIdPtr = new NIdentifier(name);

            auto* pointerDecl = new NPointerDeclaration(*typeIdPtr, *nameIdPtr);

            if (ctx->expr()) {
                auto result = visitExpr(ctx->expr());
                pointerDecl->assignmentExpr = safe_any_cast<NExpression>(result);
            }

            return antlrcpp::Any(pointerDecl);
        }

        std::string name;
        if (ctx->ident().size() > 0 && ctx->ident(0) && ctx->ident(0)->IDENTIFIER()) {
            name = ctx->ident(0)->IDENTIFIER()->getText();
        }

        auto* typeIdPtr = new NIdentifier(typeStr);
        auto* nameIdPtr = new NIdentifier(name);

        NVariableDeclaration* var = new NVariableDeclaration(*typeIdPtr, *nameIdPtr);

        if (ctx->CONST_KW()) {
            var->isConst = true;
        }

        if (ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            var->assignmentExpr = safe_any_cast<NExpression>(result);
        }

        return antlrcpp::Any(var);
    }

    antlrcpp::Any visitType(CScriptParser::TypeContext* ctx) override {
        return antlrcpp::Any(ctx->getText());
    }

    antlrcpp::Any visitExpr(CScriptParser::ExprContext* ctx) override {

        if (ctx->or_expr() && ctx->QUESTION() != nullptr) {
            std::vector<CScriptParser::ExprContext*> exprs = ctx->expr();
            if (exprs.size() >= 2) {
                auto condResult = visitOr_expr(ctx->or_expr());
                NExpression* condition = safe_any_cast<NExpression>(condResult);
                if (condition) {
                    auto trueResult = visitExpr(exprs[0]);
                    NExpression* trueExpr = safe_any_cast<NExpression>(trueResult);
                    auto falseResult = visitExpr(exprs[1]);
                    NExpression* falseExpr = safe_any_cast<NExpression>(falseResult);
                    if (trueExpr && falseExpr) {
                        auto* ternOp = new NTernaryOperator(*condition, *trueExpr, *falseExpr);
                        return antlrcpp::Any(ternOp);
                    }
                }
            }
        }

        if (ctx->primary_expr() != nullptr && ctx->DOT() != nullptr && ctx->ident() != nullptr && ctx->ASSIGN() != nullptr) {
            auto objResult = visitPrimary_expr(ctx->primary_expr());
            NExpression* objExpr = safe_any_cast<NExpression>(objResult);
            auto* memberId = new NIdentifier(ctx->ident()->getText());
            auto valResult = visitExpr(ctx->expr(0));
            NExpression* valExpr = safe_any_cast<NExpression>(valResult);
            if (objExpr && valExpr) {
                auto* memberAccess = new NMemberAccess(*objExpr, *memberId);
                return antlrcpp::Any(new NAssignment(*memberAccess, *valExpr));
            }
        }

        if (ctx->ident() != nullptr && ctx->LBRACKET() != nullptr && ctx->expr().size() >= 2) {
            auto* id = new NIdentifier(ctx->ident()->getText());
            auto indexResult = visitExpr(ctx->expr(0));
            NExpression* index = safe_any_cast<NExpression>(indexResult);
            auto valueResult = visitExpr(ctx->expr(1));
            NExpression* value = safe_any_cast<NExpression>(valueResult);
            if (index && value) {
                auto* arrayAccess = new NArrayAccess(*id, *index);
                return antlrcpp::Any(new NAssignment(*arrayAccess, *value));
            }
        }

        if (ctx->ident() != nullptr) {
            std::vector<CScriptParser::ExprContext*> identExprs = ctx->expr();
            if (!identExprs.empty()) {
                auto* id = new NIdentifier(ctx->ident()->getText());
                auto result = visitExpr(identExprs[0]);
                NExpression* val = safe_any_cast<NExpression>(result);
                if (val) {
                    if (ctx->PLUS_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::PLUS, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->MINUS_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::MINUS, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->MUL_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::MUL, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->DIV_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::DIV, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->MOD_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::MOD, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    return antlrcpp::Any(new NAssignment(*id, *val));
                }
            }
        }

        if (ctx->or_expr()) {
            return visitOr_expr(ctx->or_expr());
        }
        if (ctx->type()) {
            std::vector<CScriptParser::ExprContext*> typeExprs = ctx->expr();
            if (!typeExprs.empty()) {
                std::string typeStr = ctx->type()->getText();
                auto result = visitExpr(typeExprs[0]);
                NExpression* innerExpr = safe_any_cast<NExpression>(result);
                if (innerExpr) {
                    return antlrcpp::Any(new NCastOperator(typeStr, *innerExpr));
                }
            }
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitPrimary_expr(CScriptParser::Primary_exprContext* ctx) override {
        if (ctx->ident().size() > 0) {
            if (ctx->LPAREN()) {
                std::string funcName = ctx->ident(0)->getText();
                auto* funcId = new NIdentifier(funcName);
                ExpressionList args;
                if (ctx->call_args()) {
                    for (auto exprCtx : ctx->call_args()->expr()) {
                        auto argResult = visitExpr(exprCtx);
                        NExpression* arg = safe_any_cast<NExpression>(argResult);
                        if (arg) {
                            args.push_back(arg);
                        }
                    }
                }
                return antlrcpp::Any(new NMethodCall(*funcId, args));
            }
            if (ctx->LBRACKET() && ctx->expr()) {
                auto result = visitExpr(ctx->expr());
                NExpression* index = safe_any_cast<NExpression>(result);
                auto* arrId = new NIdentifier(ctx->ident(0)->getText());
                if (index) {
                    return antlrcpp::Any(new NArrayAccess(*arrId, *index));
                }
            }
            if (ctx->DOT() && ctx->ident().size() >= 2) {
                auto* objId = new NIdentifier(ctx->ident(0)->getText());
                auto* memberId = new NIdentifier(ctx->ident(1)->getText());
                return antlrcpp::Any(new NMemberAccess(*objId, *memberId));
            }
            if (ctx->ident().size() >= 2) {
                auto* objId = new NIdentifier(ctx->ident(0)->getText());
                auto* memberId = new NIdentifier(ctx->ident(1)->getText());
                return antlrcpp::Any(new NMemberAccess(*objId, *memberId));
            }
            if (ctx->INC() && ctx->INC()->getSymbol()->getType() == TINC) {
                auto* id = new NIdentifier(ctx->ident(0)->getText());
                return antlrcpp::Any(new NUnaryOperator(CScriptParser::INC, *id));
            }
            if (ctx->DEC() && ctx->DEC()->getSymbol()->getType() == TDEC) {
                auto* id = new NIdentifier(ctx->ident(0)->getText());
                return antlrcpp::Any(new NUnaryOperator(CScriptParser::DEC, *id));
            }
            return antlrcpp::Any(new NIdentifier(ctx->ident(0)->getText()));
        }
        if (ctx->numeric()) {
            return visitNumeric(ctx->numeric());
        }
        if (ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            return antlrcpp::Any(expr);
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitNumeric(CScriptParser::NumericContext* ctx) override {
        if (ctx->STRING()) {
            std::string strVal = ctx->STRING()->getText();
            if (strVal.size() >= 2) {
                strVal = strVal.substr(1, strVal.size() - 2);
            }
            std::string processedStr;
            for (size_t i = 0; i < strVal.size(); i++) {
                if (strVal[i] == '\\' && i + 1 < strVal.size()) {
                    switch (strVal[i + 1]) {
                        case 'n': processedStr += '\n'; i++; break;
                        case 't': processedStr += '\t'; i++; break;
                        case 'r': processedStr += '\r'; i++; break;
                        case '\\': processedStr += '\\'; i++; break;
                        case '"': processedStr += '"'; i++; break;
                        case '0': processedStr += '\0'; i++; break;
                        default: processedStr += strVal[i]; break;
                    }
                } else {
                    processedStr += strVal[i];
                }
            }
            return antlrcpp::Any(new NString(processedStr));
        }
        if (ctx->INTEGER()) {
            return antlrcpp::Any(new NInteger(strtoll(ctx->INTEGER()->getText().c_str(), nullptr, 10)));
        }
        if (ctx->DOUBLE()) {
            return antlrcpp::Any(new NDouble(strtod(ctx->DOUBLE()->getText().c_str(), nullptr)));
        }
        if (ctx->CHAR()) {
            std::string charStr = ctx->CHAR()->getText();
            char value;
            if (charStr.length() >= 3 && charStr[1] == '\\') {
                switch(charStr[2]) {
                    case 'n': value = '\n'; break;
                    case 't': value = '\t'; break;
                    case 'r': value = '\r'; break;
                    case '\\': value = '\\'; break;
                    case '\'': value = '\''; break;
                    default: value = charStr[2]; break;
                }
            } else if (charStr.length() >= 2) {
                value = charStr[1];
            } else {
                value = 0;
            }
            return antlrcpp::Any(new NInteger(static_cast<long long>(value)));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitMul_expr(CScriptParser::Mul_exprContext* ctx) override {
        if (ctx->mul_expr() && ctx->unary_expr()) {
            auto leftResult = visitMul_expr(ctx->mul_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitUnary_expr(ctx->unary_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                if (ctx->MUL()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::MUL, *right));
                }
                if (ctx->DIV()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::DIV, *right));
                }
                if (ctx->MOD()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::MOD, *right));
                }
            }
        }
        if (ctx->unary_expr()) {
            return visitUnary_expr(ctx->unary_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitUnary_expr(CScriptParser::Unary_exprContext* ctx) override {
        if (ctx->primary_expr()) {
            auto result = visitPrimary_expr(ctx->primary_expr());
            NExpression* primaryResult = safe_any_cast<NExpression>(result);
            if (primaryResult) {
                if (ctx->MINUS()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::MINUS, *primaryResult));
                }
                if (ctx->PLUS()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::PLUS, *primaryResult));
                }
                if (ctx->NOT()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::NOT, *primaryResult));
                }
                if (ctx->NOTBIT()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::NOTBIT, *primaryResult));
                }
                if (ctx->MUL()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::MUL, *primaryResult));
                }
                if (ctx->BITAND()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::BITAND, *primaryResult));
                }
                return antlrcpp::Any(primaryResult);
            }
            return antlrcpp::Any(nullptr);
        }
        if (ctx->unary_expr()) {
            auto result = visitUnary_expr(ctx->unary_expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                if (ctx->INC()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::INC, *expr));
                }
                if (ctx->DEC()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::DEC, *expr));
                }
                if (ctx->NOT()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::NOT, *expr));
                }
                if (ctx->NOTBIT()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::NOTBIT, *expr));
                }
                if (ctx->MINUS()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::MINUS, *expr));
                }
                if (ctx->PLUS()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::PLUS, *expr));
                }
                if (ctx->MUL()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::MUL, *expr));
                }
                if (ctx->BITAND()) {
                    return antlrcpp::Any(new NUnaryOperator(CScriptParser::BITAND, *expr));
                }
            }
        }
        if (ctx->THROW() && ctx->expr()) {
            std::cout << "[DEBUG] visitUnary_expr: found throw expression" << std::endl;
            auto exprResult = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(exprResult);
            if (expr) {
                return antlrcpp::Any(new NThrowExpression(expr));
            }
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitAdd_expr(CScriptParser::Add_exprContext* ctx) override {
        if (ctx->add_expr() && ctx->mul_expr()) {
            auto leftResult = visitAdd_expr(ctx->add_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitMul_expr(ctx->mul_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                if (ctx->PLUS()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::PLUS, *right));
                }
                if (ctx->MINUS()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::MINUS, *right));
                }
            }
        }
        if (ctx->mul_expr()) {
            return visitMul_expr(ctx->mul_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitShift_expr(CScriptParser::Shift_exprContext* ctx) override {
        if (ctx->shift_expr() && ctx->add_expr()) {
            auto leftResult = visitShift_expr(ctx->shift_expr());
            auto rightResult = visitAdd_expr(ctx->add_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                if (ctx->LSHIFT()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::LSHIFT, *right));
                }
                if (ctx->RSHIFT()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::RSHIFT, *right));
                }
            }
        }
        if (ctx->add_expr()) {
            return visitAdd_expr(ctx->add_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitRel_expr(CScriptParser::Rel_exprContext* ctx) override {
        if (ctx->rel_expr() && ctx->shift_expr()) {
            auto leftResult = visitRel_expr(ctx->rel_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitShift_expr(ctx->shift_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                if (ctx->LT()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::LT, *right));
                }
                if (ctx->GT()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::GT, *right));
                }
                if (ctx->LTE()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::LTE, *right));
                }
                if (ctx->GTE()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::GTE, *right));
                }
            }
        }
        if (ctx->shift_expr()) {
            return visitShift_expr(ctx->shift_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitEq_expr(CScriptParser::Eq_exprContext* ctx) override {
        if (ctx->eq_expr() && ctx->rel_expr()) {
            auto leftResult = visitEq_expr(ctx->eq_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitRel_expr(ctx->rel_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                if (ctx->EQ()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::EQ, *right));
                }
                if (ctx->NEQ()) {
                    return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::NEQ, *right));
                }
            }
        }
        if (ctx->rel_expr()) {
            return visitRel_expr(ctx->rel_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitBit_and_expr(CScriptParser::Bit_and_exprContext* ctx) override {
        if (ctx->bit_and_expr() && ctx->eq_expr()) {
            auto leftResult = visitBit_and_expr(ctx->bit_and_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitEq_expr(ctx->eq_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::BITAND, *right));
            }
        }
        if (ctx->eq_expr()) {
            return visitEq_expr(ctx->eq_expr());
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitBit_xor_expr(CScriptParser::Bit_xor_exprContext* ctx) override {
        if (ctx->bit_xor_expr() && ctx->bit_and_expr()) {
            auto leftResult = visitBit_xor_expr(ctx->bit_xor_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitBit_and_expr(ctx->bit_and_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::XOR, *right));
            }
        }
        if (ctx->bit_and_expr()) {
            auto result = visitBit_and_expr(ctx->bit_and_expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            return antlrcpp::Any(expr);
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitBit_or_expr(CScriptParser::Bit_or_exprContext* ctx) override {
        if (ctx->bit_or_expr() && ctx->bit_xor_expr()) {
            auto leftResult = visitBit_or_expr(ctx->bit_or_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitBit_xor_expr(ctx->bit_xor_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::BITOR, *right));
            }
        }
        if (ctx->bit_xor_expr()) {
            auto result = visitBit_xor_expr(ctx->bit_xor_expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            return antlrcpp::Any(expr);
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitAnd_expr(CScriptParser::And_exprContext* ctx) override {
        if (ctx->and_expr() && ctx->bit_or_expr()) {
            auto leftResult = visitAnd_expr(ctx->and_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitBit_or_expr(ctx->bit_or_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::AND, *right));
            }
        }
        if (ctx->bit_or_expr()) {
            auto result = visitBit_or_expr(ctx->bit_or_expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            return antlrcpp::Any(expr);
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitOr_expr(CScriptParser::Or_exprContext* ctx) override {
        if (ctx->or_expr() && ctx->and_expr()) {
            auto leftResult = visitOr_expr(ctx->or_expr());
            NExpression* left = safe_any_cast<NExpression>(leftResult);
            auto rightResult = visitAnd_expr(ctx->and_expr());
            NExpression* right = safe_any_cast<NExpression>(rightResult);
            if (left && right) {
                return antlrcpp::Any(new NBinaryOperator(*left, CScriptParser::OR, *right));
            }
        }
        if (ctx->and_expr()) {
            auto result = visitAnd_expr(ctx->and_expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            return antlrcpp::Any(expr);
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitBlock(CScriptParser::BlockContext* ctx) override {
        NBlock* block = new NBlock();
        for (auto stmt : ctx->stmt()) {
            auto result = visitStmt(stmt);
            NStatement* s = safe_any_cast<NStatement>(result);
            if (s) {
                block->statements.push_back(s);
            }
        }
        return antlrcpp::Any(block);
    }

    antlrcpp::Any visitIf_stmt(CScriptParser::If_stmtContext* ctx) override {
        auto condResult = visitExpr(ctx->expr());
        NExpression* condition = safe_any_cast<NExpression>(condResult);
        auto thenResult = visitBlock(ctx->block(0));
        NBlock* thenBlock = safe_any_cast<NBlock>(thenResult);

        NBlock* elseBlock = nullptr;
        if (ctx->block().size() > 1) {
            auto elseResult = visitBlock(ctx->block(1));
            elseBlock = safe_any_cast<NBlock>(elseResult);
        }

        if (condition && thenBlock) {
            return antlrcpp::Any(new NIfStatement(*condition, *thenBlock, elseBlock));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitWhile_stmt(CScriptParser::While_stmtContext* ctx) override {
        auto condResult = visitExpr(ctx->expr());
        NExpression* condition = safe_any_cast<NExpression>(condResult);
        auto bodyResult = visitBlock(ctx->block());
        NBlock* body = safe_any_cast<NBlock>(bodyResult);

        if (condition && body) {
            return antlrcpp::Any(new NWhileStatement(*condition, *body));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitFor_stmt(CScriptParser::For_stmtContext* ctx) override {
        NStatement* initStmt = nullptr;

        if (ctx->for_init()) {
            if (ctx->for_init()->var_decl()) {
                auto varResult = visitVar_decl(ctx->for_init()->var_decl());
                initStmt = safe_any_cast<NVariableDeclaration>(varResult);
            } else if (ctx->for_init()->expr()) {
                auto exprResult = visitExpr(ctx->for_init()->expr());
                NExpression* initExpr = safe_any_cast<NExpression>(exprResult);
                if (initExpr) {
                    initStmt = new NExpressionStatement(*initExpr);
                }
            }
        }

        NExpression* condition = nullptr;
        if (ctx->for_cond() && ctx->for_cond()->expr()) {
            auto condResult = visitExpr(ctx->for_cond()->expr());
            condition = safe_any_cast<NExpression>(condResult);
        }

        NExpression* update = nullptr;
        if (ctx->for_incr() && ctx->for_incr()->expr()) {
            auto incrResult = visitExpr(ctx->for_incr()->expr());
            update = safe_any_cast<NExpression>(incrResult);
        }

        auto bodyResult = visitBlock(ctx->block());
        NBlock* body = safe_any_cast<NBlock>(bodyResult);

        if (body) {
            return antlrcpp::Any(new NForStatement(initStmt, condition, update, *body));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitDo_while_stmt(CScriptParser::Do_while_stmtContext* ctx) override {
        auto bodyResult = visitBlock(ctx->block());
        NBlock* body = safe_any_cast<NBlock>(bodyResult);
        auto condResult = visitExpr(ctx->expr());
        NExpression* condition = safe_any_cast<NExpression>(condResult);

        if (body && condition) {
            return antlrcpp::Any(new NDoWhileStatement(*body, *condition));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitFunc_decl(CScriptParser::Func_declContext* ctx) override {
        std::cout << "[DEBUG] visitFunc_decl: entered" << std::endl;
        std::string retType = "int";
        if (ctx->type() && ctx->type()->IDENTIFIER()) {
            retType = ctx->type()->IDENTIFIER()->getText();
            std::cout << "[DEBUG] visitFunc_decl: retType = " << retType << std::endl;
        } else {
            std::cout << "[DEBUG] visitFunc_decl: no type or IDENTIFIER" << std::endl;
        }
        std::string name = "unknown";
        if (ctx->ident() && ctx->ident()->IDENTIFIER()) {
            name = ctx->ident()->IDENTIFIER()->getText();
            std::cout << "[DEBUG] visitFunc_decl: name = " << name << std::endl;
        } else {
            std::cout << "[DEBUG] visitFunc_decl: no ident or IDENTIFIER" << std::endl;
        }

        if (ctx->block()) {
            std::cout << "[DEBUG] visitFunc_decl: found block" << std::endl;
            auto bodyResult = visitBlock(ctx->block());
            std::cout << "[DEBUG] visitFunc_decl: bodyResult has value: " << bodyResult.has_value() << std::endl;
            NBlock* body = safe_any_cast<NBlock>(bodyResult);
            std::cout << "[DEBUG] visitFunc_decl: body = " << body << std::endl;
            if (body) {
                VariableList args;
                if (ctx->func_decl_args()) {
                    std::cout << "[DEBUG] visitFunc_decl: found func_decl_args" << std::endl;
                    for (auto vd : ctx->func_decl_args()->var_decl()) {
                        std::string argType = "int";
                        if (vd->type() && vd->type()->IDENTIFIER()) {
                            argType = vd->type()->IDENTIFIER()->getText();
                        }
                        std::string argName = "";
                        if (vd->ident().size() > 0 && vd->ident(0)->IDENTIFIER()) {
                            argName = vd->ident(0)->IDENTIFIER()->getText();
                        }
                        auto* typeIdPtr = new NIdentifier(argType);
                        auto* nameIdPtr = new NIdentifier(argName);
                        auto* argVar = new NVariableDeclaration(*typeIdPtr, *nameIdPtr);
                        args.push_back(argVar);
                    }
                }

                auto* typeIdPtr = new NIdentifier(retType);
                auto* nameIdPtr = new NIdentifier(name);
                NFunctionDeclaration* funcDecl = new NFunctionDeclaration(*typeIdPtr, *nameIdPtr, args, body);
                std::cout << "[DEBUG] visitFunc_decl: created funcDecl = " << funcDecl << std::endl;
                return antlrcpp::Any(funcDecl);
            }
        } else {
            std::cout << "[DEBUG] visitFunc_decl: no block" << std::endl;
        }

        std::cout << "[DEBUG] visitFunc_decl: returning nullptr" << std::endl;
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitStruct_decl(CScriptParser::Struct_declContext* ctx) override {
        std::string name = ctx->IDENTIFIER() ? ctx->IDENTIFIER()->getText() : "unknown";

        NBlock* members = new NBlock();
        if (ctx->struct_members()) {
            auto membersResult = visitStruct_members(ctx->struct_members());
            NBlock* structMembers = safe_any_cast<NBlock>(membersResult);
            if (structMembers) {
                members = structMembers;
            }
        }

        NIdentifier nameId(name);
        return antlrcpp::Any(new NStructDeclaration(nameId, *members));
    }

    antlrcpp::Any visitIdent(CScriptParser::IdentContext* ctx) override {
        return antlrcpp::Any(ctx->getText());
    }

    antlrcpp::Any visitEnum_decl(CScriptParser::Enum_declContext* ctx) override {
        std::string name = ctx->IDENTIFIER() ? ctx->IDENTIFIER()->getText() : "";
        NIdentifier* nameId = new NIdentifier(name);
        NBlock* items = new NBlock();
        if (ctx->enum_list()) {
            auto itemsResult = visitEnum_list(ctx->enum_list());
            NBlock* enumItems = safe_any_cast<NBlock>(itemsResult);
            if (enumItems) {
                items = enumItems;
            }
        }
        return antlrcpp::Any(new NEnumDeclaration(*nameId, *items));
    }

    antlrcpp::Any visitEnum_list(CScriptParser::Enum_listContext* ctx) override {
        NBlock* block = new NBlock();
        for (auto* enumItemCtx : ctx->enum_item()) {
            auto itemResult = visitEnum_item(enumItemCtx);
            NEnumItem* item = safe_any_cast<NEnumItem>(itemResult);
            if (item) {
                block->statements.push_back(item);
            }
        }
        return antlrcpp::Any(block);
    }

    antlrcpp::Any visitEnum_item(CScriptParser::Enum_itemContext* ctx) override {
        std::string name;
        if (ctx->ident()) {
            name = ctx->ident()->getText();
        }
        NIdentifier* nameId = new NIdentifier(name);
        NExpression* value = nullptr;
        if (ctx->expr()) {
            auto valueResult = visitExpr(ctx->expr());
            value = safe_any_cast<NExpression>(valueResult);
        }
        return antlrcpp::Any(new NEnumItem(*nameId, value));
    }

    antlrcpp::Any visitUnion_decl(CScriptParser::Union_declContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitInit_list(CScriptParser::Init_listContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitFor_init(CScriptParser::For_initContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitFor_cond(CScriptParser::For_condContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitFor_incr(CScriptParser::For_incrContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitSwitch_stmt(CScriptParser::Switch_stmtContext* ctx) override {
        NExpression* condition = nullptr;
        if (ctx->expr()) {
            auto condResult = visitExpr(ctx->expr());
            condition = safe_any_cast<NExpression>(condResult);
        }

        NBlock* caseBlock = new NBlock();
        if (ctx->case_list()) {
            auto caseListCtx = ctx->case_list();
            std::vector<CScriptParser::Case_stmtContext*> caseCtxs = caseListCtx->case_stmt();
            for (size_t i = 0; i < caseCtxs.size(); i++) {
                auto caseCtx = caseCtxs[i];
                auto caseResult = visitCase_stmt(caseCtx);
                NStatement* caseStmt = safe_any_cast<NStatement>(caseResult);
                if (caseStmt) {
                    caseBlock->statements.push_back(caseStmt);
                }
            }
        }

        if (condition && caseBlock) {
            return antlrcpp::Any(new NSwitchStatement(*condition, *caseBlock));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitCase_stmt(CScriptParser::Case_stmtContext* ctx) override {
        NExpression* value = nullptr;

        if (ctx->expr()) {
            auto exprResult = visitExpr(ctx->expr());
            value = safe_any_cast<NExpression>(exprResult);
        }

        std::vector<NStatement*> statements;
        std::vector<CScriptParser::StmtContext*> stmts = ctx->stmt();
        for (auto stmtCtx : stmts) {
            auto stmtResult = visitStmt(stmtCtx);
            NStatement* stmt = safe_any_cast<NStatement>(stmtResult);
            if (stmt) {
                statements.push_back(stmt);
            }
        }

        if ((value || ctx->DEFAULT()) && !statements.empty()) {
            NBlock* statementsBlock = new NBlock();
            for (auto stmt : statements) {
                statementsBlock->statements.push_back(stmt);
            }
            if (value) {
                return antlrcpp::Any(new NCaseStatement(*value, *statementsBlock));
            } else {
                return antlrcpp::Any(new NDefaultStatement(*statementsBlock));
            }
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitCase_list(CScriptParser::Case_listContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitStruct_members(CScriptParser::Struct_membersContext* ctx) override {
        NBlock* members = new NBlock();
        std::vector<CScriptParser::Var_declContext*> varDecls = ctx->var_decl();
        for (auto memberCtx : varDecls) {
            auto memberResult = visitVar_decl(memberCtx);
            NStatement* memberStmt = safe_any_cast<NStatement>(memberResult);
            if (memberStmt) {
                members->statements.push_back(memberStmt);
            }
        }
        return antlrcpp::Any(members);
    }
    antlrcpp::Any visitCall_args(CScriptParser::Call_argsContext* ctx) override { return antlrcpp::Any(nullptr); }
    antlrcpp::Any visitFunc_decl_args(CScriptParser::Func_decl_argsContext* ctx) override {
        VariableList args;
        if (ctx) {
            for (auto vd : ctx->var_decl()) {
                std::string argType = "int";
                if (vd->type() && vd->type()->IDENTIFIER()) {
                    argType = vd->type()->IDENTIFIER()->getText();
                }
                std::string argName = "";
                if (vd->ident().size() > 0 && vd->ident(0)->IDENTIFIER()) {
                    argName = vd->ident(0)->IDENTIFIER()->getText();
                }
                auto* typeIdPtr = new NIdentifier(argType);
                auto* nameIdPtr = new NIdentifier(argName);
                auto* argVar = new NVariableDeclaration(*typeIdPtr, *nameIdPtr);
                args.push_back(argVar);
            }
        }
        return antlrcpp::Any(args);
    }

    antlrcpp::Any visitExtern_decl(CScriptParser::Extern_declContext* ctx) override {
        std::string retType = "int";
        if (ctx->type() && ctx->type()->IDENTIFIER()) {
            retType = ctx->type()->IDENTIFIER()->getText();
        }
        std::string name = "unknown";
        if (ctx->ident() && ctx->ident()->IDENTIFIER()) {
            name = ctx->ident()->IDENTIFIER()->getText();
        }

        VariableList args;
        if (ctx->func_decl_args()) {
            auto argsResult = visitFunc_decl_args(ctx->func_decl_args());
            if (argsResult.has_value()) {
                try {
                    args = *std::any_cast<VariableList>(&const_cast<antlrcpp::Any&>(argsResult));
                } catch (...) {
                }
            }
        }

        auto* typeIdPtr = new NIdentifier(retType);
        auto* nameIdPtr = new NIdentifier(name);
        return antlrcpp::Any(new NExternDeclaration(*typeIdPtr, *nameIdPtr, args));
    }

    antlrcpp::Any visitImport_stmt(CScriptParser::Import_stmtContext* ctx) override {
        std::cout << "[DEBUG] visitImport_stmt: entered" << std::endl;

        if (ctx->STRING() && ctx->ident().size() > 0) {
            std::string modulePath = ctx->STRING()->getText();
            if (modulePath.size() >= 2) {
                modulePath = modulePath.substr(1, modulePath.size() - 2);
            }
            std::string alias = ctx->ident(0)->getText();
            std::cout << "[DEBUG] visitImport_stmt: modulePath = " << modulePath << ", alias = " << alias << std::endl;
            return antlrcpp::Any(new NImportStatement(modulePath, alias));
        } else if (ctx->STRING() && ctx->ident().empty()) {
            std::string modulePath = ctx->STRING()->getText();
            if (modulePath.size() >= 2) {
                modulePath = modulePath.substr(1, modulePath.size() - 2);
            }
            std::cout << "[DEBUG] visitImport_stmt: modulePath = " << modulePath << std::endl;
            return antlrcpp::Any(new NImportStatement(modulePath));
        } else if (ctx->ident().size() > 0 && ctx->STRING()) {
            std::vector<std::string> symbols;
            for (auto identCtx : ctx->ident()) {
                symbols.push_back(identCtx->getText());
            }
            std::string modulePath = ctx->STRING()->getText();
            if (modulePath.size() >= 2) {
                modulePath = modulePath.substr(1, modulePath.size() - 2);
            }
            std::cout << "[DEBUG] visitImport_stmt: symbols = ";
            for (const auto& symbol : symbols) {
                std::cout << symbol << " ";
            }
            std::cout << ", modulePath = " << modulePath << std::endl;
            return antlrcpp::Any(new NImportStatement(symbols, modulePath));
        }

        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitInclude_stmt(CScriptParser::Include_stmtContext* ctx) override {
        std::cout << "[DEBUG] visitInclude_stmt: entered" << std::endl;

        if (ctx->STRING()) {
            std::string filePath = ctx->STRING()->getText();
            if (filePath.size() >= 2) {
                filePath = filePath.substr(1, filePath.size() - 2);
            }
            std::cout << "[DEBUG] visitInclude_stmt: filePath = " << filePath << std::endl;
            return antlrcpp::Any(new NIncludeStatement(filePath));
        }

        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitTry_catch_stmt(CScriptParser::Try_catch_stmtContext* ctx) override {
        std::cout << "[DEBUG] visitTry_catch_stmt: entered" << std::endl;

        auto tryBlockResult = visitBlock(ctx->block());
        NBlock* tryBlock = safe_any_cast<NBlock>(tryBlockResult);
        if (!tryBlock) {
            std::cout << "[DEBUG] visitTry_catch_stmt: try block is null" << std::endl;
            return antlrcpp::Any(nullptr);
        }

        std::vector<NCatchBlock*> catchBlocks;
        for (auto catchBlockCtx : ctx->catch_block()) {
            auto catchBlockResult = visitCatch_block(catchBlockCtx);
            NCatchBlock* catchBlock = safe_any_cast<NCatchBlock>(catchBlockResult);
            if (catchBlock) {
                catchBlocks.push_back(catchBlock);
            }
        }

        if (catchBlocks.empty()) {
            std::cout << "[DEBUG] visitTry_catch_stmt: no catch blocks" << std::endl;
            return antlrcpp::Any(nullptr);
        }

        return antlrcpp::Any(new NTryCatchStatement(tryBlock, catchBlocks));
    }

    antlrcpp::Any visitCatch_block(CScriptParser::Catch_blockContext* ctx) override {
        std::cout << "[DEBUG] visitCatch_block: entered" << std::endl;

        if (ctx->ELLIPSIS()) {
            std::cout << "[DEBUG] visitCatch_block: found ellipsis catch block" << std::endl;
            auto blockResult = visitBlock(ctx->block());
            NBlock* block = safe_any_cast<NBlock>(blockResult);
            if (block) {
                return antlrcpp::Any(new NCatchBlock(block));
            }
        } else if (ctx->type() && ctx->ident()) {
            std::cout << "[DEBUG] visitCatch_block: found typed catch block" << std::endl;
            std::string typeStr = ctx->type()->getText();
            std::string idStr = ctx->ident()->getText();

            auto* typeId = new NIdentifier(typeStr);
            auto* id = new NIdentifier(idStr);

            auto blockResult = visitBlock(ctx->block());
            NBlock* block = safe_any_cast<NBlock>(blockResult);
            if (block) {
                return antlrcpp::Any(new NCatchBlock(typeId, id, block));
            }
        }

        std::cout << "[DEBUG] visitCatch_block: invalid catch block" << std::endl;
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitRegister_callback_stmt(CScriptParser::Register_callback_stmtContext* ctx) override {
        std::string callbackName = "unknown";
        if (ctx->ident(0) && ctx->ident(0)->IDENTIFIER()) {
            callbackName = ctx->ident(0)->IDENTIFIER()->getText();
        }

        std::string targetName = "unknown";
        if (ctx->ident(1) && ctx->ident(1)->IDENTIFIER()) {
            targetName = ctx->ident(1)->IDENTIFIER()->getText();
        }

        VariableList args;
        if (ctx->func_decl_args()) {
            auto argsResult = visitFunc_decl_args(ctx->func_decl_args());
            if (argsResult.has_value()) {
                try {
                    args = *std::any_cast<VariableList>(&const_cast<antlrcpp::Any&>(argsResult));
                } catch (...) {
                }
            }
        }

        auto* callbackNamePtr = new NIdentifier(callbackName);
        auto* targetNamePtr = new NIdentifier(targetName);
        return antlrcpp::Any(new NRegisterCallbackStatement(*callbackNamePtr, *targetNamePtr, args));
    }
};

}

#endif