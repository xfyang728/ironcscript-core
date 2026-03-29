#pragma once

#include "frontend/generated/CScriptParser.h"

#define TPLUS CScriptParser::PLUS
#define TMINUS CScriptParser::MINUS
#define TMUL CScriptParser::MUL
#define TDIV CScriptParser::DIV
#define TMOD CScriptParser::MOD
#define TINC CScriptParser::INC
#define TDEC CScriptParser::DEC
#define TCLT CScriptParser::LT
#define TCLE CScriptParser::LTE
#define TCGT CScriptParser::GT
#define TCGE CScriptParser::GTE
#define TCEQ CScriptParser::EQ
#define TCNE CScriptParser::NEQ
#define TXOR CScriptParser::XOR
#define TBITAND CScriptParser::BITAND
#define TBITOR CScriptParser::BITOR
#define TLSHIFT CScriptParser::LSHIFT
#define TRSHIFT CScriptParser::RSHIFT
#define TNOTBIT CScriptParser::NOTBIT
#define TAND CScriptParser::AND
#define TOR CScriptParser::OR
#define TNOT CScriptParser::NOT
#define TCOMMA CScriptParser::COMMA

#define TRETURN CScriptParser::RETURN
#define TIF CScriptParser::IF
#define TELSE CScriptParser::ELSE
#define TWHILE CScriptParser::WHILE
#define TFOR CScriptParser::FOR
#define TDO CScriptParser::DO
#define TSWITCH CScriptParser::SWITCH
#define TCASE CScriptParser::CASE
#define TDEFAULT CScriptParser::DEFAULT
#define TCONTINUE CScriptParser::CONTINUE
#define TBREAK CScriptParser::BREAK
#define TSTRUCT CScriptParser::STRUCT_KW
#define TUNION CScriptParser::UNION_KW
#define TENUM CScriptParser::ENUM_KW
#define TCONST CScriptParser::CONST_KW
#define TEXTERN CScriptParser::EXTERN_KW
#define TINTEGER CScriptParser::INTEGER
#define TDOUBLE CScriptParser::DOUBLE
#define TSTRING CScriptParser::STRING
#define TIDENTIFIER CScriptParser::IDENTIFIER
