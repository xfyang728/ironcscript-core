#pragma once

#include <string>
#include <map>
#include <vector>
#include <list>
#include <variant>
#include <functional>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "ir/Quad.h"
#include "frontend/semantic/SymbolTable.h"

namespace cse {

/**
 * @brief IR 解释器值类型
 * @details 支持 int, double, 字符串 和指针类型
 */
using InterpValue = std::variant<int, double, std::string, void*>;

/**
 * @brief IR 解释器 - 直接执行 Quad 中间代码
 * @details 用于 WASM 等不支持 JIT 执行的环境，
 *          通过解释执行 IR 四元式来运行 CScript 脚本
 */
class IRInterpreter {
public:
    using OutputCallback = std::function<void(const std::string&)>;

    IRInterpreter();
    ~IRInterpreter();

    /**
     * @brief 执行 Quad 列表
     * @param quads IR 四元式列表
     * @param symbolTable 符号表
     * @return main 函数返回值
     */
    int execute(const std::list<Quad>& quads, SymbolTable* symbolTable);

    /**
     * @brief 设置标准输出回调
     * @param callback 输出回调函数
     */
    void setOutputCallback(OutputCallback callback);

    /**
     * @brief 获取最后的错误信息
     * @return 错误信息字符串
     */
    std::string getLastError() const;

private:
    std::map<std::string, InterpValue> m_Variables;
    std::map<std::string, size_t> m_LabelPositions;
    std::map<std::string, std::vector<Quad>> m_FunctionQuads;
    std::map<std::string, std::string> m_FunctionReturnTypes;
    std::vector<InterpValue> m_ParamStack;
    OutputCallback m_OutputCallback;
    std::string m_LastError;

    /**
     * @brief 获取变量的整数值
     */
    int getIntValue(const std::string& name);

    /**
     * @brief 获取变量的双精度浮点值
     */
    double getDoubleValue(const std::string& name);

    /**
     * @brief 获取变量的字符串值
     */
    std::string getStringValue(const std::string& name);

    /**
     * @brief 从 InterpValue 获取字符串值
     */
    static std::string getStringValue_fromVal(const InterpValue& val);

    /**
     * @brief 从 InterpValue 获取双精度浮点值
     */
    static double getDoubleValue_fromVal(const InterpValue& val);

    /**
     * @brief 获取值（自动判断类型）
     */
    InterpValue getValue(const std::string& name);

    /**
     * @brief 设置变量值
     */
    void setValue(const std::string& name, const InterpValue& value);

    /**
     * @brief 判断是否为浮点数字面量
     */
    bool isDoubleLiteral(const std::string& s) const;

    /**
     * @brief 判断是否为整数字面量
     */
    bool isIntLiteral(const std::string& s) const;

    /**
     * @brief 判断是否为字符串字面量
     */
    bool isStringLiteral(const std::string& s) const;

    /**
     * @brief 判断值是否为 double 类型
     */
    bool isDoubleValue(const std::string& name) const;

    /**
     * @brief 解析字面量值
     */
    InterpValue parseLiteral(const std::string& s) const;

    /**
     * @brief 输出字符串
     */
    void output(const std::string& msg);

    /**
     * @brief 简易 printf 实现
     */
    int interpretPrintf(const std::vector<InterpValue>& args);

    /**
     * @brief 执行函数
     */
    int callFunction(const std::string& funcName, int& retVal);
};

} // namespace cse
