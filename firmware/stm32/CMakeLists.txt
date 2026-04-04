cmake_minimum_required(VERSION 3.10)

set(STM32_SDK_ROOT "D:/MyCode/IronCScript/ironcscript-core/extern/STM32/STM32F10x_StdPeriph_Lib_V3.5.0")
set(IronCS_ROOT "D:/MyCode/IronCScript/ironcscript-core")
set(TOOLCHAIN "D:/MyCode/IronCScript/ironcscript-core/extern/STM32/gcc-arm-none-eabi-10.3-2021.10/bin")

include(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER("${TOOLCHAIN}/arm-none-eabi-gcc.exe" GNU)
CMAKE_FORCE_CXX_COMPILER("${TOOLCHAIN}/arm-none-eabi-g++.exe" GNU)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_EXECUTABLE_FORMAT ELF)

set(CMAKE_FIND_ROOT_PATH "${STM32_SDK_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS_INIT "-Os -fno-exceptions -ffunction-sections -fdata-sections -mcpu=cortex-m3 -DEMBEDDED_BUILD")
set(CMAKE_CXX_FLAGS_INIT "-Os -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffunction-sections -fdata-sections -mcpu=cortex-m3 -DEMBEDDED_BUILD")

project(IronCS_STM32 C CXX ASM)

enable_language(ASM)

add_definitions(-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER)

include_directories(
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/CoreSupport
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/inc
    ${IronCS_ROOT}/src
    ${IronCS_ROOT}/src/bytecode
    ${IronCS_ROOT}/src/hal
    ${IronCS_ROOT}/src/industrial
    ${IronCS_ROOT}/src/platform/stm32
)

set(STARTUP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/startup_minimal.s")

set(COMMON_SOURCES
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
)

set(VM_SOURCES
    ${IronCS_ROOT}/src/platform/stm32/STM32Hardware.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32GPIO.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32Timer.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32UART.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32DFUBootloader.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32CSBLoader.cpp
    ${IronCS_ROOT}/src/bytecode/vm/BytecodeVM.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_vm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/hardware/OLED.c
)

add_library(common STATIC ${COMMON_SOURCES})

add_executable(IronCS_flash.elf
    ${STARTUP_FILE}
    ${VM_SOURCES}
)

add_dependencies(IronCS_flash.elf common)

target_link_options(IronCS_flash.elf PRIVATE
    "-Wl,--gc-sections"
    "-Wl,--whole-archive"
    "-Wl,-T" "${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8T6_FLASH.ld"
    "-specs=nano.specs"
    "-nostartfiles"
    "-mcpu=cortex-m3"
    "-Wl,--no-whole-archive"
)

target_link_libraries(IronCS_flash.elf PUBLIC
    common
    -lc
    -lm
    -lgcc
)

add_custom_command(OUTPUT IronCS_flash.bin
    COMMAND ${CMAKE_OBJCOPY} --output-format=binary ${CMAKE_BINARY_DIR}/IronCS_flash.elf ${CMAKE_BINARY_DIR}/IronCS_flash.bin
    DEPENDS IronCS_flash.elf
    COMMENT "Generating internal Flash firmware .bin file"
)

add_custom_target(flash_run DEPENDS IronCS_flash.bin)

enable_language(C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)