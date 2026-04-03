#include <stdio.h>

int main() {
    FILE* fp;
    int result = 0;

    fp = fopen("test_ferror.txt", "r");
    if (fp) {
        fclose(fp);
    } else {
        printf("ferror test: file does not exist, ferror(fp)=%d\n", ferror(fp));
    }

    fp = fopen("test_ferror.txt", "w");
    if (fp) {
        fprintf(fp, "Testing ferror\n");
        fclose(fp);
        printf("ferror test: file written successfully\n");
        result = 0;
    } else {
        printf("ferror test: failed to create file\n");
        result = 1;
    }

    return result;
}