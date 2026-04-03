extern void printf(...);

void testChar() {
    char c = 65;
    printf("char 65 = '%c'\n", c);
    char c2 = c + 1;
    printf("char 66 = '%c'\n", c2);
}

void main() {
    printf("=== Char Tests ===\n");
    testChar();
    printf("=== DONE ===\n");
}
