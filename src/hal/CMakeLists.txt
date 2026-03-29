# HAL Abstraction Layer

set(HAL_HEADERS
    IHardwareAbstraction.h
    IBootloader.h
    EmbeddedRuntime.h
    IStandardGPIO.h
    IStandardUART.h
    IStandardTimer.h
    HardwareFactory.h
)

set(HAL_SOURCES
    HardwareFactory.cpp
    ../platform/mock/MockGPIO.cpp
    ../platform/mock/MockTimer.cpp
    ../platform/mock/MockUART.cpp
)

add_library(HAL STATIC ${HAL_SOURCES})

target_include_directories(HAL PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/hal
)