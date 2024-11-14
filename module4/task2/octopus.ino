#include <Stepper.h>
#include <ESP32Servo.h>

// Setup
#define NUM_SERVOS 8

// Create servo arrays
Servo servos[NUM_SERVOS];
int servoPins[NUM_SERVOS] = {4, 13, 14, 15, 16, 21, 22, 23};
int servoPositions[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0};

// Stepper Motor Settings
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Init functions
void initStepper() {
    // Initialize stepper motor speed
    myStepper.setSpeed(5);
}

void initServos() {
    for (int i = 0; i < NUM_SERVOS; i++) {
        // Map pin to servo
        servos[i].attach(servoPins[i]);
        // Set initial position
        servos[i].write(servoPositions[i]);
    }
}

void setup() {
    Serial.begin(115200);
    initStepper();
    initServos();  
}

// Basic control functions
int rotate(int degrees) {
    const int steps = stepsPerRevolution * degrees / 360;
    myStepper.step(steps);
    return 1;
}

int moveArm(int arm_idx, int degrees) {
    int new_angle = servoPositions[arm_idx] + degrees;
    // Check if we can do the roation
    if (new_angle > 180 || new_angle < 0) {
        return -1;
    }
    servoPositions[arm_idx] = new_angle;
    servos[arm_idx].write(servoPositions[arm_idx]);
    return 1;
}

int moveAllArmsUp() {
    for (int i = 0; i < NUM_SERVOS; i++) {
        if (moveArm(i, 180 - servoPositions[i]) < 0) {
            return -1;
        }
    }
    return 1;
}

int moveAllArmsDown() {
    for (int i = 0; i < NUM_SERVOS; i++) {
        if (moveArm(i, -servoPositions[i]) < 0) {
            return -1;
        }
    }
    return 1;
}

// Animations

void loop() {
  

  delay(1000);
}