#include "IRGenerator.h"
#include "frontend/parser/tokens.h"
#include "module/StandardLibraryRegistry.h"

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <set>
#include <cstdio>

namespace cse {

// 辅助函数：将整数转换为字符串
std::string intToString(int value) {
    char buffer[32];
    sprintf(buffer, "%d", value);
    return buffer;
}

// 辅助函数：将长整数转换为字符串
std::string longToString(long long value) {
    char buffer[32];
    sprintf(buffer, "%lld", value);
    return buffer;
}

// 辅助函数：将浮点数转换为字符串
std::string doubleToString(double value) {
    char buffer[32];
    sprintf(buffer, "%f", value);
    return buffer;
}

IRGenerator::IRGenerator(SymbolTable& symTable) : symbolTable(symTable), hasErrors(false), tempVarCounter(0), paramEvalVarCounter(0), paramIndex(0) {
}

IRGenerator::~IRGenerator() {
}

void IRGenerator::generateIR(NBlock& root) {
    analyzeBlock(&root);
}

const std::list<Quad>& IRGenerator::getQuadList() const {
    return quadList;
}

void IRGenerator::error(const std::string& message, const Node* node) {
    std::cerr << "Error: " << message << std::endl;
    hasErrors = true;
}

std::string IRGenerator::generateTempVar() {
    std::stringstream ss;
    ss << "t" << tempVarCounter++;
    return ss.str();
}

std::string IRGenerator::generateParamEvalVar(int paramIndex) {
    std::stringstream ss;
    ss << "pe" << paramIndex << "_" << paramEvalVarCounter++;
    return ss.str();
}

void IRGenerator::analyzeStatement(NStatement* statement) {
    if (auto* varDecl = dynamic_cast<NVariableDeclaration*>(statement)) {
        analyzeVariableDeclaration(varDecl);
    } else if (auto* arrayDecl = dynamic_cast<NArrayDeclaration*>(statement)) {
        analyzeArrayDeclaration(arrayDecl);
    } else if (auto* pointerDecl = dynamic_cast<NPointerDeclaration*>(statement)) {
        analyzePointerDeclaration(pointerDecl);
    } else if (auto* structDecl = dynamic_cast<NStructDeclaration*>(statement)) {
        // 结构体声明：直接跳过，成员已在 analyzeBlock 中处理
    } else if (auto* funcDecl = dynamic_cast<NFunctionDeclaration*>(statement)) {
        analyzeFunctionDeclaration(funcDecl);
    } else if (auto* exprStmt = dynamic_cast<NExpressionStatement*>(statement)) {
        analyzeExpressionStatement(exprStmt);
    } else if (auto* returnStmt = dynamic_cast<NReturnStatement*>(statement)) {
        analyzeReturnStatement(returnStmt);
    } else if (auto* ifStmt = dynamic_cast<NIfStatement*>(statement)) {
        analyzeIfStatement(ifStmt);
    } else if (auto* whileStmt = dynamic_cast<NWhileStatement*>(statement)) {
        analyzeWhileStatement(whileStmt);
    } else if (auto* forStmt = dynamic_cast<NForStatement*>(statement)) {
        analyzeForStatement(forStmt);
    } else if (auto* doWhileStmt = dynamic_cast<NDoWhileStatement*>(statement)) {
        analyzeDoWhileStatement(doWhileStmt);
    } else if (auto* switchStmt = dynamic_cast<NSwitchStatement*>(statement)) {
        analyzeSwitchStatement(switchStmt);
    } else if (auto* caseStmt = dynamic_cast<NCaseStatement*>(statement)) {
        analyzeCaseStatement(caseStmt);
    } else if (auto* defaultStmt = dynamic_cast<NDefaultStatement*>(statement)) {
        analyzeDefaultStatement(defaultStmt);
    } else if (auto* continueStmt = dynamic_cast<NContinueStatement*>(statement)) {
        analyzeContinueStatement(continueStmt);
    } else if (auto* breakStmt = dynamic_cast<NBreakStatement*>(statement)) {
        analyzeBreakStatement(breakStmt);
    } else if (auto* block = dynamic_cast<NBlock*>(statement)) {
        analyzeBlock(block);
    } else if (auto* tryCatchStmt = dynamic_cast<NTryCatchStatement*>(statement)) {
        analyzeTryCatchStatement(tryCatchStmt);
    } else if (auto* enumDecl = dynamic_cast<NEnumDeclaration*>(statement)) {
        analyzeEnumDeclaration(enumDecl);
    } else if (auto* enumItem = dynamic_cast<NEnumItem*>(statement)) {
        analyzeEnumItem(enumItem);
    } else if (auto* externDecl = dynamic_cast<NExternDeclaration*>(statement)) {
        // extern 声明：生成 EXTERN 四元式
        std::cerr << "[DEBUG] Generating IR for extern: " << externDecl->id.name << std::endl;
        quadList.push_back(Quad(OpEnum::EXTERN, externDecl->type.name, "", externDecl->id.name));
    } else if (auto* regCallback = dynamic_cast<NRegisterCallbackStatement*>(statement)) {
        // register callback 语句：生成 REGISTER_CALLBACK 四元式
        std::cerr << "[DEBUG] Generating IR for register callback: " << regCallback->callbackName.name
                  << " as " << regCallback->targetName.name << std::endl;
        quadList.push_back(Quad(OpEnum::REGISTER_CALLBACK, regCallback->targetName.name, "",
                                regCallback->callbackName.name));
    } else if (auto* includeStmt = dynamic_cast<NIncludeStatement*>(statement)) {
        // #include <stdio.h> - 处理标准库头文件
        std::string filePath = includeStmt->filePath;
        std::cerr << "[DEBUG] IR generating include: " << filePath << std::endl;

        // Check if this is a standard library header
        std::string headerName = filePath;
        bool isStdlib = false;
        if (filePath.front() == '<' && filePath.back() == '>') {
            headerName = filePath.substr(1, filePath.size() - 2);
            isStdlib = true;
        } else {
            isStdlib = StandardLibraryRegistry::isStandardLibraryHeader(filePath);
            if (isStdlib) {
                headerName = filePath;
            }
        }

        if (isStdlib) {
            // Generate EXTERN quads for all functions in this header
            const StdlibHeader* header = StandardLibraryRegistry::findHeader(headerName);
            if (header) {
                for (const auto& func : header->functions) {
                    std::cerr << "[DEBUG] Generating EXTERN for stdlib function: " << func.name << std::endl;
                    // EXTERN: type, "", name
                    quadList.push_back(Quad(OpEnum::EXTERN, func.returnType, "", func.name));
                }
            }
        }
    } else {
        std::cerr << "[WARNING] Unknown statement type in IRGenerator: " << typeid(*statement).name() << std::endl;
    }
}

void IRGenerator::analyzeBlock(NBlock* block) {
    symbolTable.enterScope();

    for (auto& statement : block->statements) {
        if (auto* enumDecl = dynamic_cast<NEnumDeclaration*>(statement)) {
            analyzeEnumDeclaration(enumDecl);
        }
    }

    for (auto& statement : block->statements) {
        if (!dynamic_cast<NEnumDeclaration*>(statement)) {
            analyzeStatement(statement);
        }
    }

    symbolTable.exitScope();
}

void IRGenerator::analyzeVariableDeclaration(NVariableDeclaration* decl) {
    Symbol symbol;
    symbol.name = decl->id.name;
    symbol.type = decl->type.name;
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbol.isConst = decl->isConst;
    symbol.constantValue = 0;

    if (decl->isConst) {
        // 常量必须初始化
        if (!decl->assignmentExpr) {
            symbolTable.insertSymbol(symbol);
            return;
        }
        std::string value = analyzeExpression(decl->assignmentExpr);
        if (value.find_first_not_of("0123456789.-") == std::string::npos) {
            // 值是纯数字
            if (value.find('.') != std::string::npos) {
                symbol.constantValue = static_cast<int64_t>(std::stod(value));
            } else {
                symbol.constantValue = std::stoll(value);
            }
            symbolTable.insertSymbol(symbol);
            return;
        }
        // 常量初始化为非字面量表达式（如变量），生成赋值
        quadList.push_back(Quad(OpEnum::ASSIGN, value, "", decl->id.name));
        symbolTable.insertSymbol(symbol);
        return;
    }

    if (decl->assignmentExpr) {
        std::string value = analyzeExpression(decl->assignmentExpr);
        quadList.push_back(Quad(OpEnum::ASSIGN, value, "", decl->id.name));
    }
    symbolTable.insertSymbol(symbol);
}

void IRGenerator::analyzeArrayDeclaration(NArrayDeclaration* decl) {
    Symbol symbol;
    symbol.name = decl->id.name;
    symbol.type = decl->type.name + "[]";
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbolTable.insertSymbol(symbol);
    
    // 直接检查数组大小是否是常量
    std::string size;
    if (auto* intLiteral = dynamic_cast<NInteger*>(decl->size)) {
        size = longToString(intLiteral->value);
    } else {
        size = analyzeExpression(decl->size);
    }
    quadList.push_back(Quad(OpEnum::ARRAY, size, decl->type.name, decl->id.name));
    
    if (decl->initializer) {
        int index = 0;
        for (auto expr : *decl->initializer) {
            std::string value = analyzeExpression(expr);
            std::string tempIndex = intToString(index);
            quadList.push_back(Quad(OpEnum::ARRAY_STORE, value, tempIndex, decl->id.name));
            index++;
        }
    }
}

void IRGenerator::analyzePointerDeclaration(NPointerDeclaration* decl) {
    Symbol symbol;
    symbol.name = decl->id.name;
    symbol.type = decl->type.name + "*";
    symbol.isFunction = false;
    symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
    symbolTable.insertSymbol(symbol);

    if (decl->assignmentExpr) {
        std::string value = analyzeExpression(decl->assignmentExpr);
        quadList.push_back(Quad(OpEnum::ASSIGN, value, "", decl->id.name));
    }
}

void IRGenerator::analyzeFunctionDeclaration(NFunctionDeclaration* decl) {
    std::cerr << "[DEBUG] analyzeFunctionDeclaration: " << decl->id.name << std::endl;
    Symbol funcSymbol;
    funcSymbol.name = decl->id.name;
    funcSymbol.type = decl->type.name;
    funcSymbol.isFunction = true;
    funcSymbol.isGlobal = true;

    for (auto& param : decl->arguments) {
        funcSymbol.paramTypes.push_back(param->type.name);
    }

    symbolTable.insertSymbol(funcSymbol);

    quadList.push_back(Quad(OpEnum::FUNC, decl->type.name, "", decl->id.name));

    symbolTable.enterScope();

    paramIndex = 0;
    for (auto& param : decl->arguments) {
        Symbol paramSymbol;
        paramSymbol.name = param->id.name;
        paramSymbol.type = param->type.name;
        paramSymbol.isFunction = false;
        paramSymbol.isGlobal = false;
        symbolTable.insertSymbol(paramSymbol);

        std::string paramName = "param_" + std::to_string(paramIndex);
        quadList.push_back(Quad(OpEnum::PARAM, paramName, "", param->id.name));
        paramIndex++;
    }

    analyzeBlock(decl->block);

    quadList.push_back(Quad(OpEnum::ENDFUNC, "", "", decl->id.name));

    symbolTable.exitScope();
}

void IRGenerator::analyzeExpressionStatement(NExpressionStatement* stmt) {
    // 检查表达式是否是解引用赋值操作 *p = value;
    if (auto* assignment = dynamic_cast<NAssignment*>(&stmt->expression)) {
        if (auto* unaryOp = dynamic_cast<NUnaryOperator*>(&assignment->lhs)) {
            if (unaryOp->op == TMUL) {
                analyzeExpression(&stmt->expression);
                return;
            }
        }
    }
    
    // 检查表达式是否是解引用操作
    if (auto* unaryOp = dynamic_cast<NUnaryOperator*>(&stmt->expression)) {
        if (unaryOp->op == TMUL) { // TMUL (pointer dereference)
            // 这是一个单独的解引用表达式语句，如 *p;
            // 不需要生成任何代码，因为这只是读取值并丢弃
            return;
        }
    }
    analyzeExpression(&stmt->expression);
}

void IRGenerator::analyzeReturnStatement(NReturnStatement* stmt) {
    std::string result = analyzeExpression(&stmt->expression);
    quadList.push_back(Quad(OpEnum::RET, "", "", result));
}

void IRGenerator::analyzeIfStatement(NIfStatement* stmt) {
    std::string condition = analyzeExpression(&stmt->condition);
    std::string elseLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    
    quadList.push_back(Quad(OpEnum::JMPF, condition, "", elseLabel));
    
    analyzeBlock(&stmt->trueBlock);
    
    quadList.push_back(Quad(OpEnum::JMP, "", "", endLabel));
    quadList.push_back(Quad(OpEnum::LABEL, "", "", elseLabel));
    
    if (stmt->falseBlock) {
        analyzeBlock(stmt->falseBlock);
    }
    
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
}

void IRGenerator::analyzeWhileStatement(NWhileStatement* stmt) {
    std::string startLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    
    std::string oldStartLabel = currentLoopStartLabel;
    std::string oldEndLabel = currentLoopEndLabel;
    std::string oldIncrementLabel = currentLoopIncrementLabel;
    currentLoopStartLabel = startLabel;
    currentLoopEndLabel = endLabel;
    currentLoopIncrementLabel = "";
    
    quadList.push_back(Quad(OpEnum::LABEL, "", "", startLabel));
    
    std::string condition = analyzeExpression(&stmt->condition);
    quadList.push_back(Quad(OpEnum::JMPF, condition, "", endLabel));
    
    analyzeBlock(&stmt->block);
    
    quadList.push_back(Quad(OpEnum::JMP, "", "", startLabel));
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
    
    currentLoopStartLabel = oldStartLabel;
    currentLoopEndLabel = oldEndLabel;
    currentLoopIncrementLabel = oldIncrementLabel;
}

void IRGenerator::analyzeForStatement(NForStatement* stmt) {
    std::cerr << "[DEBUG] analyzeForStatement: condition=" << (stmt->condition ? "present" : "nullptr")
              << ", increment=" << (stmt->increment ? "present" : "nullptr") << std::endl;

    NExpression* actualCondition = stmt->condition;
    NExpression* actualIncrement = stmt->increment;

    std::string conditionLabel = generateTempVar();
    std::string incrementLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    
    std::string oldStartLabel = currentLoopStartLabel;
    std::string oldEndLabel = currentLoopEndLabel;
    std::string oldIncrementLabel = currentLoopIncrementLabel;
    currentLoopStartLabel = conditionLabel;
    currentLoopEndLabel = endLabel;
    currentLoopIncrementLabel = incrementLabel;

    if (stmt->initialization) {
        analyzeStatement(stmt->initialization);
    }

    quadList.push_back(Quad(OpEnum::JMP, "", "", conditionLabel));

    quadList.push_back(Quad(OpEnum::LABEL, "", "", conditionLabel));

    if (actualCondition) {
        std::string conditionResult = analyzeExpression(actualCondition);
        quadList.push_back(Quad(OpEnum::JMPF, conditionResult, "", endLabel));
    }

    analyzeBlock(&stmt->block);

    quadList.push_back(Quad(OpEnum::LABEL, "", "", incrementLabel));

    if (actualIncrement) {
        analyzeExpression(actualIncrement);
    }

    quadList.push_back(Quad(OpEnum::JMP, "", "", conditionLabel));
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
    
    currentLoopStartLabel = oldStartLabel;
    currentLoopEndLabel = oldEndLabel;
    currentLoopIncrementLabel = oldIncrementLabel;
}

void IRGenerator::analyzeDoWhileStatement(NDoWhileStatement* stmt) {
    std::string startLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    
    std::string oldStartLabel = currentLoopStartLabel;
    std::string oldEndLabel = currentLoopEndLabel;
    std::string oldIncrementLabel = currentLoopIncrementLabel;
    currentLoopStartLabel = startLabel;
    currentLoopEndLabel = endLabel;
    currentLoopIncrementLabel = "";
    
    quadList.push_back(Quad(OpEnum::LABEL, "", "", startLabel));
    
    analyzeBlock(&stmt->block);
    
    std::string condition = analyzeExpression(&stmt->condition);
    quadList.push_back(Quad(OpEnum::JMPT, condition, "", startLabel));
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
    
    currentLoopStartLabel = oldStartLabel;
    currentLoopEndLabel = oldEndLabel;
    currentLoopIncrementLabel = oldIncrementLabel;
}

void IRGenerator::analyzeSwitchStatement(NSwitchStatement* stmt) {
    std::string condition = analyzeExpression(&stmt->condition);
    std::string endLabel = generateTempVar();

    // 保存当前switch的endLabel和condition变量
    std::string oldEndLabel = currentSwitchEndLabel;
    std::string oldCondVar = currentSwitchCondition;
    currentSwitchEndLabel = endLabel;
    currentSwitchCondition = condition;

    // 分析case列表
    analyzeBlock(&stmt->caseList);

    // 恢复之前的endLabel
    currentSwitchEndLabel = oldEndLabel;
    currentSwitchCondition = oldCondVar;

    // 生成结束标签
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
}

void IRGenerator::analyzeCaseStatement(NCaseStatement* stmt) {
    std::string value = analyzeExpression(&stmt->value);
    std::string caseLabel = generateTempVar();
    std::string nextCaseLabel = generateTempVar();
    std::string endLabel = currentSwitchEndLabel;
    std::string condVar = currentSwitchCondition;

    // 生成比较: if (cond != value) goto nextCaseLabel
    std::string neResult = generateTempVar();
    quadList.push_back(Quad(OpEnum::NE, condVar, value, neResult));
    quadList.push_back(Quad(OpEnum::JMPT, neResult, "", nextCaseLabel));

    // 生成case标签
    quadList.push_back(Quad(OpEnum::LABEL, "", "", caseLabel));

    // 分析case语句块
    analyzeBlock(&stmt->statements);

    // 跳转到switch结束
    if (!endLabel.empty()) {
        quadList.push_back(Quad(OpEnum::JMP, "", "", endLabel));
    }

    // 生成下一个case的标签
    quadList.push_back(Quad(OpEnum::LABEL, "", "", nextCaseLabel));
}

void IRGenerator::analyzeDefaultStatement(NDefaultStatement* stmt) {
    std::string defaultLabel = generateTempVar();
    std::string endLabel = currentSwitchEndLabel;

    // 生成default标签
    quadList.push_back(Quad(OpEnum::LABEL, "", "", defaultLabel));

    // 分析default语句块
    analyzeBlock(&stmt->statements);

    // 跳转到switch结束
    if (!endLabel.empty()) {
        quadList.push_back(Quad(OpEnum::JMP, "", "", endLabel));
    }
}

void IRGenerator::analyzeContinueStatement(NContinueStatement* stmt) {
    std::string targetLabel = currentLoopIncrementLabel.empty() ? currentLoopStartLabel : currentLoopIncrementLabel;
    if (targetLabel.empty()) {
        std::cerr << "Error: continue statement outside of loop" << std::endl;
        hasErrors = true;
        return;
    }
    quadList.push_back(Quad(OpEnum::JMP, "", "", targetLabel));
}

void IRGenerator::analyzeBreakStatement(NBreakStatement* stmt) {
    if (!currentSwitchEndLabel.empty()) {
        quadList.push_back(Quad(OpEnum::JMP, "", "", currentSwitchEndLabel));
    } else if (!currentLoopEndLabel.empty()) {
        quadList.push_back(Quad(OpEnum::JMP, "", "", currentLoopEndLabel));
    } else {
        std::cerr << "Error: break statement outside of loop or switch" << std::endl;
        hasErrors = true;
    }
}

void IRGenerator::analyzeEnumDeclaration(NEnumDeclaration* decl) {
    // 枚举值的默认值从0开始
    int enumValue = 0;
    
    // 分析枚举项
    for (auto& item : decl->items.statements) {
        if (auto* enumItem = dynamic_cast<NEnumItem*>(item)) {
            // 分析枚举项的值
            if (enumItem->value) {
                // 如果有显式值，使用该值
                if (auto* intLiteral = dynamic_cast<NInteger*>(enumItem->value)) {
                    // 直接获取整数值
                    enumValue = intLiteral->value;
                } else if (auto* id = dynamic_cast<NIdentifier*>(enumItem->value)) {
                    // 处理枚举项引用其他枚举项的情况
                    Symbol* symbol = symbolTable.findSymbol(id->name);
                    if (symbol && symbol->isEnum) {
                        enumValue = symbol->constantValue;
                    }
                } else {
                    // 其他表达式类型，暂时设置为0
                    enumValue = 0;
                }
            }
            
            // 为枚举项添加到当前作用域
            Symbol symbol;
            symbol.name = enumItem->name.name;
            symbol.type = "int";
            symbol.isFunction = false;
            symbol.isGlobal = (symbolTable.getScopeLevel() == 1);
            symbol.constantValue = enumValue;
            symbol.isEnum = true;
            symbolTable.insertSymbol(symbol);
            
            // 递增默认值
            enumValue++;
        }
    }
}

void IRGenerator::analyzeEnumItem(NEnumItem* item) {
    // 枚举项的分析在analyzeEnumDeclaration中处理
}


std::string IRGenerator::analyzeExpression(NExpression* expression) {
    if (auto* binaryOp = dynamic_cast<NBinaryOperator*>(expression)) {
        return analyzeBinaryOperator(binaryOp);
    } else if (auto* ternaryOp = dynamic_cast<NTernaryOperator*>(expression)) {
        return analyzeTernaryOperator(ternaryOp);
    } else if (auto* unaryOp = dynamic_cast<NUnaryOperator*>(expression)) {
        return analyzeUnaryOperator(unaryOp);
    } else if (auto* castOp = dynamic_cast<NCastOperator*>(expression)) {
        return analyzeCastOperator(castOp);
    } else if (auto* assignment = dynamic_cast<NAssignment*>(expression)) {
        return analyzeAssignment(assignment);
    } else if (auto* methodCall = dynamic_cast<NMethodCall*>(expression)) {
        return analyzeMethodCall(methodCall);
    } else if (auto* id = dynamic_cast<NIdentifier*>(expression)) {
        return analyzeIdentifier(id);
    } else if (auto* arrayAccess = dynamic_cast<NArrayAccess*>(expression)) {
        return analyzeArrayAccess(arrayAccess);
    } else if (auto* memberAccess = dynamic_cast<NMemberAccess*>(expression)) {
        return analyzeMemberAccess(memberAccess);
    } else if (auto* throwExpr = dynamic_cast<NThrowExpression*>(expression)) {
        return analyzeThrowExpression(throwExpr);
    } else if (auto* intLiteral = dynamic_cast<NInteger*>(expression)) {
        return longToString(intLiteral->value);
    } else if (auto* doubleLiteral = dynamic_cast<NDouble*>(expression)) {
        std::string temp = generateTempVar();
        quadList.push_back(Quad(OpEnum::ASSIGN, doubleToString(doubleLiteral->value), "", temp));
        return temp;
    } else if (auto* stringLiteral = dynamic_cast<NString*>(expression)) {
        std::string temp = generateTempVar();
        quadList.push_back(Quad(OpEnum::ASSIGN, stringLiteral->value, "", temp));
        // 将临时变量标记为字符串
        stringVariables[temp] = true;
        return temp;
    }
    return "";
}

// 辅助函数：检查一个值是否是字符串
bool IRGenerator::isStringValue(const std::string& value) {
    if (value.length() > 0 && value[0] == '"') {
        return true;
    }
    
    if (stringVariables.find(value) != stringVariables.end() && stringVariables[value]) {
        return true;
    }
    
    for (auto& quad : quadList) {
        if (quad.getResult() == value && quad.getOp() == OpEnum::ASSIGN) {
            return isStringValue(quad.getArg1());
        }
    }

    return false;
}

bool IsVariadicFunction(const std::string& funcName) {
    static std::set<std::string> variadicFunctions = {
        "printf", "scanf", "sprintf", "snprintf", "fprintf", "sscanf", "fscanf",
        "vprintf", "vscanf", "vsprintf", "vsnprintf", "vfprintf", "vsscanf", "vfscanf",
        "execl", "execle", "execlp", "execvp", "execv", "execve",
        "open", "read", "write"  // Unix-style variadic
    };
    return variadicFunctions.find(funcName) != variadicFunctions.end();
}

bool IRGenerator::isDoubleExpression(NExpression* expression) {
    if (dynamic_cast<NDouble*>(expression)) {
        return true;
    }
    
    if (auto* id = dynamic_cast<NIdentifier*>(expression)) {
        Symbol* symbol = symbolTable.findSymbol(id->name);
        if (symbol && (symbol->type == "double" || symbol->type == "float")) {
            return true;
        }
    }
    
    if (auto* binaryOp = dynamic_cast<NBinaryOperator*>(expression)) {
        return isDoubleExpression(&binaryOp->lhs) || isDoubleExpression(&binaryOp->rhs);
    }
    
    if (auto* unaryOp = dynamic_cast<NUnaryOperator*>(expression)) {
        return isDoubleExpression(&unaryOp->expr);
    }
    
    if (auto* methodCall = dynamic_cast<NMethodCall*>(expression)) {
        std::string funcName = methodCall->id.name;
        if (funcName == "sqrt" || funcName == "pow" || funcName == "sin" ||
            funcName == "cos" || funcName == "tan" || funcName == "fabs" ||
            funcName == "exp" || funcName == "log" || funcName == "log10" ||
            funcName == "asin" || funcName == "acos" || funcName == "atan" ||
            funcName == "atan2" || funcName == "floor" || funcName == "ceil" ||
            funcName == "round" || funcName == "fmod") {
            return true;
        }
    }
    
    return false;
}

std::string IRGenerator::analyzeBinaryOperator(NBinaryOperator* op) {
    std::string left = analyzeExpression(&op->lhs);
    std::string right = analyzeExpression(&op->rhs);
    std::string temp = generateTempVar();

    if (std::find(knownVariables.begin(), knownVariables.end(), temp) == knownVariables.end()) {
        knownVariables.push_back(temp);
    }

    OpEnum opCode;
    switch (op->op) {
        case TPLUS: opCode = OpEnum::ADD; break;
        case TMINUS: opCode = OpEnum::SUB; break;
        case TMUL: opCode = OpEnum::MUL; break;
        case TDIV: opCode = OpEnum::DIV; break;
        case TMOD: opCode = OpEnum::MOD; break;
        case TCLT: opCode = OpEnum::LT; break;
        case TCLE: opCode = OpEnum::LE; break;
        case TCGT: opCode = OpEnum::GT; break;
        case TCGE: opCode = OpEnum::GE; break;
        case TCEQ: opCode = OpEnum::EQ; break;
        case TCNE: opCode = OpEnum::NE; break;
        case TXOR: opCode = OpEnum::XOR; break;
        case TBITAND: opCode = OpEnum::AND; break;
        case TBITOR: opCode = OpEnum::OR; break;
        case TLSHIFT: opCode = OpEnum::LSHIFT; break;
        case TRSHIFT: opCode = OpEnum::RSHIFT; break;
        case TNOTBIT: opCode = OpEnum::LOGICAL_NOT; break;
        case TAND: opCode = OpEnum::LOGICAL_AND; break;
        case TOR: opCode = OpEnum::LOGICAL_OR; break;
        case TNOT: opCode = OpEnum::NOT; break;
        case TCOMMA: return right;
        default: opCode = OpEnum::ADD;
    }
    
    // 处理字符串拼接
    if (opCode == OpEnum::ADD) {
        // 检查是否是字符串拼接
        bool isStringLeft = isStringValue(left);
        bool isStringRight = isStringValue(right);
        
        // 如果任意一个操作数是字符串，使用字符串拼接操作
        if (isStringLeft || isStringRight) {
            opCode = OpEnum::STRING_CONCAT;
            // 将生成的临时变量标记为字符串
            stringVariables[temp] = true;
        }
    }
    
    if (opCode == OpEnum::NOT || opCode == OpEnum::LOGICAL_NOT) {
        // 对于NOT操作，右操作数是实际的操作数
        quadList.push_back(Quad(opCode, right, "", temp));
    } else {
        quadList.push_back(Quad(opCode, left, right, temp));
    }
    return temp;
}

std::string IRGenerator::analyzeTernaryOperator(NTernaryOperator* op) {
    std::string elseLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    std::string temp = generateTempVar();
    
    if (std::find(knownVariables.begin(), knownVariables.end(), temp) == knownVariables.end()) {
        knownVariables.push_back(temp);
    }
    
    std::string conditionResult = analyzeExpression(&op->condition);
    quadList.push_back(Quad(OpEnum::ASSIGN, conditionResult, "", temp));
    quadList.push_back(Quad(OpEnum::JMPF, temp, "", elseLabel));
    
    std::string trueResult = analyzeExpression(&op->trueExpr);
    quadList.push_back(Quad(OpEnum::ASSIGN, trueResult, "", temp));
    quadList.push_back(Quad(OpEnum::JMP, "", "", endLabel));
    
    quadList.push_back(Quad(OpEnum::LABEL, "", "", elseLabel));
    std::string falseResult = analyzeExpression(&op->falseExpr);
    quadList.push_back(Quad(OpEnum::ASSIGN, falseResult, "", temp));
    
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
    return temp;
}

std::string IRGenerator::analyzeAssignment(NAssignment* assignment) {
    // 分析右值
    std::string value = analyzeExpression(&assignment->rhs);
    
    // 检查左值是否是解引用操作
    if (auto* unaryOp = dynamic_cast<NUnaryOperator*>(&assignment->lhs)) {
        if (unaryOp->op == TMUL) { // TMUL (pointer dereference)
            // 处理指针解引用赋值：*p = value
            std::string ptr = analyzeExpression(&unaryOp->expr);
            // 生成 STORE_DEREFERENCE 操作来存储值到指针指向的地址
            quadList.push_back(Quad(OpEnum::STORE_DEREFERENCE, ptr, value, ""));
            return value;
        }
    }
    
    // 检查左值是否是数组访问
    if (auto* arrayAccess = dynamic_cast<NArrayAccess*>(&assignment->lhs)) {
        // 处理数组访问赋值：arr[index] = value
        std::string index = analyzeExpression(&arrayAccess->index);
        // 生成 ARRAY_STORE 操作来存储值到数组元素
        quadList.push_back(Quad(OpEnum::ARRAY_STORE, value, index, arrayAccess->id.name));
        return value;
    }
    
    // 检查左值是否是成员访问
    if (auto* memberAccess = dynamic_cast<NMemberAccess*>(&assignment->lhs)) {
        // 处理成员访问赋值：obj.member = value
        std::string object = analyzeExpression(&memberAccess->object);
        
        // 检查对象变量是否已经被分配，如果没有，先分配一个临时变量来记录
        // 这里我们把对象变量名和成员名组合成一个伪变量名来追踪
        std::string structVarName = object;
        
        // 生成 MEMBER_STORE 操作
        quadList.push_back(Quad(OpEnum::MEMBER_STORE, structVarName, memberAccess->member.name, value));
        return value;
    }
    
    // 检查左值是否是标识符
    if (auto* id = dynamic_cast<NIdentifier*>(&assignment->lhs)) {
        // 处理普通变量赋值
        if (std::find(knownVariables.begin(), knownVariables.end(), id->name) == knownVariables.end()) {
            knownVariables.push_back(id->name);
        }
        quadList.push_back(Quad(OpEnum::ASSIGN, value, "", id->name));
        
        // 检查右值是否是字符串，如果是，将左值变量标记为字符串
        if (value.length() > 0 && value[0] == '"') {
            stringVariables[id->name] = true;
        }
        // 检查右值是否是临时变量，并且该临时变量是字符串
        else if (stringVariables.find(value) != stringVariables.end() && stringVariables[value]) {
            stringVariables[id->name] = true;
        }
        
        return id->name;
    }
    
    // 处理其他类型的左值表达式
    std::string lhs = analyzeExpression(&assignment->lhs);
    quadList.push_back(Quad(OpEnum::ASSIGN, value, "", lhs));
    return lhs;
}

std::string IRGenerator::analyzeMethodCall(NMethodCall* call) {
    int totalArgs = static_cast<int>(call->arguments.size());

    std::vector<std::string> argTemps(totalArgs);
    std::vector<bool> argIsDouble(totalArgs);

    for (int i = 0; i < totalArgs; i++) {
        argIsDouble[i] = isDoubleExpression(call->arguments[i]);
        argTemps[i] = generateParamEvalVar(i);
        std::string exprResult = analyzeExpression(call->arguments[i]);
        quadList.push_back(Quad(OpEnum::ASSIGN, exprResult, "", argTemps[i]));
    }

    for (int i = 0; i < totalArgs; i++) {
        std::string paramName = "param_" + std::to_string(i);
        quadList.push_back(Quad(OpEnum::ASSIGN, argTemps[i], "", paramName));
    }

    std::string temp = generateTempVar();
    quadList.push_back(Quad(OpEnum::CALL, call->id.name, std::to_string(totalArgs), temp));
    return temp;
}

std::string IRGenerator::analyzeIdentifier(NIdentifier* id) {
    Symbol* symbol = symbolTable.findSymbol(id->name);
    if (symbol && symbol->isEnum) {
        return intToString(symbol->constantValue);
    }

    if (symbol && symbol->isConst) {
        return intToString(symbol->constantValue);
    }

    if (std::find(knownVariables.begin(), knownVariables.end(), id->name) == knownVariables.end()) {
        knownVariables.push_back(id->name);
    }
    return id->name;
}

std::string IRGenerator::analyzeArrayAccess(NArrayAccess* access) {
    std::string index = analyzeExpression(&access->index);
    std::string temp = generateTempVar();
    quadList.push_back(Quad(OpEnum::ARRAY_LOAD, access->id.name, index, temp));
    return temp;
}

std::string IRGenerator::analyzeMemberAccess(NMemberAccess* access) {
    std::string object = analyzeExpression(&access->object);
    std::string temp = generateTempVar();
    quadList.push_back(Quad(OpEnum::MEMBER_ACCESS, object, access->member.name, temp));
    return temp;
}

std::string IRGenerator::analyzeUnaryOperator(NUnaryOperator* op) {
    std::string expr = analyzeExpression(&op->expr);
    std::string temp = generateTempVar();
    
    if (op->op == TBITAND) { // TBITAND (address-of)
        quadList.push_back(Quad(OpEnum::ADDRESS_OF, expr, "", temp));
    } else if (op->op == TMUL) { // TMUL (pointer dereference)
        quadList.push_back(Quad(OpEnum::DEREFERENCE, expr, "", temp));
    } else if (op->op == TNOTBIT) { // ~ (bitwise NOT)
        quadList.push_back(Quad(OpEnum::NOT, expr, "", temp));
    } else if (op->op == TNOT) { // ! (logical NOT)
        quadList.push_back(Quad(OpEnum::LOGICAL_NOT, expr, "", temp));
    } else if (op->op == TMINUS) { // - (unary minus)
        if (auto* doubleLiteral = dynamic_cast<NDouble*>(&op->expr)) {
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::ASSIGN, doubleToString(-doubleLiteral->value), "", temp));
            return temp;
        } else if (auto* intLiteral = dynamic_cast<NInteger*>(&op->expr)) {
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::ASSIGN, longToString(-intLiteral->value), "", temp));
            return temp;
        } else {
            std::string expr = analyzeExpression(&op->expr);
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::SUB, "", expr, temp));
            return temp;
        }
    } else if (op->op == TPLUS) { // + (unary plus)
        if (auto* doubleLiteral = dynamic_cast<NDouble*>(&op->expr)) {
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::ASSIGN, doubleToString(doubleLiteral->value), "", temp));
            return temp;
        } else if (auto* intLiteral = dynamic_cast<NInteger*>(&op->expr)) {
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::ASSIGN, longToString(intLiteral->value), "", temp));
            return temp;
        } else {
            std::string expr = analyzeExpression(&op->expr);
            std::string temp = generateTempVar();
            quadList.push_back(Quad(OpEnum::ADD, "", expr, temp));
            return temp;
        }
    } else if (op->op == TINC) { // ++ (prefix increment)
        quadList.push_back(Quad(OpEnum::ADD, expr, "1", temp));
        quadList.push_back(Quad(OpEnum::ASSIGN, temp, "", expr));
    } else if (op->op == TDEC) { // -- (prefix decrement)
        quadList.push_back(Quad(OpEnum::SUB, expr, "1", temp));
        quadList.push_back(Quad(OpEnum::ASSIGN, temp, "", expr));
    }
    
    return temp;
}

std::string IRGenerator::analyzeCastOperator(NCastOperator* op) {
    std::cerr << "[DEBUG] analyzeCastOperator: targetType=" << op->targetType << std::endl;
    std::string expr = analyzeExpression(&op->expr);
    std::string temp = generateTempVar();
    quadList.push_back(Quad(OpEnum::CAST, op->targetType, expr, temp));
    std::cerr << "[DEBUG] Cast quad: CAST " << op->targetType << ", " << expr << " -> " << temp << std::endl;
    return temp;
}

void IRGenerator::analyzeTryCatchStatement(NTryCatchStatement* stmt) {
    std::cerr << "[DEBUG] analyzeTryCatchStatement: entered" << std::endl;
    
    // 生成try块代码
    std::string tryLabel = generateTempVar();
    std::string catchLabel = generateTempVar();
    std::string endLabel = generateTempVar();
    
    // 标记try块开始
    quadList.push_back(Quad(OpEnum::LABEL, "", "", tryLabel));
    
    // 分析try块
    std::cerr << "[DEBUG] analyzeTryCatchStatement: analyzing try block" << std::endl;
    analyzeBlock(stmt->tryBlock);
    
    // 跳转到try-catch结束
    quadList.push_back(Quad(OpEnum::JMP, "", "", endLabel));
    
    // 标记catch块开始
    quadList.push_back(Quad(OpEnum::LABEL, "", "", catchLabel));
    
    // 分析catch块
    for (auto* catchBlock : stmt->catchBlocks) {
        if (catchBlock->isEllipsis) {
            // 捕获所有异常
            std::cerr << "[DEBUG] analyzeTryCatchStatement: catch (...)" << std::endl;
        } else {
            // 捕获特定类型的异常
            std::cerr << "[DEBUG] analyzeTryCatchStatement: catch (" << catchBlock->type->name << " " << catchBlock->id->name << ")" << std::endl;
            
            // 为catch块参数分配变量
            Symbol symbol;
            symbol.name = catchBlock->id->name;
            symbol.type = catchBlock->type->name;
            symbol.isFunction = false;
            symbol.isGlobal = false;
            symbolTable.insertSymbol(symbol);
            
            // 生成异常值的赋值指令
            // 假设异常值在 RAX 寄存器中
            quadList.push_back(Quad(OpEnum::ASSIGN, "rax", "", catchBlock->id->name));
        }
        
        // 分析catch块内容
        std::cerr << "[DEBUG] analyzeTryCatchStatement: analyzing catch block" << std::endl;
        analyzeBlock(catchBlock->block);
    }
    
    // 标记try-catch结束
    quadList.push_back(Quad(OpEnum::LABEL, "", "", endLabel));
}

std::string IRGenerator::analyzeThrowExpression(NThrowExpression* expr) {
    std::cerr << "[DEBUG] analyzeThrowExpression: entered" << std::endl;
    
    // 分析抛出的表达式
    std::string thrownValue = analyzeExpression(expr->expression);
    
    // 生成THROW四元式
    quadList.push_back(Quad(OpEnum::THROW, thrownValue, "", ""));
    
    // 返回一个临时变量（虽然throw表达式不会有返回值）
    std::string temp = generateTempVar();
    return temp;
}

} // namespace cse