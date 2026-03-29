// 测试错误处理
int main() {
    int x = 10;
    int y = 20;
    int sum = add(x, y); // 未定义的函数
    int product = multiply(x, y); // 未定义的函数
    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);
    return sum + product;
}
