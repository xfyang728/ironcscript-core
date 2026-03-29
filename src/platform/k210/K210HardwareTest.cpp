#include "K210HardwareTest.h"
#include "K210HAL.h"
#include "hal/IStandardGPIO.h"
#include "hal/IStandardUART.h"
#include "hal/IStandardTimer.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include "fpioa.h"
#include "gpio.h"
#include "sysctl.h"
}

#if defined(__K210__) || defined(CSE_K210)
#include "platform/k210/K210GPIO.h"
#include "platform/k210/K210Timer.h"
#include "platform/k210/K210UART.h"
#endif

namespace cse {

void K210HardwareTest::printResult(const char* testName, bool success) {
    printf("[%s] %s: %s\r\n",
           success ? "PASS" : "FAIL",
           testName,
           success ? "OK" : "FAILED");
}

bool K210HardwareTest::testGPIO() {
    printf("[TEST] GPIO Test Starting...\r\n");

#if defined(__K210__) || defined(CSE_K210)
    static K210GPIO gpio;

    printf("[TEST] Platform: %s\r\n", gpio.getPlatformName());

    const uint32_t TEST_PIN = 13;

    fpioa_set_function(TEST_PIN, FUNC_GPIO3);
    gpio.setMode(TEST_PIN, GPIOMode::OUTPUT);
    printf("[TEST] Pin %u set to OUTPUT mode\r\n", TEST_PIN);

    for (int i = 0; i < 3; i++) {
        gpio.write(TEST_PIN, true);
        printf("[TEST] Pin %u HIGH\r\n", TEST_PIN);
        k210_delay_ms(500);

        gpio.write(TEST_PIN, false);
        printf("[TEST] Pin %u LOW\r\n", TEST_PIN);
        k210_delay_ms(500);
    }

    gpio.setMode(TEST_PIN, GPIOMode::INPUT);
    printf("[TEST] Pin %u set to INPUT mode\r\n", TEST_PIN);

    printf("[TEST] GPIO Test Complete\r\n");
    return true;
#else
    printf("[TEST] GPIO Test - Not on K210 platform\r\n");
    return false;
#endif
}

bool K210HardwareTest::testUART() {
    printf("[TEST] UART Test Starting...\r\n");

#if defined(__K210__) || defined(CSE_K210)
    static K210GPIO gpio;
    static K210UART uart(0);
    uart.setGPIO(&gpio);

    printf("[TEST] Platform: %s\r\n", uart.getPlatformName());

    UARTConfig config;
    config.baudrate = 115200;
    config.data_bits = 8;
    config.parity = UARTParity::NONE;
    config.stop_bits = UARTStopBits::ONE;

    if (!uart.configure(config)) {
        printf("[ERROR] Failed to configure UART\r\n");
        return false;
    }
    printf("[TEST] UART configured at 115200 8N1\r\n");

    const char* testData = "Hello from K210 UART!\r\n";
    int written = uart.write(reinterpret_cast<const uint8_t*>(testData), strlen(testData));
    printf("[TEST] Wrote %d bytes\r\n", written);

    uint8_t buffer[64];
    int received = uart.read(buffer, sizeof(buffer) - 1, 2000);
    if (received > 0) {
        buffer[received] = '\0';
        printf("[TEST] Received: %s\r\n", buffer);
    } else {
        printf("[TEST] No data received (timeout)\r\n");
    }

    printf("[TEST] UART Test Complete\r\n");
    return true;
#else
    printf("[TEST] UART Test - Not on K210 platform\r\n");
    return false;
#endif
}

bool K210HardwareTest::testTimer() {
    printf("[TEST] Timer Test Starting...\r\n");

#if defined(__K210__) || defined(CSE_K210)
    static K210Timer timer(0);

    printf("[TEST] Platform: %s\r\n", timer.getPlatformName());

    uint64_t startTicks = timer.getTicks();
    printf("[TEST] Start ticks: %llu\r\n", (unsigned long long)startTicks);

    if (!timer.start(1000000, true)) {
        printf("[ERROR] Failed to start timer\r\n");
        return false;
    }
    printf("[TEST] Timer started (1 second period)\r\n");

    k210_delay_ms(2500);

    uint64_t endTicks = timer.getTicks();
    printf("[TEST] End ticks: %llu\r\n", (unsigned long long)endTicks);

    timer.stop();
    printf("[TEST] Timer stopped\r\n");

    uint64_t elapsed = endTicks - startTicks;
    printf("[TEST] Elapsed: %llu ticks\r\n", (unsigned long long)elapsed);

    bool success = (elapsed > 0);
    printf("[TEST] Timer Test Complete\r\n");
    return success;
#else
    printf("[TEST] Timer Test - Not on K210 platform\r\n");
    return false;
#endif
}

bool K210HardwareTest::runAllTests() {
    printf("\r\n");
    printf("========================================\r\n");
    printf("IronCS K210 Hardware Test Suite\r\n");
    printf("========================================\r\n");
    printf("\r\n");

    bool gpioResult = testGPIO();
    printResult("GPIO Test", gpioResult);
    printf("\r\n");

    bool uartResult = testUART();
    printResult("UART Test", uartResult);
    printf("\r\n");

    bool timerResult = testTimer();
    printResult("Timer Test", timerResult);
    printf("\r\n");

    printf("========================================\r\n");
    printf("Test Results:\r\n");
    printf("  GPIO:  %s\r\n", gpioResult ? "PASS" : "FAIL");
    printf("  UART:  %s\r\n", uartResult ? "PASS" : "FAIL");
    printf("  Timer: %s\r\n", timerResult ? "PASS" : "FAIL");
    printf("========================================\r\n");
    printf("\r\n");

    return gpioResult && uartResult && timerResult;
}

}