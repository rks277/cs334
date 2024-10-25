// Includes the Arduino Stepper Library
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

int servoPosition = 0;  // Track the current position of the servo

void setup() {
  Serial.begin(115200);
 
  // Initialize stepper motor speed
  myStepper.setSpeed(5);

  // Attach servo motor to pin
  myServo.attach(servoPin);
 
  // Set servo to initial position (0 degrees)
  myServo.write(servoPosition);
}

void loop() {
  // Rotate stepper motor 360° (one full revolution)
  myStepper.step(stepsPerRevolution);

  // Increment servo position by 10 degrees after each full stepper rotation
  servoPosition += 10;

  // Check if servo has reached or exceeded 180 degrees
  if (servoPosition > 180) {
    servoPosition = 0;  // Reset to 0 degrees if it exceeds 180
  }

  // Move servo to the updated position
  myServo.write(servoPosition);

  // Log the current positions
  Serial.print("Stepper completed one revolution, servo moved to: ");
  Serial.println(servoPosition);

  // Delay before the next iteration (adjust if needed)
  delay(1000);
}