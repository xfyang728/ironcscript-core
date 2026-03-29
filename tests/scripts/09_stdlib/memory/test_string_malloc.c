int main() {
    // 测试malloc和free
    char* s1 = malloc(10);
    strcpy(s1, "Hello");
    printf("String: %s\n", s1);
    free(s1);
    
    return 0;
}
