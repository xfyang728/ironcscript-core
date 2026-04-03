
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptLexer : public antlr4::Lexer {
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

