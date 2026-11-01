#include "Preprocessor.h"

#include <cctype>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace cse {
namespace {

struct Macro {
    bool functionLike = false;
    std::vector<std::string> params;
    std::string body;
};

bool isIdentStart(char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '_'; }
bool isIdentChar(char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; }

std::string trim(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) b++;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) e--;
    return s.substr(b, e - b);
}

// 跳过字符串/字符字面量与注释，返回下一个可处理的字符位置。
size_t skipQuotedOrComment(const std::string& s, size_t i) {
    if (s[i] == '"' || s[i] == '\'') {
        char quote = s[i];
        size_t j = i + 1;
        while (j < s.size()) {
            if (s[j] == '\\') { j += 2; continue; }
            if (s[j] == quote) return j + 1;
            j++;
        }
        return s.size();
    }
    if (s[i] == '/' && i + 1 < s.size() && s[i + 1] == '/') {
        size_t j = s.find('\n', i);
        return j == std::string::npos ? s.size() : j;
    }
    if (s[i] == '/' && i + 1 < s.size() && s[i + 1] == '*') {
        size_t j = s.find("*/", i + 2);
        return j == std::string::npos ? s.size() : j + 2;
    }
    return i;
}

std::string expandText(const std::string& text, const std::map<std::string, Macro>& macros,
                       std::set<std::string>& disabled, int depth);

// 解析函数宏实参：i 指向 '('，返回右括号之后的位置，并填 args。
size_t parseArguments(const std::string& s, size_t i, std::vector<std::string>& args) {
    if (i >= s.size() || s[i] != '(') return i;
    int parens = 0;
    std::string current;
    size_t j = i;
    for (; j < s.size(); ++j) {
        char c = s[j];
        if (c == '"' || c == '\'') {
            size_t end = skipQuotedOrComment(s, j);
            current.append(s, j, end - j);
            j = end - 1;
            continue;
        }
        if (c == '/' && j + 1 < s.size() && (s[j + 1] == '/' || s[j + 1] == '*')) {
            size_t end = skipQuotedOrComment(s, j);
            current.append(s, j, end - j);
            j = end - 1;
            continue;
        }
        if (c == '(') {
            parens++;
            if (parens == 1) continue;
        } else if (c == ')') {
            parens--;
            if (parens == 0) {
                args.push_back(trim(current));
                return j + 1;
            }
        } else if (c == ',' && parens == 1) {
            args.push_back(trim(current));
            current.clear();
            continue;
        }
        current.push_back(c);
    }
    args.push_back(trim(current));
    return j;
}

// 把 body 中的参数标识符替换为实参文本。
std::string substituteParams(const std::string& body, const std::vector<std::string>& params,
                             const std::vector<std::string>& args) {
    std::string out;
    size_t i = 0;
    while (i < body.size()) {
        if (isIdentStart(body[i])) {
            size_t j = i;
            while (j < body.size() && isIdentChar(body[j])) j++;
            std::string name = body.substr(i, j - i);
            bool replaced = false;
            for (size_t p = 0; p < params.size(); ++p) {
                if (params[p] == name && p < args.size()) {
                    out += args[p];
                    replaced = true;
                    break;
                }
            }
            if (!replaced) out += name;
            i = j;
        } else if (body[i] == '"' || body[i] == '\'' ||
                   (body[i] == '/' && i + 1 < body.size() && (body[i + 1] == '/' || body[i + 1] == '*'))) {
            size_t end = skipQuotedOrComment(body, i);
            out.append(body, i, end - i);
            i = end;
        } else {
            out.push_back(body[i]);
            i++;
        }
    }
    return out;
}

std::string expandText(const std::string& text, const std::map<std::string, Macro>& macros,
                       std::set<std::string>& disabled, int depth) {
    if (depth > 64) return text;
    std::string out;
    size_t i = 0;
    while (i < text.size()) {
        char c = text[i];
        if (c == '"' || c == '\'' || (c == '/' && i + 1 < text.size() && (text[i + 1] == '/' || text[i + 1] == '*'))) {
            size_t end = skipQuotedOrComment(text, i);
            out.append(text, i, end - i);
            i = end;
            continue;
        }
        if (isIdentStart(c)) {
            size_t j = i;
            while (j < text.size() && isIdentChar(text[j])) j++;
            std::string name = text.substr(i, j - i);
            auto it = macros.find(name);
            if (it != macros.end() && disabled.find(name) == disabled.end()) {
                const Macro& m = it->second;
                if (m.functionLike) {
                    size_t k = j;
                    while (k < text.size() && std::isspace(static_cast<unsigned char>(text[k]))) k++;
                    if (k < text.size() && text[k] == '(') {
                        std::vector<std::string> args;
                        size_t after = parseArguments(text, k, args);
                        std::vector<std::string> expandedArgs;
                        for (auto& a : args) expandedArgs.push_back(expandText(a, macros, disabled, depth + 1));
                        std::string body = substituteParams(m.body, m.params, expandedArgs);
                        disabled.insert(name);
                        out += expandText(body, macros, disabled, depth + 1);
                        disabled.erase(name);
                        i = after;
                        continue;
                    }
                } else {
                    disabled.insert(name);
                    out += expandText(m.body, macros, disabled, depth + 1);
                    disabled.erase(name);
                    i = j;
                    continue;
                }
            }
            out += name;
            i = j;
            continue;
        }
        out.push_back(c);
        i++;
    }
    return out;
}

} // namespace

std::string preprocessSource(const std::string& source) {
    std::map<std::string, Macro> macros;
    std::vector<std::string> lines;
    {
        size_t start = 0;
        while (start <= source.size()) {
            size_t nl = source.find('\n', start);
            if (nl == std::string::npos) {
                lines.push_back(source.substr(start));
                break;
            }
            lines.push_back(source.substr(start, nl - start));
            start = nl + 1;
            if (start == source.size()) {
                lines.push_back("");
                break;
            }
        }
    }

    bool blockComment = false;
    std::vector<std::string> bodyLines;

    for (const auto& rawLine : lines) {
        std::string line = rawLine;
        // 判断是否为指令行（允许前置空白）。块注释内一律不识别。
        size_t p = 0;
        while (p < line.size() && std::isspace(static_cast<unsigned char>(line[p]))) p++;
        bool directive = !blockComment && p < line.size() && line[p] == '#';

        // 更新块注释状态（粗粒度：只扫描本行）
        for (size_t k = 0; k < line.size(); ++k) {
            if (blockComment) {
                if (line[k] == '*' && k + 1 < line.size() && line[k + 1] == '/') { blockComment = false; k++; }
            } else if (line[k] == '/' && k + 1 < line.size() && line[k + 1] == '*') {
                blockComment = true;
                k++;
            } else if (line[k] == '"' || line[k] == '\'') {
                k = skipQuotedOrComment(line, k);
                if (k >= line.size()) break;
                k--;
            }
        }

        if (!directive) {
            bodyLines.push_back(line);
            continue;
        }

        std::string rest = line.substr(p + 1);
        size_t q = 0;
        while (q < rest.size() && std::isspace(static_cast<unsigned char>(rest[q]))) q++;
        size_t r = q;
        while (r < rest.size() && isIdentChar(rest[r])) r++;
        std::string word = rest.substr(q, r - q);
        std::string arg = trim(rest.substr(r));

        if (word == "define") {
            size_t t = 0;
            while (t < arg.size() && std::isspace(static_cast<unsigned char>(arg[t]))) t++;
            size_t n = t;
            while (n < arg.size() && isIdentChar(arg[n])) n++;
            std::string name = arg.substr(t, n - t);
            if (!name.empty()) {
                size_t m = n;
                Macro mac;
                if (m < arg.size() && arg[m] == '(') {
                    mac.functionLike = true;
                    size_t close = arg.find(')', m + 1);
                    if (close != std::string::npos) {
                        std::string paramText = arg.substr(m + 1, close - m - 1);
                        size_t ps = 0;
                        while (ps <= paramText.size()) {
                            size_t comma = paramText.find(',', ps);
                            std::string one = trim(paramText.substr(ps, comma == std::string::npos ? std::string::npos : comma - ps));
                            if (!one.empty()) mac.params.push_back(one);
                            if (comma == std::string::npos) break;
                            ps = comma + 1;
                        }
                        mac.body = trim(arg.substr(close + 1));
                    }
                } else {
                    mac.body = trim(arg.substr(m));
                }
                macros[name] = mac;
            }
            bodyLines.push_back("");
            continue;
        }
        if (word == "undef") {
            macros.erase(arg);
            bodyLines.push_back("");
            continue;
        }
        if (word == "include") {
            bodyLines.push_back(line); // 交给语法分析器
            continue;
        }
        bodyLines.push_back(line);
    }

    std::string joined;
    for (size_t i = 0; i < bodyLines.size(); ++i) {
        joined += bodyLines[i];
        if (i + 1 < bodyLines.size()) joined += "\n";
    }

    std::set<std::string> disabled;
    return expandText(joined, macros, disabled, 0);
}

} // namespace cse
