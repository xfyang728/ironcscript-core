#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* s1 = malloc(10);
    strcpy(s1, "Hello");
    printf("String: %s\n", s1);
    free(s1);
    return 0;
}
