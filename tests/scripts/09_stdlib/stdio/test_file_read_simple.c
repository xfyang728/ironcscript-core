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
        return 0;
    }
    return -1;
}
