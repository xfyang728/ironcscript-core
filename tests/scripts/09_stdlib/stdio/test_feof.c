#include <stdio.h>

int main() {
    FILE* fp;
    int is_eof;

    fp = fopen("test_feof.txt", "w");
    if (fp) {
        fprintf(fp, "AB");
        fclose(fp);
    }

    fp = fopen("test_feof.txt", "r");
    if (fp) {
        fgetc(fp);
        fgetc(fp);
        fgetc(fp);
        is_eof = feof(fp);
        fclose(fp);
        printf("feof test: eof=%d\n", is_eof);
        if (is_eof != 0) {
            printf("feof test: PASSED\n");
            return 0;
        }
        printf("feof test: FAILED expected nonzero\n");
        return 1;
    }
    printf("feof test: FAILED fopen\n");
    return 1;
}
