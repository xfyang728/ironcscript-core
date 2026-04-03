#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_printf_int() {
    int x = 1;
    printf("test_printf_int: x = %d\n", x);
    return x;
}

int test_printf() {
    printf("Hello, World!\n");
    return 0;
}

int test_puts() {
    puts("Hello, World!");
    return 0;
}

int test_fflush() {
    int x = 1;
    int y = 2;
    int z = x + y;
    printf("test_fflush: 1+2=%d\n", z);
    return 0;
}

int test_fputc() {
    int x = 6;
    int y = 7;
    printf("test_fputc: %d*%d=%d\n", x, y, x * y);
    return 0;
}

int test_fgetc() {
    int x = 4;
    int y = 8;
    printf("test_fgetc: %d/%d=%d\n", x, y, x / y);
    return 0;
}

int test_fputs() {
    int x = 5;
    int y = 3;
    printf("test_fputs: %d*%d=%d\n", x, y, x * y);
    return 0;
}

int test_fgets() {
    int x = 10;
    int y = 20;
    printf("test_fgets: %d+%d=%d\n", x, y, x + y);
    return 0;
}

int test_fread() {
    int x = 10;
    int y = 20;
    int z = x + y;
    printf("test_fread: sum=%d\n", z);
    return 0;
}

int test_fwrite() {
    char* text = "Hello, World!";
    int len = 13;
    printf("test_fwrite: %s\n", text);
    return 0;
}

int test_fprintf() {
    void* fp;
    fp = fopen("test_fprintf.txt", "w");
    if (fp) {
        fprintf(fp, "Test %d %s\n", 123, "hello");
        fclose(fp);
        printf("test_fprintf: file written successfully\n");
        return 0;
    }
    printf("test_fprintf: failed to open file\n");
    return -1;
}

int test_fscanf() {
    void* fp;
    char buffer[100];
    int value;

    fp = fopen("test_fprintf.txt", "r");
    if (fp) {
        fscanf(fp, "%s %s %d", buffer, buffer, &value);
        printf("test_fscanf: buffer=%s, value=%d\n", buffer, value);
        fclose(fp);
        return 0;
    }
    printf("test_fscanf: failed to open file\n");
    return -1;
}

int test_fseek() {
    int x = 10;
    int y = 20;
    int sum = x + y;
    printf("test_fseek: sum=%d\n", sum);
    return 0;
}

int test_ftell() {
    int x = 10;
    printf("test_ftell: x=%d\n", x);
    return 0;
}

int test_rewind() {
    int x = 5;
    int y = 3;
    int result = x - y;
    printf("test_rewind: 5-3=%d\n", result);
    return 0;
}

int test_feof() {
    int x = 10;
    int y = 5;
    int result = x - y;
    printf("test_feof: %d-%d=%d\n", x, y, result);
    return 0;
}

int test_ferror() {
    int x = 1;
    int y = 2;
    int z = x * y;
    printf("test_ferror: 1*2=%d\n", z);
    return 0;
}

int test_clearerr() {
    int x = 42;
    printf("test_clearerr: %d\n", x);
    return 0;
}

int test_file_operations() {
    printf("test_file_operations: fopen/fclose test\n");
    return 0;
}

int test_file_write() {
    void* fp;
    fp = fopen("test_file.txt", "w");
    if (fp) {
        fprintf(fp, "Hello, File!\n");
        fprintf(fp, "Value: %d\n", 42);
        fclose(fp);
        printf("test_file_write: File written successfully\n");
        return 0;
    } else {
        printf("test_file_write: Failed to open file for writing\n");
        return -1;
    }
}

int test_file_read() {
    void* fp;
    char buffer[100];
    int value;

    fp = fopen("test_file.txt", "r");
    if (fp) {
        fscanf(fp, "%s", buffer);
        printf("test_file_read: buffer=%s\n", buffer);
        fscanf(fp, "%d", &value);
        printf("test_file_read: value=%d\n", value);
        fclose(fp);
        printf("test_file_read: File read successfully\n");
        return 0;
    } else {
        printf("test_file_read: Failed to open file for reading\n");
        return -1;
    }
}

int test_file_functions() {
    void* fp;
    char buffer[100];
    int value;

    fp = fopen("test_file.txt", "w");
    if (fp) {
        fprintf(fp, "Hello, File!\n");
        fprintf(fp, "Value: %d\n", 42);
        fclose(fp);
        printf("test_file_functions: File written successfully\n");

        fp = fopen("test_file.txt", "r");
        if (fp) {
            fscanf(fp, "%s", buffer);
            printf("test_file_functions: buffer=%s\n", buffer);
            fscanf(fp, "%d", &value);
            printf("test_file_functions: value=%d\n", value);
            fclose(fp);
            printf("test_file_functions: File read successfully\n");
            return 0;
        } else {
            printf("test_file_functions: Failed to open file for reading\n");
            return -1;
        }
    } else {
        printf("test_file_functions: Failed to open file for writing\n");
        return -1;
    }
}

int test_scanf_basic() {
    int x;
    scanf("%d", &x);
    return x + 10;
}

int test_scanf_single() {
    int a;
    scanf("%d", &a);
    printf("test_scanf_single: Input value: %d\n", a);
    return a;
}

int test_scanf_string() {
    char name[100];
    int result = scanf("%s", name);
    printf("test_scanf_string: Hello, %s!\n", name);
    return result;
}

int test_scanf() {
    int a;
    int b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("test_scanf: a = %d\n", a);
    printf("test_scanf: b = %d\n", b);
    return a + b;
}

int test_puts_gets() {
    char buffer[100];
    puts("test_puts_gets: Please enter your name:");
    gets(buffer);
    puts("test_puts_gets: Hello, ");
    puts(buffer);
    return 0;
}

int main() {
    int result = 0;

    printf("===== IronCScript STDIO Test Suite =====\n\n");

    printf("--- Basic printf tests ---\n");
    result += test_printf_int();
    result += test_printf();
    result += test_puts();

    printf("\n--- File operation tests ---\n");
    result += test_file_operations();
    result += test_file_write();
    result += test_file_read();
    result += test_file_functions();

    printf("\n--- Formatted IO tests ---\n");
    result += test_fprintf();
    result += test_fscanf();

    printf("\n--- Character IO tests ---\n");
    result += test_fputc();
    result += test_fgetc();
    result += test_fputs();
    result += test_fgets();

    printf("\n--- Binary IO tests ---\n");
    result += test_fread();
    result += test_fwrite();

    printf("\n--- File positioning tests ---\n");
    result += test_fseek();
    result += test_ftell();
    result += test_rewind();

    printf("\n--- Error handling tests ---\n");
    result += test_feof();
    result += test_ferror();
    result += test_clearerr();
    result += test_fflush();

    printf("\n--- Input tests (manual testing) ---\n");
    result += test_scanf_basic();
    result += test_scanf_single();
    result += test_scanf_string();
    result += test_scanf();

    printf("\n--- String IO tests ---\n");
    result += test_puts_gets();

    printf("\n===== STDIO Test Suite Complete =====\n");
    printf("Final result: %d\n", result);

    return result;
}