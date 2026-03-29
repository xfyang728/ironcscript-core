#ifndef CSE_IR_GENERATOR_H
#define CSE_IR_GENERATOR_H

#include <vector>
#include <map>
#include <string>
#include <list>
#include "frontend/parser/node.h"
#include "frontend/generated/CScriptParser.h"
#include "Quad.h"
#include "../frontend/semantic/SymbolTable.h"

namespace cse {

class IRGenerator {
public:
    IRGenerator(SymbolTable& symbolTable);
    ~IRGenerator();

    void generateIR(NBlock& root);
    const std::list<Quad>& getQuadList() const;
    const std::vector<std::string>& getKnownVariables() const;
    void error(const std::string& message, const Node* node = nullptr);

private:
    SymbolTable& symbolTable;
    std::list<Quad> quadList;
    std::vector<std::string> knownVariables;
    std::map<std::string, bool> stringVariables;
    bool hasErrors;
    int tempVarCounter;
    int paramIndex;
    std::string currentSwitchEndLabel;
    std::string currentSwitchCondition;

    std::string currentLoopStartLabel;
    std::string currentLoopEndLabel;
    std::string currentLoopIncrementLabel;

    std::string generateTempVar();
    void analyzeStatement(NStatement* statement);
    std::string analyzeExpression(NExpression* expression);
    void analyzeVariableDeclaration(NVariableDeclaration* decl);
    void analyzeArrayDeclaration(NArrayDeclaration* decl);
    void analyzePointerDeclaration(NPointerDeclaration* decl);
    void analyzeFunctionDeclaration(NFunctionDeclaration* decl);
    void analyzeExpressionStatement(NExpressionStatement* stmt);
    void analyzeReturnStatement(NReturnStatement* stmt);
    void analyzeIfStatement(NIfStatement* stmt);
    void analyzeWhileStatement(NWhileStatement* stmt);
    void analyzeForStatement(NForStatement* stmt);
    void analyzeDoWhileStatement(NDoWhileStatement* stmt);
    void analyzeSwitchStatement(NSwitchStatement* stmt);
    void analyzeCaseStatement(NCaseStatement* stmt);
    void analyzeDefaultStatement(NDefaultStatement* stmt);
    void analyzeContinueStatement(NContinueStatement* stmt);
    void analyzeBreakStatement(NBreakStatement* stmt);
    void analyzeTryCatchStatement(NTryCatchStatement* stmt);
    std::string analyzeThrowExpression(NThrowExpression* expr);
    void analyzeEnumDeclaration(NEnumDeclaration* decl);
    void analyzeEnumItem(NEnumItem* item);
    std::string analyzeBinaryOperator(NBinaryOperator* op);
    std::string analyzeTernaryOperator(NTernaryOperator* op);
    std::string analyzeUnaryOperator(NUnaryOperator* op);
    std::string analyzeCastOperator(NCastOperator* op);
    std::string analyzeAssignment(NAssignment* assignment);
    std::string analyzeMethodCall(NMethodCall* call);
    std::string analyzeIdentifier(NIdentifier* id);
    std::string analyzeArrayAccess(NArrayAccess* access);
    std::string analyzeMemberAccess(NMemberAccess* access);
    bool isStringValue(const std::string& value);
    bool isDoubleExpression(NExpression* expression);
    void analyzeBlock(NBlock* block);
};

}

#endif
