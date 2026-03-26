# RMUTP_CARBOT

ESP32 Motor Driver Library สำหรับรถ 2 ล้อ (L298N)

## Features
- ควบคุมมอเตอร์ซ้าย/ขวา
- PWM ปรับความเร็ว (0–100%)
- เลี้ยวซ้าย/ขวา
- รองรับ ESP32 เท่านั้น

## Usage
```cpp
#include "RMUTP_CARBOT.h"

const int ENA = 12;
const int IN1 = 14;
const int IN2 = 27;
const int IN3 = 26;
const int IN4 = 25;
const int ENB = 33;

const int freq = 1000;
const int pwmChannelA = 0;
const int pwmChannelB = 1;
const int resolution = 8;  


RMUTP_CARBOT car(ENA, IN1, IN2, ENB, IN3, IN4);

void setup(void) 
{
  car.begin(freq, resolution, pwmChannelA, pwmChannelB);
}

void loop(void) 
{
  car.Forward(80);
}