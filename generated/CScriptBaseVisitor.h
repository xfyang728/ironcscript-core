
// Generated from D:/MyCode/CScriptEngine/src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CScriptVisitor.h"


/**
 * This class provides an empty implementation of CScriptVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CScriptBaseVisitor : public CScriptVisitor {
public:

  virtual std::any visitProgram(CScriptParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(CScriptParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImport_stmt(CScriptParser::Import_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInclude_stmt(CScriptParser::Include_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRegister_callback_stmt(CScriptParser::Register_callback_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(CScriptParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar_decl(CScriptParser::Var_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_decl(CScriptParser::Func_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtern_decl(CScriptParser::Extern_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_decl_args(CScriptParser::Func_decl_argsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdent(CScriptParser::IdentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(CScriptParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct_decl(CScriptParser::Struct_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnion_decl(CScriptParser::Union_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct_members(CScriptParser::Struct_membersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnum_decl(CScriptParser::Enum_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnum_list(CScriptParser::Enum_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnum_item(CScriptParser::Enum_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInit_list(CScriptParser::Init_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(CScriptParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOr_expr(CScriptParser::Or_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnd_expr(CScriptParser::And_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBit_or_expr(CScriptParser::Bit_or_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBit_xor_expr(CScriptParser::Bit_xor_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBit_and_expr(CScriptParser::Bit_and_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEq_expr(CScriptParser::Eq_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRel_expr(CScriptParser::Rel_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShift_expr(CScriptParser::Shift_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdd_expr(CScriptParser::Add_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMul_expr(CScriptParser::Mul_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_expr(CScriptParser::Unary_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expr(CScriptParser::Primary_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall_args(CScriptParser::Call_argsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumeric(CScriptParser::NumericContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_stmt(CScriptParser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_stmt(CScriptParser::While_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_stmt(CScriptParser::For_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_init(CScriptParser::For_initContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_cond(CScriptParser::For_condContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_incr(CScriptParser::For_incrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDo_while_stmt(CScriptParser::Do_while_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTry_catch_stmt(CScriptParser::Try_catch_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCatch_block(CScriptParser::Catch_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitch_stmt(CScriptParser::Switch_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_list(CScriptParser::Case_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_stmt(CScriptParser::Case_stmtContext *ctx) override {
    return visitChildren(ctx);
  }


};

