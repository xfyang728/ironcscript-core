
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, RETURN = 7, 
    IF = 8, ELSE = 9, WHILE = 10, FOR = 11, DO = 12, SWITCH = 13, CASE = 14, 
    DEFAULT = 15, CONTINUE = 16, BREAK = 17, STRUCT_KW = 18, UNION_KW = 19, 
    ENUM_KW = 20, CONST_KW = 21, EXTERN_KW = 22, THROW = 23, EXPORT = 24, 
    IMPORT = 25, INCLUDE = 26, INTEGER = 27, DOUBLE = 28, CHAR = 29, STRING = 30, 
    ANGLE_STRING = 31, IDENTIFIER = 32, PLUS = 33, MINUS = 34, MUL = 35, 
    DIV = 36, MOD = 37, EQ = 38, NEQ = 39, LT = 40, LTE = 41, GT = 42, GTE = 43, 
    AND = 44, OR = 45, NOT = 46, BITAND = 47, BITOR = 48, XOR = 49, NOTBIT = 50, 
    LSHIFT = 51, RSHIFT = 52, QUESTION = 53, COLON = 54, COMMA = 55, SEMI = 56, 
    LPAREN = 57, RPAREN = 58, LBRACE = 59, RBRACE = 60, LBRACKET = 61, RBRACKET = 62, 
    DOT = 63, ASSIGN = 64, PLUS_EQ = 65, MINUS_EQ = 66, MUL_EQ = 67, DIV_EQ = 68, 
    MOD_EQ = 69, INC = 70, DEC = 71, ELLIPSIS = 72, HASH = 73, COMMENT = 74, 
    MULTI_LINE_COMMENT = 75, WS = 76
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

