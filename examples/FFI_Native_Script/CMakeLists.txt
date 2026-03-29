cmake_minimum_required(VERSION 3.15)
project(FFI_Native_Script)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FFI_Native_Script main.cpp)

target_link_libraries(FFI_Native_Script CScriptEngineLib)

target_include_directories(FFI_Native_Script PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

if(WIN32)
    target_compile_definitions(FFI_Native_Script PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
