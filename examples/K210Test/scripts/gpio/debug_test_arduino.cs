// Arduino风格调试日志示例
// 演示如何使用 print/println 输出整数调试信息

extern void delay(int ms);
extern void print(int value);
extern void println(int value);

void setup(int a) {
    println(a);
    print(200);
}
int add(int a, int b) {
    return a + b;
}

void debugDelay() {
    println(1000);
    delay(500);
}

void main() {
    setup(100);
    int result = add(5, 7);
    println(result);
    debugDelay();
    println(999);
    // setup();
}