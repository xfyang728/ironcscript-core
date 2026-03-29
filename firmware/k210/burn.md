# K210 烧录指南

## 环境准备

### 安装 kflash

```bash
pip3 install kflash
```

### 查看帮助

```bash
kflash --help
```

## 硬件连接

| K210 引脚 | 说明 |
|-----------|------|
| USB 转串口 | 连接电脑 USB |
| BOOT 引脚 | 烧录时需要拉低 |
| RESET 引脚 | 复位按钮 |

**当前配置**：
- 串口：`COM9`
- 波特率：`115200`

## 烧录固件

固件烧录到 Flash 地址 `0x00000`：

```bash
kflash -p COM9 -b 115200 -B goE firmware.bin
```

参数说明：
- `-p COM9` - 串口设备
- `-b 115200` - 波特率
- `-B goE` - 板子类型 (Maix GOE)
- `firmware.bin` - 固件文件

## 烧录脚本

脚本烧录到 Flash 地址 `0x80000`：

```bash
# 擦除并烧录脚本
kflash -p COM9 -b 115200 -a 0x80000 -e script.csb

# 仅烧录脚本（不擦除）
kflash -p COM9 -b 115200 -a 0x80000 script.csb
```

参数说明：
- `-a 0x80000` - 脚本存储地址
- `-e` - 烧录前擦除 Flash

## 常用命令示例

### 1. 烧录固件
```bash
kflash -p COM9 -b 115200 -B goE d:/MyCode/IronCScript/firmware/k210/build/IronCS_vm.bin
```

### 2. 烧录脚本
```bash
kflash -p COM9 -b 115200 -a 0x80000 -e d:/MyCode/IronCScript/examples/K210Test/debug_test_arduino.csb
```

### 3. 烧录后自动运行
```bash
kflash -p COM9 -b 115200 -a 0x80000 -e -t 60 d:/MyCode/IronCScript/examples/K210Test/debug_test_arduino.csb
```

### 4. 接收串口日志

使用 PowerShell 脚本接收串口日志并保存到文件：

```bash
powershell -File d:/MyCode/IronCScript/tools/serial_log.ps1 COM9 115200
```

日志将同时显示在终端并保存到 `d:/MyCode/IronCScript/examples/out.s`（覆盖写入）。

按 `Ctrl+C` 退出并保存日志。

### 5. 完整烧录流程（烧录后自动接收日志）

终端 1：先启动日志接收
```bash
powershell -File d:/MyCode/IronCScript/tools/serial_log.ps1 COM9 115200
```

终端 2：烧录脚本
```bash
kflash -p COM9 -b 115200 -a 0x80000 -e d:/MyCode/IronCScript/examples/K210Test/debug_test_arduino.csb
```

或使用烧录后自动运行（使用 kflash 内置终端）：
```bash
kflash -p COM9 -b 115200 -a 0x80000 -e -t -n d:/MyCode/IronCScript/examples/K210Test/debug_test_arduino.csb 2>&1 | tee d:/MyCode/IronCScript/examples/out.s
```

## kflash ISP 下载流程

K210 的烧录过程如下：

```
PC 端                                    K210 芯片
-------                                  -------
1. 打开串口
2. 设置 DTR/RTS -> BOOT=低, RESET=低
3. 设置 RESET=高                           [芯片启动，检测 BOOT 引脚]
                                          [BOOT 引脚低 -> 进入 ISP 模式]
4. 发送握手信号                           <-- 响应
5. 发送 RAM 烧录程序到芯片 RAM
6. 发送启动 RAM 程序命令                  --> 运行 RAM 中的烧录程序
7. ISP 程序接收固件                       <-- 发送固件数据
8. ISP 程序写入 Flash
9. 设置 DTR/RTS -> BOOT=高, RESET=低
10. 设置 RESET=高                          [芯片正常启动，从 Flash 加载固件]
```

## 故障排除

### 烧录失败

1. **检查串口**：确认 COM 号正确
2. **检查波特率**：115200 是默认波特率
3. **手动进入 ISP 模式**：
   - 按住 BOOT 按钮
   - 按一下 RESET 按钮
   - 保持 BOOT 按下，松开 RESET
   - 此时可以烧录

### 串口无响应

```bash
# 列出所有串口 (Windows PowerShell)
[System.IO.Ports.SerialPort]::GetPortNames()
```

### 波特率选择

- `115200` - 最稳定，兼容性最好
- `1500000` - 烧录速度快，但需要设备支持

## 地址映射

| 地址范围 | 用途 |
|---------|------|
| 0x00000 - 0x7FFFF | 固件区 (512KB) |
| 0x80000 - 0xFFFFF | 脚本区 (512KB) |

## 相关文档

- [build.md](build.md) - 固件编译指南
