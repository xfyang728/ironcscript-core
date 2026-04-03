extern void printf(...);

void testValues(int a, int b) {
    printf("a=%d, b=%d\n", a, b);
}

void main() {
    printf("Test\n");
    testValues(5, 3);
    printf("End\n");
}