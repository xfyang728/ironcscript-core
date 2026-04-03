#ifndef CSE_STDLIB_H
#define CSE_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

// 函数声明
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void* calloc(size_t count, size_t size);

// 字符串转换
int atoi(const char* str);
long atol(const char* str);
double atof(const char* str);

// 随机数
int rand(void);
void srand(unsigned int seed);

// 系统函数
int system(const char* command);
char* getenv(const char* name);

// 退出函数
void exit(int status);
void abort(void);

#ifdef __cplusplus
}
#endif

#endif