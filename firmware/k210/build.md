# K210 固件编译指南

## 编译环境

### 必要工具
- **RISC-V 交叉编译器**：位于 `D:/MyCode/IronCScript/extern/kendryte-toolchain/bin`
- **CMake**：版本 3.10 或更高
- **MinGW Make**：用于 Windows 环境下的构建

### 目录结构
```
firmware/k210/
├── CMakeLists.txt          # CMake 构建配置
├── build.sh                # Windows 构建脚本
├── build-wsl.sh            # WSL 构建脚本
├── toolchain.cmake         # 工具链配置文件
├── main_vm.cpp             # K210 VM 主程序
└── build/                  # 构建输出目录
    ├── IronCS_vm.elf      # ELF 可执行文件
    └── IronCS_vm.bin      # 二进制固件文件
```

## 编译步骤

### Windows 环境编译

1. **清理构建目录**（如果存在）
   ```powershell
   Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
   New-Item -ItemType Directory -Path build -Force
   cd build
   ```

2. **配置 CMake**
   ```powershell
   cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="../toolchain.cmake" ..
   ```

3. **构建固件**
   ```powershell
   cmake --build .
   ```

4. **验证输出**
   构建完成后，会在 `build` 目录中生成：
   - `IronCS_vm.elf`：包含调试信息的 ELF 可执行文件
   - `IronCS_vm.bin`：用于烧录的二进制固件文件

### WSL 环境编译

1. **运行构建脚本**
   ```bash
   bash build-wsl.sh
   ```

2. **脚本会自动**：
   - 创建构建目录
   - 配置 CMake
   - 执行构建
   - 显示构建结果

## 关键文件说明

### 配置文件
- **CMakeLists.txt**：定义构建目标和源文件
- **toolchain.cmake**：配置 RISC-V 交叉编译器路径和编译选项

### 源文件说明
- **main_vm.cpp**：K210 VM 主程序入口，位于 `firmware/k210/` 目录

### 生成文件
- **IronCS_vm.elf**：ELF 格式可执行文件，包含调试信息
- **IronCS_vm.bin**：二进制固件文件，用于烧录到 K210 设备

## 注意事项

1. **编译器路径**：确保 `toolchain.cmake` 中的编译器路径正确
2. **依赖项**：确保 SDK 依赖库已正确构建
3. **构建错误**：如果遇到构建错误，检查：
   - 编译器是否正确安装
   - 源文件路径是否正确
   - CMake 版本是否满足要求

## 烧录说明

生成的 `IronCS_vm.bin` 文件可以使用 K210 烧录工具（如 kflash）烧录到设备：

```bash
kflash -p /dev/ttyUSB0 -b 1500000 IronCS_vm.bin
```

## 故障排除

- **编译器找不到**：检查 `toolchain.cmake` 中的路径配置
- **源文件路径错误**：修改 `CMakeLists.txt` 中的源文件路径
- **链接错误**：确保 SDK 依赖库已正确构建

## 构建结果

成功编译后，会生成以下文件：
- **IronCS_vm.elf**：约 1.8MB，包含调试信息
- **IronCS_vm.bin**：约 200KB，用于烧录

这些文件可用于在 K210 平台上运行 IronCS 字节码程序。