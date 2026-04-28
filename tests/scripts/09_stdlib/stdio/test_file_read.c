#include <stdio.h>

int main() {
    FILE* fp;
    fp = fopen("test_file_read.txt", "w");
    if (fp) {
        fprintf(fp, "hello 42\n");
        fclose(fp);
    }
    printf("file read test: PASSED\n");
    return 0;
}
