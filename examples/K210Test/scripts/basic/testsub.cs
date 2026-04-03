extern void printf(...);

void testsub(int a, int b) {
    printf("testsub(%d, %d)\n", a, b);
}

void main() {
    printf("1000\n");
    int a = 10;
    int b = 3;
    testsub(a + b, a - b);
    printf("2000\n");
}