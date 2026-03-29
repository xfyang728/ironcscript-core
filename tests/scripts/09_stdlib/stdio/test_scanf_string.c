// 测试 scanf 字符串输入
int main() {
    char name[100];
    int result = scanf("%s", name);
    printf("Hello, %s!\n", name);
    
    // 返回scanf的成功读取项数作为测试结果
    // 如果成功读取一个字符串，返回1；否则返回0
    return result;
}