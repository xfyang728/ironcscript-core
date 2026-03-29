
// Generated from d:/MyCode/CScriptEngine/src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CScriptParser.
 */
class  CScriptListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CScriptParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CScriptParser::ProgramContext *ctx) = 0;

  virtual void enterStmt(CScriptParser::StmtContext *ctx) = 0;
  virtual void exitStmt(CScriptParser::StmtContext *ctx) = 0;

  virtual void enterBlock(CScriptParser::BlockContext *ctx) = 0;
  virtual void exitBlock(CScriptParser::BlockContext *ctx) = 0;

  virtual void enterVar_decl(CScriptParser::Var_declContext *ctx) = 0;
  virtual void exitVar_decl(CScriptParser::Var_declContext *ctx) = 0;

  virtual void enterFunc_decl(CScriptParser::Func_declContext *ctx) = 0;
  virtual void exitFunc_decl(CScriptParser::Func_declContext *ctx) = 0;

  virtual void enterExtern_decl(CScriptParser::Extern_declContext *ctx) = 0;
  virtual void exitExtern_decl(CScriptParser::Extern_declContext *ctx) = 0;

  virtual void enterFunc_decl_args(CScriptParser::Func_decl_argsContext *ctx) = 0;
  virtual void exitFunc_decl_args(CScriptParser::Func_decl_argsContext *ctx) = 0;

  virtual void enterIdent(CScriptParser::IdentContext *ctx) = 0;
  virtual void exitIdent(CScriptParser::IdentContext *ctx) = 0;

  virtual void enterType(CScriptParser::TypeContext *ctx) = 0;
  virtual void exitType(CScriptParser::TypeContext *ctx) = 0;

  virtual void enterStruct_decl(CScriptParser::Struct_declContext *ctx) = 0;
  virtual void exitStruct_decl(CScriptParser::Struct_declContext *ctx) = 0;

  virtual void enterUnion_decl(CScriptParser::Union_declContext *ctx) = 0;
  virtual void exitUnion_decl(CScriptParser::Union_declContext *ctx) = 0;

  virtual void enterStruct_members(CScriptParser::Struct_membersContext *ctx) = 0;
  virtual void exitStruct_members(CScriptParser::Struct_membersContext *ctx) = 0;

  virtual void enterEnum_decl(CScriptParser::Enum_declContext *ctx) = 0;
  virtual void exitEnum_decl(CScriptParser::Enum_declContext *ctx) = 0;

  virtual void enterEnum_list(CScriptParser::Enum_listContext *ctx) = 0;
  virtual void exitEnum_list(CScriptParser::Enum_listContext *ctx) = 0;

  virtual void enterEnum_item(CScriptParser::Enum_itemContext *ctx) = 0;
  virtual void exitEnum_item(CScriptParser::Enum_itemContext *ctx) = 0;

  virtual void enterInit_list(CScriptParser::Init_listContext *ctx) = 0;
  virtual void exitInit_list(CScriptParser::Init_listContext *ctx) = 0;

  virtual void enterExpr(CScriptParser::ExprContext *ctx) = 0;
  virtual void exitExpr(CScriptParser::ExprContext *ctx) = 0;

  virtual void enterOr_expr(CScriptParser::Or_exprContext *ctx) = 0;
  virtual void exitOr_expr(CScriptParser::Or_exprContext *ctx) = 0;

  virtual void enterAnd_expr(CScriptParser::And_exprContext *ctx) = 0;
  virtual void exitAnd_expr(CScriptParser::And_exprContext *ctx) = 0;

  virtual void enterBit_or_expr(CScriptParser::Bit_or_exprContext *ctx) = 0;
  virtual void exitBit_or_expr(CScriptParser::Bit_or_exprContext *ctx) = 0;

  virtual void enterBit_xor_expr(CScriptParser::Bit_xor_exprContext *ctx) = 0;
  virtual void exitBit_xor_expr(CScriptParser::Bit_xor_exprContext *ctx) = 0;

  virtual void enterBit_and_expr(CScriptParser::Bit_and_exprContext *ctx) = 0;
  virtual void exitBit_and_expr(CScriptParser::Bit_and_exprContext *ctx) = 0;

  virtual void enterEq_expr(CScriptParser::Eq_exprContext *ctx) = 0;
  virtual void exitEq_expr(CScriptParser::Eq_exprContext *ctx) = 0;

  virtual void enterRel_expr(CScriptParser::Rel_exprContext *ctx) = 0;
  virtual void exitRel_expr(CScriptParser::Rel_exprContext *ctx) = 0;

  virtual void enterShift_expr(CScriptParser::Shift_exprContext *ctx) = 0;
  virtual void exitShift_expr(CScriptParser::Shift_exprContext *ctx) = 0;

  virtual void enterAdd_expr(CScriptParser::Add_exprContext *ctx) = 0;
  virtual void exitAdd_expr(CScriptParser::Add_exprContext *ctx) = 0;

  virtual void enterMul_expr(CScriptParser::Mul_exprContext *ctx) = 0;
  virtual void exitMul_expr(CScriptParser::Mul_exprContext *ctx) = 0;

  virtual void enterUnary_expr(CScriptParser::Unary_exprContext *ctx) = 0;
  virtual void exitUnary_expr(CScriptParser::Unary_exprContext *ctx) = 0;

  virtual void enterPrimary_expr(CScriptParser::Primary_exprContext *ctx) = 0;
  virtual void exitPrimary_expr(CScriptParser::Primary_exprContext *ctx) = 0;

  virtual void enterCall_args(CScriptParser::Call_argsContext *ctx) = 0;
  virtual void exitCall_args(CScriptParser::Call_argsContext *ctx) = 0;

  virtual void enterNumeric(CScriptParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(CScriptParser::NumericContext *ctx) = 0;

  virtual void enterIf_stmt(CScriptParser::If_stmtContext *ctx) = 0;
  virtual void exitIf_stmt(CScriptParser::If_stmtContext *ctx) = 0;

  virtual void enterWhile_stmt(CScriptParser::While_stmtContext *ctx) = 0;
  virtual void exitWhile_stmt(CScriptParser::While_stmtContext *ctx) = 0;

  virtual void enterFor_stmt(CScriptParser::For_stmtContext *ctx) = 0;
  virtual void exitFor_stmt(CScriptParser::For_stmtContext *ctx) = 0;

  virtual void enterFor_init(CScriptParser::For_initContext *ctx) = 0;
  virtual void exitFor_init(CScriptParser::For_initContext *ctx) = 0;

  virtual void enterFor_cond(CScriptParser::For_condContext *ctx) = 0;
  virtual void exitFor_cond(CScriptParser::For_condContext *ctx) = 0;

  virtual void enterFor_incr(CScriptParser::For_incrContext *ctx) = 0;
  virtual void exitFor_incr(CScriptParser::For_incrContext *ctx) = 0;

  virtual void enterDo_while_stmt(CScriptParser::Do_while_stmtContext *ctx) = 0;
  virtual void exitDo_while_stmt(CScriptParser::Do_while_stmtContext *ctx) = 0;

  virtual void enterSwitch_stmt(CScriptParser::Switch_stmtContext *ctx) = 0;
  virtual void exitSwitch_stmt(CScriptParser::Switch_stmtContext *ctx) = 0;

  virtual void enterCase_list(CScriptParser::Case_listContext *ctx) = 0;
  virtual void exitCase_list(CScriptParser::Case_listContext *ctx) = 0;

  virtual void enterCase_stmt(CScriptParser::Case_stmtContext *ctx) = 0;
  virtual void exitCase_stmt(CScriptParser::Case_stmtContext *ctx) = 0;


};

