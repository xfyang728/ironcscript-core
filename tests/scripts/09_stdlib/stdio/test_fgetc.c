#include <stdio.h>

int main() {
    FILE* fp;
    int result = 0;

    fp = fopen("test_fgetc.txt", "w");
    if (fp) {
        fprintf(fp, "ABC");
        fclose(fp);
    }

    fp = fopen("test_fgetc.txt", "r");
    if (fp) {
        int c1 = fgetc(fp);
        int c2 = fgetc(fp);
        int c3 = fgetc(fp);
        printf("fgetc test: read chars '%c', '%c', '%c'\n", c1, c2, c3);
        fclose(fp);
        result = (c1 == 'A' && c2 == 'B' && c3 == 'C') ? 0 : 1;
    } else {
        printf("fgetc test: failed to open file\n");
        result = 1;
    }

    return result;
}