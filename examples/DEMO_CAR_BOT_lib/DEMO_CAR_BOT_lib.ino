#include "RMUTP_CARBOT.h"  // เรียกใช้ไลบารี่ควบคุมรถ

const int ENA = 12;   // ขา PWM มอเตอร์ซ้าย
const int IN1 = 14;   // ควบคุมทิศทางมอเตอร์ซ้าย (ขา 1)
const int IN2 = 27;   // ควบคุมทิศทางมอเตอร์ซ้าย (ขา 2)
const int IN3 = 26;   // ควบคุมทิศทางมอเตอร์ขวา (ขา 1)
const int IN4 = 25;   // ควบคุมทิศทางมอเตอร์ขวา (ขา 2)
const int ENB = 33;   // ขา PWM มอเตอร์ขวา

const int freq = 1000;        // ความถี่ PWM 1000 Hz
const int pwmChannelA = 0;    // Channel PWM มอเตอร์ซ้าย
const int pwmChannelB = 1;    // Channel PWM มอเตอร์ขวา
const int resolution = 8;     // ความละเอียด PWM 8-bit (0-255)

// =============================
// การสร้าง object ควบคุมรถ
// =============================

// รูปแบบ:
// RMUTP_CARBOT(ENA, IN1, IN2, ENB, IN3, IN4)
//
// ความหมายขา:
// ─────────────────────────────
// ฝั่งซ้าย (Left Motor)
// ENA  = ขา PWM ควบคุมความเร็วล้อซ้าย
// IN1  = ควบคุมทิศทางล้อซ้าย (ขา 1)
// IN2  = ควบคุมทิศทางล้อซ้าย (ขา 2)
//
// ฝั่งขวา (Right Motor)
// ENB  = ขา PWM ควบคุมความเร็วล้อขวา
// IN3  = ควบคุมทิศทางล้อขวา (ขา 1)
// IN4  = ควบคุมทิศทางล้อขวา (ขา 2)
// ─────────────────────────────
RMUTP_CARBOT car(ENA,   IN1,    IN2, ENB, IN3, IN4);  // สร้าง object ควบคุมรถ

void setup(void) {
  car.begin(freq, resolution, pwmChannelA, pwmChannelB);  // เริ่มต้นระบบ PWM และตั้งค่าขา
}

void loop(void) {

  car.R_Forward(50);  delay(1000);  car.Stop();  delay(500);   // ล้อขวาเดินหน้า 50% 1 วิ → หยุด
  car.R_Reverse(50);  delay(1000);  car.Stop();  delay(500);   // ล้อขวาถอยหลัง 50% 1 วิ → หยุด

  car.L_Forward(50);  delay(1000);  car.Stop();  delay(500);   // ล้อซ้ายเดินหน้า 50% 1 วิ → หยุด
  car.L_Reverse(50);  delay(1000);  car.Stop();  delay(500);   // ล้อซ้ายถอยหลัง 50% 1 วิ → หยุด

  car.Forward(100);   delay(2000);                              // วิ่งตรงเต็มสปีด 2 วิ
  car.Reverse(100);   delay(2000);                              // ถอยหลังเต็มสปีด 2 วิ
  car.Stop();         delay(500);                               // หยุดรถ

  car.TurnRight1(75); delay(1000);  car.Stop(); delay(500);    // เลี้ยวขวาแบบล้อเดียว 75%
  car.TurnLeft1(75);  delay(1000);  car.Stop(); delay(500);    // เลี้ยวซ้ายแบบล้อเดียว 75%

  
  car.TurnRight2(85); delay(2000);  car.Stop(); delay(500);    // หมุนขวาอยู่กับที่ 85%
  car.TurnLeft2(85);  delay(2000);  car.Stop(); delay(500);    // หมุนซ้ายอยู่กับที่ 85%
  
}