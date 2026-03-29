int main() {
    int a = 10;
    int *p = &a;
    *p = 20;
    int b = *p;
    return b; // Should return 20
}
