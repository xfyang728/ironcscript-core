extern void println(int value);

void testWhile() {
    int i = 0;
    while (i < 5) {
        println(i);
        i = i + 1;
    }
}

void testWhileSum() {
    int sum = 0;
    int i = 1;
    while (i <= 10) {
        sum = sum + i;
        i = i + 1;
    }
    println(sum);
}

void testDoWhile() {
    int i = 0;
    do {
        println(i);
        i = i + 1;
    } while (i < 3);
}

void main() {
    println(1000);
    testWhile();
    println(2000);
    testWhileSum();
    println(3000);
    testDoWhile();
    println(9999);
}