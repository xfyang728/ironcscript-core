extern void printf(...);

void testBool() {
    int trueVal = 1;
    int falseVal = 0;
    printf("true = %d, false = %d\n", trueVal, falseVal);
}

void main() {
    printf("=== Bool Tests ===\n");
    testBool();
    printf("=== DONE ===\n");
}
