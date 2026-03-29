cmake_minimum_required(VERSION 3.10)

if(NOT SDK_ROOT)
    set(SDK_ROOT "D:/MyCode/IronCScript/ironcscript-core/extern/kendryte_camera-screen-standalone")
endif()

if(NOT IronCS_ROOT)
    set(IronCS_ROOT "D:/MyCode/IronCScript/ironcscript-core")
endif()

if(NOT TOOLCHAIN)
    set(TOOLCHAIN "D:/MyCode/IronCScript/ironcscript-core/extern/kendryte-toolchain/bin")
endif()

set(CMAKE_TOOLCHAIN_PREFIX "${TOOLCHAIN}/riscv64-unknown-elf-")

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "riscv64")
set(CMAKE_C_COMPILER "${CMAKE_TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${CMAKE_TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_AR "${CMAKE_TOOLCHAIN_PREFIX}ar.exe")
set(CMAKE_LINKER "${CMAKE_TOOLCHAIN_PREFIX}ld.exe")
set(CMAKE_OBJCOPY "${CMAKE_TOOLCHAIN_PREFIX}objcopy.exe")
set(CMAKE_SIZE "${CMAKE_TOOLCHAIN_PREFIX}size.exe")
set(CMAKE_OBJDUMP "${CMAKE_TOOLCHAIN_PREFIX}objdump.exe")
set(CMAKE_RANLIB "${CMAKE_TOOLCHAIN_PREFIX}ranlib.exe")
set(CMAKE_NM "${CMAKE_TOOLCHAIN_PREFIX}nm.exe")
set(CMAKE_EXECUTABLE_FORMAT "ELF" CACHE INTERNAL "")

set(CRTI_OBJ "${TOOLCHAIN}/../lib/gcc/riscv64-unknown-elf/8.2.0/crti.o")
set(CRTBEGIN_OBJ "${TOOLCHAIN}/../lib/gcc/riscv64-unknown-elf/8.2.0/crtbegin.o")
set(CRTEND_OBJ "${TOOLCHAIN}/../lib/gcc/riscv64-unknown-elf/8.2.0/crtend.o")
set(CRTN_OBJ "${TOOLCHAIN}/../lib/gcc/riscv64-unknown-elf/8.2.0/crtn.o")

set(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_C_COMPILER> -o <TARGET> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> \"${CRTI_OBJ}\" \"${CRTBEGIN_OBJ}\" <OBJECTS> \"${CRTEND_OBJ}\" \"${CRTN_OBJ}\" -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_CXX_LINK_EXECUTABLE
    "<CMAKE_CXX_COMPILER> -o <TARGET> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> \"${CRTI_OBJ}\" \"${CRTBEGIN_OBJ}\" <OBJECTS> \"${CRTEND_OBJ}\" \"${CRTN_OBJ}\" -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_FIND_ROOT_PATH "${SDK_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

link_directories("${SDK_ROOT}/build")

set(CMAKE_C_FLAGS "-mcmodel=medany -march=rv64gc -mabi=lp64f -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -DCONFIG_LOG_LEVEL=LOG_INFO -DCONFIG_LOG_ENABLE -D__riscv64 -D__K210__ -DCSE_K210" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-mcmodel=medany -march=rv64gc -mabi=lp64f -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -DCONFIG_LOG_LEVEL=LOG_INFO -DCONFIG_LOG_ENABLE -D__riscv64 -D__K210__ -DCSE_K210" CACHE STRING "")

project(IronCSK210VM C CXX ASM)

include_directories(
    ${SDK_ROOT}/src
    ${SDK_ROOT}/config
    ${SDK_ROOT}/kendryte_libraries/kendryte_standalone-sdk/lib/bsp/include
    ${SDK_ROOT}/kendryte_libraries/kendryte_standalone-sdk/lib/drivers/include
    ${SDK_ROOT}/kendryte_libraries/kendryte_standalone-sdk/lib/utils/include
    ${IronCS_ROOT}/src
    ${IronCS_ROOT}/src/vm/k210
    ${IronCS_ROOT}/src/platform/k210
    ${IronCS_ROOT}/src/bytecode
    ${IronCS_ROOT}/src/hal
    ${IronCS_ROOT}/src/industrial
    ${IronCS_ROOT}/firmware
)

set(VM_SOURCES
    ${IronCS_ROOT}/src/platform/k210/K210Bootloader.cpp
    ${IronCS_ROOT}/src/platform/k210/K210Flash.cpp
    ${IronCS_ROOT}/src/platform/k210/K210Hardware.cpp
    ${IronCS_ROOT}/src/platform/k210/K210GPIO.cpp
    ${IronCS_ROOT}/src/platform/k210/K210Timer.cpp
    ${IronCS_ROOT}/src/platform/k210/K210UART.cpp
    ${IronCS_ROOT}/src/platform/k210/CSBLoader.cpp
    ${IronCS_ROOT}/src/bytecode/vm/BytecodeVM.cpp
    ${IronCS_ROOT}/src/bytecode/BytecodeFormat.cpp
    ${IronCS_ROOT}/src/hal/CSError.cpp
    ${IronCS_ROOT}/src/hal/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_vm.cpp
    ${SDK_ROOT}/config/fpioa-config.c
)

add_executable(IronCS_vm.elf ${VM_SOURCES})

target_link_options(IronCS_vm.elf PRIVATE
    "-nostartfiles"
    "-static"
    "-Wl,--gc-sections"
    "-Wl,-static"
    "-Wl,-EL"
    "-Wl,--no-relax"
    "-T" "${SDK_ROOT}/kendryte_libraries/kendryte_standalone-sdk/lds/kendryte.ld"
)

target_link_libraries(IronCS_vm.elf PUBLIC
    -Wl,--start-group
    "${SDK_ROOT}/build/kendryte_lcd-nt35310-standalone-driver/libkendryte_lcd-nt35310-standalone-driver.a"
    "${SDK_ROOT}/build/kendryte_camera-standalone-driver/libkendryte_camera-standalone-driver.a"
    "gcc"
    "m"
    "c"
    -Wl,--whole-archive
    "${SDK_ROOT}/build/kendryte_standalone-sdk/libkendryte_standalone-sdk.a"
    -Wl,--no-whole-archive
    -Wl,--end-group
)

add_custom_command(OUTPUT IronCS_vm.bin
    COMMAND ${CMAKE_OBJCOPY} --output-format=binary ${CMAKE_BINARY_DIR}/IronCS_vm.elf ${CMAKE_BINARY_DIR}/IronCS_vm.bin
    DEPENDS IronCS_vm.elf
    COMMENT "Generating .bin file"
)

add_custom_target(flash ALL DEPENDS IronCS_vm.bin)