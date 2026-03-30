int sub(int a, int b, int c) {
    return a - b + c;
}

int main() {
    int a = 10;
    int b = 7;
    int result = sub(4, a - b, a + b);
    return result;
}