#include <stdio.h>;

import "math_module" as math;

int main() {
    int result = math.add(10, 20);
    printf("import math: math.add(10, 20) = %d\n", result);
    if (result == 30) {
        printf("import math: PASSED\n");
    } else {
        printf("import math: FAILED (expected 30, got %d)\n", result);
    }
    return 0;
}
