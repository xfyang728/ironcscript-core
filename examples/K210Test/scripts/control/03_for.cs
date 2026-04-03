extern void println(int value);

void testForBasic() {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        println(i);
    }
}

void testForSum() {
    int sum = 0;
    int i;
    for (i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    println(sum);
}

void testForReverse() {
    int i;
    for (i = 5; i > 0; i = i - 1) {
        println(i);
    }
}

void main() {
    println(1000);
    testForBasic();
    println(2000);
    testForSum();
    println(3000);
    testForReverse();
    println(9999);
}