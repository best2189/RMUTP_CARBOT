#include "RMUTP_CARBOT.h"

#define PWM(x) map(constrain(x,0,100), 0,100, 0,_maxDuty)

RMUTP_CARBOT::RMUTP_CARBOT(int ENA, int IN1, int IN2, int ENB, int IN3, int IN4) {
  _ENA = ENA;
  _IN1 = IN1;
  _IN2 = IN2;

  _ENB = ENB;
  _IN3 = IN3;
  _IN4 = IN4;
}

void RMUTP_CARBOT::begin(int freq, int resolution, int chA, int chB) {

  _chA = chA;
  _chB = chB;

  // ⭐ รองรับทุก bit
  _maxDuty = (1 << resolution) - 1;

  pinMode(_IN1, OUTPUT);
  pinMode(_IN2, OUTPUT);
  pinMode(_IN3, OUTPUT);
  pinMode(_IN4, OUTPUT);

  // ใช้แบบ pin (attachChannel)
  ledcAttachChannel(_ENA, freq, resolution, _chA);
  ledcAttachChannel(_ENB, freq, resolution, _chB);

  // reset
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);

  ledcWrite(_ENA, 0);
  ledcWrite(_ENB, 0);
}

// ===== RIGHT =====
void RMUTP_CARBOT::R_Forward(int speed) {
  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);
}

void RMUTP_CARBOT::R_Reverse(int speed) {
  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
}

void RMUTP_CARBOT::R_Stop() {
  ledcWrite(_ENB, 0);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);
}

// ===== LEFT =====
void RMUTP_CARBOT::L_Forward(int speed) {
  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
}

void RMUTP_CARBOT::L_Reverse(int speed) {
  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
}

void RMUTP_CARBOT::L_Stop() {
  ledcWrite(_ENA, 0);
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
}

// ===== MOVE =====
void RMUTP_CARBOT::Stop() {
  L_Stop();
  R_Stop();
}

void RMUTP_CARBOT::Forward(int speed) {
  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);

  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);
}

void RMUTP_CARBOT::Reverse(int speed) {
  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);

  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
}

// ===== TURN =====
void RMUTP_CARBOT::TurnRight1(int speed) {
  R_Stop();
  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);

 }

void RMUTP_CARBOT::TurnLeft1(int speed) {

 L_Stop();
  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);

}



// =======================================
// การเลี้ยวแบบ “หมุนอยู่กับที่” (Spin Turn)
// =======================================
//
// หลักการ:
// ทำให้ล้อซ้าย และ ล้อขวา หมุน “สวนทางกัน”
// → ไม่เกิดการวิ่งไปข้างหน้า/ถอยหลัง
// → แต่จะเกิด “แรงบิด (Torque)” ทำให้รถหมุนรอบตัวเอง
//
// ---------------------------------------
// 🔄 เลี้ยวขวาอยู่กับที่ (TurnRight2)
// ---------------------------------------
// ล้อซ้าย  : เดินหน้า
// ล้อขวา  : ถอยหลัง
//
// IN1 = LOW   → ซ้ายเดินหน้า
// IN2 = HIGH
//
// IN3 = HIGH  → ขวาถอยหลัง
// IN4 = LOW
//
// ผลลัพธ์:
// รถจะหมุนไปทางขวา (หมุนตามเข็มนาฬิกา)
//
// ---------------------------------------
// 🔄 เลี้ยวซ้ายอยู่กับที่ (TurnLeft2)
// ---------------------------------------
// ล้อซ้าย  : ถอยหลัง
// ล้อขวา  : เดินหน้า
//
// IN1 = HIGH → ซ้ายถอยหลัง
// IN2 = LOW
//
// IN3 = LOW  → ขวาเดินหน้า
// IN4 = HIGH
//
// ผลลัพธ์:
// รถจะหมุนไปทางซ้าย (หมุนทวนเข็มนาฬิกา)
//
// ---------------------------------------
// 💡 สรุปสั้น:
// หมุนขวา = ซ้ายหน้า + ขวาหลัง
// หมุนซ้าย = ซ้ายหลัง + ขวาหน้า
//
// ---------------------------------------
// ⚠️ หมายเหตุ:
// ถ้าทิศหมุนกลับกัน
// → ให้สลับสายมอเตอร์ หรือสลับ HIGH/LOW
// =======================================


void RMUTP_CARBOT::TurnRight2(int speed) {
  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);

  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
}

void RMUTP_CARBOT::TurnLeft2(int speed) {


  ledcWrite(_ENB, PWM(speed));
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);

  ledcWrite(_ENA, PWM(speed));
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
}