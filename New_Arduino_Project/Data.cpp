#pragma once
#include "Lib.h"


CD74HC4067 mux(s0, s1, s2, s3);  


int readMux(float &temperature, int channel) {
  //Definer variabler
  float temp;
  float sumOfSquares = 0;
  float rms;
  const int numReadings = 20;
  float RegulateTemp;
  //Skift til rigtige kanal
  mux.channel(NewChannels[channel]);
  //Læs 20 værdier for sensoren og udregn RMS
  for (int i = 0; i<numReadings;i++) {
    float reading = analogRead(SIG_pin);
    sumOfSquares += reading * reading;
  }
  rms = sqrt(sumOfSquares / numReadings);
  //Update temperatur værdi og tilføj konverteringskonstant
  temp = rms * KonvKonstant;
  //Check Temperatur for regulering
  if (CurrentReading == numPoints && channel == 1 ) {
        if (Timer < millis()/1000) {
          if (HotTimer == 0 && ColdTimer == 0) {
            Timer = millis()/1000 + 3;
            RegulateTemp = (temperatures[8][numPoints-1] + temperatures[11][numPoints-1])/2.0;
            regulator(RegulateTemp);
          }
        }
      }
  temperature = temp;
}

void linearReg(const float y[], int n, float& m, float& b) {
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
    float* newArray = new float[size];
    
    for (int i = 0; i < size; i++) {
        newArray[i] = fabs(array1[i] + array2[i]) / 2.0;
    }
    
    return newArray;
}

float calculateThreshold(float m, float Error) {
  float Threshold = 0.0;
  Threshold = fabs(Error) * WEIGHT_1 + m * WEIGHT_2;
  return Threshold;
}

int calculateTimer(float threshold, float tempNTC1, float tempNTC2, float tempNTC3, float tempNTC4) {
    float meanNTC = (tempNTC1 + tempNTC2 + tempNTC3 + tempNTC4) / 4.0;
    if (meanNTC < 0) {
        meanNTC = fabs(meanNTC) / 2.0;
    }
    return threshold + meanNTC * WEIGHT_3;
}

void regulator(float value) {
    float errorFreezing = value - (GlobalHot+GlobalCold)/2.0;
    float errorHot = value - (GlobalHot+GlobalCold)/2.0;
    float m, b;
    float threshold;
    int timer;
    float error = ((GlobalHot-GlobalCold)/5.0);
    int ColdHardCap = 0;
    int HotHardCap = 0;
    if ((temperatures[8][numPoints-1] > GlobalHot) || (temperatures[11][numPoints-1] > GlobalHot)) {
      HotHardCap = 1;
      float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
        linearReg(temperatureArray, numPoints, m, b);
        // errorHot = temperatureArray[numPoints - 1] - WantedTemperature;
        threshold = calculateThreshold(m, errorHot);
        if (threshold > THRESHOLD_CHECK/3) {
            timer = calculateTimer(threshold, temperatures[0][numPoints - 1], temperatures[1][numPoints - 1], temperatures[2][numPoints - 1], temperatures[3][numPoints - 1]);
            ColdTimer = 0;
            HotTimer = millis() / 1000 + timer / 10;
        }
        delete[] temperatureArray;
    } else if ((temperatures[8][numPoints-1] < GlobalCold) || (temperatures[11][numPoints-1] < GlobalCold)) {
      ColdHardCap = 1;
      float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
      linearReg(temperatureArray, numPoints, m, b);
      // errorFreezing = temperatureArray[numPoints - 1] - WantedTemperature;
      threshold = calculateThreshold(m, errorFreezing);
      if (threshold > THRESHOLD_CHECK/3) {
          HotTimer = 0;
          ColdTimer = millis() / 1000 + threshold / 10;
      }
      delete[] temperatureArray;
    }
    if (errorFreezing <= -error && ColdTimer == 0 && HotTimer == 0 && ColdHardCap == 0 && HotHardCap == 0) {
        float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
        linearReg(temperatureArray, numPoints, m, b);
        // errorFreezing = temperatureArray[numPoints - 1] - WantedTemperature;
        threshold = calculateThreshold(m, errorFreezing);
        if (threshold > THRESHOLD_CHECK) {
            ColdTimer = millis() / 1000 + threshold / 10;
        }
        delete[] temperatureArray;
    }
    if (errorHot >= error && ColdTimer == 0 && HotTimer == 0 && ColdHardCap == 0 && HotHardCap == 0) {
        float* temperatureArray = meanOfArray(temperatures[8], temperatures[11], numPoints);
        linearReg(temperatureArray, numPoints, m, b);
        // errorHot = temperatureArray[numPoints - 1] - WantedTemperature;
        threshold = calculateThreshold(m, errorHot);
        if (threshold > THRESHOLD_CHECK) {
            timer = calculateTimer(threshold, temperatures[0][numPoints - 1], temperatures[1][numPoints - 1], temperatures[2][numPoints - 1], temperatures[3][numPoints - 1]);
            HotTimer = millis() / 1000 + timer / 10;
        }
        delete[] temperatureArray;
    }
}

void checkRegulator() {
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