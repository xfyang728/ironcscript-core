extern void analogWrite(int pin, int value);
extern void print(int value);
extern void println(int value);

void main() {
    println(111);
    analogWrite(36, 128);
    println(222);
    analogWrite(37, 64);
    println(333);
}