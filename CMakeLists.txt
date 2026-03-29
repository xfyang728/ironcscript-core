cmake_minimum_required (VERSION 3.8)

if(NOT CMAKE_CROSSCOMPILING)
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)

    if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "/NXCOMPAT:NO")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
    elseif(MINGW)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
        set(CMAKE_BUILD_TYPE Debug)
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (POLICY CMP0141 AND NOT CMAKE_CROSSCOMPILING)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (IronCScriptCore)

add_definitions(-DYY_NO_UNISTD_H)
add_definitions(-DUSE_ANTLR)
add_definitions(-DANTLR4CPP_STATIC)

set(ANTLR_INCLUDE_DIR
    extern/antlr4-runtime/include/antlr4-runtime
    extern/antlr4-runtime/include/antlr4-runtime/atn
    extern/antlr4-runtime/include/antlr4-runtime/dfa
    extern/antlr4-runtime/include/antlr4-runtime/internal
    extern/antlr4-runtime/include/antlr4-runtime/misc
    extern/antlr4-runtime/include/antlr4-runtime/support
    extern/antlr4-runtime/include/antlr4-runtime/tree
    extern/antlr4-runtime/include/antlr4-runtime/tree/pattern
    extern/antlr4-runtime/include/antlr4-runtime/tree/xpath
)
set(ANTLR_STATIC_LIB "${CMAKE_SOURCE_DIR}/extern/antlr4-runtime/lib/libantlr4-runtime-static.a")

set(CAPSTONE_DIR ${CMAKE_SOURCE_DIR}/extern/capstone_build_mingw)
set(CAPSTONE_LIB "${CMAKE_SOURCE_DIR}/extern/capstone_build_mingw/libcapstone.a")

include_directories(src)
include_directories(${CAPSTONE_DIR})
include_directories(extern/capstone_src/include)
include_directories(extern/googletest-1.17.0/googletest/include)
include_directories(extern/googletest-1.17.0/googlemock/include)
include_directories(${ANTLR_INCLUDE_DIR})

if(CMAKE_CROSSCOMPILING)
    add_definitions(-DCSE_CROSS_COMPILING)
    if(RISCV64)
        add_definitions(-DCSE_RISCV64)
    endif()
endif()

set(LIB_SOURCES
    src/frontend/generated/CScriptParser.cpp
    src/frontend/generated/CScriptLexer.cpp
    src/frontend/generated/CScriptBaseListener.cpp
    src/frontend/generated/CScriptBaseVisitor.cpp
    src/frontend/generated/CScriptListener.cpp
    src/frontend/generated/CScriptVisitor.cpp
    src/ir/IRGenerator.cpp
    src/ir/Quad.cpp
    src/frontend/semantic/SemanticAnalyzer.cpp
    src/frontend/semantic/SymbolTable.cpp
    src/IronCScript.cpp
    src/IronCScriptImpl.cpp
)

if(WIN32)
    list(APPEND LIB_SOURCES
        src/backend/WinMemoryManager.cpp
    )
endif()

if(NOT CMAKE_CROSSCOMPILING)
    list(APPEND LIB_SOURCES
        src/backend/x64/X64Code.cpp
        src/backend/x64/X64CodeOps.cpp
        src/backend/x64/X64CodeControl.cpp
        src/backend/x64/X64CodeMemory.cpp
        src/backend/x64/X64CodeUtils.cpp
    )
endif()

if(CMAKE_CROSSCOMPILING AND RISCV64)
    list(APPEND LIB_SOURCES
        src/backend/rv64/RV64Code.cpp
        src/backend/rv64/RV64MemoryManager.cpp
    )
endif()

list(APPEND LIB_SOURCES
    src/backend/codegen.cpp
    src/backend/MemoryManager.cpp
    src/backend/Architecture.cpp
    src/backend/BaseCodeGenerator.cpp
    src/backend/CodeGeneratorFactory.cpp
    src/backend/CompiledCache.cpp
    src/backend/FFIRegistry.cpp
    src/backend/ScriptFunctionRegistry.cpp
)

add_subdirectory(src/backend/cache)
add_subdirectory(src/bytecode)
add_subdirectory(src/exception)

if(NOT CMAKE_CROSSCOMPILING)
    add_subdirectory(src/module)
    add_subdirectory(src/platform)
    add_subdirectory(src/gc)
    add_subdirectory(src/sandbox)
    add_subdirectory(extern/googletest-1.17.0)
endif()

add_library(IronCScriptCoreLib STATIC ${LIB_SOURCES})
if(NOT CMAKE_CROSSCOMPILING)
    target_link_libraries(IronCScriptCoreLib PUBLIC ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB})
    target_link_libraries(IronCScriptCoreLib PUBLIC Cache BytecodeModule Exception ModuleManager PlatformAbstraction GarbageCollector Sandbox)
else()
    target_link_libraries(IronCScriptCoreLib PUBLIC ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB})
    target_link_libraries(IronCScriptCoreLib PUBLIC Cache Exception)
endif()

if(NOT CMAKE_CROSSCOMPILING)
    add_executable(IronCScriptCLI src/main_cli.cpp)
    target_link_libraries(IronCScriptCLI PRIVATE IronCScriptCoreLib)
endif()

if(CMAKE_CROSSCOMPILING AND RISCV64)
    add_executable(IronCScriptEmbedded src/main_cli_embedded.cpp)
    target_link_libraries(IronCScriptEmbedded PRIVATE IronCScriptCoreLib)

    add_executable(IronCScriptRISCVIpf src/main_cli_riscv.cpp)
    target_link_libraries(IronCScriptRISCVIpf PRIVATE IronCScriptCoreLib)
endif()

if(NOT CMAKE_CROSSCOMPILING)
    enable_testing()

    set(TEST_SOURCES
        tests/integration_tests/test_IronCScript.cpp
        tests/component_tests/test_ir.cpp
        tests/component_tests/test_codegen.cpp
    )

    add_executable(IronCScriptTests ${TEST_SOURCES})
    target_link_libraries(IronCScriptTests PRIVATE GTest::gtest_main IronCScriptCoreLib ${CAPSTONE_LIB} ${ANTLR_STATIC_LIB} PlatformAbstraction ModuleManager)

    add_test(NAME IronCScriptTests COMMAND IronCScriptTests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

    add_subdirectory(tools/cscriptc)
    add_subdirectory(tools/csburn)
endif()

if(NOT CMAKE_CROSSCOMPILING)
    add_subdirectory(examples/ExceptionTest)
    add_subdirectory(examples/FFI_Native_Script)
    add_subdirectory(examples/FFI_Script_Native)
    add_subdirectory(examples/ModuleTest)
    add_subdirectory(examples/TryCatchTest)
    add_subdirectory(examples/K210Test)
endif()
