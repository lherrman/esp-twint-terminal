#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin(21, 22); // SDA, SCL
  Serial.begin(115200);

}

float value = 9;

void loop() {
  uint8_t address = 8; // address of the receiver ESP32
  Wire.beginTransmission(address);
  Wire.write((uint8_t*)&value, sizeof(value));
  Wire.endTransmission();
  delay(500); 

  if (value == 9) {
    value = 16;
  } else {
    value = 9;
  }
}
