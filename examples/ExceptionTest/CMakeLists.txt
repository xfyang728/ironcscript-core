if(NOT CSE_PLATFORM_EMBEDDED)
    add_executable(ExceptionTest exception_test.cpp)
    target_link_libraries(ExceptionTest CScriptEngineLib ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB} PlatformAbstraction)
endif()
