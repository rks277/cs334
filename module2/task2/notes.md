Need to plug the 5v joystick pin into the 3V3 pin on the esp32

Backups: 
// // Player 1 Joystick (controls x and y)
// int JoyStick1_X = 0;         // Analog Pin for Joystick 1 X-axis (Player 1)
// int JoyStick1_Y = 4;         // Analog Pin for Joystick 1 Y-axis (Player 1)

// const int p1SwitchPin = 21;   // Pin connected to the switch
// int p1SwitchState = 0; 

// const int p2SwitchPin = 5;   // Pin connected to the switch
// int p2SwitchState = 0; 
// bool off = true;
// bool ended = false;

// const int p1ButtonPin = 17;   // Pin connected to the switch
// int p1ButtonState = 0; 

// // Player 2 Joystick (controls z - depth)
// int JoyStick2_Y = 2;         // Analog Pin for Joystick 2 Y-axis (Player 2)

// // LEDs
// // Structure to manage the state of each LED
// struct blinkLedState {
//   int ledPin;
//   unsigned long previousMillis;
//   int blinkInterval;
//   bool ledState;
// };

// const int treasureLedPin = 13;
// blinkLedState radarBlinkLed = {14, 0, 300, false};  // LED on pin 12 with 300ms blink interval

// // Define the pins for the 3x2 LED array
// const int greenLED0 = 26;  // Green LED for depth 0 (treasure)
// const int greenLED1 = 27;  // Green LED for depth 1 (treasure)
// const int greenLED2 = 25;  // Green LED for depth 2 (treasure)

// const int redLED0 = 12;  // Red LED for depth 0 (submarine)
// const int redLED1 = 33;  // Red LED for depth 1 (submarine)
// const int redLED2 = 32;  // Red LED for depth 2 (submarine)

// //////////////////////////////////////////////////////////////////////////////////////////
// // Global variables for game
// //////////////////////////////////////////////////////////////////////////////////////////
// // Submarine position and depth variables
// int x = 0;  // X coordinate controlled by Player 1
// int vX = 0; // Sub velocity in x direction
// int vY = 0; // Sub velocity in y direction
// int vZ = 0;
// int y = 0;  // Y coordinate controlled by Player 1
// int z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

// // Treasure coords
// int tX = 0;
// int tY = 0;
// int tZ = 0;

// int game_tX = 0;
// int game_tY = 0;
// int game_tZ = 0;


// // Joystick Threshold
// const int joystickThreshold = 100;
// int previousZ = 0;  // Stores the previous Z value for depth comparison

// void setup() {
//     initGame();
//     pinMode(p1ButtonPin, INPUT_PULLUP);
//     pinMode(p2SwitchPin, INPUT_PULLUP);
//     pinMode(p1SwitchPin, INPUT_PULLUP);

//     // Setup for Player 1 Joystick
//     pinMode(JoyStick1_X, INPUT);
//     pinMode(JoyStick1_Y, INPUT);
//     // pinMode(JoyStick1_button, INPUT_PULLUP);

//     // Setup for Player 2 Joystick
//     // pinMode(JoyStick2_Y, INPUT);
//     // pinMode(JoyStick2_button, INPUT_PULLUP);

//     // Setup treasure led
//     pinMode(treasureLedPin, OUTPUT);
//     pinMode(radarBlinkLed.ledPin, OUTPUT);

//     // Initialize all LED pins as OUTPUT (this is for player 2's depth controler)
//     pinMode(greenLED0, OUTPUT);
//     pinMode(greenLED1, OUTPUT);
//     pinMode(greenLED2, OUTPUT);

//     pinMode(redLED0, OUTPUT);
//     pinMode(redLED1, OUTPUT);
//     pinMode(redLED2, OUTPUT);
//     digitalWrite(treasureLedPin, LOW);

//     // Start Serial communication for debugging or display
//     Serial.begin(9600);

//     // Initial message
//     Serial.println("Submarine Game!!!");
// }

// void loop() {
//     // Read the state of the switch
//     p2SwitchState = digitalRead(p2SwitchPin);
//     p1SwitchState = digitalRead(p1SwitchPin);

//     // Since we're using a pull-up, LOW means the switch is pressed
//     if (p2SwitchState == LOW && ended == false) {
//       if (off) {
//         defaultGame();
//       }
//       off = false;

//       // if (p1SwitchState == LOW) {
//       //   tX = game_tX;
//       //   tY = game_tY;
//       //   tZ = game_tZ;
//       // }

//       updateXY();
//       displayVelocity();
//       handleSubAtTreasure();
//       player2RadarBlink();
//       updateZLEDs();
//       grabTreasure();

//       // Check if the depth (z) has changed
//       if (z != previousZ) {
//           displayDepth(z);  // Update the depth display
//           previousZ = z;    // Store the new Z value
//       }

//       // Print the current coordinates and depth of the submarine
//       displayPosition(x, y, z);

//       // Delay for smoother updates
//       delay(200);
//     } else if (!off) {
//       initGame();
//       Serial.print("\n %%%%%%%%%%%%%%%%%%%%%%%%% \n Powering Off! \n  %%%%%%%%%%%%%%%%%%%%%%%%%");
//       resetZLEDs();
//       digitalWrite(treasureLedPin, LOW);
//       digitalWrite(14, LOW);
//       off = true;
//     } else if (ended && p2SwitchState == HIGH) {
//       ended = false;
//     } else if (ended) {
//       initGame();
//       resetZLEDs();
//       digitalWrite(treasureLedPin, LOW);
//       digitalWrite(14, LOW);
//       off = true;
//     } 
// }

// //////////////////////////////////////////////////////////////////////////////////////////
// // Game event utilities
// //////////////////////////////////////////////////////////////////////////////////////////
// void defaultGame() {
//     Serial.print("\nSTARTING GAME IN TUTORIAL MODE\n");
//     // Submarine position and depth variables
//     x = 0;  // X coordinate controlled by Player 1
//     vX = 0; // Sub velocity in x direction
//     vY = 0; // Sub velocity in y direction
//     vZ = 0;
//     y = 0;  // Y coordinate controlled by Player 1
//     z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

//     // Treasure coords
//     tX = 0;
//     tY = 0;
//     tZ = 0;
// }

// void initGame() {
//     // Submarine position and depth variables
//     x = 0;  // X coordinate controlled by Player 1
//     vX = 0; // Sub velocity in x direction
//     vY = 0; // Sub velocity in y direction
//     vZ = 0;
//     y = 0;  // Y coordinate controlled by Player 1
//     z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

//     // Treasure coords
//     game_tX = int(random(-10, 10));
//     game_tY = int(random(-10, 10));
//     game_tZ = int(random(0, 4));
// }

// void handleSubAtTreasure() {
//   if (atTreasureCheck()) {
//     // Turn on the LED
//     digitalWrite(treasureLedPin, HIGH);
//   } else {
//     digitalWrite(treasureLedPin, LOW);
//   }
// }

// bool atTreasureCheck() {
//   if (x == tX && y == tY && z == tZ) {
//     return true;
//   }
//   return false;
// }

// void directionalizeJoystickMap() {
//   if (vX < 4095 / 3) {
//     vX = -1;
//   } else if (vX >= 4095 / 3 && vX < 2.2 * 4095 / 3) {
//     vX = 0;
//   } else {
//     vX = 1;
//   }
//   if (vY < 4095 / 3) {
//     vY = 1;
//   } else if (vY >= 4095 / 3 && vY < 2* 4095 / 3) {
//     vY = 0;
//   } else {
//     vY = -1;
//   }
//   if (vZ < 4095 / 3) {
//     vZ = -1;
//   } else if (vZ >= 4095 / 3 && vZ < 2* 4095 / 3) {
//     vZ = 0;
//   } else {
//     vZ = 1;
//   }
// }

// void grabTreasure() {
//   // Read the state of Player 1 button
//   p1ButtonState = digitalRead(p1ButtonPin);
//   // Check if the button is pressed (since we're using pull-up, LOW means pressed)
//   if (p1ButtonState == LOW) {
//     Serial.print("\n ############################# \n Submarine robot arm deployed \n Trying to grab treasure... \n #############################\n ");
//     delay(500);
//     if (atTreasureCheck()) {
//       Serial.print("Success!!! You have won the game, treasure is being collected :)\n");
//       ended = true;
//     } else {
//       Serial.print("Failure!!! Could not find treasure, robot arm lost in the deep ocean... Submarine exploded:(\n");
//       ended = true;
//     }
//     Serial.print("\n The game has now ended.\n");
//   }
// }

// float computeDistToTreasure() {
//     float sqX = sq(x - tX);
//     float sqY = sq(y - tY);
//     float sum = sqX + sqY;
//     return sqrt(sum);
// }

// void player2RadarBlink() {
//     int rate = int(computeDistToTreasure() / 10);  // Scale the rate
//     int blinkInterval = map(computeDistToTreasure(), 0, 100, 1, 10000);
//     radarBlinkLed.blinkInterval = blinkInterval;  // Minimum blink interval of 100ms
//     blinkLED(radarBlinkLed);
// }

// //////////////////////////////////////////////////////////////////////////////////////////
// // Hardware utilities
// //////////////////////////////////////////////////////////////////////////////////////////
// // Function to update the LEDs based on the current Z levels
// void updateZLEDs() {
//   // Turn off all LEDs first
//   resetZLEDs();

//   // Update Green LEDs (treasure depth)
//   switch (tZ) {
//     case 0:
//       digitalWrite(greenLED0, HIGH);
//       break;
//     case 1:
//       digitalWrite(greenLED1, HIGH);
//       break;
//     case 2:
//       digitalWrite(greenLED2, HIGH);
//       break;
//   }

//   // Update Red LEDs (submarine depth)
//   switch (z) {
//     case 0:
//       digitalWrite(redLED0, HIGH);
//       break;
//     case 1:
//       digitalWrite(redLED1, HIGH);
//       break;
//     case 2:
//       digitalWrite(redLED2, HIGH);
//       break;
//   }
// }

// // Function to reset all LEDs (turn them off)
// void resetZLEDs() {
//   // Turn off all green LEDs
//   digitalWrite(greenLED0, LOW);
//   digitalWrite(greenLED1, LOW);
//   digitalWrite(greenLED2, LOW);

//   // Turn off all red LEDs
//   digitalWrite(redLED0, LOW);
//   digitalWrite(redLED1, LOW);
//   digitalWrite(redLED2, LOW);
// }


// void updateXY() {
//   // Read Player 1's joystick for X and Y coordinates
//   vX = analogRead(JoyStick1_X);
//   vY = analogRead(JoyStick1_Y);
//   vZ = analogRead(JoyStick2_Y);
//   directionalizeJoystickMap();
//   x += vX;
//   y += vY;
//   z += vZ;
//   if (z < 0) {
//     z = 0;
//   } else if (z > 2) {
//     z = 2;
//   }
// }

// // Function to read and update z axis based on Player 2's joystick
// void readJoystickZ(int pin) {
//     int joyValue = analogRead(pin);

//     // Adjust z based on joystick Y-axis movement (up/down)
//     if (joyValue < 512 - joystickThreshold) {
//         z = max(z - 1, 0);  // Decrease z, but don't go below 0 (surface)
//     } else if (joyValue > 512 + joystickThreshold) {
//         z = min(z + 1, 2);  // Increase z, but don't exceed 2 (deep underwater)
//     }
// }

// // Non-blocking blink function
// void blinkLED(blinkLedState &led) {
//   unsigned long currentMillis = millis();  // Get current time

//   // Check if the blink interval has passed
//   if (currentMillis - led.previousMillis >= led.blinkInterval) {
//     // Save the last time the LED was toggled
//     led.previousMillis = currentMillis;

//     // Toggle the LED state
//     led.ledState = !led.ledState;
//     digitalWrite(led.ledPin, led.ledState ? HIGH : LOW);
//   }
// }

// //////////////////////////////////////////////////////////////////////////////////////////
// // Debugging stuff
// //////////////////////////////////////////////////////////////////////////////////////////

// void displayVelocity() {
//   Serial.print("Submarine V_x: ");
//   Serial.print(vX);
//   Serial.print(", V_y: ");
//   Serial.print(vY);
//   Serial.print("\n");
// }

// // Utility function to display the position of the submarine
// void displayPosition(int x, int y, int z) {
//     Serial.print("Submarine Position - X: ");
//     Serial.print(x);
//     Serial.print(", Y: ");
//     Serial.print(y);
//     Serial.print(", Depth (Z): ");
    
//     switch(z) {
//         case 0:
//             Serial.println("Surface");
//             break;
//         case 1:
//             Serial.println("Mid-Depth");
//             break;
//         case 2:
//             Serial.println("Deep Underwater");
//             break;
//     }
// }

// // Utility function to display depth changes
// void displayDepth(int z) {
//     Serial.print("Depth changed to: ");
//     switch(z) {
//         case 0:
//             Serial.println("Surface");
//             break;
//         case 1:
//             Serial.println("Mid-Depth");
//             break;
//         case 2:
//             Serial.println("Deep Underwater");
//             break;
//     }
// }

// Player 1 Joystick (controls x and y)
int JoyStick1_X = 0;         // Analog Pin for Joystick 1 X-axis (Player 1)
int JoyStick1_Y = 4;         // Analog Pin for Joystick 1 Y-axis (Player 1)

const int p1SwitchPin = 21;   // Pin connected to the switch
int p1SwitchState = 0;

const int p2SwitchPin = 5;   // Pin connected to the switch
int p2SwitchState = 0;
bool off = true;
bool ended = false;

const int p1ButtonPin = 17;   // Pin connected to the switch
int p1ButtonState = 0;

// Player 2 Joystick (controls z - depth)
int JoyStick2_Y = 2;         // Analog Pin for Joystick 2 Y-axis (Player 2)

// LEDs
// Structure to manage the state of each LED
struct blinkLedState {
  int ledPin;
  unsigned long previousMillis;
  int blinkInterval;
  bool ledState;
};

const int treasureLedPin = 13;
blinkLedState radarBlinkLed = {14, 0, 300, false};  // LED on pin 12 with 300ms blink interval

// Define the pins for the 3x2 LED array
const int greenLED0 = 26;  // Green LED for depth 0 (treasure)
const int greenLED1 = 27;  // Green LED for depth 1 (treasure)
const int greenLED2 = 25;  // Green LED for depth 2 (treasure)

const int redLED0 = 12;  // Red LED for depth 0 (submarine)
const int redLED1 = 33;  // Red LED for depth 1 (submarine)
const int redLED2 = 32;  // Red LED for depth 2 (submarine)

//////////////////////////////////////////////////////////////////////////////////////////
// Global variables for game
//////////////////////////////////////////////////////////////////////////////////////////
// Submarine position and depth variables
int x = 0;  // X coordinate controlled by Player 1
int vX = 0; // Sub velocity in x direction
int vY = 0; // Sub velocity in y direction
int vZ = 0;
int y = 0;  // Y coordinate controlled by Player 1
int z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

// Treasure coords
int tX = 0;
int tY = 0;
int tZ = 0;

int game_tX = 0;
int game_tY = 0;
int game_tZ = 0;


// Joystick Threshold
const int joystickThreshold = 100;
int previousZ = 0;  // Stores the previous Z value for depth comparison

void setup() {
    initGame();
    pinMode(p1ButtonPin, INPUT_PULLUP);
    pinMode(p2SwitchPin, INPUT_PULLUP);
    pinMode(p1SwitchPin, INPUT_PULLUP);

    // Setup for Player 1 Joystick
    pinMode(JoyStick1_X, INPUT);
    pinMode(JoyStick1_Y, INPUT);

    // Setup treasure led
    pinMode(treasureLedPin, OUTPUT);
    pinMode(radarBlinkLed.ledPin, OUTPUT);

    // Initialize all LED pins as OUTPUT (this is for player 2's depth controller)
    pinMode(greenLED0, OUTPUT);
    pinMode(greenLED1, OUTPUT);
    pinMode(greenLED2, OUTPUT);

    pinMode(redLED0, OUTPUT);
    pinMode(redLED1, OUTPUT);
    pinMode(redLED2, OUTPUT);
    digitalWrite(treasureLedPin, LOW);

    // Start Serial communication for debugging or display
    Serial.begin(9600);

    // Initial message
    // Serial.println("Submarine Game!!!");  // Old Serial.print commented out
}

void loop() {
    // Read the state of the switch
    p2SwitchState = digitalRead(p2SwitchPin);
    p1SwitchState = digitalRead(p1SwitchPin);

    // Since we're using a pull-up, LOW means the switch is pressed
    if (p2SwitchState == LOW && ended == false) {
        if (off) {
            defaultGame();
        }
        off = false;

        // if (p1SwitchState == LOW) {
        //     tX = game_tX;
        //     tY = game_tY;
        //     tZ = game_tZ;
        // }

        updateXY();
        // displayVelocity();  // Old Serial.print commented out
        handleSubAtTreasure();
        player2RadarBlink();
        updateZLEDs();
        grabTreasure();

        // Check if the depth (z) has changed
        if (z != previousZ) {
            // displayDepth(z);  // Old Serial.print commented out
            previousZ = z;    // Store the new Z value
        }

        // Print the current coordinates and depth of the submarine to serial
        displayPosition(x, y, z);

        // Delay for smoother updates
        delay(200);
    } else if (!off) {
        initGame();
        // Serial.print("\n %%%%%%%%%%%%%%%%%%%%%%%%% \n Powering Off! \n  %%%%%%%%%%%%%%%%%%%%%%%%%");  // Old Serial.print commented out
        resetZLEDs();
        digitalWrite(treasureLedPin, LOW);
        digitalWrite(14, LOW);
        off = true;
    } else if (ended && p2SwitchState == HIGH) {
        ended = false;
    } else if (ended) {
        initGame();
        resetZLEDs();
        digitalWrite(treasureLedPin, LOW);
        digitalWrite(14, LOW);
        off = true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Game event utilities
//////////////////////////////////////////////////////////////////////////////////////////
void defaultGame() {
    // Serial.print("\nSTARTING GAME IN TUTORIAL MODE\n");  // Old Serial.print commented out
    // Submarine position and depth variables
    x = 0;  // X coordinate controlled by Player 1
    vX = 0; // Sub velocity in x direction
    vY = 0; // Sub velocity in y direction
    vZ = 0;
    y = 0;  // Y coordinate controlled by Player 1
    z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

    // Treasure coords
    tX = 0;
    tY = 0;
    tZ = 0;
}

void initGame() {
    // Submarine position and depth variables
    x = 0;  // X coordinate controlled by Player 1
    vX = 0; // Sub velocity in x direction
    vY = 0; // Sub velocity in y direction
    vZ = 0;
    y = 0;  // Y coordinate controlled by Player 1
    z = 0;  // Z coordinate (depth) controlled by Player 2 (0, 1, or 2)

    // Treasure coords
    game_tX = int(random(-10, 10));
    game_tY = int(random(-10, 10));
    game_tZ = int(random(0, 4));
}

void handleSubAtTreasure() {
    if (atTreasureCheck()) {
        // Turn on the LED
        digitalWrite(treasureLedPin, HIGH);
    } else {
        digitalWrite(treasureLedPin, LOW);
    }
}

bool atTreasureCheck() {
    if (x == tX && y == tY && z == tZ) {
        return true;
    }
    return false;
}

void directionalizeJoystickMap() {
    if (vX < 4095 / 3) {
        vX = -1;
    } else if (vX >= 4095 / 3 && vX < 2.2 * 4095 / 3) {
        vX = 0;
    } else {
        vX = 1;
    }
    if (vY < 4095 / 3) {
        vY = 1;
    } else if (vY >= 4095 / 3 && vY < 2 * 4095 / 3) {
        vY = 0;
    } else {
        vY = -1;
    }
    if (vZ < 4095 / 3) {
        vZ = -1;
    } else if (vZ >= 4095 / 3 && vZ < 2 * 4095 / 3) {
        vZ = 0;
    } else {
        vZ = 1;
    }
}

void grabTreasure() {
    // Read the state of Player 1 button
    p1ButtonState = digitalRead(p1ButtonPin);
    // Check if the button is pressed (since we're using pull-up, LOW means pressed)
    if (p1ButtonState == LOW) {
        // Serial.print("\n ############################# \n Submarine robot arm deployed \n Trying to grab treasure... \n #############################\n ");  // Old Serial.print commented out
        delay(500);
        if (atTreasureCheck()) {
            // Serial.print("Success!!! You have won the game, treasure is being collected :)\n");  // Old Serial.print commented out
            ended = true;
        } else {
            // Serial.print("Failure!!! Could not find treasure, robot arm lost in the deep ocean... Submarine exploded:(\n");  // Old Serial.print commented out
            ended = true;
        }
        // Serial.print("\n The game has now ended.\n");  // Old Serial.print commented out
    }
}

float computeDistToTreasure() {
    float sqX = sq(x - tX);
    float sqY = sq(y - tY);
    float sum = sqX + sqY;
    return sqrt(sum);
}

void player2RadarBlink() {
    int rate = int(computeDistToTreasure() / 10);  // Scale the rate
    int blinkInterval = map(computeDistToTreasure(), 0, 100, 1, 10000);
    radarBlinkLed.blinkInterval = blinkInterval;  // Minimum blink interval of 100ms
    blinkLED(radarBlinkLed);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Hardware utilities
//////////////////////////////////////////////////////////////////////////////////////////
// Function to update the LEDs based on the current Z levels
void updateZLEDs() {
    // Turn off all LEDs first
    resetZLEDs();

    // Update Green LEDs (treasure depth)
    switch (tZ) {
        case 0:
            digitalWrite(greenLED0, HIGH);
            break;
        case 1:
            digitalWrite(greenLED1, HIGH);
            break;
        case 2:
            digitalWrite(greenLED2, HIGH);
            break;
    }

    // Update Red LEDs (submarine depth)
    switch (z) {
        case 0:
            digitalWrite(redLED0, HIGH);
            break;
        case 1:
            digitalWrite(redLED1, HIGH);
            break;
        case 2:
            digitalWrite(redLED2, HIGH);
            break;
    }
}

// Function to reset all LEDs (turn them off)
void resetZLEDs() {
    // Turn off all green LEDs
    digitalWrite(greenLED0, LOW);
    digitalWrite(greenLED1, LOW);
    digitalWrite(greenLED2, LOW);

    // Turn off all red LEDs
    digitalWrite(redLED0, LOW);
    digitalWrite(redLED1, LOW);
    digitalWrite(redLED2, LOW);
}

void updateXY() {
    // Read Player 1's joystick for X and Y coordinates
    vX = analogRead(JoyStick1_X);
    vY = analogRead(JoyStick1_Y);
    vZ = analogRead(JoyStick2_Y);
    directionalizeJoystickMap();
    x += vX;
    y += vY;
    z += vZ;

    if (z < 0) {
        z = 0;
    } else if (z > 2) {
        z = 2;
    }

    // Send the current submarine coordinates to the serial port
    Serial.print(x); Serial.print(",");
    Serial.print(y); Serial.print(",");
    Serial.println(z);
}

// Non-blocking blink function
void blinkLED(blinkLedState &led) {
    unsigned long currentMillis = millis();  // Get current time

    // Check if the blink interval has passed
    if (currentMillis - led.previousMillis >= led.blinkInterval) {
        // Save the last time the LED was toggled
        led.previousMillis = currentMillis;

        // Toggle the LED state
        led.ledState = !led.ledState;
        digitalWrite(led.ledPin, led.ledState ? HIGH : LOW);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Debugging stuff
//////////////////////////////////////////////////////////////////////////////////////////

// Utility function to display the position of the submarine
void displayPosition(int x, int y, int z) {
    // Serial.print("Submarine Position - X: ");  // Old Serial.print commented out
    // Serial.print(x);
    // Serial.print(", Y: ");
    // Serial.print(y);
    // Serial.print(", Depth (Z): ");
    
    switch (z) {
        case 0:
            // Serial.println("Surface");  // Old Serial.print commented out
            break;
        case 1:
            // Serial.println("Mid-Depth");  // Old Serial.print commented out
            break;
        case 2:
            // Serial.println("Deep Underwater");  // Old Serial.print commented out
            break;
    }
}

// Utility function to display depth changes
void displayDepth(int z) {
    // Serial.print("Depth changed to: ");  // Old Serial.print commented out
    switch (z) {
        case 0:
            // Serial.println("Surface");  // Old Serial.print commented out
            break;
        case 1:
            // Serial.println("Mid-Depth");  // Old Serial.print commented out
            break;
        case 2:
            // Serial.println("Deep Underwater");  // Old Serial.print commented out
            break;
    }
}


