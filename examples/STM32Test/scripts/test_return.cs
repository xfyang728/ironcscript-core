extern int lightSensorGet();
extern void ledOn();
extern void ledOff();
extern void delay(int ms);

void main() {
    int val = lightSensorGet();
    if (val == 1) {
        ledOn();
    } else {
        ledOff();
    }
    delay(500);
}