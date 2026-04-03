extern void printf(...);

void testInt() {
    int a = 42;
    int b = -17;
    int c = a + b;
    printf("42 + -17 = %d\n", c);
    printf("42 - -17 = %d\n", a - b);
    printf("42 * -17 = %d\n", a * b);
    printf("42 / -17 = %d\n", a / b);
    printf("42 %% -17 = %d\n", a % b);
}

void testLong() {
    long a = 100000L;
    long b = 50000L;
    printf("100000 + 50000 = %d\n", (int)(a + b));
    printf("100000 - 50000 = %d\n", (int)(a - b));
}

void testChar() {
    char c = 65;
    printf("char 65 = '%c'\n", c);
    char c2 = c + 1;
    printf("char 66 = '%c'\n", c2);
}

void testBool() {
    int trueVal = 1;
    int falseVal = 0;
    printf("true = %d, false = %d\n", trueVal, falseVal);
}

void main() {
    printf("=== Integer Tests ===\n");
    testInt();
    printf("=== Long Tests ===\n");
    testLong();
    printf("=== Char Tests ===\n");
    testChar();
    printf("=== Bool Tests ===\n");
    testBool();
    printf("=== DONE ===\n");
}