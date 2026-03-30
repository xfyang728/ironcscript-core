int main() {
    void* ptr1;
    ptr1 = malloc(20);
    printf("malloc done\n");
    free(ptr1);
    return 0;
}