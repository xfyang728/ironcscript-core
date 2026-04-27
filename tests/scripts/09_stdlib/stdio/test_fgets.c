#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];

    fp = fopen("test_fgets.txt", "w");
    if (fp) {
        fprintf(fp, "Hello fgets!\n");
        fclose(fp);
    }

    fp = fopen("test_fgets.txt", "r");
    if (fp) {
        printf("fgets test: calling fgets()\n");
        fgets(buffer, 100, fp);
        fclose(fp);
        printf("fgets test: PASSED\n");
        return 0;
    }
    printf("fgets test: FAILED fopen\n");
    return 1;
}
