extern void delay(int ms);
extern void printf(...);
extern void analogWrite(int pin, int value);

void main() {
    int g = 0;
    int result = 255 - g;
    printf("%d\n", result);
    analogWrite(37, result);
    delay(1000);
    analogWrite(37, 255);
}