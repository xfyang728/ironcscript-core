
// Generated from D:/MyCode/CScriptEngine/pre/CScript.g4 by ANTLR 4.13.2


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
      "program", "stmt", "block", "var_decl", "func_decl", "extern_decl", 
      "func_decl_args", "ident", "type", "struct_decl", "union_decl", "struct_members", 
      "enum_decl", "enum_list", "enum_item", "init_list", "expr", "or_expr", 
      "and_expr", "bit_or_expr", "bit_xor_expr", "bit_and_expr", "eq_expr", 
      "rel_expr", "shift_expr", "add_expr", "mul_expr", "unary_expr", "primary_expr", 
      "call_args", "numeric", "if_stmt", "while_stmt", "for_stmt", "for_init", 
      "for_cond", "for_incr", "do_while_stmt", "switch_stmt", "case_list", 
      "case_stmt"
    },
    std::vector<std::string>{
      "", "'return'", "'if'", "'else'", "'while'", "'for'", "'do'", "'switch'", 
      "'case'", "'default'", "'continue'", "'break'", "'struct'", "'union'", 
      "'enum'", "'const'", "'extern'", "", "", "", "", "", "'+'", "'-'", 
      "'*'", "'/'", "'%'", "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", 
      "'&&'", "'||'", "'!'", "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", 
      "'\\u003F'", "':'", "','", "';'", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'.'", "'='", "'+='", "'-='", "'*='", "'/='", "'%='", "'++'", 
      "'--'"
    },
    std::vector<std::string>{
      "", "RETURN", "IF", "ELSE", "WHILE", "FOR", "DO", "SWITCH", "CASE", 
      "DEFAULT", "CONTINUE", "BREAK", "STRUCT_KW", "UNION_KW", "ENUM_KW", 
      "CONST_KW", "EXTERN_KW", "INTEGER", "DOUBLE", "CHAR", "STRING", "IDENTIFIER", 
      "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "LT", "LTE", "GT", 
      "GTE", "AND", "OR", "NOT", "BITAND", "BITOR", "XOR", "NOTBIT", "LSHIFT", 
      "RSHIFT", "QUESTION", "COLON", "COMMA", "SEMI", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "DOT", "ASSIGN", "PLUS_EQ", 
      "MINUS_EQ", "MUL_EQ", "DIV_EQ", "MOD_EQ", "INC", "DEC", "COMMENT", 
      "MULTI_LINE_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,63,582,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,1,0,5,0,84,8,0,10,
  	0,12,0,87,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,130,8,1,1,2,1,2,5,2,134,8,2,
  	10,2,12,2,137,9,2,1,2,1,2,1,2,3,2,142,8,2,1,3,1,3,1,3,1,3,3,3,148,8,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,160,8,3,1,3,1,3,1,3,1,3,1,
  	3,3,3,167,8,3,1,3,1,3,1,3,1,3,1,3,3,3,174,8,3,1,3,1,3,1,3,1,3,1,3,3,3,
  	181,8,3,3,3,183,8,3,1,4,1,4,1,4,1,4,3,4,189,8,4,1,4,1,4,1,4,1,5,1,5,1,
  	5,1,5,1,5,3,5,199,8,5,1,5,1,5,1,6,1,6,1,6,5,6,206,8,6,10,6,12,6,209,9,
  	6,1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,11,1,11,1,11,1,11,1,11,5,11,232,8,11,10,11,12,11,235,9,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,247,8,12,1,13,1,13,1,
  	13,5,13,252,8,13,10,13,12,13,255,9,13,1,14,1,14,1,14,3,14,260,8,14,1,
  	15,1,15,1,15,5,15,265,8,15,10,15,12,15,268,9,15,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,3,16,306,8,16,1,17,1,17,1,17,1,17,1,17,1,17,5,17,314,
  	8,17,10,17,12,17,317,9,17,1,18,1,18,1,18,1,18,1,18,1,18,5,18,325,8,18,
  	10,18,12,18,328,9,18,1,19,1,19,1,19,1,19,1,19,1,19,5,19,336,8,19,10,19,
  	12,19,339,9,19,1,20,1,20,1,20,1,20,1,20,1,20,5,20,347,8,20,10,20,12,20,
  	350,9,20,1,21,1,21,1,21,1,21,1,21,1,21,5,21,358,8,21,10,21,12,21,361,
  	9,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,5,22,372,8,22,10,22,
  	12,22,375,9,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,5,23,392,8,23,10,23,12,23,395,9,23,1,24,1,24,1,24,
  	1,24,1,24,1,24,1,24,1,24,1,24,5,24,406,8,24,10,24,12,24,409,9,24,1,25,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,5,25,420,8,25,10,25,12,25,423,
  	9,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,
  	437,8,26,10,26,12,26,440,9,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,461,8,27,
  	1,28,1,28,1,28,3,28,466,8,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,3,28,491,8,28,1,29,1,29,1,29,5,29,496,8,29,10,29,12,29,499,9,29,
  	1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,3,31,510,8,31,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,33,1,33,1,33,3,33,521,8,33,1,33,1,33,3,33,525,8,
  	33,1,33,1,33,3,33,529,8,33,1,33,1,33,1,33,1,34,1,34,3,34,536,8,34,1,35,
  	1,35,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,
  	1,38,1,38,1,38,1,38,1,39,5,39,558,8,39,10,39,12,39,561,9,39,1,40,1,40,
  	1,40,1,40,5,40,567,8,40,10,40,12,40,570,9,40,1,40,1,40,1,40,5,40,575,
  	8,40,10,40,12,40,578,9,40,3,40,580,8,40,1,40,0,10,34,36,38,40,42,44,46,
  	48,50,52,41,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
  	42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,0,1,1,0,17,
  	20,630,0,85,1,0,0,0,2,129,1,0,0,0,4,141,1,0,0,0,6,182,1,0,0,0,8,184,1,
  	0,0,0,10,193,1,0,0,0,12,202,1,0,0,0,14,210,1,0,0,0,16,212,1,0,0,0,18,
  	214,1,0,0,0,20,220,1,0,0,0,22,226,1,0,0,0,24,246,1,0,0,0,26,248,1,0,0,
  	0,28,256,1,0,0,0,30,261,1,0,0,0,32,305,1,0,0,0,34,307,1,0,0,0,36,318,
  	1,0,0,0,38,329,1,0,0,0,40,340,1,0,0,0,42,351,1,0,0,0,44,362,1,0,0,0,46,
  	376,1,0,0,0,48,396,1,0,0,0,50,410,1,0,0,0,52,424,1,0,0,0,54,460,1,0,0,
  	0,56,490,1,0,0,0,58,492,1,0,0,0,60,500,1,0,0,0,62,502,1,0,0,0,64,511,
  	1,0,0,0,66,517,1,0,0,0,68,535,1,0,0,0,70,537,1,0,0,0,72,539,1,0,0,0,74,
  	541,1,0,0,0,76,548,1,0,0,0,78,559,1,0,0,0,80,579,1,0,0,0,82,84,3,2,1,
  	0,83,82,1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,88,1,0,0,
  	0,87,85,1,0,0,0,88,89,5,0,0,1,89,1,1,0,0,0,90,91,3,6,3,0,91,92,5,45,0,
  	0,92,130,1,0,0,0,93,130,3,24,12,0,94,95,3,24,12,0,95,96,5,45,0,0,96,130,
  	1,0,0,0,97,130,3,8,4,0,98,130,3,10,5,0,99,130,3,18,9,0,100,101,3,18,9,
  	0,101,102,5,45,0,0,102,130,1,0,0,0,103,130,3,20,10,0,104,105,3,20,10,
  	0,105,106,5,45,0,0,106,130,1,0,0,0,107,108,3,32,16,0,108,109,5,45,0,0,
  	109,130,1,0,0,0,110,111,5,24,0,0,111,112,3,14,7,0,112,113,5,53,0,0,113,
  	114,3,32,16,0,114,115,5,45,0,0,115,130,1,0,0,0,116,117,5,1,0,0,117,118,
  	3,32,16,0,118,119,5,45,0,0,119,130,1,0,0,0,120,130,3,62,31,0,121,130,
  	3,64,32,0,122,130,3,66,33,0,123,130,3,74,37,0,124,130,3,76,38,0,125,126,
  	5,10,0,0,126,130,5,45,0,0,127,128,5,11,0,0,128,130,5,45,0,0,129,90,1,
  	0,0,0,129,93,1,0,0,0,129,94,1,0,0,0,129,97,1,0,0,0,129,98,1,0,0,0,129,
  	99,1,0,0,0,129,100,1,0,0,0,129,103,1,0,0,0,129,104,1,0,0,0,129,107,1,
  	0,0,0,129,110,1,0,0,0,129,116,1,0,0,0,129,120,1,0,0,0,129,121,1,0,0,0,
  	129,122,1,0,0,0,129,123,1,0,0,0,129,124,1,0,0,0,129,125,1,0,0,0,129,127,
  	1,0,0,0,130,3,1,0,0,0,131,135,5,48,0,0,132,134,3,2,1,0,133,132,1,0,0,
  	0,134,137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,138,1,0,0,0,137,
  	135,1,0,0,0,138,142,5,49,0,0,139,140,5,48,0,0,140,142,5,49,0,0,141,131,
  	1,0,0,0,141,139,1,0,0,0,142,5,1,0,0,0,143,144,3,16,8,0,144,147,3,14,7,
  	0,145,146,5,53,0,0,146,148,3,32,16,0,147,145,1,0,0,0,147,148,1,0,0,0,
  	148,183,1,0,0,0,149,150,3,16,8,0,150,151,3,14,7,0,151,152,5,50,0,0,152,
  	153,3,32,16,0,153,159,5,51,0,0,154,155,5,53,0,0,155,156,5,48,0,0,156,
  	157,3,30,15,0,157,158,5,49,0,0,158,160,1,0,0,0,159,154,1,0,0,0,159,160,
  	1,0,0,0,160,183,1,0,0,0,161,162,3,16,8,0,162,163,5,24,0,0,163,166,3,14,
  	7,0,164,165,5,53,0,0,165,167,3,32,16,0,166,164,1,0,0,0,166,167,1,0,0,
  	0,167,183,1,0,0,0,168,169,5,15,0,0,169,170,3,16,8,0,170,173,3,14,7,0,
  	171,172,5,53,0,0,172,174,3,32,16,0,173,171,1,0,0,0,173,174,1,0,0,0,174,
  	183,1,0,0,0,175,176,5,12,0,0,176,177,3,14,7,0,177,180,3,14,7,0,178,179,
  	5,53,0,0,179,181,3,32,16,0,180,178,1,0,0,0,180,181,1,0,0,0,181,183,1,
  	0,0,0,182,143,1,0,0,0,182,149,1,0,0,0,182,161,1,0,0,0,182,168,1,0,0,0,
  	182,175,1,0,0,0,183,7,1,0,0,0,184,185,3,16,8,0,185,186,3,14,7,0,186,188,
  	5,46,0,0,187,189,3,12,6,0,188,187,1,0,0,0,188,189,1,0,0,0,189,190,1,0,
  	0,0,190,191,5,47,0,0,191,192,3,4,2,0,192,9,1,0,0,0,193,194,5,16,0,0,194,
  	195,3,16,8,0,195,196,3,14,7,0,196,198,5,46,0,0,197,199,3,12,6,0,198,197,
  	1,0,0,0,198,199,1,0,0,0,199,200,1,0,0,0,200,201,5,47,0,0,201,11,1,0,0,
  	0,202,207,3,6,3,0,203,204,5,44,0,0,204,206,3,6,3,0,205,203,1,0,0,0,206,
  	209,1,0,0,0,207,205,1,0,0,0,207,208,1,0,0,0,208,13,1,0,0,0,209,207,1,
  	0,0,0,210,211,5,21,0,0,211,15,1,0,0,0,212,213,5,21,0,0,213,17,1,0,0,0,
  	214,215,5,12,0,0,215,216,5,21,0,0,216,217,5,48,0,0,217,218,3,22,11,0,
  	218,219,5,49,0,0,219,19,1,0,0,0,220,221,5,13,0,0,221,222,5,21,0,0,222,
  	223,5,48,0,0,223,224,3,22,11,0,224,225,5,49,0,0,225,21,1,0,0,0,226,227,
  	3,6,3,0,227,233,5,45,0,0,228,229,3,6,3,0,229,230,5,45,0,0,230,232,1,0,
  	0,0,231,228,1,0,0,0,232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,
  	23,1,0,0,0,235,233,1,0,0,0,236,237,5,14,0,0,237,238,5,21,0,0,238,239,
  	5,48,0,0,239,240,3,26,13,0,240,241,5,49,0,0,241,247,1,0,0,0,242,243,5,
  	14,0,0,243,244,5,21,0,0,244,245,5,48,0,0,245,247,5,49,0,0,246,236,1,0,
  	0,0,246,242,1,0,0,0,247,25,1,0,0,0,248,253,3,28,14,0,249,250,5,44,0,0,
  	250,252,3,28,14,0,251,249,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,253,
  	254,1,0,0,0,254,27,1,0,0,0,255,253,1,0,0,0,256,259,3,14,7,0,257,258,5,
  	53,0,0,258,260,3,32,16,0,259,257,1,0,0,0,259,260,1,0,0,0,260,29,1,0,0,
  	0,261,266,3,32,16,0,262,263,5,44,0,0,263,265,3,32,16,0,264,262,1,0,0,
  	0,265,268,1,0,0,0,266,264,1,0,0,0,266,267,1,0,0,0,267,31,1,0,0,0,268,
  	266,1,0,0,0,269,270,5,46,0,0,270,271,3,16,8,0,271,272,5,47,0,0,272,273,
  	3,32,16,0,273,306,1,0,0,0,274,275,3,34,17,0,275,276,5,42,0,0,276,277,
  	3,32,16,0,277,278,5,43,0,0,278,279,3,32,16,0,279,306,1,0,0,0,280,281,
  	3,14,7,0,281,282,5,53,0,0,282,283,3,32,16,0,283,306,1,0,0,0,284,285,3,
  	14,7,0,285,286,5,54,0,0,286,287,3,32,16,0,287,306,1,0,0,0,288,289,3,14,
  	7,0,289,290,5,55,0,0,290,291,3,32,16,0,291,306,1,0,0,0,292,293,3,14,7,
  	0,293,294,5,56,0,0,294,295,3,32,16,0,295,306,1,0,0,0,296,297,3,14,7,0,
  	297,298,5,57,0,0,298,299,3,32,16,0,299,306,1,0,0,0,300,301,3,14,7,0,301,
  	302,5,58,0,0,302,303,3,32,16,0,303,306,1,0,0,0,304,306,3,34,17,0,305,
  	269,1,0,0,0,305,274,1,0,0,0,305,280,1,0,0,0,305,284,1,0,0,0,305,288,1,
  	0,0,0,305,292,1,0,0,0,305,296,1,0,0,0,305,300,1,0,0,0,305,304,1,0,0,0,
  	306,33,1,0,0,0,307,308,6,17,-1,0,308,309,3,36,18,0,309,315,1,0,0,0,310,
  	311,10,1,0,0,311,312,5,34,0,0,312,314,3,36,18,0,313,310,1,0,0,0,314,317,
  	1,0,0,0,315,313,1,0,0,0,315,316,1,0,0,0,316,35,1,0,0,0,317,315,1,0,0,
  	0,318,319,6,18,-1,0,319,320,3,38,19,0,320,326,1,0,0,0,321,322,10,1,0,
  	0,322,323,5,33,0,0,323,325,3,38,19,0,324,321,1,0,0,0,325,328,1,0,0,0,
  	326,324,1,0,0,0,326,327,1,0,0,0,327,37,1,0,0,0,328,326,1,0,0,0,329,330,
  	6,19,-1,0,330,331,3,40,20,0,331,337,1,0,0,0,332,333,10,1,0,0,333,334,
  	5,37,0,0,334,336,3,40,20,0,335,332,1,0,0,0,336,339,1,0,0,0,337,335,1,
  	0,0,0,337,338,1,0,0,0,338,39,1,0,0,0,339,337,1,0,0,0,340,341,6,20,-1,
  	0,341,342,3,42,21,0,342,348,1,0,0,0,343,344,10,1,0,0,344,345,5,38,0,0,
  	345,347,3,42,21,0,346,343,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,348,
  	349,1,0,0,0,349,41,1,0,0,0,350,348,1,0,0,0,351,352,6,21,-1,0,352,353,
  	3,44,22,0,353,359,1,0,0,0,354,355,10,1,0,0,355,356,5,36,0,0,356,358,3,
  	44,22,0,357,354,1,0,0,0,358,361,1,0,0,0,359,357,1,0,0,0,359,360,1,0,0,
  	0,360,43,1,0,0,0,361,359,1,0,0,0,362,363,6,22,-1,0,363,364,3,46,23,0,
  	364,373,1,0,0,0,365,366,10,2,0,0,366,367,5,27,0,0,367,372,3,46,23,0,368,
  	369,10,1,0,0,369,370,5,28,0,0,370,372,3,46,23,0,371,365,1,0,0,0,371,368,
  	1,0,0,0,372,375,1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,45,1,0,0,
  	0,375,373,1,0,0,0,376,377,6,23,-1,0,377,378,3,48,24,0,378,393,1,0,0,0,
  	379,380,10,4,0,0,380,381,5,29,0,0,381,392,3,48,24,0,382,383,10,3,0,0,
  	383,384,5,30,0,0,384,392,3,48,24,0,385,386,10,2,0,0,386,387,5,31,0,0,
  	387,392,3,48,24,0,388,389,10,1,0,0,389,390,5,32,0,0,390,392,3,48,24,0,
  	391,379,1,0,0,0,391,382,1,0,0,0,391,385,1,0,0,0,391,388,1,0,0,0,392,395,
  	1,0,0,0,393,391,1,0,0,0,393,394,1,0,0,0,394,47,1,0,0,0,395,393,1,0,0,
  	0,396,397,6,24,-1,0,397,398,3,50,25,0,398,407,1,0,0,0,399,400,10,2,0,
  	0,400,401,5,40,0,0,401,406,3,50,25,0,402,403,10,1,0,0,403,404,5,41,0,
  	0,404,406,3,50,25,0,405,399,1,0,0,0,405,402,1,0,0,0,406,409,1,0,0,0,407,
  	405,1,0,0,0,407,408,1,0,0,0,408,49,1,0,0,0,409,407,1,0,0,0,410,411,6,
  	25,-1,0,411,412,3,52,26,0,412,421,1,0,0,0,413,414,10,2,0,0,414,415,5,
  	22,0,0,415,420,3,52,26,0,416,417,10,1,0,0,417,418,5,23,0,0,418,420,3,
  	52,26,0,419,413,1,0,0,0,419,416,1,0,0,0,420,423,1,0,0,0,421,419,1,0,0,
  	0,421,422,1,0,0,0,422,51,1,0,0,0,423,421,1,0,0,0,424,425,6,26,-1,0,425,
  	426,3,54,27,0,426,438,1,0,0,0,427,428,10,3,0,0,428,429,5,24,0,0,429,437,
  	3,54,27,0,430,431,10,2,0,0,431,432,5,25,0,0,432,437,3,54,27,0,433,434,
  	10,1,0,0,434,435,5,26,0,0,435,437,3,54,27,0,436,427,1,0,0,0,436,430,1,
  	0,0,0,436,433,1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,0,438,439,1,0,0,0,
  	439,53,1,0,0,0,440,438,1,0,0,0,441,461,3,56,28,0,442,443,5,35,0,0,443,
  	461,3,54,27,0,444,445,5,39,0,0,445,461,3,54,27,0,446,447,5,36,0,0,447,
  	461,3,54,27,0,448,449,5,24,0,0,449,461,3,54,27,0,450,451,5,23,0,0,451,
  	461,3,54,27,0,452,453,5,22,0,0,453,461,3,54,27,0,454,455,3,14,7,0,455,
  	456,5,59,0,0,456,461,1,0,0,0,457,458,3,14,7,0,458,459,5,60,0,0,459,461,
  	1,0,0,0,460,441,1,0,0,0,460,442,1,0,0,0,460,444,1,0,0,0,460,446,1,0,0,
  	0,460,448,1,0,0,0,460,450,1,0,0,0,460,452,1,0,0,0,460,454,1,0,0,0,460,
  	457,1,0,0,0,461,55,1,0,0,0,462,463,3,14,7,0,463,465,5,46,0,0,464,466,
  	3,58,29,0,465,464,1,0,0,0,465,466,1,0,0,0,466,467,1,0,0,0,467,468,5,47,
  	0,0,468,491,1,0,0,0,469,470,3,14,7,0,470,471,5,50,0,0,471,472,3,32,16,
  	0,472,473,5,51,0,0,473,491,1,0,0,0,474,475,3,14,7,0,475,476,5,52,0,0,
  	476,477,3,14,7,0,477,491,1,0,0,0,478,479,3,14,7,0,479,480,5,59,0,0,480,
  	491,1,0,0,0,481,482,3,14,7,0,482,483,5,60,0,0,483,491,1,0,0,0,484,491,
  	3,14,7,0,485,491,3,60,30,0,486,487,5,46,0,0,487,488,3,32,16,0,488,489,
  	5,47,0,0,489,491,1,0,0,0,490,462,1,0,0,0,490,469,1,0,0,0,490,474,1,0,
  	0,0,490,478,1,0,0,0,490,481,1,0,0,0,490,484,1,0,0,0,490,485,1,0,0,0,490,
  	486,1,0,0,0,491,57,1,0,0,0,492,497,3,32,16,0,493,494,5,44,0,0,494,496,
  	3,32,16,0,495,493,1,0,0,0,496,499,1,0,0,0,497,495,1,0,0,0,497,498,1,0,
  	0,0,498,59,1,0,0,0,499,497,1,0,0,0,500,501,7,0,0,0,501,61,1,0,0,0,502,
  	503,5,2,0,0,503,504,5,46,0,0,504,505,3,32,16,0,505,506,5,47,0,0,506,509,
  	3,4,2,0,507,508,5,3,0,0,508,510,3,4,2,0,509,507,1,0,0,0,509,510,1,0,0,
  	0,510,63,1,0,0,0,511,512,5,4,0,0,512,513,5,46,0,0,513,514,3,32,16,0,514,
  	515,5,47,0,0,515,516,3,4,2,0,516,65,1,0,0,0,517,518,5,5,0,0,518,520,5,
  	46,0,0,519,521,3,68,34,0,520,519,1,0,0,0,520,521,1,0,0,0,521,522,1,0,
  	0,0,522,524,5,45,0,0,523,525,3,70,35,0,524,523,1,0,0,0,524,525,1,0,0,
  	0,525,526,1,0,0,0,526,528,5,45,0,0,527,529,3,72,36,0,528,527,1,0,0,0,
  	528,529,1,0,0,0,529,530,1,0,0,0,530,531,5,47,0,0,531,532,3,4,2,0,532,
  	67,1,0,0,0,533,536,3,6,3,0,534,536,3,32,16,0,535,533,1,0,0,0,535,534,
  	1,0,0,0,536,69,1,0,0,0,537,538,3,32,16,0,538,71,1,0,0,0,539,540,3,32,
  	16,0,540,73,1,0,0,0,541,542,5,6,0,0,542,543,3,4,2,0,543,544,5,4,0,0,544,
  	545,5,46,0,0,545,546,3,32,16,0,546,547,5,47,0,0,547,75,1,0,0,0,548,549,
  	5,7,0,0,549,550,5,46,0,0,550,551,3,32,16,0,551,552,5,47,0,0,552,553,5,
  	48,0,0,553,554,3,78,39,0,554,555,5,49,0,0,555,77,1,0,0,0,556,558,3,80,
  	40,0,557,556,1,0,0,0,558,561,1,0,0,0,559,557,1,0,0,0,559,560,1,0,0,0,
  	560,79,1,0,0,0,561,559,1,0,0,0,562,563,5,8,0,0,563,564,3,32,16,0,564,
  	568,5,43,0,0,565,567,3,2,1,0,566,565,1,0,0,0,567,570,1,0,0,0,568,566,
  	1,0,0,0,568,569,1,0,0,0,569,580,1,0,0,0,570,568,1,0,0,0,571,572,5,9,0,
  	0,572,576,5,43,0,0,573,575,3,2,1,0,574,573,1,0,0,0,575,578,1,0,0,0,576,
  	574,1,0,0,0,576,577,1,0,0,0,577,580,1,0,0,0,578,576,1,0,0,0,579,562,1,
  	0,0,0,579,571,1,0,0,0,580,81,1,0,0,0,47,85,129,135,141,147,159,166,173,
  	180,182,188,198,207,233,246,253,259,266,305,315,326,337,348,359,371,373,
  	391,393,405,407,419,421,436,438,460,465,490,497,509,520,524,528,535,559,
  	568,576,579
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
    setState(85);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 71021612760310) != 0)) {
      setState(82);
      stmt();
      setState(87);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(88);
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

tree::TerminalNode* CScriptParser::StmtContext::CONTINUE() {
  return getToken(CScriptParser::CONTINUE, 0);
}

tree::TerminalNode* CScriptParser::StmtContext::BREAK() {
  return getToken(CScriptParser::BREAK, 0);
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
    setState(129);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(90);
      var_decl();
      setState(91);
      match(CScriptParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(93);
      enum_decl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(94);
      enum_decl();
      setState(95);
      match(CScriptParser::SEMI);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(97);
      func_decl();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(98);
      extern_decl();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(99);
      struct_decl();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(100);
      struct_decl();
      setState(101);
      match(CScriptParser::SEMI);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(103);
      union_decl();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(104);
      union_decl();
      setState(105);
      match(CScriptParser::SEMI);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(107);
      expr();
      setState(108);
      match(CScriptParser::SEMI);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(110);
      match(CScriptParser::MUL);
      setState(111);
      ident();
      setState(112);
      match(CScriptParser::ASSIGN);
      setState(113);
      expr();
      setState(114);
      match(CScriptParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(116);
      match(CScriptParser::RETURN);
      setState(117);
      expr();
      setState(118);
      match(CScriptParser::SEMI);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(120);
      if_stmt();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(121);
      while_stmt();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(122);
      for_stmt();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(123);
      do_while_stmt();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(124);
      switch_stmt();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(125);
      match(CScriptParser::CONTINUE);
      setState(126);
      match(CScriptParser::SEMI);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(127);
      match(CScriptParser::BREAK);
      setState(128);
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
  enterRule(_localctx, 4, CScriptParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(131);
      match(CScriptParser::LBRACE);
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 71021612760310) != 0)) {
        setState(132);
        stmt();
        setState(137);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(138);
      match(CScriptParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(139);
      match(CScriptParser::LBRACE);
      setState(140);
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
  enterRule(_localctx, 6, CScriptParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(182);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(143);
      type();
      setState(144);
      ident();
      setState(147);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(145);
        match(CScriptParser::ASSIGN);
        setState(146);
        expr();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(149);
      type();
      setState(150);
      ident();
      setState(151);
      match(CScriptParser::LBRACKET);
      setState(152);
      expr();
      setState(153);
      match(CScriptParser::RBRACKET);
      setState(159);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(154);
        match(CScriptParser::ASSIGN);
        setState(155);
        match(CScriptParser::LBRACE);
        setState(156);
        init_list();
        setState(157);
        match(CScriptParser::RBRACE);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(161);
      type();
      setState(162);
      match(CScriptParser::MUL);
      setState(163);
      ident();
      setState(166);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(164);
        match(CScriptParser::ASSIGN);
        setState(165);
        expr();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(168);
      match(CScriptParser::CONST_KW);
      setState(169);
      type();
      setState(170);
      ident();
      setState(173);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(171);
        match(CScriptParser::ASSIGN);
        setState(172);
        expr();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(175);
      match(CScriptParser::STRUCT_KW);
      setState(176);
      ident();
      setState(177);
      ident();
      setState(180);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CScriptParser::ASSIGN) {
        setState(178);
        match(CScriptParser::ASSIGN);
        setState(179);
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
  enterRule(_localctx, 8, CScriptParser::RuleFunc_decl);
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
    setState(184);
    type();
    setState(185);
    ident();
    setState(186);
    match(CScriptParser::LPAREN);
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2134016) != 0)) {
      setState(187);
      func_decl_args();
    }
    setState(190);
    match(CScriptParser::RPAREN);
    setState(191);
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
  enterRule(_localctx, 10, CScriptParser::RuleExtern_decl);
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
    setState(193);
    match(CScriptParser::EXTERN_KW);
    setState(194);
    type();
    setState(195);
    ident();
    setState(196);
    match(CScriptParser::LPAREN);
    setState(198);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2134016) != 0)) {
      setState(197);
      func_decl_args();
    }
    setState(200);
    match(CScriptParser::RPAREN);
   
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
  enterRule(_localctx, 12, CScriptParser::RuleFunc_decl_args);
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
    setState(202);
    var_decl();
    setState(207);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(203);
      match(CScriptParser::COMMA);
      setState(204);
      var_decl();
      setState(209);
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
  enterRule(_localctx, 14, CScriptParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
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
  enterRule(_localctx, 16, CScriptParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(CScriptParser::IDENTIFIER);
   
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
  enterRule(_localctx, 18, CScriptParser::RuleStruct_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    match(CScriptParser::STRUCT_KW);
    setState(215);
    match(CScriptParser::IDENTIFIER);
    setState(216);
    match(CScriptParser::LBRACE);
    setState(217);
    struct_members();
    setState(218);
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
  enterRule(_localctx, 20, CScriptParser::RuleUnion_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(CScriptParser::UNION_KW);
    setState(221);
    match(CScriptParser::IDENTIFIER);
    setState(222);
    match(CScriptParser::LBRACE);
    setState(223);
    struct_members();
    setState(224);
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
  enterRule(_localctx, 22, CScriptParser::RuleStruct_members);
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
    setState(226);
    var_decl();
    setState(227);
    match(CScriptParser::SEMI);
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2134016) != 0)) {
      setState(228);
      var_decl();
      setState(229);
      match(CScriptParser::SEMI);
      setState(235);
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

tree::TerminalNode* CScriptParser::Enum_declContext::IDENTIFIER() {
  return getToken(CScriptParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 24, CScriptParser::RuleEnum_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(236);
      match(CScriptParser::ENUM_KW);
      setState(237);
      match(CScriptParser::IDENTIFIER);
      setState(238);
      match(CScriptParser::LBRACE);
      setState(239);
      enum_list();
      setState(240);
      match(CScriptParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(242);
      match(CScriptParser::ENUM_KW);
      setState(243);
      match(CScriptParser::IDENTIFIER);
      setState(244);
      match(CScriptParser::LBRACE);
      setState(245);
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
  enterRule(_localctx, 26, CScriptParser::RuleEnum_list);
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
    setState(248);
    enum_item();
    setState(253);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(249);
      match(CScriptParser::COMMA);
      setState(250);
      enum_item();
      setState(255);
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
  enterRule(_localctx, 28, CScriptParser::RuleEnum_item);
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
    setState(256);
    ident();
    setState(259);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ASSIGN) {
      setState(257);
      match(CScriptParser::ASSIGN);
      setState(258);
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
  enterRule(_localctx, 30, CScriptParser::RuleInit_list);
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
    expr();
    setState(266);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(262);
      match(CScriptParser::COMMA);
      setState(263);
      expr();
      setState(268);
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

CScriptParser::IdentContext* CScriptParser::ExprContext::ident() {
  return getRuleContext<CScriptParser::IdentContext>(0);
}

tree::TerminalNode* CScriptParser::ExprContext::ASSIGN() {
  return getToken(CScriptParser::ASSIGN, 0);
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
  enterRule(_localctx, 32, CScriptParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(305);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(269);
      match(CScriptParser::LPAREN);
      setState(270);
      type();
      setState(271);
      match(CScriptParser::RPAREN);
      setState(272);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(274);
      or_expr(0);
      setState(275);
      match(CScriptParser::QUESTION);
      setState(276);
      expr();
      setState(277);
      match(CScriptParser::COLON);
      setState(278);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(280);
      ident();
      setState(281);
      match(CScriptParser::ASSIGN);
      setState(282);
      expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(284);
      ident();
      setState(285);
      match(CScriptParser::PLUS_EQ);
      setState(286);
      expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(288);
      ident();
      setState(289);
      match(CScriptParser::MINUS_EQ);
      setState(290);
      expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(292);
      ident();
      setState(293);
      match(CScriptParser::MUL_EQ);
      setState(294);
      expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(296);
      ident();
      setState(297);
      match(CScriptParser::DIV_EQ);
      setState(298);
      expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(300);
      ident();
      setState(301);
      match(CScriptParser::MOD_EQ);
      setState(302);
      expr();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(304);
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
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, CScriptParser::RuleOr_expr, precedence);

    

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
    setState(308);
    and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(315);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleOr_expr);
        setState(310);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(311);
        match(CScriptParser::OR);
        setState(312);
        and_expr(0); 
      }
      setState(317);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
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
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, CScriptParser::RuleAnd_expr, precedence);

    

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
    setState(319);
    bit_or_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(326);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<And_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAnd_expr);
        setState(321);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(322);
        match(CScriptParser::AND);
        setState(323);
        bit_or_expr(0); 
      }
      setState(328);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
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
  size_t startState = 38;
  enterRecursionRule(_localctx, 38, CScriptParser::RuleBit_or_expr, precedence);

    

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
    setState(330);
    bit_xor_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(337);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_or_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_or_expr);
        setState(332);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(333);
        match(CScriptParser::BITOR);
        setState(334);
        bit_xor_expr(0); 
      }
      setState(339);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
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
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, CScriptParser::RuleBit_xor_expr, precedence);

    

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
    setState(341);
    bit_and_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_xor_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_xor_expr);
        setState(343);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(344);
        match(CScriptParser::XOR);
        setState(345);
        bit_and_expr(0); 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, CScriptParser::RuleBit_and_expr, precedence);

    

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
    setState(352);
    eq_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Bit_and_exprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleBit_and_expr);
        setState(354);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(355);
        match(CScriptParser::BITAND);
        setState(356);
        eq_expr(0); 
      }
      setState(361);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
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
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, CScriptParser::RuleEq_expr, precedence);

    

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
    setState(363);
    rel_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(373);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(371);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(365);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(366);
          match(CScriptParser::EQ);
          setState(367);
          rel_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Eq_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleEq_expr);
          setState(368);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(369);
          match(CScriptParser::NEQ);
          setState(370);
          rel_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(375);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CScriptParser::RuleRel_expr, precedence);

    

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
    setState(377);
    shift_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(393);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(391);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(379);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(380);
          match(CScriptParser::LT);
          setState(381);
          shift_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(382);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(383);
          match(CScriptParser::LTE);
          setState(384);
          shift_expr(0);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(385);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(386);
          match(CScriptParser::GT);
          setState(387);
          shift_expr(0);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<Rel_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleRel_expr);
          setState(388);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(389);
          match(CScriptParser::GTE);
          setState(390);
          shift_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(395);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CScriptParser::RuleShift_expr, precedence);

    

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
    setState(397);
    add_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(407);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(405);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(399);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(400);
          match(CScriptParser::LSHIFT);
          setState(401);
          add_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Shift_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleShift_expr);
          setState(402);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(403);
          match(CScriptParser::RSHIFT);
          setState(404);
          add_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(409);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CScriptParser::RuleAdd_expr, precedence);

    

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
    mul_expr(0);
    _ctx->stop = _input->LT(-1);
    setState(421);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(419);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(413);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(414);
          match(CScriptParser::PLUS);
          setState(415);
          mul_expr(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Add_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleAdd_expr);
          setState(416);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(417);
          match(CScriptParser::MINUS);
          setState(418);
          mul_expr(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(423);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CScriptParser::RuleMul_expr, precedence);

    

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
    setState(425);
    unary_expr();
    _ctx->stop = _input->LT(-1);
    setState(438);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(436);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(427);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(428);
          match(CScriptParser::MUL);
          setState(429);
          unary_expr();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(430);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(431);
          match(CScriptParser::DIV);
          setState(432);
          unary_expr();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Mul_exprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMul_expr);
          setState(433);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(434);
          match(CScriptParser::MOD);
          setState(435);
          unary_expr();
          break;
        }

        default:
          break;
        } 
      }
      setState(440);
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
  enterRule(_localctx, 54, CScriptParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(460);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(441);
      primary_expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(442);
      match(CScriptParser::NOT);
      setState(443);
      unary_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(444);
      match(CScriptParser::NOTBIT);
      setState(445);
      unary_expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(446);
      match(CScriptParser::BITAND);
      setState(447);
      unary_expr();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(448);
      match(CScriptParser::MUL);
      setState(449);
      unary_expr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(450);
      match(CScriptParser::MINUS);
      setState(451);
      unary_expr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(452);
      match(CScriptParser::PLUS);
      setState(453);
      unary_expr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(454);
      ident();
      setState(455);
      match(CScriptParser::INC);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(457);
      ident();
      setState(458);
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
  enterRule(_localctx, 56, CScriptParser::RulePrimary_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(490);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(462);
      ident();
      setState(463);
      match(CScriptParser::LPAREN);
      setState(465);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 71021612630016) != 0)) {
        setState(464);
        call_args();
      }
      setState(467);
      match(CScriptParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(469);
      ident();
      setState(470);
      match(CScriptParser::LBRACKET);
      setState(471);
      expr();
      setState(472);
      match(CScriptParser::RBRACKET);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(474);
      ident();
      setState(475);
      match(CScriptParser::DOT);
      setState(476);
      ident();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(478);
      ident();
      setState(479);
      match(CScriptParser::INC);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(481);
      ident();
      setState(482);
      match(CScriptParser::DEC);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(484);
      ident();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(485);
      numeric();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(486);
      match(CScriptParser::LPAREN);
      setState(487);
      expr();
      setState(488);
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
  enterRule(_localctx, 58, CScriptParser::RuleCall_args);
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
    setState(492);
    expr();
    setState(497);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::COMMA) {
      setState(493);
      match(CScriptParser::COMMA);
      setState(494);
      expr();
      setState(499);
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
  enterRule(_localctx, 60, CScriptParser::RuleNumeric);
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
    setState(500);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1966080) != 0))) {
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
  enterRule(_localctx, 62, CScriptParser::RuleIf_stmt);
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
    setState(502);
    match(CScriptParser::IF);
    setState(503);
    match(CScriptParser::LPAREN);
    setState(504);
    expr();
    setState(505);
    match(CScriptParser::RPAREN);
    setState(506);
    block();
    setState(509);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CScriptParser::ELSE) {
      setState(507);
      match(CScriptParser::ELSE);
      setState(508);
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
  enterRule(_localctx, 64, CScriptParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(511);
    match(CScriptParser::WHILE);
    setState(512);
    match(CScriptParser::LPAREN);
    setState(513);
    expr();
    setState(514);
    match(CScriptParser::RPAREN);
    setState(515);
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
  enterRule(_localctx, 66, CScriptParser::RuleFor_stmt);
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
    setState(517);
    match(CScriptParser::FOR);
    setState(518);
    match(CScriptParser::LPAREN);
    setState(520);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 71021612666880) != 0)) {
      setState(519);
      for_init();
    }
    setState(522);
    match(CScriptParser::SEMI);
    setState(524);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 71021612630016) != 0)) {
      setState(523);
      for_cond();
    }
    setState(526);
    match(CScriptParser::SEMI);
    setState(528);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 71021612630016) != 0)) {
      setState(527);
      for_incr();
    }
    setState(530);
    match(CScriptParser::RPAREN);
    setState(531);
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
  enterRule(_localctx, 68, CScriptParser::RuleFor_init);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(535);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(533);
      var_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(534);
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
  enterRule(_localctx, 70, CScriptParser::RuleFor_cond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
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
  enterRule(_localctx, 72, CScriptParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(539);
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
  enterRule(_localctx, 74, CScriptParser::RuleDo_while_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(541);
    match(CScriptParser::DO);
    setState(542);
    block();
    setState(543);
    match(CScriptParser::WHILE);
    setState(544);
    match(CScriptParser::LPAREN);
    setState(545);
    expr();
    setState(546);
    match(CScriptParser::RPAREN);
   
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
  enterRule(_localctx, 76, CScriptParser::RuleSwitch_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    match(CScriptParser::SWITCH);
    setState(549);
    match(CScriptParser::LPAREN);
    setState(550);
    expr();
    setState(551);
    match(CScriptParser::RPAREN);
    setState(552);
    match(CScriptParser::LBRACE);
    setState(553);
    case_list();
    setState(554);
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
  enterRule(_localctx, 78, CScriptParser::RuleCase_list);
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
    setState(559);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CScriptParser::CASE

    || _la == CScriptParser::DEFAULT) {
      setState(556);
      case_stmt();
      setState(561);
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
  enterRule(_localctx, 80, CScriptParser::RuleCase_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CScriptParser::CASE: {
        enterOuterAlt(_localctx, 1);
        setState(562);
        match(CScriptParser::CASE);
        setState(563);
        expr();
        setState(564);
        match(CScriptParser::COLON);
        setState(568);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 71021612760310) != 0)) {
          setState(565);
          stmt();
          setState(570);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CScriptParser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(571);
        match(CScriptParser::DEFAULT);
        setState(572);
        match(CScriptParser::COLON);
        setState(576);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 71021612760310) != 0)) {
          setState(573);
          stmt();
          setState(578);
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
    case 17: return or_exprSempred(antlrcpp::downCast<Or_exprContext *>(context), predicateIndex);
    case 18: return and_exprSempred(antlrcpp::downCast<And_exprContext *>(context), predicateIndex);
    case 19: return bit_or_exprSempred(antlrcpp::downCast<Bit_or_exprContext *>(context), predicateIndex);
    case 20: return bit_xor_exprSempred(antlrcpp::downCast<Bit_xor_exprContext *>(context), predicateIndex);
    case 21: return bit_and_exprSempred(antlrcpp::downCast<Bit_and_exprContext *>(context), predicateIndex);
    case 22: return eq_exprSempred(antlrcpp::downCast<Eq_exprContext *>(context), predicateIndex);
    case 23: return rel_exprSempred(antlrcpp::downCast<Rel_exprContext *>(context), predicateIndex);
    case 24: return shift_exprSempred(antlrcpp::downCast<Shift_exprContext *>(context), predicateIndex);
    case 25: return add_exprSempred(antlrcpp::downCast<Add_exprContext *>(context), predicateIndex);
    case 26: return mul_exprSempred(antlrcpp::downCast<Mul_exprContext *>(context), predicateIndex);

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
