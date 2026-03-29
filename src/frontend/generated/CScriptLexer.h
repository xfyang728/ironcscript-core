
// Generated from D:/MyCode/CScriptEngine/src/frontend/parser/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, RETURN = 9, IF = 10, ELSE = 11, WHILE = 12, FOR = 13, DO = 14, 
    SWITCH = 15, CASE = 16, DEFAULT = 17, CONTINUE = 18, BREAK = 19, STRUCT_KW = 20, 
    UNION_KW = 21, ENUM_KW = 22, CONST_KW = 23, EXTERN_KW = 24, THROW = 25, 
    INTEGER = 26, DOUBLE = 27, CHAR = 28, STRING = 29, IDENTIFIER = 30, 
    PLUS = 31, MINUS = 32, MUL = 33, DIV = 34, MOD = 35, EQ = 36, NEQ = 37, 
    LT = 38, LTE = 39, GT = 40, GTE = 41, AND = 42, OR = 43, NOT = 44, BITAND = 45, 
    BITOR = 46, XOR = 47, NOTBIT = 48, LSHIFT = 49, RSHIFT = 50, QUESTION = 51, 
    COLON = 52, COMMA = 53, SEMI = 54, LPAREN = 55, RPAREN = 56, LBRACE = 57, 
    RBRACE = 58, LBRACKET = 59, RBRACKET = 60, DOT = 61, ASSIGN = 62, PLUS_EQ = 63, 
    MINUS_EQ = 64, MUL_EQ = 65, DIV_EQ = 66, MOD_EQ = 67, INC = 68, DEC = 69, 
    ELLIPSIS = 70, COMMENT = 71, MULTI_LINE_COMMENT = 72, WS = 73
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

