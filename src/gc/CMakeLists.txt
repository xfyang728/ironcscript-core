cmake_minimum_required(VERSION 3.10)

add_library(GarbageCollector STATIC
    GarbageCollector.cpp
)

target_include_directories(GarbageCollector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})