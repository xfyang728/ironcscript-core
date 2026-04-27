#include <stdio.h>

int main() {
    FILE* fp;
    int pos;
    int ch;

    fp = fopen("test_rewind.txt", "w");
    if (fp) {
        fprintf(fp, "ABCDEFGH");
        fclose(fp);
    }

    fp = fopen("test_rewind.txt", "r");
    if (fp) {
        ch = fgetc(fp);
        ch = fgetc(fp);
        ch = fgetc(fp);
        pos = ftell(fp);
        printf("rewind test: before=%d\n", pos);
        rewind(fp);
        printf("rewind test: called rewind()\n");
        pos = ftell(fp);
        fclose(fp);
        printf("rewind test: after=%d\n", pos);
        printf("rewind test: PASSED\n");
        return 0;
    }
    printf("rewind test: FAILED fopen\n");
    return 1;
}
