#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];
    int result = 0;

    fp = fopen("test_fgets.txt", "w");
    if (fp) {
        fprintf(fp, "Hello, World!\n");
        fprintf(fp, "Testing fgets\n");
        fclose(fp);
    }

    fp = fopen("test_fgets.txt", "r");
    if (fp) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("fgets test: read line: '%s'\n", buffer);
        }
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("fgets test: read line: '%s'\n", buffer);
        }
        fclose(fp);
        result = 0;
    } else {
        printf("fgets test: failed to open file\n");
        result = 1;
    }

    return result;
}