#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>

float value = 9;
uint8_t address = 8; // address of the receiver ESP32


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {2, 5, 17, 4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {0, 15, 16}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String msg;

void setup() {
  Wire.begin(21, 22); // SDA, SCL
  Serial.begin(115200);

  msg = "";
}

void sendValue(float valueOut) {
  Wire.beginTransmission(address);
  Wire.write((uint8_t*)&valueOut, sizeof(valueOut));
  Wire.endTransmission();
}



void loop() {

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg += kpd.key[i].kchar;
                // break;
                //     case HOLD:
                //     msg = " HOLD.";
                // break;
                //     case RELEASED:
                //     msg = " RELEASED.";
                // break;
                //     case IDLE:
                //     msg = " IDLE.";
                }
                //Serial.print("Key ");
                //Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
            }
        }
    }
}  // End loop