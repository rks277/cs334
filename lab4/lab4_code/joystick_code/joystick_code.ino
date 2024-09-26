int JoyStick_X = 0; // Analog Pin  X
int JoyStick_Y = 4; // // Analog Pin  Y
int JoyStick_button = 2; // IO Pin

const int buttonPin = 14;
const int switchPin = 13;
int buttonState = 0;
int switchState = 0;


void setup()
{
    // Joystick
    pinMode(JoyStick_X, INPUT);
    pinMode(JoyStick_Y, INPUT);
    pinMode(JoyStick_button, INPUT_PULLUP);

    // Button
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(switchPin, INPUT_PULLUP);


    Serial.begin(9600);
}
void loop()
{
    int x, y, button;
    x = analogRead(JoyStick_X); //  X
    y = analogRead(JoyStick_Y); //  Y
    button = digitalRead(JoyStick_button); // 
    //x = map(x, 0, 4095, -512, 512);
    //y = map(y, 0, 4095, 512, -512);
    
    Serial.print("X : ");
    Serial.print(x, DEC);
    Serial.print(" / Y : ");
    Serial.print(y, DEC);
    Serial.print(" , B : ");
    Serial.println(button, DEC);

    buttonState = digitalRead(buttonPin);
    switchState = digitalRead(switchState);

    Serial.print(buttonState);
    Serial.print(switchState);


    delay(100);
}