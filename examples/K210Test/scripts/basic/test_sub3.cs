extern void printf(...);

void testSub2(int a, int b) {
    printf("testSub2(%d, %d) = %d\n", a, b, a - b);
}

void main() {
    printf("1000\n");
    testSub2(10, 3);
    printf("2000\n");
    testSub2(100, 50);
    printf("3000\n");
}