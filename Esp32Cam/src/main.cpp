#include <Arduino.h>

void setup() {
  Serial.begin(115200); // dùng 115200 cho ESP32-CAM
  delay(1000);
  Serial.println("ESP32-CAM UART TX demo: gửi OPEN/CLOSE mỗi 2s");
}

void loop() {
  Serial.println("OPEN");
  delay(2000);

  Serial.println("CLOSE");
  delay(2000);
}
