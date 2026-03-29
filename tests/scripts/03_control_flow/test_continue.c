// 测试 continue 语句
int main() {
    int sum = 0;
    int i = 0;
    
    // 测试 continue 在 for 循环中
    for (i = 0; i < 10; i++) {
        if (i == 5) {
            continue;
        }
        sum = sum + i;
    }
    
    // sum 应该是 0+1+2+3+4+6+7+8+9 = 40 (跳过5)
    return sum;
}
