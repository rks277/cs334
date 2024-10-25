#include <ESP32Servo.h>

Servo myServo;
int servoPin = 4;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(30);
  delay(1000);
  Serial.println("hi");

  myServo.write(60);
  delay(1000);

}