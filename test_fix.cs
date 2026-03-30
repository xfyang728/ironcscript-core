extern void println(int);

extern void analogWrite(int, int);

void main() {
    int g = 0;
    analogWrite(37, 255 - g);
    println(255 - g);
}