extern void lightSensorInit();
extern void ledInit();
extern int lightSensorGet();
extern void ledOn();
extern void ledOff();
extern void delay(int ms);

void main() {
    lightSensorInit();
    ledInit();

    while (1) {
        if (lightSensorGet() == 1) {
            ledOn();
        } else {
            ledOff();
        }

        delay(100);
    }
}