#include <stdio.h>

int main() {
    FILE* fp;
    int result = 0;

    fp = fopen("test_clearerr.txt", "w");
    if (fp) {
        fprintf(fp, "Testing clearerr\n");
        fclose(fp);

        fp = fopen("test_clearerr.txt", "r");
        if (fp) {
            char buffer[100];
            fgets(buffer, sizeof(buffer), fp);
            fclose(fp);

            clearerr(fp);
            printf("clearerr test: cleared successfully\n");
            result = 0;
        } else {
            printf("clearerr test: failed to open file\n");
            result = 1;
        }
    } else {
        printf("clearerr test: failed to create file\n");
        result = 1;
    }

    return result;
}