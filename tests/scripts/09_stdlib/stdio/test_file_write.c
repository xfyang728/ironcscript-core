int write_file() {
    FILE* fp;
    fp = fopen("test_file.txt", "w");
    if (fp) {
        fprintf(fp, "Hello, File!\n");
        fprintf(fp, "Value: %d\n", 42);
        fclose(fp);
        printf("File written successfully\n");
        return 0;
    } else {
        printf("Failed to open file for writing\n");
        return -1;
    }
}

int main() {
    return write_file();
}
