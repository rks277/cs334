#include <Stepper.h>
#include <ESP32Servo.h>

// Setup
#define NUM_SERVOS 8
#define NUM_ANIMATIONS 5

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
void waveMotion(int amplitude, int speed) {
    for (int angle = 0; angle <= amplitude; angle += speed) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            int waveAngle = angle + (i * speed);
            waveAngle = waveAngle % 180;
            servos[i].write(waveAngle);
            servoPositions[i] = waveAngle;
        }
        delay(100);
    }
}

void sequential(int stepAngle, int liftAngle) {
    for (int i = 0; i < NUM_SERVOS; i++) {
        rotate(stepAngle);
        if (moveArm(i, liftAngle) < 0) {
            continue;
        }
        delay(200);
        moveArm(i, -liftAngle);
    }
}

void bounce(int bounceAngle, int stepAngle, int bounces) {
    for (int b = 0; b < bounces; b++) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            if (moveArm(i, bounceAngle) < 0) {
                continue;
            }
        }
        delay(200);

        for (int i = 0; i < NUM_SERVOS; i++) {
            moveArm(i, -bounceAngle);
        }
        delay(200);
    }
}

void spiral(int maxStepAngle, int sweepAngle) {
    for (int angle = 0; angle < maxStepAngle; angle += 20) {
        rotate(angle);

        for (int i = 0; i < NUM_SERVOS; i++) {
            if (moveArm(i, sweepAngle - servoPositions[i]) < 0) {
                continue;
            }
        }
        delay(200);

        for (int i = 0; i < NUM_SERVOS; i++) {
            moveArm(i, -sweepAngle);
        }
        delay(200);
    }
}

void cascade(int cascadeAngle, int stepAngle) {
    for (int i = 0; i < NUM_SERVOS; i++) {
        if (moveArm(i, cascadeAngle - servoPositions[i]) < 0) {
            continue;
        }
        delay(100);
        rotate(stepAngle);
    }

    for (int i = 0; i < NUM_SERVOS; i++) {
        moveArm(i, -cascadeAngle);
    }
    delay(500);
}

void loop() {
    int animationIndex = random(0, NUM_ANIMATIONS);
    switch (animationIndex) {
        case 0:
            Serial.println("Playing wave motion");
            waveMotion(180, 10);
            break;
        case 1:
            Serial.println("Playing sequential motion");
            sequentialLift(10, 30);
            break;
        case 2:
            Serial.println("Playing bounce animation");
            bounceAnimation(30, 5);
            break;
        case 3:
            Serial.println("Playing spiral sweep");
            spiralSweep(60, 45);
            break;
        case 4:
            Serial.println("Playing cascade effect");
            cascadeEffect(90, 15);
            break;
    }
    
    delay(1000);
}