#include <Arduino.h>
#include <WiFi.h>

#include <SPI.h>
#include <SD.h>
SPIClass SDSPI(VSPI);



File myFile;
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  SDSPI.begin(18, 19, 23); // SDSPI.begin(SCLK, MISO, MOSI);
  SDSPI.setFrequency(1000000);
  
  Serial.print("Initializing SD card...");
 
  if (!SD.begin(5, SDSPI)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
 
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
 
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop() {
  // nothing happens after setup
}
