#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 信号处理函数
void signal_handler(int signum) {
    printf("信号 %d 被捕获\n", signum);
}

// atexit 回调函数
void exit_handler() {
    printf("程序即将退出\n");
}

int main() {
    // 测试 getenv 函数
    char* path = getenv("PATH");
    if (path != NULL) {
        printf("PATH 环境变量存在\n");
    } else {
        printf("PATH 环境变量不存在\n");
    }
    
    // 测试 atexit 函数
    atexit(exit_handler);
    printf("已注册退出处理函数\n");
    
    // 测试 signal 函数
    signal(SIGINT, signal_handler);
    printf("已注册 SIGINT 信号处理函数\n");
    
    // 注意：system 函数可能会启动外部进程，这里只做简单测试
    // system("echo 'Hello from system call'");
    
    // 注意：abort 和 exit 会终止程序，这里不实际调用
    printf("系统接口函数测试完成\n");
    
    return 0;
}