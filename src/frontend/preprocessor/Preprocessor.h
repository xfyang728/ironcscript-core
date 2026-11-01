#pragma once

#include <string>

namespace cse {

// C-Script 源级预处理器。
// 支持 #define（对象宏 / 函数宏）、#undef；条件编译按 C-Script 方言保持不支持；
// #include 原样保留，交由语法分析器的 include_stmt 处理。
// 指令行被替换为空行，保证诊断中的行号与源文件一致。
std::string preprocessSource(const std::string& source);

} // namespace cse
