extern void ledInit();
extern void ledOn();
extern void ledOff();

void main() {
    ledInit();
    ledOff();

    if (1 == 1) {
        ledOn();
    }
}