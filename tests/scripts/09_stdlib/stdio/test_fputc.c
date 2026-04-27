#include <stdio.h>

int main() {
    FILE* fp;
    int ch;

    fp = fopen("test_fputc.txt", "w");
    if (fp) {
        fputc(65, fp);
        fputc(66, fp);
        fputc(67, fp);
        fclose(fp);
        printf("fputc test: wrote 3 chars\n");
        printf("fputc test: PASSED\n");
        return 0;
    }
    printf("fputc test: FAILED fopen\n");
    return 1;
}
