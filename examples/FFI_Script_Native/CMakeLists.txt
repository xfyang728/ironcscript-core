cmake_minimum_required(VERSION 3.15)

project(CScriptEngineExamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)

if(NOT CMAKE_CROSSCOMPILING)
    find_package(Threads REQUIRED)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(FFI_Script_Native
    test_extern_all.cpp
)

add_executable(FFI_SimpleTest
    test_extern_double.cpp
)

target_link_libraries(FFI_Script_Native
    PRIVATE
    CScriptEngineLib
)

if(NOT CMAKE_CROSSCOMPILING)
    target_link_libraries(FFI_Script_Native PRIVATE Threads::Threads)
    target_link_libraries(FFI_SimpleTest PRIVATE Threads::Threads)
endif()

target_link_libraries(FFI_SimpleTest
    PRIVATE
    CScriptEngineLib
)

target_include_directories(FFI_Script_Native
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)