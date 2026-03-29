
// Generated from D:/MyCode/CScriptEngine/src/frontend/parser/CScript.g4 by ANTLR 4.13.2


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
      "block", "var_decl", "func_decl", "extern_decl", "func_decl_args", 
      "ident", "type", "struct_decl", "union_decl", "struct_members", "enum_decl", 
      "enum_list", "enum_item", "init_list", "expr", "or_expr", "and_expr", 
      "bit_or_expr", "bit_xor_expr", "bit_and_expr", "eq_expr", "rel_expr", 
      "shift_expr", "add_expr", "mul_expr", "unary_expr", "primary_expr", 
      "call_args", "numeric", "if_stmt", "while_stmt", "for_stmt", "for_init", 
      "for_cond", "for_incr", "do_while_stmt", "try_catch_stmt", "catch_block", 
      "switch_stmt", "case_list", "case_stmt"
    },
    std::vector<std::string>{
      "", "'import'", "'as'", "'from'", "'include'", "'register'", "'::'", 
      "'try'", "'catch'", "'return'", "'if'", "'else'", "'while'", "'for'", 
      "'do'", "'switch'", "'case'", "'default'", "'continue'", "'break'", 
      "'struct'", "'union'", "'enum'", "'const'", "'extern'", "'throw'", 
      "", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'%'", "'=='", "'!='", 
      "'<'", "'<='", "'>'", "'>='", "'&&'", "'||'", "'!'", "'&'", "'|'", 
      "'^'", "'~'", "'<<'", "'>>'", "'\\u003F'", "':'", "','", "';'", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'.'", "'='", "'+='", "'-='", "'*='", 
      "'/='", "'%='", "'++'", "'--'", "'...'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "RETURN", "IF", "ELSE", "WHILE", 
      "FOR", "DO", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "BREAK", "STRUCT_KW", 
      "UNION_KW", "ENUM_KW", "CONST_KW", "EXTERN_KW", "THROW", "INTEGER", 
      "DOUBLE", "CHAR", "STRING", "IDENTIFIER", "PLUS", "MINUS", "MUL", 
      "DIV", "MOD", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND", "OR", 
      "NOT", "BITAND", "BITOR", "XOR", "NOTBIT", "LSHIFT", "RSHIFT", "QUESTION", 
      "COLON", "COMMA", "SEMI", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "DOT", "ASSIGN", "PLUS_EQ", "MINUS_EQ", "MUL_EQ", 
      "DIV_EQ", "MOD_EQ", "INC", "DEC", "ELLIPSIS", "COMMENT", "MULTI_LINE_COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,73,679,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,1,0,5,0,94,8,0,10,0,12,0,97,9,0,1,0,
  	1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,3,1,141,8,1,1,2,1,2,1,2,1,2,3,2,147,8,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,5,2,155,8,2,10,2,12,2,158,9,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,165,8,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,177,8,4,1,4,1,4,
  	1,4,1,5,1,5,5,5,184,8,5,10,5,12,5,187,9,5,1,5,1,5,1,5,3,5,192,8,5,1,6,
  	1,6,1,6,1,6,3,6,198,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,210,
  	8,6,1,6,1,6,1,6,1,6,1,6,3,6,217,8,6,1,6,1,6,1,6,1,6,1,6,3,6,224,8,6,1,
  	6,1,6,1,6,1,6,1,6,3,6,231,8,6,3,6,233,8,6,1,7,1,7,1,7,1,7,3,7,239,8,7,
  	1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,3,8,249,8,8,1,8,1,8,1,8,1,9,1,9,1,9,5,
  	9,257,8,9,10,9,12,9,260,9,9,1,10,1,10,1,11,1,11,5,11,266,8,11,10,11,12,
  	11,269,9,11,1,11,1,11,3,11,273,8,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,5,14,292,8,14,10,14,
  	12,14,295,9,14,1,15,1,15,3,15,299,8,15,1,15,1,15,1,15,1,15,1,15,1,16,
  	1,16,1,16,5,16,309,8,16,10,16,12,16,312,9,16,1,17,1,17,1,17,3,17,317,
  	8,17,1,18,1,18,1,18,5,18,322,8,18,10,18,12,18,325,9,18,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,3,19,376,8,19,1,20,1,20,1,20,1,20,1,20,1,20,5,20,
  	384,8,20,10,20,12,20,387,9,20,1,21,1,21,1,21,1,21,1,21,1,21,5,21,395,
  	8,21,10,21,12,21,398,9,21,1,22,1,22,1,22,1,22,1,22,1,22,5,22,406,8,22,
  	10,22,12,22,409,9,22,1,23,1,23,1,23,1,23,1,23,1,23,5,23,417,8,23,10,23,
  	12,23,420,9,23,1,24,1,24,1,24,1,24,1,24,1,24,5,24,428,8,24,10,24,12,24,
  	431,9,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,5,25,442,8,25,10,
  	25,12,25,445,9,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,1,26,1,26,1,26,1,26,5,26,462,8,26,10,26,12,26,465,9,26,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,5,27,476,8,27,10,27,12,27,479,9,27,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,5,28,490,8,28,10,28,12,28,
  	493,9,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	5,29,507,8,29,10,29,12,29,510,9,29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,
  	3,30,533,8,30,1,31,1,31,1,31,3,31,538,8,31,1,31,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,3,31,567,8,31,1,32,1,32,1,32,5,
  	32,572,8,32,10,32,12,32,575,9,32,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,
  	34,1,34,3,34,586,8,34,1,35,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,3,
  	36,597,8,36,1,36,1,36,3,36,601,8,36,1,36,1,36,3,36,605,8,36,1,36,1,36,
  	1,36,1,37,1,37,3,37,612,8,37,1,38,1,38,1,39,1,39,1,40,1,40,1,40,1,40,
  	1,40,1,40,1,40,1,41,1,41,1,41,4,41,628,8,41,11,41,12,41,629,1,42,1,42,
  	1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,3,42,644,8,42,1,43,
  	1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,44,5,44,655,8,44,10,44,12,44,658,
  	9,44,1,45,1,45,1,45,1,45,5,45,664,8,45,10,45,12,45,667,9,45,1,45,1,45,
  	1,45,5,45,672,8,45,10,45,12,45,675,9,45,3,45,677,8,45,1,45,0,10,40,42,
  	44,46,48,50,52,54,56,58,46,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,
  	78,80,82,84,86,88,90,0,1,1,0,26,29,737,0,95,1,0,0,0,2,140,1,0,0,0,4,164,
  	1,0,0,0,6,166,1,0,0,0,8,170,1,0,0,0,10,191,1,0,0,0,12,232,1,0,0,0,14,
  	234,1,0,0,0,16,243,1,0,0,0,18,253,1,0,0,0,20,261,1,0,0,0,22,272,1,0,0,
  	0,24,274,1,0,0,0,26,280,1,0,0,0,28,286,1,0,0,0,30,296,1,0,0,0,32,305,
  	1,0,0,0,34,313,1,0,0,0,36,318,1,0,0,0,38,375,1,0,0,0,40,377,1,0,0,0,42,
  	388,1,0,0,0,44,399,1,0,0,0,46,410,1,0,0,0,48,421,1,0,0,0,50,432,1,0,0,
  	0,52,446,1,0,0,0,54,466,1,0,0,0,56,480,1,0,0,0,58,494,1,0,0,0,60,532,
  	1,0,0,0,62,566,1,0,0,0,64,568,1,0,0,0,66,576,1,0,0,0,68,578,1,0,0,0,70,
  	587,1,0,0,0,72,593,1,0,0,0,74,611,1,0,0,0,76,613,1,0,0,0,78,615,1,0,0,
  	0,80,617,1,0,0,0,82,624,1,0,0,0,84,643,1,0,0,0,86,645,1,0,0,0,88,656,
  	1,0,0,0,90,676,1,0,0,0,92,94,3,2,1,0,93,92,1,0,0,0,94,97,1,0,0,0,95,93,
  	1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,0,0,1,99,1,
  	1,0,0,0,100,101,3,12,6,0,101,102,5,54,0,0,102,141,1,0,0,0,103,141,3,30,
  	15,0,104,141,3,14,7,0,105,141,3,16,8,0,106,141,3,24,12,0,107,108,3,24,
  	12,0,108,109,5,54,0,0,109,141,1,0,0,0,110,141,3,26,13,0,111,112,3,26,
  	13,0,112,113,5,54,0,0,113,141,1,0,0,0,114,115,3,38,19,0,115,116,5,54,
  	0,0,116,141,1,0,0,0,117,118,5,33,0,0,118,119,3,20,10,0,119,120,5,62,0,
  	0,120,121,3,38,19,0,121,122,5,54,0,0,122,141,1,0,0,0,123,124,5,9,0,0,
  	124,125,3,38,19,0,125,126,5,54,0,0,126,141,1,0,0,0,127,141,3,68,34,0,
  	128,141,3,70,35,0,129,141,3,72,36,0,130,141,3,80,40,0,131,141,3,86,43,
  	0,132,141,3,82,41,0,133,134,5,18,0,0,134,141,5,54,0,0,135,136,5,19,0,
  	0,136,141,5,54,0,0,137,141,3,8,4,0,138,141,3,4,2,0,139,141,3,6,3,0,140,
  	100,1,0,0,0,140,103,1,0,0,0,140,104,1,0,0,0,140,105,1,0,0,0,140,106,1,
  	0,0,0,140,107,1,0,0,0,140,110,1,0,0,0,140,111,1,0,0,0,140,114,1,0,0,0,
  	140,117,1,0,0,0,140,123,1,0,0,0,140,127,1,0,0,0,140,128,1,0,0,0,140,129,
  	1,0,0,0,140,130,1,0,0,0,140,131,1,0,0,0,140,132,1,0,0,0,140,133,1,0,0,
  	0,140,135,1,0,0,0,140,137,1,0,0,0,140,138,1,0,0,0,140,139,1,0,0,0,141,
  	3,1,0,0,0,142,143,5,1,0,0,143,146,5,29,0,0,144,145,5,2,0,0,145,147,3,
  	20,10,0,146,144,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,165,5,54,
  	0,0,149,150,5,1,0,0,150,151,5,57,0,0,151,156,3,20,10,0,152,153,5,53,0,
  	0,153,155,3,20,10,0,154,152,1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,156,
  	157,1,0,0,0,157,159,1,0,0,0,158,156,1,0,0,0,159,160,5,58,0,0,160,161,
  	5,3,0,0,161,162,5,29,0,0,162,163,5,54,0,0,163,165,1,0,0,0,164,142,1,0,
  	0,0,164,149,1,0,0,0,165,5,1,0,0,0,166,167,5,4,0,0,167,168,5,29,0,0,168,
  	169,5,54,0,0,169,7,1,0,0,0,170,171,5,5,0,0,171,172,3,20,10,0,172,173,
  	5,2,0,0,173,174,3,20,10,0,174,176,5,55,0,0,175,177,3,18,9,0,176,175,1,
  	0,0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,179,5,56,0,0,179,180,5,54,0,
  	0,180,9,1,0,0,0,181,185,5,57,0,0,182,184,3,2,1,0,183,182,1,0,0,0,184,
  	187,1,0,0,0,185,183,1,0,0,0,185,186,1,0,0,0,186,188,1,0,0,0,187,185,1,
  	0,0,0,188,192,5,58,0,0,189,190,5,57,0,0,190,192,5,58,0,0,191,181,1,0,
  	0,0,191,189,1,0,0,0,192,11,1,0,0,0,193,194,3,22,11,0,194,197,3,20,10,
  	0,195,196,5,62,0,0,196,198,3,38,19,0,197,195,1,0,0,0,197,198,1,0,0,0,
  	198,233,1,0,0,0,199,200,3,22,11,0,200,201,3,20,10,0,201,202,5,59,0,0,
  	202,203,3,38,19,0,203,209,5,60,0,0,204,205,5,62,0,0,205,206,5,57,0,0,
  	206,207,3,36,18,0,207,208,5,58,0,0,208,210,1,0,0,0,209,204,1,0,0,0,209,
  	210,1,0,0,0,210,233,1,0,0,0,211,212,3,22,11,0,212,213,5,33,0,0,213,216,
  	3,20,10,0,214,215,5,62,0,0,215,217,3,38,19,0,216,214,1,0,0,0,216,217,
  	1,0,0,0,217,233,1,0,0,0,218,219,5,23,0,0,219,220,3,22,11,0,220,223,3,
  	20,10,0,221,222,5,62,0,0,222,224,3,38,19,0,223,221,1,0,0,0,223,224,1,
  	0,0,0,224,233,1,0,0,0,225,226,5,20,0,0,226,227,3,20,10,0,227,230,3,20,
  	10,0,228,229,5,62,0,0,229,231,3,38,19,0,230,228,1,0,0,0,230,231,1,0,0,
  	0,231,233,1,0,0,0,232,193,1,0,0,0,232,199,1,0,0,0,232,211,1,0,0,0,232,
  	218,1,0,0,0,232,225,1,0,0,0,233,13,1,0,0,0,234,235,3,22,11,0,235,236,
  	3,20,10,0,236,238,5,55,0,0,237,239,3,18,9,0,238,237,1,0,0,0,238,239,1,
  	0,0,0,239,240,1,0,0,0,240,241,5,56,0,0,241,242,3,10,5,0,242,15,1,0,0,
  	0,243,244,5,24,0,0,244,245,3,22,11,0,245,246,3,20,10,0,246,248,5,55,0,
  	0,247,249,3,18,9,0,248,247,1,0,0,0,248,249,1,0,0,0,249,250,1,0,0,0,250,
  	251,5,56,0,0,251,252,5,54,0,0,252,17,1,0,0,0,253,258,3,12,6,0,254,255,
  	5,53,0,0,255,257,3,12,6,0,256,254,1,0,0,0,257,260,1,0,0,0,258,256,1,0,
  	0,0,258,259,1,0,0,0,259,19,1,0,0,0,260,258,1,0,0,0,261,262,5,30,0,0,262,
  	21,1,0,0,0,263,267,5,30,0,0,264,266,5,33,0,0,265,264,1,0,0,0,266,269,
  	1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,273,1,0,0,0,269,267,1,0,0,
  	0,270,271,5,22,0,0,271,273,5,30,0,0,272,263,1,0,0,0,272,270,1,0,0,0,273,
  	23,1,0,0,0,274,275,5,20,0,0,275,276,5,30,0,0,276,277,5,57,0,0,277,278,
  	3,28,14,0,278,279,5,58,0,0,279,25,1,0,0,0,280,281,5,21,0,0,281,282,5,
  	30,0,0,282,283,5,57,0,0,283,284,3,28,14,0,284,285,5,58,0,0,285,27,1,0,
  	0,0,286,287,3,12,6,0,287,293,5,54,0,0,288,289,3,12,6,0,289,290,5,54,0,
  	0,290,292,1,0,0,0,291,288,1,0,0,0,292,295,1,0,0,0,293,291,1,0,0,0,293,
  	294,1,0,0,0,294,29,1,0,0,0,295,293,1,0,0,0,296,298,5,22,0,0,297,299,5,
  	30,0,0,298,297,1,0,0,0,298,299,1,0,0,0,299,300,1,0,0,0,300,301,5,57,0,
  	0,301,302,3,32,16,0,302,303,5,58,0,0,303,304,5,54,0,0,304,31,1,0,0,0,
  	305,310,3,34,17,0,306,307,5,53,0,0,307,309,3,34,17,0,308,306,1,0,0,0,
  	309,312,1,0,0,0,310,308,1,0,0,0,310,311,1,0,0,0,311,33,1,0,0,0,312,310,
  	1,0,0,0,313,316,3,20,10,0,314,315,5,62,0,0,315,317,3,38,19,0,316,314,
  	1,0,0,0,316,317,1,0,0,0,317,35,1,0,0,0,318,323,3,38,19,0,319,320,5,53,
  	0,0,320,322,3,38,19,0,321,319,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,
  	323,324,1,0,0,0,324,37,1,0,0,0,325,323,1,0,0,0,326,327,5,55,0,0,327,328,
  	3,22,11,0,328,329,5,56,0,0,329,330,3,38,19,0,330,376,1,0,0,0,331,332,
  	3,40,20,0,332,333,5,51,0,0,333,334,3,38,19,0,334,335,5,52,0,0,335,336,
  	3,38,19,0,336,376,1,0,0,0,337,338,3,62,31,0,338,339,5,61,0,0,339,340,
  	3,20,10,0,340,341,5,62,0,0,341,342,3,38,19,0,342,376,1,0,0,0,343,344,
  	3,20,10,0,344,345,5,59,0,0,345,346,3,38,19,0,346,347,5,60,0,0,347,348,
  	5,62,0,0,348,349,3,38,19,0,349,376,1,0,0,0,350,351,3,20,10,0,351,352,
  	5,62,0,0,352,353,3,38,19,0,353,376,1,0,0,0,354,355,3,20,10,0,355,356,
  	5,63,0,0,356,357,3,38,19,0,357,376,1,0,0,0,358,359,3,20,10,0,359,360,
  	5,64,0,0,360,361,3,38,19,0,361,376,1,0,0,0,362,363,3,20,10,0,363,364,
  	5,65,0,0,364,365,3,38,19,0,365,376,1,0,0,0,366,367,3,20,10,0,367,368,
  	5,66,0,0,368,369,3,38,19,0,369,376,1,0,0,0,370,371,3,20,10,0,371,372,
  	5,67,0,0,372,373,3,38,19,0,373,376,1,0,0,0,374,376,3,40,20,0,375,326,
  	1,0,0,0,375,331,1,0,0,0,375,337,1,0,0,0,375,343,1,0,0,0,375,350,1,0,0,
  	0,375,354,1,0,0,0,375,358,1,0,0,0,375,362,1,0,0,0,375,366,1,0,0,0,375,
  	370,1,0,0,0,375,374,1,0,0,0,376,39,1,0,0,0,377,378,6,20,-1,0,378,379,
  	3,42,21,0,379,385,1,0,0,0,380,381,10,1,0,0,381,382,5,43,0,0,382,384,3,
  	42,21,0,383,380,1,0,0,0,384,387,1,0,0,0,385,383,1,0,0,0,385,386,1,0,0,
  	0,386,41,1,0,0,0,387,385,1,0,0,0,388,389,6,21,-1,0,389,390,3,44,22,0,
  	390,396,1,0,0,0,391,392,10,1,0,0,392,393,5,42,0,0,393,395,3,44,22,0,394,
  	391,1,0,0,0,395,398,1,0,0,0,396,394,1,0,0,0,396,397,1,0,0,0,397,43,1,
  	0,0,0,398,396,1,0,0,0,399,400,6,22,-1,0,400,401,3,46,23,0,401,407,1,0,
  	0,0,402,403,10,1,0,0,403,404,5,46,0,0,404,406,3,46,23,0,405,402,1,0,0,
  	0,406,409,1,0,0,0,407,405,1,0,0,0,407,408,1,0,0,0,408,45,1,0,0,0,409,
  	407,1,0,0,0,410,411,6,23,-1,0,411,412,3,48,24,0,412,418,1,0,0,0,413,414,
  	10,1,0,0,414,415,5,47,0,0,415,417,3,48,24,0,416,413,1,0,0,0,417,420,1,
  	0,0,0,418,416,1,0,0,0,418,419,1,0,0,0,419,47,1,0,0,0,420,418,1,0,0,0,
  	421,422,6,24,-1,0,422,423,3,50,25,0,423,429,1,0,0,0,424,425,10,1,0,0,
  	425,426,5,45,0,0,426,428,3,50,25,0,427,424,1,0,0,0,428,431,1,0,0,0,429,
  	427,1,0,0,0,429,430,1,0,0,0,430,49,1,0,0,0,431,429,1,0,0,0,432,433,6,
  	25,-1,0,433,434,3,52,26,0,434,443,1,0,0,0,435,436,10,2,0,0,436,437,5,
  	36,0,0,437,442,3,52,26,0,438,439,10,1,0,0,439,440,5,37,0,0,440,442,3,
  	52,26,0,441,435,1,0,0,0,441,438,1,0,0,0,442,445,1,0,0,0,443,441,1,0,0,
  	0,443,444,1,0,0,0,444,51,1,0,0,0,445,443,1,0,0,0,446,447,6,26,-1,0,447,
  	448,3,54,27,0,448,463,1,0,0,0,449,450,10,4,0,0,450,451,5,38,0,0,451,462,
  	3,54,27,0,452,453,10,3,0,0,453,454,5,39,0,0,454,462,3,54,27,0,455,456,
  	10,2,0,0,456,457,5,40,0,0,457,462,3,54,27,0,458,459,10,1,0,0,459,460,
  	5,41,0,0,460,462,3,54,27,0,461,449,1,0,0,0,461,452,1,0,0,0,461,455,1,
  	0,0,0,461,458,1,0,0,0,462,465,1,0,0,0,463,461,1,0,0,0,463,464,1,0,0,0,
  	464,53,1,0,0,0,465,463,1,0,0,0,466,467,6,27,-1,0,467,468,3,56,28,0,468,
  	477,1,0,0,0,469,470,10,2,0,0,470,471,5,49,0,0,471,476,3,56,28,0,472,473,
  	10,1,0,0,473,474,5,50,0,0,474,476,3,56,28,0,475,469,1,0,0,0,475,472,1,
  	0,0,0,476,479,1,0,0,0,477,475,1,0,0,0,477,478,1,0,0,0,478,55,1,0,0,0,
  	479,477,1,0,0,0,480,481,6,28,-1,0,481,482,3,58,29,0,482,491,1,0,0,0,483,
  	484,10,2,0,0,484,485,5,31,0,0,485,490,3,58,29,0,486,487,10,1,0,0,487,
  	488,5,32,0,0,488,490,3,58,29,0,489,483,1,0,0,0,489,486,1,0,0,0,490,493,
  	1,0,0,0,491,489,1,0,0,0,491,492,1,0,0,0,492,57,1,0,0,0,493,491,1,0,0,
  	0,494,495,6,29,-1,0,495,496,3,60,30,0,496,508,1,0,0,0,497,498,10,3,0,
  	0,498,499,5,33,0,0,499,507,3,60,30,0,500,501,10,2,0,0,501,502,5,34,0,
  	0,502,507,3,60,30,0,503,504,10,1,0,0,504,505,5,35,0,0,505,507,3,60,30,
  	0,506,497,1,0,0,0,506,500,1,0,0,0,506,503,1,0,0,0,507,510,1,0,0,0,508,
  	506,1,0,0,0,508,509,1,0,0,0,509,59,1,0,0,0,510,508,1,0,0,0,511,533,3,
  	62,31,0,512,513,5,44,0,0,513,533,3,60,30,0,514,515,5,48,0,0,515,533,3,
  	60,30,0,516,517,5,45,0,0,517,533,3,60,30,0,518,519,5,33,0,0,519,533,3,
  	60,30,0,520,521,5,32,0,0,521,533,3,60,30,0,522,523,5,31,0,0,523,533,3,
  	60,30,0,524,525,5,25,0,0,525,533,3,38,19,0,526,527,3,20,10,0,527,528,
  	5,68,0,0,528,533,1,0,0,0,529,530,3,20,10,0,530,531,5,69,0,0,531,533,1,
  	0,0,0,532,511,1,0,0,0,532,512,1,0,0,0,532,514,1,0,0,0,532,516,1,0,0,0,
  	532,518,1,0,0,0,532,520,1,0,0,0,532,522,1,0,0,0,532,524,1,0,0,0,532,526,
  	1,0,0,0,532,529,1,0,0,0,533,61,1,0,0,0,534,535,3,20,10,0,535,537,5,55,
  	0,0,536,538,3,64,32,0,537,536,1,0,0,0,537,538,1,0,0,0,538,539,1,0,0,0,
  	539,540,5,56,0,0,540,567,1,0,0,0,541,542,3,20,10,0,542,543,5,59,0,0,543,
  	544,3,38,19,0,544,545,5,60,0,0,545,567,1,0,0,0,546,547,3,20,10,0,547,
  	548,5,61,0,0,548,549,3,20,10,0,549,567,1,0,0,0,550,551,3,20,10,0,551,
  	552,5,6,0,0,552,553,3,20,10,0,553,567,1,0,0,0,554,555,3,20,10,0,555,556,
  	5,68,0,0,556,567,1,0,0,0,557,558,3,20,10,0,558,559,5,69,0,0,559,567,1,
  	0,0,0,560,567,3,20,10,0,561,567,3,66,33,0,562,563,5,55,0,0,563,564,3,
  	38,19,0,564,565,5,56,0,0,565,567,1,0,0,0,566,534,1,0,0,0,566,541,1,0,
  	0,0,566,546,1,0,0,0,566,550,1,0,0,0,566,554,1,0,0,0,566,557,1,0,0,0,566,
  	560,1,0,0,0,566,561,1,0,0,0,566,562,1,0,0,0,567,63,1,0,0,0,568,573,3,
  	38,19,0,569,570,5,53,0,0,570,572,3,38,19,0,571,569,1,0,0,0,572,575,1,
  	0,0,0,573,571,1,0,0,0,573,574,1,0,0,0,574,65,1,0,0,0,575,573,1,0,0,0,
  	576,577,7,0,0,0,577,67,1,0,0,0,578,579,5,10,0,0,579,580,5,55,0,0,580,
  	581,3,38,19,0,581,582,5,56,0,0,582,585,3,10,5,0,583,584,5,11,0,0,584,
  	586,3,10,5,0,585,583,1,0,0,0,585,586,1,0,0,0,586,69,1,0,0,0,587,588,5,
  	12,0,0,588,589,5,55,0,0,589,590,3,38,19,0,590,591,5,56,0,0,591,592,3,
  	10,5,0,592,71,1,0,0,0,593,594,5,13,0,0,594,596,5,55,0,0,595,597,3,74,
  	37,0,596,595,1,0,0,0,596,597,1,0,0,0,597,598,1,0,0,0,598,600,5,54,0,0,
  	599,601,3,76,38,0,600,599,1,0,0,0,600,601,1,0,0,0,601,602,1,0,0,0,602,
  	604,5,54,0,0,603,605,3,78,39,0,604,603,1,0,0,0,604,605,1,0,0,0,605,606,
  	1,0,0,0,606,607,5,56,0,0,607,608,3,10,5,0,608,73,1,0,0,0,609,612,3,12,
  	6,0,610,612,3,38,19,0,611,609,1,0,0,0,611,610,1,0,0,0,612,75,1,0,0,0,
  	613,614,3,38,19,0,614,77,1,0,0,0,615,616,3,38,19,0,616,79,1,0,0,0,617,
  	618,5,14,0,0,618,619,3,10,5,0,619,620,5,12,0,0,620,621,5,55,0,0,621,622,
  	3,38,19,0,622,623,5,56,0,0,623,81,1,0,0,0,624,625,5,7,0,0,625,627,3,10,
  	5,0,626,628,3,84,42,0,627,626,1,0,0,0,628,629,1,0,0,0,629,627,1,0,0,0,
  	629,630,1,0,0,0,630,83,1,0,0,0,631,632,5,8,0,0,632,633,5,55,0,0,633,634,
  	3,22,11,0,634,635,3,20,10,0,635,636,5,56,0,0,636,637,3,10,5,0,637,644,
  	1,0,0,0,638,639,5,8,0,0,639,640,5,55,0,0,640,641,5,70,0,0,641,642,5,56,
  	0,0,642,644,3,10,5,0,643,631,1,0,0,0,643,638,1,0,0,0,644,85,1,0,0,0,645,
  	646,5,15,0,0,646,647,5,55,0,0,647,648,3,38,19,0,648,649,5,56,0,0,649,
  	650,5,57,0,0,650,651,3,88,44,0,651,652,5,58,0,0,652,87,1,0,0,0,653,655,
  	3,90,45,0,654,653,1,0,0,0,655,658,1,0,0,0,656,654,1,0,0,0,656,657,1,0,
  	0,0,657,89,1,0,0,0,658,656,1,0,0,0,659,660,5,16,0,0,660,661,3,38,19,0,
  	661,665,5,52,0,0,662,664,3,2,1,0,663,662,1,0,0,0,664,667,1,0,0,0,665,
  	663,1,0,0,0,665,666,1,0,0,0,666,677,1,0,0,0,667,665,1,0,0,0,668,669,5,
  	17,0,0,669,673,5,52,0,0,670,672,3,2,1,0,671,670,1,0,0,0,672,675,1,0,0,
  	0,673,671,1,0,0,0,673,674,1,0,0,0,674,677,1,0,0,0,675,673,1,0,0,0,676,
  	659,1,0,0,0,676,668,1,0,0,0,677,91,1,0,0,0,55,95,140,146,156,164,176,
  	185,191,197,209,216,223,230,232,238,248,258,267,272,293,298,310,316,323,
  	375,385,396,407,418,429,441,443,461,463,475,477,489,491,506,508,532,537,
  	566,573,585,596,600,604,611,629,643,656,665,673,676
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
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36363065733478066) != 0)) {
      setState(92);
      stmt();
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
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


size_t CScriptParser::StmtContext::getRuleIndex() const {
  return CScriptParser::RuleStmt;
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
    setState(140);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(100);
      var_decl();
      setState(101);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(103);
      enum_decl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(104);
      func_decl();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(105);
      extern_decl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(106);
      struct_decl();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(107);
      struct_decl();
      setState(108);
      match(CScriptParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(110);
      union_decl();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(111);
      union_decl();
      setState(112);
      match(CScriptParser::SEMI);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(114);
      expr();
      setState(115);
      match(CScriptParser::SEMI);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(117);
      match(CScriptParser::MUL);
      setState(118);
      ident();
      setState(119);
      match(CScriptParser::ASSIGN);
      setState(120);
      expr();
      setState(121);
      match(CScriptParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(123);
      match(CScriptParser::RETURN);
      setState(124);
      expr();
      setState(125);
      match(CScriptParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(127);
      if_stmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(128);
      while_stmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(129);
      for_stmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(130);
      do_while_stmt();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(131);
      switch_stmt();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(132);
      try_catch_stmt();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(133);
      match(CScriptParser::CONTINUE);
      setState(134);
      match(CScriptParser::SEMI);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(135);
      match(CScriptParser::BREAK);
      setState(136);
      match(CScriptParser::SEMI);
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(137);
      register_callback_stmt();
      break;
    }

    case 21: {
      enterOuterAlt(_localctx, 21);
      setState(138);
      import_stmt();
      break;
    }

    case 22: {
      enterOuterAlt(_localctx, 22);
      setState(139);
      include_stmt();
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
    setState(164);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(142);
      match(CScriptParser::T__0);
      setState(143);
      match(CScriptParser::STRING);
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::T__1) {
        setState(144);
        match(CScriptParser::T__1);
        setState(145);
        ident();
      }
      setState(148);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(149);
      match(CScriptParser::T__0);
      setState(150);
      match(CScriptParser::LBRACE);
      setState(151);
      ident();
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CScriptParser::COMMA) {
        setState(152);
        match(CScriptParser::COMMA);
        setState(153);
        ident();
        setState(158);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(159);
      match(CScriptParser::RBRACE);
      setState(160);
      match(CScriptParser::T__2);
      setState(161);
      match(CScriptParser::STRING);
      setState(162);
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

tree::TerminalNode* CScriptParser::Include_stmtContext::STRING() {
  return getToken(CScriptParser::STRING, 0);
}

tree::TerminalNode* CScriptParser::Include_stmtContext::SEMI() {
  return getToken(CScriptParser::SEMI, 0);
}


size_t CScriptParser::Include_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleInclude_stmt;
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(CScriptParser::T__3);
    setState(167);
    match(CScriptParser::STRING);
    setState(168);
    match(CScriptParser::SEMI);
   
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
    setState(170);
    match(CScriptParser::T__4);
    setState(171);
    ident();
    setState(172);
    match(CScriptParser::T__1);
    setState(173);
    ident();
    setState(174);
    match(CScriptParser::LPAREN);
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1087373312) != 0)) {
      setState(175);
      func_decl_args();
    }
    setState(178);
    match(CScriptParser::RPAREN);
    setState(179);
    match(CScriptParser::SEMI);
   
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


std::any CScriptParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::BlockContext* CScriptParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 10, CScriptParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(191);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(181);
      match(CScriptParser::LBRACE);
      setState(185);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 36363065733478066) != 0)) {
        setState(182);
        stmt();
        setState(187);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(188);
      match(CScriptParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(189);
      match(CScriptParser::LBRACE);
      setState(190);
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


std::any CScriptParser::Var_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitVar_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Var_declContext* CScriptParser::var_decl() {
  Var_declContext *_localctx = _tracker.createInstance<Var_declContext>(_ctx, getState());
  enterRule(_localctx, 12, CScriptParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(193);
      type();
      setState(194);
      ident();
      setState(197);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(195);
        match(CScriptParser::ASSIGN);
        setState(196);
        expr();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(199);
      type();
      setState(200);
      ident();
      setState(201);
      match(CScriptParser::LBRACKET);
      setState(202);
      expr();
      setState(203);
      match(CScriptParser::RBRACKET);
      setState(209);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(204);
        match(CScriptParser::ASSIGN);
        setState(205);
        match(CScriptParser::LBRACE);
        setState(206);
        init_list();
        setState(207);
        match(CScriptParser::RBRACE);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(211);
      type();
      setState(212);
      match(CScriptParser::MUL);
      setState(213);
      ident();
      setState(216);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(214);
        match(CScriptParser::ASSIGN);
        setState(215);
        expr();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(218);
      match(CScriptParser::CONST_KW);
      setState(219);
      type();
      setState(220);
      ident();
      setState(223);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(221);
        match(CScriptParser::ASSIGN);
        setState(222);
        expr();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(225);
      match(CScriptParser::STRUCT_KW);
      setState(226);
      ident();
      setState(227);
      ident();
      setState(230);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(228);
        match(CScriptParser::ASSIGN);
        setState(229);
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


std::any CScriptParser::Func_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFunc_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Func_declContext* CScriptParser::func_decl() {
  Func_declContext *_localctx = _tracker.createInstance<Func_declContext>(_ctx, getState());
  enterRule(_localctx, 14, CScriptParser::RuleFunc_decl);
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
    setState(234);
    type();
    setState(235);
    ident();
    setState(236);
    match(CScriptParser::LPAREN);
    setState(238);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1087373312) != 0)) {
      setState(237);
      func_decl_args();
    }
    setState(240);
    match(CScriptParser::RPAREN);
    setState(241);
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


std::any CScriptParser::Extern_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExtern_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Extern_declContext* CScriptParser::extern_decl() {
  Extern_declContext *_localctx = _tracker.createInstance<Extern_declContext>(_ctx, getState());
  enterRule(_localctx, 16, CScriptParser::RuleExtern_decl);
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
    setState(243);
    match(CScriptParser::EXTERN_KW);
    setState(244);
    type();
    setState(245);
    ident();
    setState(246);
    match(CScriptParser::LPAREN);
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1087373312) != 0)) {
      setState(247);
      func_decl_args();
    }
    setState(250);
    match(CScriptParser::RPAREN);
    setState(251);
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


std::any CScriptParser::Func_decl_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFunc_decl_args(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Func_decl_argsContext* CScriptParser::func_decl_args() {
  Func_decl_argsContext *_localctx = _tracker.createInstance<Func_decl_argsContext>(_ctx, getState());
  enterRule(_localctx, 18, CScriptParser::RuleFunc_decl_args);
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
    setState(253);
    var_decl();
    setState(258);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(254);
      match(CScriptParser::COMMA);
      setState(255);
      var_decl();
      setState(260);
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


std::any CScriptParser::IdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitIdent(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::IdentContext* CScriptParser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 20, CScriptParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
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


std::any CScriptParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::TypeContext* CScriptParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 22, CScriptParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(272);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(263);
        match(CScriptParser::IDENTIFIER);
        setState(267);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(264);
            match(CScriptParser::MUL); 
          }
          setState(269);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
        }
        break;
      }

      case CScriptParser::ENUM_KW: {
        enterOuterAlt(_localctx, 2);
        setState(270);
        match(CScriptParser::ENUM_KW);
        setState(271);
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


std::any CScriptParser::Struct_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitStruct_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Struct_declContext* CScriptParser::struct_decl() {
  Struct_declContext *_localctx = _tracker.createInstance<Struct_declContext>(_ctx, getState());
  enterRule(_localctx, 24, CScriptParser::RuleStruct_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274);
    match(CScriptParser::STRUCT_KW);
    setState(275);
    match(CScriptParser::IDENTIFIER);
    setState(276);
    match(CScriptParser::LBRACE);
    setState(277);
    struct_members();
    setState(278);
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


std::any CScriptParser::Union_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitUnion_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Union_declContext* CScriptParser::union_decl() {
  Union_declContext *_localctx = _tracker.createInstance<Union_declContext>(_ctx, getState());
  enterRule(_localctx, 26, CScriptParser::RuleUnion_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    match(CScriptParser::UNION_KW);
    setState(281);
    match(CScriptParser::IDENTIFIER);
    setState(282);
    match(CScriptParser::LBRACE);
    setState(283);
    struct_members();
    setState(284);
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


std::any CScriptParser::Struct_membersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitStruct_members(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Struct_membersContext* CScriptParser::struct_members() {
  Struct_membersContext *_localctx = _tracker.createInstance<Struct_membersContext>(_ctx, getState());
  enterRule(_localctx, 28, CScriptParser::RuleStruct_members);
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
    var_decl();
    setState(287);
    match(CScriptParser::SEMI);
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1087373312) != 0)) {
      setState(288);
      var_decl();
      setState(289);
      match(CScriptParser::SEMI);
      setState(295);
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


std::any CScriptParser::Enum_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_decl(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_declContext* CScriptParser::enum_decl() {
  Enum_declContext *_localctx = _tracker.createInstance<Enum_declContext>(_ctx, getState());
  enterRule(_localctx, 30, CScriptParser::RuleEnum_decl);
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
    setState(296);
    match(CScriptParser::ENUM_KW);
    setState(298);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::IDENTIFIER) {
      setState(297);
      match(CScriptParser::IDENTIFIER);
    }
    setState(300);
    match(CScriptParser::LBRACE);
    setState(301);
    enum_list();
    setState(302);
    match(CScriptParser::RBRACE);
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


std::any CScriptParser::Enum_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_listContext* CScriptParser::enum_list() {
  Enum_listContext *_localctx = _tracker.createInstance<Enum_listContext>(_ctx, getState());
  enterRule(_localctx, 32, CScriptParser::RuleEnum_list);
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
    enum_item();
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(306);
      match(CScriptParser::COMMA);
      setState(307);
      enum_item();
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


std::any CScriptParser::Enum_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitEnum_item(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Enum_itemContext* CScriptParser::enum_item() {
  Enum_itemContext *_localctx = _tracker.createInstance<Enum_itemContext>(_ctx, getState());
  enterRule(_localctx, 34, CScriptParser::RuleEnum_item);
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
    setState(313);
    ident();
    setState(316);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ASSIGN) {
      setState(314);
      match(CScriptParser::ASSIGN);
      setState(315);
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


std::any CScriptParser::Init_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitInit_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Init_listContext* CScriptParser::init_list() {
  Init_listContext *_localctx = _tracker.createInstance<Init_listContext>(_ctx, getState());
  enterRule(_localctx, 36, CScriptParser::RuleInit_list);
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
    setState(318);
    expr();
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(319);
      match(CScriptParser::COMMA);
      setState(320);
      expr();
      setState(325);
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


std::any CScriptParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::ExprContext* CScriptParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 38, CScriptParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(375);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(326);
      match(CScriptParser::LPAREN);
      setState(327);
      type();
      setState(328);
      match(CScriptParser::RPAREN);
      setState(329);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(331);
      or_expr(0);
      setState(332);
      match(CScriptParser::QUESTION);
      setState(333);
      expr();
      setState(334);
      match(CScriptParser::COLON);
      setState(335);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(337);
      primary_expr();
      setState(338);
      match(CScriptParser::DOT);
      setState(339);
      ident();
      setState(340);
      match(CScriptParser::ASSIGN);
      setState(341);
      expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(343);
      ident();
      setState(344);
      match(CScriptParser::LBRACKET);
      setState(345);
      expr();
      setState(346);
      match(CScriptParser::RBRACKET);
      setState(347);
      match(CScriptParser::ASSIGN);
      setState(348);
      expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(350);
      ident();
      setState(351);
      match(CScriptParser::ASSIGN);
      setState(352);
      expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(354);
      ident();
      setState(355);
      match(CScriptParser::PLUS_EQ);
      setState(356);
      expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(358);
      ident();
      setState(359);
      match(CScriptParser::MINUS_EQ);
      setState(360);
      expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(362);
      ident();
      setState(363);
      match(CScriptParser::MUL_EQ);
      setState(364);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(366);
      ident();
      setState(367);
      match(CScriptParser::DIV_EQ);
      setState(368);
      expr();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(370);
      ident();
      setState(371);
      match(CScriptParser::MOD_EQ);
      setState(372);
      expr();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(374);
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
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, CScriptParser::RuleOr_expr, precedence);

    

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
    setState(378);
    and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(385);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleOr_expr);
        setState(380);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(381);
        match(CScriptParser::OR);
        setState(382);
        and_expr(0); 
      }
      setState(387);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, CScriptParser::RuleAnd_expr, precedence);

    

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
    setState(389);
    bit_or_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(396);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<And_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAnd_expr);
        setState(391);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(392);
        match(CScriptParser::AND);
        setState(393);
        bit_or_expr(0); 
      }
      setState(398);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, CScriptParser::RuleBit_or_expr, precedence);

    

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
    setState(400);
    bit_xor_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(407);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_or_expr);
        setState(402);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(403);
        match(CScriptParser::BITOR);
        setState(404);
        bit_xor_expr(0); 
      }
      setState(409);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CScriptParser::RuleBit_xor_expr, precedence);

    

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
    setState(411);
    bit_and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(418);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_xor_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_xor_expr);
        setState(413);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(414);
        match(CScriptParser::XOR);
        setState(415);
        bit_and_expr(0); 
      }
      setState(420);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CScriptParser::RuleBit_and_expr, precedence);

    

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
    setState(422);
    eq_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(429);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_and_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_and_expr);
        setState(424);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(425);
        match(CScriptParser::BITAND);
        setState(426);
        eq_expr(0); 
      }
      setState(431);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CScriptParser::RuleEq_expr, precedence);

    

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
    setState(433);
    rel_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(443);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(441);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(435);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(436);
          match(CScriptParser::EQ);
          setState(437);
          rel_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(438);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(439);
          match(CScriptParser::NEQ);
          setState(440);
          rel_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(445);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CScriptParser::RuleRel_expr, precedence);

    

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
    setState(447);
    shift_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(463);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(461);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(449);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(450);
          match(CScriptParser::LT);
          setState(451);
          shift_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(452);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(453);
          match(CScriptParser::LTE);
          setState(454);
          shift_expr(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(455);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(456);
          match(CScriptParser::GT);
          setState(457);
          shift_expr(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(458);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(459);
          match(CScriptParser::GTE);
          setState(460);
          shift_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(465);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CScriptParser::RuleShift_expr, precedence);

    

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
    setState(467);
    add_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(477);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(475);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(469);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(470);
          match(CScriptParser::LSHIFT);
          setState(471);
          add_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(472);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(473);
          match(CScriptParser::RSHIFT);
          setState(474);
          add_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(479);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CScriptParser::RuleAdd_expr, precedence);

    

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
    setState(481);
    mul_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(491);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(489);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(483);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(484);
          match(CScriptParser::PLUS);
          setState(485);
          mul_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(486);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(487);
          match(CScriptParser::MINUS);
          setState(488);
          mul_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(493);
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
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, CScriptParser::RuleMul_expr, precedence);

    

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
    setState(495);
    unary_expr();
    _ctx->stop = _input->LT(-1);
    setState(508);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(506);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(497);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(498);
          match(CScriptParser::MUL);
          setState(499);
          unary_expr();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(500);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(501);
          match(CScriptParser::DIV);
          setState(502);
          unary_expr();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(503);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(504);
          match(CScriptParser::MOD);
          setState(505);
          unary_expr();
          break;
        }

        default:
          break;
        } 
      }
      setState(510);
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


std::any CScriptParser::Unary_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitUnary_expr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Unary_exprContext* CScriptParser::unary_expr() {
  Unary_exprContext *_localctx = _tracker.createInstance<Unary_exprContext>(_ctx, getState());
  enterRule(_localctx, 60, CScriptParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(532);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(511);
      primary_expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(512);
      match(CScriptParser::NOT);
      setState(513);
      unary_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(514);
      match(CScriptParser::NOTBIT);
      setState(515);
      unary_expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(516);
      match(CScriptParser::BITAND);
      setState(517);
      unary_expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(518);
      match(CScriptParser::MUL);
      setState(519);
      unary_expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(520);
      match(CScriptParser::MINUS);
      setState(521);
      unary_expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(522);
      match(CScriptParser::PLUS);
      setState(523);
      unary_expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(524);
      match(CScriptParser::THROW);
      setState(525);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(526);
      ident();
      setState(527);
      match(CScriptParser::INC);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(529);
      ident();
      setState(530);
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


std::any CScriptParser::Primary_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitPrimary_expr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Primary_exprContext* CScriptParser::primary_expr() {
  Primary_exprContext *_localctx = _tracker.createInstance<Primary_exprContext>(_ctx, getState());
  enterRule(_localctx, 62, CScriptParser::RulePrimary_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(566);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(534);
      ident();
      setState(535);
      match(CScriptParser::LPAREN);
      setState(537);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 36363065700122624) != 0)) {
        setState(536);
        call_args();
      }
      setState(539);
      match(CScriptParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(541);
      ident();
      setState(542);
      match(CScriptParser::LBRACKET);
      setState(543);
      expr();
      setState(544);
      match(CScriptParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(546);
      ident();
      setState(547);
      match(CScriptParser::DOT);
      setState(548);
      ident();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(550);
      ident();
      setState(551);
      match(CScriptParser::T__5);
      setState(552);
      ident();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(554);
      ident();
      setState(555);
      match(CScriptParser::INC);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(557);
      ident();
      setState(558);
      match(CScriptParser::DEC);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(560);
      ident();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(561);
      numeric();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(562);
      match(CScriptParser::LPAREN);
      setState(563);
      expr();
      setState(564);
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


std::any CScriptParser::Call_argsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCall_args(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Call_argsContext* CScriptParser::call_args() {
  Call_argsContext *_localctx = _tracker.createInstance<Call_argsContext>(_ctx, getState());
  enterRule(_localctx, 64, CScriptParser::RuleCall_args);
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
    setState(568);
    expr();
    setState(573);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(569);
      match(CScriptParser::COMMA);
      setState(570);
      expr();
      setState(575);
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


std::any CScriptParser::NumericContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitNumeric(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::NumericContext* CScriptParser::numeric() {
  NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, getState());
  enterRule(_localctx, 66, CScriptParser::RuleNumeric);
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
    setState(576);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1006632960) != 0))) {
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

std::vector<CScriptParser::BlockContext *> CScriptParser::If_stmtContext::block() {
  return getRuleContexts<CScriptParser::BlockContext>();
}

CScriptParser::BlockContext* CScriptParser::If_stmtContext::block(size_t i) {
  return getRuleContext<CScriptParser::BlockContext>(i);
}

tree::TerminalNode* CScriptParser::If_stmtContext::ELSE() {
  return getToken(CScriptParser::ELSE, 0);
}


size_t CScriptParser::If_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleIf_stmt;
}


std::any CScriptParser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::If_stmtContext* CScriptParser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 68, CScriptParser::RuleIf_stmt);
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
    setState(578);
    match(CScriptParser::IF);
    setState(579);
    match(CScriptParser::LPAREN);
    setState(580);
    expr();
    setState(581);
    match(CScriptParser::RPAREN);
    setState(582);
    block();
    setState(585);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ELSE) {
      setState(583);
      match(CScriptParser::ELSE);
      setState(584);
      block();
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

CScriptParser::BlockContext* CScriptParser::While_stmtContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
}


size_t CScriptParser::While_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleWhile_stmt;
}


std::any CScriptParser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::While_stmtContext* CScriptParser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 70, CScriptParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587);
    match(CScriptParser::WHILE);
    setState(588);
    match(CScriptParser::LPAREN);
    setState(589);
    expr();
    setState(590);
    match(CScriptParser::RPAREN);
    setState(591);
    block();
   
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

CScriptParser::BlockContext* CScriptParser::For_stmtContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
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


std::any CScriptParser::For_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_stmtContext* CScriptParser::for_stmt() {
  For_stmtContext *_localctx = _tracker.createInstance<For_stmtContext>(_ctx, getState());
  enterRule(_localctx, 72, CScriptParser::RuleFor_stmt);
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
    setState(593);
    match(CScriptParser::FOR);
    setState(594);
    match(CScriptParser::LPAREN);
    setState(596);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36363065713754112) != 0)) {
      setState(595);
      for_init();
    }
    setState(598);
    match(CScriptParser::SEMI);
    setState(600);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36363065700122624) != 0)) {
      setState(599);
      for_cond();
    }
    setState(602);
    match(CScriptParser::SEMI);
    setState(604);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36363065700122624) != 0)) {
      setState(603);
      for_incr();
    }
    setState(606);
    match(CScriptParser::RPAREN);
    setState(607);
    block();
   
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


std::any CScriptParser::For_initContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_init(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_initContext* CScriptParser::for_init() {
  For_initContext *_localctx = _tracker.createInstance<For_initContext>(_ctx, getState());
  enterRule(_localctx, 74, CScriptParser::RuleFor_init);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(611);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(609);
      var_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(610);
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


std::any CScriptParser::For_condContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_cond(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_condContext* CScriptParser::for_cond() {
  For_condContext *_localctx = _tracker.createInstance<For_condContext>(_ctx, getState());
  enterRule(_localctx, 76, CScriptParser::RuleFor_cond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(613);
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


std::any CScriptParser::For_incrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitFor_incr(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::For_incrContext* CScriptParser::for_incr() {
  For_incrContext *_localctx = _tracker.createInstance<For_incrContext>(_ctx, getState());
  enterRule(_localctx, 78, CScriptParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(615);
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

CScriptParser::BlockContext* CScriptParser::Do_while_stmtContext::block() {
  return getRuleContext<CScriptParser::BlockContext>(0);
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


size_t CScriptParser::Do_while_stmtContext::getRuleIndex() const {
  return CScriptParser::RuleDo_while_stmt;
}


std::any CScriptParser::Do_while_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitDo_while_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Do_while_stmtContext* CScriptParser::do_while_stmt() {
  Do_while_stmtContext *_localctx = _tracker.createInstance<Do_while_stmtContext>(_ctx, getState());
  enterRule(_localctx, 80, CScriptParser::RuleDo_while_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(617);
    match(CScriptParser::DO);
    setState(618);
    block();
    setState(619);
    match(CScriptParser::WHILE);
    setState(620);
    match(CScriptParser::LPAREN);
    setState(621);
    expr();
    setState(622);
    match(CScriptParser::RPAREN);
   
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


std::any CScriptParser::Try_catch_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitTry_catch_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Try_catch_stmtContext* CScriptParser::try_catch_stmt() {
  Try_catch_stmtContext *_localctx = _tracker.createInstance<Try_catch_stmtContext>(_ctx, getState());
  enterRule(_localctx, 82, CScriptParser::RuleTry_catch_stmt);
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
    setState(624);
    match(CScriptParser::T__6);
    setState(625);
    block();
    setState(627); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(626);
      catch_block();
      setState(629); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CScriptParser::T__7);
   
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


std::any CScriptParser::Catch_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCatch_block(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Catch_blockContext* CScriptParser::catch_block() {
  Catch_blockContext *_localctx = _tracker.createInstance<Catch_blockContext>(_ctx, getState());
  enterRule(_localctx, 84, CScriptParser::RuleCatch_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(643);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(631);
      match(CScriptParser::T__7);
      setState(632);
      match(CScriptParser::LPAREN);
      setState(633);
      type();
      setState(634);
      ident();
      setState(635);
      match(CScriptParser::RPAREN);
      setState(636);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(638);
      match(CScriptParser::T__7);
      setState(639);
      match(CScriptParser::LPAREN);
      setState(640);
      match(CScriptParser::ELLIPSIS);
      setState(641);
      match(CScriptParser::RPAREN);
      setState(642);
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


std::any CScriptParser::Switch_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitSwitch_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Switch_stmtContext* CScriptParser::switch_stmt() {
  Switch_stmtContext *_localctx = _tracker.createInstance<Switch_stmtContext>(_ctx, getState());
  enterRule(_localctx, 86, CScriptParser::RuleSwitch_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(645);
    match(CScriptParser::SWITCH);
    setState(646);
    match(CScriptParser::LPAREN);
    setState(647);
    expr();
    setState(648);
    match(CScriptParser::RPAREN);
    setState(649);
    match(CScriptParser::LBRACE);
    setState(650);
    case_list();
    setState(651);
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


std::any CScriptParser::Case_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCase_list(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Case_listContext* CScriptParser::case_list() {
  Case_listContext *_localctx = _tracker.createInstance<Case_listContext>(_ctx, getState());
  enterRule(_localctx, 88, CScriptParser::RuleCase_list);
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
    setState(656);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::CASE

    || _la == CScriptParser::DEFAULT) {
      setState(653);
      case_stmt();
      setState(658);
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


std::any CScriptParser::Case_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCase_stmt(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Case_stmtContext* CScriptParser::case_stmt() {
  Case_stmtContext *_localctx = _tracker.createInstance<Case_stmtContext>(_ctx, getState());
  enterRule(_localctx, 90, CScriptParser::RuleCase_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(676);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::CASE: {
        enterOuterAlt(_localctx, 1);
        setState(659);
        match(CScriptParser::CASE);
        setState(660);
        expr();
        setState(661);
        match(CScriptParser::COLON);
        setState(665);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 36363065733478066) != 0)) {
          setState(662);
          stmt();
          setState(667);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CScriptParser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(668);
        match(CScriptParser::DEFAULT);
        setState(669);
        match(CScriptParser::COLON);
        setState(673);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 36363065733478066) != 0)) {
          setState(670);
          stmt();
          setState(675);
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
    case 20: return or_exprSempred(antlrcpp::downCast<Or_exprContext *>(context), predicateIndex);
    case 21: return and_exprSempred(antlrcpp::downCast<And_exprContext *>(context), predicateIndex);
    case 22: return bit_or_exprSempred(antlrcpp::downCast<Bit_or_exprContext *>(context), predicateIndex);
    case 23: return bit_xor_exprSempred(antlrcpp::downCast<Bit_xor_exprContext *>(context), predicateIndex);
    case 24: return bit_and_exprSempred(antlrcpp::downCast<Bit_and_exprContext *>(context), predicateIndex);
    case 25: return eq_exprSempred(antlrcpp::downCast<Eq_exprContext *>(context), predicateIndex);
    case 26: return rel_exprSempred(antlrcpp::downCast<Rel_exprContext *>(context), predicateIndex);
    case 27: return shift_exprSempred(antlrcpp::downCast<Shift_exprContext *>(context), predicateIndex);
    case 28: return add_exprSempred(antlrcpp::downCast<Add_exprContext *>(context), predicateIndex);
    case 29: return mul_exprSempred(antlrcpp::downCast<Mul_exprContext *>(context), predicateIndex);

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
