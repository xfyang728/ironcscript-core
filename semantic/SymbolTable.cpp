#include "frontend/semantic/SymbolTable.h"
#include "platform/PlatformConstants.h"

namespace cse {

SymbolTable::SymbolTable() : currentScope(nullptr) {
    enterScope();
    registerBuiltinFunctions();
#ifdef CSE_EMBEDDED
    registerBuiltinConstants();
#endif
}

SymbolTable::~SymbolTable() {
    std::cout << "SymbolTable destructor called. Scope stack size: " << scopeStack.size() << std::endl;
    
    // 安全地清理所有scope
    while (!scopeStack.empty()) {
        Scope* oldScope = scopeStack.top();
        scopeStack.pop();
        std::cout << "Deleting scope: " << oldScope << std::endl;
        delete oldScope;
    }
    
    currentScope = nullptr;
    std::cout << "SymbolTable destruction completed." << std::endl;
}

void SymbolTable::enterScope() {
    Scope* newScope = new Scope(currentScope);
    scopeStack.push(newScope);
    currentScope = newScope;
}

void SymbolTable::exitScope() {
    if (scopeStack.size() <= 1) {
        return;
    }
    Scope* oldScope = scopeStack.top();
    scopeStack.pop();
    currentScope = scopeStack.top();
    delete oldScope;
}

bool SymbolTable::insertSymbol(const Symbol& symbol) {
    if (!currentScope) {
        return false;
    }
    if (findSymbolInCurrentScope(symbol.name) != nullptr) {
        return false;
    }
    currentScope->symbols[symbol.name] = symbol;
    return true;
}

Symbol* SymbolTable::findSymbol(const std::string& name) {
    Scope* scope = currentScope;
    while (scope) {
        auto it = scope->symbols.find(name);
        if (it != scope->symbols.end()) {
            return &it->second;
        }
        scope = scope->parent;
    }
    return nullptr;
}

Symbol* SymbolTable::findSymbolInCurrentScope(const std::string& name) {
    if (!currentScope) {
        return nullptr;
    }
    auto it = currentScope->symbols.find(name);
    if (it != currentScope->symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

void SymbolTable::registerBuiltinFunctions() {
    for (const auto& func : BUILTIN_FUNCTIONS) {
        Symbol symbol;
        symbol.name = func.name;
        symbol.type = func.returnType;
        symbol.isFunction = true;
        symbol.isGlobal = true;
        symbol.paramTypes = func.paramTypes;
        symbol.isVariadic = func.isVariadic;
        insertSymbol(symbol);
    }
}

Scope* SymbolTable::getGlobalScope() const {
    // 遍历作用域链，找到最顶层的作用域（全局作用域）
    Scope* scope = currentScope;
    while (scope && scope->parent) {
        scope = scope->parent;
    }
    return scope;
}

bool SymbolTable::insertSymbolToGlobalScope(const Symbol& symbol) {
    // 获取全局作用域
    Scope* globalScope = getGlobalScope();
    if (!globalScope) {
        return false;
    }

    // 检查符号是否已经存在
    if (globalScope->symbols.find(symbol.name) != globalScope->symbols.end()) {
        return false;
    }

    // 在全局作用域中插入符号
    globalScope->symbols[symbol.name] = symbol;
    return true;
}

void SymbolTable::registerBuiltinConstants() {
    std::function<void(const char*, int64_t)> func = [this](const char* name, int64_t value) {
        registerConstant(name, value);
    };
    PlatformConstants::registerCommon(func);
}

void SymbolTable::registerPlatformConstants(const std::string& platform) {
    std::function<void(const char*, int64_t)> func = [this](const char* name, int64_t value) {
        registerConstant(name, value);
    };

    if (platform == "k210" || platform == "K210") {
        K210Constants::registerAll(func);
    } else if (platform == "stm32" || platform == "STM32") {
        STM32Constants::registerAll(func);
    }
}

void SymbolTable::registerConstant(const std::string& name, int64_t value) {
    Symbol symbol;
    symbol.name = name;
    symbol.type = "int";
    symbol.isFunction = false;
    symbol.isGlobal = true;
    symbol.isConst = true;
    symbol.constantValue = value;
    symbol.isEnum = false;
    symbol.isEnumType = false;
    symbol.isVariadic = false;
    symbol.isExtern = false;
    insertSymbolToGlobalScope(symbol);
}

}
