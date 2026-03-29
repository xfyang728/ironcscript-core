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

void main() {
    // GPIO Test
    gpio_set_mode(0, 1);  // OUTPUT = 1
    gpio_write(0, 1);     // HIGH = 1
    delay(500);
    gpio_write(0, 0);      // LOW = 0
    delay(500);

    // Read GPIO input (pin 1)
    gpio_set_mode(1, 0);   // INPUT = 0
    int val = gpio_read(1);
    if (val == 1) {
        printf(72);  // 'H'
        printf(73);  // 'I'
    } else {
        printf(76);  // 'L'
        printf(79);  // 'O'
    }

    // UART Test
    uart_config(1, 115200, 8, 0, 1);
    uart_write(1, 65);  // 'A'

    // Timer Test
    timer_start(0, 1000000, 1);
    delay(2000);
    timer_stop(0);

    printf(79);  // 'O'
    printf(75);  // 'K'
}