#include <stdio.h>;

export int add(int a, int b) {
    return a + b;
}

export int sub(int a, int b) {
    return a - b;
}

int internal_helper() {
    return 999;
}
