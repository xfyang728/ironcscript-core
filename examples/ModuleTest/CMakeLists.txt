# Module test CMake configuration

if(NOT CSE_PLATFORM_EMBEDDED)
    add_executable(ModuleTest module_test.cpp)
    
    target_include_directories(ModuleTest
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
    )
    
    target_link_libraries(ModuleTest
        PRIVATE
            CScriptEngineLib
            ${CAPSTONE_LIB}
            ${ANTLR_STATIC_LIB}
            PlatformAbstraction
    )
endif()
