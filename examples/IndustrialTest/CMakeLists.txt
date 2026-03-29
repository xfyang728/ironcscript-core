# Industrial Test CMake configuration

if(NOT CSE_PLATFORM_EMBEDDED)
    add_executable(IndustrialTest main.cpp)
    target_include_directories(IndustrialTest PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    )
    target_link_libraries(IndustrialTest PRIVATE CScriptEngineLib)
endif()
