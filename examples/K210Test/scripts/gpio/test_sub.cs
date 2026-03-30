extern void println(int value);

void testSub(int a, int b) {
    int result = a - b;
    println(result);
}

void main() {
    println(1000);
    testSub(10, 3);
    println(2000);
    testSub(100, 50);
    println(3000);
}