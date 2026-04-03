// test_func_call.cs - 测试函数调用作为 printf 参数
extern void printf(...);

int getValue() {
    return 100;
}

void main() {
    printf("Value: %d\n", getValue());
}