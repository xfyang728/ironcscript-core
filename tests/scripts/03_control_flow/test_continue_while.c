// 测试 continue 在 while 循环中
int main() {
    int sum = 0;
    int i = 0;
    
    while (i < 5) {
        if (i == 2) {
            i = i + 1;
            continue;
        }
        sum = sum + i;
        i = i + 1;
    }
    // sum = 0 + 1 + 3 + 4 = 8
    
    return sum;
}
