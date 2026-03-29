#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

echo "========================================"
echo "CScript STM32 VM Firmware Build (CMake/WSL)"
echo "========================================"
echo "Build Dir: $BUILD_DIR"
echo ""

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

rm -rf CMakeCache.txt CMakeFiles

echo "[1/3] Running CMake..."
cmake -G "Unix Makefiles" \
    -DSTM32_SDK_ROOT="/mnt/d/MyCode/CScriptEngine/extern/stm32f4xx-hal-sdk" \
    -DCSCRIPT_ROOT="/mnt/d/MyCode/CScriptEngine" \
    -DTOOLCHAIN="/mnt/d/MyCode/CScriptEngine/extern/stm32-toolchain-linux/bin" \
    "$SCRIPT_DIR"

if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed"
    exit 1
fi

echo "[2/3] Building..."
cmake --build . -j$(nproc)

if [ $? -ne 0 ]; then
    echo "ERROR: Build failed"
    exit 1
fi

echo ""
echo "========================================"
echo "Build complete!"
echo "========================================"
echo "ELF: $BUILD_DIR/cscript_vm.elf"
echo "BIN: $BUILD_DIR/cscript_vm.bin"
echo ""

if [ -f "$BUILD_DIR/cscript_vm.elf" ]; then
    echo "ELF size:"
    /mnt/d/MyCode/CScriptEngine/extern/stm32-toolchain-linux/bin/arm-none-eabi-size "$BUILD_DIR/cscript_vm.elf" 2>/dev/null || echo "  (size tool not available)"
    ls -lh "$BUILD_DIR/cscript_vm.elf"
fi

if [ -f "$BUILD_DIR/cscript_vm.bin" ]; then
    echo "BIN size:"
    ls -lh "$BUILD_DIR/cscript_vm.bin"
fi