#include <stdio.h>

int test_fprintf() {
    FILE* fp;
    fp = fopen("test_fprintf.txt", "w");
    if (fp) {
        fprintf(fp, "Test %d %s\n", 123, "hello");
        fclose(fp);
        return 0;
    }
    return -1;
}

int main() {
    return test_fprintf();
}
