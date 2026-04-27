#include <stdio.h>;

export int strlen_test(const char* s) {
    int len = 0;
    while (s[len] != 0) {
        len = len + 1;
    }
    return len;
}

export void hello() {
    printf("string_module: hello!\n");
}
