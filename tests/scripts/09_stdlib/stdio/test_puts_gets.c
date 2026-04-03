#include <stdio.h>

int main() {
    char buffer[100];
    puts("Please enter your name:");
    gets(buffer);
    puts("Hello, ");
    puts(buffer);
    return 0;
}