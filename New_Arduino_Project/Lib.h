#pragma once
#include "Packages.h"
#include "Pin_Conf.h"
#include "Colors.h"


//Global Variables
extern float GlobalHot;
extern float GlobalCold;
extern int ColdColor;
extern int HotColor;
extern int NormColor;
extern int GraphColor;
const int numSensors = 16;
const int numPoints = 10;
extern int CurrentReading;
extern float temperatures[numSensors][numPoints];
extern const int NewChannels[16];
extern float KonvKonstant;
extern int Timer;
extern int ColdTimer;
extern int HotTimer;
extern float WantedTemperature;
extern const float WEIGHT_1;
extern const float WEIGHT_2;
extern const float WEIGHT_3;
extern const int THRESHOLD_CHECK;
extern int HotON;
extern int ColdON;
const int ORIGINAL_SIZE = 4;
const int TARGET_SIZE = 25;
extern int GraphBegin;
extern float prev_temprange;
extern int previousScreen;

//Data
extern CD74HC4067 mux;
int readMux(float &temperature, int channel);
void linearReg(const float y[], int n, float& m, float& b);
float* meanOfArray(const float array1[], const float array2[], int size);
float calculateThreshold(float m, float Error);
int calculateTimer(float threshold, float tempNTC1, float tempNTC2, float tempNTC3, float tempNTC4);
void regulator(float value);
void checkRegulator();

//Windows
enum ScreenState {
    MENU,
    SETTINGS,
    SENSORS,
    GRAPH,
    COLOR,
    SIMULATION,
    COLDCOLOR,
    HOTCOLOR,
    NORMCOLOR,
    GRAPHCOLOR
};
extern ScreenState currentScreen;
void text(const char* text, int x, int y,int size, int color1, int color2 );
void number(float number, int x, int y,int size, int color1, int color2 );
void background();
void CheckSerial();
void SerialNotFound();
void SerialFound();
void DrawMenuScreen();
void DrawSettingsScreen();
void DrawSensorsScreen();
void DrawGraphScreen();
void DrawColorScreen();
void DrawSimulationScreen();
void SensorBoxes(int startX, int startY, int boxWidth, int boxHeight, int gapX, int gapY);
void drawTemperatureBox(int x, int y, float temp, uint16_t fillColor, uint16_t textColor);

//Controls
extern MCUFRIEND_kbv tft;
extern TouchScreen ts;
extern int GraphSensor;
void MenuControls();
void SettingControls();
void SensorControls();
void GraphControls();
void ColorControls();
void SimulationControls();
void ControlSwitch(ScreenState currentScreen);

//PWM
void PWMON(int pin, int value);
void PWMOFF(int pin,int value);

//Interpolation
extern float originalGrid[ORIGINAL_SIZE][ORIGINAL_SIZE];
extern float targetGrid[TARGET_SIZE][TARGET_SIZE];
void UpdateSmallGrid();
void bilinearInterpolate(float originalGrid[ORIGINAL_SIZE][ORIGINAL_SIZE], float targetGrid[TARGET_SIZE][TARGET_SIZE]);
uint16_t getHeatmapColor(float value);
void drawColormap(float targetGrid[TARGET_SIZE][TARGET_SIZE], int startX, int startY);
