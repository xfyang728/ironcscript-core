
// Generated from src/frontend/parser/CScript.g4 by ANTLR 4.13.2


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
      "export_stmt", "block", "var_decl", "func_decl", "extern_decl", "func_decl_args", 
      "ident", "type", "struct_decl", "union_decl", "struct_members", "enum_decl", 
      "enum_list", "enum_item", "init_list", "expr", "or_expr", "and_expr", 
      "bit_or_expr", "bit_xor_expr", "bit_and_expr", "eq_expr", "rel_expr", 
      "shift_expr", "add_expr", "mul_expr", "unary_expr", "primary_expr", 
      "call_args", "numeric", "if_stmt", "while_stmt", "for_stmt", "for_init", 
      "for_cond", "for_incr", "do_while_stmt", "try_catch_stmt", "catch_block", 
      "switch_stmt", "case_list", "case_stmt"
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
  	4,1,76,706,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,1,0,5,0,96,8,0,10,0,12,0,99,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,144,8,1,1,2,1,2,1,2,1,2,3,2,150,
  	8,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,158,8,2,10,2,12,2,161,9,2,1,2,1,2,1,2,
  	1,2,1,2,3,2,168,8,2,1,3,3,3,171,8,3,1,3,1,3,1,3,3,3,176,8,3,1,4,1,4,1,
  	4,1,4,1,4,1,4,3,4,184,8,4,1,4,1,4,1,4,1,5,1,5,1,5,3,5,192,8,5,1,5,1,5,
  	1,5,1,5,3,5,198,8,5,1,6,1,6,5,6,202,8,6,10,6,12,6,205,9,6,1,6,1,6,1,6,
  	3,6,210,8,6,1,7,1,7,1,7,1,7,3,7,216,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,3,7,228,8,7,1,7,1,7,1,7,1,7,1,7,3,7,235,8,7,1,7,1,7,1,7,1,7,
  	1,7,3,7,242,8,7,1,7,1,7,1,7,1,7,1,7,3,7,249,8,7,3,7,251,8,7,1,8,1,8,1,
  	8,1,8,3,8,257,8,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,3,9,267,8,9,1,9,1,9,
  	1,9,1,10,1,10,1,10,5,10,275,8,10,10,10,12,10,278,9,10,1,11,1,11,1,12,
  	1,12,5,12,284,8,12,10,12,12,12,287,9,12,1,12,1,12,3,12,291,8,12,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,
  	1,15,1,15,5,15,310,8,15,10,15,12,15,313,9,15,1,16,1,16,3,16,317,8,16,
  	1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,5,17,327,8,17,10,17,12,17,330,
  	9,17,1,18,1,18,1,18,3,18,335,8,18,1,19,1,19,1,19,5,19,340,8,19,10,19,
  	12,19,343,9,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,394,8,20,1,21,
  	1,21,1,21,1,21,1,21,1,21,5,21,402,8,21,10,21,12,21,405,9,21,1,22,1,22,
  	1,22,1,22,1,22,1,22,5,22,413,8,22,10,22,12,22,416,9,22,1,23,1,23,1,23,
  	1,23,1,23,1,23,5,23,424,8,23,10,23,12,23,427,9,23,1,24,1,24,1,24,1,24,
  	1,24,1,24,5,24,435,8,24,10,24,12,24,438,9,24,1,25,1,25,1,25,1,25,1,25,
  	1,25,5,25,446,8,25,10,25,12,25,449,9,25,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,5,26,460,8,26,10,26,12,26,463,9,26,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,5,27,480,8,27,
  	10,27,12,27,483,9,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,5,28,
  	494,8,28,10,28,12,28,497,9,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,5,29,508,8,29,10,29,12,29,511,9,29,1,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,1,30,1,30,5,30,525,8,30,10,30,12,30,528,9,30,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,31,1,31,3,31,551,8,31,1,32,1,32,1,32,3,32,556,8,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,570,
  	8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,594,8,32,1,33,1,33,
  	1,33,5,33,599,8,33,10,33,12,33,602,9,33,1,34,1,34,1,35,1,35,1,35,1,35,
  	1,35,1,35,1,35,3,35,613,8,35,1,36,1,36,1,36,1,36,1,36,1,36,1,37,1,37,
  	1,37,3,37,624,8,37,1,37,1,37,3,37,628,8,37,1,37,1,37,3,37,632,8,37,1,
  	37,1,37,1,37,1,38,1,38,3,38,639,8,38,1,39,1,39,1,40,1,40,1,41,1,41,1,
  	41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,4,42,655,8,42,11,42,12,42,656,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,671,8,
  	43,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,45,5,45,682,8,45,10,45,12,
  	45,685,9,45,1,46,1,46,1,46,1,46,5,46,691,8,46,10,46,12,46,694,9,46,1,
  	46,1,46,1,46,5,46,699,8,46,10,46,12,46,702,9,46,3,46,704,8,46,1,46,0,
  	10,42,44,46,48,50,52,54,56,58,60,47,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,
  	72,74,76,78,80,82,84,86,88,90,92,0,2,1,0,30,31,1,0,27,30,771,0,97,1,0,
  	0,0,2,143,1,0,0,0,4,167,1,0,0,0,6,170,1,0,0,0,8,177,1,0,0,0,10,197,1,
  	0,0,0,12,209,1,0,0,0,14,250,1,0,0,0,16,252,1,0,0,0,18,261,1,0,0,0,20,
  	271,1,0,0,0,22,279,1,0,0,0,24,290,1,0,0,0,26,292,1,0,0,0,28,298,1,0,0,
  	0,30,304,1,0,0,0,32,314,1,0,0,0,34,323,1,0,0,0,36,331,1,0,0,0,38,336,
  	1,0,0,0,40,393,1,0,0,0,42,395,1,0,0,0,44,406,1,0,0,0,46,417,1,0,0,0,48,
  	428,1,0,0,0,50,439,1,0,0,0,52,450,1,0,0,0,54,464,1,0,0,0,56,484,1,0,0,
  	0,58,498,1,0,0,0,60,512,1,0,0,0,62,550,1,0,0,0,64,593,1,0,0,0,66,595,
  	1,0,0,0,68,603,1,0,0,0,70,605,1,0,0,0,72,614,1,0,0,0,74,620,1,0,0,0,76,
  	638,1,0,0,0,78,640,1,0,0,0,80,642,1,0,0,0,82,644,1,0,0,0,84,651,1,0,0,
  	0,86,670,1,0,0,0,88,672,1,0,0,0,90,683,1,0,0,0,92,703,1,0,0,0,94,96,3,
  	2,1,0,95,94,1,0,0,0,96,99,1,0,0,0,97,95,1,0,0,0,97,98,1,0,0,0,98,100,
  	1,0,0,0,99,97,1,0,0,0,100,101,5,0,0,1,101,1,1,0,0,0,102,103,3,14,7,0,
  	103,104,5,56,0,0,104,144,1,0,0,0,105,144,3,32,16,0,106,144,3,16,8,0,107,
  	144,3,18,9,0,108,144,3,26,13,0,109,110,3,26,13,0,110,111,5,56,0,0,111,
  	144,1,0,0,0,112,144,3,28,14,0,113,114,3,28,14,0,114,115,5,56,0,0,115,
  	144,1,0,0,0,116,117,3,40,20,0,117,118,5,56,0,0,118,144,1,0,0,0,119,120,
  	5,35,0,0,120,121,3,22,11,0,121,122,5,64,0,0,122,123,3,40,20,0,123,124,
  	5,56,0,0,124,144,1,0,0,0,125,126,5,7,0,0,126,127,3,40,20,0,127,128,5,
  	56,0,0,128,144,1,0,0,0,129,144,3,70,35,0,130,144,3,72,36,0,131,144,3,
  	74,37,0,132,144,3,82,41,0,133,144,3,88,44,0,134,144,3,84,42,0,135,136,
  	5,16,0,0,136,144,5,56,0,0,137,138,5,17,0,0,138,144,5,56,0,0,139,144,3,
  	8,4,0,140,144,3,4,2,0,141,144,3,6,3,0,142,144,3,10,5,0,143,102,1,0,0,
  	0,143,105,1,0,0,0,143,106,1,0,0,0,143,107,1,0,0,0,143,108,1,0,0,0,143,
  	109,1,0,0,0,143,112,1,0,0,0,143,113,1,0,0,0,143,116,1,0,0,0,143,119,1,
  	0,0,0,143,125,1,0,0,0,143,129,1,0,0,0,143,130,1,0,0,0,143,131,1,0,0,0,
  	143,132,1,0,0,0,143,133,1,0,0,0,143,134,1,0,0,0,143,135,1,0,0,0,143,137,
  	1,0,0,0,143,139,1,0,0,0,143,140,1,0,0,0,143,141,1,0,0,0,143,142,1,0,0,
  	0,144,3,1,0,0,0,145,146,5,25,0,0,146,149,5,30,0,0,147,148,5,1,0,0,148,
  	150,3,22,11,0,149,147,1,0,0,0,149,150,1,0,0,0,150,151,1,0,0,0,151,168,
  	5,56,0,0,152,153,5,25,0,0,153,154,5,59,0,0,154,159,3,22,11,0,155,156,
  	5,55,0,0,156,158,3,22,11,0,157,155,1,0,0,0,158,161,1,0,0,0,159,157,1,
  	0,0,0,159,160,1,0,0,0,160,162,1,0,0,0,161,159,1,0,0,0,162,163,5,60,0,
  	0,163,164,5,2,0,0,164,165,5,30,0,0,165,166,5,56,0,0,166,168,1,0,0,0,167,
  	145,1,0,0,0,167,152,1,0,0,0,168,5,1,0,0,0,169,171,5,73,0,0,170,169,1,
  	0,0,0,170,171,1,0,0,0,171,172,1,0,0,0,172,173,5,26,0,0,173,175,7,0,0,
  	0,174,176,5,56,0,0,175,174,1,0,0,0,175,176,1,0,0,0,176,7,1,0,0,0,177,
  	178,5,3,0,0,178,179,3,22,11,0,179,180,5,1,0,0,180,181,3,22,11,0,181,183,
  	5,57,0,0,182,184,3,20,10,0,183,182,1,0,0,0,183,184,1,0,0,0,184,185,1,
  	0,0,0,185,186,5,58,0,0,186,187,5,56,0,0,187,9,1,0,0,0,188,189,5,24,0,
  	0,189,191,3,14,7,0,190,192,5,56,0,0,191,190,1,0,0,0,191,192,1,0,0,0,192,
  	198,1,0,0,0,193,194,5,24,0,0,194,198,3,16,8,0,195,196,5,24,0,0,196,198,
  	3,32,16,0,197,188,1,0,0,0,197,193,1,0,0,0,197,195,1,0,0,0,198,11,1,0,
  	0,0,199,203,5,59,0,0,200,202,3,2,1,0,201,200,1,0,0,0,202,205,1,0,0,0,
  	203,201,1,0,0,0,203,204,1,0,0,0,204,206,1,0,0,0,205,203,1,0,0,0,206,210,
  	5,60,0,0,207,208,5,59,0,0,208,210,5,60,0,0,209,199,1,0,0,0,209,207,1,
  	0,0,0,210,13,1,0,0,0,211,212,3,24,12,0,212,215,3,22,11,0,213,214,5,64,
  	0,0,214,216,3,40,20,0,215,213,1,0,0,0,215,216,1,0,0,0,216,251,1,0,0,0,
  	217,218,3,24,12,0,218,219,3,22,11,0,219,220,5,61,0,0,220,221,3,40,20,
  	0,221,227,5,62,0,0,222,223,5,64,0,0,223,224,5,59,0,0,224,225,3,38,19,
  	0,225,226,5,60,0,0,226,228,1,0,0,0,227,222,1,0,0,0,227,228,1,0,0,0,228,
  	251,1,0,0,0,229,230,3,24,12,0,230,231,5,35,0,0,231,234,3,22,11,0,232,
  	233,5,64,0,0,233,235,3,40,20,0,234,232,1,0,0,0,234,235,1,0,0,0,235,251,
  	1,0,0,0,236,237,5,21,0,0,237,238,3,24,12,0,238,241,3,22,11,0,239,240,
  	5,64,0,0,240,242,3,40,20,0,241,239,1,0,0,0,241,242,1,0,0,0,242,251,1,
  	0,0,0,243,244,5,18,0,0,244,245,3,22,11,0,245,248,3,22,11,0,246,247,5,
  	64,0,0,247,249,3,40,20,0,248,246,1,0,0,0,248,249,1,0,0,0,249,251,1,0,
  	0,0,250,211,1,0,0,0,250,217,1,0,0,0,250,229,1,0,0,0,250,236,1,0,0,0,250,
  	243,1,0,0,0,251,15,1,0,0,0,252,253,3,24,12,0,253,254,3,22,11,0,254,256,
  	5,57,0,0,255,257,3,20,10,0,256,255,1,0,0,0,256,257,1,0,0,0,257,258,1,
  	0,0,0,258,259,5,58,0,0,259,260,3,12,6,0,260,17,1,0,0,0,261,262,5,22,0,
  	0,262,263,3,24,12,0,263,264,3,22,11,0,264,266,5,57,0,0,265,267,3,20,10,
  	0,266,265,1,0,0,0,266,267,1,0,0,0,267,268,1,0,0,0,268,269,5,58,0,0,269,
  	270,5,56,0,0,270,19,1,0,0,0,271,276,3,14,7,0,272,273,5,55,0,0,273,275,
  	3,14,7,0,274,272,1,0,0,0,275,278,1,0,0,0,276,274,1,0,0,0,276,277,1,0,
  	0,0,277,21,1,0,0,0,278,276,1,0,0,0,279,280,5,32,0,0,280,23,1,0,0,0,281,
  	285,5,32,0,0,282,284,5,35,0,0,283,282,1,0,0,0,284,287,1,0,0,0,285,283,
  	1,0,0,0,285,286,1,0,0,0,286,291,1,0,0,0,287,285,1,0,0,0,288,289,5,20,
  	0,0,289,291,5,32,0,0,290,281,1,0,0,0,290,288,1,0,0,0,291,25,1,0,0,0,292,
  	293,5,18,0,0,293,294,5,32,0,0,294,295,5,59,0,0,295,296,3,30,15,0,296,
  	297,5,60,0,0,297,27,1,0,0,0,298,299,5,19,0,0,299,300,5,32,0,0,300,301,
  	5,59,0,0,301,302,3,30,15,0,302,303,5,60,0,0,303,29,1,0,0,0,304,305,3,
  	14,7,0,305,311,5,56,0,0,306,307,3,14,7,0,307,308,5,56,0,0,308,310,1,0,
  	0,0,309,306,1,0,0,0,310,313,1,0,0,0,311,309,1,0,0,0,311,312,1,0,0,0,312,
  	31,1,0,0,0,313,311,1,0,0,0,314,316,5,20,0,0,315,317,5,32,0,0,316,315,
  	1,0,0,0,316,317,1,0,0,0,317,318,1,0,0,0,318,319,5,59,0,0,319,320,3,34,
  	17,0,320,321,5,60,0,0,321,322,5,56,0,0,322,33,1,0,0,0,323,328,3,36,18,
  	0,324,325,5,55,0,0,325,327,3,36,18,0,326,324,1,0,0,0,327,330,1,0,0,0,
  	328,326,1,0,0,0,328,329,1,0,0,0,329,35,1,0,0,0,330,328,1,0,0,0,331,334,
  	3,22,11,0,332,333,5,64,0,0,333,335,3,40,20,0,334,332,1,0,0,0,334,335,
  	1,0,0,0,335,37,1,0,0,0,336,341,3,40,20,0,337,338,5,55,0,0,338,340,3,40,
  	20,0,339,337,1,0,0,0,340,343,1,0,0,0,341,339,1,0,0,0,341,342,1,0,0,0,
  	342,39,1,0,0,0,343,341,1,0,0,0,344,345,5,57,0,0,345,346,3,24,12,0,346,
  	347,5,58,0,0,347,348,3,40,20,0,348,394,1,0,0,0,349,350,3,42,21,0,350,
  	351,5,53,0,0,351,352,3,40,20,0,352,353,5,54,0,0,353,354,3,40,20,0,354,
  	394,1,0,0,0,355,356,3,64,32,0,356,357,5,63,0,0,357,358,3,22,11,0,358,
  	359,5,64,0,0,359,360,3,40,20,0,360,394,1,0,0,0,361,362,3,22,11,0,362,
  	363,5,61,0,0,363,364,3,40,20,0,364,365,5,62,0,0,365,366,5,64,0,0,366,
  	367,3,40,20,0,367,394,1,0,0,0,368,369,3,22,11,0,369,370,5,64,0,0,370,
  	371,3,40,20,0,371,394,1,0,0,0,372,373,3,22,11,0,373,374,5,65,0,0,374,
  	375,3,40,20,0,375,394,1,0,0,0,376,377,3,22,11,0,377,378,5,66,0,0,378,
  	379,3,40,20,0,379,394,1,0,0,0,380,381,3,22,11,0,381,382,5,67,0,0,382,
  	383,3,40,20,0,383,394,1,0,0,0,384,385,3,22,11,0,385,386,5,68,0,0,386,
  	387,3,40,20,0,387,394,1,0,0,0,388,389,3,22,11,0,389,390,5,69,0,0,390,
  	391,3,40,20,0,391,394,1,0,0,0,392,394,3,42,21,0,393,344,1,0,0,0,393,349,
  	1,0,0,0,393,355,1,0,0,0,393,361,1,0,0,0,393,368,1,0,0,0,393,372,1,0,0,
  	0,393,376,1,0,0,0,393,380,1,0,0,0,393,384,1,0,0,0,393,388,1,0,0,0,393,
  	392,1,0,0,0,394,41,1,0,0,0,395,396,6,21,-1,0,396,397,3,44,22,0,397,403,
  	1,0,0,0,398,399,10,1,0,0,399,400,5,45,0,0,400,402,3,44,22,0,401,398,1,
  	0,0,0,402,405,1,0,0,0,403,401,1,0,0,0,403,404,1,0,0,0,404,43,1,0,0,0,
  	405,403,1,0,0,0,406,407,6,22,-1,0,407,408,3,46,23,0,408,414,1,0,0,0,409,
  	410,10,1,0,0,410,411,5,44,0,0,411,413,3,46,23,0,412,409,1,0,0,0,413,416,
  	1,0,0,0,414,412,1,0,0,0,414,415,1,0,0,0,415,45,1,0,0,0,416,414,1,0,0,
  	0,417,418,6,23,-1,0,418,419,3,48,24,0,419,425,1,0,0,0,420,421,10,1,0,
  	0,421,422,5,48,0,0,422,424,3,48,24,0,423,420,1,0,0,0,424,427,1,0,0,0,
  	425,423,1,0,0,0,425,426,1,0,0,0,426,47,1,0,0,0,427,425,1,0,0,0,428,429,
  	6,24,-1,0,429,430,3,50,25,0,430,436,1,0,0,0,431,432,10,1,0,0,432,433,
  	5,49,0,0,433,435,3,50,25,0,434,431,1,0,0,0,435,438,1,0,0,0,436,434,1,
  	0,0,0,436,437,1,0,0,0,437,49,1,0,0,0,438,436,1,0,0,0,439,440,6,25,-1,
  	0,440,441,3,52,26,0,441,447,1,0,0,0,442,443,10,1,0,0,443,444,5,47,0,0,
  	444,446,3,52,26,0,445,442,1,0,0,0,446,449,1,0,0,0,447,445,1,0,0,0,447,
  	448,1,0,0,0,448,51,1,0,0,0,449,447,1,0,0,0,450,451,6,26,-1,0,451,452,
  	3,54,27,0,452,461,1,0,0,0,453,454,10,2,0,0,454,455,5,38,0,0,455,460,3,
  	54,27,0,456,457,10,1,0,0,457,458,5,39,0,0,458,460,3,54,27,0,459,453,1,
  	0,0,0,459,456,1,0,0,0,460,463,1,0,0,0,461,459,1,0,0,0,461,462,1,0,0,0,
  	462,53,1,0,0,0,463,461,1,0,0,0,464,465,6,27,-1,0,465,466,3,56,28,0,466,
  	481,1,0,0,0,467,468,10,4,0,0,468,469,5,40,0,0,469,480,3,56,28,0,470,471,
  	10,3,0,0,471,472,5,41,0,0,472,480,3,56,28,0,473,474,10,2,0,0,474,475,
  	5,42,0,0,475,480,3,56,28,0,476,477,10,1,0,0,477,478,5,43,0,0,478,480,
  	3,56,28,0,479,467,1,0,0,0,479,470,1,0,0,0,479,473,1,0,0,0,479,476,1,0,
  	0,0,480,483,1,0,0,0,481,479,1,0,0,0,481,482,1,0,0,0,482,55,1,0,0,0,483,
  	481,1,0,0,0,484,485,6,28,-1,0,485,486,3,58,29,0,486,495,1,0,0,0,487,488,
  	10,2,0,0,488,489,5,51,0,0,489,494,3,58,29,0,490,491,10,1,0,0,491,492,
  	5,52,0,0,492,494,3,58,29,0,493,487,1,0,0,0,493,490,1,0,0,0,494,497,1,
  	0,0,0,495,493,1,0,0,0,495,496,1,0,0,0,496,57,1,0,0,0,497,495,1,0,0,0,
  	498,499,6,29,-1,0,499,500,3,60,30,0,500,509,1,0,0,0,501,502,10,2,0,0,
  	502,503,5,33,0,0,503,508,3,60,30,0,504,505,10,1,0,0,505,506,5,34,0,0,
  	506,508,3,60,30,0,507,501,1,0,0,0,507,504,1,0,0,0,508,511,1,0,0,0,509,
  	507,1,0,0,0,509,510,1,0,0,0,510,59,1,0,0,0,511,509,1,0,0,0,512,513,6,
  	30,-1,0,513,514,3,62,31,0,514,526,1,0,0,0,515,516,10,3,0,0,516,517,5,
  	35,0,0,517,525,3,62,31,0,518,519,10,2,0,0,519,520,5,36,0,0,520,525,3,
  	62,31,0,521,522,10,1,0,0,522,523,5,37,0,0,523,525,3,62,31,0,524,515,1,
  	0,0,0,524,518,1,0,0,0,524,521,1,0,0,0,525,528,1,0,0,0,526,524,1,0,0,0,
  	526,527,1,0,0,0,527,61,1,0,0,0,528,526,1,0,0,0,529,551,3,64,32,0,530,
  	531,5,46,0,0,531,551,3,62,31,0,532,533,5,50,0,0,533,551,3,62,31,0,534,
  	535,5,47,0,0,535,551,3,62,31,0,536,537,5,35,0,0,537,551,3,62,31,0,538,
  	539,5,34,0,0,539,551,3,62,31,0,540,541,5,33,0,0,541,551,3,62,31,0,542,
  	543,5,23,0,0,543,551,3,40,20,0,544,545,3,22,11,0,545,546,5,70,0,0,546,
  	551,1,0,0,0,547,548,3,22,11,0,548,549,5,71,0,0,549,551,1,0,0,0,550,529,
  	1,0,0,0,550,530,1,0,0,0,550,532,1,0,0,0,550,534,1,0,0,0,550,536,1,0,0,
  	0,550,538,1,0,0,0,550,540,1,0,0,0,550,542,1,0,0,0,550,544,1,0,0,0,550,
  	547,1,0,0,0,551,63,1,0,0,0,552,553,3,22,11,0,553,555,5,57,0,0,554,556,
  	3,66,33,0,555,554,1,0,0,0,555,556,1,0,0,0,556,557,1,0,0,0,557,558,5,58,
  	0,0,558,594,1,0,0,0,559,560,3,22,11,0,560,561,5,61,0,0,561,562,3,40,20,
  	0,562,563,5,62,0,0,563,594,1,0,0,0,564,565,3,22,11,0,565,566,5,63,0,0,
  	566,567,3,22,11,0,567,569,5,57,0,0,568,570,3,66,33,0,569,568,1,0,0,0,
  	569,570,1,0,0,0,570,571,1,0,0,0,571,572,5,58,0,0,572,594,1,0,0,0,573,
  	574,3,22,11,0,574,575,5,63,0,0,575,576,3,22,11,0,576,594,1,0,0,0,577,
  	578,3,22,11,0,578,579,5,4,0,0,579,580,3,22,11,0,580,594,1,0,0,0,581,582,
  	3,22,11,0,582,583,5,70,0,0,583,594,1,0,0,0,584,585,3,22,11,0,585,586,
  	5,71,0,0,586,594,1,0,0,0,587,594,3,22,11,0,588,594,3,68,34,0,589,590,
  	5,57,0,0,590,591,3,40,20,0,591,592,5,58,0,0,592,594,1,0,0,0,593,552,1,
  	0,0,0,593,559,1,0,0,0,593,564,1,0,0,0,593,573,1,0,0,0,593,577,1,0,0,0,
  	593,581,1,0,0,0,593,584,1,0,0,0,593,587,1,0,0,0,593,588,1,0,0,0,593,589,
  	1,0,0,0,594,65,1,0,0,0,595,600,3,40,20,0,596,597,5,55,0,0,597,599,3,40,
  	20,0,598,596,1,0,0,0,599,602,1,0,0,0,600,598,1,0,0,0,600,601,1,0,0,0,
  	601,67,1,0,0,0,602,600,1,0,0,0,603,604,7,1,0,0,604,69,1,0,0,0,605,606,
  	5,8,0,0,606,607,5,57,0,0,607,608,3,40,20,0,608,609,5,58,0,0,609,612,3,
  	12,6,0,610,611,5,9,0,0,611,613,3,12,6,0,612,610,1,0,0,0,612,613,1,0,0,
  	0,613,71,1,0,0,0,614,615,5,10,0,0,615,616,5,57,0,0,616,617,3,40,20,0,
  	617,618,5,58,0,0,618,619,3,12,6,0,619,73,1,0,0,0,620,621,5,11,0,0,621,
  	623,5,57,0,0,622,624,3,76,38,0,623,622,1,0,0,0,623,624,1,0,0,0,624,625,
  	1,0,0,0,625,627,5,56,0,0,626,628,3,78,39,0,627,626,1,0,0,0,627,628,1,
  	0,0,0,628,629,1,0,0,0,629,631,5,56,0,0,630,632,3,80,40,0,631,630,1,0,
  	0,0,631,632,1,0,0,0,632,633,1,0,0,0,633,634,5,58,0,0,634,635,3,12,6,0,
  	635,75,1,0,0,0,636,639,3,14,7,0,637,639,3,40,20,0,638,636,1,0,0,0,638,
  	637,1,0,0,0,639,77,1,0,0,0,640,641,3,40,20,0,641,79,1,0,0,0,642,643,3,
  	40,20,0,643,81,1,0,0,0,644,645,5,12,0,0,645,646,3,12,6,0,646,647,5,10,
  	0,0,647,648,5,57,0,0,648,649,3,40,20,0,649,650,5,58,0,0,650,83,1,0,0,
  	0,651,652,5,5,0,0,652,654,3,12,6,0,653,655,3,86,43,0,654,653,1,0,0,0,
  	655,656,1,0,0,0,656,654,1,0,0,0,656,657,1,0,0,0,657,85,1,0,0,0,658,659,
  	5,6,0,0,659,660,5,57,0,0,660,661,3,24,12,0,661,662,3,22,11,0,662,663,
  	5,58,0,0,663,664,3,12,6,0,664,671,1,0,0,0,665,666,5,6,0,0,666,667,5,57,
  	0,0,667,668,5,72,0,0,668,669,5,58,0,0,669,671,3,12,6,0,670,658,1,0,0,
  	0,670,665,1,0,0,0,671,87,1,0,0,0,672,673,5,13,0,0,673,674,5,57,0,0,674,
  	675,3,40,20,0,675,676,5,58,0,0,676,677,5,59,0,0,677,678,3,90,45,0,678,
  	679,5,60,0,0,679,89,1,0,0,0,680,682,3,92,46,0,681,680,1,0,0,0,682,685,
  	1,0,0,0,683,681,1,0,0,0,683,684,1,0,0,0,684,91,1,0,0,0,685,683,1,0,0,
  	0,686,687,5,14,0,0,687,688,3,40,20,0,688,692,5,54,0,0,689,691,3,2,1,0,
  	690,689,1,0,0,0,691,694,1,0,0,0,692,690,1,0,0,0,692,693,1,0,0,0,693,704,
  	1,0,0,0,694,692,1,0,0,0,695,696,5,15,0,0,696,700,5,54,0,0,697,699,3,2,
  	1,0,698,697,1,0,0,0,699,702,1,0,0,0,700,698,1,0,0,0,700,701,1,0,0,0,701,
  	704,1,0,0,0,702,700,1,0,0,0,703,686,1,0,0,0,703,695,1,0,0,0,704,93,1,
  	0,0,0,60,97,143,149,159,167,170,175,183,191,197,203,209,215,227,234,241,
  	248,250,256,266,276,285,290,311,316,328,334,341,393,403,414,425,436,447,
  	459,461,479,481,493,495,507,509,524,526,550,555,569,593,600,612,623,627,
  	631,638,656,670,683,692,700,703
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
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
      setState(94);
      stmt();
      setState(99);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(100);
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
    setState(143);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(102);
      var_decl();
      setState(103);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(105);
      enum_decl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(106);
      func_decl();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(107);
      extern_decl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(108);
      struct_decl();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(109);
      struct_decl();
      setState(110);
      match(CScriptParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(112);
      union_decl();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(113);
      union_decl();
      setState(114);
      match(CScriptParser::SEMI);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(116);
      expr();
      setState(117);
      match(CScriptParser::SEMI);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(119);
      match(CScriptParser::MUL);
      setState(120);
      ident();
      setState(121);
      match(CScriptParser::ASSIGN);
      setState(122);
      expr();
      setState(123);
      match(CScriptParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(125);
      match(CScriptParser::RETURN);
      setState(126);
      expr();
      setState(127);
      match(CScriptParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(129);
      if_stmt();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(130);
      while_stmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(131);
      for_stmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(132);
      do_while_stmt();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(133);
      switch_stmt();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(134);
      try_catch_stmt();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(135);
      match(CScriptParser::CONTINUE);
      setState(136);
      match(CScriptParser::SEMI);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(137);
      match(CScriptParser::BREAK);
      setState(138);
      match(CScriptParser::SEMI);
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(139);
      register_callback_stmt();
      break;
    }

    case 21: {
      enterOuterAlt(_localctx, 21);
      setState(140);
      import_stmt();
      break;
    }

    case 22: {
      enterOuterAlt(_localctx, 22);
      setState(141);
      include_stmt();
      break;
    }

    case 23: {
      enterOuterAlt(_localctx, 23);
      setState(142);
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
    setState(167);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(145);
      match(CScriptParser::IMPORT);
      setState(146);
      match(CScriptParser::STRING);
      setState(149);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::T__0) {
        setState(147);
        match(CScriptParser::T__0);
        setState(148);
        ident();
      }
      setState(151);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(152);
      match(CScriptParser::IMPORT);
      setState(153);
      match(CScriptParser::LBRACE);
      setState(154);
      ident();
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CScriptParser::COMMA) {
        setState(155);
        match(CScriptParser::COMMA);
        setState(156);
        ident();
        setState(161);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(162);
      match(CScriptParser::RBRACE);
      setState(163);
      match(CScriptParser::T__1);
      setState(164);
      match(CScriptParser::STRING);
      setState(165);
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
    setState(170);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::HASH) {
      setState(169);
      match(CScriptParser::HASH);
    }
    setState(172);
    match(CScriptParser::INCLUDE);
    setState(173);
    _la = _input->LA(1);
    if (!(_la == CScriptParser::STRING

    || _la == CScriptParser::ANGLE_STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::SEMI) {
      setState(174);
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
    setState(177);
    match(CScriptParser::T__2);
    setState(178);
    ident();
    setState(179);
    match(CScriptParser::T__0);
    setState(180);
    ident();
    setState(181);
    match(CScriptParser::LPAREN);
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(182);
      func_decl_args();
    }
    setState(185);
    match(CScriptParser::RPAREN);
    setState(186);
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
    setState(197);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CScriptParser::ExportVarDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(188);
      match(CScriptParser::EXPORT);
      setState(189);
      var_decl();
      setState(191);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::SEMI) {
        setState(190);
        match(CScriptParser::SEMI);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CScriptParser::ExportFuncDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(193);
      match(CScriptParser::EXPORT);
      setState(194);
      func_decl();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CScriptParser::ExportEnumDeclContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(195);
      match(CScriptParser::EXPORT);
      setState(196);
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
    setState(209);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(199);
      match(CScriptParser::LBRACE);
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
        setState(200);
        stmt();
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(206);
      match(CScriptParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(207);
      match(CScriptParser::LBRACE);
      setState(208);
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
  enterRule(_localctx, 14, CScriptParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(250);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(211);
      type();
      setState(212);
      ident();
      setState(215);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(213);
        match(CScriptParser::ASSIGN);
        setState(214);
        expr();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(217);
      type();
      setState(218);
      ident();
      setState(219);
      match(CScriptParser::LBRACKET);
      setState(220);
      expr();
      setState(221);
      match(CScriptParser::RBRACKET);
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(222);
        match(CScriptParser::ASSIGN);
        setState(223);
        match(CScriptParser::LBRACE);
        setState(224);
        init_list();
        setState(225);
        match(CScriptParser::RBRACE);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(229);
      type();
      setState(230);
      match(CScriptParser::MUL);
      setState(231);
      ident();
      setState(234);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(232);
        match(CScriptParser::ASSIGN);
        setState(233);
        expr();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(236);
      match(CScriptParser::CONST_KW);
      setState(237);
      type();
      setState(238);
      ident();
      setState(241);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(239);
        match(CScriptParser::ASSIGN);
        setState(240);
        expr();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(243);
      match(CScriptParser::STRUCT_KW);
      setState(244);
      ident();
      setState(245);
      ident();
      setState(248);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(246);
        match(CScriptParser::ASSIGN);
        setState(247);
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
  enterRule(_localctx, 16, CScriptParser::RuleFunc_decl);
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
    setState(252);
    type();
    setState(253);
    ident();
    setState(254);
    match(CScriptParser::LPAREN);
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(255);
      func_decl_args();
    }
    setState(258);
    match(CScriptParser::RPAREN);
    setState(259);
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
  enterRule(_localctx, 18, CScriptParser::RuleExtern_decl);
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
    setState(261);
    match(CScriptParser::EXTERN_KW);
    setState(262);
    type();
    setState(263);
    ident();
    setState(264);
    match(CScriptParser::LPAREN);
    setState(266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(265);
      func_decl_args();
    }
    setState(268);
    match(CScriptParser::RPAREN);
    setState(269);
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
  enterRule(_localctx, 20, CScriptParser::RuleFunc_decl_args);
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
    setState(271);
    var_decl();
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(272);
      match(CScriptParser::COMMA);
      setState(273);
      var_decl();
      setState(278);
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
  enterRule(_localctx, 22, CScriptParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
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
  enterRule(_localctx, 24, CScriptParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(290);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(281);
        match(CScriptParser::IDENTIFIER);
        setState(285);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(282);
            match(CScriptParser::MUL); 
          }
          setState(287);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
        }
        break;
      }

      case CScriptParser::ENUM_KW: {
        enterOuterAlt(_localctx, 2);
        setState(288);
        match(CScriptParser::ENUM_KW);
        setState(289);
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
  enterRule(_localctx, 26, CScriptParser::RuleStruct_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    match(CScriptParser::STRUCT_KW);
    setState(293);
    match(CScriptParser::IDENTIFIER);
    setState(294);
    match(CScriptParser::LBRACE);
    setState(295);
    struct_members();
    setState(296);
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
  enterRule(_localctx, 28, CScriptParser::RuleUnion_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(CScriptParser::UNION_KW);
    setState(299);
    match(CScriptParser::IDENTIFIER);
    setState(300);
    match(CScriptParser::LBRACE);
    setState(301);
    struct_members();
    setState(302);
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
  enterRule(_localctx, 30, CScriptParser::RuleStruct_members);
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
    setState(304);
    var_decl();
    setState(305);
    match(CScriptParser::SEMI);
    setState(311);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4298375168) != 0)) {
      setState(306);
      var_decl();
      setState(307);
      match(CScriptParser::SEMI);
      setState(313);
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
  enterRule(_localctx, 32, CScriptParser::RuleEnum_decl);
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
    setState(314);
    match(CScriptParser::ENUM_KW);
    setState(316);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::IDENTIFIER) {
      setState(315);
      match(CScriptParser::IDENTIFIER);
    }
    setState(318);
    match(CScriptParser::LBRACE);
    setState(319);
    enum_list();
    setState(320);
    match(CScriptParser::RBRACE);
    setState(321);
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
  enterRule(_localctx, 34, CScriptParser::RuleEnum_list);
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
    setState(323);
    enum_item();
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(324);
      match(CScriptParser::COMMA);
      setState(325);
      enum_item();
      setState(330);
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
  enterRule(_localctx, 36, CScriptParser::RuleEnum_item);
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
    setState(331);
    ident();
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ASSIGN) {
      setState(332);
      match(CScriptParser::ASSIGN);
      setState(333);
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
  enterRule(_localctx, 38, CScriptParser::RuleInit_list);
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
    setState(336);
    expr();
    setState(341);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(337);
      match(CScriptParser::COMMA);
      setState(338);
      expr();
      setState(343);
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
  enterRule(_localctx, 40, CScriptParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(393);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(344);
      match(CScriptParser::LPAREN);
      setState(345);
      type();
      setState(346);
      match(CScriptParser::RPAREN);
      setState(347);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(349);
      or_expr(0);
      setState(350);
      match(CScriptParser::QUESTION);
      setState(351);
      expr();
      setState(352);
      match(CScriptParser::COLON);
      setState(353);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(355);
      primary_expr();
      setState(356);
      match(CScriptParser::DOT);
      setState(357);
      ident();
      setState(358);
      match(CScriptParser::ASSIGN);
      setState(359);
      expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(361);
      ident();
      setState(362);
      match(CScriptParser::LBRACKET);
      setState(363);
      expr();
      setState(364);
      match(CScriptParser::RBRACKET);
      setState(365);
      match(CScriptParser::ASSIGN);
      setState(366);
      expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(368);
      ident();
      setState(369);
      match(CScriptParser::ASSIGN);
      setState(370);
      expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(372);
      ident();
      setState(373);
      match(CScriptParser::PLUS_EQ);
      setState(374);
      expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(376);
      ident();
      setState(377);
      match(CScriptParser::MINUS_EQ);
      setState(378);
      expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(380);
      ident();
      setState(381);
      match(CScriptParser::MUL_EQ);
      setState(382);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(384);
      ident();
      setState(385);
      match(CScriptParser::DIV_EQ);
      setState(386);
      expr();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(388);
      ident();
      setState(389);
      match(CScriptParser::MOD_EQ);
      setState(390);
      expr();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(392);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, CScriptParser::RuleOr_expr, precedence);

    

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
    setState(396);
    and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(403);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleOr_expr);
        setState(398);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(399);
        match(CScriptParser::OR);
        setState(400);
        and_expr(0); 
      }
      setState(405);
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
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, CScriptParser::RuleAnd_expr, precedence);

    

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
    setState(407);
    bit_or_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(414);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<And_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAnd_expr);
        setState(409);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(410);
        match(CScriptParser::AND);
        setState(411);
        bit_or_expr(0); 
      }
      setState(416);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CScriptParser::RuleBit_or_expr, precedence);

    

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
    setState(418);
    bit_xor_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(425);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_or_expr);
        setState(420);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(421);
        match(CScriptParser::BITOR);
        setState(422);
        bit_xor_expr(0); 
      }
      setState(427);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CScriptParser::RuleBit_xor_expr, precedence);

    

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
    setState(429);
    bit_and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(436);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_xor_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_xor_expr);
        setState(431);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(432);
        match(CScriptParser::XOR);
        setState(433);
        bit_and_expr(0); 
      }
      setState(438);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CScriptParser::RuleBit_and_expr, precedence);

    

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
    setState(440);
    eq_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(447);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_and_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_and_expr);
        setState(442);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(443);
        match(CScriptParser::BITAND);
        setState(444);
        eq_expr(0); 
      }
      setState(449);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CScriptParser::RuleEq_expr, precedence);

    

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
    setState(451);
    rel_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(461);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(459);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(453);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(454);
          match(CScriptParser::EQ);
          setState(455);
          rel_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(456);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(457);
          match(CScriptParser::NEQ);
          setState(458);
          rel_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(463);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CScriptParser::RuleRel_expr, precedence);

    

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
    setState(465);
    shift_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(481);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(479);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(467);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(468);
          match(CScriptParser::LT);
          setState(469);
          shift_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(470);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(471);
          match(CScriptParser::LTE);
          setState(472);
          shift_expr(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(473);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(474);
          match(CScriptParser::GT);
          setState(475);
          shift_expr(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(476);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(477);
          match(CScriptParser::GTE);
          setState(478);
          shift_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(483);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CScriptParser::RuleShift_expr, precedence);

    

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
    add_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(495);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(493);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(487);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(488);
          match(CScriptParser::LSHIFT);
          setState(489);
          add_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(490);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(491);
          match(CScriptParser::RSHIFT);
          setState(492);
          add_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(497);
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
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, CScriptParser::RuleAdd_expr, precedence);

    

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
    mul_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(509);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(507);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(501);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(502);
          match(CScriptParser::PLUS);
          setState(503);
          mul_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(504);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(505);
          match(CScriptParser::MINUS);
          setState(506);
          mul_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(511);
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
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, CScriptParser::RuleMul_expr, precedence);

    

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
    setState(513);
    unary_expr();
    _ctx->stop = _input->LT(-1);
    setState(526);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(524);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(515);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(516);
          match(CScriptParser::MUL);
          setState(517);
          unary_expr();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(518);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(519);
          match(CScriptParser::DIV);
          setState(520);
          unary_expr();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(521);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(522);
          match(CScriptParser::MOD);
          setState(523);
          unary_expr();
          break;
        }

        default:
          break;
        } 
      }
      setState(528);
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
  enterRule(_localctx, 62, CScriptParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(550);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(529);
      primary_expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(530);
      match(CScriptParser::NOT);
      setState(531);
      unary_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(532);
      match(CScriptParser::NOTBIT);
      setState(533);
      unary_expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(534);
      match(CScriptParser::BITAND);
      setState(535);
      unary_expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(536);
      match(CScriptParser::MUL);
      setState(537);
      unary_expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(538);
      match(CScriptParser::MINUS);
      setState(539);
      unary_expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(540);
      match(CScriptParser::PLUS);
      setState(541);
      unary_expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(542);
      match(CScriptParser::THROW);
      setState(543);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(544);
      ident();
      setState(545);
      match(CScriptParser::INC);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(547);
      ident();
      setState(548);
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
  enterRule(_localctx, 64, CScriptParser::RulePrimary_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(593);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(552);
      ident();
      setState(553);
      match(CScriptParser::LPAREN);
      setState(555);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260661395456) != 0)) {
        setState(554);
        call_args();
      }
      setState(557);
      match(CScriptParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(559);
      ident();
      setState(560);
      match(CScriptParser::LBRACKET);
      setState(561);
      expr();
      setState(562);
      match(CScriptParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(564);
      ident();
      setState(565);
      match(CScriptParser::DOT);
      setState(566);
      ident();
      setState(567);
      match(CScriptParser::LPAREN);
      setState(569);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 145452260661395456) != 0)) {
        setState(568);
        call_args();
      }
      setState(571);
      match(CScriptParser::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(573);
      ident();
      setState(574);
      match(CScriptParser::DOT);
      setState(575);
      ident();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(577);
      ident();
      setState(578);
      match(CScriptParser::T__3);
      setState(579);
      ident();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(581);
      ident();
      setState(582);
      match(CScriptParser::INC);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(584);
      ident();
      setState(585);
      match(CScriptParser::DEC);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(587);
      ident();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(588);
      numeric();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(589);
      match(CScriptParser::LPAREN);
      setState(590);
      expr();
      setState(591);
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
  enterRule(_localctx, 66, CScriptParser::RuleCall_args);
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
    setState(595);
    expr();
    setState(600);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(596);
      match(CScriptParser::COMMA);
      setState(597);
      expr();
      setState(602);
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
  enterRule(_localctx, 68, CScriptParser::RuleNumeric);
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
    setState(603);
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
  enterRule(_localctx, 70, CScriptParser::RuleIf_stmt);
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
    setState(605);
    match(CScriptParser::IF);
    setState(606);
    match(CScriptParser::LPAREN);
    setState(607);
    expr();
    setState(608);
    match(CScriptParser::RPAREN);
    setState(609);
    block();
    setState(612);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ELSE) {
      setState(610);
      match(CScriptParser::ELSE);
      setState(611);
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
  enterRule(_localctx, 72, CScriptParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(614);
    match(CScriptParser::WHILE);
    setState(615);
    match(CScriptParser::LPAREN);
    setState(616);
    expr();
    setState(617);
    match(CScriptParser::RPAREN);
    setState(618);
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
  enterRule(_localctx, 74, CScriptParser::RuleFor_stmt);
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
    setState(620);
    match(CScriptParser::FOR);
    setState(621);
    match(CScriptParser::LPAREN);
    setState(623);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260664803328) != 0)) {
      setState(622);
      for_init();
    }
    setState(625);
    match(CScriptParser::SEMI);
    setState(627);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260661395456) != 0)) {
      setState(626);
      for_cond();
    }
    setState(629);
    match(CScriptParser::SEMI);
    setState(631);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 145452260661395456) != 0)) {
      setState(630);
      for_incr();
    }
    setState(633);
    match(CScriptParser::RPAREN);
    setState(634);
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
  enterRule(_localctx, 76, CScriptParser::RuleFor_init);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(638);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(636);
      var_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(637);
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
  enterRule(_localctx, 78, CScriptParser::RuleFor_cond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(640);
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
  enterRule(_localctx, 80, CScriptParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(642);
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
  enterRule(_localctx, 82, CScriptParser::RuleDo_while_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(644);
    match(CScriptParser::DO);
    setState(645);
    block();
    setState(646);
    match(CScriptParser::WHILE);
    setState(647);
    match(CScriptParser::LPAREN);
    setState(648);
    expr();
    setState(649);
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
  enterRule(_localctx, 84, CScriptParser::RuleTry_catch_stmt);
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
    setState(651);
    match(CScriptParser::T__4);
    setState(652);
    block();
    setState(654); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(653);
      catch_block();
      setState(656); 
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


std::any CScriptParser::Catch_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CScriptVisitor*>(visitor))
    return parserVisitor->visitCatch_block(this);
  else
    return visitor->visitChildren(this);
}

CScriptParser::Catch_blockContext* CScriptParser::catch_block() {
  Catch_blockContext *_localctx = _tracker.createInstance<Catch_blockContext>(_ctx, getState());
  enterRule(_localctx, 86, CScriptParser::RuleCatch_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(670);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(658);
      match(CScriptParser::T__5);
      setState(659);
      match(CScriptParser::LPAREN);
      setState(660);
      type();
      setState(661);
      ident();
      setState(662);
      match(CScriptParser::RPAREN);
      setState(663);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(665);
      match(CScriptParser::T__5);
      setState(666);
      match(CScriptParser::LPAREN);
      setState(667);
      match(CScriptParser::ELLIPSIS);
      setState(668);
      match(CScriptParser::RPAREN);
      setState(669);
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
  enterRule(_localctx, 88, CScriptParser::RuleSwitch_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(672);
    match(CScriptParser::SWITCH);
    setState(673);
    match(CScriptParser::LPAREN);
    setState(674);
    expr();
    setState(675);
    match(CScriptParser::RPAREN);
    setState(676);
    match(CScriptParser::LBRACE);
    setState(677);
    case_list();
    setState(678);
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
  enterRule(_localctx, 90, CScriptParser::RuleCase_list);
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
    setState(683);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::CASE

    || _la == CScriptParser::DEFAULT) {
      setState(680);
      case_stmt();
      setState(685);
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
  enterRule(_localctx, 92, CScriptParser::RuleCase_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(703);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::CASE: {
        enterOuterAlt(_localctx, 1);
        setState(686);
        match(CScriptParser::CASE);
        setState(687);
        expr();
        setState(688);
        match(CScriptParser::COLON);
        setState(692);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
          setState(689);
          stmt();
          setState(694);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CScriptParser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(695);
        match(CScriptParser::DEFAULT);
        setState(696);
        match(CScriptParser::COLON);
        setState(700);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 145452260787174824) != 0) || _la == CScriptParser::HASH) {
          setState(697);
          stmt();
          setState(702);
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
    case 21: return or_exprSempred(antlrcpp::downCast<Or_exprContext *>(context), predicateIndex);
    case 22: return and_exprSempred(antlrcpp::downCast<And_exprContext *>(context), predicateIndex);
    case 23: return bit_or_exprSempred(antlrcpp::downCast<Bit_or_exprContext *>(context), predicateIndex);
    case 24: return bit_xor_exprSempred(antlrcpp::downCast<Bit_xor_exprContext *>(context), predicateIndex);
    case 25: return bit_and_exprSempred(antlrcpp::downCast<Bit_and_exprContext *>(context), predicateIndex);
    case 26: return eq_exprSempred(antlrcpp::downCast<Eq_exprContext *>(context), predicateIndex);
    case 27: return rel_exprSempred(antlrcpp::downCast<Rel_exprContext *>(context), predicateIndex);
    case 28: return shift_exprSempred(antlrcpp::downCast<Shift_exprContext *>(context), predicateIndex);
    case 29: return add_exprSempred(antlrcpp::downCast<Add_exprContext *>(context), predicateIndex);
    case 30: return mul_exprSempred(antlrcpp::downCast<Mul_exprContext *>(context), predicateIndex);

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
