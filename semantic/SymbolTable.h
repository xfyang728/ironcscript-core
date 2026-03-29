#ifndef CSE_SYMBOL_TABLE_H
#define CSE_SYMBOL_TABLE_H

#include <map>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <cstdint>

namespace cse {

struct BuiltinFunction {
    const char* name;
    const char* returnType;
    bool isVariadic;
    std::vector<std::string> paramTypes;
};

static const std::vector<BuiltinFunction> BUILTIN_FUNCTIONS = {
    // === 输入输出函数 (16) ===
    {"printf", "int", true, {}},
    {"scanf", "int", true, {}},
    {"sprintf", "int", true, {}},
    {"sscanf", "int", true, {}},
    {"fprintf", "int", true, {}},
    {"fscanf", "int", true, {}},
    {"puts", "int", false, {"char*"}},
    {"gets", "char*", false, {"char*"}},
    {"fputs", "int", false, {"char*", "FILE*"}},
    {"fgets", "char*", false, {"char*", "int", "FILE*"}},
    {"putchar", "int", false, {"int"}},
    {"getchar", "int", false, {}},
    {"putc", "int", false, {"int", "FILE*"}},
    {"getc", "int", false, {"FILE*"}},
    // === 字符串函数 (25) ===
    {"strlen", "int", false, {"char*"}},
    {"strcpy", "char*", false, {"char*", "char*"}},
    {"strncpy", "char*", false, {"char*", "char*", "size_t"}},
    {"strcat", "char*", false, {"char*", "char*"}},
    {"strncat", "char*", false, {"char*", "char*", "size_t"}},
    {"strcmp", "int", false, {"char*", "char*"}},
    {"strncmp", "int", false, {"char*", "char*", "size_t"}},
    {"strchr", "char*", false, {"char*", "int"}},
    {"strrchr", "char*", false, {"char*", "int"}},
    {"strstr", "char*", false, {"char*", "char*"}},
    {"strdup", "char*", false, {"char*"}},
    {"strndup", "char*", false, {"char*", "size_t"}},
    {"strtok", "char*", false, {"char*", "char*"}},
    {"strtol", "long", false, {"char*", "char**", "int"}},
    {"strtod", "double", false, {"char*", "char**"}},
    {"strtof", "float", false, {"char*", "char**"}},
    {"atoi", "int", false, {"char*"}},
    {"atol", "long", false, {"char*"}},
    {"atof", "double", false, {"char*"}},
    {"atoll", "long long", false, {"char*"}},
    // === 内存函数 (4) ===
    {"malloc", "void*", false, {"size_t"}},
    {"free", "void", false, {"void*"}},
    {"calloc", "void*", false, {"size_t", "size_t"}},
    {"realloc", "void*", false, {"void*", "size_t"}},
    {"memset", "void*", false, {"void*", "int", "size_t"}},
    {"memcpy", "void*", false, {"void*", "void*", "size_t"}},
    {"memmove", "void*", false, {"void*", "void*", "size_t"}},
    {"memcmp", "int", false, {"void*", "void*", "size_t"}},
    {"memchr", "void*", false, {"void*", "int", "size_t"}},
    // === 数学函数 (20) ===
    {"sqrt", "double", false, {"double"}},
    {"sin", "double", false, {"double"}},
    {"cos", "double", false, {"double"}},
    {"tan", "double", false, {"double"}},
    {"asin", "double", false, {"double"}},
    {"acos", "double", false, {"double"}},
    {"atan", "double", false, {"double"}},
    {"atan2", "double", false, {"double", "double"}},
    {"sinh", "double", false, {"double"}},
    {"cosh", "double", false, {"double"}},
    {"tanh", "double", false, {"double"}},
    {"pow", "double", false, {"double", "double"}},
    {"exp", "double", false, {"double"}},
    {"log", "double", false, {"double"}},
    {"log10", "double", false, {"double"}},
    {"log2", "double", false, {"double"}},
    {"floor", "double", false, {"double"}},
    {"ceil", "double", false, {"double"}},
    {"fabs", "double", false, {"double"}},
    {"abs", "int", false, {"int"}},
    // === 文件操作函数 (15) ===
    {"fopen", "FILE*", false, {"char*", "char*"}},
    {"fclose", "int", false, {"FILE*"}},
    {"fread", "size_t", false, {"void*", "size_t", "size_t", "FILE*"}},
    {"fwrite", "size_t", false, {"void*", "size_t", "size_t", "FILE*"}},
    {"fseek", "int", false, {"FILE*", "long", "int"}},
    {"ftell", "long", false, {"FILE*"}},
    {"rewind", "void", false, {"FILE*"}},
    {"feof", "int", false, {"FILE*"}},
    {"ferror", "int", false, {"FILE*"}},
    {"clearerr", "void", false, {"FILE*"}},
    {"fgetc", "int", false, {"FILE*"}},
    {"fputc", "int", false, {"int", "FILE*"}},
    {"fflush", "int", false, {"FILE*"}},
    // === 时间函数 (6) ===
    {"time", "time_t", false, {"time_t*"}},
    {"clock", "clock_t", false, {}},
    {"difftime", "double", false, {"time_t", "time_t"}},
    {"mktime", "time_t", false, {"time_t*"}},
    {"strftime", "size_t", false, {"char*", "size_t", "char*", "time_t*"}},
    {"gmtime", "time_t*", false, {"time_t*"}},
    // === 字符分类函数 (10) ===
    {"isdigit", "int", false, {"int"}},
    {"isalpha", "int", false, {"int"}},
    {"isalnum", "int", false, {"int"}},
    {"isspace", "int", false, {"int"}},
    {"isupper", "int", false, {"int"}},
    {"islower", "int", false, {"int"}},
    {"isgraph", "int", false, {"int"}},
    {"isprint", "int", false, {"int"}},
    {"ispunct", "int", false, {"int"}},
    {"iscntrl", "int", false, {"int"}},
    // === 大小写转换 (2) ===
    {"toupper", "int", false, {"int"}},
    {"tolower", "int", false, {"int"}},
    // === 系统接口函数 (6) ===
    {"system", "int", false, {"char*"}},
    {"getenv", "char*", false, {"char*"}},
    {"abort", "void", false, {}},
    {"exit", "void", false, {"int"}},
    {"atexit", "int", false, {"void*"}},
    {"signal", "void*", false, {"int", "void*"}},
    // === 其他 (5) ===
    {"rand", "int", false, {}},
    {"srand", "void", false, {"unsigned int"}},
    {"bsearch", "void*", false, {"void*", "void*", "size_t", "size_t", "void*"}},
    {"qsort", "void", false, {"void*", "size_t", "size_t", "void*"}},
    {"raise", "int", false, {"int"}},
};

struct Symbol {
    std::string name;
    std::string type;
    bool isFunction;
    bool isGlobal;
    int offset;
    std::vector<std::string> paramTypes;
    int constantValue;
    bool isEnum;
    bool isEnumType;
    bool isVariadic;
    bool isConst;
    bool isExtern;

    Symbol() : constantValue(0), isEnum(false), isEnumType(false), isVariadic(false), isConst(false), isExtern(false) {}
};

struct Scope {
    std::map<std::string, Symbol> symbols;
    Scope* parent;
    int nextOffset;

    Scope(Scope* parentScope = nullptr) : parent(parentScope), nextOffset(0) {}
};

class SymbolTable {
public:
    SymbolTable();
    ~SymbolTable();

    void enterScope();
    void exitScope();
    bool insertSymbol(const Symbol& symbol);
    Symbol* findSymbol(const std::string& name);
    Symbol* findSymbolInCurrentScope(const std::string& name);

    Scope* getCurrentScope() const { return currentScope; }
    Scope* getGlobalScope() const;
    bool insertSymbolToGlobalScope(const Symbol& symbol);
    int getScopeLevel() const { return scopeStack.size(); }

    void registerBuiltinConstants();
    void registerConstant(const std::string& name, int64_t value);
    void registerPlatformConstants(const std::string& platform);

private:
    std::stack<Scope*> scopeStack;
    Scope* currentScope;
    void registerBuiltinFunctions();
};

}

#endif
