#include <stdlib.h>

int main() {
    int result = 0;
    char* ptr = malloc(100);
    memset(ptr, 0, 50);
    free(ptr);
    return result;
}