#pragma once
#include "Lib.h"

float GlobalCold = 30.0;
float GlobalHot = 35.0;
int ColdColor = BLUE;
int HotColor = RED;
int NormColor = GREEN;
int GraphColor = CYAN;
float temperatures[numSensors][numPoints] = {0};
const int NewChannels[16] = {15,14,13,12,9,11,3,5,10,2,8,4,6,1,7,0};
int CurrentReading = 0;
float KonvKonstant = 0.043636;
int Timer = 0;
int HotTimer = 0;
int ColdTimer = 0;
float WantedTemperature = 32.5;
const float WEIGHT_1 = 40.0;
const float WEIGHT_2 = 100.0;
const float WEIGHT_3 = 5.0;
const int THRESHOLD_CHECK = 100;
int HotON = 0;
int ColdON = 0;
int GraphSensor = 0;
int GraphBegin = 0;
float prev_temprange = 0.0;
int previousScreen = -1;