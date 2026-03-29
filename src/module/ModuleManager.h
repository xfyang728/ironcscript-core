#ifndef CSE_MODULE_MANAGER_H
#define CSE_MODULE_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "frontend/parser/node.h"
#include "frontend/semantic/SymbolTable.h"

namespace cse {

class Module {
public:
    std::string name;
    std::string path;
    NBlock* ast;
    SymbolTable* symbolTable;
    std::vector<std::string> exports;
    
    Module(const std::string& name, const std::string& path) :
        name(name), path(path), ast(nullptr), symbolTable(nullptr) { }
    
    ~Module() {
        if (ast) {
            for (auto stmt : ast->statements) {
                delete stmt;
            }
            delete ast;
        }
        if (symbolTable) {
            delete symbolTable;
        }
    }
};

class ModuleManager {
private:
    std::map<std::string, std::unique_ptr<Module>> modules;
    std::string currentDirectory;
    std::string scriptDirectory; // 当前脚本所在目录
    std::vector<std::string> moduleSearchPaths; // 模块搜索路径
    
    std::string resolveModulePath(const std::string& modulePath);
    std::string getModuleNameFromPath(const std::string& path);
    std::string findModuleFile(const std::string& modulePath);
    
public:
    ModuleManager();
    ~ModuleManager();
    
    void setCurrentDirectory(const std::string& directory);
    void setScriptDirectory(const std::string& directory);
    void addModuleSearchPath(const std::string& path);
    
    Module* loadModule(const std::string& modulePath);
    Module* getModule(const std::string& moduleName);
    
    bool importModule(const std::string& modulePath, const std::string& alias, SymbolTable& symbolTable);
    bool importNamedSymbols(const std::string& modulePath, const std::vector<std::string>& symbols, SymbolTable& symbolTable);
    bool includeFile(const std::string& filePath, NBlock& block);
};

} // namespace cse

#endif // CSE_MODULE_MANAGER_H