int main() {
    char buffer[100];
    char str[50];
    int num;
    float fnum;
    FILE *file;
    
    // Test printf (already tested in other files, but included for completeness)
    printf("Testing input/output functions...\n");
    
    // Test sprintf
    sprintf(buffer, "String: %s, Number: %d, Float: %.2f", "test", 123, 45.67);
    printf("sprintf result: %s\n", buffer);
    
    // Test puts
    puts("Testing puts function");
    
    // Test putchar
    putchar('H');
    putchar('e');
    putchar('l');
    putchar('l');
    putchar('o');
    putchar('\n');
    
    // Test gets (note: gets is unsafe, but included for compatibility)
    printf("Enter a string: ");
    gets(str);
    printf("gets result: %s\n", str);
    
    // Test fgets
    printf("Enter another string: ");
    fgets(str, sizeof(str), stdin);
    printf("fgets result: %s\n", str);
    
    // Test fprintf and fputs with a file
    file = fopen("test_output.txt", "w");
    if (file) {
        fprintf(file, "This is a test: %d\n", 42);
        fputs("This is a fputs test\n", file);
        fclose(file);
        printf("File written successfully\n");
        
        // Test fscanf
        file = fopen("test_output.txt", "r");
        if (file) {
            fscanf(file, "This is a test: %d\n", &num);
            printf("fscanf result: %d\n", num);
            fclose(file);
        }
    }
    
    // Test sscanf
    char test_str[] = "Number: 123, Float: 45.67";
    sscanf(test_str, "Number: %d, Float: %f", &num, &fnum);
    printf("sscanf result: num=%d, fnum=%.2f\n", num, fnum);
    
    return 0;
}
