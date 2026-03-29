#ifndef CSE_K210_HARDWARE_TEST_H
#define CSE_K210_HARDWARE_TEST_H

#include <cstdint>

namespace cse {

class K210HardwareTest {
public:
    static bool runAllTests();

    static bool testGPIO();
    static bool testUART();
    static bool testTimer();

    static void printResult(const char* testName, bool success);
};

}

#endif