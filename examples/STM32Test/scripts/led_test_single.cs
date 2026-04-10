extern void ledInit();
extern void ledOn();
extern void ledOff();
extern void delay(int ms);

int main() {
    ledInit();
    ledOn();
    delay(1000);
    ledOff();
    return 0;
}