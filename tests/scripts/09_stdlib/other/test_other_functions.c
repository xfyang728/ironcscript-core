#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 比较函数用于 qsort 和 bsearch
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // 测试 srand 和 rand 函数
    srand(time(NULL));
    printf("随机数测试：\n");
    for (int i = 0; i < 5; i++) {
        int random = rand();
        printf("随机数 %d: %d\n", i+1, random);
    }
    
    // 测试 qsort 函数
    int arr[] = {5, 2, 8, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("\n排序前数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    qsort(arr, n, sizeof(int), compare);
    
    printf("排序后数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // 测试 bsearch 函数
    int key = 3;
    int* result = (int*)bsearch(&key, arr, n, sizeof(int), compare);
    if (result != NULL) {
        printf("找到元素 %d\n", *result);
    } else {
        printf("未找到元素 %d\n", key);
    }
    
    // 注意：raise 函数会发送信号，这里不实际调用
    printf("\n其他函数测试完成\n");
    
    return 0;
}