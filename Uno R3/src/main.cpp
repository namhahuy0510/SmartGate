// Motor L298N điều khiển bằng Uno R3
// Motor nối OUT3, OUT4
// IN3 = D13, IN4 = D12, ENB = D11 (PWM)

#include <Arduino.h>

int IN3 = 13;
int IN4 = 12;
int ENB = 11;

int targetSpeed = 100;   // tốc độ tối đa (0-255)
int runTime   = 300;    // thời gian giữ tốc độ (ms)
int stopTime  = 1000;    // thời gian brake (ms)
int stepDelay = 30;      // độ mượt ramp (ms)

void rampUp(int pinA, int pinB) {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  for (int s = 0; s <= targetSpeed; s += 5) {
    analogWrite(ENB, s);
    delay(stepDelay);
  }
}

void rampDown() {
  for (int s = targetSpeed; s >= 0; s -= 5) {
    analogWrite(ENB, s);
    delay(stepDelay);
  }
  // Brake mạnh
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);
}

void setup() {
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  Serial.println("Motor giả lập đóng/mở cửa với ramp up/down");
}

void loop() {
  // Quay thuận (mở cửa)
  Serial.println("Motor quay thuan (Mo cua)");
  rampUp(IN3, IN4);
  delay(runTime);
  Serial.println("Ramp down + Brake");
  rampDown();
  delay(stopTime);

  // Quay ngược (đóng cửa)
  Serial.println("Motor quay nguoc (Dong cua)");
  rampUp(IN4, IN3);
  delay(runTime);
  Serial.println("Ramp down + Brake");
  rampDown();
  delay(stopTime);
}
