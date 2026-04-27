#include <stdio.h>

int main() {
    FILE* fp;
    int err;

    fp = fopen("test_ferror.txt", "w");
    if (fp) {
        fprintf(fp, "Hello ferror");
        fclose(fp);
    }

    fp = fopen("test_ferror.txt", "r");
    if (fp) {
        fgetc(fp);
        fclose(fp);
        err = ferror(fp);
        printf("ferror test: error=%d\n", err);
        if (err == 0) {
            printf("ferror test: PASSED\n");
            return 0;
        }
        printf("ferror test: FAILED expected 0\n");
        return 1;
    }
    printf("ferror test: FAILED fopen\n");
    return 1;
}
