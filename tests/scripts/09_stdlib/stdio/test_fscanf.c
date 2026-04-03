#include <stdio.h>

int test_fscanf() {
    FILE* fp;
    char buffer[100];
    int value;

    fp = fopen("test_fprintf.txt", "r");
    if (fp) {
        fscanf(fp, "%s %s %d", buffer, buffer, &value);
        printf("buffer=%s, value=%d\n", buffer, value);
        fclose(fp);
        return 0;
    }
    return -1;
}

int main() {
    return test_fscanf();
}
