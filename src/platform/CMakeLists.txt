cmake_minimum_required(VERSION 3.10)

add_library(PlatformAbstraction
    PlatformAbstraction.cpp
    PlatformFactory.cpp
    RiscV64Platform.cpp
    RiscV64EmbeddedPlatform.cpp
    StandardLibrary.cpp
)

# 在非交叉编译环境中添加X64Platform
if(NOT CMAKE_CROSSCOMPILING)
    target_sources(PlatformAbstraction PRIVATE X64Platform.cpp)
endif()

# 包含头文件目录
target_include_directories(PlatformAbstraction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 链接垃圾回收器
target_link_libraries(PlatformAbstraction PUBLIC GarbageCollector)

# 平台特定的编译选项
if(WIN32)
    target_compile_definitions(PlatformAbstraction PRIVATE _WIN32)
elseif(UNIX)
    target_compile_definitions(PlatformAbstraction PRIVATE UNIX)
endif()

# 为RISC-V平台添加特定编译选项
if(CMAKE_SYSTEM_PROCESSOR MATCHES "riscv64")
    target_compile_definitions(PlatformAbstraction PRIVATE __riscv64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    target_compile_definitions(PlatformAbstraction PRIVATE __x86_64__)
endif()

# K210平台支持
if(CSE_K210)
    add_subdirectory(k210)
endif()

# STM32平台支持
if(CSE_STM32)
    add_subdirectory(stm32)
endif()