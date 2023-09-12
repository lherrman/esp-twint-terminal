#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <TM1637.h>

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
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String msg = "";

TM1637 disp(19, 18);

void sendValue(float valueOut)
{
    Wire.beginTransmission(address);
    Wire.write((uint8_t *)&valueOut, sizeof(valueOut));

    Wire.endTransmission();
}
enum class State
{
    IDLE_SHOW_DEFAULT,
    ENTERING_VALUE,
    SHOWING_VALUE,
};

class Controller {
    public:
        void keyPressed(char key){
            disp.clearScreen();
            disp.display("    ");
        
            if (state == State::IDLE_SHOW_DEFAULT)
            {
                if (key == '*')
                {
                }
                else if (key == '#')
                {
                }
                else
                {
                    input_buffer = key;
                    state = State::ENTERING_VALUE;
                }
            }
            else if (state == State::ENTERING_VALUE)
            {
                if (key == '*')
                {
                    // remove last character from input_buffer if it exists
                    if (input_buffer.length() > 1)
                    {
                        input_buffer.remove(input_buffer.length() - 1);
                    }
                    else if (input_buffer.length() == 1)
                    {
                        state = State::IDLE_SHOW_DEFAULT;
                        input_buffer = "";
                    }
                }
                else if (key == '#')
                {
                    value = input_buffer.toFloat();
                    input_buffer = "";
                    state = State::SHOWING_VALUE;
                }
                else if (input_buffer.length() < 3)
                {
                    input_buffer += key;
                    
                }
                
            }
            else if (state == State::SHOWING_VALUE)
            {
                if (key == '*')
                {
                    state = State::IDLE_SHOW_DEFAULT;
                }
                else if (key == '#')
                {
                }
                else
                {
                    state = State::ENTERING_VALUE;
                    input_buffer = key;
                }
            }

        }

        void run()
        {
            if (state == State::IDLE_SHOW_DEFAULT)
            {
                value = 0;
                disp.setBrightness(1);
                idle_animation();
            }
            else if (state == State::ENTERING_VALUE)
            {
                disp.setBrightness(5);
                int offset = 4 - input_buffer.length();
                disp.display(input_buffer, true, false, offset);
            }
            else if (state == State::SHOWING_VALUE)
            {
                disp.setBrightness(5);
                int val = (int)value;
                disp.display(val);
            }
            send_cyclic();
        }

        void send_cyclic()
        {
            unsigned long current_time = millis();
            static unsigned long last_time = 0;
            if (current_time - last_time > 500)
            {
                sendValue(value);
                last_time = current_time;
            }
        }

        void idle_animation()
        {
            disp.display("----");
        }

    private:
        State state;
        String input_buffer;
        float value;
};

Controller controller;

void setup()
{
    Wire.begin(21, 22); // SDA, SCL
    Serial.begin(115200);

    disp.init();
    disp.setBrightness(5);

    controller = Controller();
}

void loop()
{
    
        // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged && kpd.key[i].kstate == PRESSED)
            {
                char key = kpd.key[i].kchar;
                controller.keyPressed(key);
            }
                  
        }
    }
    controller.run();


}