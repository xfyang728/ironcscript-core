#ifndef CSE_AST_BUILDER_H
#define CSE_AST_BUILDER_H

#include "frontend/parser/node.h"
#include "frontend/generated/CScriptParser.h"
#include "frontend/generated/CScriptVisitor.h"
#include "frontend/parser/tokens.h"
#include <vector>
#include <string>
#include <map>
#include <set>
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
        if (anyVal.type() == typeid(NExportStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NExportStatement*>(anyVal));
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
        if (anyVal.type() == typeid(NBlockStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NBlockStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NGotoStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NGotoStatement*>(anyVal));
            }
        }
        if (anyVal.type() == typeid(NLabelStatement*)) {
            if constexpr (std::is_base_of_v<NStatement, T>) {
                return dynamic_cast<T*>(std::any_cast<NLabelStatement*>(anyVal));
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
private:
    std::string currentSourceFile;
    std::map<std::string, int> m_StructSizes;
    std::map<std::string, std::string> m_Typedefs;
    std::map<std::string, std::vector<long long>> m_ArrayDims;
    std::set<std::string> m_FunctionNames;
    std::map<std::string, std::string> m_FuncPtrAliases;

    // 把 ANTLR 拼接连写的类型文本（如 "unsignedint"、"staticint"）归一化为基础类型。
    static std::string normalizeTypeText(const std::string& raw) {
        std::string s = raw;
        std::string stars;
        size_t starPos = s.find('*');
        if (starPos != std::string::npos) {
            stars = s.substr(starPos);
            s = s.substr(0, starPos);
        }
        static const char* quals[] = {"static", "extern", "volatile", "const",
                                      "unsigned", "signed", "long", "short"};
        bool changed = true;
        while (changed) {
            changed = false;
            for (const char* q : quals) {
                std::string qs(q);
                if (s.size() > qs.size() && s.compare(0, qs.size(), qs) == 0) {
                    s = s.substr(qs.size());
                    changed = true;
                    break;
                }
            }
        }
        if (s.empty()) {
            s = "long";
        }
        return s + stars;
    }

    static bool hasQualifier(const std::string& raw, const std::string& qualifier) {
        return raw.find(qualifier) != std::string::npos;
    }

public:
    ASTBuilder() : currentSourceFile("") {}
    ~ASTBuilder() {}

    void setSourceFile(const std::string& file) { currentSourceFile = file; }
    const std::string& getSourceFile() const { return currentSourceFile; }

    NBlock* build(CScriptParser::ProgramContext* ctx) {
        auto result = visitProgram(ctx);
        NBlock* block = safe_any_cast<NBlock>(result);
        return block;
    }

    antlrcpp::Any visitProgram(CScriptParser::ProgramContext* ctx) override {
        NBlock* block = new NBlock();
        auto stmts = ctx->stmt();
        for (auto stmt : stmts) {
            auto result = visitStmt(stmt);
            if (result.has_value()) {
                NStatement* s = safe_any_cast<NStatement>(result);
                if (s) {
                    block->statements.push_back(s);
                }
            }
        }
        return antlrcpp::Any(block);
    }

    antlrcpp::Any visitStmt(CScriptParser::StmtContext* ctx) override {
        if (ctx->var_decl()) {
            return visitVar_decl(ctx->var_decl());
        }
        if (ctx->func_decl()) {
            return visitFunc_decl(ctx->func_decl());
        }
        if (ctx->extern_decl()) {
            return visitExtern_decl(ctx->extern_decl());
        }
        if (ctx->struct_decl()) {
            return visitStruct_decl(ctx->struct_decl());
        }
        if (ctx->enum_decl()) {
            return visitEnum_decl(ctx->enum_decl());
        }
        if (ctx->if_stmt()) {
            return visitIf_stmt(ctx->if_stmt());
        }
        if (ctx->while_stmt()) {
            return visitWhile_stmt(ctx->while_stmt());
        }
        if (ctx->for_stmt()) {
            return visitFor_stmt(ctx->for_stmt());
        }
        if (ctx->switch_stmt()) {
            return visitSwitch_stmt(ctx->switch_stmt());
        }
        if (ctx->do_while_stmt()) {
            return visitDo_while_stmt(ctx->do_while_stmt());
        }
        if (ctx->try_catch_stmt()) {
            return visitTry_catch_stmt(ctx->try_catch_stmt());
        }
        if (ctx->register_callback_stmt()) {
            return visitRegister_callback_stmt(ctx->register_callback_stmt());
        }
        if (ctx->typedef_decl()) {
            return visitTypedef_decl(ctx->typedef_decl());
        }
        if (ctx->goto_stmt()) {
            return visitGoto_stmt(ctx->goto_stmt());
        }
        if (ctx->label_stmt()) {
            return visitLabel_stmt(ctx->label_stmt());
        }
        if (ctx->import_stmt()) {
            return visitImport_stmt(ctx->import_stmt());
        }
        if (ctx->include_stmt()) {
            return visitInclude_stmt(ctx->include_stmt());
        }
        if (ctx->export_stmt()) {
            return ctx->export_stmt()->accept(this);
        }
        if (ctx->RETURN() && ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NReturnStatement(*expr));
            }
        }
        if (ctx->BREAK()) {
            return antlrcpp::Any(new NBreakStatement());
        }
        if (ctx->CONTINUE()) {
            return antlrcpp::Any(new NContinueStatement());
        }
        if (ctx->MUL() && ctx->ident() && ctx->expr()) {
            auto* id = new NIdentifier(ctx->ident()->getText());
            auto result = visitExpr(ctx->expr());
            NExpression* val = safe_any_cast<NExpression>(result);
            if (val) {
                return antlrcpp::Any(new NExpressionStatement(*new NAssignment(*new NUnaryOperator(CScriptParser::MUL, *id), *val)));
            }
        }
        if (ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NExpressionStatement(*expr));
            }
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitVar_decl(CScriptParser::Var_declContext* ctx) override {
        std::string typeStr;
        std::string rawType;
        if (ctx->type()) {
            rawType = ctx->type()->getText();
        }
        if (ctx->type() && ctx->type()->ENUM_KW()) {
            typeStr = ctx->type()->IDENTIFIER(0)->getText();
        } else if (ctx->type()) {
            typeStr = normalizeTypeText(rawType);
        }
        bool isStatic = hasQualifier(rawType, "static");
        auto typedefIt = m_Typedefs.find(typeStr);
        if (typedefIt != m_Typedefs.end() && !typeStr.empty() && typeStr.back() != '*') {
            typeStr = typedefIt->second;
        }

        if (!ctx->LPAREN().empty() && ctx->MUL() && !ctx->ident().empty()) {
            // 函数指针声明 int (*fp)(); 以 int 变量承载，调用处按已赋值函数名直接调用
            std::string name;
            if (ctx->ident(0) && ctx->ident(0)->IDENTIFIER()) {
                name = ctx->ident(0)->IDENTIFIER()->getText();
            }
            auto* typeIdPtr = new NIdentifier("int");
            auto* nameIdPtr = new NIdentifier(name);
            return antlrcpp::Any(new NVariableDeclaration(*typeIdPtr, *nameIdPtr));
        }

        if (!ctx->LBRACKET().empty()) {
            std::string name;
            if (ctx->ident().size() > 0 && ctx->ident(0)->IDENTIFIER()) {
                name = ctx->ident(0)->IDENTIFIER()->getText();
            }

            std::vector<NExpression*> dims;
            for (auto* dimCtx : ctx->expr()) {
                auto dimResult = visitExpr(dimCtx);
                if (auto* dimExpr = safe_any_cast<NExpression>(dimResult)) {
                    dims.push_back(dimExpr);
                }
            }

            NExpression* sizeExpr = nullptr;
            std::vector<long long> dimVals;
            long long total = 1;
            bool allConst = !dims.empty();
            for (auto* dimExpr : dims) {
                if (auto* n = dynamic_cast<NInteger*>(dimExpr)) {
                    dimVals.push_back(n->value);
                    total *= n->value;
                } else {
                    allConst = false;
                }
            }
            if (dims.size() == 1) {
                sizeExpr = dims[0];
            } else if (allConst) {
                sizeExpr = new NInteger(total);
            } else if (!dims.empty()) {
                sizeExpr = dims[0];
            }
            if (allConst && !dims.empty()) {
                m_ArrayDims[name] = dimVals;
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

        if (ctx->STRUCT_KW() || ctx->UNION_KW()) {
            std::string kind = ctx->STRUCT_KW() ? "struct " : "union ";
            std::string structName, varName;
            if (ctx->ident().size() >= 2) {
                if (ctx->ident(0) && ctx->ident(0)->IDENTIFIER()) {
                    structName = ctx->ident(0)->IDENTIFIER()->getText();
                }
                if (ctx->ident(1) && ctx->ident(1)->IDENTIFIER()) {
                    varName = ctx->ident(1)->IDENTIFIER()->getText();
                }
            }

            auto* typeIdPtr = new NIdentifier(kind + structName);
            auto* nameIdPtr = new NIdentifier(varName);

            NExpression* initExpr = nullptr;
            if (!ctx->expr().empty()) {
                auto result = visitExpr(ctx->expr(0));
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

            if (!ctx->expr().empty()) {
                auto result = visitExpr(ctx->expr(0));
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

        if (!ctx->expr().empty()) {
            auto result = visitExpr(ctx->expr(0));
            var->assignmentExpr = safe_any_cast<NExpression>(result);
        } else if (isStatic) {
            // static 局部变量零初始化（单次执行语义）
            var->assignmentExpr = new NInteger(0);
        }

        return antlrcpp::Any(var);
    }

    antlrcpp::Any visitType(CScriptParser::TypeContext* ctx) override {
        return antlrcpp::Any(ctx->getText());
    }

    // 常量维度的多维数组扁平化为一维下标
    NExpression* flattenIndices(const std::string& name,
                                const std::vector<NExpression*>& idxs) {
        if (idxs.empty()) {
            return nullptr;
        }
        auto it = m_ArrayDims.find(name);
        if (it == m_ArrayDims.end() || it->second.size() != idxs.size() || idxs.size() < 2) {
            return idxs[0];
        }
        NExpression* result = idxs[0];
        for (size_t k = 1; k < idxs.size(); k++) {
            long long factor = 1;
            for (size_t m = k + 1; m < it->second.size(); m++) {
                factor *= it->second[m];
            }
            NExpression* term = idxs[k];
            if (factor != 1) {
                term = new NBinaryOperator(*term, CScriptParser::MUL, *new NInteger(factor));
            }
            result = new NBinaryOperator(*result, CScriptParser::PLUS, *term);
        }
        return result;
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

        if (ctx->ident() != nullptr && !ctx->LBRACKET().empty() && ctx->expr().size() >= 2) {
            auto* id = new NIdentifier(ctx->ident()->getText());
            size_t idxCount = ctx->LBRACKET().size();
            std::vector<NExpression*> idxs;
            for (size_t k = 0; k < idxCount && k + 1 < ctx->expr().size(); k++) {
                auto idxResult = visitExpr(ctx->expr(k));
                if (auto* idxExpr = safe_any_cast<NExpression>(idxResult)) {
                    idxs.push_back(idxExpr);
                }
            }
            NExpression* index = flattenIndices(id->name, idxs);
            auto valueResult = visitExpr(ctx->expr(ctx->expr().size() - 1));
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
                    if (ctx->LSHIFT_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::LSHIFT, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->RSHIFT_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::RSHIFT, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->BITAND_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::BITAND, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->BITOR_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::BITOR, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->XOR_EQ()) {
                        auto* binOp = new NBinaryOperator(*id, CScriptParser::XOR, *val);
                        return antlrcpp::Any(new NAssignment(*id, *binOp));
                    }
                    if (ctx->ASSIGN()) {
                        if (auto* rhsId = dynamic_cast<NIdentifier*>(val)) {
                            if (m_FunctionNames.find(rhsId->name) != m_FunctionNames.end()) {
                                m_FuncPtrAliases[id->name] = rhsId->name;
                                return antlrcpp::Any(new NAssignment(*id, *new NInteger(0)));
                            }
                        }
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
            // 处理 import 模块的成员函数调用: alias.funcName(args)
            if (ctx->ident().size() >= 2 && ctx->DOT() && ctx->LPAREN()) {
                std::string moduleName = ctx->ident(0)->getText();
                std::string funcName = ctx->ident(1)->getText();
                std::string fullName = moduleName + "." + funcName;
                auto* funcId = new NIdentifier(fullName);
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
            if (ctx->LPAREN()) {
                std::string funcName = ctx->ident(0)->getText();
                auto aliasIt = m_FuncPtrAliases.find(funcName);
                if (aliasIt != m_FuncPtrAliases.end()) {
                    funcName = aliasIt->second;
                }
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
            if (!ctx->LBRACKET().empty() && !ctx->expr().empty()) {
                if (ctx->DOT() && ctx->ident().size() >= 2) {
                    // 成员数组：u.c[k]（联合体成员重叠时等价于 u 的起始地址）
                    auto* objId = new NIdentifier(ctx->ident(0)->getText());
                    auto* memberId = new NIdentifier(ctx->ident(1)->getText());
                    return antlrcpp::Any(new NMemberAccess(*objId, *memberId));
                }
                auto* arrId = new NIdentifier(ctx->ident(0)->getText());
                std::vector<NExpression*> idxs;
                for (size_t k = 0; k < ctx->LBRACKET().size() && k < ctx->expr().size(); k++) {
                    auto idxResult = visitExpr(ctx->expr(k));
                    if (auto* idxExpr = safe_any_cast<NExpression>(idxResult)) {
                        idxs.push_back(idxExpr);
                    }
                }
                NExpression* index = flattenIndices(arrId->name, idxs);
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
        if (!ctx->expr().empty()) {
            auto result = visitExpr(ctx->expr(0));
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
        if (ctx->HEX_INTEGER()) {
            std::string text = ctx->HEX_INTEGER()->getText();
            return antlrcpp::Any(new NInteger(strtoll(text.c_str() + 2, nullptr, 16)));
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
        if (ctx->SIZEOF() && ctx->STRUCT_KW() && ctx->IDENTIFIER()) {
            std::string structName = ctx->IDENTIFIER()->getText();
            int size = 4;
            auto it = m_StructSizes.find(structName);
            if (it != m_StructSizes.end()) {
                size = it->second;
            }
            return antlrcpp::Any(new NInteger(size));
        }
        if (ctx->SIZEOF() && ctx->type()) {
            std::string t = normalizeTypeText(ctx->type()->getText());
            int size = 4;
            if (t == "char") {
                size = 1;
            } else if (t == "short") {
                size = 2;
            } else if (t == "double" || t == "float") {
                size = 8;
            } else if (!t.empty() && t.back() == '*') {
                size = 8;
            }
            return antlrcpp::Any(new NInteger(size));
        }
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

    antlrcpp::Any visitBody(CScriptParser::BodyContext* ctx) override {
        if (!ctx) {
            return antlrcpp::Any((NBlock*)nullptr);
        }
        if (ctx->block()) {
            return visitBlock(ctx->block());
        }
        NBlock* block = new NBlock();
        if (ctx->single_stmt()) {
            auto result = visitSingle_stmt(ctx->single_stmt());
            NStatement* s = safe_any_cast<NStatement>(result);
            if (s) {
                block->statements.push_back(s);
            }
        }
        return antlrcpp::Any(block);
    }

    antlrcpp::Any visitSingle_stmt(CScriptParser::Single_stmtContext* ctx) override {
        if (!ctx) {
            return antlrcpp::Any((NStatement*)nullptr);
        }
        if (ctx->if_stmt()) {
            return visitIf_stmt(ctx->if_stmt());
        }
        if (ctx->while_stmt()) {
            return visitWhile_stmt(ctx->while_stmt());
        }
        if (ctx->for_stmt()) {
            return visitFor_stmt(ctx->for_stmt());
        }
        if (ctx->do_while_stmt()) {
            return visitDo_while_stmt(ctx->do_while_stmt());
        }
        if (ctx->switch_stmt()) {
            return visitSwitch_stmt(ctx->switch_stmt());
        }
        if (ctx->try_catch_stmt()) {
            return visitTry_catch_stmt(ctx->try_catch_stmt());
        }
        if (ctx->register_callback_stmt()) {
            return visitRegister_callback_stmt(ctx->register_callback_stmt());
        }
        if (ctx->RETURN() && ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NReturnStatement(*expr));
            }
        }
        if (ctx->BREAK()) {
            return antlrcpp::Any(new NBreakStatement());
        }
        if (ctx->CONTINUE()) {
            return antlrcpp::Any(new NContinueStatement());
        }
        if (ctx->MUL() && ctx->ident() && ctx->expr()) {
            auto* id = new NIdentifier(ctx->ident()->getText());
            auto result = visitExpr(ctx->expr());
            NExpression* val = safe_any_cast<NExpression>(result);
            if (val) {
                return antlrcpp::Any(new NExpressionStatement(*new NAssignment(*new NUnaryOperator(CScriptParser::MUL, *id), *val)));
            }
        }
        if (ctx->expr()) {
            auto result = visitExpr(ctx->expr());
            NExpression* expr = safe_any_cast<NExpression>(result);
            if (expr) {
                return antlrcpp::Any(new NExpressionStatement(*expr));
            }
        }
        return antlrcpp::Any((NStatement*)nullptr);
    }

    antlrcpp::Any visitIf_stmt(CScriptParser::If_stmtContext* ctx) override {
        auto condResult = visitExpr(ctx->expr());
        NExpression* condition = safe_any_cast<NExpression>(condResult);
        auto thenResult = visitBody(ctx->body(0));
        NBlock* thenBlock = safe_any_cast<NBlock>(thenResult);

        NBlock* elseBlock = nullptr;
        if (ctx->body().size() > 1) {
            auto elseResult = visitBody(ctx->body(1));
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
        auto bodyResult = visitBody(ctx->body());
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

        auto bodyResult = visitBody(ctx->body());
        NBlock* body = safe_any_cast<NBlock>(bodyResult);

        if (body) {
            return antlrcpp::Any(new NForStatement(initStmt, condition, update, *body));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitDo_while_stmt(CScriptParser::Do_while_stmtContext* ctx) override {
        auto bodyResult = visitBody(ctx->body());
        NBlock* body = safe_any_cast<NBlock>(bodyResult);
        auto condResult = visitExpr(ctx->expr());
        NExpression* condition = safe_any_cast<NExpression>(condResult);

        if (body && condition) {
            return antlrcpp::Any(new NDoWhileStatement(*body, *condition));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitFunc_decl(CScriptParser::Func_declContext* ctx) override {
        std::string retType = "int";
        if (ctx->type()) {
            retType = normalizeTypeText(ctx->type()->getText());
        }
        std::string name = "unknown";
        if (ctx->ident() && ctx->ident()->IDENTIFIER()) {
            name = ctx->ident()->IDENTIFIER()->getText();
        }

        if (!name.empty()) {
            m_FunctionNames.insert(name);
        }
        if (ctx->block()) {
            auto bodyResult = visitBlock(ctx->block());
            NBlock* body = safe_any_cast<NBlock>(bodyResult);
            if (body) {
                VariableList args;
                if (ctx->func_decl_args()) {
                    for (auto vd : ctx->func_decl_args()->var_decl()) {
                        std::string argType = "int";
                        if (vd->type()) {
                            argType = normalizeTypeText(vd->type()->getText());
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
                bool isVariadic = ctx->func_decl_args() && ctx->func_decl_args()->ELLIPSIS() != nullptr;
                NFunctionDeclaration* funcDecl = new NFunctionDeclaration(*typeIdPtr, *nameIdPtr, args, body, isVariadic);
                return antlrcpp::Any(funcDecl);
            }
        }

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

        int totalSize = 0;
        for (auto* member : members->statements) {
            if (auto* vd = dynamic_cast<NVariableDeclaration*>(member)) {
                totalSize += sizeOfType(vd->type.name);
            } else if (auto* ad = dynamic_cast<NArrayDeclaration*>(member)) {
                long long count = 1;
                if (auto* n = dynamic_cast<NInteger*>(ad->size)) {
                    count = n->value;
                }
                totalSize += sizeOfType(ad->type.name) * static_cast<int>(count);
            }
        }
        m_StructSizes[name] = totalSize;

        NIdentifier nameId(name);
        NStructDeclaration* structDecl = new NStructDeclaration(nameId, *members);

        std::vector<std::string> varNames;
        for (auto* idCtx : ctx->ident()) {
            if (idCtx && idCtx->IDENTIFIER()) {
                varNames.push_back(idCtx->IDENTIFIER()->getText());
            }
        }
        if (varNames.empty()) {
            return antlrcpp::Any(structDecl);
        }

        NBlock* stmts = new NBlock();
        stmts->statements.push_back(structDecl);
        for (auto& vn : varNames) {
            auto* t = new NIdentifier("struct " + name);
            auto* n = new NIdentifier(vn);
            stmts->statements.push_back(new NVariableDeclaration(*t, *n));
        }
        return antlrcpp::Any(new NBlockStatement(stmts));
    }

    antlrcpp::Any visitTypedef_decl(CScriptParser::Typedef_declContext* ctx) override {
        NBlock* stmts = new NBlock();
        if (ctx->STRUCT_KW()) {
            std::string alias = ctx->ident() && ctx->ident()->IDENTIFIER()
                                    ? ctx->ident()->IDENTIFIER()->getText()
                                    : "typedef_anon";
            std::string structName = ctx->IDENTIFIER() ? ctx->IDENTIFIER()->getText()
                                                       : ("anon_" + alias);

            NBlock* members = new NBlock();
            if (ctx->struct_members()) {
                auto membersResult = visitStruct_members(ctx->struct_members());
                NBlock* structMembers = safe_any_cast<NBlock>(membersResult);
                if (structMembers) {
                    members = structMembers;
                }
            }
            NIdentifier nameId(structName);
            stmts->statements.push_back(new NStructDeclaration(nameId, *members));
            m_Typedefs[alias] = "struct " + structName;
        } else if (ctx->ident() && ctx->ident()->IDENTIFIER()) {
            m_Typedefs[ctx->ident()->IDENTIFIER()->getText()] =
                normalizeTypeText(ctx->type()->getText());
        }
        return antlrcpp::Any(new NBlockStatement(stmts));
    }

    static int sizeOfType(const std::string& t) {
        if (t == "char") return 1;
        if (t == "short") return 2;
        if (t == "double" || t == "float") return 8;
        if (!t.empty() && t.back() == '*') return 8;
        return 4;
    }

    antlrcpp::Any visitGoto_stmt(CScriptParser::Goto_stmtContext* ctx) override {
        std::string label = ctx->ident() && ctx->ident()->IDENTIFIER()
                                ? ctx->ident()->IDENTIFIER()->getText()
                                : "";
        auto* labelId = new NIdentifier(label);
        return antlrcpp::Any(new NGotoStatement(*labelId));
    }

    antlrcpp::Any visitLabel_stmt(CScriptParser::Label_stmtContext* ctx) override {
        std::string name = ctx->ident() && ctx->ident()->IDENTIFIER()
                               ? ctx->ident()->IDENTIFIER()->getText()
                               : "";
        NBlock* block = new NBlock();
        block->statements.push_back(new NLabelStatement(*new NIdentifier(name)));
        if (ctx->stmt()) {
            auto result = visitStmt(ctx->stmt());
            NStatement* inner = safe_any_cast<NStatement>(result);
            if (inner) {
                block->statements.push_back(inner);
            }
        }
        return antlrcpp::Any(new NBlockStatement(block));
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
                if (vd->type()) {
                    argType = normalizeTypeText(vd->type()->getText());
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
        if (ctx->type()) {
            retType = normalizeTypeText(ctx->type()->getText());
        }
        std::string name = "unknown";
        if (ctx->ident() && ctx->ident()->IDENTIFIER()) {
            name = ctx->ident()->IDENTIFIER()->getText();
        }

        // extern 变量声明：extern int a;
        if (!ctx->LPAREN()) {
            auto* typeIdPtr = new NIdentifier(retType);
            auto* nameIdPtr = new NIdentifier(name);
            return antlrcpp::Any(new NVariableDeclaration(*typeIdPtr, *nameIdPtr));
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

        if (ctx->STRING() && ctx->ident().size() > 0) {
            std::string modulePath = ctx->STRING()->getText();
            if (modulePath.size() >= 2) {
                modulePath = modulePath.substr(1, modulePath.size() - 2);
            }
            std::string alias = ctx->ident(0)->getText();
            return antlrcpp::Any(new NImportStatement(modulePath, alias));
        } else if (ctx->STRING() && ctx->ident().empty()) {
            std::string modulePath = ctx->STRING()->getText();
            if (modulePath.size() >= 2) {
                modulePath = modulePath.substr(1, modulePath.size() - 2);
            }
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
            return antlrcpp::Any(new NImportStatement(symbols, modulePath));
        }

        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitInclude_stmt(CScriptParser::Include_stmtContext* ctx) override {

        std::string filePath;
        if (ctx->STRING()) {
            filePath = ctx->STRING()->getText();
            if (filePath.size() >= 2) {
                filePath = filePath.substr(1, filePath.size() - 2);
            }
        } else if (ctx->ANGLE_STRING()) {
            filePath = ctx->ANGLE_STRING()->getText();
            if (filePath.size() >= 2) {
                filePath = filePath.substr(1, filePath.size() - 2);
            }
        }

        if (!filePath.empty()) {
            size_t line = ctx->getStart()->getLine();
            size_t col = ctx->getStart()->getCharPositionInLine();
            return antlrcpp::Any(new NIncludeStatement(filePath, currentSourceFile, line, col));
        }

        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitExportVarDecl(CScriptParser::ExportVarDeclContext* ctx) override {
        auto result = visitVar_decl(ctx->var_decl());
        NStatement* decl = safe_any_cast<NStatement>(result);
        if (decl) {
            return antlrcpp::Any(new NExportStatement(decl));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitExportFuncDecl(CScriptParser::ExportFuncDeclContext* ctx) override {
        auto result = visitFunc_decl(ctx->func_decl());
        NStatement* decl = safe_any_cast<NStatement>(result);
        if (decl) {
            return antlrcpp::Any(new NExportStatement(decl));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitExportEnumDecl(CScriptParser::ExportEnumDeclContext* ctx) override {
        auto result = visitEnum_decl(ctx->enum_decl());
        NStatement* decl = safe_any_cast<NStatement>(result);
        if (decl) {
            return antlrcpp::Any(new NExportStatement(decl));
        }
        return antlrcpp::Any(nullptr);
    }

    antlrcpp::Any visitTry_catch_stmt(CScriptParser::Try_catch_stmtContext* ctx) override {

        auto tryBlockResult = visitBlock(ctx->block());
        NBlock* tryBlock = safe_any_cast<NBlock>(tryBlockResult);
        if (!tryBlock) {
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
            return antlrcpp::Any(nullptr);
        }

        return antlrcpp::Any(new NTryCatchStatement(tryBlock, catchBlocks));
    }

    antlrcpp::Any visitCatch_block(CScriptParser::Catch_blockContext* ctx) override {

        if (ctx->ELLIPSIS()) {
            auto blockResult = visitBlock(ctx->block());
            NBlock* block = safe_any_cast<NBlock>(blockResult);
            if (block) {
                return antlrcpp::Any(new NCatchBlock(block));
            }
        } else if (ctx->type() && ctx->ident()) {
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