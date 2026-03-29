int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int sum = 0;
    int i = 0;
    for (i = 0; i < 5; i++) {
        sum += arr[i];
    }
    return sum; // Should return 15
}
