extern void println(int value);

void testPointerBasic() {
    int a = 42;
    int *p;
    p = &a;
    println(*p);
}

void testAddressOf() {
    int x;
    int *ptr;
    x = 100;
    ptr = &x;
    println(*ptr);
}

void main() {
    println(1000);
    testPointerBasic();
    println(2000);
    testAddressOf();
    println(9999);
}