// Blue LED Test Script
// Test blue LED separately to debug

extern void led_init();
extern void rgb_set(int r, int g, int b);
extern void delay(int ms);
extern void printf(...);

void main() {
    printf("%d\n", 1);
    led_init();
    
    printf("%d\n", 2);
    
    rgb_set(255, 0, 0);
    delay(2000);

    rgb_set(0, 255, 0);
    delay(2000);

    rgb_set(0, 0, 255);
    delay(2000);
    
    printf("%d\n", 5);
    rgb_set(0, 0, 0);
}
