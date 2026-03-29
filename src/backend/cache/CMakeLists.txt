cmake_minimum_required(VERSION 3.10)

add_library(Cache STATIC
    StringTable.cpp
    CacheWriter.cpp
    CacheReader.cpp
    ScriptCache.cpp
)

if(NOT CSE_PLATFORM_EMBEDDED)
    target_sources(Cache PRIVATE
        X64Relocator.cpp
    )
endif()

target_include_directories(Cache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
