#include <stdio.h>

int main() {
    FILE* fp;
    int pos;

    fp = fopen("test_ftell.txt", "w");
    if (fp) {
        fprintf(fp, "ABCDEFGH");
        fclose(fp);
    }

    fp = fopen("test_ftell.txt", "r");
    if (fp) {
        pos = ftell(fp);
        printf("ftell test: init_pos=%d\n", pos);
        fseek(fp, 4, 0);
        pos = ftell(fp);
        fclose(fp);
        printf("ftell test: after_seek=%d\n", pos);
        if (pos == 4) {
            printf("ftell test: PASSED\n");
            return 0;
        }
        printf("ftell test: FAILED expected 4\n");
        return 1;
    }
    printf("ftell test: FAILED fopen\n");
    return 1;
}
