#include <stdio.h>

int main() {
    FILE* fp;
    int result = 0;

    fp = fopen("test_fflush.txt", "w");
    if (fp) {
        fprintf(fp, "Testing fflush\n");
        fflush(fp);
        printf("fflush test: flushed successfully\n");
        fclose(fp);
        result = 0;
    } else {
        printf("fflush test: failed to open file\n");
        result = 1;
    }

    return result;
}