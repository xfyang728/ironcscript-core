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

void main() {
    printf("=== Integer Tests ===\n");
    testInt();
    printf("=== DONE ===\n");
}
