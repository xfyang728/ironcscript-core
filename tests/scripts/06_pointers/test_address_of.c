int main() {
    int a = 42; // 明确初始化值
    int *p = &a;
    return *p; // 应该返回42
}