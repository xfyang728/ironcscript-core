if(NOT CSE_PLATFORM_EMBEDDED)
    add_executable(TryCatchTest try_catch_test.cpp)
    target_link_libraries(TryCatchTest CScriptEngineLib ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB} PlatformAbstraction)
endif()
