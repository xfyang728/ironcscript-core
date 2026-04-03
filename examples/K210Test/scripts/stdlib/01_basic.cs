extern void println(int value);
extern void delay(int ms);
extern int millis();

void testDelay() {
    println(1000);
    delay(10);
    println(1001);
}

void testMillis() {
    int t1;
    int t2;
    println(2000);
    t1 = millis();
    delay(5);
    t2 = millis();
    println(t1);
    println(t2);
}

void testMath() {
    int a;
    int b;
    int c;
    a = 10;
    b = 3;
    c = a / b;
    println(c);
    c = a % b;
    println(c);
}

void testAbs() {
    int a;
    int b;
    a = -5;
    b = 5;
    if (a < 0) {
        a = 0 - a;
    }
    if (b < 0) {
        b = 0 - b;
    }
    println(a);
    println(b);
}

void main() {
    println(100);
    testDelay();
    println(300);
    testMillis();
    println(500);
    testMath();
    println(700);
    testAbs();
    println(999);
}