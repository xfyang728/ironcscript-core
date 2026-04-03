#include <stdio.h>

int main() {
    FILE* fp;
    char buffer[100];
    int value;

    fp = fopen("test_file.txt", "w");
    if (fp) {
        fprintf(fp, "Hello, File!\n");
        fprintf(fp, "Value: %d\n", 42);
        fclose(fp);
        printf("File written successfully\n");

        fp = fopen("test_file.txt", "r");
        if (fp) {
            fscanf(fp, "%s", buffer);
            printf("buffer=%s\n", buffer);
            fscanf(fp, "%d", &value);
            printf("value=%d\n", value);
            fclose(fp);
            printf("File read successfully\n");
        } else {
            printf("Failed to open file for reading\n");
        }
    } else {
        printf("Failed to open file for writing\n");
    }

    return 0;
}
