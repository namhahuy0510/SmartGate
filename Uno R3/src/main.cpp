#include <Arduino.h>
#include <SoftwareSerial.h>

int IN3 = 13;
int IN4 = 12;
int ENB = 11;

// RX = D10, TX = D9 (TX không dùng, chỉ RX)
SoftwareSerial espSerial(10, 9);

void setup() {
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(115200);     // Monitor trên PC
  espSerial.begin(115200);  // Nhận lệnh từ ESP32-CAM

  Serial.println("UNO ready: nhận lệnh OPEN/CLOSE từ ESP32-CAM");
}

void loop() {
  if (espSerial.available()) {
    String cmd = espSerial.readStringUntil('\n');
    cmd.trim();

    int targetSpeed = random(80, 151);
    int runTime     = random(200, 901);
    int stopTime    = random(100, 201);
    int stepDelay   = random(10, 41);

    if (cmd == "OPEN") {
      Serial.println("Lệnh OPEN");
      // quay thuận
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, targetSpeed);
      delay(runTime);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 255);
      delay(stopTime);

    } else if (cmd == "CLOSE") {
      Serial.println("Lệnh CLOSE");
      // quay ngược
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, targetSpeed);
      delay(runTime);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 255);
      delay(stopTime);
    }
  }
}
