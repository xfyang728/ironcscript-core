extern void analogWrite(int pin, int value);
extern void printf(...);

void main() {
    printf("%d\n", 111);
    analogWrite(36, 128);
    printf("%d\n", 222);
    analogWrite(37, 64);
    printf("%d\n", 333);
}