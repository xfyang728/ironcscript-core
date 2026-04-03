#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];
    int value;

    fp = fopen("test_file.txt", "r");
    if (fp) {
        fscanf(fp, "%s", buffer);
        printf("buffer=%s\n", buffer);
        fscanf(fp, "%d", &value);
        printf("value=%d\n", value);
        fclose(fp);
        printf("File read successfully\n");
        return 0;
    } else {
        printf("Failed to open file for reading\n");
        return -1;
    }
}
