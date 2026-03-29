int main() {
    int sum = 0;
    int i = 0;
    for (; i < 10; i = i + 1) {
        if (i == 5) {
            break;
        }
        sum = sum + i;
    }
    return sum;
}
