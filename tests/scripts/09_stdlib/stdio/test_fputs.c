#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];

    fp = fopen("test_fputs.txt", "w");
    if (fp) {
        printf("fputs test: calling fputs()\n");
        fputs("Hello fputs!", fp);
        fclose(fp);
        printf("fputs test: PASSED\n");
        return 0;
    }
    printf("fputs test: FAILED fopen\n");
    return 1;
}
