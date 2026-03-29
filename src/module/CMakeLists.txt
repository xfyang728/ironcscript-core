# Module system CMake configuration

# 仅在非嵌入式平台编译模块管理器
if(NOT CSE_EMBEDDED)
    set(SOURCE_FILES
        ModuleManager.cpp
    )

    set(HEADER_FILES
        ModuleManager.h
    )

    add_library(ModuleManager
        ${SOURCE_FILES}
        ${HEADER_FILES}
    )

    target_include_directories(ModuleManager
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
    )

    # 设置 C++ 标准为 C++17 以支持 filesystem 库
    set_target_properties(ModuleManager PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    # 链接 filesystem 库（在某些编译器上可能需要）
    if(MSVC)
        # MSVC 从 VS 2017 开始内置支持 filesystem
    else()
        # GCC 和 Clang 可能需要链接 stdc++fs
        target_link_libraries(ModuleManager PRIVATE stdc++fs)
    endif()

    # target_link_libraries(ModuleManager
    #     PRIVATE
    #         frontend
    # )
endif()
