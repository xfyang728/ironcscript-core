// RGB LED Test Script (Arduino Style)
// Control RGB LED using analogWrite (PWM)
// K210 pins: G=IO13, R=IO14, B=IO12

extern void rgb_set(int r, int g, int b);
extern void pinMode(int pin, int mode);
extern void analogWrite(int pin, int value);
extern void delay(int ms);
extern void printf(...);

// 常量定义
const int OUTPUT = 1;
const int LED_R = 14;
const int LED_G = 13;
const int LED_B = 12;

const int LED_G_PIN = 37;
const int LED_R_PIN = 36;
const int LED_B_PIN = 35;

void rgbWrite(int r, int g, int b) {
    analogWrite(LED_R_PIN, r == 0);
    analogWrite(LED_G_PIN, g == 0);
    analogWrite(LED_B_PIN, b == 0);
}

void main() {
    rgb_set(255, 0, 0);
    delay(2000);

    rgbWrite(0, 255, 0);
    delay(2000);
    
    rgbWrite(0, 0, 0);
}
