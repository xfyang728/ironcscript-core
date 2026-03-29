# STM32 Platform Support

set(STM32_PLATFORM_SOURCES
    STM32Hardware.cpp
    STM32DFUBootloader.cpp
    STM32GPIO.cpp
    STM32Timer.cpp
    STM32UART.cpp
)

add_library(STM32Platform STATIC ${STM32_PLATFORM_SOURCES})

target_include_directories(STM32Platform PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/platform/stm32
)

target_link_libraries(STM32Platform
    BytecodeVM
    BytecodeCompiler
)

if(CSE_STM32_FIRMWARE)
    target_compile_definitions(STM32Platform PRIVATE __STM32__=1)
    target_compile_options(STM32Platform PRIVATE -fno-exceptions -fno-rtti -fno-threadsafe-statics)
endif()