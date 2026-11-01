
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    RETURN = 8, IF = 9, ELSE = 10, WHILE = 11, FOR = 12, DO = 13, SWITCH = 14, 
    CASE = 15, DEFAULT = 16, CONTINUE = 17, BREAK = 18, STRUCT_KW = 19, 
    UNION_KW = 20, ENUM_KW = 21, CONST_KW = 22, EXTERN_KW = 23, THROW = 24, 
    EXPORT = 25, IMPORT = 26, INCLUDE = 27, SIZEOF = 28, VOID_KW = 29, GOTO = 30, 
    INTEGER = 31, HEX_INTEGER = 32, DOUBLE = 33, CHAR = 34, STRING = 35, 
    ANGLE_STRING = 36, IDENTIFIER = 37, PLUS = 38, MINUS = 39, MUL = 40, 
    DIV = 41, MOD = 42, EQ = 43, NEQ = 44, LT = 45, LTE = 46, GT = 47, GTE = 48, 
    AND = 49, OR = 50, NOT = 51, BITAND = 52, BITOR = 53, XOR = 54, NOTBIT = 55, 
    LSHIFT = 56, RSHIFT = 57, QUESTION = 58, COLON = 59, COMMA = 60, SEMI = 61, 
    LPAREN = 62, RPAREN = 63, LBRACE = 64, RBRACE = 65, LBRACKET = 66, RBRACKET = 67, 
    DOT = 68, ASSIGN = 69, PLUS_EQ = 70, MINUS_EQ = 71, MUL_EQ = 72, DIV_EQ = 73, 
    MOD_EQ = 74, LSHIFT_EQ = 75, RSHIFT_EQ = 76, BITAND_EQ = 77, BITOR_EQ = 78, 
    XOR_EQ = 79, INC = 80, DEC = 81, ELLIPSIS = 82, HASH = 83, COMMENT = 84, 
    MULTI_LINE_COMMENT = 85, WS = 86
  };

  explicit CScriptLexer(antlr4::CharStream *input);

  ~CScriptLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

