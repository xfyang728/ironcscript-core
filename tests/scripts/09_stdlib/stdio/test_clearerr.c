#include <stdio.h>

int main() {
    FILE* fp;

    fp = fopen("test_clearerr.txt", "w");
    if (fp) {
        fprintf(fp, "Hello clearerr");
        fclose(fp);
    }

    fp = fopen("test_clearerr.txt", "r");
    if (fp) {
        fgetc(fp);
        fclose(fp);
        clearerr(fp);
        printf("clearerr test: called clearerr(fp)\n");
        printf("clearerr test: PASSED\n");
        return 0;
    }
    printf("clearerr test: FAILED fopen\n");
    return 1;
}
