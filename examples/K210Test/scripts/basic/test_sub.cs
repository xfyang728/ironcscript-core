extern void printf(...);

void testSub(int a, int b) {
    int result = a - b;
    printf("testSub(%d, %d) = %d\n", a, b, result);
}

void main() {
    printf("1000\n");
    testSub(10, 3);
    printf("2000\n");
    testSub(100, 50);
    printf("3000\n");
}