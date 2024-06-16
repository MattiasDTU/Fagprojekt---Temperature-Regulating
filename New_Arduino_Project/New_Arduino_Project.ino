#pragma once
#include "Lib.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  TCCR5A = B00100011; // Phase and frequency correct PWM change at OCR5A
  TCCR5B = B11001;  //(Prescale)
  OCR5A = 159; // 16MHz/(100kHz+1)=159   prescaler set to 1
  OCR5B = 79; 
  OCR5C = 79;//motors sto
  // Setup Output pins
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  pinMode(SIG_pin, INPUT);
  //PWM
  pinMode(COOL, OUTPUT);
  analogWrite(COOL, 168);
  pinMode(HEAT, OUTPUT);
  analogWrite(HEAT, 255);
  //pinMode(pwmPin3, OUTPUT);
  // Set all digital pins to low state
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);  // Landscape orientation
  CheckSerial();
  delay(2000);
  while (!Serial) {
    SerialNotFound();
  }
  SerialFound();
  delay(2000);
  currentScreen = MENU;
}

void loop() {
  while (CurrentReading != numPoints) {
    for (int i = 0; i < numPoints; i++) {
      readMux(temperatures[i][CurrentReading], i);
    }
    CurrentReading++;
  }
  //Skub alle værdier en tilbage i vores array
  for (int i = 0; i < numSensors; i++) {
    for (int j = 0; j < numPoints-1; j++) {
    temperatures[i][j] = temperatures[i][j + 1];
    }
    //Opdater sidste værdi i array
    readMux(temperatures[i][numPoints - 1], i); 
  }
  //Tjek Skærm variablen
  if (currentScreen != previousScreen) {
    if (currentScreen == SETTINGS) {
      DrawSettingsScreen();
    } else if (currentScreen == SENSORS) {
      DrawSensorsScreen();
    } else if (currentScreen == GRAPH) {
      DrawGraphScreen();
    } else if (currentScreen == COLOR || currentScreen == HOTCOLOR || currentScreen == COLDCOLOR || currentScreen == GRAPHCOLOR || currentScreen == NORMCOLOR ) {
      DrawColorScreen();
    } else if (currentScreen == SIMULATION) {
      DrawSimulationScreen();
    } else if (currentScreen == MENU) {
      DrawMenuScreen();
    }
  previousScreen = currentScreen;
  }
  ControlSwitch(currentScreen);
  checkRegulator();
  if (CurrentReading == numPoints) {
    for (int Sensor = 0; Sensor < numSensors; Sensor++) {
      Serial.print(temperatures[Sensor][numPoints-1]);
      Serial.print(", ");
    }
    Serial.print(millis());
    if (HotTimer > 0) {
      Serial.print(",FAN ON");
    }
    if (ColdTimer > 0) {
      Serial.print(",HEAT ON");
    }
    if (HotTimer == 0 && ColdTimer == 0) {
      Serial.print(",Nothing on");
    }
    Serial.println();
  }

}
