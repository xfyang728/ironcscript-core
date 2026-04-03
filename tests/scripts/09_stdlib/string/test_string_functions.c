#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[50] = "World";
    char str3[100];
    char* result;
    
    // Test strlen
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    printf("strlen(str1) = %d\n", len1);
    printf("strlen(str2) = %d\n", len2);
    
    // Test strcpy
    strcpy(str3, str1);
    printf("strcpy(str3, str1) = %s\n", str3);
    
    // Test strcat
    strcat(str3, " ");
    strcat(str3, str2);
    printf("strcat(str3, str2) = %s\n", str3);
    
    // Test strcmp
    int cmp = strcmp(str1, str2);
    printf("strcmp(str1, str2) = %d\n", cmp);
    
    // Test strstr
    result = strstr(str3, "World");
    if (result) {
        printf("strstr(str3, \"World\") = %s\n", result);
    } else {
        printf("strstr(str3, \"World\") = not found\n");
    }
    
    return 0;
}