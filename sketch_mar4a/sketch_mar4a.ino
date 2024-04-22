
                // .--------------------------------.
                // |      __  __       _            |
                // |     |  \/  | __ _(_)_ __       |
                // |     | |\/| |/ _` | | '_ \      |
                // |     | |  | | (_| | | | | |     |
                // |     |_|  |_|\__,_|_|_| |_|     |
                // '--------------------------------'

#include "Libs.h"

void setup() {
  // Setup Output pins
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  // Set all digital pins to low state
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  Serial.begin(9600 );

  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.setRotation(1);  // Landscape orientation
}



void loop() {
  if (currentReading < numPoints) {
    // Collect one data point for each sensor
    for (int Sensor = 0; Sensor < numSensors; Sensor++) {
      readMux(temperatures[Sensor][currentReading], Sensor);
    }
    currentReading++;
  } else {
    // Update the array one point at a time for each sensor
    for (int Sensor = 0; Sensor < numSensors; Sensor++) {
      // Shift values to make room for the new reading
      for (int i = 0; i < numPoints - 1; i++) {
        temperatures[Sensor][i] = temperatures[Sensor][i + 1];
      }
      // Read new data point
      readMux(temperatures[Sensor][numPoints - 1], Sensor);
    }
  }

  // if (currentReading == numPoints) {
  //   for (int Sensor = 0; Sensor < numSensors; Sensor++) {
  //     Serial.print("Sensor ");
  //     Serial.print(Sensor);
  //     Serial.print(": ");
  //     for (int reading = 0; reading < numPoints; reading++) {
  //       Serial.print(temperatures[Sensor][reading]);
  //       Serial.print(", ");
  //     }
  //     Serial.println();
  //   }
  // } 
  //// Konstant kørende ting:
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);     //.kbv these pins are shared with TFT
  pinMode(XM, OUTPUT);     //.kbv these pins are shared with TFT
  if (Screen == 'M') {
    if (Update_window == 0) {
      Serial.println("Updating Menu Layout...");
      Menu_Layout();
      Update_window = 1;
      Serial.println("Menu Layout Updated.");
    }
    Menu_Controls();
  }
  if (Screen == 'S') {
    if (Update_window == 0) {
      Serial.println("Updating Sensor Layout...");
      Sensor_Layout();
      Update_window = 1;
      Serial.println("Sensor Layout Updated.");
    }
    Sensor_Controls();
  }
  if (Screen == 'C') {
    if (Update_window == 0) {
      Serial.println("Updating Config Layout...");
      Config_Layout();
      Update_window = 1;
      Serial.println("Sensor Config Updated.");
    }
    Config_Controls();
    }
  if (Screen == 'W') {
    if (Update_window == 0) {
      Serial.println("Updating Color Layout...");
      Color_Layout();
      Update_window = 1;
      Serial.println("Color layout Updated.");
    }
    Color_Controls();
  }  
  if (Screen == 'G') {
    if (Update_window == 0) {
      Serial.println("Updating Graph Layout...");
      Graph_Layout();
      Update_window = 1;
      Serial.println("Color Graph Updated.");
    }
    Graph_Control();
  }
/*
  if (p.z > ts.pressureThreshhold) {
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    }
    */
}
