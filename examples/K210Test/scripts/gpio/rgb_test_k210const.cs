// RGB LED Test Script (K210Constants Style)
// Control RGB LED using platform constants from --platform k210
// Uses K210Constants: GPIO3, GPIO4, GPIO5, FUNC_GPIO3, FUNC_GPIO4, FUNC_GPIO5, OUTPUT, HIGH, etc.

extern void delay(int ms);
extern void print(int value);
extern void println(int value);
extern void pinMode(int pin, int mode);
extern void analogWrite(int pin, int value);
extern void digitalWrite(int pin, int value);
extern void rgb_set(int r, int g, int b);
extern void fpioa_set_func(int pin, int function);

// LED FPIOA Pins (原理图: IO12/IO13/IO14)
const int LED_G_FPIOA_PIN = 13;
const int LED_R_FPIOA_PIN = 14;
const int LED_B_FPIOA_PIN = 12;

void rgbInit() {
    fpioa_set_func(LED_G_FPIOA_PIN, FUNC_GPIO5);
    fpioa_set_func(LED_R_FPIOA_PIN, FUNC_GPIO4);
    fpioa_set_func(LED_B_FPIOA_PIN, FUNC_GPIO3);

    pinMode(GPIO4, OUTPUT);
    pinMode(GPIO5, OUTPUT);
    pinMode(GPIO3, OUTPUT);

    digitalWrite(GPIO4, HIGH);
    digitalWrite(GPIO5, HIGH);
    digitalWrite(GPIO3, HIGH);
}

void rgbWrite(int r, int g, int b) {
    analogWrite(GPIO4, 255 - r);
    analogWrite(GPIO5, 255 - g);
    analogWrite(GPIO3, 255 - b);
}

void main() {
    println(111);
    rgbInit();

    print(888);
    rgbWrite(255, 0, 0);
    delay(2000);

    rgbWrite(0, 255, 0);
    delay(2000);

    rgbWrite(0, 0, 255);
    delay(2000);

    rgbWrite(0, 0, 0);
    println(999);
}