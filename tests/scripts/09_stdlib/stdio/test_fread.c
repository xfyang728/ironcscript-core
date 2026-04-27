#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];
    int bytes;

    fp = fopen("test_fread.txt", "w");
    if (fp) {
        fprintf(fp, "ABCDEFGH");
        fclose(fp);
    }

    fp = fopen("test_fread.txt", "r");
    if (fp) {
        bytes = fread(buffer, 1, 8, fp);
        fclose(fp);
        printf("fread test: bytes=%d\n", bytes);
        if (bytes == 8) {
            printf("fread test: PASSED\n");
            return 0;
        }
        printf("fread test: FAILED expected 8 bytes\n");
        return 1;
    }
    printf("fread test: FAILED fopen\n");
    return 1;
}
