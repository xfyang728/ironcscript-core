#ifndef CSE_SEMANTIC_ANALYZER_H
#define CSE_SEMANTIC_ANALYZER_H

#include <string>
#include <vector>
#include "frontend/parser/node.h"
#include "frontend/generated/CScriptParser.h"
#include "SymbolTable.h"
#include "module/ModuleManager.h"

namespace cse {

class SemanticAnalyzer {
public:
    SemanticAnalyzer(SymbolTable& symbolTable, ModuleManager* moduleManager = nullptr);
    ~SemanticAnalyzer();

    void setCurrentBlock(NBlock* block);
    void setSourceFile(const std::string& file) { currentSourceFile = file; }
    const std::string& getSourceFile() const { return currentSourceFile; }
    bool analyze(NBlock& root);

    void error(const std::string& message, const Node* node);
    void debug(const std::string& message, const Node* node);

private:
    SymbolTable& symbolTable;
    ModuleManager* moduleManager;
    bool hasErrors;
    std::string currentFunctionReturnType;
    std::string currentSourceFile;
    NBlock* currentBlock;

    void analyzeStatement(NStatement* statement);
    void analyzeExpression(NExpression* expression);

    void analyzeVariableDeclaration(NVariableDeclaration* decl);
    void analyzePointerDeclaration(NPointerDeclaration* decl);
    void analyzeArrayDeclaration(NArrayDeclaration* decl);
    void analyzeFunctionDeclaration(NFunctionDeclaration* decl);
    void analyzeExpressionStatement(NExpressionStatement* stmt);
    void analyzeReturnStatement(NReturnStatement* stmt);
    void analyzeIfStatement(NIfStatement* stmt);
    void analyzeWhileStatement(NWhileStatement* stmt);
    void analyzeForStatement(NForStatement* stmt);
    void analyzeDoWhileStatement(NDoWhileStatement* stmt);

    void analyzeBinaryOperator(NBinaryOperator* op);
    void analyzeTernaryOperator(NTernaryOperator* op);
    void analyzeAssignment(NAssignment* assignment);
    void analyzeMethodCall(NMethodCall* call);
    void analyzeIdentifier(NIdentifier* id);
    void analyzeArrayAccess(NArrayAccess* arr);
    void analyzeMemberAccess(NMemberAccess* member);
    void analyzeBlock(NBlock* block);
    void analyzeEnumDeclaration(NEnumDeclaration* decl);
    void analyzeImportStatement(NImportStatement* stmt);
    void analyzeIncludeStatement(NIncludeStatement* stmt);

    void registerStandardLibraryFunction(const std::string& name, const std::string& returnType,
                                       const std::vector<std::string>& paramTypes, bool isVariadic);

    std::string inferType(NExpression* expression);
    bool checkTypeCompatibility(const std::string& type1, const std::string& type2);
    bool checkAssignmentCompatibility(const std::string& lhsType, const std::string& rhsType);
    int64_t evaluateConstExpression(NExpression* expression);
};

}

#endif
