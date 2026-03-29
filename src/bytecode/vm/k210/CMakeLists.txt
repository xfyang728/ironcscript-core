# K210 VM Module

set(K210VM_SOURCES
    K210VM.cpp
)

add_library(K210VM STATIC ${K210VM_SOURCES})
target_include_directories(K210VM PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(K210VM
    BytecodeModule
)
