extern void println(int value);

void testIf() {
    int a = 10;

    if (a > 5) {
        println(1);
    }

    if (a < 5) {
        println(2);
    }

    if (a == 10) {
        println(3);
    }
}

void testIfElse() {
    int a = 10;

    if (a > 5) {
        println(10);
    } else {
        println(0);
    }

    if (a < 5) {
        println(0);
    } else {
        println(20);
    }
}

void testIfElseIf() {
    int a = 5;

    if (a == 1) {
        println(1);
    } else if (a == 2) {
        println(2);
    } else if (a == 5) {
        println(5);
    } else {
        println(0);
    }
}

void main() {
    println(1000);
    testIf();
    println(2000);
    testIfElse();
    println(3000);
    testIfElseIf();
    println(9999);
}