extern void ledInit();
extern void ledOn();
extern void ledOff();
extern void delay(int ms);

int main() {
    ledInit();
    while (1) {
        ledOn();
        delay(500);
        ledOff();
        delay(500);
    }
    return 0;
}