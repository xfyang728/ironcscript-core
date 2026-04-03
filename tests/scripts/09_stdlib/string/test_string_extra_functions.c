#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str1[50] = "Hello";
    char str2[50] = "World";
    char str3[100] = "";
    char str4[50] = "Hello, World!";
    char* result;
    int num;
    long lnum;
    double dnum;
    float fnum;
    long long ll_num;
    
    // Test strncpy
    strncpy(str3, str1, 3);
    str3[3] = '\0'; // Ensure null termination
    printf("strncpy(str3, str1, 3) = %s\n", str3);
    
    // Test strncat
    strncat(str3, " ", 1);
    strncat(str3, str2, 3);
    printf("strncat result: %s\n", str3);
    
    // Test strncmp
    int ncmp = strncmp(str1, "Hell", 4);
    printf("strncmp(str1, \"Hell\", 4) = %d\n", ncmp);
    
    // Test strchr
    result = strchr(str4, 'W');
    if (result) {
        printf("strchr(str4, 'W') = %s\n", result);
    } else {
        printf("strchr(str4, 'W') = not found\n");
    }
    
    // Test strrchr
    result = strrchr(str4, 'o');
    if (result) {
        printf("strrchr(str4, 'o') = %s\n", result);
    } else {
        printf("strrchr(str4, 'o') = not found\n");
    }
    
    // Test strdup
    result = strdup(str1);
    if (result) {
        printf("strdup(str1) = %s\n", result);
        free(result);
    }
    
    // Test strndup
    result = strndup(str2, 3);
    if (result) {
        printf("strndup(str2, 3) = %s\n", result);
        free(result);
    }
    
    // Test strtok
    char str5[] = "Hello,World,Test";
    result = strtok(str5, ",");
    while (result != NULL) {
        printf("strtok result: %s\n", result);
        result = strtok(NULL, ",");
    }
    
    // Test atoi
    num = atoi("123");
    printf("atoi(\"123\") = %d\n", num);
    
    // Test atol
    lnum = atol("123456");
    printf("atol(\"123456\") = %ld\n", lnum);
    
    // Test atof
    dnum = atof("123.45");
    printf("atof(\"123.45\") = %f\n", dnum);
    
    // Test atoll
    ll_num = atoll("1234567890123");
    printf("atoll(\"1234567890123\") = %lld\n", ll_num);
    
    // Test strtol
    char str6[] = "12345abc";
    char* endptr;
    lnum = strtol(str6, &endptr, 10);
    printf("strtol(\"12345abc\") = %ld, remaining: %s\n", lnum, endptr);
    
    // Test strtod
    char str7[] = "123.45abc";
    dnum = strtod(str7, &endptr);
    printf("strtod(\"123.45abc\") = %f, remaining: %s\n", dnum, endptr);
    
    // Test strtof
    char str8[] = "123.45abc";
    fnum = strtof(str8, &endptr);
    printf("strtof(\"123.45abc\") = %f, remaining: %s\n", fnum, endptr);
    
    return 0;
}
