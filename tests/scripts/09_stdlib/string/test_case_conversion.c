#include <stdio.h>
#include <ctype.h>

int main() {
    char lower = 'a';
    char upper = toupper(lower);
    printf("%c\n", upper);
    char lower2 = tolower(upper);
    printf("%c\n", lower2);
    return 0;
}