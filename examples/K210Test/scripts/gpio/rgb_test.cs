// RGB LED Test Script
// Control RGB LED on K210 pins: G=13, R=14, B=15

extern void rgb_set(int r, int g, int b);
extern void delay(int ms);

void main() {
    // Red
    rgb_set(255, 0, 0);
    delay(2000);

    // Green
    rgb_set(0, 255, 0);
    delay(2000);

    // Blue
    rgb_set(0, 0, 255);
    delay(2000);

    // Yellow
    // rgb_set(255, 255, 0);
    // delay(2000);

    // // Purple
    // rgb_set(255, 0, 255);
    // delay(2000);

    // // Cyan
    // rgb_set(0, 255, 255);
    // delay(2000);

    // // White
    // rgb_set(255, 255, 255);
    // delay(2000);

    // Off
    rgb_set(0, 0, 0);
}
