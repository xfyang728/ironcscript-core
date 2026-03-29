#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

echo "=========================================="
echo "CScript K210 VM Firmware Build"
echo "=========================================="
echo "Build Dir: $BUILD_DIR"
echo ""

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

rm -rf CMakeCache.txt CMakeFiles

echo "[1/3] Running CMake..."
cmake -G "Unix Makefiles" \
    -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/toolchain.cmake" \
    "$SCRIPT_DIR"

if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed"
    exit 1
fi

echo "[2/3] Building..."
cmake --build .

if [ $? -ne 0 ]; then
    echo "ERROR: Build failed"
    exit 1
fi

echo ""
echo "=========================================="
echo "Build complete!"
echo "=========================================="

if [ -f "$BUILD_DIR/cscript_vm.elf" ]; then
    echo "ELF: $BUILD_DIR/cscript_vm.elf"
    ls -lh "$BUILD_DIR/cscript_vm.elf"
fi

if [ -f "$BUILD_DIR/cscript_vm.bin" ]; then
    echo "BIN: $BUILD_DIR/cscript_vm.bin"
    ls -lh "$BUILD_DIR/cscript_vm.bin"
fi