#ifndef CSE_STDIO_H
#define CSE_STDIO_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// 文件类型
typedef void* FILE;

// 标准流
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

// 常量
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

// 函数声明
int printf(const char* format, ...);
int scanf(const char* format, ...);
int puts(const char* str);
int getchar(void);
int putchar(int c);
char* gets(char* buffer);

// 文件操作
FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
int fprintf(FILE* stream, const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int fgetc(FILE* stream);
int fputc(int c, FILE* stream);
char* fgets(char* buffer, int size, FILE* stream);
int fputs(const char* str, FILE* stream);

// 二进制 I/O
size_t fread(void* buffer, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);

// 文件定位
int fseek(FILE* stream, long offset, int origin);
long ftell(FILE* stream);
void rewind(FILE* stream);

// 错误处理
int feof(FILE* stream);
int ferror(FILE* stream);
void clearerr(FILE* stream);
int fflush(FILE* stream);

#ifdef __cplusplus
}
#endif

#endif