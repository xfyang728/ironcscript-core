// Industrial FFI Test Script
// This script demonstrates how to use the Industrial FFI bindings from CScript

extern int gpio_set_mode(int pin, int mode);
extern int gpio_write(int pin, int value);
extern int gpio_read(int pin);
extern int timer_start(int timer_id, int period_us, int periodic);
extern int timer_pwm_config(int timer_id, int frequency_hz, int duty_cycle);
extern int uart_config(int uart_id, int baudrate, int data_bits, int parity, int stop_bits);
extern int modbus_set_slave(int addr);
extern int modbus_read_holding(int addr, int count, int* output);
extern int modbus_write_single(int addr, int value);
extern int get_ticks();

// GPIO mode constants
int GPIO_INPUT = 0;
int GPIO_OUTPUT = 3;

int main() {
    // Test 1: GPIO Output (LED blink simulation)
    print("=== Test 1: GPIO Output ===");
    gpio_set_mode(0, GPIO_OUTPUT);
    gpio_write(0, 1);
    print("GPIO pin 0 set to HIGH");
    gpio_write(0, 0);
    print("GPIO pin 0 set to LOW");

    // Test 2: GPIO Input
    print("\n=== Test 2: GPIO Input ===");
    gpio_set_mode(1, GPIO_INPUT);
    int value = gpio_read(1);
    print("GPIO pin 1 read value: ");
    print_int(value);

    // Test 3: Timer PWM (50Hz servo signal)
    print("\n=== Test 3: Timer PWM ===");
    timer_pwm_config(0, 50, 75);  // 50Hz, 75% duty cycle
    print("Timer 0 configured for PWM at 50Hz");

    // Test 4: UART Configuration
    print("\n=== Test 4: UART Configuration ===");
    int result = uart_config(0, 115200, 8, 0, 1);  // 115200 baud, 8N1
    print("UART0 configured: 115200 8N1");
    print_int(result);

    // Test 5: Modbus RTU (read temperature sensor)
    print("\n=== Test 5: Modbus RTU ===");
    modbus_set_slave(1);

    int registers[2];
    int success = modbus_read_holding(0, 1, registers);

    if (success == 0) {
        print("Modbus read successful");
        print_int(registers[0]);
    } else {
        print("Modbus read failed");
    }

    // Test 6: Modbus Write
    print("\n=== Test 6: Modbus Write ===");
    success = modbus_write_single(100, 500);
    if (success == 0) {
        print("Modbus write successful");
    } else {
        print("Modbus write failed");
    }

    // Test 7: System Ticks
    print("\n=== Test 7: System Ticks ===");
    int start_ticks = get_ticks();
    int end_ticks = get_ticks();
    print("Ticks delta: ");
    print_int(end_ticks - start_ticks);

    print("\n=== All Tests Complete ===");
    return 0;
}

void print(string msg) {
    // Implementation would call native print function
}

void print_int(int value) {
    // Implementation would convert int to string and print
}
