# Bytecode Module

set(BYTECODE_SOURCES
    BytecodeFormat.cpp
    BytecodeCompiler.cpp
    vm/BytecodeVM.cpp
)

add_library(BytecodeModule STATIC ${BYTECODE_SOURCES})
target_include_directories(BytecodeModule PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

if(NOT CSE_EMBEDDED)
    target_link_libraries(BytecodeModule CScriptEngineLib)
endif()

# K210 VM Module
add_subdirectory(vm/k210)
