#include <stdio.h>

int main() {
    FILE* fp;
    int result = 0;

    fp = fopen("test_feof.txt", "r");
    if (fp) {
        char buffer[100];
        while (!feof(fp)) {
            if (fgets(buffer, sizeof(buffer), fp) == NULL) {
                break;
            }
        }
        printf("feof test: reached end of file, feof(fp)=%d\n", feof(fp));
        fclose(fp);
        result = 0;
    } else {
        printf("feof test: file does not exist (expected)\n");
        result = 0;
    }

    fp = fopen("test_feof.txt", "w");
    if (fp) {
        fprintf(fp, "Hello\n");
        fclose(fp);
        printf("feof test: file created successfully\n");
    }

    return result;
}