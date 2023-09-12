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

unsigned long last_time_value_set = 0;
unsigned long current_time;

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
    SETTINGS_MENU,
    INSIDE_SETTING,
};

class Controller {
    public:
        void keyLongPressed(char key)
        {
            if (key == '*')
            {
                if (state == State::IDLE_SHOW_DEFAULT)
                {
                    settings_menu_index = 0;
                    settings_selctor_index = 0;
                    state = State::SETTINGS_MENU;
                }
                else if (state == State::SETTINGS_MENU)
                {
                    state = State::IDLE_SHOW_DEFAULT;
                }
            }
        }

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
                    setValue(input_buffer);
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
            else if (state == State::SETTINGS_MENU)
            {

                int MAX_SETTINGS_MENU_INDEX = 1;
                if (key ==  '2')
                {
                    // UP
                    if (settings_menu_index > 0)
                    {
                        settings_menu_index--;
                    }
                }
                else if (key == '8')
                {
                    // DOWN
                    if (settings_menu_index < MAX_SETTINGS_MENU_INDEX)
                    {
                        settings_menu_index++;
                    }
                }
                else if ((key == '*') || (key == '4'))
                {
                    // BACK
                    state = State::IDLE_SHOW_DEFAULT;
                }
                else if (key == '#')
                {
                    // SELECT
                }
                else if (key == '5')
                {
                    // ENTER
                    state = State::INSIDE_SETTING;
                }
            }
            else if (state == State::INSIDE_SETTING)
            {
                if ((key == '*') || (key == '4'))
                {
                    // BACK
                    settings_selctor_index = 0;
                    state = State::SETTINGS_MENU;
                }
                else if (key == '5')
                {
                    // SELECT

                    // Save settings
                    if (settings_menu_index == 0)
                    {
                        setting_0_TimeAutoReset_index = settings_selctor_index;
                    }
                    else if (settings_menu_index == 1)
                    {
                        setting_1_Animation = settings_selctor_index;
                    }

                    state = State::SETTINGS_MENU;
                }
                else if (key == '2')
                {
                    // UP
                if (settings_selctor_index > 0)
                {
                    settings_selctor_index--;
                }
                }
                else if (key == '8')
                {
                    // DOWN
                    settings_selctor_index++;
                }
            }

        }



        void run()
        {
            current_time = millis();

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

                // Reset to idle if set time has passed
                if (current_time - last_time_value_set > setting_0_values[setting_0_TimeAutoReset_index] * 1000)
                {   
                    state = State::IDLE_SHOW_DEFAULT;
                }

                disp.setBrightness(5);
                int val = (int)value;
                disp.display(val);
            }
            else if (state == State::SETTINGS_MENU)
            {
                disp.setBrightness(5);
   
                switch (settings_menu_index)
                {
                case 0:
                    // Idle animation
                    disp.display("0 RS");
                    break;
                case 1:
                    // Time auto reset
                    disp.display("1 An");
                    break;
                case 2: 
                    disp.display("2 Of");
                    break;
                }
            }

            else if (state == State::INSIDE_SETTING)
            {
                disp.setBrightness(5);
                settings_menu_logic();
            }

            last_state = state;
            send_cyclic();
        }


        void settings_menu_logic()
        {
            int max_index = 1;
            switch (settings_menu_index)
                {
                case 0: {
                    // Time auto reset

                    // On Entry
                    if (last_state != State::INSIDE_SETTING)
                    {
                        settings_selctor_index = setting_0_TimeAutoReset_index;
                    }

                    // Clamp selector index
                    max_index = 4;
                    if (settings_selctor_index > max_index)
                    {
                        settings_selctor_index = max_index;
                    }



                    // Show options
                    int setting_value = setting_0_values[settings_selctor_index];
                    String setting_value_str = String(setting_value);
                    if (setting_value == 0)
                    {
                        setting_value_str = "Off";
                    }
                    else
                    {
                        if (setting_value_str.length() == 2)
                        {
                            setting_value_str =  setting_value_str + " s";
                        }
                        else if (setting_value_str.length() == 3)
                        {
                            setting_value_str = setting_value_str + "s";
                        }
                    }
                    disp.display(setting_value_str);

                    break;
                }
                case 1:{
                    // Idle animation

                    // Clamp selector index
                    max_index = 1;
                    if (settings_selctor_index > max_index)
                    {
                        settings_selctor_index = max_index;
                    }                    

                    // Show options
                    if (settings_selctor_index == 0)
                    {
                        disp.display("An 1");
                    }
                    else if (settings_selctor_index == 1)
                    {
                        disp.display("An 2");
                    }

                    break;
                }
                case 2: {
                    
                    break;
                }
            }
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


        // State Variables
        State state;
        State last_state;
        String input_buffer;
        float value;
        int settings_menu_index = 0;
        int settings_selctor_index = 0;

        // Settings
        int setting_0_TimeAutoReset_index = 1; 
        int setting_0_values[5] = {30, 60, 120, 300, 0}; // seconds (0 = never)
        int setting_1_Animation = 0; // 0 = none, 1 = animation 1, 2 = animation 2

        void setValue(String valueStrIn)
        {
            last_time_value_set = millis();
            value = valueStrIn.toFloat();
        }

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
            else if ( kpd.key[i].stateChanged && kpd.key[i].kstate == HOLD)
            {
                char key = kpd.key[i].kchar;
                controller.keyLongPressed(key);
            }
                  
        }
    }
    controller.run();


}