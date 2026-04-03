extern void println(int value);

void testStructBasic() {
    int x;
    int y;
    x = 10;
    y = 20;
    println(x);
    println(y);
}

void testStructPointers() {
    int x;
    int y;
    int *px;
    int *py;
    px = &x;
    py = &y;
    x = 100;
    y = 200;
    println(*px);
    println(*py);
}

void testStructNested() {
    int a;
    int b;
    int c;
    a = 1;
    b = 2;
    c = 3;
    println(a);
    println(b);
    println(c);
}

void main() {
    println(1000);
    testStructBasic();
    println(2000);
    testStructPointers();
    println(3000);
    testStructNested();
    println(9999);
}