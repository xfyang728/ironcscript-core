#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];
    
    // 测试 fopen 和 fclose 函数
    fp = fopen("test_file.txt", "w+");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    printf("文件打开成功\n");
    
    // 测试 fwrite 函数
    const char* text = "Hello, File Operations!";
    size_t written = fwrite(text, 1, sizeof(text) - 1, fp);
    printf("写入了 %zu 个字符\n", written);
    
    // 测试 fseek 和 ftell 函数
    fseek(fp, 0, SEEK_SET);
    long position = ftell(fp);
    printf("文件指针位置：%ld\n", position);
    
    // 测试 fread 函数
    size_t read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[read] = '\0';
    printf("读取的内容：%s\n", buffer);
    
    // 测试 rewind 函数
    rewind(fp);
    position = ftell(fp);
    printf("rewind 后文件指针位置：%ld\n", position);
    
    // 测试 fgetc 和 fputc 函数
    int ch = fgetc(fp);
    printf("第一个字符：%c\n", ch);
    fputc('X', fp);
    
    // 测试 fgets 和 fputs 函数
    rewind(fp);
    fgets(buffer, sizeof(buffer), fp);
    printf("fgets 读取的内容：%s", buffer);
    
    // 测试 fflush 函数
    fflush(fp);
    printf("文件已刷新\n");
    
    // 测试 feof、ferror 和 clearerr 函数
    if (feof(fp)) {
        printf("文件结束\n");
    }
    if (ferror(fp)) {
        printf("文件错误\n");
        clearerr(fp);
        printf("错误已清除\n");
    }
    
    // 测试 fclose 函数
    fclose(fp);
    printf("文件已关闭\n");
    
    return 0;
}