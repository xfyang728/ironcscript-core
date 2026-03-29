// Blue LED Test Script
// Test blue LED separately to debug

extern void led_init();
extern void rgb_set(int r, int g, int b);
extern void delay(int ms);
extern void print(int val);

void main() {
    // Method 1: Use default led_init
    print(1);
    led_init();
    
    // Test blue only
    print(2);
    
    // Red
    rgb_set(255, 0, 0);
    delay(2000);

    // Green
    rgb_set(0, 255, 0);
    delay(2000);

    // Blue
    rgb_set(0, 0, 255);
    delay(2000);
    
    // Off
    print(5);
    rgb_set(0, 0, 0);
}
