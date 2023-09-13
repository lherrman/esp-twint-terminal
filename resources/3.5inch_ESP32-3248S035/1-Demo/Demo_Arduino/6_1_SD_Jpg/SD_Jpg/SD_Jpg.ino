// Example for library:
// https://github.com/Bodmer/TJpg_Decoder

// This example if for an ESP8266 or ESP32, it renders a Jpeg file
// that is stored in a SD card file. The test image is in the sketch
// "data" folder (press Ctrl+K to see it). You must save the image
// to the SD card using you PC.



// Include SD
#define FS_NO_GLOBALS
#include <FS.h>
#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif

#define SD_CS   5

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"




/
void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n Testing TJpg_Decoder library");

  // Initialise SD before TFT
  if (!SD.begin(SD_CS)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(0);
  }
  Serial.println("\r\nInitialisation done.");


}

void loop()
{
  // tft.fillScreen(TFT_RED);
  // delay(2000);

  // // Time recorded for test purposes
  // uint32_t t = millis();

  // // Get the width and height in pixels of the jpeg if you wish
  // uint16_t w = 0, h = 0;
  // TJpgDec.getSdJpgSize(&w, &h, "/panda.jpg");
  // Serial.print("Width = "); Serial.print(w); Serial.print(", height = "); Serial.println(h);

  // // Draw the image, top left at 0,0
  // TJpgDec.drawSdJpg(0, 0, "/panda.jpg");

  // // How much time did rendering take
  // t = millis() - t;
  // Serial.print(t); Serial.println(" ms");

  // // Wait before drawing again
  // delay(2000);
}
