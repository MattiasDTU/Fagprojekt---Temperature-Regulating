#pragma once
#include "Lib.h"
/*
Denne fil bliver brugt til at definere alle globale variabler der benyttes henover programmet
*/
float GlobalCold = 30.0;
float GlobalHot = 35.0;
int ColdColor = BLUE;
int HotColor = RED;
int NormColor = GREEN;
int GraphColor = CYAN;
float temperatures[numSensors][numPoints] = {0};
const int NewChannels[16] = {12,13,14,15,5,3,11,9,4,8,2,10,0,7,1,6};
int CurrentReading = 0;
float KonvKonstant = 0.043019; //0.036584; //0.043636;
int Timer = 0;
int HotTimer = 0;
int ColdTimer = 0;
float WantedTemperature = 32.5;
const float WEIGHT_1 = 80;  //60
const float WEIGHT_2 = 400.0;
const float WEIGHT_3 = 10.0;
const int THRESHOLD_CHECK = 100;
int HotON = 0;
int ColdON = 0;
int GraphSensor = 0;
int GraphBegin = 0;
float prev_temprange = 0.0;
int previousScreen = -1;