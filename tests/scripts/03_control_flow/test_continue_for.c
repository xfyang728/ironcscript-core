// 测试 continue 在 for 循环中 - 跳过偶数
int main() {
    int sum = 0;
    int i = 0;
    
    for (i = 0; i < 10; i = i + 1) {
        if (i % 2 == 0) {
            continue;
        }
        sum = sum + i;
    }
    // sum = 1 + 3 + 5 + 7 + 9 = 25
    
    return sum;
}
