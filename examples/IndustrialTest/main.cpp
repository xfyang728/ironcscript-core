#include <iostream>
#include <CScriptEngine.h>
#include <backend/FFIRegistry.h>

static int mock_gpio_set_mode(uint32_t pin, uint32_t mode) {
    std::cout << "[MOCK] gpio_set_mode(pin=" << pin << ", mode=" << mode << ")" << std::endl;
    return 0;
}

static int mock_gpio_write(uint32_t pin, uint32_t value) {
    std::cout << "[MOCK] gpio_write(pin=" << pin << ", value=" << value << ")" << std::endl;
    return 0;
}

static uint32_t mock_gpio_read(uint32_t pin) {
    std::cout << "[MOCK] gpio_read(pin=" << pin << ") -> 1" << std::endl;
    return 1;
}

static int mock_timer_start(uint32_t timer_id, uint32_t period_us, uint32_t periodic) {
    std::cout << "[MOCK] timer_start(timer_id=" << timer_id << ", period_us=" << period_us << ", periodic=" << periodic << ")" << std::endl;
    return 0;
}

static int mock_timer_pwm_config(uint32_t timer_id, uint32_t frequency_hz, uint8_t duty_cycle) {
    std::cout << "[MOCK] timer_pwm_config(timer_id=" << timer_id << ", freq=" << frequency_hz << "Hz, duty=" << (int)duty_cycle << "%)" << std::endl;
    return 0;
}

static int mock_uart_config(uint32_t uart_id, uint32_t baudrate, uint8_t data_bits, uint8_t parity, uint8_t stop_bits) {
    std::cout << "[MOCK] uart_config(uart_id=" << uart_id << ", baud=" << baudrate << ", data=" << (int)data_bits << ", parity=" << (int)parity << ", stop=" << (int)stop_bits << ")" << std::endl;
    return 0;
}

static int mock_modbus_set_slave(uint8_t addr) {
    std::cout << "[MOCK] modbus_set_slave(addr=" << (int)addr << ")" << std::endl;
    return 0;
}

static int mock_modbus_read_holding(uint16_t addr) {
    std::cout << "[MOCK] modbus_read_holding(addr=" << addr << ")" << std::endl;
    return 250;
}

static uint64_t mock_get_ticks() {
    return 1000000;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Industrial FFI Test Program (Mock)" << std::endl;
    std::cout << "========================================" << std::endl;

    cse::FFIRegistry& ffi = cse::FFIRegistry::instance();

    ffi.registerNative("gpio_set_mode", reinterpret_cast<void*>(&mock_gpio_set_mode));
    ffi.registerNative("gpio_write", reinterpret_cast<void*>(&mock_gpio_write));
    ffi.registerNative("gpio_read", reinterpret_cast<void*>(&mock_gpio_read));
    ffi.registerNative("timer_start", reinterpret_cast<void*>(&mock_timer_start));
    ffi.registerNative("timer_pwm_config", reinterpret_cast<void*>(&mock_timer_pwm_config));
    ffi.registerNative("uart_config", reinterpret_cast<void*>(&mock_uart_config));
    ffi.registerNative("modbus_set_slave", reinterpret_cast<void*>(&mock_modbus_set_slave));
    ffi.registerNative("modbus_read_holding", reinterpret_cast<void*>(&mock_modbus_read_holding));
    ffi.registerNative("get_ticks", reinterpret_cast<void*>(&mock_get_ticks));

    std::cout << "\n[INFO] Registered " << ffi.functionCount() << " industrial FFI functions" << std::endl;

    const char* testScript = R"(
        extern int gpio_set_mode(int pin, int mode);
        extern int gpio_write(int pin, int value);
        extern int gpio_read(int pin);
        extern int timer_start(int timer_id, int period_us, int periodic);
        extern int timer_pwm_config(int timer_id, int frequency_hz, int duty_cycle);
        extern int uart_config(int uart_id, int baudrate, int data_bits, int parity, int stop_bits);
        extern int modbus_set_slave(int addr);
        extern int modbus_read_holding(int addr);
        extern int get_ticks();

        int main() {
            gpio_set_mode(0, 3);
            gpio_write(0, 1);
            int val = gpio_read(1);

            timer_start(0, 1000000, 1);
            timer_pwm_config(0, 50, 75);

            uart_config(0, 115200, 8, 0, 1);

            modbus_set_slave(1);
            int temp = modbus_read_holding(0);

            int ticks = get_ticks();

            return 0;
        }
    )";

    std::cout << "\nExecuting Industrial FFI test script..." << std::endl;

    cse::CScriptEngine engine;
    if (engine.execute(testScript)) {
        std::cout << "\n[PASS] Script executed successfully" << std::endl;
    } else {
        std::cout << "\n[FAIL] Script execution failed: " << engine.getLastError() << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  Industrial FFI Test Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
