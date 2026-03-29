int main() {
    void* ptr1;
    char buffer[20];
    
    ptr1 = malloc(20);
    printf("malloc done\n");
    
    strcpy((char*)ptr1, "Hello");
    printf("strcpy done\n");
    
    printf("Content: %s\n", (char*)ptr1);
    
    free(ptr1);
    return 0;
}
