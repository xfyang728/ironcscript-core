extern void println(int value);

void testsub(int a, int b) {
    println(a);
    println(b);
}

void main() {
    println(1000);
    testsub(3, 10-3);
    println(2000);
}