D:\MyCode\IronCScript\ironcscript-core\tests\scripts\01_basic\test_float.c
  4,5:     printf("%f\n", x);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\01_basic\test_simple.c
  4,5:     printf("%f\n", x);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\06_pointers\test_cast_simple.c
  4,5:     printf("malloc done\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\06_pointers\test_cast.c
  6,5:     printf("malloc done\n");
  9,5:     printf("strcpy done\n");
  11,5:     printf("Content: %s\n", (char*)ptr1);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\math\test_abs_only.c
  4,5:     printf("abs(%d) = %d\n", int_value, abs_result);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\math\test_math_extra_functions.c
  10,5:     printf("Testing math functions...\n");
  14,5:     printf("asin(%.2f) = %.4f\n", x, asin_result);
  18,5:     printf("acos(%.2f) = %.4f\n", x, acos_result);
  22,5:     printf("atan(%.2f) = %.4f\n", x, atan_result);
  26,5:     printf("atan2(%.2f, %.2f) = %.4f\n", y, x, atan2_result);
  31,5:     printf("sinh(%.2f) = %.4f\n", x, sinh_result);
  35,5:     printf("cosh(%.2f) = %.4f\n", x, cosh_result);
  39,5:     printf("tanh(%.2f) = %.4f\n", x, tanh_result);
  44,5:     printf("exp(%.2f) = %.4f\n", x, exp_result);
  48,5:     printf("log(%.4f) = %.4f\n", value, log_result);
  52,5:     printf("log10(100.0) = %.4f\n", log10_result);
  56,5:     printf("log2(8.0) = %.4f\n", log2_result);
  61,5:     printf("floor(%.2f) = %.2f\n", positive_value, floor_result);
  65,5:     printf("ceil(%.2f) = %.2f\n", negative_value, ceil_result);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\math\test_math_functions.c
  8,5:     printf("sqrt(%.1f) = %.1f\n", x, sqrt_result);
  12,5:     printf("pow(%.1f, %.1f) = %.1f\n", x, y, pow_result);
  16,5:     printf("sin(%.1f) = %.1f\n", angle, sin_result);
  20,5:     printf("cos(%.1f) = %.1f\n", angle, cos_result);
  24,5:     printf("tan(%.1f) = %.1f\n", angle, tan_result);
  29,5:     printf("abs(%d) = %d\n", int_value, abs_result);
  34,5:     printf("fabs(%.2f) = %.2f\n", double_value, fabs_result);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\math\test_pow_debug.c
  6,5:     printf("x = %f, y = %f, pow_result = %f\n", x, y, pow_result);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\math\test_sqrt_only.c
  4,5:     printf("sqrt(%.1f) = %.1f\n", x, sqrt_result);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\memory\test_memory_alloc_functions.c
  8,5:     printf("Testing memory allocation functions...\n");
  12,9:         printf("calloc(5, sizeof(int)) = %p\n", int_array);
  16,13:             printf("int_array[%d] = %d\n", i, int_array[i]);
  22,13:             printf("realloc(ptr1, 10 * sizeof(int)) = %p\n", ptr1);
  32,17:                 printf("int_array[%d] = %d\n", i, int_array[i]);
  38,17:                 printf("realloc(ptr2, 3 * sizeof(int)) = %p\n", ptr2);
  43,21:                     printf("int_array[%d] = %d\n", i, int_array[i]);
  47,17:                 printf("free(int_array) done\n");
  49,17:                 printf("realloc to smaller size failed\n");
  53,13:             printf("realloc failed\n");
  57,9:         printf("calloc failed\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\memory\test_memory_functions.c
  9,9:         printf("malloc(100) = %p\n", ptr1);
  13,9:         printf("memset(ptr1, 0, 100) done\n");
  18,9:         printf("memcpy(ptr1, buffer, %d) done\n", strlen(buffer) + 1);
  19,9:         printf("Content: %s\n", (char*)ptr1);
  24,13:             printf("realloc(ptr1, 200) = %p\n", ptr2);
  26,13:             printf("Content after realloc: %s\n", (char*)ptr2);
  30,13:             printf("free(ptr2) done\n");
  32,13:             printf("realloc failed\n");
  36,9:         printf("malloc failed\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\memory\test_string_malloc.c
  5,5:     printf("String: %s\n", s1);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\other\test_other_functions.c
  13,5:     printf("随机数测试：\n");
  16,9:         printf("随机数 %d: %d\n", i+1, random);
  22,5:     printf("\n排序前数组：");
  24,9:         printf("%d ", arr[i]);
  26,5:     printf("\n");
  30,5:     printf("排序后数组：");
  32,9:         printf("%d ", arr[i]);
  34,5:     printf("\n");
  40,9:         printf("找到元素 %d\n", *result);
  42,9:         printf("未找到元素 %d\n", key);
  46,5:     printf("\n其他函数测试完成\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_file_functions.c
  8,10:         fprintf(fp, "Hello, File!\n");
  9,10:         fprintf(fp, "Value: %d\n", 42);
  11,9:         printf("File written successfully\n");
  16,13:             printf("buffer=%s\n", buffer);
  18,13:             printf("value=%d\n", value);
  20,13:             printf("File read successfully\n");
  22,13:             printf("Failed to open file for reading\n");
  25,9:         printf("Failed to open file for writing\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_file_operations.c
  10,9:         printf("无法打开文件\n");
  13,5:     printf("文件打开成功\n");
  18,5:     printf("写入了 %zu 个字符\n", written);
  23,5:     printf("文件指针位置：%ld\n", position);
  28,5:     printf("读取的内容：%s\n", buffer);
  33,5:     printf("rewind 后文件指针位置：%ld\n", position);
  37,5:     printf("第一个字符：%c\n", ch);
  43,5:     printf("fgets 读取的内容：%s", buffer);
  47,5:     printf("文件已刷新\n");
  51,9:         printf("文件结束\n");
  54,9:         printf("文件错误\n");
  56,9:         printf("错误已清除\n");
  61,5:     printf("文件已关闭\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_file_read_simple.c
  9,9:         printf("buffer=%s\n", buffer);
  11,9:         printf("value=%d\n", value);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_file_read.c
  9,9:         printf("buffer=%s\n", buffer);
  11,9:         printf("value=%d\n", value);
  13,9:         printf("File read successfully\n");
  16,9:         printf("Failed to open file for reading\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_file_write.c
  5,10:         fprintf(fp, "Hello, File!\n");
  6,10:         fprintf(fp, "Value: %d\n", 42);
  8,9:         printf("File written successfully\n");
  11,9:         printf("Failed to open file for writing\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_fprintf.c
  1,11: int test_fprintf() {
  3,23:     fp = fopen("test_fprintf.txt", "w");
  5,10:         fprintf(fp, "Test %d %s\n", 123, "hello");
  13,18:     return test_fprintf();

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_fscanf.c
  6,23:     fp = fopen("test_fprintf.txt", "r");
  9,9:         printf("buffer=%s, value=%d\n", buffer, value);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_io_functions.c
  8,13:     // Test printf (already tested in other files, but included for completeness)
  9,5:     printf("Testing input/output functions...\n");
  11,14:     // Test sprintf
  12,6:     sprintf(buffer, "String: %s, Number: %d, Float: %.2f", "test", 123, 45.67);
  13,5:     printf("sprintf result: %s\n", buffer);
  13,14:     printf("sprintf result: %s\n", buffer);
  27,5:     printf("Enter a string: ");
  29,5:     printf("gets result: %s\n", str);
  32,5:     printf("Enter another string: ");
  34,5:     printf("fgets result: %s\n", str);
  36,14:     // Test fprintf and fputs with a file
  39,10:         fprintf(file, "This is a test: %d\n", 42);
  42,9:         printf("File written successfully\n");
  48,13:             printf("fscanf result: %d\n", num);
  56,5:     printf("sscanf result: num=%d, fnum=%.2f\n", num, fnum);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_printf_int.c
  3,5:     printf("x = %d\n", x);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_printf.c
  2,5:     printf("Hello, World!\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_scanf_single.c
  5,5:     printf("Input value: %d\n", a);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_scanf_string.c
  5,5:     printf("Hello, %s!\n", name);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\stdio\test_scanf.c
  7,5:     printf("a = %d\n", a);
  8,5:     printf("b = %d\n", b);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\string\test_case_conversion.c
  7,5:     printf("%c", upper); // Fixed: Use format specifier "%c" for a single character
  9,5:     printf("%c", lower2); // Fixed: Use format specifier "%c" for a single character

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\string\test_strcpy_simple.c
  4,5:     printf("buffer = %s\n", buffer);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\string\test_string_extra_functions.c
  16,5:     printf("strncpy(str3, str1, 3) = %s\n", str3);
  21,5:     printf("strncat result: %s\n", str3);
  25,5:     printf("strncmp(str1, \"Hell\", 4) = %d\n", ncmp);
  30,9:         printf("strchr(str4, 'W') = %s\n", result);
  32,9:         printf("strchr(str4, 'W') = not found\n");
  38,9:         printf("strrchr(str4, 'o') = %s\n", result);
  40,9:         printf("strrchr(str4, 'o') = not found\n");
  46,9:         printf("strdup(str1) = %s\n", result);
  53,9:         printf("strndup(str2, 3) = %s\n", result);
  61,9:         printf("strtok result: %s\n", result);
  67,5:     printf("atoi(\"123\") = %d\n", num);
  71,5:     printf("atol(\"123456\") = %ld\n", lnum);
  75,5:     printf("atof(\"123.45\") = %f\n", dnum);
  79,5:     printf("atoll(\"1234567890123\") = %lld\n", ll_num);
  85,5:     printf("strtol(\"12345abc\") = %ld, remaining: %s\n", lnum, endptr);
  90,5:     printf("strtod(\"123.45abc\") = %f, remaining: %s\n", dnum, endptr);
  95,5:     printf("strtof(\"123.45abc\") = %f, remaining: %s\n", fnum, endptr);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\string\test_string_functions.c
  10,5:     printf("strlen(str1) = %d\n", len1);
  11,5:     printf("strlen(str2) = %d\n", len2);
  15,5:     printf("strcpy(str3, str1) = %s\n", str3);
  20,5:     printf("strcat(str3, str2) = %s\n", str3);
  24,5:     printf("strcmp(str1, str2) = %d\n", cmp);
  29,9:         printf("strstr(str3, \"World\") = %s\n", result);
  31,9:         printf("strstr(str3, \"World\") = not found\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\system\test_system_functions.c
  7,5:     printf("信号 %d 被捕获\n", signum);
  12,5:     printf("程序即将退出\n");
  19,9:         printf("PATH 环境变量存在\n");
  21,9:         printf("PATH 环境变量不存在\n");
  26,5:     printf("已注册退出处理函数\n");
  30,5:     printf("已注册 SIGINT 信号处理函数\n");
  36,5:     printf("系统接口函数测试完成\n");

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib\time\test_time_functions.c
  12,5:     printf("Testing time functions...\n");
  15,5:     printf("Current time (seconds since epoch): %lld\n", (long long)current_time);
  20,9:         printf("GMT time: %04d-%02d-%02d %02d:%02d:%02d\n", 
  28,9:         printf("Formatted time: %s\n", time_string);
  41,5:     printf("Elapsed time: %.3f seconds\n", diff_time);
  54,5:     printf("Difference between times: %.3f seconds\n", diff);
  67,5:     printf("mktime result: %lld\n", (long long)converted_time);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\11_edge_cases\test_error_handling.c
  7,5:     printf("Sum: %d\n", sum);
  8,5:     printf("Product: %d\n", product);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\11_edge_cases\test_semantic.c
  5,5:     printf("The sum is: %d\n", c);

D:\MyCode\IronCScript\ironcscript-core\tests\scripts\11_edge_cases\test_syntax_error.c
  6,5:     printf("Sum: %d\n", sum);
