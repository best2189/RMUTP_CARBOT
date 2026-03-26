#ifndef RMUTP_CARBOT_h
#define RMUTP_CARBOT_h

#include <Arduino.h>

#ifndef ESP32
#error "RMUTP_CARBOT library works only with ESP32 by Supong68"
#endif

class RMUTP_CARBOT {
  public:
    RMUTP_CARBOT(int ENA, int IN1, int IN2, int ENB, int IN3, int IN4);

    void begin(int freq = 1000, int resolution = 8, int chA = 0, int chB = 1);

    // Control
    void R_Forward(int speed);
    void R_Reverse(int speed);
    void R_Stop();

    void L_Forward(int speed);
    void L_Reverse(int speed);
    void L_Stop();

    void Stop();
    void Forward(int speed);
    void Reverse(int speed);

    void TurnRight1(int speed);
    void TurnLeft1(int speed);

    void TurnRight2(int speed);
    void TurnLeft2(int speed);

  private:
    int _ENA, _IN1, _IN2;
    int _ENB, _IN3, _IN4;

    int _chA, _chB;
    int _maxDuty;   // ⭐ รองรับหลาย resolution
};


#endif