#include <stdio.h>

int main() {
    FILE* fp;
    int ret;

    fp = fopen("test_fflush.txt", "w");
    if (fp) {
        fprintf(fp, "Testing fflush");
        ret = fflush(fp);
        fclose(fp);
        printf("fflush test: flush_ret=%d\n", ret);
        printf("fflush test: PASSED\n");
        return 0;
    }
    printf("fflush test: FAILED fopen\n");
    return 1;
}
