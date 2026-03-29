#include "StandardLibrary.h"
#include "gc/GarbageCollector.h"
#include "sandbox/MemorySandbox.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif

namespace cse {

const std::vector<std::string> StandardLibrary::builtinFunctions = {
    "malloc",
    "free",
    "memset",
    "memcpy",
    "printf",
    "exit",
    "abs"
};

const std::vector<std::string> StandardLibrary::standardLibFunctions = {
    // === 输入输出函数 (14) ===
    "scanf", "sscanf", "fscanf", "printf", "sprintf", "fprintf",
    "puts", "fputs", "gets", "fgets",
    "putchar", "getchar", "putc", "getc",
    // === 字符串函数 (25) ===
    "strlen", "strcpy", "strncpy", "strcat", "strncat",
    "strcmp", "strncmp", "strchr", "strrchr", "strstr", "strstr",
    "strdup", "strndup", "strtok", "strtol", "strtod", "strtof",
    "atoi", "atol", "atof", "atoll",
    "memset", "memcpy", "memmove", "memcmp", "memchr",
    // === 内存函数 (2) ===
    "calloc", "realloc",
    // === 数学函数 (20) ===
    "sqrt", "sin", "cos", "tan", "asin", "acos", "atan", "atan2",
    "sinh", "cosh", "tanh",
    "pow", "exp", "log", "log10", "log2",
    "floor", "ceil", "fabs",
    // === 文件操作函数 (15) ===
    "fopen", "fclose", "fread", "fwrite", "fseek", "ftell",
    "rewind", "feof", "ferror", "clearerr",
    "fgetc", "fputc", "fgets", "fputs", "fflush",
    // === 时间函数 (6) ===
    "time", "clock", "difftime", "mktime", "strftime", "gmtime",
    // === 字符分类函数 (10) ===
    "isdigit", "isalpha", "isalnum", "isspace", "isupper",
    "islower", "isgraph", "isprint", "ispunct", "iscntrl",
    // === 大小写转换 (2) ===
    "toupper", "tolower",
    // === 系统接口函数 (6) ===
    "system", "getenv", "abort", "exit", "atexit", "signal",
    // === 其他 (5) ===
    "rand", "srand", "bsearch", "qsort", "raise"
};

StandardLibrary::StandardLibrary() = default;

StandardLibrary& StandardLibrary::instance() {
    static StandardLibrary instance;
    return instance;
}

bool StandardLibrary::isBuiltin(const std::string& funcName) const {
    for (const auto& func : builtinFunctions) {
        if (func == funcName) return true;
    }
    return false;
}

bool StandardLibrary::isStandardLib(const std::string& funcName) const {
    for (const auto& func : standardLibFunctions) {
        if (func == funcName) return true;
    }
    return false;
}

FunctionSource StandardLibrary::getFunctionSource(const std::string& funcName) const {
    if (isBuiltin(funcName)) return FunctionSource::Builtin;
    if (isStandardLib(funcName)) return FunctionSource::StandardLib;
    return FunctionSource::UserFFI;
}

void* StandardLibrary::builtin_malloc(size_t size) {
    // 通知内存沙箱分配内存
    MemorySandbox::instance().allocateMemory(size);
    // 检查是否应该停止执行
    if (MemorySandbox::instance().shouldStop()) {
        return nullptr;
    }
    return GarbageCollector::instance().allocate(GCObjectType::UserData, size);
}

void StandardLibrary::builtin_free(void* ptr) {
    // 通知内存沙箱释放内存
    // 注意：这里我们不知道释放的内存大小，所以暂时不更新内存使用量
    // 实际生产环境中，应该在分配内存时记录大小，以便在释放时正确更新
    GarbageCollector::instance().release(ptr);
}

void StandardLibrary::builtin_memset(void* ptr, int value, size_t num) {
    std::memset(ptr, value, num);
}

void* StandardLibrary::builtin_memcpy(void* dest, const void* src, size_t count) {
    return std::memcpy(dest, src, count);
}

int StandardLibrary::builtin_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = std::vprintf(format, args);
    va_end(args);
    return result;
}

void StandardLibrary::builtin_exit(int status) {
    std::exit(status);
}

int StandardLibrary::builtin_abs(int n) {
    return n >= 0 ? n : -n;
}

void* StandardLibrary::resolve(const std::string& funcName) {
    if (isBuiltin(funcName)) {
        if (funcName == "malloc") return reinterpret_cast<void*>(&builtin_malloc);
        if (funcName == "free") return reinterpret_cast<void*>(&builtin_free);
        if (funcName == "memset") return reinterpret_cast<void*>(&builtin_memset);
        if (funcName == "memcpy") return reinterpret_cast<void*>(&builtin_memcpy);
        if (funcName == "printf") return reinterpret_cast<void*>(&builtin_printf);
        if (funcName == "exit") return reinterpret_cast<void*>(&builtin_exit);
        if (funcName == "abs") return reinterpret_cast<void*>(&builtin_abs);
    }

    if (isStandardLib(funcName)) {
#ifdef _WIN32
        static HMODULE hModule = nullptr;
        if (!hModule) {
            hModule = LoadLibraryA("msvcrt.dll");
            if (!hModule) {
                hModule = LoadLibraryA("libucrtapp.dll");
            }
            if (!hModule) {
                hModule = LoadLibraryA("libucrtbase.dll");
            }
            if (!hModule) {
                hModule = LoadLibraryA("ucrtbase.dll");
            }
        }
        if (hModule) {
            void* addr = reinterpret_cast<void*>(GetProcAddress(hModule, funcName.c_str()));
            if (addr) return addr;
        }
#elif defined(CSE_EMBEDDED)
        // 在嵌入式平台上，标准库函数的地址会由代码生成器直接处理
        return nullptr;
#else
        // 在非嵌入式平台上，使用 dlopen 和 dlsym 获取标准库函数地址
        void* handle = dlopen("libc.so.6", RTLD_LAZY);
        if (handle) {
            void* addr = dlsym(handle, funcName.c_str());
            dlclose(handle);
            return addr;
        }
        return nullptr;
#endif
    }

    return nullptr;
}

} // namespace cse
