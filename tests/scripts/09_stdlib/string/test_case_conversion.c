// #include <stdio.h>
// #include <ctype.h>

int main() {
    char lower = 'a';
    char upper = toupper(lower);
    printf("%c", upper); // Fixed: Use format specifier "%c" for a single character
    char lower2 = tolower(upper);
    printf("%c", lower2); // Fixed: Use format specifier "%c" for a single character
    return 0;
}