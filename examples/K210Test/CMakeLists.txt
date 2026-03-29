# K210 Test Example
# 在 K210 上运行字节码的测试程序

set(K210_TEST_SOURCES
    k210_test.cpp
)

add_executable(k210_test ${K210_TEST_SOURCES})

target_link_libraries(k210_test
    K210VM
    BytecodeModule
)

target_include_directories(k210_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
