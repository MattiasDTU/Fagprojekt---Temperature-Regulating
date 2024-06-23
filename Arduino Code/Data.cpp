#pragma once
#include "Lib.h"
/*
Denne fil indeholder alle funktioner der benyttes til dataindsamling, databehandling og reguleringskontrol
*/

CD74HC4067 mux(s0, s1, s2, s3);  //Definer mux pins


int readMux(float &temperature, int channel) {
  //Definer variabler
  float temp;
  float sumOfReadings = 0;
  float Mean;
  const int numReadings = 20;
  float RegulateTemp;
  //Skift til rigtige kanal
  mux.channel(NewChannels[channel]);
  //Læs 20 værdier for sensoren og udregn RMS
  for (int i = 0; i<numReadings;i++) {
    float reading = analogRead(SIG_pin);
    sumOfReadings += reading;
  }
  Mean = (sumOfReadings / numReadings);
  //Update temperatur værdi og tilføj konverteringskonstant
  temp = Mean * KonvKonstant;
  //Check Temperatur for regulering
  if (CurrentReading == numPoints && channel == 1 ) { //Tjek om vi er gået alle kanalerne igennem
        if (Timer < millis()/1000) { //Tjek om pause timer er færdig
          if (HotTimer == 0 && ColdTimer == 0) { //Tjek om regulering allerede er i gang
            Timer = millis()/1000 + 3; //Begynd Timer pause
            RegulateTemp = (temperatures[8][numPoints-1] + temperatures[11][numPoints-1])/2.0; //udregn den gennemsnitlige værdi af vores to sensorer
            regulator(RegulateTemp); //Tjek for regulering
          }
        }
      }
  temperature = temp;
}

void linearReg(const float y[], int n, float& m, float& b) {
  //Udfører lineær regression
    int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    
    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }
    
    float xMean = sumX / n;
    float yMean = sumY / n;
    
    m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    b = yMean - m * xMean;
}

float* meanOfArray(const float array1[], const float array2[], int size) {
  //Udregner den gennemsnitlige array af vores to sensorer
    float* newArray = new float[size];
    
    for (int i = 0; i < size; i++) {
        newArray[i] = fabs(array1[i] + array2[i]) / 2.0;
    }
    
    return newArray;
}

float calculateThreshold(float m, float Error) {
  //Udregner Threshold ud fra hældning, Error og vores vægte
  float Threshold = 0.0;
  Threshold = fabs(Error) * WEIGHT_1 + fabs(m) * WEIGHT_2;
  return Threshold;
}

int calculateTimer(float threshold, float tempNTC1, float tempNTC2, float tempNTC3, float tempNTC4) {
  //Udregner timer ud fra Threshold og temperaturen uden for boxen
    float meanNTC = (tempNTC1 + tempNTC2 + tempNTC3 + tempNTC4) / 4.0;
    if (meanNTC < 0) {
        meanNTC = fabs(meanNTC) / 2.0;
    }
    return threshold + meanNTC * WEIGHT_3;
}

void regulator(float value) {
  //Tjekker om regulering skal påbegyndes
    float Error = value - (GlobalHot+GlobalCold)/2.0; //Udregner Error
    float m, b;
    float threshold;
    int timer;
    float MAXError = (GlobalHot-GlobalCold)/5.0; //Udregner MAX Error
    int ColdHardCap = 0;
    int HotHardCap = 0;
    if (Error <= -MAXError ) {
        float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
        linearReg(temperatureArray, numPoints, m, b);
        threshold = calculateThreshold(m, Error);
        if (threshold > THRESHOLD_CHECK) {
            ColdTimer = millis() / 1000 + threshold / 10;
        }
        delete[] temperatureArray;
    }
    if (Error >= MAXError) {
        float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
        linearReg(temperatureArray, numPoints, m, b);
        threshold = calculateThreshold(m, Error);
        if (threshold > THRESHOLD_CHECK) {
            timer = calculateTimer(threshold, temperatures[0][numPoints - 1], temperatures[1][numPoints - 1], temperatures[2][numPoints - 1], temperatures[3][numPoints - 1]);
            HotTimer = millis() / 1000 + timer / 10;
        }
        delete[] temperatureArray;
    }
}

void checkRegulator() { //Tjekker om regulering allerede er i gang og om der skal tændes eller slukkes
    if (ColdTimer > millis() / 1000) {
        if (HotON == 0) {
            PWMON(HEAT, 0);
            HotON = 1;
        }
    } else {
        PWMOFF(HEAT, 255);
        ColdTimer = 0;
        HotON = 0;
    }
    if (HotTimer > millis() / 1000) {
        if (ColdON == 0) {
            PWMON(COOL, 0);
            ColdON = 1;
        }
    } else {
        PWMOFF(COOL, 168);
        HotTimer = 0;
        ColdON = 0;
    }
}

