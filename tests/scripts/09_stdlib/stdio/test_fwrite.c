#include <stdio.h>

int main() {
    FILE* fp;
    char data[20];
    char buffer[100];
    int bytes;
    int i;

    i = 0;
    while (i < 20) {
        data[i] = 65 + i;
        i = i + 1;
    }

    fp = fopen("test_fwrite.txt", "w");
    if (fp) {
        bytes = fwrite(data, 1, 20, fp);
        fclose(fp);
        printf("fwrite test: wrote=%d bytes\n", bytes);
        if (bytes == 20) {
            printf("fwrite test: PASSED\n");
            return 0;
        }
        printf("fwrite test: FAILED expected 20\n");
        return 1;
    }
    printf("fwrite test: FAILED fopen\n");
    return 1;
}
