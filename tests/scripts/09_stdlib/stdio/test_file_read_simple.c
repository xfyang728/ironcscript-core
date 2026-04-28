#include <stdio.h>

int main() {
    FILE* fp;
    fp = fopen("test_file_simple.txt", "w");
    if (fp) {
        fprintf(fp, "hello");
        fclose(fp);
    }
    printf("file read simple: PASSED\n");
    return 0;
}
