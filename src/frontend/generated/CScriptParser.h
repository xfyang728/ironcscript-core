
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, RETURN = 9, IF = 10, ELSE = 11, WHILE = 12, FOR = 13, DO = 14, 
    SWITCH = 15, CASE = 16, DEFAULT = 17, CONTINUE = 18, BREAK = 19, STRUCT_KW = 20, 
    UNION_KW = 21, ENUM_KW = 22, CONST_KW = 23, EXTERN_KW = 24, THROW = 25, 
    INTEGER = 26, DOUBLE = 27, CHAR = 28, STRING = 29, ANGLE_STRING = 30, 
    IDENTIFIER = 31, PLUS = 32, MINUS = 33, MUL = 34, DIV = 35, MOD = 36, 
    EQ = 37, NEQ = 38, LT = 39, LTE = 40, GT = 41, GTE = 42, AND = 43, OR = 44, 
    NOT = 45, BITAND = 46, BITOR = 47, XOR = 48, NOTBIT = 49, LSHIFT = 50, 
    RSHIFT = 51, QUESTION = 52, COLON = 53, COMMA = 54, SEMI = 55, LPAREN = 56, 
    RPAREN = 57, LBRACE = 58, RBRACE = 59, LBRACKET = 60, RBRACKET = 61, 
    DOT = 62, ASSIGN = 63, PLUS_EQ = 64, MINUS_EQ = 65, MUL_EQ = 66, DIV_EQ = 67, 
    MOD_EQ = 68, INC = 69, DEC = 70, ELLIPSIS = 71, HASH = 72, COMMENT = 73, 
    MULTI_LINE_COMMENT = 74, WS = 75
  };

  enum {
    RuleProgram = 0, RuleStmt = 1, RuleImport_stmt = 2, RuleInclude_stmt = 3, 
    RuleRegister_callback_stmt = 4, RuleBlock = 5, RuleVar_decl = 6, RuleFunc_decl = 7, 
    RuleExtern_decl = 8, RuleFunc_decl_args = 9, RuleIdent = 10, RuleType = 11, 
    RuleStruct_decl = 12, RuleUnion_decl = 13, RuleStruct_members = 14, 
    RuleEnum_decl = 15, RuleEnum_list = 16, RuleEnum_item = 17, RuleInit_list = 18, 
    RuleExpr = 19, RuleOr_expr = 20, RuleAnd_expr = 21, RuleBit_or_expr = 22, 
    RuleBit_xor_expr = 23, RuleBit_and_expr = 24, RuleEq_expr = 25, RuleRel_expr = 26, 
    RuleShift_expr = 27, RuleAdd_expr = 28, RuleMul_expr = 29, RuleUnary_expr = 30, 
    RulePrimary_expr = 31, RuleCall_args = 32, RuleNumeric = 33, RuleIf_stmt = 34, 
    RuleWhile_stmt = 35, RuleFor_stmt = 36, RuleFor_init = 37, RuleFor_cond = 38, 
    RuleFor_incr = 39, RuleDo_while_stmt = 40, RuleTry_catch_stmt = 41, 
    RuleCatch_block = 42, RuleSwitch_stmt = 43, RuleCase_list = 44, RuleCase_stmt = 45
  };

  explicit CScriptParser(antlr4::TokenStream *input);

  CScriptParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CScriptParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class StmtContext;
  class Import_stmtContext;
  class Include_stmtContext;
  class Register_callback_stmtContext;
  class BlockContext;
  class Var_declContext;
  class Func_declContext;
  class Extern_declContext;
  class Func_decl_argsContext;
  class IdentContext;
  class TypeContext;
  class Struct_declContext;
  class Union_declContext;
  class Struct_membersContext;
  class Enum_declContext;
  class Enum_listContext;
  class Enum_itemContext;
  class Init_listContext;
  class ExprContext;
  class Or_exprContext;
  class And_exprContext;
  class Bit_or_exprContext;
  class Bit_xor_exprContext;
  class Bit_and_exprContext;
  class Eq_exprContext;
  class Rel_exprContext;
  class Shift_exprContext;
  class Add_exprContext;
  class Mul_exprContext;
  class Unary_exprContext;
  class Primary_exprContext;
  class Call_argsContext;
  class NumericContext;
  class If_stmtContext;
  class While_stmtContext;
  class For_stmtContext;
  class For_initContext;
  class For_condContext;
  class For_incrContext;
  class Do_while_stmtContext;
  class Try_catch_stmtContext;
  class Catch_blockContext;
  class Switch_stmtContext;
  class Case_listContext;
  class Case_stmtContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Var_declContext *var_decl();
    antlr4::tree::TerminalNode *SEMI();
    Enum_declContext *enum_decl();
    Func_declContext *func_decl();
    Extern_declContext *extern_decl();
    Struct_declContext *struct_decl();
    Union_declContext *union_decl();
    ExprContext *expr();
    antlr4::tree::TerminalNode *MUL();
    IdentContext *ident();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *RETURN();
    If_stmtContext *if_stmt();
    While_stmtContext *while_stmt();
    For_stmtContext *for_stmt();
    Do_while_stmtContext *do_while_stmt();
    Switch_stmtContext *switch_stmt();
    Try_catch_stmtContext *try_catch_stmt();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *BREAK();
    Register_callback_stmtContext *register_callback_stmt();
    Import_stmtContext *import_stmt();
    Include_stmtContext *include_stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmtContext* stmt();

  class  Import_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *SEMI();
    std::vector<IdentContext *> ident();
    IdentContext* ident(size_t i);
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_stmtContext* import_stmt();

  class  Include_stmtContext : public antlr4::ParserRuleContext {
  public:
    Include_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *ANGLE_STRING();
    antlr4::tree::TerminalNode *HASH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Include_stmtContext* include_stmt();

  class  Register_callback_stmtContext : public antlr4::ParserRuleContext {
  public:
    Register_callback_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentContext *> ident();
    IdentContext* ident(size_t i);
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMI();
    Func_decl_argsContext *func_decl_args();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Register_callback_stmtContext* register_callback_stmt();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  Var_declContext : public antlr4::ParserRuleContext {
  public:
    Var_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<IdentContext *> ident();
    IdentContext* ident(size_t i);
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *LBRACE();
    Init_listContext *init_list();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *CONST_KW();
    antlr4::tree::TerminalNode *STRUCT_KW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Var_declContext* var_decl();

  class  Func_declContext : public antlr4::ParserRuleContext {
  public:
    Func_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    IdentContext *ident();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    Func_decl_argsContext *func_decl_args();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_declContext* func_decl();

  class  Extern_declContext : public antlr4::ParserRuleContext {
  public:
    Extern_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXTERN_KW();
    TypeContext *type();
    IdentContext *ident();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMI();
    Func_decl_argsContext *func_decl_args();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Extern_declContext* extern_decl();

  class  Func_decl_argsContext : public antlr4::ParserRuleContext {
  public:
    Func_decl_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Var_declContext *> var_decl();
    Var_declContext* var_decl(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_decl_argsContext* func_decl_args();

  class  IdentContext : public antlr4::ParserRuleContext {
  public:
    IdentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentContext* ident();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<antlr4::tree::TerminalNode *> MUL();
    antlr4::tree::TerminalNode* MUL(size_t i);
    antlr4::tree::TerminalNode *ENUM_KW();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  Struct_declContext : public antlr4::ParserRuleContext {
  public:
    Struct_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    Struct_membersContext *struct_members();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_declContext* struct_decl();

  class  Union_declContext : public antlr4::ParserRuleContext {
  public:
    Union_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNION_KW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    Struct_membersContext *struct_members();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_declContext* union_decl();

  class  Struct_membersContext : public antlr4::ParserRuleContext {
  public:
    Struct_membersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Var_declContext *> var_decl();
    Var_declContext* var_decl(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_membersContext* struct_members();

  class  Enum_declContext : public antlr4::ParserRuleContext {
  public:
    Enum_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM_KW();
    antlr4::tree::TerminalNode *LBRACE();
    Enum_listContext *enum_list();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_declContext* enum_decl();

  class  Enum_listContext : public antlr4::ParserRuleContext {
  public:
    Enum_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Enum_itemContext *> enum_item();
    Enum_itemContext* enum_item(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_listContext* enum_list();

  class  Enum_itemContext : public antlr4::ParserRuleContext {
  public:
    Enum_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_itemContext* enum_item();

  class  Init_listContext : public antlr4::ParserRuleContext {
  public:
    Init_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Init_listContext* init_list();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    Or_exprContext *or_expr();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COLON();
    Primary_exprContext *primary_expr();
    antlr4::tree::TerminalNode *DOT();
    IdentContext *ident();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *PLUS_EQ();
    antlr4::tree::TerminalNode *MINUS_EQ();
    antlr4::tree::TerminalNode *MUL_EQ();
    antlr4::tree::TerminalNode *DIV_EQ();
    antlr4::tree::TerminalNode *MOD_EQ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  Or_exprContext : public antlr4::ParserRuleContext {
  public:
    Or_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    And_exprContext *and_expr();
    Or_exprContext *or_expr();
    antlr4::tree::TerminalNode *OR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Or_exprContext* or_expr();
  Or_exprContext* or_expr(int precedence);
  class  And_exprContext : public antlr4::ParserRuleContext {
  public:
    And_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bit_or_exprContext *bit_or_expr();
    And_exprContext *and_expr();
    antlr4::tree::TerminalNode *AND();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  And_exprContext* and_expr();
  And_exprContext* and_expr(int precedence);
  class  Bit_or_exprContext : public antlr4::ParserRuleContext {
  public:
    Bit_or_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bit_xor_exprContext *bit_xor_expr();
    Bit_or_exprContext *bit_or_expr();
    antlr4::tree::TerminalNode *BITOR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bit_or_exprContext* bit_or_expr();
  Bit_or_exprContext* bit_or_expr(int precedence);
  class  Bit_xor_exprContext : public antlr4::ParserRuleContext {
  public:
    Bit_xor_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bit_and_exprContext *bit_and_expr();
    Bit_xor_exprContext *bit_xor_expr();
    antlr4::tree::TerminalNode *XOR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bit_xor_exprContext* bit_xor_expr();
  Bit_xor_exprContext* bit_xor_expr(int precedence);
  class  Bit_and_exprContext : public antlr4::ParserRuleContext {
  public:
    Bit_and_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Eq_exprContext *eq_expr();
    Bit_and_exprContext *bit_and_expr();
    antlr4::tree::TerminalNode *BITAND();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bit_and_exprContext* bit_and_expr();
  Bit_and_exprContext* bit_and_expr(int precedence);
  class  Eq_exprContext : public antlr4::ParserRuleContext {
  public:
    Eq_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Rel_exprContext *rel_expr();
    Eq_exprContext *eq_expr();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Eq_exprContext* eq_expr();
  Eq_exprContext* eq_expr(int precedence);
  class  Rel_exprContext : public antlr4::ParserRuleContext {
  public:
    Rel_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Shift_exprContext *shift_expr();
    Rel_exprContext *rel_expr();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LTE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GTE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Rel_exprContext* rel_expr();
  Rel_exprContext* rel_expr(int precedence);
  class  Shift_exprContext : public antlr4::ParserRuleContext {
  public:
    Shift_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Add_exprContext *add_expr();
    Shift_exprContext *shift_expr();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shift_exprContext* shift_expr();
  Shift_exprContext* shift_expr(int precedence);
  class  Add_exprContext : public antlr4::ParserRuleContext {
  public:
    Add_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Mul_exprContext *mul_expr();
    Add_exprContext *add_expr();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Add_exprContext* add_expr();
  Add_exprContext* add_expr(int precedence);
  class  Mul_exprContext : public antlr4::ParserRuleContext {
  public:
    Mul_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_exprContext *unary_expr();
    Mul_exprContext *mul_expr();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mul_exprContext* mul_expr();
  Mul_exprContext* mul_expr(int precedence);
  class  Unary_exprContext : public antlr4::ParserRuleContext {
  public:
    Unary_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_exprContext *primary_expr();
    antlr4::tree::TerminalNode *NOT();
    Unary_exprContext *unary_expr();
    antlr4::tree::TerminalNode *NOTBIT();
    antlr4::tree::TerminalNode *BITAND();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *THROW();
    ExprContext *expr();
    IdentContext *ident();
    antlr4::tree::TerminalNode *INC();
    antlr4::tree::TerminalNode *DEC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unary_exprContext* unary_expr();

  class  Primary_exprContext : public antlr4::ParserRuleContext {
  public:
    Primary_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentContext *> ident();
    IdentContext* ident(size_t i);
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Call_argsContext *call_args();
    antlr4::tree::TerminalNode *LBRACKET();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *INC();
    antlr4::tree::TerminalNode *DEC();
    NumericContext *numeric();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_exprContext* primary_expr();

  class  Call_argsContext : public antlr4::ParserRuleContext {
  public:
    Call_argsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Call_argsContext* call_args();

  class  NumericContext : public antlr4::ParserRuleContext {
  public:
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *DOUBLE();
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumericContext* numeric();

  class  If_stmtContext : public antlr4::ParserRuleContext {
  public:
    If_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    antlr4::tree::TerminalNode *ELSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_stmtContext* if_stmt();

  class  While_stmtContext : public antlr4::ParserRuleContext {
  public:
    While_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  While_stmtContext* while_stmt();

  class  For_stmtContext : public antlr4::ParserRuleContext {
  public:
    For_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    For_initContext *for_init();
    For_condContext *for_cond();
    For_incrContext *for_incr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_stmtContext* for_stmt();

  class  For_initContext : public antlr4::ParserRuleContext {
  public:
    For_initContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Var_declContext *var_decl();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_initContext* for_init();

  class  For_condContext : public antlr4::ParserRuleContext {
  public:
    For_condContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_condContext* for_cond();

  class  For_incrContext : public antlr4::ParserRuleContext {
  public:
    For_incrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_incrContext* for_incr();

  class  Do_while_stmtContext : public antlr4::ParserRuleContext {
  public:
    Do_while_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DO();
    BlockContext *block();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Do_while_stmtContext* do_while_stmt();

  class  Try_catch_stmtContext : public antlr4::ParserRuleContext {
  public:
    Try_catch_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockContext *block();
    std::vector<Catch_blockContext *> catch_block();
    Catch_blockContext* catch_block(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Try_catch_stmtContext* try_catch_stmt();

  class  Catch_blockContext : public antlr4::ParserRuleContext {
  public:
    Catch_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    IdentContext *ident();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    antlr4::tree::TerminalNode *ELLIPSIS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Catch_blockContext* catch_block();

  class  Switch_stmtContext : public antlr4::ParserRuleContext {
  public:
    Switch_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *LBRACE();
    Case_listContext *case_list();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Switch_stmtContext* switch_stmt();

  class  Case_listContext : public antlr4::ParserRuleContext {
  public:
    Case_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Case_stmtContext *> case_stmt();
    Case_stmtContext* case_stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_listContext* case_list();

  class  Case_stmtContext : public antlr4::ParserRuleContext {
  public:
    Case_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CASE();
    ExprContext *expr();
    antlr4::tree::TerminalNode *COLON();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    antlr4::tree::TerminalNode *DEFAULT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_stmtContext* case_stmt();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool or_exprSempred(Or_exprContext *_localctx, size_t predicateIndex);
  bool and_exprSempred(And_exprContext *_localctx, size_t predicateIndex);
  bool bit_or_exprSempred(Bit_or_exprContext *_localctx, size_t predicateIndex);
  bool bit_xor_exprSempred(Bit_xor_exprContext *_localctx, size_t predicateIndex);
  bool bit_and_exprSempred(Bit_and_exprContext *_localctx, size_t predicateIndex);
  bool eq_exprSempred(Eq_exprContext *_localctx, size_t predicateIndex);
  bool rel_exprSempred(Rel_exprContext *_localctx, size_t predicateIndex);
  bool shift_exprSempred(Shift_exprContext *_localctx, size_t predicateIndex);
  bool add_exprSempred(Add_exprContext *_localctx, size_t predicateIndex);
  bool mul_exprSempred(Mul_exprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

