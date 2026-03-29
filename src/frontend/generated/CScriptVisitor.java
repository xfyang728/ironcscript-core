// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link CScriptParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface CScriptVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link CScriptParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(CScriptParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmt(CScriptParser.StmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlock(CScriptParser.BlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#var_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVar_decl(CScriptParser.Var_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#func_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunc_decl(CScriptParser.Func_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#extern_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExtern_decl(CScriptParser.Extern_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#func_decl_args}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunc_decl_args(CScriptParser.Func_decl_argsContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#ident}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdent(CScriptParser.IdentContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(CScriptParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#struct_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_decl(CScriptParser.Struct_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#union_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnion_decl(CScriptParser.Union_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#struct_members}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStruct_members(CScriptParser.Struct_membersContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#enum_decl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_decl(CScriptParser.Enum_declContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#enum_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_list(CScriptParser.Enum_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#enum_item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnum_item(CScriptParser.Enum_itemContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#init_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInit_list(CScriptParser.Init_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpr(CScriptParser.ExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#or_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOr_expr(CScriptParser.Or_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#and_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAnd_expr(CScriptParser.And_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#bit_or_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBit_or_expr(CScriptParser.Bit_or_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#bit_xor_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBit_xor_expr(CScriptParser.Bit_xor_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#bit_and_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBit_and_expr(CScriptParser.Bit_and_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#eq_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEq_expr(CScriptParser.Eq_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#rel_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRel_expr(CScriptParser.Rel_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#shift_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitShift_expr(CScriptParser.Shift_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#add_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAdd_expr(CScriptParser.Add_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#mul_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMul_expr(CScriptParser.Mul_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#unary_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnary_expr(CScriptParser.Unary_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#primary_expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrimary_expr(CScriptParser.Primary_exprContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#call_args}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCall_args(CScriptParser.Call_argsContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#numeric}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNumeric(CScriptParser.NumericContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#if_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIf_stmt(CScriptParser.If_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#while_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhile_stmt(CScriptParser.While_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#for_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFor_stmt(CScriptParser.For_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#for_init}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFor_init(CScriptParser.For_initContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#for_cond}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFor_cond(CScriptParser.For_condContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#for_incr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFor_incr(CScriptParser.For_incrContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#do_while_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDo_while_stmt(CScriptParser.Do_while_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#switch_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSwitch_stmt(CScriptParser.Switch_stmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#case_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCase_list(CScriptParser.Case_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link CScriptParser#case_stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCase_stmt(CScriptParser.Case_stmtContext ctx);
}