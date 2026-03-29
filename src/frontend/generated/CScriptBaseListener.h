
// Generated from D:/MyCode/IronCScript/ironcscript-core/src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CScriptListener.h"


/**
 * This class provides an empty implementation of CScriptListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CScriptBaseListener : public CScriptListener {
public:

  virtual void enterProgram(CScriptParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CScriptParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStmt(CScriptParser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(CScriptParser::StmtContext * /*ctx*/) override { }

  virtual void enterImport_stmt(CScriptParser::Import_stmtContext * /*ctx*/) override { }
  virtual void exitImport_stmt(CScriptParser::Import_stmtContext * /*ctx*/) override { }

  virtual void enterInclude_stmt(CScriptParser::Include_stmtContext * /*ctx*/) override { }
  virtual void exitInclude_stmt(CScriptParser::Include_stmtContext * /*ctx*/) override { }

  virtual void enterRegister_callback_stmt(CScriptParser::Register_callback_stmtContext * /*ctx*/) override { }
  virtual void exitRegister_callback_stmt(CScriptParser::Register_callback_stmtContext * /*ctx*/) override { }

  virtual void enterBlock(CScriptParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(CScriptParser::BlockContext * /*ctx*/) override { }

  virtual void enterVar_decl(CScriptParser::Var_declContext * /*ctx*/) override { }
  virtual void exitVar_decl(CScriptParser::Var_declContext * /*ctx*/) override { }

  virtual void enterFunc_decl(CScriptParser::Func_declContext * /*ctx*/) override { }
  virtual void exitFunc_decl(CScriptParser::Func_declContext * /*ctx*/) override { }

  virtual void enterExtern_decl(CScriptParser::Extern_declContext * /*ctx*/) override { }
  virtual void exitExtern_decl(CScriptParser::Extern_declContext * /*ctx*/) override { }

  virtual void enterFunc_decl_args(CScriptParser::Func_decl_argsContext * /*ctx*/) override { }
  virtual void exitFunc_decl_args(CScriptParser::Func_decl_argsContext * /*ctx*/) override { }

  virtual void enterIdent(CScriptParser::IdentContext * /*ctx*/) override { }
  virtual void exitIdent(CScriptParser::IdentContext * /*ctx*/) override { }

  virtual void enterType(CScriptParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(CScriptParser::TypeContext * /*ctx*/) override { }

  virtual void enterStruct_decl(CScriptParser::Struct_declContext * /*ctx*/) override { }
  virtual void exitStruct_decl(CScriptParser::Struct_declContext * /*ctx*/) override { }

  virtual void enterUnion_decl(CScriptParser::Union_declContext * /*ctx*/) override { }
  virtual void exitUnion_decl(CScriptParser::Union_declContext * /*ctx*/) override { }

  virtual void enterStruct_members(CScriptParser::Struct_membersContext * /*ctx*/) override { }
  virtual void exitStruct_members(CScriptParser::Struct_membersContext * /*ctx*/) override { }

  virtual void enterEnum_decl(CScriptParser::Enum_declContext * /*ctx*/) override { }
  virtual void exitEnum_decl(CScriptParser::Enum_declContext * /*ctx*/) override { }

  virtual void enterEnum_list(CScriptParser::Enum_listContext * /*ctx*/) override { }
  virtual void exitEnum_list(CScriptParser::Enum_listContext * /*ctx*/) override { }

  virtual void enterEnum_item(CScriptParser::Enum_itemContext * /*ctx*/) override { }
  virtual void exitEnum_item(CScriptParser::Enum_itemContext * /*ctx*/) override { }

  virtual void enterInit_list(CScriptParser::Init_listContext * /*ctx*/) override { }
  virtual void exitInit_list(CScriptParser::Init_listContext * /*ctx*/) override { }

  virtual void enterExpr(CScriptParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(CScriptParser::ExprContext * /*ctx*/) override { }

  virtual void enterOr_expr(CScriptParser::Or_exprContext * /*ctx*/) override { }
  virtual void exitOr_expr(CScriptParser::Or_exprContext * /*ctx*/) override { }

  virtual void enterAnd_expr(CScriptParser::And_exprContext * /*ctx*/) override { }
  virtual void exitAnd_expr(CScriptParser::And_exprContext * /*ctx*/) override { }

  virtual void enterBit_or_expr(CScriptParser::Bit_or_exprContext * /*ctx*/) override { }
  virtual void exitBit_or_expr(CScriptParser::Bit_or_exprContext * /*ctx*/) override { }

  virtual void enterBit_xor_expr(CScriptParser::Bit_xor_exprContext * /*ctx*/) override { }
  virtual void exitBit_xor_expr(CScriptParser::Bit_xor_exprContext * /*ctx*/) override { }

  virtual void enterBit_and_expr(CScriptParser::Bit_and_exprContext * /*ctx*/) override { }
  virtual void exitBit_and_expr(CScriptParser::Bit_and_exprContext * /*ctx*/) override { }

  virtual void enterEq_expr(CScriptParser::Eq_exprContext * /*ctx*/) override { }
  virtual void exitEq_expr(CScriptParser::Eq_exprContext * /*ctx*/) override { }

  virtual void enterRel_expr(CScriptParser::Rel_exprContext * /*ctx*/) override { }
  virtual void exitRel_expr(CScriptParser::Rel_exprContext * /*ctx*/) override { }

  virtual void enterShift_expr(CScriptParser::Shift_exprContext * /*ctx*/) override { }
  virtual void exitShift_expr(CScriptParser::Shift_exprContext * /*ctx*/) override { }

  virtual void enterAdd_expr(CScriptParser::Add_exprContext * /*ctx*/) override { }
  virtual void exitAdd_expr(CScriptParser::Add_exprContext * /*ctx*/) override { }

  virtual void enterMul_expr(CScriptParser::Mul_exprContext * /*ctx*/) override { }
  virtual void exitMul_expr(CScriptParser::Mul_exprContext * /*ctx*/) override { }

  virtual void enterUnary_expr(CScriptParser::Unary_exprContext * /*ctx*/) override { }
  virtual void exitUnary_expr(CScriptParser::Unary_exprContext * /*ctx*/) override { }

  virtual void enterPrimary_expr(CScriptParser::Primary_exprContext * /*ctx*/) override { }
  virtual void exitPrimary_expr(CScriptParser::Primary_exprContext * /*ctx*/) override { }

  virtual void enterCall_args(CScriptParser::Call_argsContext * /*ctx*/) override { }
  virtual void exitCall_args(CScriptParser::Call_argsContext * /*ctx*/) override { }

  virtual void enterNumeric(CScriptParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(CScriptParser::NumericContext * /*ctx*/) override { }

  virtual void enterIf_stmt(CScriptParser::If_stmtContext * /*ctx*/) override { }
  virtual void exitIf_stmt(CScriptParser::If_stmtContext * /*ctx*/) override { }

  virtual void enterWhile_stmt(CScriptParser::While_stmtContext * /*ctx*/) override { }
  virtual void exitWhile_stmt(CScriptParser::While_stmtContext * /*ctx*/) override { }

  virtual void enterFor_stmt(CScriptParser::For_stmtContext * /*ctx*/) override { }
  virtual void exitFor_stmt(CScriptParser::For_stmtContext * /*ctx*/) override { }

  virtual void enterFor_init(CScriptParser::For_initContext * /*ctx*/) override { }
  virtual void exitFor_init(CScriptParser::For_initContext * /*ctx*/) override { }

  virtual void enterFor_cond(CScriptParser::For_condContext * /*ctx*/) override { }
  virtual void exitFor_cond(CScriptParser::For_condContext * /*ctx*/) override { }

  virtual void enterFor_incr(CScriptParser::For_incrContext * /*ctx*/) override { }
  virtual void exitFor_incr(CScriptParser::For_incrContext * /*ctx*/) override { }

  virtual void enterDo_while_stmt(CScriptParser::Do_while_stmtContext * /*ctx*/) override { }
  virtual void exitDo_while_stmt(CScriptParser::Do_while_stmtContext * /*ctx*/) override { }

  virtual void enterTry_catch_stmt(CScriptParser::Try_catch_stmtContext * /*ctx*/) override { }
  virtual void exitTry_catch_stmt(CScriptParser::Try_catch_stmtContext * /*ctx*/) override { }

  virtual void enterCatch_block(CScriptParser::Catch_blockContext * /*ctx*/) override { }
  virtual void exitCatch_block(CScriptParser::Catch_blockContext * /*ctx*/) override { }

  virtual void enterSwitch_stmt(CScriptParser::Switch_stmtContext * /*ctx*/) override { }
  virtual void exitSwitch_stmt(CScriptParser::Switch_stmtContext * /*ctx*/) override { }

  virtual void enterCase_list(CScriptParser::Case_listContext * /*ctx*/) override { }
  virtual void exitCase_list(CScriptParser::Case_listContext * /*ctx*/) override { }

  virtual void enterCase_stmt(CScriptParser::Case_stmtContext * /*ctx*/) override { }
  virtual void exitCase_stmt(CScriptParser::Case_stmtContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

