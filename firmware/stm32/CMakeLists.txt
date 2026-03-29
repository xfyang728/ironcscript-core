cmake_minimum_required(VERSION 3.10)

if(NOT STM32_SDK_ROOT)
    set(STM32_SDK_ROOT "D:/MyCode/IronCScript/ironcscript-core/extern/STM32/STM32F10x_StdPeriph_Lib_V3.5.0")
endif()

if(NOT IronCS_ROOT)
    set(IronCS_ROOT "D:/MyCode/IronCScript/ironcscript-core")
endif()

if(NOT TOOLCHAIN)
    set(TOOLCHAIN "D:/MyCode/IronCScript/ironcscript-core/extern/STM32/gcc-arm-none-eabi-10.3-2021.10/bin")
endif()

set(CMAKE_TOOLCHAIN_PREFIX "arm-none-eabi-")

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "ARM")

set(CMAKE_C_COMPILER "${TOOLCHAIN}/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN}/arm-none-eabi-g++.exe")
set(CMAKE_AR "${TOOLCHAIN}/arm-none-eabi-ar.exe")
set(CMAKE_LINKER "${TOOLCHAIN}/arm-none-eabi-ld.exe")
set(CMAKE_OBJCOPY "${TOOLCHAIN}/arm-none-eabi-objcopy.exe")
set(CMAKE_SIZE "${TOOLCHAIN}/arm-none-eabi-size.exe")
set(CMAKE_OBJDUMP "${TOOLCHAIN}/arm-none-eabi-objdump.exe")
set(CMAKE_RANLIB "${TOOLCHAIN}/arm-none-eabi-ranlib.exe")
set(CMAKE_NM "${TOOLCHAIN}/arm-none-eabi-nm.exe")

set(CMAKE_EXECUTABLE_FORMAT "ELF" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH "${STM32_SDK_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -Wextra -fno-exceptions -DCONFIG_LOG_LEVEL=LOG_INFO -DCONFIG_LOG_ENABLE -DSTM32F1 -DSTM32F103xB -DCSE_STM32" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -DCONFIG_LOG_LEVEL=LOG_INFO -DCONFIG_LOG_ENABLE -DSTM32F1 -DSTM32F103xB -DCSE_STM32" CACHE STRING "")

project(IronCSSTM32VM C CXX ASM)

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

set(STARTUP_FILE "${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s")

set(VM_SOURCES
    ${STARTUP_FILE}
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c
    ${STM32_SDK_ROOT}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
    ${STM32_SDK_ROOT}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
    ${IronCS_ROOT}/src/platform/stm32/STM32Hardware.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32GPIO.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32Timer.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32UART.cpp
    ${IronCS_ROOT}/src/platform/stm32/STM32DFUBootloader.cpp
    ${IronCS_ROOT}/src/bytecode/vm/BytecodeVM.cpp
    ${IronCS_ROOT}/src/bytecode/BytecodeFormat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_vm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c
)

add_executable(IronCS_vm.elf ${VM_SOURCES})

target_link_options(IronCS_vm.elf PRIVATE
    "-Wl,--gc-sections"
    "-Wl,-T" "${CMAKE_CURRENT_SOURCE_DIR}/STM32F103C8T6_FLASH.ld"
)

target_link_libraries(IronCS_vm.elf PUBLIC
    -Wl,--start-group
    gcc
    m
    c
    -Wl,--end-group
)

add_custom_command(OUTPUT IronCS_vm.bin
    COMMAND ${CMAKE_OBJCOPY} --output-format=binary ${CMAKE_BINARY_DIR}/IronCS_vm.elf ${CMAKE_BINARY_DIR}/IronCS_vm.bin
    DEPENDS IronCS_vm.elf
    COMMENT "Generating .bin file"
)

add_custom_target(flash ALL DEPENDS IronCS_vm.bin)