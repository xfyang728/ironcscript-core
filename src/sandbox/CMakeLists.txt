cmake_minimum_required(VERSION 3.10)

add_library(Sandbox STATIC
    MemorySandbox.cpp
)

target_include_directories(Sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})