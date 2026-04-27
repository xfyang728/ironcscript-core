#include <stdio.h>;

import "string_module" as str;

int main() {
    str.hello();
    int len = str.strlen_test("hello");
    printf("import string: strlen_test('hello') = %d\n", len);
    if (len == 5) {
        printf("import string: PASSED\n");
    } else {
        printf("import string: FAILED (expected 5, got %d)\n", len);
    }
    return 0;
}
