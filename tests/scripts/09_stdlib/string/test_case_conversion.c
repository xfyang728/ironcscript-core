#include <stdio.h>
#include <ctype.h>

int main() {
    // 测试 toupper 函数
    char lowercase = 'a';
    char uppercase = toupper(lowercase);
    printf("toupper('%c') = '%c'\n", lowercase, uppercase);
    
    // 测试 tolower 函数
    char uppercase2 = 'Z';
    char lowercase2 = tolower(uppercase2);
    printf("tolower('%c') = '%c'\n", uppercase2, lowercase2);
    
    // 测试非字母字符
    char non_alpha = '5';
    char result1 = toupper(non_alpha);
    char result2 = tolower(non_alpha);
    printf("toupper('%c') = '%c', tolower('%c') = '%c'\n", non_alpha, result1, non_alpha, result2);
    
    return 0;
}