#include <stdio.h>

int main() {
    FILE* fp;
    int pos;
    int ch;

    fp = fopen("test_fseek.txt", "w");
    if (fp) {
        fprintf(fp, "ABCDEFGHIJ");
        fclose(fp);
    }

    fp = fopen("test_fseek.txt", "r");
    if (fp) {
        fseek(fp, 5, 0);
        pos = ftell(fp);
        ch = fgetc(fp);
        fclose(fp);
        printf("fseek test: pos=%d ch=%d\n", pos, ch);
        if (pos == 5) {
            if (ch == 70) {
                printf("fseek test: PASSED\n");
                return 0;
            }
        }
        printf("fseek test: FAILED pos=%d ch=%d\n", pos, ch);
        return 1;
    }
    printf("fseek test: FAILED fopen\n");
    return 1;
}
