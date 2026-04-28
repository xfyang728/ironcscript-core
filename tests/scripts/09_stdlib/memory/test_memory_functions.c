#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void* ptr1 = malloc(100);
    memset(ptr1, 0, 100);
    printf("memset done\n");
    free(ptr1);
    printf("malloc test: PASSED\n");
    return 0;
}
