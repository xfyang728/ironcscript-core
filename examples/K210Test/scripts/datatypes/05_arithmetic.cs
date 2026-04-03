extern void println(int value);

void testConstants() {
    println(100);
    println(200);
    println(300);
    println(-50);
    println(0);
}

void testArithmetic() {
    int a = 10;
    int b = 3;

    println(a + b);
    println(a - b);
    println(a * b);
    println(a / b);
    println(a % b);

    println(a + 5);
    println(a - 5);
    println(a * 2);
    println(a / 2);
    println(a % 2);
}

void testUnary() {
    int a = 10;
    int b = -5;

    println(-a);
    println(-b);
    println(a);
    println(b);
}

void testPrecedence() {
    int result = 2 + 3 * 4;
    println(result);

    result = (2 + 3) * 4;
    println(result);

    result = 10 - 3 - 2;
    println(result);

    result = 10 / 3 / 2;
    println(result);
}

void main() {
    println(1000);
    testConstants();
    println(2000);
    testArithmetic();
    println(3000);
    testUnary();
    println(4000);
    testPrecedence();
    println(9999);
}