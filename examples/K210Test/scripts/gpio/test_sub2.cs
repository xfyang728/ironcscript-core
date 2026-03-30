extern void println(int value);

void testSub2(int a, int b) {
    int c = a - b;
    println(c);
}

void main() {
    println(1000);
    testSub2(10, 3);
    println(2000);
}