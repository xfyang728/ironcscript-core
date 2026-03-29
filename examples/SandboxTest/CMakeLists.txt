# Sandbox Test

add_executable(SandboxTest sandbox_test.cpp)

target_link_libraries(SandboxTest CScriptEngineLib)

# 包含头文件目录
target_include_directories(SandboxTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
