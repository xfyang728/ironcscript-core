#include "ModuleManager.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>

// 确保在使用类型前包含必要的头文件
#include "frontend/parser/node.h"
#include "frontend/parser/ASTBuilder.h"
#include "frontend/semantic/SymbolTable.h"
#include "frontend/semantic/SemanticAnalyzer.h"
#include "frontend/generated/CScriptLexer.h"
#include "frontend/generated/CScriptParser.h"
#include "IronCScriptImpl.h"

// 确保使用正确的命名空间
using namespace cse;

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>

// Windows平台的文件状态检查函数
inline bool fileExists(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES);
}

inline bool isDirectory(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

inline bool isRegularFile(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}

inline std::string getCurrentDirectory() {
    char buffer[256];
    if (_getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }
    return ".";
}
#else
#include <sys/stat.h>
#include <unistd.h>

// 非Windows平台的文件状态检查函数
inline bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

inline bool isDirectory(const std::string& path) {
    struct stat buffer;
    if (stat(path.c_str(), &buffer) != 0) {
        return false;
    }
    return S_ISDIR(buffer.st_mode);
}

inline bool isRegularFile(const std::string& path) {
    struct stat buffer;
    if (stat(path.c_str(), &buffer) != 0) {
        return false;
    }
    return S_ISREG(buffer.st_mode);
}

inline std::string getCurrentDirectory() {
    char buffer[256];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }
    return ".";
}
#endif

// 不使用filesystem库，改为使用字符串操作和C标准库函数

// 连接路径
inline std::string joinPath(const std::string& path1, const std::string& path2) {
    if (path1.empty()) {
        return path2;
    }
    if (path2.empty()) {
        return path1;
    }
    char lastChar = path1.back();
    if (lastChar == '/' || lastChar == '\\') {
        return path1 + path2;
    }
    return path1 + "/" + path2;
}

#ifdef CSE_EMBEDDED
// 嵌入式平台不支持模块系统
#endif

namespace cse {

std::set<std::string> ModuleManager::loadingFiles;
size_t ModuleManager::globalIncludeDepth = 0;
size_t ModuleManager::globalFailedIncludes = 0;

Module::Module(const std::string& name, const std::string& path)
    : name(name), path(path), ast(nullptr), symbolTable(nullptr) {
}

Module::~Module() {
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

ModuleManager::ModuleManager() {
#ifdef CSE_EMBEDDED
    currentDirectory = ".";
    scriptDirectory = ".";
    maxIncludeDepth = 10;
    currentIncludeDepth = 0;
    cacheHits = 0;
    cacheMisses = 0;
#else
    try {
        currentDirectory = getCurrentDirectory();
    } catch (...) {
        currentDirectory = ".";
    }
    scriptDirectory = currentDirectory;
    maxIncludeDepth = 10;
    currentIncludeDepth = 0;
    cacheHits = 0;
    cacheMisses = 0;

    moduleSearchPaths.push_back(currentDirectory);
    moduleSearchPaths.push_back(scriptDirectory);
    std::string systemModuleDir = joinPath(currentDirectory, "modules");
    if (fileExists(systemModuleDir) && isDirectory(systemModuleDir)) {
        moduleSearchPaths.push_back(systemModuleDir);
    }
#endif
}

ModuleManager::~ModuleManager() {
    // 模块会被 unique_ptr 自动清理
}

void ModuleManager::setCurrentDirectory(const std::string& directory) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
#else
    currentDirectory = directory;
#endif
}

void ModuleManager::setScriptDirectory(const std::string& directory) {
#ifdef CSE_EMBEDDED
#else
    scriptDirectory = directory;
    loadingFiles.clear();
    currentIncludeDepth = 0;
    bool found = false;
    for (size_t i = 0; i < moduleSearchPaths.size(); ++i) {
        if (moduleSearchPaths[i] == scriptDirectory) {
            found = true;
            break;
        }
    }
    if (!found) {
        moduleSearchPaths.insert(moduleSearchPaths.begin() + 1, scriptDirectory);
    }
#endif
}

void ModuleManager::addModuleSearchPath(const std::string& path) {
#ifdef CSE_EMBEDDED
#else
    moduleSearchPaths.push_back(path);
#endif
}

void ModuleManager::setMaxIncludeDepth(size_t depth) {
    maxIncludeDepth = depth;
}

void ModuleManager::setIncludeSearchPaths(const std::vector<std::string>& paths) {
#ifdef CSE_EMBEDDED
#else
    moduleSearchPaths.clear();
    moduleSearchPaths.push_back(currentDirectory);
    if (!scriptDirectory.empty() && scriptDirectory != currentDirectory) {
        moduleSearchPaths.push_back(scriptDirectory);
    }
    for (const auto& path : paths) {
        bool found = false;
        for (const auto& existing : moduleSearchPaths) {
            if (existing == path) {
                found = true;
                break;
            }
        }
        if (!found) {
            moduleSearchPaths.push_back(path);
        }
    }
#endif
}

bool ModuleManager::isCurrentlyLoading(const std::string& filePath) const {
    return loadingFiles.count(filePath) > 0;
}

std::string ModuleManager::resolveIncludePath(const std::string& filePath) {
#ifdef CSE_EMBEDDED
    return "";
#else
    if (filePath.empty()) {
        return "";
    }

    bool isAbsolute = false;
#ifdef _WIN32
    isAbsolute = (filePath.size() >= 2 && filePath[1] == ':');
#else
    isAbsolute = (filePath.size() >= 1 && filePath[0] == '/');
#endif

    if (isAbsolute) {
        return filePath;
    }

    std::vector<std::string> searchDirs;
    if (!scriptDirectory.empty()) {
        searchDirs.push_back(scriptDirectory);
    }
    for (const auto& path : moduleSearchPaths) {
        bool found = false;
        for (const auto& dir : searchDirs) {
            if (dir == path) {
                found = true;
                break;
            }
        }
        if (!found && !path.empty()) {
            searchDirs.push_back(path);
        }
    }
    if (currentDirectory != scriptDirectory) {
        bool found = false;
        for (const auto& dir : searchDirs) {
            if (dir == currentDirectory) {
                found = true;
                break;
            }
        }
        if (!found) {
            searchDirs.push_back(currentDirectory);
        }
    }

    std::vector<std::string> extensions = {".cs", ".c", ""};
    for (const auto& dir : searchDirs) {
        for (const auto& ext : extensions) {
            std::string fullPath = joinPath(dir, filePath);
            if (!ext.empty() && fullPath.find_last_of('.') == std::string::npos) {
                fullPath += ext;
            }
            if (fileExists(fullPath) && isRegularFile(fullPath)) {
                return fullPath;
            }
        }
    }

    return joinPath(scriptDirectory.empty() ? currentDirectory : scriptDirectory, filePath);
#endif
}

std::string ModuleManager::findModuleFile(const std::string& modulePath) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    return "";
#else
    // 尝试不同的扩展名
    std::vector<std::string> extensions = {".c", ""};
    
    for (const auto& searchPath : moduleSearchPaths) {
        for (const auto& ext : extensions) {
            std::string fullPath = joinPath(searchPath, modulePath);
            if (!ext.empty()) {
                fullPath += ext;
            }
            if (fileExists(fullPath) && isRegularFile(fullPath)) {
                return fullPath;
            }
        }
    }
    
    return "";
#endif
}

std::string ModuleManager::resolveModulePath(const std::string& modulePath) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    return "";
#else
    // 首先尝试使用 findModuleFile 方法查找模块文件
    std::string foundPath = findModuleFile(modulePath);
    if (!foundPath.empty()) {
        return foundPath;
    }
    
    // 如果找不到，回退到原来的逻辑
    std::string path = modulePath;
    // 简单判断是否是绝对路径（Windows下以盘符开头，Unix下以/开头）
    bool isAbsolute = false;
    #ifdef _WIN32
    isAbsolute = (path.size() >= 2 && path[1] == ':');
    #else
    isAbsolute = (path.size() >= 1 && path[0] == '/');
    #endif
    
    if (!isAbsolute) {
        path = joinPath(currentDirectory, path);
    }
    
    // 尝试添加 .c 扩展名
    size_t lastDot = path.find_last_of('.');
    if (lastDot == std::string::npos) {
        path += ".c";
    }
    
    return path;
#endif
}

std::string ModuleManager::getModuleNameFromPath(const std::string& path) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    return "";
#else
    // 直接处理字符串，避免filesystem路径操作
    std::string filename = path;
    size_t lastSlash = filename.find_last_of('/');
    if (lastSlash == std::string::npos) {
        lastSlash = filename.find_last_of('\\');
    }
    if (lastSlash != std::string::npos) {
        filename = filename.substr(lastSlash + 1);
    }
    size_t lastDot = filename.find_last_of('.');
    if (lastDot == std::string::npos) {
        return filename;
    }
    return filename.substr(0, lastDot);
#endif
}

Module* ModuleManager::loadModule(const std::string& modulePath) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    std::cerr << "[MODULE] Module system not supported on embedded platform" << std::endl;
    return nullptr;
#else
    // 解析模块路径
    std::string resolvedPath = resolveModulePath(modulePath);
    
    // 检查模块是否已经加载
    std::string moduleName = getModuleNameFromPath(resolvedPath);
    if (modules.find(moduleName) != modules.end()) {
        return modules[moduleName].get();
    }
    
    // 读取模块文件
    std::ifstream file(resolvedPath);
    if (!file.is_open()) {
        std::cerr << "[MODULE] Cannot open module file: " << resolvedPath << std::endl;
        return nullptr;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string moduleCode = buffer.str();
    file.close();
    
    // 解析模块代码
    IronCScriptImpl engine;
    NBlock* ast = nullptr;
    if (!engine.parseScript(moduleCode, ast)) {
        std::cerr << "[MODULE] Failed to parse module: " << resolvedPath << std::endl;
        return nullptr;
    }
    
    // 语义分析
    SymbolTable* symbolTable = new SymbolTable();
    SemanticAnalyzer semanticAnalyzer(*symbolTable, this);
    if (!semanticAnalyzer.analyze(*ast)) {
        std::cerr << "[MODULE] Semantic analysis failed for module: " << resolvedPath << std::endl;
        delete ast;
        delete symbolTable;
        return nullptr;
    }
    
    // 创建模块对象
    std::unique_ptr<Module> module(new Module(moduleName, resolvedPath));
    module->ast = ast;
    module->symbolTable = symbolTable;
    
    // 收集导出的符号
    // 这里简化处理，导出所有全局符号
    Scope* globalScope = symbolTable->getGlobalScope();
    if (globalScope) {
        for (const auto& symbolPair : globalScope->symbols) {
            const Symbol& symbol = symbolPair.second;
            if (symbol.isGlobal) {
                module->exports.push_back(symbol.name);
            }
        }
    }
    
    // 保存模块
    modules[moduleName] = std::move(module);
    return modules[moduleName].get();
#endif
}

Module* ModuleManager::getModule(const std::string& moduleName) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    return nullptr;
#else
    auto it = modules.find(moduleName);
    if (it != modules.end()) {
        return it->second.get();
    }
    return nullptr;
#endif
}

bool ModuleManager::importModule(const std::string& modulePath, const std::string& alias, SymbolTable& symbolTable) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    std::cerr << "[MODULE] Module system not supported on embedded platform" << std::endl;
    return false;
#else
    Module* module = loadModule(modulePath);
    if (!module) {
        return false;
    }
    
    // 获取模块的全局作用域
    Scope* moduleScope = module->symbolTable->getGlobalScope();
    if (!moduleScope) {
        return false;
    }
    
    // 导入所有符号，不只是导出的符号
    for (const auto& pair : moduleScope->symbols) {
        const std::string& symbolName = pair.first;
        const Symbol& symbol = pair.second;
        
        // 只导入函数和全局变量
        if (symbol.isFunction || symbol.isGlobal) {
            // 创建导入的符号
            Symbol importedSymbol = symbol;
            if (!alias.empty()) {
                importedSymbol.name = alias + "." + symbolName;
            }
            
            // 添加到全局符号表
            if (!symbolTable.insertSymbolToGlobalScope(importedSymbol)) {
                std::cerr << "[MODULE] Failed to insert symbol: " << importedSymbol.name << std::endl;
            } else {
                std::cerr << "[MODULE] Successfully imported symbol: " << importedSymbol.name << std::endl;
            }
        }
    }
    
    return true;
#endif
}

bool ModuleManager::importNamedSymbols(const std::string& modulePath, const std::vector<std::string>& symbols, SymbolTable& symbolTable) {
#ifdef CSE_EMBEDDED
    // 嵌入式平台不支持模块系统
    std::cerr << "[MODULE] Module system not supported on embedded platform" << std::endl;
    return false;
#else
    Module* module = loadModule(modulePath);
    if (!module) {
        return false;
    }
    
    // 获取模块的全局作用域
    Scope* moduleScope = module->symbolTable->getGlobalScope();
    if (!moduleScope) {
        return false;
    }
    
    // 导入指定的符号
    for (const std::string& symbolName : symbols) {
        auto it = moduleScope->symbols.find(symbolName);
        if (it != moduleScope->symbols.end()) {
            const Symbol& symbol = it->second;
            
            // 添加到全局符号表
            if (!symbolTable.insertSymbolToGlobalScope(symbol)) {
                std::cerr << "[MODULE] Failed to insert symbol: " << symbol.name << std::endl;
            } else {
                std::cerr << "[MODULE] Successfully imported symbol: " << symbol.name << std::endl;
            }
        } else {
            std::cerr << "[MODULE] Symbol not found in module: " << symbolName << std::endl;
        }
    }
    
    return true;
#endif
}

bool ModuleManager::includeFile(const std::string& filePath, NBlock& block,
                               const std::string& sourceFile, size_t line, size_t column) {
#ifdef CSE_EMBEDDED
    std::cerr << "[MODULE] Module system not supported on embedded platform" << std::endl;
    return false;
#else
    auto formatLocation = [](const std::string& src, size_t ln, size_t col) -> std::string {
        if (src.empty()) return "";
        return src + ":" + std::to_string(ln) + ":" + std::to_string(col) + ": ";
    };

    std::string location = formatLocation(sourceFile, line, column);
    std::string resolvedPath = resolveIncludePath(filePath);

    if (loadingFiles.count(resolvedPath) > 0) {
        std::cerr << location << "[MODULE] Circular include detected: " << resolvedPath << std::endl;
        ++globalFailedIncludes;
        return false;
    }

    if (globalIncludeDepth >= maxIncludeDepth) {
        std::cerr << location << "[MODULE] Include depth limit exceeded: " << maxIncludeDepth << std::endl;
        ++globalFailedIncludes;
        return false;
    }

    if (resolvedPath.empty()) {
        std::cerr << location << "[MODULE] Cannot resolve include path: " << filePath << std::endl;
        ++globalFailedIncludes;
        return false;
    }

    struct _stat fileStat;
    if (_stat(resolvedPath.c_str(), &fileStat) != 0) {
        std::cerr << location << "[MODULE] Cannot stat include file: " << resolvedPath << std::endl;
        ++globalFailedIncludes;
        return false;
    }
    time_t fileMtime = fileStat.st_mtime;

    auto cacheIt = includeCache.find(resolvedPath);
    if (cacheIt != includeCache.end() && cacheIt->second->mtime == fileMtime) {
        ++cacheHits;
        std::cerr << location << "[CACHE] Include cache hit: " << resolvedPath << std::endl;
        NBlock* cachedAst = cacheIt->second->ast;
        for (auto stmt : cachedAst->statements) {
            block.statements.push_back(stmt);
        }
        return true;
    }
    ++cacheMisses;
    std::cerr << location << "[CACHE] Include cache miss: " << resolvedPath << std::endl;

    std::ifstream file(resolvedPath);
    if (!file.is_open()) {
        std::cerr << location << "[MODULE] Cannot open include file: " << resolvedPath << std::endl;
        ++globalFailedIncludes;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string includeCode = buffer.str();
    file.close();

    loadingFiles.insert(resolvedPath);
    ++globalIncludeDepth;

    antlr4::ANTLRInputStream input(includeCode.c_str(), includeCode.size());
    CScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CScriptParser parser(&tokens);

    ASTBuilder builder;
    builder.setSourceFile(resolvedPath);
    NBlock* includeAst = builder.build(parser.program());

    if (includeAst == nullptr) {
        std::cerr << location << "[MODULE] Failed to parse include file: " << resolvedPath << std::endl;
        --globalIncludeDepth;
        loadingFiles.erase(resolvedPath);
        ++globalFailedIncludes;
        return false;
    }

    SymbolTable tempSymbolTable;
    SemanticAnalyzer semanticAnalyzer(tempSymbolTable, this);
    semanticAnalyzer.setCurrentBlock(&block);
    semanticAnalyzer.setSourceFile(resolvedPath);
    size_t statementsBeforeAnalysis = block.statements.size();
    if (!semanticAnalyzer.analyze(*includeAst)) {
        std::cerr << location << "[MODULE] Semantic analysis failed for include file: " << resolvedPath << std::endl;
        while (block.statements.size() > statementsBeforeAnalysis) {
            delete block.statements.back();
            block.statements.pop_back();
        }
        delete includeAst;
        --globalIncludeDepth;
        loadingFiles.erase(resolvedPath);
        ++globalFailedIncludes;
        return false;
    }

    includeCache[resolvedPath] = std::make_unique<ParsedIncludeCache>(includeAst, resolvedPath, fileMtime);

    for (auto stmt : includeAst->statements) {
        block.statements.push_back(stmt);
    }

    includeAst->statements.clear();
    delete includeAst;

    --globalIncludeDepth;
    loadingFiles.erase(resolvedPath);

    if (globalFailedIncludes > 0) {
        --globalFailedIncludes;
        return false;
    }

    return true;
#endif
}

} // namespace cse