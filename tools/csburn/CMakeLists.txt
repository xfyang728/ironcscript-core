cmake_minimum_required(VERSION 3.10)
project(CSBurn C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CSBURN_SOURCES
    csburn.cpp
    protocol.cpp
)

add_executable(csburn ${CSBURN_SOURCES})

target_include_directories(csburn PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

if(WIN32)
    target_compile_definitions(csburn PRIVATE _WIN32)
endif()
