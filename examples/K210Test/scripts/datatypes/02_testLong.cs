extern void printf(...);

void testLong() {
    long a = 100000L;
    long b = 50000L;
    printf("100000 + 50000 = %d\n", (int)(a + b));
    printf("100000 - 50000 = %d\n", (int)(a - b));
}

void main() {
    printf("=== Long Tests ===\n");
    testLong();
    printf("=== DONE ===\n");
}
