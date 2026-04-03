extern void println(int value);

void testSwitchBasic(int n) {
    switch (n) {
        case 1:
            println(101);
            break;
        case 2:
            println(102);
            break;
        case 3:
            println(103);
            break;
        default:
            println(100);
    }
}

void testSwitchFallThrough(int n) {
    switch (n) {
        case 1:
            println(1);
        case 2:
            println(2);
        case 3:
            println(3);
            break;
        default:
            println(0);
    }
}

void main() {
    println(1000);
    testSwitchBasic(1);
    testSwitchBasic(2);
    testSwitchBasic(3);
    testSwitchBasic(99);
    println(2000);
    testSwitchFallThrough(1);
    testSwitchFallThrough(2);
    println(9999);
}