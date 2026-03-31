extern void println(int value);

void testsub(int a, int b) {
    println(a);
    println(b);
}

void main() {
    println(1000);
    int a = 10;
    int b = 3;
    testsub(3, a - b);
    println(2000);
}
