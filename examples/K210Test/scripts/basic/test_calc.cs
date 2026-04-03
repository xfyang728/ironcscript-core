extern void printf(...);

int testCalc() {
    int g = 0;
    int result = 255 - g;
    return result;
}

void main() {
    printf("testCalc() = %d\n", testCalc());
}