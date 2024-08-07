#include "Motor.h"
#include "BUZZER.h"
#include "LCD.h"
#include <Arduino.h>

#define MR_IN1 12 //motor1
#define MR_IN2 13 //motor1
#define MR_IN3 32 //motor2
#define MR_IN4 33 //motor2

#define ML_IN1 27 //motor4
#define ML_IN2 14 //motor4
#define ML_IN3 25 //motor3
#define ML_IN4 26 //motor3

#define R_ENA 15  //Adjust speed  //motor1
#define R_ENB 2   //Adjust speed //motor2
#define L_ENA 19  //Adjust speed //motor4
#define L_ENB 4   //Adjust speed //motor3

BUZZER buzzer_b;
LCD lcd_m;

int LA_V;
int LB_V;
int RA_V;
int RB_V;

void Motor::motorInit() {
  pinMode(MR_IN1, OUTPUT);
  pinMode(MR_IN2, OUTPUT);
  pinMode(MR_IN3, OUTPUT);
  pinMode(MR_IN4, OUTPUT);
  pinMode(ML_IN1, OUTPUT);
  pinMode(ML_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT);
  pinMode(ML_IN4, OUTPUT);
  pinMode(L_ENA, OUTPUT);
  pinMode(L_ENB, OUTPUT);
  pinMode(R_ENA, OUTPUT);
  pinMode(R_ENB, OUTPUT);
  stop();
}

void Motor::adjectMotorSpeed(int LA, int LB, int RA, int RB) {
  LA_V = LA;
  LB_V = LB;
  RA_V = RA;
  RB_V = RB;
}

void Motor::forward() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_L, HIGH);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void Motor::backward() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void Motor::slide_left() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void Motor::slide_right() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void Motor::slide_left_front() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void Motor::slide_right_front() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

void Motor::slide_left_back() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

void Motor::slide_right_back() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void Motor::turn_left() {
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_R, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void Motor::turn_right() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_L, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void Motor::stop() {
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_L, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

void Motor::OnBuzzer()
{
  buzzer_b.Beep(1);
  lcd_m.LcdDisplay();

}

void Motor::OffBuzzer()
{
  buzzer_b.Beep(0);
}