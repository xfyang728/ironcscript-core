if(NOT CSE_PLATFORM_EMBEDDED)
    add_executable(DebuggerTest debugger_test.cpp)
    target_link_libraries(DebuggerTest CScriptEngineLib ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB} PlatformAbstraction)
endif()
