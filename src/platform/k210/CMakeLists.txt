# K210 Platform Support

set(KENDYKITE_SDK_DIR ${CMAKE_SOURCE_DIR}/extern/kendryte_camera-screen-standalone/kendryte_libraries/kendryte_standalone-sdk)

set(K210_PLATFORM_SOURCES
    K210Flash.cpp
    K210Bootloader.cpp
    K210HAL.cpp
    K210Hardware.cpp
    K210GPIO.cpp
    K210Timer.cpp
    K210UART.cpp
)

add_library(K210Platform STATIC ${K210_PLATFORM_SOURCES})

target_include_directories(K210Platform PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/platform/k210
    ${KENDYKITE_SDK_DIR}/lib/drivers/include
    ${KENDYKITE_SDK_DIR}/lib/bsp/include
)

target_link_libraries(K210Platform
    K210VM
    BytecodeCompiler
)

if(CSE_K210_FIRMWARE)
    target_compile_definitions(K210Platform PRIVATE __K210__=1)
    target_compile_options(K210Platform PRIVATE -fno-exceptions -fno-rtti -fno-threadsafe-statics)
endif()
