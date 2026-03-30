int main() {
    char c = '5';
    int d = isdigit(c);
    int a = isalpha(c);
    return (d == 1 && a == 0) ? 0 : 1;
}