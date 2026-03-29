# CScript 硬件API设计规范

## 设计目标

1. **Arduino风格**: 简洁易用，开发者友好
2. **跨平台**: K210/STM32/ESP32等平台统一接口
3. **灵活**: 支持高层封装和底层直接操作
4. **可扩展**: 方便添加新硬件模块

## API层次结构

```
┌─────────────────────────────────────────────────────────┐
│                    应用层API                            │
│  led_on(), motor_run(50), sensor_read()                │
├─────────────────────────────────────────────────────────┤
│                    中间层API                            │
│  digitalWrite(), analogRead(), i2c_write()              │
├─────────────────────────────────────────────────────────┤
│                    底层API                              │
│  gpio_set_mode(), gpio_write(), uart_send()            │
└─────────────────────────────────────────────────────────┘
```

## 1. GPIO API

### 1.1 基础GPIO (Arduino风格)

```c
// CScript脚本
extern void pinMode(int pin, int mode);
extern void digitalWrite(int pin, int value);
extern int digitalRead(int pin);

// 常量定义
const int INPUT = 0;
const int OUTPUT = 1;
const int INPUT_PULLUP = 2;
const int HIGH = 1;
const int LOW = 0;

void main() {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
}
```

### 1.2 高级GPIO

```c
// PWM输出
extern void analogWrite(int pin, int value);  // 0-255
extern void pwmSetFrequency(int pin, int freq);
extern void pwmSetDuty(int pin, int duty);    // 0-100

// 模拟输入
extern int analogRead(int pin);               // 0-4095 (12-bit)

// 引脚映射 (平台相关)
// K210: GPIOHS(0-31), GPIO(32-39)
// STM32: PA0-PA15(0-15), PB0-PB15(16-31)...
```

## 2. UART API

```c
extern void serialBegin(int baud);
extern void serialWrite(int ch);
extern int serialRead();
extern int serialAvailable();
extern void serialPrint(string s);
extern void serialPrintln(string s);
extern void serialPrintf(string fmt, ...);

void main() {
    serialBegin(115200);
    serialPrintln("Hello CScript!");
    
    while (serialAvailable()) {
        int ch = serialRead();
        serialWrite(ch);
    }
}
```

## 3. SPI API

```c
extern void spiBegin(int sck, int miso, int mosi, int cs);
extern void spiSetFrequency(int freq);
extern int spiTransfer(int data);
extern void spiWriteBuffer(int* buf, int len);
extern void spiReadBuffer(int* buf, int len);

void main() {
    spiBegin(18, 19, 23, 5);  // SCK, MISO, MOSI, CS
    spiSetFrequency(1000000);
    
    int data = spiTransfer(0x55);
}
```

## 4. I2C API

```c
extern void i2cBegin(int sda, int scl);
extern void i2cSetFrequency(int freq);
extern int i2cWrite(int addr, int reg, int data);
extern int i2cRead(int addr, int reg);

void main() {
    i2cBegin(21, 22);  // SDA, SCL
    i2cSetFrequency(100000);
    
    i2cWrite(0x3C, 0x00, 0x01);  // 设备地址, 寄存器, 数据
    int val = i2cRead(0x3C, 0x01);
}
```

## 5. Timer API

```c
extern void timerBegin(int id, int freq);
extern void timerStart(int id);
extern void timerStop(int id);
extern void timerAttachInterrupt(int id, void callback());

void main() {
    timerBegin(0, 1000);  // 1kHz
    timerStart(0);
}
```

## 6. 中断API

```c
extern void attachInterrupt(int pin, int mode, void callback());
extern void detachInterrupt(int pin);

const int RISING = 1;
const int FALLING = 2;
const int CHANGE = 3;

void buttonCallback() {
    // 中断处理
}

void main() {
    attachInterrupt(5, RISING, buttonCallback);
}
```

## 7. 系统API

```c
extern void delay(int ms);
extern void delayMicroseconds(int us);
extern unsigned long millis();
extern unsigned long micros();
extern void reboot();
extern int getFreeMemory();
```

## 平台适配层

### K210 实现

```cpp
// firmware/k210/native_api.cpp

void nativePinMode(cse::BytecodeVM* vm) {
    int pin = vm->getArg(0).value.intVal;
    int mode = vm->getArg(1).value.intVal;
    
    // 统一引脚编号转换
    if (pin >= 32) {
        // GPIO (32-39)
        gpio_set_drive_mode(pin - 32, toGpioMode(mode));
    } else {
        // GPIOHS (0-31)
        gpiohs_set_drive_mode(pin, toGpioMode(mode));
    }
}

void nativeDigitalWrite(cse::BytecodeVM* vm) {
    int pin = vm->getArg(0).value.intVal;
    int value = vm->getArg(1).value.intVal;
    
    if (pin >= 32) {
        gpio_set_pin(pin - 32, value ? GPIO_PV_HIGH : GPIO_PV_LOW);
    } else {
        gpiohs_set_pin(pin, value ? GPIO_PV_HIGH : GPIO_PV_LOW);
    }
}
```

### STM32 实现

```cpp
// firmware/stm32/native_api.cpp

void nativePinMode(cse::BytecodeVM* vm) {
    int pin = vm->getArg(0).value.intVal;
    int mode = vm->getArg(1).value.intVal;
    
    GPIO_TypeDef* port = getGpioPort(pin);
    uint16_t pinNum = getGpioPin(pin);
    
    GPIO_InitTypeDef init = {
        .Pin = pinNum,
        .Mode = toStmMode(mode),
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_HIGH
    };
    HAL_GPIO_Init(port, &init);
}

void nativeDigitalWrite(cse::BytecodeVM* vm) {
    int pin = vm->getArg(0).value.intVal;
    int value = vm->getArg(1).value.intVal;
    
    GPIO_TypeDef* port = getGpioPort(pin);
    uint16_t pinNum = getGpioPin(pin);
    
    HAL_GPIO_WritePin(port, pinNum, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
```

## 引脚编号统一方案

### K210
| 范围 | 类型 | 说明 |
|------|------|------|
| 0-31 | GPIOHS | 高速GPIO |
| 32-39 | GPIO | 普通GPIO |
| 100-147 | FPIOA | 物理引脚映射 |

### STM32
| 范围 | 类型 | 说明 |
|------|------|------|
| 0-15 | PA0-PA15 | GPIOA |
| 16-31 | PB0-PB15 | GPIOB |
| 32-47 | PC0-PC15 | GPIOC |
| ... | ... | ... |

## 注册表设计

```cpp
// 统一API注册
struct NativeApiEntry {
    const char* name;
    NativeFunction func;
    int minArgs;
    int maxArgs;
    const char* description;
};

static const NativeApiEntry g_NativeApis[] = {
    // GPIO
    {"pinMode",          nativePinMode,          2, 2, "Set pin mode"},
    {"digitalWrite",     nativeDigitalWrite,     2, 2, "Write digital value"},
    {"digitalRead",      nativeDigitalRead,      1, 1, "Read digital value"},
    {"analogWrite",      nativeAnalogWrite,      2, 2, "Write PWM value"},
    {"analogRead",       nativeAnalogRead,       1, 1, "Read analog value"},
    
    // UART
    {"serialBegin",      nativeSerialBegin,      1, 1, "Initialize serial"},
    {"serialWrite",      nativeSerialWrite,      1, 1, "Write byte"},
    {"serialRead",       nativeSerialRead,       0, 0, "Read byte"},
    {"serialAvailable",  nativeSerialAvailable,  0, 0, "Check available"},
    
    // I2C
    {"i2cBegin",         nativeI2cBegin,         2, 2, "Initialize I2C"},
    {"i2cWrite",         nativeI2cWrite,         3, 3, "Write I2C data"},
    {"i2cRead",          nativeI2cRead,          2, 2, "Read I2C data"},
    
    // SPI
    {"spiBegin",         nativeSpiBegin,         4, 4, "Initialize SPI"},
    {"spiTransfer",      nativeSpiTransfer,      1, 1, "SPI transfer"},
    
    // System
    {"delay",            nativeDelay,            1, 1, "Delay milliseconds"},
    {"millis",           nativeMillis,           0, 0, "Get uptime"},
    {"reboot",           nativeReboot,           0, 0, "Reboot system"},
    
    {nullptr, nullptr, 0, 0, nullptr}
};

void registerNativeApis(cse::BytecodeVM* vm) {
    for (int i = 0; g_NativeApis[i].name; i++) {
        vm->registerNativeFunction(g_NativeApis[i].name, g_NativeApis[i].func);
    }
}
```

## 示例脚本

### LED闪烁
```c
extern void pinMode(int pin, int mode);
extern void digitalWrite(int pin, int value);
extern void delay(int ms);

const int LED_PIN = 13;
const int OUTPUT = 1;
const int HIGH = 1;
const int LOW = 0;

void main() {
    pinMode(LED_PIN, OUTPUT);
    
    while (1) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }
}
```

### I2C传感器读取
```c
extern void serialBegin(int baud);
extern void serialPrintln(string s);
extern void i2cBegin(int sda, int scl);
extern int i2cRead(int addr, int reg);
extern void delay(int ms);

const int MPU6050_ADDR = 0x68;

void main() {
    serialBegin(115200);
    i2cBegin(21, 22);
    
    while (1) {
        int accel_x = i2cRead(MPU6050_ADDR, 0x3B);
        serialPrintln("Accel X: " + accel_x);
        delay(100);
    }
}
```

### PWM电机控制
```c
extern void pinMode(int pin, int mode);
extern void analogWrite(int pin, int value);
extern void delay(int ms);

const int MOTOR_PIN = 5;
const int OUTPUT = 1;

void main() {
    pinMode(MOTOR_PIN, OUTPUT);
    
    // 渐加速
    int speed = 0;
    while (speed <= 255) {
        analogWrite(MOTOR_PIN, speed);
        speed = speed + 5;
        delay(50);
    }
    
    // 渐减速
    while (speed >= 0) {
        analogWrite(MOTOR_PIN, speed);
        speed = speed - 5;
        delay(50);
    }
}
```

## 扩展机制

### 自定义模块注册
```cpp
// 用户可扩展自己的硬件模块
class CustomModule {
public:
    static void registerApi(cse::BytecodeVM* vm) {
        vm->registerNativeFunction("mySensor_init", nativeMySensorInit);
        vm->registerNativeFunction("mySensor_read", nativeMySensorRead);
    }
    
private:
    static void nativeMySensorInit(cse::BytecodeVM* vm);
    static void nativeMySensorRead(cse::BytecodeVM* vm);
};
```

## 版本规划

| 版本 | 功能 |
|------|------|
| v1.0 | GPIO基础API |
| v1.1 | UART, PWM, ADC |
| v1.2 | I2C, SPI |
| v1.3 | Timer, 中断 |
| v2.0 | RTOS集成, 多任务 |
