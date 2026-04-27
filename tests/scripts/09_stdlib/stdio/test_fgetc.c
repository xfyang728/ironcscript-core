#include <stdio.h>

int main() {
    FILE* fp;
    int c1;
    int c2;
    int c3;

    fp = fopen("test_fgetc.txt", "w");
    if (fp) {
        fprintf(fp, "ABC");
        fclose(fp);
    }

    fp = fopen("test_fgetc.txt", "r");
    if (fp) {
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        c3 = fgetc(fp);
        fclose(fp);
        printf("fgetc test: chars=%d %d %d\n", c1, c2, c3);
        printf("fgetc test: PASSED\n");
        return 0;
    }
    printf("fgetc test: FAILED fopen\n");
    return 1;
}
