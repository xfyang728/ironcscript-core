# STM32 固件编译指南

## 编译环境

### 必要工具
- **ARM Cortex-M 交叉编译器**：位于 `D:/MyCode/IronCScript/ironcscript-core/extern/stm32-toolchain/bin`
- **STM32 HAL SDK**：位于 `D:/MyCode/IronCScript/ironcscript-core/extern/stm32f4xx-hal-sdk`
- **CMake**：版本 3.10 或更高
- **MinGW Make**：用于 Windows 环境下的构建

### 目录结构
```
firmware/stm32/
├── CMakeLists.txt          # CMake 构建配置
├── main_vm.cpp             # STM32 VM 主程序
└── build/                  # 构建输出目录
    ├── IronCS_vm.elf      # ELF 可执行文件
    └── IronCS_vm.bin      # 二进制固件文件
```

## 编译步骤

### Windows 环境编译

1. **创建构建目录**
   ```powershell
   New-Item -ItemType Directory -Path build -Force
   cd build
   ```

2. **配置 CMake**
   ```powershell
   cmake -G "MinGW Makefiles" ..
   ```

3. **构建固件**
   ```powershell
   cmake --build .
   ```

4. **验证输出**
   构建完成后，会在 `build` 目录中生成：
   - `IronCS_vm.elf`：包含调试信息的 ELF 可执行文件
   - `IronCS_vm.bin`：用于烧录的二进制固件文件

## 依赖文件

### STM32 驱动（来自 IronCScript）
- `src/platform/stm32/STM32GPIO.cpp` - GPIO 实现
- `src/platform/stm32/STM32Timer.cpp` - Timer 实现
- `src/platform/stm32/STM32UART.cpp` - UART 实现
- `src/platform/stm32/STM32DFUBootloader.cpp` - DFU 烧录协议
- `src/platform/stm32/STM32Hardware.cpp` - 硬件抽象

### 共享代码
- `src/bytecode/vm/BytecodeVM.cpp` - 字节码虚拟机
- `src/bytecode/BytecodeFormat.cpp` - 字节码格式
- `src/hal/` - 硬件抽象层接口
- `src/industrial/` - 工业协议 (ModbusRTU)

## 注意事项

1. **工具链路径**：确保 `STM32_SDK_ROOT` 和 `TOOLCHAIN` 路径正确
2. **STM32 驱动状态**：STM32 驱动实现可能需要进一步完善
3. **Flash 地址**：STM32 默认从 `0x08000000` 开始

## 烧录说明

生成的 `IronCS_vm.bin` 文件可以使用 STM32 烧录工具烧录到设备：

使用 ST-Link:
```bash
st-flash write IronCS_vm.bin 0x08000000
```

使用 DFU 模式:
```bash
dfu-util -d 0483:df11 -a 0 --dfuse-address 0x08000000 -D IronCS_vm.bin
```

## 构建结果

成功编译后，会生成以下文件：
- **IronCS_vm.elf**：ELF 格式可执行文件
- **IronCS_vm.bin**：二进制固件文件

这些文件可用于在 STM32 平台上运行 IronCS 字节码程序。