extern void println(int value);

void testSub2(int a, int b) {
    println(a - b);
}

void main() {
    println(1000);
    testSub2(10, 3);
    println(2000);
    testSub2(100, 50);
    println(3000);
}