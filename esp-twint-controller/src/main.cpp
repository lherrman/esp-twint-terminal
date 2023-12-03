#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <TM1637.h>
#include <EEPROM.h>


float value = -1;
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

void send_package(float valueOut, int setting_2_show_default = 1, int setting_3_dark_mode = 0)
{
    Wire.beginTransmission(address);

    // create a package to send to the receiver with the value and a setting
    uint8_t package[6];
    package[4] = (uint8_t)(setting_2_show_default); // setting
    package[5] = (uint8_t)(setting_3_dark_mode); // setting ! TODO only 1 byte is being sent, need to fix this
    memcpy(&package[0], &valueOut, sizeof(valueOut));
    Wire.write(package, sizeof(package));
    //Wire.write((uint8_t *)&valueOut, sizeof(valueOut));

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
        Controller()
        {
            load_settings_from_eeprom();
        }

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

                int MAX_SETTINGS_MENU_INDEX = 3;
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
                else if ((key == '5') || (key == '#'))
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
                else if ((key == '5') || (key == '#'))
                {
                    // SELECT

                    // Save settings
                    if (settings_menu_index == 0)
                    {
                        setting_0_time_auto_reset_index = settings_selctor_index;
                    }
                    else if (settings_menu_index == 1)
                    {
                        setting_1_brightness = settings_selctor_index;
                    }
                    else if (settings_menu_index == 2)
                    {
                        setting_2_show_default = settings_selctor_index;
                    }
                    else if (settings_menu_index == 3)
                    {
                        setting_3_dark_mode = settings_selctor_index;
                    }
                    save_settings_to_eeprom();

                    state = State::SETTINGS_MENU;
                }
                else if (key == '2')
                {
                    // UP
                    settings_selctor_index += setting_menu_direction[settings_menu_index];
                }
                else if (key == '8')
                {
                    // DOWN
                    settings_selctor_index -= setting_menu_direction[settings_menu_index];
                }
            }

        }



        void run()
        {
            current_time = millis();

            if (state == State::IDLE_SHOW_DEFAULT)
            {
                value = -1;
                disp.setBrightness(3);
                idle_animation();
            }
            else if (state == State::ENTERING_VALUE)
            {
                disp.setBrightness(setting_1_brightness);
                int offset = 4 - input_buffer.length();
                disp.display(input_buffer, true, false, offset);
            }
            else if (state == State::SHOWING_VALUE)
            {

                // Reset to idle if set time has passed
                if ((current_time - last_time_value_set > setting_0_values[setting_0_time_auto_reset_index] * 1000)
                    && (setting_0_values[setting_0_time_auto_reset_index] != 0))
                {   
                    state = State::IDLE_SHOW_DEFAULT;
                }

                disp.setBrightness(setting_1_brightness);
                int val = (int)value;
                disp.display(val);
            }
            else if (state == State::SETTINGS_MENU)
            {
                disp.setBrightness(setting_1_brightness);
   
                switch (settings_menu_index)
                {
                case 0:
                    // Auto reset time
                    disp.display("0 Ar");
                    break;
                case 1: 
                    // Brightness
                    disp.display("1 Br");
                    break;
                case 2:
                    // show default qr code
                    disp.display("2 Sd"); 
                    break;
                case 3:
                    // dark mode
                    disp.display("3 da");
                    break;
                }
            }

            else if (state == State::INSIDE_SETTING)
            {
                disp.setBrightness(setting_1_brightness);
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
                        settings_selctor_index = setting_0_time_auto_reset_index;
                    }

                    // Clamp selector index
                    clamp_settings_selctor_index(0, 4);    

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
                case 1: {
                    // Brightness

                    // On Entry
                    if (last_state != State::INSIDE_SETTING)
                    {
                        settings_selctor_index = setting_1_brightness;
                    }

                    clamp_settings_selctor_index(1, 7);    

                    disp.setBrightness(settings_selctor_index);
                    String brightness_str = String("Br " + String(settings_selctor_index));
                    disp.display(brightness_str);
                    break;
                }
                case 2:{
                    // Show default qr code

                    // On Entry
                    if (last_state != State::INSIDE_SETTING)
                    {
                        settings_selctor_index = setting_2_show_default;
                    }
                    
                    clamp_settings_selctor_index(0, 1);    

                    // Show options
                    if (settings_selctor_index == 0)
                    {
                        disp.display(" Off");
                    }
                    else if (settings_selctor_index == 1)
                    {
                        disp.display(" On ");
                    }
                    break;
                }
                case 3:{
                    // Show dark mode

                    // On Entry
                    if (last_state != State::INSIDE_SETTING)
                    {
                        settings_selctor_index = setting_3_dark_mode;
                    }
                    
                    clamp_settings_selctor_index(0, 1);    

                    // Show options
                    if (settings_selctor_index == 0)
                    {
                        disp.display(" Off");
                    }
                    else if (settings_selctor_index == 1)
                    {
                        disp.display(" On ");
                    }
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
                send_package(value, setting_2_show_default, setting_3_dark_mode);
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

        // Settings menu
        int settings_menu_index = 0;
        int settings_selctor_index = 0;
        int setting_menu_direction[4] = {-1, 1, 1, 1}; // 1 = up, -1 = down

        // Settings
        int setting_0_time_auto_reset_index = 1; 
        int setting_0_values[5] = {30, 60, 120, 300, 0}; // seconds (0 = never)
        int setting_1_brightness = 5; // 1-7
        int setting_2_show_default = 0; // 1= show default qr code, 0=don't show default qr code
        int setting_3_dark_mode = 0; // 1= dark mode, 0=light mode

        void write_int_to_eeprom(int address, int value)
        {
            // Split the integer into 4 bytes
            byte four = (value & 0xFF);
            byte three = ((value >> 8) & 0xFF);
            byte two = ((value >> 16) & 0xFF);
            byte one = ((value >> 24) & 0xFF);

            // Write each byte to EEPROM
            EEPROM.write(address, one);
            EEPROM.write(address + 1, two);
            EEPROM.write(address + 2, three);
            EEPROM.write(address + 3, four);
        }
        
        int read_int_from_eeprom(int address)
        {
            // Read each byte from EEPROM
            byte one = EEPROM.read(address);
            byte two = EEPROM.read(address + 1);
            byte three = EEPROM.read(address + 2);
            byte four = EEPROM.read(address + 3);

            // Combine the 4 bytes back into an integer
            return ((one << 24) + (two << 16) + (three << 8) + four);
        }
        void save_settings_to_eeprom()
        {
            
            write_int_to_eeprom(0, setting_0_time_auto_reset_index);
            write_int_to_eeprom(4, setting_1_brightness);
            write_int_to_eeprom(8, setting_2_show_default);
            write_int_to_eeprom(12, setting_3_dark_mode);
            EEPROM.commit();
        }

        void load_settings_from_eeprom()
        {
            setting_0_time_auto_reset_index = read_int_from_eeprom(0);
            setting_1_brightness = read_int_from_eeprom(4); 
            setting_2_show_default = read_int_from_eeprom(8);
            setting_3_dark_mode = read_int_from_eeprom(12);
        }

        void setValue(String valueStrIn)
        {
            last_time_value_set = millis();
            value = valueStrIn.toFloat();
        }

        void clamp_settings_selctor_index(int min, int max)
        {
            if (settings_selctor_index > max)
            {
                settings_selctor_index = max;
            }
            else if (settings_selctor_index < min)
            {
                settings_selctor_index = min;
            }
        }

};

Controller controller;

void setup()
{
    Wire.begin(21, 22); // SDA, SCL
    Serial.begin(115200);

    disp.init();
    disp.setBrightness(5);

    EEPROM.begin(512);
    
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