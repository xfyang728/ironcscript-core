#include "SemanticAnalyzer.h"
#include "frontend/parser/tokens.h"
#include "frontend/parser/node.h"

#include <iostream>

namespace cse {

SemanticAnalyzer::SemanticAnalyzer(SymbolTable& symTable, ModuleManager* moduleManager) : symbolTable(symTable), moduleManager(moduleManager), hasErrors(false), currentFunctionReturnType(""), currentSourceFile(""), currentBlock(nullptr) {
}

SemanticAnalyzer::~SemanticAnalyzer() {
}

void SemanticAnalyzer::setCurrentBlock(NBlock* block) {
    currentBlock = block;
}

void SemanticAnalyzer::error(const std::string& message, const Node* node) {
    std::cerr << "Error: " << message << std::endl;
    hasErrors = true;
}

void SemanticAnalyzer::debug(const std::string& message, const Node* node) {
    std::cout << "Debug: " << message << std::endl;
}

bool SemanticAnalyzer::analyze(NBlock& root) {
    hasErrors = false;
    analyzeBlock(&root);
    return !hasErrors;
}

void SemanticAnalyzer::analyzeStatement(NStatement* statement) {
    if (NVariableDeclaration* varDecl = dynamic_cast<NVariableDeclaration*>(statement)) {
        analyzeVariableDeclaration(varDecl);
    } else if (NArrayDeclaration* arrDecl = dynamic_cast<NArrayDeclaration*>(statement)) {
        analyzeArrayDeclaration(arrDecl);
    } else if (NStructDeclaration* structDecl = dynamic_cast<NStructDeclaration*>(statement)) {
    } else if (NPointerDeclaration* ptrDecl = dynamic_cast<NPointerDeclaration*>(statement)) {
        analyzePointerDeclaration(ptrDecl);
    } else if (NFunctionDeclaration* funcDecl = dynamic_cast<NFunctionDeclaration*>(statement)) {
        analyzeFunctionDeclaration(funcDecl);
    } else if (NExpressionStatement* exprStmt = dynamic_cast<NExpressionStatement*>(statement)) {
        analyzeExpressionStatement(exprStmt);
    } else if (NReturnStatement* returnStmt = dynamic_cast<NReturnStatement*>(statement)) {
        analyzeReturnStatement(returnStmt);
    } else if (NIfStatement* ifStmt = dynamic_cast<NIfStatement*>(statement)) {
        analyzeIfStatement(ifStmt);
    } else if (NWhileStatement* whileStmt = dynamic_cast<NWhileStatement*>(statement)) {
        analyzeWhileStatement(whileStmt);
    } else if (NForStatement* forStmt = dynamic_cast<NForStatement*>(statement)) {
        analyzeForStatement(forStmt);
    } else if (NDoWhileStatement* doWhileStmt = dynamic_cast<NDoWhileStatement*>(statement)) {
        analyzeDoWhileStatement(doWhileStmt);
    } else if (NBlock* block = dynamic_cast<NBlock*>(statement)) {
        analyzeBlock(block);
    } else if (NEnumDeclaration* enumDecl = dynamic_cast<NEnumDeclaration*>(statement)) {
        analyzeEnumDeclaration(enumDecl);
    } else if (NExternDeclaration* externDecl = dynamic_cast<NExternDeclaration*>(statement)) {
        std::string funcName = externDecl->id.name;
        std::string returnType = externDecl->type.name;

        Symbol symbol;
        symbol.name = funcName;
        symbol.type = returnType;
        symbol.isFunction = true;
        symbol.isGlobal = true;
        symbol.isExtern = true;

        for (auto& param : externDecl->arguments) {
            symbol.paramTypes.push_back(param->type.name);
        }

        Symbol* builtin = symbolTable.findSymbol(funcName);
        if (builtin && builtin->isVariadic) {
            symbol.isVariadic = true;
            symbol.paramTypes.clear();
        }

        symbolTable.insertSymbol(symbol);
        debug("Registered external function: " + funcName + " (returns " + returnType + ")", externDecl);
    } else if (NRegisterCallbackStatement* regCallback = dynamic_cast<NRegisterCallbackStatement*>(statement)) {
        // register callback 语句
        debug("Processing register callback: " + regCallback->callbackName.name
              + " as " + regCallback->targetName.name, regCallback);
    } else if (NImportStatement* importStmt = dynamic_cast<NImportStatement*>(statement)) {
        analyzeImportStatement(importStmt);
    } else if (NIncludeStatement* includeStmt = dynamic_cast<NIncludeStatement*>(statement)) {
        analyzeIncludeStatement(includeStmt);
    }
}

void SemanticAnalyzer::analyzeExpression(NExpression* expression) {
    if (NBinaryOperator* binOp = dynamic_cast<NBinaryOperator*>(expression)) {
        analyzeBinaryOperator(binOp);
    } else if (NTernaryOperator* ternaryOp = dynamic_cast<NTernaryOperator*>(expression)) {
        analyzeTernaryOperator(ternaryOp);
    } else if (NAssignment* assignment = dynamic_cast<NAssignment*>(expression)) {
        analyzeAssignment(assignment);
    } else if (NMethodCall* methodCall = dynamic_cast<NMethodCall*>(expression)) {
        analyzeMethodCall(methodCall);
    } else if (NIdentifier* id = dynamic_cast<NIdentifier*>(expression)) {
        analyzeIdentifier(id);
    } else if (NArrayAccess* arr = dynamic_cast<NArrayAccess*>(expression)) {
        analyzeArrayAccess(arr);
    } else if (NMemberAccess* member = dynamic_cast<NMemberAccess*>(expression)) {
        analyzeMemberAccess(member);
    } else if (dynamic_cast<NInteger*>(expression)) {
    } else if (dynamic_cast<NDouble*>(expression)) {
    } else if (dynamic_cast<NString*>(expression)) {
    }
}

void SemanticAnalyzer::analyzeArrayAccess(NArrayAccess* arr) {
    analyzeIdentifier(&arr->id);
    analyzeExpression(&arr->index);
}

void SemanticAnalyzer::analyzeMemberAccess(NMemberAccess* member) {
    // 分析对象表达式
    analyzeExpression(&member->object);
    
    // 分析成员标识符
    // 这里简化处理，假设成员访问是有效的
    // 实际实现中需要检查成员是否存在
}

void SemanticAnalyzer::analyzeVariableDeclaration(NVariableDeclaration* decl) {
    std::string varName = decl->id.name;
    std::string varType = decl->type.name;

    Scope* scope = symbolTable.getCurrentScope();
    while (scope) {
        auto it = scope->symbols.find(varType);
        if (it != scope->symbols.end() && it->second.isEnumType) {
            varType = "int";
            break;
        }
        scope = scope->parent;
    }

    Symbol* existingSymbol = symbolTable.findSymbolInCurrentScope(varName);
    if (existingSymbol) {
        error("Variable '" + varName + "' already declared in this scope", decl);
        return;
    }

    if (decl->isConst && !decl->assignmentExpr) {
        error("Const variable '" + varName + "' must be initialized", decl);
    }

    Symbol symbol;
    symbol.name = varName;
    symbol.type = varType;
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbol.offset = symbolTable.getCurrentScope()->nextOffset;
    symbol.isConst = decl->isConst;
    symbol.constantValue = 0;
    symbol.sourceFile = currentSourceFile;
    symbol.isImported = !currentSourceFile.empty();

    if (decl->assignmentExpr) {
        analyzeExpression(decl->assignmentExpr);
        std::string exprType = inferType(decl->assignmentExpr);
        if (!checkAssignmentCompatibility(varType, exprType)) {
            error("Type mismatch: cannot assign " + exprType + " to " + varType, decl);
        }
        if (decl->isConst) {
            symbol.constantValue = evaluateConstExpression(decl->assignmentExpr);
            std::cout << "[DEBUG] analyzeVariableDeclaration: const " << varName << " = " << symbol.constantValue << std::endl;
        }
    }

    symbolTable.getCurrentScope()->nextOffset += 8;
    symbolTable.insertSymbol(symbol);
}

void SemanticAnalyzer::analyzePointerDeclaration(NPointerDeclaration* decl) {
    std::string varName = decl->id.name;
    std::string varType = decl->type.name;
    if (varType.find('*') == std::string::npos) {
        varType = varType + "*";
    }

    Symbol* existingSymbol = symbolTable.findSymbolInCurrentScope(varName);
    if (existingSymbol) {
        error("Variable '" + varName + "' already declared in this scope", decl);
        return;
    }

    Symbol symbol;
    symbol.name = varName;
    symbol.type = varType;
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbol.offset = symbolTable.getCurrentScope()->nextOffset;
    symbol.sourceFile = currentSourceFile;
    symbol.isImported = !currentSourceFile.empty();

    symbolTable.getCurrentScope()->nextOffset += 8;

    symbolTable.insertSymbol(symbol);

    if (decl->assignmentExpr) {
        analyzeExpression(decl->assignmentExpr);
        std::string exprType = inferType(decl->assignmentExpr);
        if (!checkAssignmentCompatibility(varType, exprType)) {
            error("Type mismatch: cannot assign " + exprType + " to " + varType, decl);
        }
    }
}

void SemanticAnalyzer::analyzeArrayDeclaration(NArrayDeclaration* decl) {
    std::string varName = decl->id.name;
    std::string varType = decl->type.name + "[]";

    Symbol* existingSymbol = symbolTable.findSymbolInCurrentScope(varName);
    if (existingSymbol) {
        error("Variable '" + varName + "' already declared in this scope", decl);
        return;
    }

    Symbol symbol;
    symbol.name = varName;
    symbol.type = varType;
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbol.offset = symbolTable.getCurrentScope()->nextOffset;
    symbol.sourceFile = currentSourceFile;
    symbol.isImported = !currentSourceFile.empty();

    symbolTable.getCurrentScope()->nextOffset += 8 * 100;

    symbolTable.insertSymbol(symbol);

    if (decl->size) {
        analyzeExpression(decl->size);
    }

    if (decl->initializer) {
        for (auto& expr : *decl->initializer) {
            analyzeExpression(expr);
        }
    }
}

void SemanticAnalyzer::analyzeEnumDeclaration(NEnumDeclaration* decl) {
    std::cout << "[DEBUG] analyzeEnumDeclaration: name=" << decl->name.name << std::endl;

    Symbol typeSymbol;
    typeSymbol.name = decl->name.name;
    typeSymbol.type = "int";
    typeSymbol.isFunction = false;
    typeSymbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    typeSymbol.isEnumType = true;
    symbolTable.insertSymbol(typeSymbol);
    std::cout << "[DEBUG] analyzeEnumDeclaration: registered enum type " << typeSymbol.name << std::endl;

    int enumValue = 0;
    for (auto& item : decl->items.statements) {
        if (auto* enumItem = dynamic_cast<NEnumItem*>(item)) {
            if (enumItem->value) {
                if (auto* intLit = dynamic_cast<NInteger*>(enumItem->value)) {
                    enumValue = intLit->value;
                }
            }

            Symbol symbol;
            symbol.name = enumItem->name.name;
            symbol.type = "int";
            symbol.isFunction = false;
            symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
            symbol.constantValue = enumValue;
            symbol.isEnum = true;
            symbolTable.insertSymbol(symbol);
            std::cout << "[DEBUG] analyzeEnumDeclaration: registered " << symbol.name << " = " << enumValue << std::endl;

            enumValue++;
        }
    }
}

void SemanticAnalyzer::analyzeFunctionDeclaration(NFunctionDeclaration* decl) {
    std::cout << "[DEBUG] analyzeFunctionDeclaration: " << decl->id.name << std::endl;
    std::string funcName = decl->id.name;
    std::string returnType = decl->type.name;

    Symbol* existingSymbol = symbolTable.findSymbolInCurrentScope(funcName);
    if (existingSymbol) {
        error("Function '" + funcName + "' already declared in this scope", decl);
        return;
    }

    Symbol symbol;
    symbol.name = funcName;
    symbol.type = returnType;
    symbol.isFunction = true;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbol.sourceFile = currentSourceFile;
    symbol.isImported = !currentSourceFile.empty();

    for (auto& param : decl->arguments) {
        symbol.paramTypes.push_back(param->type.name);
    }

    symbolTable.insertSymbol(symbol);

    symbolTable.enterScope();

    std::string oldReturnType = currentFunctionReturnType;
    currentFunctionReturnType = returnType;

    std::cout << "[DEBUG] analyzeFunctionDeclaration: analyzing " << decl->arguments.size() << " arguments" << std::endl;
    for (auto& param : decl->arguments) {
        analyzeVariableDeclaration(param);
    }

    std::cout << "[DEBUG] analyzeFunctionDeclaration: analyzing body" << std::endl;
    analyzeBlock(decl->block);

    currentFunctionReturnType = oldReturnType;

    symbolTable.exitScope();
}

void SemanticAnalyzer::analyzeExpressionStatement(NExpressionStatement* stmt) {
    analyzeExpression(&stmt->expression);
}

void SemanticAnalyzer::analyzeReturnStatement(NReturnStatement* stmt) {
    analyzeExpression(&stmt->expression);
    std::string exprType = inferType(&stmt->expression);
    if (!currentFunctionReturnType.empty()) {
        if (!checkTypeCompatibility(currentFunctionReturnType, exprType)) {
            error("Return type mismatch: expected " + currentFunctionReturnType + ", got " + exprType, stmt);
        }
    }
}

void SemanticAnalyzer::analyzeIfStatement(NIfStatement* stmt) {
    analyzeExpression(&stmt->condition);
    analyzeBlock(&stmt->trueBlock);
    if (stmt->falseBlock) {
        analyzeBlock(stmt->falseBlock);
    }
}

void SemanticAnalyzer::analyzeWhileStatement(NWhileStatement* stmt) {
    analyzeExpression(&stmt->condition);
    analyzeBlock(&stmt->block);
}

void SemanticAnalyzer::analyzeForStatement(NForStatement* stmt) {
    if (stmt->initialization) {
        analyzeStatement(stmt->initialization);
    }
    if (stmt->condition) {
        analyzeExpression(stmt->condition);
    }
    if (stmt->increment) {
        analyzeExpression(stmt->increment);
    }
    analyzeBlock(&stmt->block);
}

void SemanticAnalyzer::analyzeDoWhileStatement(NDoWhileStatement* stmt) {
    analyzeBlock(&stmt->block);
    analyzeExpression(&stmt->condition);
}

void SemanticAnalyzer::analyzeTernaryOperator(NTernaryOperator* op) {
    analyzeExpression(&op->condition);
    analyzeExpression(&op->trueExpr);
    analyzeExpression(&op->falseExpr);
}

void SemanticAnalyzer::analyzeBinaryOperator(NBinaryOperator* op) {
    analyzeExpression(&op->lhs);
    analyzeExpression(&op->rhs);

    std::string lhsType = inferType(&op->lhs);
    std::string rhsType = inferType(&op->rhs);

    if (!checkTypeCompatibility(lhsType, rhsType)) {
        error("Type mismatch in binary operation: " + lhsType + " and " + rhsType, op);
    }
}

void SemanticAnalyzer::analyzeAssignment(NAssignment* assignment) {
    if (NIdentifier* id = dynamic_cast<NIdentifier*>(&assignment->lhs)) {
        analyzeIdentifier(id);
    } else if (NUnaryOperator* unary = dynamic_cast<NUnaryOperator*>(&assignment->lhs)) {
        if (unary->op == TMUL) {
            analyzeExpression(&unary->expr);
        } else {
            error("Invalid assignment target", assignment);
            return;
        }
    } else if (NArrayAccess* arr = dynamic_cast<NArrayAccess*>(&assignment->lhs)) {
        analyzeExpression(arr);
    } else if (NMemberAccess* member = dynamic_cast<NMemberAccess*>(&assignment->lhs)) {
        analyzeExpression(member);
    } else {
        error("Invalid assignment target", assignment);
        return;
    }

    analyzeExpression(&assignment->rhs);

    std::string lhsType = inferType(&assignment->lhs);
    std::string rhsType = inferType(&assignment->rhs);

    if (!checkAssignmentCompatibility(lhsType, rhsType)) {
        error("Type mismatch in assignment: cannot assign " + rhsType + " to " + lhsType, assignment);
    }
}

void SemanticAnalyzer::analyzeMethodCall(NMethodCall* call) {
    std::string funcName = call->id.name;

    Symbol* funcSymbol = symbolTable.findSymbol(funcName);
    if (!funcSymbol) {
        error("Function '" + funcName + "' is not declared", call);
        return;
    }

    if (!funcSymbol->isFunction) {
        error("'" + funcName + "' is not a function", call);
        return;
    }

    if (!funcSymbol->isVariadic && call->arguments.size() != funcSymbol->paramTypes.size()) {
        error("Function '" + funcName + "' expects " + std::to_string(funcSymbol->paramTypes.size()) + " arguments, got " + std::to_string(call->arguments.size()), call);
        return;
    }

    if (funcSymbol->isVariadic && call->arguments.size() < funcSymbol->paramTypes.size()) {
        error("Function '" + funcName + "' expects at least " + std::to_string(funcSymbol->paramTypes.size()) + " arguments, got " + std::to_string(call->arguments.size()), call);
        return;
    }

    for (size_t i = 0; i < call->arguments.size(); i++) {
        analyzeExpression(call->arguments[i]);
        std::string argType = inferType(call->arguments[i]);
        if (i < funcSymbol->paramTypes.size()) {
            if (!checkTypeCompatibility(funcSymbol->paramTypes[i], argType)) {
                error("Type mismatch in argument " + std::to_string(i+1) + " of function '" + funcName + "': expected " + funcSymbol->paramTypes[i] + ", got " + argType, call);
            }
        }
    }
}

void SemanticAnalyzer::analyzeIdentifier(NIdentifier* id) {
    std::string name = id->name;

    Symbol* symbol = symbolTable.findSymbol(name);
    if (!symbol) {
        error("Identifier '" + name + "' is not declared", id);
    }
}

void SemanticAnalyzer::analyzeBlock(NBlock* block) {
    std::cout << "[DEBUG] analyzeBlock: processing " << block->statements.size() << " statements" << std::endl;

    NBlock* previousBlock = currentBlock;
    currentBlock = block;

    symbolTable.enterScope();

    for (auto& statement : block->statements) {
        std::cout << "[DEBUG] analyzeBlock: processing statement type: " << typeid(*statement).name() << std::endl;
        analyzeStatement(statement);
    }

    symbolTable.exitScope();

    currentBlock = previousBlock;
}

std::string SemanticAnalyzer::inferType(NExpression* expression) {
    if (NIdentifier* id = dynamic_cast<NIdentifier*>(expression)) {
        Symbol* symbol = symbolTable.findSymbol(id->name);
        if (symbol) {
            std::string type = symbol->type;
            if (type.find("[]") != std::string::npos) {
                std::string ptrType = type.substr(0, type.length() - 2) + "*";
                std::cout << "[DEBUG] inferType: array type, returning " << ptrType << std::endl;
                return ptrType;
            }
            return type;
        }
        return "int";
    } else if (NUnaryOperator* unaryOp = dynamic_cast<NUnaryOperator*>(expression)) {
        if (unaryOp->op == TMUL) {
            std::string exprType = inferType(&unaryOp->expr);
            if (exprType.find("*") != std::string::npos) {
                return exprType.substr(0, exprType.length() - 1);
            }
            return "int";
        } else if (unaryOp->op == TBITAND) {
            std::string exprType = inferType(&unaryOp->expr);
            return exprType + "*";
        }
        return "int";
    } else if (dynamic_cast<NInteger*>(expression)) {
        return "int";
    } else if (dynamic_cast<NDouble*>(expression)) {
        return "double";
    } else if (dynamic_cast<NString*>(expression)) {
        return "char*";
    } else if (NBinaryOperator* binOp = dynamic_cast<NBinaryOperator*>(expression)) {
        std::string lhsType = inferType(&binOp->lhs);
        std::string rhsType = inferType(&binOp->rhs);
        if (lhsType == "double" || rhsType == "double") {
            return "double";
        }
        return "int";
    } else if (NAssignment* assignment = dynamic_cast<NAssignment*>(expression)) {
        return inferType(&assignment->rhs);
    } else if (NMethodCall* call = dynamic_cast<NMethodCall*>(expression)) {
        Symbol* funcSymbol = symbolTable.findSymbol(call->id.name);
        if (funcSymbol) {
            return funcSymbol->type;
        }
        return "int";
    } else if (NArrayAccess* arr = dynamic_cast<NArrayAccess*>(expression)) {
        std::string arrName = arr->id.name;
        Scope* scope = symbolTable.getCurrentScope();
        while (scope) {
            if (scope->symbols.find(arrName) != scope->symbols.end()) {
                std::string type = scope->symbols[arrName].type;
                if (type.find("[]") != std::string::npos) {
                    return type.substr(0, type.length() - 2);
                }
                break;
            }
            scope = scope->parent;
        }
        return "int";
    } else if (NMemberAccess* member = dynamic_cast<NMemberAccess*>(expression)) {
        return "int";
    } else if (NCastOperator* castOp = dynamic_cast<NCastOperator*>(expression)) {
        return castOp->targetType;
    }
    return "int";
}

bool SemanticAnalyzer::checkTypeCompatibility(const std::string& type1, const std::string& type2) {
    if (type1 == type2) {
        return true;
    }

    // char is compatible with int (char promotes to int)
    if ((type1 == "int" && type2 == "char") || (type1 == "char" && type2 == "int")) {
        return true;
    }

    // char is compatible with double (char promotes to double)
    if ((type1 == "double" && type2 == "char") || (type1 == "char" && type2 == "double")) {
        return true;
    }

    // int is compatible with double
    if ((type1 == "int" && type2 == "double") || (type1 == "double" && type2 == "int")) {
        return true;
    }

    // void* is compatible with any pointer type (char*, int*, void*, etc.)
    if (type1 == "void*" && !type2.empty() && type2.back() == '*') {
        return true;
    }
    if (type2 == "void*" && !type1.empty() && type1.back() == '*') {
        return true;
    }

    // size_t is compatible with int
    if ((type1 == "size_t" && type2 == "int") || (type1 == "int" && type2 == "size_t")) {
        return true;
    }

    // long is compatible with int
    if ((type1 == "long" && type2 == "int") || (type1 == "int" && type2 == "long")) {
        return true;
    }

    // unsigned int is compatible with int
    if ((type1 == "unsigned int" && type2 == "int") || (type1 == "int" && type2 == "unsigned int")) {
        return true;
    }

    // char* is compatible with string (for printf/scanf compatibility)
    if ((type1 == "string" && type2 == "char*") || (type1 == "char*" && type2 == "string")) {
        return true;
    }

    return false;
}

int64_t SemanticAnalyzer::evaluateConstExpression(NExpression* expression) {
    if (!expression) {
        return 0;
    }

    if (NInteger* integer = dynamic_cast<NInteger*>(expression)) {
        return integer->value;
    }

    if (NIdentifier* id = dynamic_cast<NIdentifier*>(expression)) {
        Symbol* symbol = symbolTable.findSymbol(id->name);
        if (symbol && symbol->isConst) {
            return symbol->constantValue;
        }
        if (symbol && symbol->isEnum) {
            return symbol->constantValue;
        }
        return 0;
    }

    if (NBinaryOperator* binOp = dynamic_cast<NBinaryOperator*>(expression)) {
        int64_t lhs = evaluateConstExpression(&binOp->lhs);
        int64_t rhs = evaluateConstExpression(&binOp->rhs);
        switch (binOp->op) {
            case TPLUS: return lhs + rhs;
            case TMINUS: return lhs - rhs;
            case TMUL: return lhs * rhs;
            case TDIV: return rhs != 0 ? lhs / rhs : 0;
            case TMOD: return rhs != 0 ? lhs % rhs : 0;
            case TBITAND: return lhs & rhs;
            case TBITOR: return lhs | rhs;
            case TXOR: return lhs ^ rhs;
            case TLSHIFT: return lhs << rhs;
            case TRSHIFT: return lhs >> rhs;
            default: return 0;
        }
    }

    if (NUnaryOperator* unaryOp = dynamic_cast<NUnaryOperator*>(expression)) {
        int64_t val = evaluateConstExpression(&unaryOp->expr);
        switch (unaryOp->op) {
            case TMINUS: return -val;
            case TNOTBIT: return ~val;
            case TNOT: return !val;
            default: return 0;
        }
    }

    if (NAssignment* assignment = dynamic_cast<NAssignment*>(expression)) {
        return evaluateConstExpression(&assignment->rhs);
    }

    return 0;
}

bool SemanticAnalyzer::checkAssignmentCompatibility(const std::string& lhsType, const std::string& rhsType) {
    if (lhsType == rhsType) {
        return true;
    }

    // char can be assigned to int (char promotes to int)
    if (lhsType == "int" && rhsType == "char") {
        return true;
    }

    // int can be assigned to char (with potential loss of precision)
    if (lhsType == "char" && rhsType == "int") {
        return true;
    }

    // char can be assigned to double (char promotes to double)
    if (lhsType == "double" && rhsType == "char") {
        return true;
    }

    // double can be assigned to char (with potential loss of precision)
    if (lhsType == "char" && rhsType == "double") {
        return true;
    }

    // int can be assigned to double
    if (lhsType == "double" && rhsType == "int") {
        return true;
    }

    // double can be assigned to int (with potential loss of precision)
    if (lhsType == "int" && rhsType == "double") {
        return true;
    }

    // void* can be assigned from any pointer type
    if (lhsType == "void*" && !rhsType.empty() && rhsType.back() == '*') {
        return true;
    }

    // any pointer can be assigned from void*
    if (rhsType == "void*" && !lhsType.empty() && lhsType.back() == '*') {
        return true;
    }

    // size_t can be assigned from int
    if ((lhsType == "size_t" && rhsType == "int") || (lhsType == "int" && rhsType == "size_t")) {
        return true;
    }

    // long can be assigned from int
    if ((lhsType == "long" && rhsType == "int") || (lhsType == "int" && rhsType == "long")) {
        return true;
    }

    // unsigned int can be assigned from int
    if ((lhsType == "unsigned int" && rhsType == "int") || (lhsType == "int" && rhsType == "unsigned int")) {
        return true;
    }

    return false;
}

void SemanticAnalyzer::analyzeImportStatement(NImportStatement* stmt) {
    debug("Processing import statement: " + stmt->modulePath, stmt);

    if (moduleManager) {
        if (stmt->isNamedImport) {
            debug("Importing named symbols: ", stmt);
            for (const auto& symbol : stmt->symbols) {
                debug("  - " + symbol, stmt);
            }
            moduleManager->importNamedSymbols(stmt->modulePath, stmt->symbols, symbolTable);
        } else if (!stmt->alias.empty()) {
            debug("Importing module as: " + stmt->alias, stmt);
            moduleManager->importModule(stmt->modulePath, stmt->alias, symbolTable);
        } else {
            debug("Importing module: " + stmt->modulePath, stmt);
            moduleManager->importModule(stmt->modulePath, "", symbolTable);
        }
    } else {
        debug("ModuleManager not available, skipping import", stmt);
    }
}

void SemanticAnalyzer::analyzeIncludeStatement(NIncludeStatement* stmt) {
    debug("Processing include statement: " + stmt->filePath, stmt);

    if (moduleManager && currentBlock) {
        debug("Including file: " + stmt->filePath, stmt);
        std::string source = stmt->sourceFile.empty() ? currentSourceFile : stmt->sourceFile;
        if (!moduleManager->includeFile(stmt->filePath, *currentBlock,
            source, stmt->line, stmt->column)) {
            hasErrors = true;
        }
    } else {
        debug("ModuleManager not available, skipping include", stmt);
    }
}

}
