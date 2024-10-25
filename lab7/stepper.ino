//Includes the Arduino Stepper Library
#include <Stepper.h>

#include <ESP32Servo.h>

Servo myServo;
int servoPin = 4;

// Stepper Motor Settings
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);
// 14, 27, 26, 25

// Defines the number of steps per rotation
// const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
// Stepper myStepper = Stepper(stepsPerRevolution, 19, 18, 5, 17);

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
  Serial.begin(115200);
  /* Set the speed at 5 rpm: */
  myStepper.setSpeed(5);
  Serial.println("Connecting to: ");
  
  // put your setup code here, to run once:
  myServo.attach(servoPin);
}

void loop() {
  // Rotate CW slowly at 5 RPM
  Serial.println("hi");
  myStepper.setSpeed(5);
  myStepper.step(stepsPerRevolution);
  
  // put your main code here, to run repeatedly:
  myServo.write(30);
  delay(1000);

  // // Rotate CCW quickly at 10 RPM
  // myStepper.setSpeed(5);
  // myStepper.step(-stepsPerRevolution);
  // delay(1000);
}