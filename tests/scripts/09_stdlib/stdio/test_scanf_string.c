#include <stdio.h>

int main() {
    char name[100];
    int result = scanf("%s", name);
    printf("Hello, %s!\n", name);
    return result;
}