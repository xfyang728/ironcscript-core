// CScript Hardware Test Script
// This script demonstrates hardware control via CScript

// Hardware function declarations
extern void gpio_set_mode(int pin, int mode);
extern void gpio_write(int pin, int value);
extern int gpio_read(int pin);
extern void uart_config(int id, int baud, int bits, int parity, int stop);
extern void uart_write(int id, int value);
extern void timer_start(int id, int period_us, int periodic);
extern void timer_stop(int id);
extern void delay(int ms);
extern void printf(...);

void main() {
    gpio_set_mode(0, 1);
    gpio_write(0, 1);
    delay(500);
    gpio_write(0, 0);
    delay(500);

    gpio_set_mode(1, 0);
    int val = gpio_read(1);
    if (val == 1) {
        printf("%c", 72);
        printf("%c", 73);
    } else {
        printf("%c", 76);
        printf("%c", 79);
    }

    uart_config(1, 115200, 8, 0, 1);
    uart_write(1, 65);

    timer_start(0, 1000000, 1);
    delay(2000);
    timer_stop(0);

    printf("%c", 79);
    printf("%c", 75);
    printf("%c", 10);
}