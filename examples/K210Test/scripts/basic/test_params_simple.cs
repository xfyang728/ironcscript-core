extern void printf(...);

void testValues(int a, int b) {
    printf("a=%d, b=%d\n", a, b);
}

void main() {
    printf("Start\n");
    int x = 5;
    int y = 3;
    testValues(x, y);
    printf("End\n");
}