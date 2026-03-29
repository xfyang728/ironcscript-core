# 仅在非嵌入式平台编译异常处理模块
if(NOT CSE_EMBEDDED)
    set(EXCEPTION_SOURCES
        BaseException.h
        BaseException.cpp
        ExceptionHandler.h
        ExceptionHandler.cpp
        StackUnwinder.h
        StackUnwinder.cpp
    )

    add_library(Exception STATIC ${EXCEPTION_SOURCES})
    target_include_directories(Exception PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
