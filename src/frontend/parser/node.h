#ifndef CSE_NODE_H
#define CSE_NODE_H

#include <iostream>
#include <vector>

namespace cse {
    class Value;
    class CodeGenContext;
    class NStatement;
    class NExpression;
    class NVariableDeclaration;
    
    typedef std::vector<NStatement*> StatementList;
    typedef std::vector<NExpression*> ExpressionList;
    typedef std::vector<NVariableDeclaration*> VariableList;
    
    class Node {
    public:
        virtual ~Node() {}
    };
    
    class NExpression : public Node {
    };
    
    class NStatement : public Node {
    };
    
    class NInteger : public NExpression {
    public:
        long long value;
        NInteger(long long value) : value(value) { }
    };
    
    class NDouble : public NExpression {
    public:
        double value;
        NDouble(double value) : value(value) { }
    };
    
    class NString : public NExpression {
    public:
        std::string value;
        NString(const std::string& value) : value(value) { }
    };
    
    class NIdentifier : public NExpression {
    public:
        std::string name;
        NIdentifier(const std::string& name) : name(name) { }
    };
    
    class NMethodCall : public NExpression {
    public:
        const NIdentifier& id;
        ExpressionList arguments;
        NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
            id(id), arguments(arguments) { }
        NMethodCall(const NIdentifier& id) : id(id) { }
    };
    
    class NBinaryOperator : public NExpression {
    public:
        int op;
        NExpression& lhs;
        NExpression& rhs;
        NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
            lhs(lhs), rhs(rhs), op(op) { }
    };
    
    class NTernaryOperator : public NExpression {
    public:
        NExpression& condition;
        NExpression& trueExpr;
        NExpression& falseExpr;
        NTernaryOperator(NExpression& condition, NExpression& trueExpr, NExpression& falseExpr) :
            condition(condition), trueExpr(trueExpr), falseExpr(falseExpr) { }
    };

    class NAssignment : public NExpression {
    public:
        NExpression& lhs;
        NExpression& rhs;
        NAssignment(NExpression& lhs, NExpression& rhs) :
            lhs(lhs), rhs(rhs) { }
    };

    class NBlock : public NExpression {
    public:
        StatementList statements;
        NBlock() { }
    };
    
    class NExpressionStatement : public NStatement {
    public:
        NExpression& expression;
        NExpressionStatement(NExpression& expression) :
            expression(expression) { }
    };
    
    class NReturnStatement : public NStatement {
    public:
        NExpression& expression;
        NReturnStatement(NExpression& expression) :
            expression(expression) { }
    };
    
    class NVariableDeclaration : public NStatement {
    public:
        const NIdentifier& type;
        NIdentifier& id;
        NExpression* assignmentExpr;
        bool isConst;
        NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
            type(type), id(id), isConst(false) {
            assignmentExpr = NULL;
        }
        NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression* assignmentExpr) :
            type(type), id(id), assignmentExpr(assignmentExpr), isConst(false) { }
        NVariableDeclaration(NIdentifier& type, NIdentifier& id) :
            type(type), id(id), isConst(false) {
            assignmentExpr = NULL;
        }
        NVariableDeclaration(NIdentifier& type, NIdentifier& id, NExpression* assignmentExpr) :
            type(type), id(id), assignmentExpr(assignmentExpr), isConst(false) { }
    };
    
    class NArrayDeclaration : public NStatement {
    public:
        const NIdentifier& type;
        NIdentifier& id;
        NExpression* size;
        ExpressionList* initializer;
        NArrayDeclaration(const NIdentifier& type, NIdentifier& id, NExpression* size) :
            type(type), id(id), size(size) {
            initializer = NULL;
        }
        NArrayDeclaration(const NIdentifier& type, NIdentifier& id, NExpression* size, ExpressionList* initializer) :
            type(type), id(id), size(size), initializer(initializer) { }
    };
    
    class NPointerDeclaration : public NStatement {
    public:
        const NIdentifier& type;
        NIdentifier& id;
        NExpression* assignmentExpr;
        NPointerDeclaration(const NIdentifier& type, NIdentifier& id) :
            type(type), id(id) {
            assignmentExpr = NULL;
        }
        NPointerDeclaration(const NIdentifier& type, NIdentifier& id, NExpression* assignmentExpr) :
            type(type), id(id), assignmentExpr(assignmentExpr) { }
    };
    
    class NUnaryOperator : public NExpression {
    public:
        int op;
        NExpression& expr;
        NUnaryOperator(int op, NExpression& expr) :
            op(op), expr(expr) { }
    };

    class NCastOperator : public NExpression {
    public:
        std::string targetType;
        NExpression& expr;
        NCastOperator(const std::string& targetType, NExpression& expr) :
            targetType(targetType), expr(expr) { }
    };
    
    class NStructDeclaration : public NStatement {
    public:
        const NIdentifier& name;
        NBlock& members;
        NStructDeclaration(const NIdentifier& name, NBlock& members) :
            name(name), members(members) { }
    };
    
    class NUnionDeclaration : public NStatement {
    public:
        const NIdentifier& name;
        NBlock& members;
        NUnionDeclaration(const NIdentifier& name, NBlock& members) :
            name(name), members(members) { }
    };
    
    class NEnumDeclaration : public NStatement {
    public:
        const NIdentifier& name;
        NBlock& items;
        NEnumDeclaration(const NIdentifier& name, NBlock& items) :
            name(name), items(items) { }
    };
    
    class NEnumItem : public NStatement {
    public:
        NIdentifier& name;
        NExpression* value;
        NEnumItem(NIdentifier& name, NExpression* value) :
            name(name), value(value) { }
    };
    
    class NMemberAccess : public NExpression {
    public:
        NExpression& object;
        NIdentifier& member;
        NMemberAccess(NExpression& object, NIdentifier& member) :
            object(object), member(member) { }
    };
    
    class NExternDeclaration : public NStatement {
    public:
        const NIdentifier& type;
        const NIdentifier& id;
        VariableList arguments;
        NExternDeclaration(const NIdentifier& type, const NIdentifier& id,
            const VariableList& arguments) :
            type(type), id(id), arguments(arguments) {}
    };

    class NRegisterCallbackStatement : public NStatement {
    public:
        const NIdentifier& callbackName;
        const NIdentifier& targetName;
        VariableList arguments;
        NRegisterCallbackStatement(const NIdentifier& callbackName, const NIdentifier& targetName,
            const VariableList& arguments = {}) :
            callbackName(callbackName), targetName(targetName), arguments(arguments) {}
    };

    class NFunctionDeclaration : public NStatement {
    public:
        const NIdentifier& type;
        const NIdentifier& id;
        VariableList arguments;
        NBlock* block;
        NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id,
            const VariableList& arguments, NBlock* block) :
            type(type), id(id), arguments(arguments), block(block) { }
        ~NFunctionDeclaration() {
            if (block) {
                for (auto stmt : block->statements) {
                    delete stmt;
                }
                delete block;
            }
        }
    };
    
    class NIfStatement : public NStatement {
    public:
        NExpression& condition;
        NBlock& trueBlock;
        NBlock* falseBlock;
        NIfStatement(NExpression& condition, NBlock& trueBlock, NBlock* falseBlock = NULL) :
            condition(condition), trueBlock(trueBlock), falseBlock(falseBlock) { }
    };
    
    class NWhileStatement : public NStatement {
    public:
        NExpression& condition;
        NBlock& block;
        NWhileStatement(NExpression& condition, NBlock& block) :
            condition(condition), block(block) { }
    };
    
    class NForStatement : public NStatement {
    public:
        NStatement* initialization;
        NExpression* condition;
        NExpression* increment;
        NExpression* loopEnd;
        NBlock& block;
        NForStatement(NStatement* initialization, NExpression* condition, NExpression* increment, NBlock& block) :
            initialization(initialization), condition(condition), increment(increment), block(block) { }
        NForStatement(NStatement* initialization, NExpression* condition, NExpression* increment, NExpression* loopEnd, NBlock& block) :
            initialization(initialization), condition(condition), increment(increment), loopEnd(loopEnd), block(block) { }
        NForStatement(NExpression* initialization, NExpression* condition, NExpression* increment, NExpression* loopEnd, NBlock& block) :
            initialization(initialization ? new NExpressionStatement(*initialization) : nullptr), condition(condition), increment(increment), loopEnd(loopEnd), block(block) { }
    };
    
    class NDoWhileStatement : public NStatement {
    public:
        NBlock& block;
        NExpression& condition;
        NDoWhileStatement(NBlock& block, NExpression& condition) :
            block(block), condition(condition) { }
    };
    
    class NArrayAccess : public NExpression {
    public:
        NIdentifier& id;
        NExpression& index;
        NArrayAccess(NIdentifier& id, NExpression& index) :
            id(id), index(index) { }
    };
    
    class NSwitchStatement : public NStatement {
    public:
        NExpression& condition;
        NBlock& caseList;
        NSwitchStatement(NExpression& condition, NBlock& caseList) :
            condition(condition), caseList(caseList) { }
    };
    
    class NCaseStatement : public NStatement {
    public:
        NExpression& value;
        NBlock& statements;
        NCaseStatement(NExpression& value, NBlock& statements) :
            value(value), statements(statements) { }
    };
    
    class NDefaultStatement : public NStatement {
    public:
        NBlock& statements;
        NDefaultStatement(NBlock& statements) :
            statements(statements) { }
    };
    
    class NContinueStatement : public NStatement {
    public:
        NContinueStatement() { }
    };

    class NBreakStatement : public NStatement {
    public:
        NBreakStatement() { }
    };
    
    class NCatchBlock : public Node {
    public:
        NIdentifier* type;
        NIdentifier* id;
        NBlock* block;
        bool isEllipsis;
        
        NCatchBlock(NIdentifier* type, NIdentifier* id, NBlock* block) :
            type(type), id(id), block(block), isEllipsis(false) { }
        
        NCatchBlock(NBlock* block) :
            type(nullptr), id(nullptr), block(block), isEllipsis(true) { }
    };
    
    class NTryCatchStatement : public NStatement {
    public:
        NBlock* tryBlock;
        std::vector<NCatchBlock*> catchBlocks;
        
        NTryCatchStatement(NBlock* tryBlock, const std::vector<NCatchBlock*>& catchBlocks) :
            tryBlock(tryBlock), catchBlocks(catchBlocks) { }
    };
    
    class NThrowExpression : public NExpression {
    public:
        NExpression* expression;
        
        NThrowExpression(NExpression* expression) :
            expression(expression) { }
    };
    
    class NImportStatement : public NStatement {
    public:
        std::string modulePath;
        std::string alias;
        std::vector<std::string> symbols;
        bool isNamedImport;
        
        NImportStatement(const std::string& modulePath, const std::string& alias = "") :
            modulePath(modulePath), alias(alias), isNamedImport(false) { }
        
        NImportStatement(const std::vector<std::string>& symbols, const std::string& modulePath) :
            symbols(symbols), modulePath(modulePath), isNamedImport(true) { }
    };
    
    class NIncludeStatement : public NStatement {
    public:
        std::string filePath;
        std::string sourceFile;
        size_t line;
        size_t column;

        NIncludeStatement(const std::string& filePath,
                         const std::string& sourceFile = "",
                         size_t line = 0,
                         size_t column = 0) :
            filePath(filePath),
            sourceFile(sourceFile),
            line(line),
            column(column) { }
    };
}

#endif // CSE_NODE_H
