#include "IRInterpreter.h"
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

namespace cse {

IRInterpreter::IRInterpreter() {}

IRInterpreter::~IRInterpreter() {}

int IRInterpreter::execute(const std::list<Quad>& quads, SymbolTable* symbolTable) {
    (void)symbolTable;

    m_Variables.clear();
    m_LabelPositions.clear();
    m_FunctionQuads.clear();
    m_FunctionReturnTypes.clear();
    m_ParamStack.clear();
    m_LastError.clear();

    std::vector<Quad> allQuads(quads.begin(), quads.end());
    std::string currentFunc;
    for (size_t i = 0; i < allQuads.size(); i++) {
        const Quad& q = allQuads[i];
        if (q.getOp() == OpEnum::LABEL) {
            m_LabelPositions[q.getResult()] = i;
        }
        if (q.getOp() == OpEnum::FUNC) {
            currentFunc = q.getResult();
            m_FunctionReturnTypes[currentFunc] = q.getArg1();
            m_FunctionQuads[currentFunc].clear();
        }
        if (!currentFunc.empty() && q.getOp() != OpEnum::FUNC) {
            m_FunctionQuads[currentFunc].push_back(q);
        }
        if (q.getOp() == OpEnum::ENDFUNC) {
            currentFunc.clear();
        }
    }

    auto mainIt = m_FunctionQuads.find("main");
    if (mainIt == m_FunctionQuads.end()) {
        m_LastError = "No main function found";
        return 1;
    }

    int retVal = 0;
    int result = callFunction("main", retVal);
    if (result != 0) {
        return result;
    }

    return retVal;
}

void IRInterpreter::setOutputCallback(OutputCallback callback) {
    m_OutputCallback = callback;
}

std::string IRInterpreter::getLastError() const {
    return m_LastError;
}

int IRInterpreter::callFunction(const std::string& funcName, int& retVal) {
    auto it = m_FunctionQuads.find(funcName);
    if (it == m_FunctionQuads.end()) {
        m_LastError = "Function not found: " + funcName;
        return -1;
    }

    const std::vector<Quad>& funcQuads = it->second;

    /**
     * 保存当前变量映射，实现函数作用域隔离
     * 函数返回后恢复，防止内部临时变量污染外部作用域
     */
    auto savedVariables = m_Variables;

    size_t pc = 0;
    while (pc < funcQuads.size()) {
        const Quad& q = funcQuads[pc];

        switch (q.getOp()) {
        case OpEnum::LABEL:
            break;

        case OpEnum::FUNC:
            break;

        case OpEnum::ENDFUNC:
            m_Variables = savedVariables;
            return 0;

        case OpEnum::ASSIGN: {
            if (isIntLiteral(q.getArg1())) {
                setValue(q.getResult(), std::stoi(q.getArg1()));
            } else if (isDoubleLiteral(q.getArg1())) {
                setValue(q.getResult(), std::stod(q.getArg1()));
            } else if (isStringLiteral(q.getArg1())) {
                setValue(q.getResult(), getStringValue(q.getArg1()));
            } else {
                auto it = m_Variables.find(q.getArg1());
                if (it != m_Variables.end()) {
                    setValue(q.getResult(), it->second);
                } else {
                    setValue(q.getResult(), q.getArg1());
                }
            }
            break;
        }

        case OpEnum::ADD: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), a + b);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), a + b);
            }
            break;
        }

        case OpEnum::SUB: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), a - b);
            } else if (q.getArg1().empty()) {
                if (isDoubleLiteral(q.getArg2()) || isDoubleValue(q.getArg2())) {
                    double b = getDoubleValue(q.getArg2());
                    setValue(q.getResult(), -b);
                } else {
                    int b = getIntValue(q.getArg2());
                    setValue(q.getResult(), -b);
                }
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), a - b);
            }
            break;
        }

        case OpEnum::MUL: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), a * b);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), a * b);
            }
            break;
        }

        case OpEnum::DIV: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                if (b == 0.0) {
                    m_LastError = "Division by zero";
                    m_Variables = savedVariables;
                    return -1;
                }
                setValue(q.getResult(), a / b);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                if (b == 0) {
                    m_LastError = "Division by zero";
                    m_Variables = savedVariables;
                    return -1;
                }
                setValue(q.getResult(), a / b);
            }
            break;
        }

        case OpEnum::MOD: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            if (b == 0) {
                m_LastError = "Modulo by zero";
                m_Variables = savedVariables;
                return -1;
            }
            setValue(q.getResult(), a % b);
            break;
        }

        case OpEnum::EQ: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a == b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a == b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::NE: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a != b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a != b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::LT: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a < b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a < b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::LE: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a <= b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a <= b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::GT: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a > b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a > b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::GE: {
            if (isDoubleValue(q.getArg1()) || isDoubleValue(q.getArg2()) ||
                isDoubleLiteral(q.getArg1()) || isDoubleLiteral(q.getArg2())) {
                double a = getDoubleValue(q.getArg1());
                double b = getDoubleValue(q.getArg2());
                setValue(q.getResult(), (a >= b) ? 1 : 0);
            } else {
                int a = getIntValue(q.getArg1());
                int b = getIntValue(q.getArg2());
                setValue(q.getResult(), (a >= b) ? 1 : 0);
            }
            break;
        }

        case OpEnum::AND: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), a & b);
            break;
        }

        case OpEnum::OR: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), a | b);
            break;
        }

        case OpEnum::XOR: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), a ^ b);
            break;
        }

        case OpEnum::NOT: {
            int a = getIntValue(q.getArg1().empty() ? q.getArg2() : q.getArg1());
            setValue(q.getResult(), ~a);
            break;
        }

        case OpEnum::LSHIFT: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), a << b);
            break;
        }

        case OpEnum::RSHIFT: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), a >> b);
            break;
        }

        case OpEnum::LOGICAL_AND: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), (a && b) ? 1 : 0);
            break;
        }

        case OpEnum::LOGICAL_OR: {
            int a = getIntValue(q.getArg1());
            int b = getIntValue(q.getArg2());
            setValue(q.getResult(), (a || b) ? 1 : 0);
            break;
        }

        case OpEnum::LOGICAL_NOT: {
            int a = getIntValue(q.getArg1().empty() ? q.getArg2() : q.getArg1());
            setValue(q.getResult(), (!a) ? 1 : 0);
            break;
        }

        case OpEnum::CAST: {
            std::string targetType = q.getResult();
            std::string source = q.getArg1();
            if (targetType == "double" || targetType == "(double)") {
                if (isDoubleLiteral(source) || isDoubleValue(source)) {
                    setValue(q.getArg2(), getDoubleValue(source));
                } else {
                    setValue(q.getArg2(), (double)getIntValue(source));
                }
            } else if (targetType == "int" || targetType == "(int)") {
                if (isDoubleLiteral(source) || isDoubleValue(source)) {
                    setValue(q.getArg2(), (int)getDoubleValue(source));
                } else {
                    setValue(q.getArg2(), getIntValue(source));
                }
            } else {
                setValue(q.getArg2(), getValue(source));
            }
            break;
        }

        case OpEnum::JMP: {
            for (size_t j = 0; j < funcQuads.size(); j++) {
                if (funcQuads[j].getOp() == OpEnum::LABEL &&
                    funcQuads[j].getResult() == q.getResult()) {
                    pc = j;
                    goto next_iter;
                }
            }
            break;
        }

        case OpEnum::JMPF: {
            int cond = getIntValue(q.getArg1());
            if (!cond) {
                for (size_t j = 0; j < funcQuads.size(); j++) {
                    if (funcQuads[j].getOp() == OpEnum::LABEL &&
                        funcQuads[j].getResult() == q.getResult()) {
                        pc = j;
                        goto next_iter;
                    }
                }
            }
            break;
        }

        case OpEnum::JMPT: {
            int cond = getIntValue(q.getArg1());
            if (cond) {
                for (size_t j = 0; j < funcQuads.size(); j++) {
                    if (funcQuads[j].getOp() == OpEnum::LABEL &&
                        funcQuads[j].getResult() == q.getResult()) {
                        pc = j;
                        goto next_iter;
                    }
                }
            }
            break;
        }

        /**
         * PARAM 四元式在函数体内用于将 param_N 映射到实际参数名
         * 格式: PARAM param_0, "", actualParamName
         * 语义: actualParamName = param_0 的值
         */
        case OpEnum::PARAM: {
            setValue(q.getResult(), getValue(q.getArg1()));
            break;
        }

        /**
         * CALL 四元式处理
         * 格式: CALL funcName, argCount, resultTemp
         * 参数通过 ASSIGN 四元式设置到 param_0, param_1, ... 变量中
         * 需要从 m_Variables 中读取 param_N 构建参数向量
         */
        case OpEnum::CALL: {
            std::string calledFuncName = q.getArg1();
            int argCount = 0;
            if (!q.getArg2().empty()) {
                argCount = std::stoi(q.getArg2());
            }

            std::vector<InterpValue> params;
            for (int i = 0; i < argCount; i++) {
                std::string paramName = "param_" + std::to_string(i);
                params.push_back(getValue(paramName));
            }

            int callRetVal = 0;

            if (calledFuncName == "printf") {
                callRetVal = interpretPrintf(params);
                if (!q.getResult().empty()) {
                    setValue(q.getResult(), callRetVal);
                }
            } else if (calledFuncName == "puts") {
                if (!params.empty()) {
                    std::string str = getStringValue_fromVal(params[0]);
                    output(str + "\n");
                }
                if (!q.getResult().empty()) setValue(q.getResult(), 0);
            } else if (calledFuncName == "putchar") {
                if (!params.empty()) {
                    int ch = std::get<int>(params[0]);
                    char buf[2] = {(char)ch, 0};
                    output(std::string(buf));
                }
                if (!q.getResult().empty()) setValue(q.getResult(), 0);
            } else if (calledFuncName == "strlen") {
                if (!params.empty()) {
                    std::string str = getStringValue_fromVal(params[0]);
                    if (!q.getResult().empty()) setValue(q.getResult(), (int)str.size());
                }
            } else if (calledFuncName == "malloc") {
                if (!params.empty()) {
                    int size = std::get<int>(params[0]);
                    void* ptr = std::malloc(size);
                    if (!q.getResult().empty()) setValue(q.getResult(), ptr);
                }
            } else if (calledFuncName == "free") {
                if (!params.empty()) {
                    if (std::holds_alternative<void*>(params[0])) {
                        std::free(std::get<void*>(params[0]));
                    }
                }
            } else if (calledFuncName == "abs") {
                if (!params.empty()) {
                    int val = std::get<int>(params[0]);
                    if (!q.getResult().empty()) setValue(q.getResult(), std::abs(val));
                }
            } else if (calledFuncName == "atoi") {
                if (!params.empty()) {
                    std::string str = getStringValue_fromVal(params[0]);
                    if (!q.getResult().empty()) setValue(q.getResult(), std::atoi(str.c_str()));
                }
            } else if (calledFuncName == "sqrt" || calledFuncName == "sin" || calledFuncName == "cos" ||
                       calledFuncName == "tan" || calledFuncName == "log" || calledFuncName == "log2" ||
                       calledFuncName == "log10" || calledFuncName == "exp" || calledFuncName == "fabs" ||
                       calledFuncName == "floor" || calledFuncName == "ceil") {
                if (!params.empty()) {
                    double val = getDoubleValue_fromVal(params[0]);
                    double result = 0;
                    if (calledFuncName == "sqrt") result = std::sqrt(val);
                    else if (calledFuncName == "sin") result = std::sin(val);
                    else if (calledFuncName == "cos") result = std::cos(val);
                    else if (calledFuncName == "tan") result = std::tan(val);
                    else if (calledFuncName == "log") result = std::log(val);
                    else if (calledFuncName == "log2") result = std::log2(val);
                    else if (calledFuncName == "log10") result = std::log10(val);
                    else if (calledFuncName == "exp") result = std::exp(val);
                    else if (calledFuncName == "fabs") result = std::fabs(val);
                    else if (calledFuncName == "floor") result = std::floor(val);
                    else if (calledFuncName == "ceil") result = std::ceil(val);
                    if (!q.getResult().empty()) setValue(q.getResult(), result);
                }
            } else if (calledFuncName == "pow") {
                if (params.size() >= 2) {
                    double a = getDoubleValue_fromVal(params[0]);
                    double b = getDoubleValue_fromVal(params[1]);
                    if (!q.getResult().empty()) setValue(q.getResult(), std::pow(a, b));
                }
            } else {
                auto funcIt = m_FunctionQuads.find(calledFuncName);
                if (funcIt != m_FunctionQuads.end()) {
                    callRetVal = 0;
                    int res = callFunction(calledFuncName, callRetVal);
                    if (res != 0) {
                        m_Variables = savedVariables;
                        return res;
                    }
                    if (!q.getResult().empty()) {
                        std::string retType = "int";
                        auto rtIt = m_FunctionReturnTypes.find(calledFuncName);
                        if (rtIt != m_FunctionReturnTypes.end()) {
                            retType = rtIt->second;
                        }
                        if (retType == "double") {
                            setValue(q.getResult(), (double)callRetVal);
                        } else {
                            setValue(q.getResult(), callRetVal);
                        }
                    }
                } else {
                    m_LastError = "Unknown function: " + calledFuncName;
                }
            }
            break;
        }

        /**
         * RET/RETURN 四元式
         * IR 生成器格式: Quad(OpEnum::RET, "", "", result)
         * 返回值在 result 字段，不是 arg1 字段
         */
        case OpEnum::RET:
        case OpEnum::RETURN: {
            if (!q.getResult().empty()) {
                if (isDoubleLiteral(q.getResult()) || isDoubleValue(q.getResult())) {
                    retVal = (int)getDoubleValue(q.getResult());
                } else {
                    retVal = getIntValue(q.getResult());
                }
            }
            m_Variables = savedVariables;
            return 0;
        }

        case OpEnum::ARRAY: {
            int size = 1;
            if (!q.getArg2().empty()) {
                size = getIntValue(q.getArg2());
            }
            if (size <= 0) size = 1;
            void* arr = std::calloc(size, sizeof(int));
            setValue(q.getResult(), arr);
            break;
        }

        case OpEnum::ARRAY_LOAD: {
            std::string arrName = q.getArg1();
            int index = getIntValue(q.getArg2());
            auto arrIt = m_Variables.find(arrName);
            if (arrIt != m_Variables.end() && std::holds_alternative<void*>(arrIt->second)) {
                int* arr = static_cast<int*>(std::get<void*>(arrIt->second));
                setValue(q.getResult(), arr[index]);
            }
            break;
        }

        case OpEnum::ARRAY_STORE: {
            std::string arrName = q.getResult();
            int index = getIntValue(q.getArg2());
            auto arrIt = m_Variables.find(arrName);
            if (arrIt != m_Variables.end() && std::holds_alternative<void*>(arrIt->second)) {
                int* arr = static_cast<int*>(std::get<void*>(arrIt->second));
                InterpValue val = getValue(q.getArg1());
                if (std::holds_alternative<int>(val)) {
                    arr[index] = std::get<int>(val);
                } else if (std::holds_alternative<double>(val)) {
                    arr[index] = (int)std::get<double>(val);
                }
            }
            break;
        }

        case OpEnum::SET_AL: {
            break;
        }

        case OpEnum::STRING_CONCAT: {
            std::string a = getStringValue(q.getArg1());
            std::string b = getStringValue(q.getArg2());
            setValue(q.getResult(), a + b);
            break;
        }

        case OpEnum::EXTERN: {
            break;
        }

        case OpEnum::REGISTER_CALLBACK: {
            break;
        }

        case OpEnum::POP: {
            break;
        }

        default:
            break;
        }

        pc++;
    next_iter:;
    }

    m_Variables = savedVariables;
    return 0;
}

int IRInterpreter::getIntValue(const std::string& name) {
    if (isIntLiteral(name)) {
        return std::stoi(name);
    }
    if (isDoubleLiteral(name)) {
        return (int)std::stod(name);
    }
    if (name == "0" || name == "false") return 0;
    if (name == "1" || name == "true") return 1;

    auto it = m_Variables.find(name);
    if (it != m_Variables.end()) {
        if (std::holds_alternative<int>(it->second)) {
            return std::get<int>(it->second);
        }
        if (std::holds_alternative<double>(it->second)) {
            return (int)std::get<double>(it->second);
        }
    }
    return 0;
}

double IRInterpreter::getDoubleValue(const std::string& name) {
    if (isDoubleLiteral(name)) {
        return std::stod(name);
    }
    if (isIntLiteral(name)) {
        return (double)std::stoi(name);
    }

    auto it = m_Variables.find(name);
    if (it != m_Variables.end()) {
        if (std::holds_alternative<double>(it->second)) {
            return std::get<double>(it->second);
        }
        if (std::holds_alternative<int>(it->second)) {
            return (double)std::get<int>(it->second);
        }
    }
    return 0.0;
}

std::string IRInterpreter::getStringValue(const std::string& name) {
    if (isStringLiteral(name)) {
        if (name.size() >= 2 && name.front() == '"' && name.back() == '"') {
            std::string s = name.substr(1, name.size() - 2);
            std::string result;
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] == '\\' && i + 1 < s.size()) {
                    switch (s[i + 1]) {
                    case 'n': result += '\n'; i++; break;
                    case 't': result += '\t'; i++; break;
                    case '\\': result += '\\'; i++; break;
                    case '"': result += '"'; i++; break;
                    case '0': result += '\0'; i++; break;
                    default: result += s[i]; break;
                    }
                } else {
                    result += s[i];
                }
            }
            return result;
        }
        return name;
    }

    auto it = m_Variables.find(name);
    if (it != m_Variables.end()) {
        if (std::holds_alternative<std::string>(it->second)) {
            return std::get<std::string>(it->second);
        }
    }
    return name;
}

std::string IRInterpreter::getStringValue_fromVal(const InterpValue& val) {
    if (std::holds_alternative<std::string>(val)) {
        return std::get<std::string>(val);
    }
    if (std::holds_alternative<int>(val)) {
        return std::to_string(std::get<int>(val));
    }
    if (std::holds_alternative<double>(val)) {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "%g", std::get<double>(val));
        return std::string(buf);
    }
    return "";
}

double IRInterpreter::getDoubleValue_fromVal(const InterpValue& val) {
    if (std::holds_alternative<double>(val)) {
        return std::get<double>(val);
    }
    if (std::holds_alternative<int>(val)) {
        return (double)std::get<int>(val);
    }
    return 0.0;
}

InterpValue IRInterpreter::getValue(const std::string& name) {
    if (isDoubleLiteral(name)) {
        return std::stod(name);
    }
    if (isIntLiteral(name)) {
        return std::stoi(name);
    }
    if (isStringLiteral(name)) {
        return getStringValue(name);
    }

    auto it = m_Variables.find(name);
    if (it != m_Variables.end()) {
        return it->second;
    }
    return 0;
}

void IRInterpreter::setValue(const std::string& name, const InterpValue& value) {
    m_Variables[name] = value;
}

bool IRInterpreter::isDoubleLiteral(const std::string& s) const {
    if (s.empty()) return false;
    if (s.find('.') != std::string::npos && s.front() != '"') {
        try {
            std::stod(s);
            return true;
        } catch (...) {
            return false;
        }
    }
    return false;
}

bool IRInterpreter::isIntLiteral(const std::string& s) const {
    if (s.empty()) return false;
    if (s.front() == '"') return false;
    size_t start = 0;
    if (s[0] == '-' && s.size() > 1) start = 1;
    for (size_t i = start; i < s.size(); i++) {
        if (!std::isdigit(s[i])) return false;
    }
    return start < s.size();
}

bool IRInterpreter::isStringLiteral(const std::string& s) const {
    return !s.empty() && s.front() == '"';
}

bool IRInterpreter::isDoubleValue(const std::string& name) const {
    auto it = m_Variables.find(name);
    if (it != m_Variables.end()) {
        return std::holds_alternative<double>(it->second);
    }
    return false;
}

InterpValue IRInterpreter::parseLiteral(const std::string& s) const {
    if (isDoubleLiteral(s)) return std::stod(s);
    if (isIntLiteral(s)) return std::stoi(s);
    if (isStringLiteral(s)) return s;
    return 0;
}

void IRInterpreter::output(const std::string& msg) {
    if (m_OutputCallback) {
        m_OutputCallback(msg);
    } else {
        std::cout << msg;
    }
}

int IRInterpreter::interpretPrintf(const std::vector<InterpValue>& args) {
    if (args.empty()) return 0;

    std::string fmt = getStringValue_fromVal(args[0]);
    std::string result;
    int argIndex = 1;
    size_t i = 0;

    while (i < fmt.size()) {
        if (fmt[i] == '%' && i + 1 < fmt.size()) {
            i++;
            std::string flags;
            while (i < fmt.size() && (fmt[i] == '-' || fmt[i] == '+' ||
                   fmt[i] == '0' || fmt[i] == ' ' || fmt[i] == '#')) {
                flags += fmt[i++];
            }
            std::string width;
            while (i < fmt.size() && std::isdigit(fmt[i])) {
                width += fmt[i++];
            }
            std::string precision;
            if (i < fmt.size() && fmt[i] == '.') {
                i++;
                while (i < fmt.size() && std::isdigit(fmt[i])) {
                    precision += fmt[i++];
                }
            }
            if (i < fmt.size() && fmt[i] == 'l') i++;
            if (i < fmt.size() && fmt[i] == 'l') i++;

            if (i < fmt.size()) {
                char spec = fmt[i++];
                if (argIndex < (int)args.size()) {
                    char buf[256] = {0};
                    const InterpValue& val = args[argIndex++];

                    switch (spec) {
                    case 'd':
                    case 'i':
                        if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%d", std::get<int>(val));
                        } else if (std::holds_alternative<double>(val)) {
                            std::snprintf(buf, sizeof(buf), "%d", (int)std::get<double>(val));
                        }
                        break;
                    case 'f':
                        if (std::holds_alternative<double>(val)) {
                            int prec = 6;
                            if (!precision.empty()) prec = std::stoi(precision);
                            std::snprintf(buf, sizeof(buf), "%.*f", prec, std::get<double>(val));
                        } else if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%f", (double)std::get<int>(val));
                        }
                        break;
                    case 's':
                        result += getStringValue_fromVal(val);
                        buf[0] = 0;
                        break;
                    case 'c':
                        if (std::holds_alternative<int>(val)) {
                            result += (char)std::get<int>(val);
                        }
                        buf[0] = 0;
                        break;
                    case 'x':
                        if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%x", std::get<int>(val));
                        }
                        break;
                    case 'X':
                        if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%X", std::get<int>(val));
                        }
                        break;
                    case 'o':
                        if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%o", std::get<int>(val));
                        }
                        break;
                    case 'u':
                        if (std::holds_alternative<int>(val)) {
                            std::snprintf(buf, sizeof(buf), "%u", (unsigned int)std::get<int>(val));
                        }
                        break;
                    case 'p':
                        std::snprintf(buf, sizeof(buf), "%p",
                            std::holds_alternative<void*>(val) ? std::get<void*>(val) : nullptr);
                        break;
                    case '%':
                        result += '%';
                        buf[0] = 0;
                        argIndex--;
                        break;
                    default:
                        result += '%';
                        result += spec;
                        buf[0] = 0;
                        argIndex--;
                        break;
                    }
                    result += buf;
                } else {
                    result += '%';
                    result += spec;
                }
            }
        } else if (fmt[i] == '\\' && i + 1 < fmt.size()) {
            i++;
            switch (fmt[i]) {
            case 'n': result += '\n'; break;
            case 't': result += '\t'; break;
            case '\\': result += '\\'; break;
            case '"': result += '"'; break;
            case '0': result += '\0'; break;
            default: result += fmt[i]; break;
            }
            i++;
        } else {
            result += fmt[i++];
        }
    }

    output(result);
    return (int)result.size();
}

} // namespace cse
