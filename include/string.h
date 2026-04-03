#ifndef CSE_STRING_H
#define CSE_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

// 函数声明
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t n);
char* strchr(const char* str, int c);
char* strrchr(const char* str, int c);
char* strstr(const char* haystack, const char* needle);

// 内存操作
void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
void* memmove(void* dest, const void* src, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);

#ifdef __cplusplus
}
#endif

#endif