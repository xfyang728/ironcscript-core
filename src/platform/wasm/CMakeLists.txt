set(WASM_PLATFORM_SOURCES
    WasmPlatform.cpp
)

add_library(WasmPlatform STATIC ${WASM_PLATFORM_SOURCES})

target_include_directories(WasmPlatform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
