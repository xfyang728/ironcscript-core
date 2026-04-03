#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void* ptr1;
    void* ptr2;
    char buffer[50];
    
    // Test malloc
    ptr1 = malloc(100);
    if (ptr1) {
        printf("malloc(100) = %p\n", ptr1);
        
        // Test memset
        memset(ptr1, 0, 100);
        printf("memset(ptr1, 0, 100) done\n");
        
        // Test memcpy
        strcpy(buffer, "Hello, World!");
        memcpy(ptr1, buffer, strlen(buffer) + 1);
        printf("memcpy(ptr1, buffer, %d) done\n", strlen(buffer) + 1);
        printf("Content: %s\n", (char*)ptr1);
        
        // Test realloc
        ptr2 = realloc(ptr1, 200);
        if (ptr2) {
            printf("realloc(ptr1, 200) = %p\n", ptr2);
            strcat((char*)ptr2, " Reallocated");
            printf("Content after realloc: %s\n", (char*)ptr2);
            
            // Test free
            free(ptr2);
            printf("free(ptr2) done\n");
        } else {
            printf("realloc failed\n");
            free(ptr1);
        }
    } else {
        printf("malloc failed\n");
    }
    
    return 0;
}