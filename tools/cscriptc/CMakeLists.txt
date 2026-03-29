# IronCS Compiler Tool (cscriptc)
# 主机端编译器，将 IronCS 编译为字节码

set(CSCRIPTC_SOURCES
    cscriptc.cpp
)

add_executable(cscriptc ${CSCRIPTC_SOURCES})

target_link_libraries(cscriptc
    IronCScriptCoreLib
    ModuleManager
    BytecodeModule
    Exception
    ${ANTLR_STATIC_LIB}
    ${CAPSTONE_LIB}
)

target_include_directories(cscriptc PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(cscriptc "-Wl,--start-group")
target_link_libraries(cscriptc IronCScriptCoreLib ModuleManager)
target_link_libraries(cscriptc "-Wl,--end-group")

install(TARGETS cscriptc DESTINATION bin)