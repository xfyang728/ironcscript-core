#ifndef CSE_STANDARD_LIBRARY_H
#define CSE_STANDARD_LIBRARY_H

#include <string>
#include <vector>
#include <cstdarg>

namespace cse {

enum class FunctionSource {
    Builtin,      // 内置实现，不依赖任何外部库
    StandardLib,   // 从 C 运行时加载 (msvcrt, libc)
    UserFFI       // 用户注册
};

class StandardLibrary {
public:
    static StandardLibrary& instance();

    void* resolve(const std::string& funcName);

    FunctionSource getFunctionSource(const std::string& funcName) const;

    bool isBuiltin(const std::string& funcName) const;
    bool isStandardLib(const std::string& funcName) const;

private:
    StandardLibrary();

    static void* builtin_malloc(size_t size);
    static void builtin_free(void* ptr);
    static void builtin_memset(void* ptr, int value, size_t num);
    static void* builtin_memcpy(void* dest, const void* src, size_t count);
    static int builtin_printf(const char* format, ...);
    static void builtin_exit(int status);
    static int builtin_abs(int n);

    static const std::vector<std::string> builtinFunctions;
    static const std::vector<std::string> standardLibFunctions;
};

} // namespace cse

#endif // CSE_STANDARD_LIBRARY_H
