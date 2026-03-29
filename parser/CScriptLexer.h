
// Generated from D:/MyCode/CScriptEngine/pre/CScript.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CScriptLexer : public antlr4::Lexer {
public:
  enum {
    RETURN = 1, IF = 2, ELSE = 3, WHILE = 4, FOR = 5, DO = 6, SWITCH = 7, 
    CASE = 8, DEFAULT = 9, CONTINUE = 10, BREAK = 11, STRUCT_KW = 12, UNION_KW = 13, 
    ENUM_KW = 14, CONST_KW = 15, EXTERN_KW = 16, INTEGER = 17, DOUBLE = 18, 
    CHAR = 19, STRING = 20, IDENTIFIER = 21, PLUS = 22, MINUS = 23, MUL = 24, 
    DIV = 25, MOD = 26, EQ = 27, NEQ = 28, LT = 29, LTE = 30, GT = 31, GTE = 32, 
    AND = 33, OR = 34, NOT = 35, BITAND = 36, BITOR = 37, XOR = 38, NOTBIT = 39, 
    LSHIFT = 40, RSHIFT = 41, QUESTION = 42, COLON = 43, COMMA = 44, SEMI = 45, 
    LPAREN = 46, RPAREN = 47, LBRACE = 48, RBRACE = 49, LBRACKET = 50, RBRACKET = 51, 
    DOT = 52, ASSIGN = 53, PLUS_EQ = 54, MINUS_EQ = 55, MUL_EQ = 56, DIV_EQ = 57, 
    MOD_EQ = 58, INC = 59, DEC = 60, COMMENT = 61, MULTI_LINE_COMMENT = 62, 
    WS = 63
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

