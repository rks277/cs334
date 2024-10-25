// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

#define BUZZER_PIN 16
int photoresistorPin = 34;  // Analog pin for photoresistor
int touchPin = 4;

int melody1[] = {
  REST, REST, REST, REST, NOTE_E4, NOTE_A4, NOTE_C5,
  
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,

  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,

  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4,

  NOTE_E4, REST, NOTE_E4, NOTE_A4, NOTE_C5,

  //repeat
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,

  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,

  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4,

  NOTE_E4
};

int durations1[] = {
  4, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8,

  2, 8, 8, 8, 8,

  //repeats
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8,

  2
};

int melody2[] = {
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,  REST, NOTE_A4,
  
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4,
  
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4,
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  NOTE_C5, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,
  
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  NOTE_C5, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,
  
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4, 
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  NOTE_C5, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,
  
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_D4,
  
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4
};

int durations2[] = {
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 8, 4, 8, 4,
  1,
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 8, 4, 8, 4,
  2, 8, 16,
  
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16,
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  
  1,
  4, 8, 8, 2,
  4, 8, 4, 8, 4,
  1,
  
  4, 8, 8, 8, 8, 8, 8, 
  1,
  4, 8, 8, 8, 8, 8, 8, 
  1,
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  
  1,
  4, 8, 8, 2,
  4, 8, 4, 8, 4,
  1,
  
  4, 8, 8, 8, 8, 8, 8, 
  1,
  4, 8, 8, 8, 8, 8, 8, 
  1,
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 8, 4, 8, 4,
  1, 
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  
  1,
  4, 8, 8, 2,
  4, 8, 4, 8, 4,
  1,
  
  4, 8, 8, 8, 8, 8, 8, 
  1,
  4, 8, 8, 8, 8, 8, 8, 
  1,
  
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 8, 4, 8, 4,
  1
};

void setup()
{
  Serial.begin(9600);
  delay(1000); // give me time to bring up serial monitor

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(touchPin, INPUT);
}

void loop()
{
  readWriteData();
  music();
}

void music()
{
  int size = sizeof(durations2) / sizeof(int);
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durationsLion[note];
    tone(BUZZER_PIN, melody2[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
    readWriteData();
  }
}

void readWriteData()
{
  // Read touch sensor value
  String touchValue = String(touchRead(touchPin));
  Serial.println("Capacitive touch: " + touchValue);

  // Read photoresistor value
  String data = String(analogRead(photoresistorPin));  
  Serial.println("Photoresistor value: " + data);
}
