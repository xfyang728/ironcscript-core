/**
 * @file ModuleManager.h
 * @brief 模块管理系统头文件
 * @author IronCScript Team
 * @version 1.0.0
 */

#ifndef CSE_MODULE_MANAGER_H
#define CSE_MODULE_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <set>
#include "frontend/parser/node.h"
#include "frontend/semantic/SymbolTable.h"

namespace cse {

/**
 * @brief 模块封装类
 * @details 存储已加载模块的元信息，包括模块名、路径、AST和符号表
 */
class Module {
public:
    std::string name;
    std::string path;
    NBlock* ast;
    SymbolTable* symbolTable;
    std::vector<std::string> exports;

    /**
     * @brief 构造函数
     * @param name 模块名称
     * @param path 模块文件路径
     */
    Module(const std::string& name, const std::string& path);

    /**
     * @brief 析构函数
     * @details 释放AST和符号表占用的内存
     */
    ~Module();
};

/**
 * @brief 已解析 AST 块的缓存条目
 */
struct ParsedIncludeCache {
    NBlock* ast;
    std::string filePath;
    time_t mtime;

    ParsedIncludeCache(NBlock* a, const std::string& path, time_t mt)
        : ast(a), filePath(path), mtime(mt) {}
};

/**
 * @brief 模块管理器类
 * @details 负责模块加载、路径解析、循环检测和include文件处理
 */
class ModuleManager {
private:
    std::map<std::string, std::unique_ptr<Module>> modules;
    std::string currentDirectory;
    std::string scriptDirectory;
    std::vector<std::string> moduleSearchPaths;
    static std::set<std::string> loadingFiles;
    size_t maxIncludeDepth;
    size_t currentIncludeDepth;

    std::map<std::string, std::unique_ptr<ParsedIncludeCache>> includeCache;
    size_t cacheHits;
    size_t cacheMisses;

public:
    static size_t globalIncludeDepth;
    static size_t globalFailedIncludes;
    static constexpr size_t DEFAULT_MAX_INCLUDE_DEPTH = 10;

    size_t getCacheHits() const { return cacheHits; }
    size_t getCacheMisses() const { return cacheMisses; }
    void resetCacheStats() { cacheHits = 0; cacheMisses = 0; }

    /**
     * @brief 解析模块路径
     * @param modulePath 模块路径
     * @return 解析后的绝对路径
     */
    std::string resolveModulePath(const std::string& modulePath);

    /**
     * @brief 从路径获取模块名
     * @param path 文件路径
     * @return 模块名
     */
    std::string getModuleNameFromPath(const std::string& path);

    /**
     * @brief 查找模块文件
     * @param modulePath 模块路径
     * @return 找到的文件路径，若未找到则返回空字符串
     */
    std::string findModuleFile(const std::string& modulePath);

public:
    /**
     * @brief 构造函数
     */
    ModuleManager();

    /**
     * @brief 析构函数
     */
    ~ModuleManager();

    /**
     * @brief 设置当前工作目录
     * @param directory 当前目录路径
     */
    void setCurrentDirectory(const std::string& directory);

    /**
     * @brief 设置脚本所在目录
     * @param directory 脚本文件所在目录
     * @details 用于相对路径解析，include文件优先基于此目录查找
     */
    void setScriptDirectory(const std::string& directory);

    /**
     * @brief 添加模块搜索路径
     * @param path 要添加的搜索路径
     */
    void addModuleSearchPath(const std::string& path);

    /**
     * @brief 设置最大include嵌套深度
     * @param depth 最大深度值，默认10
     * @details 防止过度嵌套导致的栈溢出
     */
    void setMaxIncludeDepth(size_t depth);

    /**
     * @brief 设置include搜索路径列表
     * @param paths 搜索路径向量
     * @details 搜索顺序：脚本目录 → 已配置搜索路径 → 当前目录
     */
    void setIncludeSearchPaths(const std::vector<std::string>& paths);

    /**
     * @brief 检查文件是否正在加载中
     * @param filePath 文件路径
     * @return 如果文件正在加载返回true，否则返回false
     * @details 用于循环include检测
     */
    bool isCurrentlyLoading(const std::string& filePath) const;

    /**
     * @brief 解析include文件路径
     * @param filePath include的文件路径
     * @return 解析后的绝对路径
     * @details 搜索顺序：脚本目录 → 已配置搜索路径 → 当前目录
     */
    std::string resolveIncludePath(const std::string& filePath);

    /**
     * @brief 执行include文件包含
     * @param filePath 要包含的文件路径
     * @param block AST块引用，用于接收被包含文件的语句
     * @param sourceFile 来源文件名（用于错误信息）
     * @param line 来源文件行号（用于错误信息）
     * @param column 来源文件列号（用于错误信息）
     * @return 成功返回true，失败返回false
     * @throws 循环检测失败、深度超限、文件不存在等情况
     */
    bool includeFile(const std::string& filePath, NBlock& block,
                    const std::string& sourceFile = "", size_t line = 0, size_t column = 0);

    /**
     * @brief 加载模块
     * @param modulePath 模块路径
     * @return 加载的模块指针，失败返回nullptr
     */
    Module* loadModule(const std::string& modulePath);

    /**
     * @brief 获取已加载的模块
     * @param moduleName 模块名
     * @return 模块指针，若未找到返回nullptr
     */
    Module* getModule(const std::string& moduleName);

    /**
     * @brief 导入模块到符号表
     * @param modulePath 模块路径
     * @param alias 模块别名
     * @param symbolTable 目标符号表
     * @return 成功返回true，失败返回false
     */
    bool importModule(const std::string& modulePath, const std::string& alias, SymbolTable& symbolTable);

    /**
     * @brief 导入模块中的指定符号
     * @param modulePath 模块路径
     * @param symbols 要导入的符号名列表
     * @param symbolTable 目标符号表
     * @return 成功返回true，失败返回false
     */
    bool importNamedSymbols(const std::string& modulePath, const std::vector<std::string>& symbols, SymbolTable& symbolTable);
};

} // namespace cse

#endif // CSE_MODULE_MANAGER_H