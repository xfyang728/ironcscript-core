extern void println(int value);

void testRelational() {
    int a = 10;
    int b = 20;

    println(a == b);
    println(a != b);
    println(a < b);
    println(a > b);
    println(a <= b);
    println(a >= b);
}

void testLogical() {
    int t = 1;
    int f = 0;

    println(t && f);
    println(t && t);
    println(f || f);
    println(t || f);
    println(!t);
    println(!f);
}

void testBitwise() {
    int a = 5;
    int b = 3;

    println(a & b);
    println(a | b);
    println(a ^ b);
    println(~a);
    println(a << 1);
    println(a >> 1);
}

void main() {
    println(1000);
    testRelational();
    println(2000);
    testLogical();
    println(3000);
    testBitwise();
    println(9999);
}