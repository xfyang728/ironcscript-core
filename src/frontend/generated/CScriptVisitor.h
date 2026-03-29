
// Generated from D:/MyCode/CScriptEngine/src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CScriptParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CScriptParser.
 */
class  CScriptVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CScriptParser.
   */
    virtual std::any visitProgram(CScriptParser::ProgramContext *context) = 0;

    virtual std::any visitStmt(CScriptParser::StmtContext *context) = 0;

    virtual std::any visitImport_stmt(CScriptParser::Import_stmtContext *context) = 0;

    virtual std::any visitInclude_stmt(CScriptParser::Include_stmtContext *context) = 0;

    virtual std::any visitRegister_callback_stmt(CScriptParser::Register_callback_stmtContext *context) = 0;

    virtual std::any visitBlock(CScriptParser::BlockContext *context) = 0;

    virtual std::any visitVar_decl(CScriptParser::Var_declContext *context) = 0;

    virtual std::any visitFunc_decl(CScriptParser::Func_declContext *context) = 0;

    virtual std::any visitExtern_decl(CScriptParser::Extern_declContext *context) = 0;

    virtual std::any visitFunc_decl_args(CScriptParser::Func_decl_argsContext *context) = 0;

    virtual std::any visitIdent(CScriptParser::IdentContext *context) = 0;

    virtual std::any visitType(CScriptParser::TypeContext *context) = 0;

    virtual std::any visitStruct_decl(CScriptParser::Struct_declContext *context) = 0;

    virtual std::any visitUnion_decl(CScriptParser::Union_declContext *context) = 0;

    virtual std::any visitStruct_members(CScriptParser::Struct_membersContext *context) = 0;

    virtual std::any visitEnum_decl(CScriptParser::Enum_declContext *context) = 0;

    virtual std::any visitEnum_list(CScriptParser::Enum_listContext *context) = 0;

    virtual std::any visitEnum_item(CScriptParser::Enum_itemContext *context) = 0;

    virtual std::any visitInit_list(CScriptParser::Init_listContext *context) = 0;

    virtual std::any visitExpr(CScriptParser::ExprContext *context) = 0;

    virtual std::any visitOr_expr(CScriptParser::Or_exprContext *context) = 0;

    virtual std::any visitAnd_expr(CScriptParser::And_exprContext *context) = 0;

    virtual std::any visitBit_or_expr(CScriptParser::Bit_or_exprContext *context) = 0;

    virtual std::any visitBit_xor_expr(CScriptParser::Bit_xor_exprContext *context) = 0;

    virtual std::any visitBit_and_expr(CScriptParser::Bit_and_exprContext *context) = 0;

    virtual std::any visitEq_expr(CScriptParser::Eq_exprContext *context) = 0;

    virtual std::any visitRel_expr(CScriptParser::Rel_exprContext *context) = 0;

    virtual std::any visitShift_expr(CScriptParser::Shift_exprContext *context) = 0;

    virtual std::any visitAdd_expr(CScriptParser::Add_exprContext *context) = 0;

    virtual std::any visitMul_expr(CScriptParser::Mul_exprContext *context) = 0;

    virtual std::any visitUnary_expr(CScriptParser::Unary_exprContext *context) = 0;

    virtual std::any visitPrimary_expr(CScriptParser::Primary_exprContext *context) = 0;

    virtual std::any visitCall_args(CScriptParser::Call_argsContext *context) = 0;

    virtual std::any visitNumeric(CScriptParser::NumericContext *context) = 0;

    virtual std::any visitIf_stmt(CScriptParser::If_stmtContext *context) = 0;

    virtual std::any visitWhile_stmt(CScriptParser::While_stmtContext *context) = 0;

    virtual std::any visitFor_stmt(CScriptParser::For_stmtContext *context) = 0;

    virtual std::any visitFor_init(CScriptParser::For_initContext *context) = 0;

    virtual std::any visitFor_cond(CScriptParser::For_condContext *context) = 0;

    virtual std::any visitFor_incr(CScriptParser::For_incrContext *context) = 0;

    virtual std::any visitDo_while_stmt(CScriptParser::Do_while_stmtContext *context) = 0;

    virtual std::any visitTry_catch_stmt(CScriptParser::Try_catch_stmtContext *context) = 0;

    virtual std::any visitCatch_block(CScriptParser::Catch_blockContext *context) = 0;

    virtual std::any visitSwitch_stmt(CScriptParser::Switch_stmtContext *context) = 0;

    virtual std::any visitCase_list(CScriptParser::Case_listContext *context) = 0;

    virtual std::any visitCase_stmt(CScriptParser::Case_stmtContext *context) = 0;


};

