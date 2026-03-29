// RGB LED Test Script (Arduino Style)
// Control RGB LED using analogWrite (PWM)
// K210 pins: G=IO13, R=IO14, B=IO12

extern void rgb_set(int r, int g, int b);
// Arduino风格API
extern void pinMode(int pin, int mode);
extern void analogWrite(int pin, int value);
extern void delay(int ms);

// 常量定义
const int OUTPUT = 1;
const int LED_R = 14;  // 红灯引脚
const int LED_G = 13;  // 绿灯引脚
const int LED_B = 12;  // 蓝灯引脚

const int LED_G_PIN = 37;
const int LED_R_PIN = 36;
const int LED_B_PIN = 35;

// RGB颜色设置函数
void rgbWrite(int r, int g, int b) {
    analogWrite(LED_R_PIN, r == 0);
    analogWrite(LED_G_PIN, g == 0);
    analogWrite(LED_B_PIN, b == 0);
}

void main() {
    // Red
    rgb_set(255, 0, 0);
    delay(2000);

    // 初始化引脚
    // pinMode(LED_R, OUTPUT);
    // pinMode(LED_G, OUTPUT);
    // pinMode(LED_B, OUTPUT);
    
    // // 红色
    // rgbWrite(255, 0, 0);
    // delay(2000);
    
    // 绿色
    rgbWrite(0, 255, 0);
    delay(2000);
    
    // // 蓝色
    // rgbWrite(0, 0, 255);
    // delay(2000);
    
    // // 黄色 (红+绿)
    // rgbWrite(255, 255, 0);
    // delay(2000);
    
    // // 紫色 (红+蓝)
    // rgbWrite(255, 0, 255);
    // delay(2000);
    
    // // 青色 (绿+蓝)
    // rgbWrite(0, 255, 255);
    // delay(2000);
    
    // // 白色 (红+绿+蓝)
    // rgbWrite(255, 255, 255);
    // delay(2000);
    
    // 关闭
    rgbWrite(0, 0, 0);
}
