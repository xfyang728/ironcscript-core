
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2


#include "CScriptListener.h"
#include "CScriptVisitor.h"

#include "CScriptParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CScriptParserStaticData final {
  CScriptParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CScriptParserStaticData(const CScriptParserStaticData&) = delete;
  CScriptParserStaticData(CScriptParserStaticData&&) = delete;
  CScriptParserStaticData& operator=(const CScriptParserStaticData&) = delete;
  CScriptParserStaticData& operator=(CScriptParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cscriptParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CScriptParserStaticData> cscriptParserStaticData = nullptr;

void cscriptParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cscriptParserStaticData != nullptr) {
    return;
  }
#else
  assert(cscriptParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CScriptParserStaticData>(
    std::vector<std::string>{
      "program", "stmt", "import_stmt", "include_stmt", "register_callback_stmt", 
      "export_stmt", "block", "body", "single_stmt", "var_decl", "func_decl", 
      "extern_decl", "func_decl_args", "ident", "type", "struct_decl", "union_decl", 
      "struct_members", "enum_decl", "enum_list", "enum_item", "init_list", 
      "expr", "or_expr", "and_expr", "bit_or_expr", "bit_xor_expr", "bit_and_expr", 
      "eq_expr", "rel_expr", "shift_expr", "add_expr", "mul_expr", "unary_expr", 
      "primary_expr", "call_args", "numeric", "if_stmt", "while_stmt", "for_stmt", 
      "for_init", "for_cond", "for_incr", "do_while_stmt", "try_catch_stmt", 
      "catch_block", "switch_stmt", "case_list", "case_stmt"
    },
    std::vector<std::string>{
      "", "'as'", "'from'", "'register'", "'::'", "'try'", "'catch'", "'return'", 
      "'if'", "'else'", "'while'", "'for'", "'do'", "'switch'", "'case'", 
      "'default'", "'continue'", "'break'", "'struct'", "'union'", "'enum'", 
      "'const'", "'extern'", "'throw'", "'export'", "'import'", "'include'", 
      "", "", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'%'", "'=='", 
      "'!='", "'<'", "'<='", "'>'", "'>='", "'&&'", "'||'", "'!'", "'&'", 
      "'|'", "'^'", "'~'", "'<<'", "'>>'", "'\\u003F'", "':'", "','", "';'", 
      "'('", "')'", "'{'", "'}'", "'['", "']'", "'.'", "'='", "'+='", "'-='", 
      "'*='", "'/='", "'%='", "'++'", "'--'", "'...'", "'#'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "RETURN", "IF", "ELSE", "WHILE", "FOR", 
      "DO", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "BREAK", "STRUCT_KW", 
      "UNION_KW", "ENUM_KW", "CONST_KW", "EXTERN_KW", "THROW", "EXPORT", 
      "IMPORT", "INCLUDE", "INTEGER", "DOUBLE", "CHAR", "STRING", "ANGLE_STRING", 
      "IDENTIFIER", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "LT", 
      "LTE", "GT", "GTE", "AND", "OR", "NOT", "BITAND", "BITOR", "XOR", 
      "NOTBIT", "LSHIFT", "RSHIFT", "QUESTION", "COLON", "COMMA", "SEMI", 
      "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "DOT", 
      "ASSIGN", "PLUS_EQ", "MINUS_EQ", "MUL_EQ", "DIV_EQ", "MOD_EQ", "INC", 
      "DEC", "ELLIPSIS", "HASH", "COMMENT", "MULTI_LINE_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,76,742,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,1,0,5,
  	0,100,8,0,10,0,12,0,103,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,148,8,
  	1,1,2,1,2,1,2,1,2,3,2,154,8,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,162,8,2,10,
  	2,12,2,165,9,2,1,2,1,2,1,2,1,2,1,2,3,2,172,8,2,1,3,3,3,175,8,3,1,3,1,
  	3,1,3,3,3,180,8,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,188,8,4,1,4,1,4,1,4,1,5,
  	1,5,1,5,3,5,196,8,5,1,5,1,5,1,5,1,5,3,5,202,8,5,1,6,1,6,5,6,206,8,6,10,
  	6,12,6,209,9,6,1,6,1,6,1,6,3,6,214,8,6,1,7,1,7,3,7,218,8,7,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,3,8,244,8,8,1,9,1,9,1,9,1,9,3,9,250,8,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,262,8,9,1,9,1,9,1,9,1,9,1,9,3,9,269,8,9,
  	1,9,1,9,1,9,1,9,1,9,3,9,276,8,9,1,9,1,9,1,9,1,9,1,9,3,9,283,8,9,3,9,285,
  	8,9,1,10,1,10,1,10,1,10,3,10,291,8,10,1,10,1,10,1,10,1,11,1,11,1,11,1,
  	11,1,11,3,11,301,8,11,1,11,1,11,1,11,1,12,1,12,1,12,5,12,309,8,12,10,
  	12,12,12,312,9,12,1,13,1,13,1,14,1,14,5,14,318,8,14,10,14,12,14,321,9,
  	14,1,14,1,14,3,14,325,8,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,5,17,344,8,17,10,17,12,17,
  	347,9,17,1,18,1,18,3,18,351,8,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,
  	19,5,19,361,8,19,10,19,12,19,364,9,19,1,20,1,20,1,20,3,20,369,8,20,1,
  	21,1,21,1,21,5,21,374,8,21,10,21,12,21,377,9,21,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,3,22,428,8,22,1,23,1,23,1,23,1,23,1,23,1,23,5,23,436,8,23,
  	10,23,12,23,439,9,23,1,24,1,24,1,24,1,24,1,24,1,24,5,24,447,8,24,10,24,
  	12,24,450,9,24,1,25,1,25,1,25,1,25,1,25,1,25,5,25,458,8,25,10,25,12,25,
  	461,9,25,1,26,1,26,1,26,1,26,1,26,1,26,5,26,469,8,26,10,26,12,26,472,
  	9,26,1,27,1,27,1,27,1,27,1,27,1,27,5,27,480,8,27,10,27,12,27,483,9,27,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,5,28,494,8,28,10,28,12,28,
  	497,9,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,5,29,514,8,29,10,29,12,29,517,9,29,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,5,30,528,8,30,10,30,12,30,531,9,30,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,1,31,5,31,542,8,31,10,31,12,31,545,9,31,
  	1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,5,32,559,
  	8,32,10,32,12,32,562,9,32,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,585,
  	8,33,1,34,1,34,1,34,3,34,590,8,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,3,34,604,8,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,34,3,34,628,8,34,1,35,1,35,1,35,5,35,633,8,35,10,35,12,35,636,
  	9,35,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,647,8,37,1,38,
  	1,38,1,38,1,38,1,38,1,38,1,39,1,39,1,39,3,39,658,8,39,1,39,1,39,3,39,
  	662,8,39,1,39,1,39,3,39,666,8,39,1,39,1,39,1,39,1,40,1,40,3,40,673,8,
  	40,1,41,1,41,1,42,1,42,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,686,8,
  	43,1,44,1,44,1,44,4,44,691,8,44,11,44,12,44,692,1,45,1,45,1,45,1,45,1,
  	45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,3,45,707,8,45,1,46,1,46,1,46,1,
  	46,1,46,1,46,1,46,1,46,1,47,5,47,718,8,47,10,47,12,47,721,9,47,1,48,1,
  	48,1,48,1,48,5,48,727,8,48,10,48,12,48,730,9,48,1,48,1,48,1,48,5,48,735,
  	8,48,10,48,12,48,738,9,48,3,48,740,8,48,1,48,0,10,46,48,50,52,54,56,58,
  	60,62,64,49,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
  	42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,
  	88,90,92,94,96,0,2,1,0,30,31,1,0,27,30,818,0,101,1,0,0,0,2,147,1,0,0,
  	0,4,171,1,0,0,0,6,174,1,0,0,0,8,181,1,0,0,0,10,201,1,0,0,0,12,213,1,0,
  	0,0,14,217,1,0,0,0,16,243,1,0,0,0,18,284,1,0,0,0,20,286,1,0,0,0,22,295,
  	1,0,0,0,24,305,1,0,0,0,26,313,1,0,0,0,28,324,1,0,0,0,30,326,1,0,0,0,32,
  	332,1,0,0,0,34,338,1,0,0,0,36,348,1,0,0,0,38,357,1,0,0,0,40,365,1,0,0,
  	0,42,370,1,0,0,0,44,427,1,0,0,0,46,429,1,0,0,0,48,440,1,0,0,0,50,451,
  	1,0,0,0,52,462,1,0,0,0,54,473,1,0,0,0,56,484,1,0,0,0,58,498,1,0,0,0,60,
  	518,1,0,0,0,62,532,1,0,0,0,64,546,1,0,0,0,66,584,1,0,0,0,68,627,1,0,0,
  	0,70,629,1,0,0,0,72,637,1,0,0,0,74,639,1,0,0,0,76,648,1,0,0,0,78,654,
  	1,0,0,0,80,672,1,0,0,0,82,674,1,0,0,0,84,676,1,0,0,0,86,678,1,0,0,0,88,
  	687,1,0,0,0,90,706,1,0,0,0,92,708,1,0,0,0,94,719,1,0,0,0,96,739,1,0,0,
  	0,98,100,3,2,1,0,99,98,1,0,0,0,100,103,1,0,0,0,101,99,1,0,0,0,101,102,
  	1,0,0,0,102,104,1,0,0,0,103,101,1,0,0,0,104,105,5,0,0,1,105,1,1,0,0,0,
  	106,107,3,18,9,0,107,108,5,56,0,0,108,148,1,0,0,0,109,148,3,36,18,0,110,
  	148,3,20,10,0,111,148,3,22,11,0,112,148,3,30,15,0,113,114,3,30,15,0,114,
  	115,5,56,0,0,115,148,1,0,0,0,116,148,3,32,16,0,117,118,3,32,16,0,118,
  	119,5,56,0,0,119,148,1,0,0,0,120,121,3,44,22,0,121,122,5,56,0,0,122,148,
  	1,0,0,0,123,124,5,35,0,0,124,125,3,26,13,0,125,126,5,64,0,0,126,127,3,
  	44,22,0,127,128,5,56,0,0,128,148,1,0,0,0,129,130,5,7,0,0,130,131,3,44,
  	22,0,131,132,5,56,0,0,132,148,1,0,0,0,133,148,3,74,37,0,134,148,3,76,
  	38,0,135,148,3,78,39,0,136,148,3,86,43,0,137,148,3,92,46,0,138,148,3,
  	88,44,0,139,140,5,16,0,0,140,148,5,56,0,0,141,142,5,17,0,0,142,148,5,
  	56,0,0,143,148,3,8,4,0,144,148,3,4,2,0,145,148,3,6,3,0,146,148,3,10,5,
  	0,147,106,1,0,0,0,147,109,1,0,0,0,147,110,1,0,0,0,147,111,1,0,0,0,147,
  	112,1,0,0,0,147,113,1,0,0,0,147,116,1,0,0,0,147,117,1,0,0,0,147,120,1,
  	0,0,0,147,123,1,0,0,0,147,129,1,0,0,0,147,133,1,0,0,0,147,134,1,0,0,0,
  	147,135,1,0,0,0,147,136,1,0,0,0,147,137,1,0,0,0,147,138,1,0,0,0,147,139,
  	1,0,0,0,147,141,1,0,0,0,147,143,1,0,0,0,147,144,1,0,0,0,147,145,1,0,0,
  	0,147,146,1,0,0,0,148,3,1,0,0,0,149,150,5,25,0,0,150,153,5,30,0,0,151,
  	152,5,1,0,0,152,154,3,26,13,0,153,151,1,0,0,0,153,154,1,0,0,0,154,155,
  	1,0,0,0,155,172,5,56,0,0,156,157,5,25,0,0,157,158,5,59,0,0,158,163,3,
  	26,13,0,159,160,5,55,0,0,160,162,3,26,13,0,161,159,1,0,0,0,162,165,1,
  	0,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,166,1,0,0,0,165,163,1,0,0,0,
  	166,167,5,60,0,0,167,168,5,2,0,0,168,169,5,30,0,0,169,170,5,56,0,0,170,
  	172,1,0,0,0,171,149,1,0,0,0,171,156,1,0,0,0,172,5,1,0,0,0,173,175,5,73,
  	0,0,174,173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,177,5,26,0,0,
  	177,179,7,0,0,0,178,180,5,56,0,0,179,178,1,0,0,0,179,180,1,0,0,0,180,
  	7,1,0,0,0,181,182,5,3,0,0,182,183,3,26,13,0,183,184,5,1,0,0,184,185,3,
  	26,13,0,185,187,5,57,0,0,186,188,3,24,12,0,187,186,1,0,0,0,187,188,1,
  	0,0,0,188,189,1,0,0,0,189,190,5,58,0,0,190,191,5,56,0,0,191,9,1,0,0,0,
  	192,193,5,24,0,0,193,195,3,18,9,0,194,196,5,56,0,0,195,194,1,0,0,0,195,
  	196,1,0,0,0,196,202,1,0,0,0,197,198,5,24,0,0,198,202,3,20,10,0,199,200,
  	5,24,0,0,200,202,3,36,18,0,201,192,1,0,0,0,201,197,1,0,0,0,201,199,1,
  	0,0,0,202,11,1,0,0,0,203,207,5,59,0,0,204,206,3,2,1,0,205,204,1,0,0,0,
  	206,209,1,0,0,0,207,205,1,0,0,0,207,208,1,0,0,0,208,210,1,0,0,0,209,207,
  	1,0,0,0,210,214,5,60,0,0,211,212,5,59,0,0,212,214,5,60,0,0,213,203,1,
  	0,0,0,213,211,1,0,0,0,214,13,1,0,0,0,215,218,3,12,6,0,216,218,3,16,8,
  	0,217,215,1,0,0,0,217,216,1,0,0,0,218,15,1,0,0,0,219,220,3,44,22,0,220,
  	221,5,56,0,0,221,244,1,0,0,0,222,223,5,35,0,0,223,224,3,26,13,0,224,225,
  	5,64,0,0,225,226,3,44,22,0,226,227,5,56,0,0,227,244,1,0,0,0,228,229,5,
  	7,0,0,229,230,3,44,22,0,230,231,5,56,0,0,231,244,1,0,0,0,232,244,3,74,
  	37,0,233,244,3,76,38,0,234,244,3,78,39,0,235,244,3,86,43,0,236,244,3,
  	92,46,0,237,244,3,88,44,0,238,239,5,16,0,0,239,244,5,56,0,0,240,241,5,
  	17,0,0,241,244,5,56,0,0,242,244,3,8,4,0,243,219,1,0,0,0,243,222,1,0,0,
  	0,243,228,1,0,0,0,243,232,1,0,0,0,243,233,1,0,0,0,243,234,1,0,0,0,243,
  	235,1,0,0,0,243,236,1,0,0,0,243,237,1,0,0,0,243,238,1,0,0,0,243,240,1,
  	0,0,0,243,242,1,0,0,0,244,17,1,0,0,0,245,246,3,28,14,0,246,249,3,26,13,
  	0,247,248,5,64,0,0,248,250,3,44,22,0,249,247,1,0,0,0,249,250,1,0,0,0,
  	250,285,1,0,0,0,251,252,3,28,14,0,252,253,3,26,13,0,253,254,5,61,0,0,
  	254,255,3,44,22,0,255,261,5,62,0,0,256,257,5,64,0,0,257,258,5,59,0,0,
  	258,259,3,42,21,0,259,260,5,60,0,0,260,262,1,0,0,0,261,256,1,0,0,0,261,
  	262,1,0,0,0,262,285,1,0,0,0,263,264,3,28,14,0,264,265,5,35,0,0,265,268,
  	3,26,13,0,266,267,5,64,0,0,267,269,3,44,22,0,268,266,1,0,0,0,268,269,
  	1,0,0,0,269,285,1,0,0,0,270,271,5,21,0,0,271,272,3,28,14,0,272,275,3,
  	26,13,0,273,274,5,64,0,0,274,276,3,44,22,0,275,273,1,0,0,0,275,276,1,
  	0,0,0,276,285,1,0,0,0,277,278,5,18,0,0,278,279,3,26,13,0,279,282,3,26,
  	13,0,280,281,5,64,0,0,281,283,3,44,22,0,282,280,1,0,0,0,282,283,1,0,0,
  	0,283,285,1,0,0,0,284,245,1,0,0,0,284,251,1,0,0,0,284,263,1,0,0,0,284,
  	270,1,0,0,0,284,277,1,0,0,0,285,19,1,0,0,0,286,287,3,28,14,0,287,288,
  	3,26,13,0,288,290,5,57,0,0,289,291,3,24,12,0,290,289,1,0,0,0,290,291,
  	1,0,0,0,291,292,1,0,0,0,292,293,5,58,0,0,293,294,3,12,6,0,294,21,1,0,
  	0,0,295,296,5,22,0,0,296,297,3,28,14,0,297,298,3,26,13,0,298,300,5,57,
  	0,0,299,301,3,24,12,0,300,299,1,0,0,0,300,301,1,0,0,0,301,302,1,0,0,0,
  	302,303,5,58,0,0,303,304,5,56,0,0,304,23,1,0,0,0,305,310,3,18,9,0,306,
  	307,5,55,0,0,307,309,3,18,9,0,308,306,1,0,0,0,309,312,1,0,0,0,310,308,
  	1,0,0,0,310,311,1,0,0,0,311,25,1,0,0,0,312,310,1,0,0,0,313,314,5,32,0,
  	0,314,27,1,0,0,0,315,319,5,32,0,0,316,318,5,35,0,0,317,316,1,0,0,0,318,
  	321,1,0,0,0,319,317,1,0,0,0,319,320,1,0,0,0,320,325,1,0,0,0,321,319,1,
  	0,0,0,322,323,5,20,0,0,323,325,5,32,0,0,324,315,1,0,0,0,324,322,1,0,0,
  	0,325,29,1,0,0,0,326,327,5,18,0,0,327,328,5,32,0,0,328,329,5,59,0,0,329,
  	330,3,34,17,0,330,331,5,60,0,0,331,31,1,0,0,0,332,333,5,19,0,0,333,334,
  	5,32,0,0,334,335,5,59,0,0,335,336,3,34,17,0,336,337,5,60,0,0,337,33,1,
  	0,0,0,338,339,3,18,9,0,339,345,5,56,0,0,340,341,3,18,9,0,341,342,5,56,
  	0,0,342,344,1,0,0,0,343,340,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,345,
  	346,1,0,0,0,346,35,1,0,0,0,347,345,1,0,0,0,348,350,5,20,0,0,349,351,5,
  	32,0,0,350,349,1,0,0,0,350,351,1,0,0,0,351,352,1,0,0,0,352,353,5,59,0,
  	0,353,354,3,38,19,0,354,355,5,60,0,0,355,356,5,56,0,0,356,37,1,0,0,0,
  	357,362,3,40,20,0,358,359,5,55,0,0,359,361,3,40,20,0,360,358,1,0,0,0,
  	361,364,1,0,0,0,362,360,1,0,0,0,362,363,1,0,0,0,363,39,1,0,0,0,364,362,
  	1,0,0,0,365,368,3,26,13,0,366,367,5,64,0,0,367,369,3,44,22,0,368,366,
  	1,0,0,0,368,369,1,0,0,0,369,41,1,0,0,0,370,375,3,44,22,0,371,372,5,55,
  	0,0,372,374,3,44,22,0,373,371,1,0,0,0,374,377,1,0,0,0,375,373,1,0,0,0,
  	375,376,1,0,0,0,376,43,1,0,0,0,377,375,1,0,0,0,378,379,5,57,0,0,379,380,
  	3,28,14,0,380,381,5,58,0,0,381,382,3,44,22,0,382,428,1,0,0,0,383,384,
  	3,46,23,0,384,385,5,53,0,0,385,386,3,44,22,0,386,387,5,54,0,0,387,388,
  	3,44,22,0,388,428,1,0,0,0,389,390,3,68,34,0,390,391,5,63,0,0,391,392,
  	3,26,13,0,392,393,5,64,0,0,393,394,3,44,22,0,394,428,1,0,0,0,395,396,
  	3,26,13,0,396,397,5,61,0,0,397,398,3,44,22,0,398,399,5,62,0,0,399,400,
  	5,64,0,0,400,401,3,44,22,0,401,428,1,0,0,0,402,403,3,26,13,0,403,404,
  	5,64,0,0,404,405,3,44,22,0,405,428,1,0,0,0,406,407,3,26,13,0,407,408,
  	5,65,0,0,408,409,3,44,22,0,409,428,1,0,0,0,410,411,3,26,13,0,411,412,
  	5,66,0,0,412,413,3,44,22,0,413,428,1,0,0,0,414,415,3,26,13,0,415,416,
  	5,67,0,0,416,417,3,44,22,0,417,428,1,0,0,0,418,419,3,26,13,0,419,420,
  	5,68,0,0,420,421,3,44,22,0,421,428,1,0,0,0,422,423,3,26,13,0,423,424,
  	5,69,0,0,424,425,3,44,22,0,425,428,1,0,0,0,426,428,3,46,23,0,427,378,
  	1,0,0,0,427,383,1,0,0,0,427,389,1,0,0,0,427,395,1,0,0,0,427,402,1,0,0,
  	0,427,406,1,0,0,0,427,410,1,0,0,0,427,414,1,0,0,0,427,418,1,0,0,0,427,
  	422,1,0,0,0,427,426,1,0,0,0,428,45,1,0,0,0,429,430,6,23,-1,0,430,431,
  	3,48,24,0,431,437,1,0,0,0,432,433,10,1,0,0,433,434,5,45,0,0,434,436,3,
  	48,24,0,435,432,1,0,0,0,436,439,1,0,0,0,437,435,1,0,0,0,437,438,1,0,0,
  	0,438,47,1,0,0,0,439,437,1,0,0,0,440,441,6,24,-1,0,441,442,3,50,25,0,
  	442,448,1,0,0,0,443,444,10,1,0,0,444,445,5,44,0,0,445,447,3,50,25,0,446,
  	443,1,0,0,0,447,450,1,0,0,0,448,446,1,0,0,0,448,449,1,0,0,0,449,49,1,
  	0,0,0,450,448,1,0,0,0,451,452,6,25,-1,0,452,453,3,52,26,0,453,459,1,0,
  	0,0,454,455,10,1,0,0,455,456,5,48,0,0,456,458,3,52,26,0,457,454,1,0,0,
  	0,458,461,1,0,0,0,459,457,1,0,0,0,459,460,1,0,0,0,460,51,1,0,0,0,461,
  	459,1,0,0,0,462,463,6,26,-1,0,463,464,3,54,27,0,464,470,1,0,0,0,465,466,
  	10,1,0,0,466,467,5,49,0,0,467,469,3,54,27,0,468,465,1,0,0,0,469,472,1,
  	0,0,0,470,468,1,0,0,0,470,471,1,0,0,0,471,53,1,0,0,0,472,470,1,0,0,0,
  	473,474,6,27,-1,0,474,475,3,56,28,0,475,481,1,0,0,0,476,477,10,1,0,0,
  	477,478,5,47,0,0,478,480,3,56,28,0,479,476,1,0,0,0,480,483,1,0,0,0,481,
  	479,1,0,0,0,481,482,1,0,0,0,482,55,1,0,0,0,483,481,1,0,0,0,484,485,6,
  	28,-1,0,485,486,3,58,29,0,486,495,1,0,0,0,487,488,10,2,0,0,488,489,5,
  	38,0,0,489,494,3,58,29,0,490,491,10,1,0,0,491,492,5,39,0,0,492,494,3,
  	58,29,0,493,487,1,0,0,0,493,490,1,0,0,0,494,497,1,0,0,0,495,493,1,0,0,
  	0,495,496,1,0,0,0,496,57,1,0,0,0,497,495,1,0,0,0,498,499,6,29,-1,0,499,
  	500,3,60,30,0,500,515,1,0,0,0,501,502,10,4,0,0,502,503,5,40,0,0,503,514,
  	3,60,30,0,504,505,10,3,0,0,505,506,5,41,0,0,506,514,3,60,30,0,507,508,
  	10,2,0,0,508,509,5,42,0,0,509,514,3,60,30,0,510,511,10,1,0,0,511,512,
  	5,43,0,0,512,514,3,60,30,0,513,501,1,0,0,0,513,504,1,0,0,0,513,507,1,
  	0,0,0,513,510,1,0,0,0,514,517,1,0,0,0,515,513,1,0,0,0,515,516,1,0,0,0,
  	516,59,1,0,0,0,517,515,1,0,0,0,518,519,6,30,-1,0,519,520,3,62,31,0,520,
  	529,1,0,0,0,521,522,10,2,0,0,522,523,5,51,0,0,523,528,3,62,31,0,524,525,
  	10,1,0,0,525,526,5,52,0,0,526,528,3,62,31,0,527,521,1,0,0,0,527,524,1,
  	0,0,0,528,531,1,0,0,0,529,527,1,0,0,0,529,530,1,0,0,0,530,61,1,0,0,0,
  	531,529,1,0,0,0,532,533,6,31,-1,0,533,534,3,64,32,0,534,543,1,0,0,0,535,
  	536,10,2,0,0,536,537,5,33,0,0,537,542,3,64,32,0,538,539,10,1,0,0,539,
  	540,5,34,0,0,540,542,3,64,32,0,541,535,1,0,0,0,541,538,1,0,0,0,542,545,
  	1,0,0,0,543,541,1,0,0,0,543,544,1,0,0,0,544,63,1,0,0,0,545,543,1,0,0,
  	0,546,547,6,32,-1,0,547,548,3,66,33,0,548,560,1,0,0,0,549,550,10,3,0,
  	0,550,551,5,35,0,0,551,559,3,66,33,0,552,553,10,2,0,0,553,554,5,36,0,
  	0,554,559,3,66,33,0,555,556,10,1,0,0,556,557,5,37,0,0,557,559,3,66,33,
  	0,558,549,1,0,0,0,558,552,1,0,0,0,558,555,1,0,0,0,559,562,1,0,0,0,560,
  	558,1,0,0,0,560,561,1,0,0,0,561,65,1,0,0,0,562,560,1,0,0,0,563,585,3,
  	68,34,0,564,565,5,46,0,0,565,585,3,66,33,0,566,567,5,50,0,0,567,585,3,
  	66,33,0,568,569,5,47,0,0,569,585,3,66,33,0,570,571,5,35,0,0,571,585,3,
  	66,33,0,572,573,5,34,0,0,573,585,3,66,33,0,574,575,5,33,0,0,575,585,3,
  	66,33,0,576,577,5,23,0,0,577,585,3,44,22,0,578,579,3,26,13,0,579,580,
  	5,70,0,0,580,585,1,0,0,0,581,582,3,26,13,0,582,583,5,71,0,0,583,585,1,
  	0,0,0,584,563,1,0,0,0,584,564,1,0,0,0,584,566,1,0,0,0,584,568,1,0,0,0,
  	584,570,1,0,0,0,584,572,1,0,0,0,584,574,1,0,0,0,584,576,1,0,0,0,584,578,
  	1,0,0,0,584,581,1,0,0,0,585,67,1,0,0,0,586,587,3,26,13,0,587,589,5,57,
  	0,0,588,590,3,70,35,0,589,588,1,0,0,0,589,590,1,0,0,0,590,591,1,0,0,0,
  	591,592,5,58,0,0,592,628,1,0,0,0,593,594,3,26,13,0,594,595,5,61,0,0,595,
  	596,3,44,22,0,596,597,5,62,0,0,597,628,1,0,0,0,598,599,3,26,13,0,599,
  	600,5,63,0,0,600,601,3,26,13,0,601,603,5,57,0,0,602,604,3,70,35,0,603,
  	602,1,0,0,0,603,604,1,0,0,0,604,605,1,0,0,0,605,606,5,58,0,0,606,628,
  	1,0,0,0,607,608,3,26,13,0,608,609,5,63,0,0,609,610,3,26,13,0,610,628,
  	1,0,0,0,611,612,3,26,13,0,612,613,5,4,0,0,613,614,3,26,13,0,614,628,1,
  	0,0,0,615,616,3,26,13,0,616,617,5,70,0,0,617,628,1,0,0,0,618,619,3,26,
  	13,0,619,620,5,71,0,0,620,628,1,0,0,0,621,628,3,26,13,0,622,628,3,72,
  	36,0,623,624,5,57,0,0,624,625,3,44,22,0,625,626,5,58,0,0,626,628,1,0,
  	0,0,627,586,1,0,0,0,627,593,1,0,0,0,627,598,1,0,0,0,627,607,1,0,0,0,627,
  	611,1,0,0,0,627,615,1,0,0,0,627,618,1,0,0,0,627,621,1,0,0,0,627,622,1,
  	0,0,0,627,623,1,0,0,0,628,69,1,0,0,0,629,634,3,44,22,0,630,631,5,55,0,
  	0,631,633,3,44,22,0,632,630,1,0,0,0,633,636,1,0,0,0,634,632,1,0,0,0,634,
  	635,1,0,0,0,635,71,1,0,0,0,636,634,1,0,0,0,637,638,7,1,0,0,638,73,1,0,
  	0,0,639,640,5,8,0,0,640,641,5,57,0,0,641,642,3,44,22,0,642,643,5,58,0,
  	0,643,646,3,14,7,0,644,645,5,9,0,0,645,647,3,14,7,0,646,644,1,0,0,0,646,
  	647,1,0,0,0,647,75,1,0,0,0,648,649,5,10,0,0,649,650,5,57,0,0,650,651,
  	3,44,22,0,651,652,5,58,0,0,652,653,3,14,7,0,653,77,1,0,0,0,654,655,5,
  	11,0,0,655,657,5,57,0,0,656,658,3,80,40,0,657,656,1,0,0,0,657,658,1,0,
  	0,0,658,659,1,0,0,0,659,661,5,56,0,0,660,662,3,82,41,0,661,660,1,0,0,
  	0,661,662,1,0,0,0,662,663,1,0,0,0,663,665,5,56,0,0,664,666,3,84,42,0,
  	665,664,1,0,0,0,665,666,1,0,0,0,666,667,1,0,0,0,667,668,5,58,0,0,668,
  	669,3,14,7,0,669,79,1,0,0,0,670,673,3,18,9,0,671,673,3,44,22,0,672,670,
  	1,0,0,0,672,671,1,0,0,0,673,81,1,0,0,0,674,675,3,44,22,0,675,83,1,0,0,
  	0,676,677,3,44,22,0,677,85,1,0,0,0,678,679,5,12,0,0,679,680,3,14,7,0,
  	680,681,5,10,0,0,681,682,5,57,0,0,682,683,3,44,22,0,683,685,5,58,0,0,
  	684,686,5,56,0,0,685,684,1,0,0,0,685,686,1,0,0,0,686,87,1,0,0,0,687,688,
  	5,5,0,0,688,690,3,12,6,0,689,691,3,90,45,0,690,689,1,0,0,0,691,692,1,
  	0,0,0,692,690,1,0,0,0,692,693,1,0,0,0,693,89,1,0,0,0,694,695,5,6,0,0,
  	695,696,5,57,0,0,696,697,3,28,14,0,697,698,3,26,13,0,698,699,5,58,0,0,
  	699,700,3,12,6,0,700,707,1,0,0,0,701,702,5,6,0,0,702,703,5,57,0,0,703,
  	704,5,72,0,0,704,705,5,58,0,0,705,707,3,12,6,0,706,694,1,0,0,0,706,701,
  	1,0,0,0,707,91,1,0,0,0,708,709,5,13,0,0,709,710,5,57,0,0,710,711,3,44,
  	22,0,711,712,5,58,0,0,712,713,5,59,0,0,713,714,3,94,47,0,714,715,5,60,
  	0,0,715,93,1,0,0,0,716,718,3,96,48,0,717,716,1,0,0,0,718,721,1,0,0,0,
  	719,717,1,0,0,0,719,720,1,0,0,0,720,95,1,0,0,0,721,719,1,0,0,0,722,723,
  	5,14,0,0,723,724,3,44,22,0,724,728,5,54,0,0,725,727,3,2,1,0,726,725,1,
  	0,0,0,727,730,1,0,0,0,728,726,1,0,0,0,728,729,1,0,0,0,729,740,1,0,0,0,
  	730,728,1,0,0,0,731,732,5,15,0,0,732,736,5,54,0,0,733,735,3,2,1,0,734,
  	733,1,0,0,0,735,738,1,0,0,0,736,734,1,0,0,0,736,737,1,0,0,0,737,740,1,
  	0,0,0,738,736,1,0,0,0,739,722,1,0,0,0,739,731,1,0,0,0,740,97,1,0,0,0,
  	63,101,147,153,163,171,174,179,187,195,201,207,213,217,243,249,261,268,
  	275,282,284,290,300,310,319,324,345,350,362,368,375,427,437,448,459,470,
  	481,493,495,513,515,527,529,541,543,558,560,584,589,603,627,634,646,657,
  	661,665,672,685,692,706,719,728,736,739
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cscriptParserStaticData = std::move(staticData);
}

}

CScriptParser::CScriptParser(TokenStream *input) : CScriptParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CScriptParser::CScriptParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CScriptParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cscriptParserStaticData->atn, cscriptParserStaticData->decisionToDFA, cscriptParserStaticData->sharedContextCache, options);
}

CScriptParser::~CScriptParser() {
  delete _interpreter;
}

const atn::ATN& CScriptParser::getATN() const {
  return *cscriptParserStaticData->atn;
}

std::string CScriptParser::getGrammarFileName() const {
  return "CScript.g4";
}

const std::vector<std::string>& CScriptParser::getRuleNames() const {
  return cscriptParserStaticData->ruleNames;
}

const dfa::Vocabulary& CScriptParser::getVocabulary() const {
  return cscriptParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CScriptParser::getSerializedATN() const {
  return cscriptParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

CScriptParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::ProgramContext::EOF() {
  return getToken(CScriptParser::EOF, 0);
}

std::vector<CScriptParser::StmtContext *> CScriptParser::ProgramContext::stmt() {
  return getRuleContexts<CScriptParser::StmtContext>();
}

CScriptParser::StmtContext* CScriptParser::ProgramContext::stmt(size_t i) {
  return getRuleContext<CScriptParser::StmtContext>(i);
}


size_t CScriptParser::ProgramContext::getRuleIndex() const {
  return CScriptParser::RuleProgram;
}

void CScriptParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CScriptParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any CScriptParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::ProgramContext* CScriptParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CScriptParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
      setState(98);
      stmt();
      setState(103);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(104);
    match(CScriptParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

CScriptParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Var_declContext* CScriptParser::StmtContext::var_decl() {
  return getRuleContext<CScriptParser::Var_declContext>(0);
}

tree::TerminalNode* CScriptParser::StmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

CScriptParser::Enum_declContext* CScriptParser::StmtContext::enum_decl() {
  return getRuleContext<CScriptParser::Enum_declContext>(0);
}

CScriptParser::Func_declContext* CScriptParser::StmtContext::func_decl() {
  return getRuleContext<CScriptParser::Func_declContext>(0);
}

CScriptParser::Extern_declContext* CScriptParser::StmtContext::extern_decl() {
  return getRuleContext<CScriptParser::Extern_declContext>(0);
}

CScriptParser::Struct_declContext* CScriptParser::StmtContext::struct_decl() {
  return getRuleContext<CScriptParser::Struct_declContext>(0);
}

CScriptParser::Union_declContext* CScriptParser::StmtContext::union_decl() {
  return getRuleContext<CScriptParser::Union_declContext>(0);
}

CScriptParser::ExprContext* CScriptParser::StmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::StmtContext::MUL() {
  return getToken(CScriptParser::MUL, 0);
}

CScriptParser::IdentContext* CScriptParser::StmtContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::StmtContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
}

tree::TerminalNode* CScriptParser::StmtContext::RETURN() {
  return getToken(CScriptParser::RETURN, 0);
}

CScriptParser::If_stmtContext* CScriptParser::StmtContext::if_stmt() {
  return getRuleContext<CScriptParser::If_stmtContext>(0);
}

CScriptParser::While_stmtContext* CScriptParser::StmtContext::while_stmt() {
  return getRuleContext<CScriptParser::While_stmtContext>(0);
}

CScriptParser::For_stmtContext* CScriptParser::StmtContext::for_stmt() {
  return getRuleContext<CScriptParser::For_stmtContext>(0);
}

CScriptParser::Do_while_stmtContext* CScriptParser::StmtContext::do_while_stmt() {
  return getRuleContext<CScriptParser::Do_while_stmtContext>(0);
}

CScriptParser::Switch_stmtContext* CScriptParser::StmtContext::switch_stmt() {
  return getRuleContext<CScriptParser::Switch_stmtContext>(0);
}

CScriptParser::Try_catch_stmtContext* CScriptParser::StmtContext::try_catch_stmt() {
  return getRuleContext<CScriptParser::Try_catch_stmtContext>(0);
}

tree::TerminalNode* CScriptParser::StmtContext::CONTINUE() {
  return getToken(CScriptParser::CONTINUE, 0);
}

tree::TerminalNode* CScriptParser::StmtContext::BREAK() {
  return getToken(CScriptParser::BREAK, 0);
}

CScriptParser::Register_callback_stmtContext* CScriptParser::StmtContext::register_callback_stmt() {
  return getRuleContext<CScriptParser::Register_callback_stmtContext>(0);
}

CScriptParser::Import_stmtContext* CScriptParser::StmtContext::import_stmt() {
  return getRuleContext<CScriptParser::Import_stmtContext>(0);
}

CScriptParser::Include_stmtContext* CScriptParser::StmtContext::include_stmt() {
  return getRuleContext<CScriptParser::Include_stmtContext>(0);
}

CScriptParser::Export_stmtContext* CScriptParser::StmtContext::export_stmt() {
  return getRuleContext<CScriptParser::Export_stmtContext>(0);
}


size_t CScriptParser::StmtContext::getRuleIndex() const {
  return CScriptParser::RuleStmt;
}

void CScriptParser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void CScriptParser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}


std::any CScriptParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::StmtContext* CScriptParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 2, CScriptParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(106);
      var_decl();
      setState(107);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      enum_decl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(110);
      func_decl();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(111);
      extern_decl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(112);
      struct_decl();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(113);
      struct_decl();
      setState(114);
      match(CScriptParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(116);
      union_decl();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(117);
      union_decl();
      setState(118);
      match(CScriptParser::SEMI);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(120);
      expr();
      setState(121);
      match(CScriptParser::SEMI);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(123);
      match(CScriptParser::MUL);
      setState(124);
      ident();
      setState(125);
      match(CScriptParser::ASSIGN);
      setState(126);
      expr();
      setState(127);
      match(CScriptParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(129);
      match(CScriptParser::RETURN);
      setState(130);
      expr();
      setState(131);
      match(CScriptParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(133);
      if_stmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(134);
      while_stmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(135);
      for_stmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(136);
      do_while_stmt();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(137);
      switch_stmt();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(138);
      try_catch_stmt();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(139);
      match(CScriptParser::CONTINUE);
      setState(140);
      match(CScriptParser::SEMI);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(141);
      match(CScriptParser::BREAK);
      setState(142);
      match(CScriptParser::SEMI);
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(143);
      register_callback_stmt();
      break;
    }

    case 21: {
      enterOuterAlt(_localctx, 21);
      setState(144);
      import_stmt();
      break;
    }

    case 22: {
      enterOuterAlt(_localctx, 22);
      setState(145);
      include_stmt();
      break;
    }

    case 23: {
      enterOuterAlt(_localctx, 23);
      setState(146);
      export_stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_stmtContext ------------------------------------------------------------------

CScriptParser::Import_stmtContext::Import_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Import_stmtContext::IMPORT() {
  return getToken(CScriptParser::IMPORT, 0);
}

tree::TerminalNode* CScriptParser::Import_stmtContext::STRING() {
  return getToken(CScriptParser::STRING, 0);
}

tree::TerminalNode* CScriptParser::Import_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

std::vector<CScriptParser::IdentContext *> CScriptParser::Import_stmtContext::ident() {
  return getRuleContexts<CScriptParser::IdentContext>();
}

CScriptParser::IdentContext* CScriptParser::Import_stmtContext::ident(size_t i) {
  return getRuleContext<CScriptParser::IdentContext>(i);
}

tree::TerminalNode* CScriptParser::Import_stmtContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

tree::TerminalNode* CScriptParser::Import_stmtContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> CScriptParser::Import_stmtContext::COMMA() {
  return getTokens(CScriptParser::COMMA);
}

tree::TerminalNode* CScriptParser::Import_stmtContext::COMMA(size_t i) {
  return getToken(CScriptParser::COMMA, i);
}


size_t CScriptParser::Import_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleImport_stmt;
}

void CScriptParser::Import_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_stmt(this);
}

void CScriptParser::Import_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_stmt(this);
}


std::any CScriptParser::Import_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitImport_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Import_stmtContext* CScriptParser::import_stmt() {
  Import_stmtContext *_localctx = _tracker.createInstance<Import_stmtContext>(_ctx, getState());
  enterRule(_localctx, 4, CScriptParser::RuleImport_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(171);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(149);
      match(CScriptParser::IMPORT);
      setState(150);
      match(CScriptParser::STRING);
      setState(153);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::T__0) {
        setState(151);
        match(CScriptParser::T__0);
        setState(152);
        ident();
      }
      setState(155);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(156);
      match(CScriptParser::IMPORT);
      setState(157);
      match(CScriptParser::LBRACE);
      setState(158);
      ident();
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CScriptParser::COMMA) {
        setState(159);
        match(CScriptParser::COMMA);
        setState(160);
        ident();
        setState(165);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(166);
      match(CScriptParser::RBRACE);
      setState(167);
      match(CScriptParser::T__1);
      setState(168);
      match(CScriptParser::STRING);
      setState(169);
      match(CScriptParser::SEMI);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Include_stmtContext ------------------------------------------------------------------

CScriptParser::Include_stmtContext::Include_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Include_stmtContext::INCLUDE() {
  return getToken(CScriptParser::INCLUDE, 0);
}

tree::TerminalNode* CScriptParser::Include_stmtContext::STRING() {
  return getToken(CScriptParser::STRING, 0);
}

tree::TerminalNode* CScriptParser::Include_stmtContext::ANGLE_STRING() {
  return getToken(CScriptParser::ANGLE_STRING, 0);
}

tree::TerminalNode* CScriptParser::Include_stmtContext::HASH() {
  return getToken(CScriptParser::HASH, 0);
}

tree::TerminalNode* CScriptParser::Include_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}


size_t CScriptParser::Include_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleInclude_stmt;
}

void CScriptParser::Include_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInclude_stmt(this);
}

void CScriptParser::Include_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInclude_stmt(this);
}


std::any CScriptParser::Include_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitInclude_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Include_stmtContext* CScriptParser::include_stmt() {
  Include_stmtContext *_localctx = _tracker.createInstance<Include_stmtContext>(_ctx, getState());
  enterRule(_localctx, 6, CScriptParser::RuleInclude_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::HASH) {
      setState(173);
      match(CScriptParser::HASH);
    }
    setState(176);
    match(CScriptParser::INCLUDE);
    setState(177);
    _la = _input->LA(1);
    if (!(_la == CScriptParser::STRING

    || _la == CScriptParser::ANGLE_STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::SEMI) {
      setState(178);
      match(CScriptParser::SEMI);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Register_callback_stmtContext ------------------------------------------------------------------

CScriptParser::Register_callback_stmtContext::Register_callback_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::IdentContext *> CScriptParser::Register_callback_stmtContext::ident() {
  return getRuleContexts<CScriptParser::IdentContext>();
}

CScriptParser::IdentContext* CScriptParser::Register_callback_stmtContext::ident(size_t i) {
  return getRuleContext<CScriptParser::IdentContext>(i);
}

tree::TerminalNode* CScriptParser::Register_callback_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

tree::TerminalNode* CScriptParser::Register_callback_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

tree::TerminalNode* CScriptParser::Register_callback_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

CScriptParser::Func_decl_argsContext* CScriptParser::Register_callback_stmtContext::func_decl_args() {
  return getRuleContext<CScriptParser::Func_decl_argsContext>(0);
}


size_t CScriptParser::Register_callback_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleRegister_callback_stmt;
}

void CScriptParser::Register_callback_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegister_callback_stmt(this);
}

void CScriptParser::Register_callback_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegister_callback_stmt(this);
}


std::any CScriptParser::Register_callback_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitRegister_callback_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Register_callback_stmtContext* CScriptParser::register_callback_stmt() {
  Register_callback_stmtContext *_localctx = _tracker.createInstance<Register_callback_stmtContext>(_ctx, getState());
  enterRule(_localctx, 8, CScriptParser::RuleRegister_callback_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    match(CScriptParser::T__2);
    setState(182);
    ident();
    setState(183);
    match(CScriptParser::T__0);
    setState(184);
    ident();
    setState(185);
    match(CScriptParser::LPAREN);
    setState(187);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(186);
      func_decl_args();
    }
    setState(189);
    match(CScriptParser::RPAREN);
    setState(190);
    match(CScriptParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Export_stmtContext ------------------------------------------------------------------

CScriptParser::Export_stmtContext::Export_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CScriptParser::Export_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleExport_stmt;
}

void CScriptParser::Export_stmtContext::copyFrom(Export_stmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExportFuncDeclContext ------------------------------------------------------------------

tree::TerminalNode* CScriptParser::ExportFuncDeclContext::EXPORT() {
  return getToken(CScriptParser::EXPORT, 0);
}

CScriptParser::Func_declContext* CScriptParser::ExportFuncDeclContext::func_decl() {
  return getRuleContext<CScriptParser::Func_declContext>(0);
}

CScriptParser::ExportFuncDeclContext::ExportFuncDeclContext(Export_stmtContext *ctx) { copyFrom(ctx); }

void CScriptParser::ExportFuncDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportFuncDecl(this);
}
void CScriptParser::ExportFuncDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportFuncDecl(this);
}

std::any CScriptParser::ExportFuncDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExportFuncDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExportVarDeclContext ------------------------------------------------------------------

tree::TerminalNode* CScriptParser::ExportVarDeclContext::EXPORT() {
  return getToken(CScriptParser::EXPORT, 0);
}

CScriptParser::Var_declContext* CScriptParser::ExportVarDeclContext::var_decl() {
  return getRuleContext<CScriptParser::Var_declContext>(0);
}

tree::TerminalNode* CScriptParser::ExportVarDeclContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

CScriptParser::ExportVarDeclContext::ExportVarDeclContext(Export_stmtContext *ctx) { copyFrom(ctx); }

void CScriptParser::ExportVarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportVarDecl(this);
}
void CScriptParser::ExportVarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportVarDecl(this);
}

std::any CScriptParser::ExportVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExportVarDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExportEnumDeclContext ------------------------------------------------------------------

tree::TerminalNode* CScriptParser::ExportEnumDeclContext::EXPORT() {
  return getToken(CScriptParser::EXPORT, 0);
}

CScriptParser::Enum_declContext* CScriptParser::ExportEnumDeclContext::enum_decl() {
  return getRuleContext<CScriptParser::Enum_declContext>(0);
}

CScriptParser::ExportEnumDeclContext::ExportEnumDeclContext(Export_stmtContext *ctx) { copyFrom(ctx); }

void CScriptParser::ExportEnumDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportEnumDecl(this);
}
void CScriptParser::ExportEnumDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportEnumDecl(this);
}

std::any CScriptParser::ExportEnumDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExportEnumDecl(this);
  else
    return visitor->visitChildren(this);
}
CScriptParser::Export_stmtContext* CScriptParser::export_stmt() {
  Export_stmtContext *_localctx = _tracker.createInstance<Export_stmtContext>(_ctx, getState());
  enterRule(_localctx, 10, CScriptParser::RuleExport_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(201);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CScriptParser::ExportVarDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(192);
      match(CScriptParser::EXPORT);
      setState(193);
      var_decl();
      setState(195);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::SEMI) {
        setState(194);
        match(CScriptParser::SEMI);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CScriptParser::ExportFuncDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(197);
      match(CScriptParser::EXPORT);
      setState(198);
      func_decl();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CScriptParser::ExportEnumDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(199);
      match(CScriptParser::EXPORT);
      setState(200);
      enum_decl();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CScriptParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::BlockContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

tree::TerminalNode* CScriptParser::BlockContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}

std::vector<CScriptParser::StmtContext *> CScriptParser::BlockContext::stmt() {
  return getRuleContexts<CScriptParser::StmtContext>();
}

CScriptParser::StmtContext* CScriptParser::BlockContext::stmt(size_t i) {
  return getRuleContext<CScriptParser::StmtContext>(i);
}


size_t CScriptParser::BlockContext::getRuleIndex() const {
  return CScriptParser::RuleBlock;
}

void CScriptParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void CScriptParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any CScriptParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::BlockContext* CScriptParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 12, CScriptParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(213);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(203);
      match(CScriptParser::LBRACE);
      setState(207);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
        setState(204);
        stmt();
        setState(209);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(210);
      match(CScriptParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(211);
      match(CScriptParser::LBRACE);
      setState(212);
      match(CScriptParser::RBRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BodyContext ------------------------------------------------------------------

CScriptParser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::BlockContext* CScriptParser::BodyContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
}

CScriptParser::Single_stmtContext* CScriptParser::BodyContext::single_stmt() {
  return getRuleContext<CScriptParser::Single_stmtContext>(0);
}


size_t CScriptParser::BodyContext::getRuleIndex() const {
  return CScriptParser::RuleBody;
}

void CScriptParser::BodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBody(this);
}

void CScriptParser::BodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBody(this);
}


std::any CScriptParser::BodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBody(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::BodyContext* CScriptParser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 14, CScriptParser::RuleBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        block();
        break;
      }

      case CScriptParser::T__2:
      case CScriptParser::T__4:
      case CScriptParser::RETURN:
      case CScriptParser::IF:
      case CScriptParser::WHILE:
      case CScriptParser::FOR:
      case CScriptParser::DO:
      case CScriptParser::SWITCH:
      case CScriptParser::CONTINUE:
      case CScriptParser::BREAK:
      case CScriptParser::THROW:
      case CScriptParser::INTEGER:
      case CScriptParser::DOUBLE:
      case CScriptParser::CHAR:
      case CScriptParser::STRING:
      case CScriptParser::IDENTIFIER:
      case CScriptParser::PLUS:
      case CScriptParser::MINUS:
      case CScriptParser::MUL:
      case CScriptParser::NOT:
      case CScriptParser::BITAND:
      case CScriptParser::NOTBIT:
      case CScriptParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        single_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Single_stmtContext ------------------------------------------------------------------

CScriptParser::Single_stmtContext::Single_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::ExprContext* CScriptParser::Single_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::MUL() {
  return getToken(CScriptParser::MUL, 0);
}

CScriptParser::IdentContext* CScriptParser::Single_stmtContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::RETURN() {
  return getToken(CScriptParser::RETURN, 0);
}

CScriptParser::If_stmtContext* CScriptParser::Single_stmtContext::if_stmt() {
  return getRuleContext<CScriptParser::If_stmtContext>(0);
}

CScriptParser::While_stmtContext* CScriptParser::Single_stmtContext::while_stmt() {
  return getRuleContext<CScriptParser::While_stmtContext>(0);
}

CScriptParser::For_stmtContext* CScriptParser::Single_stmtContext::for_stmt() {
  return getRuleContext<CScriptParser::For_stmtContext>(0);
}

CScriptParser::Do_while_stmtContext* CScriptParser::Single_stmtContext::do_while_stmt() {
  return getRuleContext<CScriptParser::Do_while_stmtContext>(0);
}

CScriptParser::Switch_stmtContext* CScriptParser::Single_stmtContext::switch_stmt() {
  return getRuleContext<CScriptParser::Switch_stmtContext>(0);
}

CScriptParser::Try_catch_stmtContext* CScriptParser::Single_stmtContext::try_catch_stmt() {
  return getRuleContext<CScriptParser::Try_catch_stmtContext>(0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::CONTINUE() {
  return getToken(CScriptParser::CONTINUE, 0);
}

tree::TerminalNode* CScriptParser::Single_stmtContext::BREAK() {
  return getToken(CScriptParser::BREAK, 0);
}

CScriptParser::Register_callback_stmtContext* CScriptParser::Single_stmtContext::register_callback_stmt() {
  return getRuleContext<CScriptParser::Register_callback_stmtContext>(0);
}


size_t CScriptParser::Single_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleSingle_stmt;
}

void CScriptParser::Single_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingle_stmt(this);
}

void CScriptParser::Single_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingle_stmt(this);
}


std::any CScriptParser::Single_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitSingle_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Single_stmtContext* CScriptParser::single_stmt() {
  Single_stmtContext *_localctx = _tracker.createInstance<Single_stmtContext>(_ctx, getState());
  enterRule(_localctx, 16, CScriptParser::RuleSingle_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(243);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(219);
      expr();
      setState(220);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(222);
      match(CScriptParser::MUL);
      setState(223);
      ident();
      setState(224);
      match(CScriptParser::ASSIGN);
      setState(225);
      expr();
      setState(226);
      match(CScriptParser::SEMI);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(228);
      match(CScriptParser::RETURN);
      setState(229);
      expr();
      setState(230);
      match(CScriptParser::SEMI);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(232);
      if_stmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(233);
      while_stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(234);
      for_stmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(235);
      do_while_stmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(236);
      switch_stmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(237);
      try_catch_stmt();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(238);
      match(CScriptParser::CONTINUE);
      setState(239);
      match(CScriptParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(240);
      match(CScriptParser::BREAK);
      setState(241);
      match(CScriptParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(242);
      register_callback_stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declContext ------------------------------------------------------------------

CScriptParser::Var_declContext::Var_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::TypeContext* CScriptParser::Var_declContext::type() {
  return getRuleContext<CScriptParser::TypeContext>(0);
}

std::vector<CScriptParser::IdentContext *> CScriptParser::Var_declContext::ident() {
  return getRuleContexts<CScriptParser::IdentContext>();
}

CScriptParser::IdentContext* CScriptParser::Var_declContext::ident(size_t i) {
  return getRuleContext<CScriptParser::IdentContext>(i);
}

tree::TerminalNode* CScriptParser::Var_declContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
}

CScriptParser::ExprContext* CScriptParser::Var_declContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Var_declContext::LBRACKET() {
  return getToken(CScriptParser::LBRACKET, 0);
}

tree::TerminalNode* CScriptParser::Var_declContext::RBRACKET() {
  return getToken(CScriptParser::RBRACKET, 0);
}

tree::TerminalNode* CScriptParser::Var_declContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

CScriptParser::Init_listContext* CScriptParser::Var_declContext::init_list() {
  return getRuleContext<CScriptParser::Init_listContext>(0);
}

tree::TerminalNode* CScriptParser::Var_declContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}

tree::TerminalNode* CScriptParser::Var_declContext::MUL() {
  return getToken(CScriptParser::MUL, 0);
}

tree::TerminalNode* CScriptParser::Var_declContext::CONST_KW() {
  return getToken(CScriptParser::CONST_KW, 0);
}

tree::TerminalNode* CScriptParser::Var_declContext::STRUCT_KW() {
  return getToken(CScriptParser::STRUCT_KW, 0);
}


size_t CScriptParser::Var_declContext::getRuleIndex() const {
  return CScriptParser::RuleVar_decl;
}

void CScriptParser::Var_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_decl(this);
}

void CScriptParser::Var_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_decl(this);
}


std::any CScriptParser::Var_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitVar_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Var_declContext* CScriptParser::var_decl() {
  Var_declContext *_localctx = _tracker.createInstance<Var_declContext>(_ctx, getState());
  enterRule(_localctx, 18, CScriptParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(284);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(245);
      type();
      setState(246);
      ident();
      setState(249);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(247);
        match(CScriptParser::ASSIGN);
        setState(248);
        expr();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(251);
      type();
      setState(252);
      ident();
      setState(253);
      match(CScriptParser::LBRACKET);
      setState(254);
      expr();
      setState(255);
      match(CScriptParser::RBRACKET);
      setState(261);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(256);
        match(CScriptParser::ASSIGN);
        setState(257);
        match(CScriptParser::LBRACE);
        setState(258);
        init_list();
        setState(259);
        match(CScriptParser::RBRACE);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(263);
      type();
      setState(264);
      match(CScriptParser::MUL);
      setState(265);
      ident();
      setState(268);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(266);
        match(CScriptParser::ASSIGN);
        setState(267);
        expr();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(270);
      match(CScriptParser::CONST_KW);
      setState(271);
      type();
      setState(272);
      ident();
      setState(275);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(273);
        match(CScriptParser::ASSIGN);
        setState(274);
        expr();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(277);
      match(CScriptParser::STRUCT_KW);
      setState(278);
      ident();
      setState(279);
      ident();
      setState(282);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(280);
        match(CScriptParser::ASSIGN);
        setState(281);
        expr();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_declContext ------------------------------------------------------------------

CScriptParser::Func_declContext::Func_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::TypeContext* CScriptParser::Func_declContext::type() {
  return getRuleContext<CScriptParser::TypeContext>(0);
}

CScriptParser::IdentContext* CScriptParser::Func_declContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Func_declContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

tree::TerminalNode* CScriptParser::Func_declContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

CScriptParser::BlockContext* CScriptParser::Func_declContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
}

CScriptParser::Func_decl_argsContext* CScriptParser::Func_declContext::func_decl_args() {
  return getRuleContext<CScriptParser::Func_decl_argsContext>(0);
}


size_t CScriptParser::Func_declContext::getRuleIndex() const {
  return CScriptParser::RuleFunc_decl;
}

void CScriptParser::Func_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_decl(this);
}

void CScriptParser::Func_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_decl(this);
}


std::any CScriptParser::Func_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFunc_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Func_declContext* CScriptParser::func_decl() {
  Func_declContext *_localctx = _tracker.createInstance<Func_declContext>(_ctx, getState());
  enterRule(_localctx, 20, CScriptParser::RuleFunc_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    type();
    setState(287);
    ident();
    setState(288);
    match(CScriptParser::LPAREN);
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(289);
      func_decl_args();
    }
    setState(292);
    match(CScriptParser::RPAREN);
    setState(293);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Extern_declContext ------------------------------------------------------------------

CScriptParser::Extern_declContext::Extern_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Extern_declContext::EXTERN_KW() {
  return getToken(CScriptParser::EXTERN_KW, 0);
}

CScriptParser::TypeContext* CScriptParser::Extern_declContext::type() {
  return getRuleContext<CScriptParser::TypeContext>(0);
}

CScriptParser::IdentContext* CScriptParser::Extern_declContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Extern_declContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

tree::TerminalNode* CScriptParser::Extern_declContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

tree::TerminalNode* CScriptParser::Extern_declContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

CScriptParser::Func_decl_argsContext* CScriptParser::Extern_declContext::func_decl_args() {
  return getRuleContext<CScriptParser::Func_decl_argsContext>(0);
}


size_t CScriptParser::Extern_declContext::getRuleIndex() const {
  return CScriptParser::RuleExtern_decl;
}

void CScriptParser::Extern_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtern_decl(this);
}

void CScriptParser::Extern_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtern_decl(this);
}


std::any CScriptParser::Extern_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExtern_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Extern_declContext* CScriptParser::extern_decl() {
  Extern_declContext *_localctx = _tracker.createInstance<Extern_declContext>(_ctx, getState());
  enterRule(_localctx, 22, CScriptParser::RuleExtern_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(CScriptParser::EXTERN_KW);
    setState(296);
    type();
    setState(297);
    ident();
    setState(298);
    match(CScriptParser::LPAREN);
    setState(300);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(299);
      func_decl_args();
    }
    setState(302);
    match(CScriptParser::RPAREN);
    setState(303);
    match(CScriptParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_decl_argsContext ------------------------------------------------------------------

CScriptParser::Func_decl_argsContext::Func_decl_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::Var_declContext *> CScriptParser::Func_decl_argsContext::var_decl() {
  return getRuleContexts<CScriptParser::Var_declContext>();
}

CScriptParser::Var_declContext* CScriptParser::Func_decl_argsContext::var_decl(size_t i) {
  return getRuleContext<CScriptParser::Var_declContext>(i);
}

std::vector<tree::TerminalNode *> CScriptParser::Func_decl_argsContext::COMMA() {
  return getTokens(CScriptParser::COMMA);
}

tree::TerminalNode* CScriptParser::Func_decl_argsContext::COMMA(size_t i) {
  return getToken(CScriptParser::COMMA, i);
}


size_t CScriptParser::Func_decl_argsContext::getRuleIndex() const {
  return CScriptParser::RuleFunc_decl_args;
}

void CScriptParser::Func_decl_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_decl_args(this);
}

void CScriptParser::Func_decl_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_decl_args(this);
}


std::any CScriptParser::Func_decl_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFunc_decl_args(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Func_decl_argsContext* CScriptParser::func_decl_args() {
  Func_decl_argsContext *_localctx = _tracker.createInstance<Func_decl_argsContext>(_ctx, getState());
  enterRule(_localctx, 24, CScriptParser::RuleFunc_decl_args);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    var_decl();
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(306);
      match(CScriptParser::COMMA);
      setState(307);
      var_decl();
      setState(312);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentContext ------------------------------------------------------------------

CScriptParser::IdentContext::IdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::IdentContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
}


size_t CScriptParser::IdentContext::getRuleIndex() const {
  return CScriptParser::RuleIdent;
}

void CScriptParser::IdentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdent(this);
}

void CScriptParser::IdentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdent(this);
}


std::any CScriptParser::IdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitIdent(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::IdentContext* CScriptParser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 26, CScriptParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(313);
    match(CScriptParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

CScriptParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::TypeContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
}

std::vector<tree::TerminalNode *> CScriptParser::TypeContext::MUL() {
  return getTokens(CScriptParser::MUL);
}

tree::TerminalNode* CScriptParser::TypeContext::MUL(size_t i) {
  return getToken(CScriptParser::MUL, i);
}

tree::TerminalNode* CScriptParser::TypeContext::ENUM_KW() {
  return getToken(CScriptParser::ENUM_KW, 0);
}


size_t CScriptParser::TypeContext::getRuleIndex() const {
  return CScriptParser::RuleType;
}

void CScriptParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void CScriptParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any CScriptParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::TypeContext* CScriptParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 28, CScriptParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(324);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(315);
        match(CScriptParser::IDENTIFIER);
        setState(319);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(316);
            match(CScriptParser::MUL); 
          }
          setState(321);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
        }
        break;
      }

      case CScriptParser::ENUM_KW: {
        enterOuterAlt(_localctx, 2);
        setState(322);
        match(CScriptParser::ENUM_KW);
        setState(323);
        match(CScriptParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_declContext ------------------------------------------------------------------

CScriptParser::Struct_declContext::Struct_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Struct_declContext::STRUCT_KW() {
  return getToken(CScriptParser::STRUCT_KW, 0);
}

tree::TerminalNode* CScriptParser::Struct_declContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* CScriptParser::Struct_declContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

CScriptParser::Struct_membersContext* CScriptParser::Struct_declContext::struct_members() {
  return getRuleContext<CScriptParser::Struct_membersContext>(0);
}

tree::TerminalNode* CScriptParser::Struct_declContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}


size_t CScriptParser::Struct_declContext::getRuleIndex() const {
  return CScriptParser::RuleStruct_decl;
}

void CScriptParser::Struct_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_decl(this);
}

void CScriptParser::Struct_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_decl(this);
}


std::any CScriptParser::Struct_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitStruct_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Struct_declContext* CScriptParser::struct_decl() {
  Struct_declContext *_localctx = _tracker.createInstance<Struct_declContext>(_ctx, getState());
  enterRule(_localctx, 30, CScriptParser::RuleStruct_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
    match(CScriptParser::STRUCT_KW);
    setState(327);
    match(CScriptParser::IDENTIFIER);
    setState(328);
    match(CScriptParser::LBRACE);
    setState(329);
    struct_members();
    setState(330);
    match(CScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Union_declContext ------------------------------------------------------------------

CScriptParser::Union_declContext::Union_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Union_declContext::UNION_KW() {
  return getToken(CScriptParser::UNION_KW, 0);
}

tree::TerminalNode* CScriptParser::Union_declContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
}

tree::TerminalNode* CScriptParser::Union_declContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

CScriptParser::Struct_membersContext* CScriptParser::Union_declContext::struct_members() {
  return getRuleContext<CScriptParser::Struct_membersContext>(0);
}

tree::TerminalNode* CScriptParser::Union_declContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}


size_t CScriptParser::Union_declContext::getRuleIndex() const {
  return CScriptParser::RuleUnion_decl;
}

void CScriptParser::Union_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnion_decl(this);
}

void CScriptParser::Union_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnion_decl(this);
}


std::any CScriptParser::Union_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitUnion_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Union_declContext* CScriptParser::union_decl() {
  Union_declContext *_localctx = _tracker.createInstance<Union_declContext>(_ctx, getState());
  enterRule(_localctx, 32, CScriptParser::RuleUnion_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(332);
    match(CScriptParser::UNION_KW);
    setState(333);
    match(CScriptParser::IDENTIFIER);
    setState(334);
    match(CScriptParser::LBRACE);
    setState(335);
    struct_members();
    setState(336);
    match(CScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_membersContext ------------------------------------------------------------------

CScriptParser::Struct_membersContext::Struct_membersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::Var_declContext *> CScriptParser::Struct_membersContext::var_decl() {
  return getRuleContexts<CScriptParser::Var_declContext>();
}

CScriptParser::Var_declContext* CScriptParser::Struct_membersContext::var_decl(size_t i) {
  return getRuleContext<CScriptParser::Var_declContext>(i);
}

std::vector<tree::TerminalNode *> CScriptParser::Struct_membersContext::SEMI() {
  return getTokens(CScriptParser::SEMI);
}

tree::TerminalNode* CScriptParser::Struct_membersContext::SEMI(size_t i) {
  return getToken(CScriptParser::SEMI, i);
}


size_t CScriptParser::Struct_membersContext::getRuleIndex() const {
  return CScriptParser::RuleStruct_members;
}

void CScriptParser::Struct_membersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_members(this);
}

void CScriptParser::Struct_membersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_members(this);
}


std::any CScriptParser::Struct_membersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitStruct_members(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Struct_membersContext* CScriptParser::struct_members() {
  Struct_membersContext *_localctx = _tracker.createInstance<Struct_membersContext>(_ctx, getState());
  enterRule(_localctx, 34, CScriptParser::RuleStruct_members);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
    var_decl();
    setState(339);
    match(CScriptParser::SEMI);
    setState(345);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(340);
      var_decl();
      setState(341);
      match(CScriptParser::SEMI);
      setState(347);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_declContext ------------------------------------------------------------------

CScriptParser::Enum_declContext::Enum_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Enum_declContext::ENUM_KW() {
  return getToken(CScriptParser::ENUM_KW, 0);
}

tree::TerminalNode* CScriptParser::Enum_declContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

CScriptParser::Enum_listContext* CScriptParser::Enum_declContext::enum_list() {
  return getRuleContext<CScriptParser::Enum_listContext>(0);
}

tree::TerminalNode* CScriptParser::Enum_declContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}

tree::TerminalNode* CScriptParser::Enum_declContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}

tree::TerminalNode* CScriptParser::Enum_declContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
}


size_t CScriptParser::Enum_declContext::getRuleIndex() const {
  return CScriptParser::RuleEnum_decl;
}

void CScriptParser::Enum_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_decl(this);
}

void CScriptParser::Enum_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_decl(this);
}


std::any CScriptParser::Enum_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_declContext* CScriptParser::enum_decl() {
  Enum_declContext *_localctx = _tracker.createInstance<Enum_declContext>(_ctx, getState());
  enterRule(_localctx, 36, CScriptParser::RuleEnum_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
    match(CScriptParser::ENUM_KW);
    setState(350);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::IDENTIFIER) {
      setState(349);
      match(CScriptParser::IDENTIFIER);
    }
    setState(352);
    match(CScriptParser::LBRACE);
    setState(353);
    enum_list();
    setState(354);
    match(CScriptParser::RBRACE);
    setState(355);
    match(CScriptParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_listContext ------------------------------------------------------------------

CScriptParser::Enum_listContext::Enum_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::Enum_itemContext *> CScriptParser::Enum_listContext::enum_item() {
  return getRuleContexts<CScriptParser::Enum_itemContext>();
}

CScriptParser::Enum_itemContext* CScriptParser::Enum_listContext::enum_item(size_t i) {
  return getRuleContext<CScriptParser::Enum_itemContext>(i);
}

std::vector<tree::TerminalNode *> CScriptParser::Enum_listContext::COMMA() {
  return getTokens(CScriptParser::COMMA);
}

tree::TerminalNode* CScriptParser::Enum_listContext::COMMA(size_t i) {
  return getToken(CScriptParser::COMMA, i);
}


size_t CScriptParser::Enum_listContext::getRuleIndex() const {
  return CScriptParser::RuleEnum_list;
}

void CScriptParser::Enum_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_list(this);
}

void CScriptParser::Enum_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_list(this);
}


std::any CScriptParser::Enum_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_listContext* CScriptParser::enum_list() {
  Enum_listContext *_localctx = _tracker.createInstance<Enum_listContext>(_ctx, getState());
  enterRule(_localctx, 38, CScriptParser::RuleEnum_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    enum_item();
    setState(362);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(358);
      match(CScriptParser::COMMA);
      setState(359);
      enum_item();
      setState(364);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Enum_itemContext ------------------------------------------------------------------

CScriptParser::Enum_itemContext::Enum_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::IdentContext* CScriptParser::Enum_itemContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Enum_itemContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
}

CScriptParser::ExprContext* CScriptParser::Enum_itemContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}


size_t CScriptParser::Enum_itemContext::getRuleIndex() const {
  return CScriptParser::RuleEnum_item;
}

void CScriptParser::Enum_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnum_item(this);
}

void CScriptParser::Enum_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnum_item(this);
}


std::any CScriptParser::Enum_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_item(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_itemContext* CScriptParser::enum_item() {
  Enum_itemContext *_localctx = _tracker.createInstance<Enum_itemContext>(_ctx, getState());
  enterRule(_localctx, 40, CScriptParser::RuleEnum_item);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365);
    ident();
    setState(368);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ASSIGN) {
      setState(366);
      match(CScriptParser::ASSIGN);
      setState(367);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Init_listContext ------------------------------------------------------------------

CScriptParser::Init_listContext::Init_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::ExprContext *> CScriptParser::Init_listContext::expr() {
  return getRuleContexts<CScriptParser::ExprContext>();
}

CScriptParser::ExprContext* CScriptParser::Init_listContext::expr(size_t i) {
  return getRuleContext<CScriptParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> CScriptParser::Init_listContext::COMMA() {
  return getTokens(CScriptParser::COMMA);
}

tree::TerminalNode* CScriptParser::Init_listContext::COMMA(size_t i) {
  return getToken(CScriptParser::COMMA, i);
}


size_t CScriptParser::Init_listContext::getRuleIndex() const {
  return CScriptParser::RuleInit_list;
}

void CScriptParser::Init_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInit_list(this);
}

void CScriptParser::Init_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInit_list(this);
}


std::any CScriptParser::Init_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitInit_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Init_listContext* CScriptParser::init_list() {
  Init_listContext *_localctx = _tracker.createInstance<Init_listContext>(_ctx, getState());
  enterRule(_localctx, 42, CScriptParser::RuleInit_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(370);
    expr();
    setState(375);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(371);
      match(CScriptParser::COMMA);
      setState(372);
      expr();
      setState(377);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CScriptParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::ExprContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::TypeContext* CScriptParser::ExprContext::type() {
  return getRuleContext<CScriptParser::TypeContext>(0);
}

tree::TerminalNode* CScriptParser::ExprContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

std::vector<CScriptParser::ExprContext *> CScriptParser::ExprContext::expr() {
  return getRuleContexts<CScriptParser::ExprContext>();
}

CScriptParser::ExprContext* CScriptParser::ExprContext::expr(size_t i) {
  return getRuleContext<CScriptParser::ExprContext>(i);
}

CScriptParser::Or_exprContext* CScriptParser::ExprContext::or_expr() {
  return getRuleContext<CScriptParser::Or_exprContext>(0);
}

tree::TerminalNode* CScriptParser::ExprContext::QUESTION() {
  return getToken(CScriptParser::QUESTION, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::COLON() {
  return getToken(CScriptParser::COLON, 0);
}

CScriptParser::Primary_exprContext* CScriptParser::ExprContext::primary_expr() {
  return getRuleContext<CScriptParser::Primary_exprContext>(0);
}

tree::TerminalNode* CScriptParser::ExprContext::DOT() {
  return getToken(CScriptParser::DOT, 0);
}

CScriptParser::IdentContext* CScriptParser::ExprContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::ExprContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::LBRACKET() {
  return getToken(CScriptParser::LBRACKET, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::RBRACKET() {
  return getToken(CScriptParser::RBRACKET, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::PLUS_EQ() {
  return getToken(CScriptParser::PLUS_EQ, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::MINUS_EQ() {
  return getToken(CScriptParser::MINUS_EQ, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::MUL_EQ() {
  return getToken(CScriptParser::MUL_EQ, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::DIV_EQ() {
  return getToken(CScriptParser::DIV_EQ, 0);
}

tree::TerminalNode* CScriptParser::ExprContext::MOD_EQ() {
  return getToken(CScriptParser::MOD_EQ, 0);
}


size_t CScriptParser::ExprContext::getRuleIndex() const {
  return CScriptParser::RuleExpr;
}

void CScriptParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void CScriptParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


std::any CScriptParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::ExprContext* CScriptParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 44, CScriptParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(427);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(378);
      match(CScriptParser::LPAREN);
      setState(379);
      type();
      setState(380);
      match(CScriptParser::RPAREN);
      setState(381);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(383);
      or_expr(0);
      setState(384);
      match(CScriptParser::QUESTION);
      setState(385);
      expr();
      setState(386);
      match(CScriptParser::COLON);
      setState(387);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(389);
      primary_expr();
      setState(390);
      match(CScriptParser::DOT);
      setState(391);
      ident();
      setState(392);
      match(CScriptParser::ASSIGN);
      setState(393);
      expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(395);
      ident();
      setState(396);
      match(CScriptParser::LBRACKET);
      setState(397);
      expr();
      setState(398);
      match(CScriptParser::RBRACKET);
      setState(399);
      match(CScriptParser::ASSIGN);
      setState(400);
      expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(402);
      ident();
      setState(403);
      match(CScriptParser::ASSIGN);
      setState(404);
      expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(406);
      ident();
      setState(407);
      match(CScriptParser::PLUS_EQ);
      setState(408);
      expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(410);
      ident();
      setState(411);
      match(CScriptParser::MINUS_EQ);
      setState(412);
      expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(414);
      ident();
      setState(415);
      match(CScriptParser::MUL_EQ);
      setState(416);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(418);
      ident();
      setState(419);
      match(CScriptParser::DIV_EQ);
      setState(420);
      expr();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(422);
      ident();
      setState(423);
      match(CScriptParser::MOD_EQ);
      setState(424);
      expr();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(426);
      or_expr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Or_exprContext ------------------------------------------------------------------

CScriptParser::Or_exprContext::Or_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::And_exprContext* CScriptParser::Or_exprContext::and_expr() {
  return getRuleContext<CScriptParser::And_exprContext>(0);
}

CScriptParser::Or_exprContext* CScriptParser::Or_exprContext::or_expr() {
  return getRuleContext<CScriptParser::Or_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Or_exprContext::OR() {
  return getToken(CScriptParser::OR, 0);
}


size_t CScriptParser::Or_exprContext::getRuleIndex() const {
  return CScriptParser::RuleOr_expr;
}

void CScriptParser::Or_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr_expr(this);
}

void CScriptParser::Or_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr_expr(this);
}


std::any CScriptParser::Or_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitOr_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Or_exprContext* CScriptParser::or_expr() {
   return or_expr(0);
}

CScriptParser::Or_exprContext* CScriptParser::or_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Or_exprContext *_localctx = _tracker.createInstance<Or_exprContext>(_ctx, parentState);
  CScriptParser::Or_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CScriptParser::RuleOr_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(430);
    and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(437);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleOr_expr);
        setState(432);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(433);
        match(CScriptParser::OR);
        setState(434);
        and_expr(0); 
      }
      setState(439);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- And_exprContext ------------------------------------------------------------------

CScriptParser::And_exprContext::And_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Bit_or_exprContext* CScriptParser::And_exprContext::bit_or_expr() {
  return getRuleContext<CScriptParser::Bit_or_exprContext>(0);
}

CScriptParser::And_exprContext* CScriptParser::And_exprContext::and_expr() {
  return getRuleContext<CScriptParser::And_exprContext>(0);
}

tree::TerminalNode* CScriptParser::And_exprContext::AND() {
  return getToken(CScriptParser::AND, 0);
}


size_t CScriptParser::And_exprContext::getRuleIndex() const {
  return CScriptParser::RuleAnd_expr;
}

void CScriptParser::And_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnd_expr(this);
}

void CScriptParser::And_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnd_expr(this);
}


std::any CScriptParser::And_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitAnd_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::And_exprContext* CScriptParser::and_expr() {
   return and_expr(0);
}

CScriptParser::And_exprContext* CScriptParser::and_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::And_exprContext *_localctx = _tracker.createInstance<And_exprContext>(_ctx, parentState);
  CScriptParser::And_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CScriptParser::RuleAnd_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(441);
    bit_or_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(448);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<And_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAnd_expr);
        setState(443);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(444);
        match(CScriptParser::AND);
        setState(445);
        bit_or_expr(0); 
      }
      setState(450);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Bit_or_exprContext ------------------------------------------------------------------

CScriptParser::Bit_or_exprContext::Bit_or_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Bit_xor_exprContext* CScriptParser::Bit_or_exprContext::bit_xor_expr() {
  return getRuleContext<CScriptParser::Bit_xor_exprContext>(0);
}

CScriptParser::Bit_or_exprContext* CScriptParser::Bit_or_exprContext::bit_or_expr() {
  return getRuleContext<CScriptParser::Bit_or_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Bit_or_exprContext::BITOR() {
  return getToken(CScriptParser::BITOR, 0);
}


size_t CScriptParser::Bit_or_exprContext::getRuleIndex() const {
  return CScriptParser::RuleBit_or_expr;
}

void CScriptParser::Bit_or_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBit_or_expr(this);
}

void CScriptParser::Bit_or_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBit_or_expr(this);
}


std::any CScriptParser::Bit_or_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBit_or_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Bit_or_exprContext* CScriptParser::bit_or_expr() {
   return bit_or_expr(0);
}

CScriptParser::Bit_or_exprContext* CScriptParser::bit_or_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Bit_or_exprContext *_localctx = _tracker.createInstance<Bit_or_exprContext>(_ctx, parentState);
  CScriptParser::Bit_or_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CScriptParser::RuleBit_or_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(452);
    bit_xor_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(459);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_or_expr);
        setState(454);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(455);
        match(CScriptParser::BITOR);
        setState(456);
        bit_xor_expr(0); 
      }
      setState(461);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Bit_xor_exprContext ------------------------------------------------------------------

CScriptParser::Bit_xor_exprContext::Bit_xor_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Bit_and_exprContext* CScriptParser::Bit_xor_exprContext::bit_and_expr() {
  return getRuleContext<CScriptParser::Bit_and_exprContext>(0);
}

CScriptParser::Bit_xor_exprContext* CScriptParser::Bit_xor_exprContext::bit_xor_expr() {
  return getRuleContext<CScriptParser::Bit_xor_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Bit_xor_exprContext::XOR() {
  return getToken(CScriptParser::XOR, 0);
}


size_t CScriptParser::Bit_xor_exprContext::getRuleIndex() const {
  return CScriptParser::RuleBit_xor_expr;
}

void CScriptParser::Bit_xor_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBit_xor_expr(this);
}

void CScriptParser::Bit_xor_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBit_xor_expr(this);
}


std::any CScriptParser::Bit_xor_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBit_xor_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Bit_xor_exprContext* CScriptParser::bit_xor_expr() {
   return bit_xor_expr(0);
}

CScriptParser::Bit_xor_exprContext* CScriptParser::bit_xor_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Bit_xor_exprContext *_localctx = _tracker.createInstance<Bit_xor_exprContext>(_ctx, parentState);
  CScriptParser::Bit_xor_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CScriptParser::RuleBit_xor_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(463);
    bit_and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(470);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_xor_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_xor_expr);
        setState(465);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(466);
        match(CScriptParser::XOR);
        setState(467);
        bit_and_expr(0); 
      }
      setState(472);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Bit_and_exprContext ------------------------------------------------------------------

CScriptParser::Bit_and_exprContext::Bit_and_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Eq_exprContext* CScriptParser::Bit_and_exprContext::eq_expr() {
  return getRuleContext<CScriptParser::Eq_exprContext>(0);
}

CScriptParser::Bit_and_exprContext* CScriptParser::Bit_and_exprContext::bit_and_expr() {
  return getRuleContext<CScriptParser::Bit_and_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Bit_and_exprContext::BITAND() {
  return getToken(CScriptParser::BITAND, 0);
}


size_t CScriptParser::Bit_and_exprContext::getRuleIndex() const {
  return CScriptParser::RuleBit_and_expr;
}

void CScriptParser::Bit_and_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBit_and_expr(this);
}

void CScriptParser::Bit_and_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBit_and_expr(this);
}


std::any CScriptParser::Bit_and_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBit_and_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Bit_and_exprContext* CScriptParser::bit_and_expr() {
   return bit_and_expr(0);
}

CScriptParser::Bit_and_exprContext* CScriptParser::bit_and_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Bit_and_exprContext *_localctx = _tracker.createInstance<Bit_and_exprContext>(_ctx, parentState);
  CScriptParser::Bit_and_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CScriptParser::RuleBit_and_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(474);
    eq_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(481);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_and_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_and_expr);
        setState(476);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(477);
        match(CScriptParser::BITAND);
        setState(478);
        eq_expr(0); 
      }
      setState(483);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Eq_exprContext ------------------------------------------------------------------

CScriptParser::Eq_exprContext::Eq_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Rel_exprContext* CScriptParser::Eq_exprContext::rel_expr() {
  return getRuleContext<CScriptParser::Rel_exprContext>(0);
}

CScriptParser::Eq_exprContext* CScriptParser::Eq_exprContext::eq_expr() {
  return getRuleContext<CScriptParser::Eq_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Eq_exprContext::EQ() {
  return getToken(CScriptParser::EQ, 0);
}

tree::TerminalNode* CScriptParser::Eq_exprContext::NEQ() {
  return getToken(CScriptParser::NEQ, 0);
}


size_t CScriptParser::Eq_exprContext::getRuleIndex() const {
  return CScriptParser::RuleEq_expr;
}

void CScriptParser::Eq_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEq_expr(this);
}

void CScriptParser::Eq_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEq_expr(this);
}


std::any CScriptParser::Eq_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEq_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Eq_exprContext* CScriptParser::eq_expr() {
   return eq_expr(0);
}

CScriptParser::Eq_exprContext* CScriptParser::eq_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Eq_exprContext *_localctx = _tracker.createInstance<Eq_exprContext>(_ctx, parentState);
  CScriptParser::Eq_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CScriptParser::RuleEq_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(485);
    rel_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(495);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(493);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(487);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(488);
          match(CScriptParser::EQ);
          setState(489);
          rel_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(490);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(491);
          match(CScriptParser::NEQ);
          setState(492);
          rel_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(497);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Rel_exprContext ------------------------------------------------------------------

CScriptParser::Rel_exprContext::Rel_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Shift_exprContext* CScriptParser::Rel_exprContext::shift_expr() {
  return getRuleContext<CScriptParser::Shift_exprContext>(0);
}

CScriptParser::Rel_exprContext* CScriptParser::Rel_exprContext::rel_expr() {
  return getRuleContext<CScriptParser::Rel_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Rel_exprContext::LT() {
  return getToken(CScriptParser::LT, 0);
}

tree::TerminalNode* CScriptParser::Rel_exprContext::LTE() {
  return getToken(CScriptParser::LTE, 0);
}

tree::TerminalNode* CScriptParser::Rel_exprContext::GT() {
  return getToken(CScriptParser::GT, 0);
}

tree::TerminalNode* CScriptParser::Rel_exprContext::GTE() {
  return getToken(CScriptParser::GTE, 0);
}


size_t CScriptParser::Rel_exprContext::getRuleIndex() const {
  return CScriptParser::RuleRel_expr;
}

void CScriptParser::Rel_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRel_expr(this);
}

void CScriptParser::Rel_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRel_expr(this);
}


std::any CScriptParser::Rel_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitRel_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Rel_exprContext* CScriptParser::rel_expr() {
   return rel_expr(0);
}

CScriptParser::Rel_exprContext* CScriptParser::rel_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Rel_exprContext *_localctx = _tracker.createInstance<Rel_exprContext>(_ctx, parentState);
  CScriptParser::Rel_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, CScriptParser::RuleRel_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(499);
    shift_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(515);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(513);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(501);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(502);
          match(CScriptParser::LT);
          setState(503);
          shift_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(504);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(505);
          match(CScriptParser::LTE);
          setState(506);
          shift_expr(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(507);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(508);
          match(CScriptParser::GT);
          setState(509);
          shift_expr(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(510);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(511);
          match(CScriptParser::GTE);
          setState(512);
          shift_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(517);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Shift_exprContext ------------------------------------------------------------------

CScriptParser::Shift_exprContext::Shift_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Add_exprContext* CScriptParser::Shift_exprContext::add_expr() {
  return getRuleContext<CScriptParser::Add_exprContext>(0);
}

CScriptParser::Shift_exprContext* CScriptParser::Shift_exprContext::shift_expr() {
  return getRuleContext<CScriptParser::Shift_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Shift_exprContext::LSHIFT() {
  return getToken(CScriptParser::LSHIFT, 0);
}

tree::TerminalNode* CScriptParser::Shift_exprContext::RSHIFT() {
  return getToken(CScriptParser::RSHIFT, 0);
}


size_t CScriptParser::Shift_exprContext::getRuleIndex() const {
  return CScriptParser::RuleShift_expr;
}

void CScriptParser::Shift_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShift_expr(this);
}

void CScriptParser::Shift_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShift_expr(this);
}


std::any CScriptParser::Shift_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitShift_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Shift_exprContext* CScriptParser::shift_expr() {
   return shift_expr(0);
}

CScriptParser::Shift_exprContext* CScriptParser::shift_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Shift_exprContext *_localctx = _tracker.createInstance<Shift_exprContext>(_ctx, parentState);
  CScriptParser::Shift_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, CScriptParser::RuleShift_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(519);
    add_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(529);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(527);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(521);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(522);
          match(CScriptParser::LSHIFT);
          setState(523);
          add_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(524);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(525);
          match(CScriptParser::RSHIFT);
          setState(526);
          add_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(531);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Add_exprContext ------------------------------------------------------------------

CScriptParser::Add_exprContext::Add_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Mul_exprContext* CScriptParser::Add_exprContext::mul_expr() {
  return getRuleContext<CScriptParser::Mul_exprContext>(0);
}

CScriptParser::Add_exprContext* CScriptParser::Add_exprContext::add_expr() {
  return getRuleContext<CScriptParser::Add_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Add_exprContext::PLUS() {
  return getToken(CScriptParser::PLUS, 0);
}

tree::TerminalNode* CScriptParser::Add_exprContext::MINUS() {
  return getToken(CScriptParser::MINUS, 0);
}


size_t CScriptParser::Add_exprContext::getRuleIndex() const {
  return CScriptParser::RuleAdd_expr;
}

void CScriptParser::Add_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_expr(this);
}

void CScriptParser::Add_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_expr(this);
}


std::any CScriptParser::Add_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitAdd_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Add_exprContext* CScriptParser::add_expr() {
   return add_expr(0);
}

CScriptParser::Add_exprContext* CScriptParser::add_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Add_exprContext *_localctx = _tracker.createInstance<Add_exprContext>(_ctx, parentState);
  CScriptParser::Add_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, CScriptParser::RuleAdd_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(533);
    mul_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(543);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(541);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(535);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(536);
          match(CScriptParser::PLUS);
          setState(537);
          mul_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(538);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(539);
          match(CScriptParser::MINUS);
          setState(540);
          mul_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(545);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Mul_exprContext ------------------------------------------------------------------

CScriptParser::Mul_exprContext::Mul_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Unary_exprContext* CScriptParser::Mul_exprContext::unary_expr() {
  return getRuleContext<CScriptParser::Unary_exprContext>(0);
}

CScriptParser::Mul_exprContext* CScriptParser::Mul_exprContext::mul_expr() {
  return getRuleContext<CScriptParser::Mul_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Mul_exprContext::MUL() {
  return getToken(CScriptParser::MUL, 0);
}

tree::TerminalNode* CScriptParser::Mul_exprContext::DIV() {
  return getToken(CScriptParser::DIV, 0);
}

tree::TerminalNode* CScriptParser::Mul_exprContext::MOD() {
  return getToken(CScriptParser::MOD, 0);
}


size_t CScriptParser::Mul_exprContext::getRuleIndex() const {
  return CScriptParser::RuleMul_expr;
}

void CScriptParser::Mul_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMul_expr(this);
}

void CScriptParser::Mul_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMul_expr(this);
}


std::any CScriptParser::Mul_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitMul_expr(this);
  else
    return visitor->visitChildren(this);
}


CScriptParser::Mul_exprContext* CScriptParser::mul_expr() {
   return mul_expr(0);
}

CScriptParser::Mul_exprContext* CScriptParser::mul_expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CScriptParser::Mul_exprContext *_localctx = _tracker.createInstance<Mul_exprContext>(_ctx, parentState);
  CScriptParser::Mul_exprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, CScriptParser::RuleMul_expr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(547);
    unary_expr();
    _ctx->stop = _input->LT(-1);
    setState(560);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(558);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(549);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(550);
          match(CScriptParser::MUL);
          setState(551);
          unary_expr();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(552);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(553);
          match(CScriptParser::DIV);
          setState(554);
          unary_expr();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(555);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(556);
          match(CScriptParser::MOD);
          setState(557);
          unary_expr();
          break;
        }

        default:
          break;
        } 
      }
      setState(562);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Unary_exprContext ------------------------------------------------------------------

CScriptParser::Unary_exprContext::Unary_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Primary_exprContext* CScriptParser::Unary_exprContext::primary_expr() {
  return getRuleContext<CScriptParser::Primary_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::NOT() {
  return getToken(CScriptParser::NOT, 0);
}

CScriptParser::Unary_exprContext* CScriptParser::Unary_exprContext::unary_expr() {
  return getRuleContext<CScriptParser::Unary_exprContext>(0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::NOTBIT() {
  return getToken(CScriptParser::NOTBIT, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::BITAND() {
  return getToken(CScriptParser::BITAND, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::MUL() {
  return getToken(CScriptParser::MUL, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::MINUS() {
  return getToken(CScriptParser::MINUS, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::PLUS() {
  return getToken(CScriptParser::PLUS, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::THROW() {
  return getToken(CScriptParser::THROW, 0);
}

CScriptParser::ExprContext* CScriptParser::Unary_exprContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

CScriptParser::IdentContext* CScriptParser::Unary_exprContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::INC() {
  return getToken(CScriptParser::INC, 0);
}

tree::TerminalNode* CScriptParser::Unary_exprContext::DEC() {
  return getToken(CScriptParser::DEC, 0);
}


size_t CScriptParser::Unary_exprContext::getRuleIndex() const {
  return CScriptParser::RuleUnary_expr;
}

void CScriptParser::Unary_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnary_expr(this);
}

void CScriptParser::Unary_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnary_expr(this);
}


std::any CScriptParser::Unary_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitUnary_expr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Unary_exprContext* CScriptParser::unary_expr() {
  Unary_exprContext *_localctx = _tracker.createInstance<Unary_exprContext>(_ctx, getState());
  enterRule(_localctx, 66, CScriptParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(584);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(563);
      primary_expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(564);
      match(CScriptParser::NOT);
      setState(565);
      unary_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(566);
      match(CScriptParser::NOTBIT);
      setState(567);
      unary_expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(568);
      match(CScriptParser::BITAND);
      setState(569);
      unary_expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(570);
      match(CScriptParser::MUL);
      setState(571);
      unary_expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(572);
      match(CScriptParser::MINUS);
      setState(573);
      unary_expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(574);
      match(CScriptParser::PLUS);
      setState(575);
      unary_expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(576);
      match(CScriptParser::THROW);
      setState(577);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(578);
      ident();
      setState(579);
      match(CScriptParser::INC);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(581);
      ident();
      setState(582);
      match(CScriptParser::DEC);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Primary_exprContext ------------------------------------------------------------------

CScriptParser::Primary_exprContext::Primary_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::IdentContext *> CScriptParser::Primary_exprContext::ident() {
  return getRuleContexts<CScriptParser::IdentContext>();
}

CScriptParser::IdentContext* CScriptParser::Primary_exprContext::ident(size_t i) {
  return getRuleContext<CScriptParser::IdentContext>(i);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

CScriptParser::Call_argsContext* CScriptParser::Primary_exprContext::call_args() {
  return getRuleContext<CScriptParser::Call_argsContext>(0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::LBRACKET() {
  return getToken(CScriptParser::LBRACKET, 0);
}

CScriptParser::ExprContext* CScriptParser::Primary_exprContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::RBRACKET() {
  return getToken(CScriptParser::RBRACKET, 0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::DOT() {
  return getToken(CScriptParser::DOT, 0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::INC() {
  return getToken(CScriptParser::INC, 0);
}

tree::TerminalNode* CScriptParser::Primary_exprContext::DEC() {
  return getToken(CScriptParser::DEC, 0);
}

CScriptParser::NumericContext* CScriptParser::Primary_exprContext::numeric() {
  return getRuleContext<CScriptParser::NumericContext>(0);
}


size_t CScriptParser::Primary_exprContext::getRuleIndex() const {
  return CScriptParser::RulePrimary_expr;
}

void CScriptParser::Primary_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary_expr(this);
}

void CScriptParser::Primary_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary_expr(this);
}


std::any CScriptParser::Primary_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitPrimary_expr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Primary_exprContext* CScriptParser::primary_expr() {
  Primary_exprContext *_localctx = _tracker.createInstance<Primary_exprContext>(_ctx, getState());
  enterRule(_localctx, 68, CScriptParser::RulePrimary_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(627);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(586);
      ident();
      setState(587);
      match(CScriptParser::LPAREN);
      setState(589);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260661395456) != 0)) {
        setState(588);
        call_args();
      }
      setState(591);
      match(CScriptParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(593);
      ident();
      setState(594);
      match(CScriptParser::LBRACKET);
      setState(595);
      expr();
      setState(596);
      match(CScriptParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(598);
      ident();
      setState(599);
      match(CScriptParser::DOT);
      setState(600);
      ident();
      setState(601);
      match(CScriptParser::LPAREN);
      setState(603);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260661395456) != 0)) {
        setState(602);
        call_args();
      }
      setState(605);
      match(CScriptParser::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(607);
      ident();
      setState(608);
      match(CScriptParser::DOT);
      setState(609);
      ident();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(611);
      ident();
      setState(612);
      match(CScriptParser::T__3);
      setState(613);
      ident();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(615);
      ident();
      setState(616);
      match(CScriptParser::INC);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(618);
      ident();
      setState(619);
      match(CScriptParser::DEC);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(621);
      ident();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(622);
      numeric();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(623);
      match(CScriptParser::LPAREN);
      setState(624);
      expr();
      setState(625);
      match(CScriptParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Call_argsContext ------------------------------------------------------------------

CScriptParser::Call_argsContext::Call_argsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::ExprContext *> CScriptParser::Call_argsContext::expr() {
  return getRuleContexts<CScriptParser::ExprContext>();
}

CScriptParser::ExprContext* CScriptParser::Call_argsContext::expr(size_t i) {
  return getRuleContext<CScriptParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> CScriptParser::Call_argsContext::COMMA() {
  return getTokens(CScriptParser::COMMA);
}

tree::TerminalNode* CScriptParser::Call_argsContext::COMMA(size_t i) {
  return getToken(CScriptParser::COMMA, i);
}


size_t CScriptParser::Call_argsContext::getRuleIndex() const {
  return CScriptParser::RuleCall_args;
}

void CScriptParser::Call_argsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall_args(this);
}

void CScriptParser::Call_argsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall_args(this);
}


std::any CScriptParser::Call_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCall_args(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Call_argsContext* CScriptParser::call_args() {
  Call_argsContext *_localctx = _tracker.createInstance<Call_argsContext>(_ctx, getState());
  enterRule(_localctx, 70, CScriptParser::RuleCall_args);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(629);
    expr();
    setState(634);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(630);
      match(CScriptParser::COMMA);
      setState(631);
      expr();
      setState(636);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

CScriptParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::NumericContext::INTEGER() {
  return getToken(CScriptParser::INTEGER, 0);
}

tree::TerminalNode* CScriptParser::NumericContext::DOUBLE() {
  return getToken(CScriptParser::DOUBLE, 0);
}

tree::TerminalNode* CScriptParser::NumericContext::CHAR() {
  return getToken(CScriptParser::CHAR, 0);
}

tree::TerminalNode* CScriptParser::NumericContext::STRING() {
  return getToken(CScriptParser::STRING, 0);
}


size_t CScriptParser::NumericContext::getRuleIndex() const {
  return CScriptParser::RuleNumeric;
}

void CScriptParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void CScriptParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


std::any CScriptParser::NumericContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitNumeric(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::NumericContext* CScriptParser::numeric() {
  NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, getState());
  enterRule(_localctx, 72, CScriptParser::RuleNumeric);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(637);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2013265920) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_stmtContext ------------------------------------------------------------------

CScriptParser::If_stmtContext::If_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::If_stmtContext::IF() {
  return getToken(CScriptParser::IF, 0);
}

tree::TerminalNode* CScriptParser::If_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::ExprContext* CScriptParser::If_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::If_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

std::vector<CScriptParser::BodyContext *> CScriptParser::If_stmtContext::body() {
  return getRuleContexts<CScriptParser::BodyContext>();
}

CScriptParser::BodyContext* CScriptParser::If_stmtContext::body(size_t i) {
  return getRuleContext<CScriptParser::BodyContext>(i);
}

tree::TerminalNode* CScriptParser::If_stmtContext::ELSE() {
  return getToken(CScriptParser::ELSE, 0);
}


size_t CScriptParser::If_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleIf_stmt;
}

void CScriptParser::If_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf_stmt(this);
}

void CScriptParser::If_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf_stmt(this);
}


std::any CScriptParser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::If_stmtContext* CScriptParser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 74, CScriptParser::RuleIf_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(639);
    match(CScriptParser::IF);
    setState(640);
    match(CScriptParser::LPAREN);
    setState(641);
    expr();
    setState(642);
    match(CScriptParser::RPAREN);
    setState(643);
    body();
    setState(646);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(644);
      match(CScriptParser::ELSE);
      setState(645);
      body();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_stmtContext ------------------------------------------------------------------

CScriptParser::While_stmtContext::While_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::While_stmtContext::WHILE() {
  return getToken(CScriptParser::WHILE, 0);
}

tree::TerminalNode* CScriptParser::While_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::ExprContext* CScriptParser::While_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::While_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

CScriptParser::BodyContext* CScriptParser::While_stmtContext::body() {
  return getRuleContext<CScriptParser::BodyContext>(0);
}


size_t CScriptParser::While_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleWhile_stmt;
}

void CScriptParser::While_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile_stmt(this);
}

void CScriptParser::While_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile_stmt(this);
}


std::any CScriptParser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::While_stmtContext* CScriptParser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 76, CScriptParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(648);
    match(CScriptParser::WHILE);
    setState(649);
    match(CScriptParser::LPAREN);
    setState(650);
    expr();
    setState(651);
    match(CScriptParser::RPAREN);
    setState(652);
    body();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_stmtContext ------------------------------------------------------------------

CScriptParser::For_stmtContext::For_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::For_stmtContext::FOR() {
  return getToken(CScriptParser::FOR, 0);
}

tree::TerminalNode* CScriptParser::For_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> CScriptParser::For_stmtContext::SEMI() {
  return getTokens(CScriptParser::SEMI);
}

tree::TerminalNode* CScriptParser::For_stmtContext::SEMI(size_t i) {
  return getToken(CScriptParser::SEMI, i);
}

tree::TerminalNode* CScriptParser::For_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

CScriptParser::BodyContext* CScriptParser::For_stmtContext::body() {
  return getRuleContext<CScriptParser::BodyContext>(0);
}

CScriptParser::For_initContext* CScriptParser::For_stmtContext::for_init() {
  return getRuleContext<CScriptParser::For_initContext>(0);
}

CScriptParser::For_condContext* CScriptParser::For_stmtContext::for_cond() {
  return getRuleContext<CScriptParser::For_condContext>(0);
}

CScriptParser::For_incrContext* CScriptParser::For_stmtContext::for_incr() {
  return getRuleContext<CScriptParser::For_incrContext>(0);
}


size_t CScriptParser::For_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleFor_stmt;
}

void CScriptParser::For_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_stmt(this);
}

void CScriptParser::For_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_stmt(this);
}


std::any CScriptParser::For_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_stmtContext* CScriptParser::for_stmt() {
  For_stmtContext *_localctx = _tracker.createInstance<For_stmtContext>(_ctx, getState());
  enterRule(_localctx, 78, CScriptParser::RuleFor_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(654);
    match(CScriptParser::FOR);
    setState(655);
    match(CScriptParser::LPAREN);
    setState(657);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260664803328) != 0)) {
      setState(656);
      for_init();
    }
    setState(659);
    match(CScriptParser::SEMI);
    setState(661);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260661395456) != 0)) {
      setState(660);
      for_cond();
    }
    setState(663);
    match(CScriptParser::SEMI);
    setState(665);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260661395456) != 0)) {
      setState(664);
      for_incr();
    }
    setState(667);
    match(CScriptParser::RPAREN);
    setState(668);
    body();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_initContext ------------------------------------------------------------------

CScriptParser::For_initContext::For_initContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::Var_declContext* CScriptParser::For_initContext::var_decl() {
  return getRuleContext<CScriptParser::Var_declContext>(0);
}

CScriptParser::ExprContext* CScriptParser::For_initContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}


size_t CScriptParser::For_initContext::getRuleIndex() const {
  return CScriptParser::RuleFor_init;
}

void CScriptParser::For_initContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_init(this);
}

void CScriptParser::For_initContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_init(this);
}


std::any CScriptParser::For_initContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_init(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_initContext* CScriptParser::for_init() {
  For_initContext *_localctx = _tracker.createInstance<For_initContext>(_ctx, getState());
  enterRule(_localctx, 80, CScriptParser::RuleFor_init);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(672);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(670);
      var_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(671);
      expr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_condContext ------------------------------------------------------------------

CScriptParser::For_condContext::For_condContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::ExprContext* CScriptParser::For_condContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}


size_t CScriptParser::For_condContext::getRuleIndex() const {
  return CScriptParser::RuleFor_cond;
}

void CScriptParser::For_condContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_cond(this);
}

void CScriptParser::For_condContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_cond(this);
}


std::any CScriptParser::For_condContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_cond(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_condContext* CScriptParser::for_cond() {
  For_condContext *_localctx = _tracker.createInstance<For_condContext>(_ctx, getState());
  enterRule(_localctx, 82, CScriptParser::RuleFor_cond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(674);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_incrContext ------------------------------------------------------------------

CScriptParser::For_incrContext::For_incrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::ExprContext* CScriptParser::For_incrContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}


size_t CScriptParser::For_incrContext::getRuleIndex() const {
  return CScriptParser::RuleFor_incr;
}

void CScriptParser::For_incrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_incr(this);
}

void CScriptParser::For_incrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_incr(this);
}


std::any CScriptParser::For_incrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_incr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_incrContext* CScriptParser::for_incr() {
  For_incrContext *_localctx = _tracker.createInstance<For_incrContext>(_ctx, getState());
  enterRule(_localctx, 84, CScriptParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(676);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Do_while_stmtContext ------------------------------------------------------------------

CScriptParser::Do_while_stmtContext::Do_while_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Do_while_stmtContext::DO() {
  return getToken(CScriptParser::DO, 0);
}

CScriptParser::BodyContext* CScriptParser::Do_while_stmtContext::body() {
  return getRuleContext<CScriptParser::BodyContext>(0);
}

tree::TerminalNode* CScriptParser::Do_while_stmtContext::WHILE() {
  return getToken(CScriptParser::WHILE, 0);
}

tree::TerminalNode* CScriptParser::Do_while_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::ExprContext* CScriptParser::Do_while_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Do_while_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

tree::TerminalNode* CScriptParser::Do_while_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}


size_t CScriptParser::Do_while_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleDo_while_stmt;
}

void CScriptParser::Do_while_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDo_while_stmt(this);
}

void CScriptParser::Do_while_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDo_while_stmt(this);
}


std::any CScriptParser::Do_while_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitDo_while_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Do_while_stmtContext* CScriptParser::do_while_stmt() {
  Do_while_stmtContext *_localctx = _tracker.createInstance<Do_while_stmtContext>(_ctx, getState());
  enterRule(_localctx, 86, CScriptParser::RuleDo_while_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    match(CScriptParser::DO);
    setState(679);
    body();
    setState(680);
    match(CScriptParser::WHILE);
    setState(681);
    match(CScriptParser::LPAREN);
    setState(682);
    expr();
    setState(683);
    match(CScriptParser::RPAREN);
    setState(685);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::SEMI) {
      setState(684);
      match(CScriptParser::SEMI);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Try_catch_stmtContext ------------------------------------------------------------------

CScriptParser::Try_catch_stmtContext::Try_catch_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CScriptParser::BlockContext* CScriptParser::Try_catch_stmtContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
}

std::vector<CScriptParser::Catch_blockContext *> CScriptParser::Try_catch_stmtContext::catch_block() {
  return getRuleContexts<CScriptParser::Catch_blockContext>();
}

CScriptParser::Catch_blockContext* CScriptParser::Try_catch_stmtContext::catch_block(size_t i) {
  return getRuleContext<CScriptParser::Catch_blockContext>(i);
}


size_t CScriptParser::Try_catch_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleTry_catch_stmt;
}

void CScriptParser::Try_catch_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTry_catch_stmt(this);
}

void CScriptParser::Try_catch_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTry_catch_stmt(this);
}


std::any CScriptParser::Try_catch_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitTry_catch_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Try_catch_stmtContext* CScriptParser::try_catch_stmt() {
  Try_catch_stmtContext *_localctx = _tracker.createInstance<Try_catch_stmtContext>(_ctx, getState());
  enterRule(_localctx, 88, CScriptParser::RuleTry_catch_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(687);
    match(CScriptParser::T__4);
    setState(688);
    block();
    setState(690); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(689);
      catch_block();
      setState(692); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CScriptParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Catch_blockContext ------------------------------------------------------------------

CScriptParser::Catch_blockContext::Catch_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Catch_blockContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::TypeContext* CScriptParser::Catch_blockContext::type() {
  return getRuleContext<CScriptParser::TypeContext>(0);
}

CScriptParser::IdentContext* CScriptParser::Catch_blockContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::Catch_blockContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

CScriptParser::BlockContext* CScriptParser::Catch_blockContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
}

tree::TerminalNode* CScriptParser::Catch_blockContext::ELLIPSIS() {
  return getToken(CScriptParser::ELLIPSIS, 0);
}


size_t CScriptParser::Catch_blockContext::getRuleIndex() const {
  return CScriptParser::RuleCatch_block;
}

void CScriptParser::Catch_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatch_block(this);
}

void CScriptParser::Catch_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatch_block(this);
}


std::any CScriptParser::Catch_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCatch_block(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Catch_blockContext* CScriptParser::catch_block() {
  Catch_blockContext *_localctx = _tracker.createInstance<Catch_blockContext>(_ctx, getState());
  enterRule(_localctx, 90, CScriptParser::RuleCatch_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(706);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(694);
      match(CScriptParser::T__5);
      setState(695);
      match(CScriptParser::LPAREN);
      setState(696);
      type();
      setState(697);
      ident();
      setState(698);
      match(CScriptParser::RPAREN);
      setState(699);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(701);
      match(CScriptParser::T__5);
      setState(702);
      match(CScriptParser::LPAREN);
      setState(703);
      match(CScriptParser::ELLIPSIS);
      setState(704);
      match(CScriptParser::RPAREN);
      setState(705);
      block();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Switch_stmtContext ------------------------------------------------------------------

CScriptParser::Switch_stmtContext::Switch_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Switch_stmtContext::SWITCH() {
  return getToken(CScriptParser::SWITCH, 0);
}

tree::TerminalNode* CScriptParser::Switch_stmtContext::LPAREN() {
  return getToken(CScriptParser::LPAREN, 0);
}

CScriptParser::ExprContext* CScriptParser::Switch_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Switch_stmtContext::RPAREN() {
  return getToken(CScriptParser::RPAREN, 0);
}

tree::TerminalNode* CScriptParser::Switch_stmtContext::LBRACE() {
  return getToken(CScriptParser::LBRACE, 0);
}

CScriptParser::Case_listContext* CScriptParser::Switch_stmtContext::case_list() {
  return getRuleContext<CScriptParser::Case_listContext>(0);
}

tree::TerminalNode* CScriptParser::Switch_stmtContext::RBRACE() {
  return getToken(CScriptParser::RBRACE, 0);
}


size_t CScriptParser::Switch_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleSwitch_stmt;
}

void CScriptParser::Switch_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitch_stmt(this);
}

void CScriptParser::Switch_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitch_stmt(this);
}


std::any CScriptParser::Switch_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitSwitch_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Switch_stmtContext* CScriptParser::switch_stmt() {
  Switch_stmtContext *_localctx = _tracker.createInstance<Switch_stmtContext>(_ctx, getState());
  enterRule(_localctx, 92, CScriptParser::RuleSwitch_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(708);
    match(CScriptParser::SWITCH);
    setState(709);
    match(CScriptParser::LPAREN);
    setState(710);
    expr();
    setState(711);
    match(CScriptParser::RPAREN);
    setState(712);
    match(CScriptParser::LBRACE);
    setState(713);
    case_list();
    setState(714);
    match(CScriptParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Case_listContext ------------------------------------------------------------------

CScriptParser::Case_listContext::Case_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CScriptParser::Case_stmtContext *> CScriptParser::Case_listContext::case_stmt() {
  return getRuleContexts<CScriptParser::Case_stmtContext>();
}

CScriptParser::Case_stmtContext* CScriptParser::Case_listContext::case_stmt(size_t i) {
  return getRuleContext<CScriptParser::Case_stmtContext>(i);
}


size_t CScriptParser::Case_listContext::getRuleIndex() const {
  return CScriptParser::RuleCase_list;
}

void CScriptParser::Case_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCase_list(this);
}

void CScriptParser::Case_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCase_list(this);
}


std::any CScriptParser::Case_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCase_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Case_listContext* CScriptParser::case_list() {
  Case_listContext *_localctx = _tracker.createInstance<Case_listContext>(_ctx, getState());
  enterRule(_localctx, 94, CScriptParser::RuleCase_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(719);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::CASE

    || _la == CScriptParser::DEFAULT) {
      setState(716);
      case_stmt();
      setState(721);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Case_stmtContext ------------------------------------------------------------------

CScriptParser::Case_stmtContext::Case_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CScriptParser::Case_stmtContext::CASE() {
  return getToken(CScriptParser::CASE, 0);
}

CScriptParser::ExprContext* CScriptParser::Case_stmtContext::expr() {
  return getRuleContext<CScriptParser::ExprContext>(0);
}

tree::TerminalNode* CScriptParser::Case_stmtContext::COLON() {
  return getToken(CScriptParser::COLON, 0);
}

std::vector<CScriptParser::StmtContext *> CScriptParser::Case_stmtContext::stmt() {
  return getRuleContexts<CScriptParser::StmtContext>();
}

CScriptParser::StmtContext* CScriptParser::Case_stmtContext::stmt(size_t i) {
  return getRuleContext<CScriptParser::StmtContext>(i);
}

tree::TerminalNode* CScriptParser::Case_stmtContext::DEFAULT() {
  return getToken(CScriptParser::DEFAULT, 0);
}


size_t CScriptParser::Case_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleCase_stmt;
}

void CScriptParser::Case_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCase_stmt(this);
}

void CScriptParser::Case_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCase_stmt(this);
}


std::any CScriptParser::Case_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCase_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Case_stmtContext* CScriptParser::case_stmt() {
  Case_stmtContext *_localctx = _tracker.createInstance<Case_stmtContext>(_ctx, getState());
  enterRule(_localctx, 96, CScriptParser::RuleCase_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(739);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::CASE: {
        enterOuterAlt(_localctx, 1);
        setState(722);
        match(CScriptParser::CASE);
        setState(723);
        expr();
        setState(724);
        match(CScriptParser::COLON);
        setState(728);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
          setState(725);
          stmt();
          setState(730);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CScriptParser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(731);
        match(CScriptParser::DEFAULT);
        setState(732);
        match(CScriptParser::COLON);
        setState(736);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
          setState(733);
          stmt();
          setState(738);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 23: return or_exprSempred(antlrcpp::downCast<Or_exprContext *>(context), predicateIndex);
    case 24: return and_exprSempred(antlrcpp::downCast<And_exprContext *>(context), predicateIndex);
    case 25: return bit_or_exprSempred(antlrcpp::downCast<Bit_or_exprContext *>(context), predicateIndex);
    case 26: return bit_xor_exprSempred(antlrcpp::downCast<Bit_xor_exprContext *>(context), predicateIndex);
    case 27: return bit_and_exprSempred(antlrcpp::downCast<Bit_and_exprContext *>(context), predicateIndex);
    case 28: return eq_exprSempred(antlrcpp::downCast<Eq_exprContext *>(context), predicateIndex);
    case 29: return rel_exprSempred(antlrcpp::downCast<Rel_exprContext *>(context), predicateIndex);
    case 30: return shift_exprSempred(antlrcpp::downCast<Shift_exprContext *>(context), predicateIndex);
    case 31: return add_exprSempred(antlrcpp::downCast<Add_exprContext *>(context), predicateIndex);
    case 32: return mul_exprSempred(antlrcpp::downCast<Mul_exprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CScriptParser::or_exprSempred(Or_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::and_exprSempred(And_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::bit_or_exprSempred(Bit_or_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::bit_xor_exprSempred(Bit_xor_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::bit_and_exprSempred(Bit_and_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::eq_exprSempred(Eq_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 2);
    case 6: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::rel_exprSempred(Rel_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 4);
    case 8: return precpred(_ctx, 3);
    case 9: return precpred(_ctx, 2);
    case 10: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::shift_exprSempred(Shift_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 2);
    case 12: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::add_exprSempred(Add_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 2);
    case 14: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CScriptParser::mul_exprSempred(Mul_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 15: return precpred(_ctx, 3);
    case 16: return precpred(_ctx, 2);
    case 17: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CScriptParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cscriptParserInitialize();
#else
  ::antlr4::internal::call_once(cscriptParserOnceFlag, cscriptParserInitialize);
#endif
}
