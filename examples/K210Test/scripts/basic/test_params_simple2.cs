extern void printf(...);

void testValues(int a, int b) {
    printf("a=%d, b=%d\n", a, b);
}

void main() {
    printf("Start\n");
    int x = 5;
    int y = 2;
    int diff = x - y;
    printf("diff=%d\n", diff);
    testValues(x, y);
    printf("End\n");
}