// Arduino风格调试日志示例
// 演示如何使用 print/println 输出整数调试信息

extern void delay(int ms);
extern void printf(...);

void setup(int a) {
    printf("%d\n", a);
    printf("%d\n", 200);
}
int add(int a, int b) {
    return a + b;
}

void debugDelay() {
    printf("%d\n", 1000);
    delay(500);
}

void main() {
    setup(100);
    int result = add(5, 7);
    printf("%d\n", result);
    debugDelay();
    printf("%d\n", 999);
}