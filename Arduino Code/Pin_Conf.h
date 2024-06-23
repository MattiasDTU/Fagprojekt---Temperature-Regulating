#pragma once
#include "Lib.h"
////////////// Settings for skærm
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
//240 x 320
#define TS_MINX 140
#define TS_MINY 140
#define TS_MAXX 900	
#define TS_MAXY 900

#define YP A2
#define XM A3
#define YM 8
#define XP 9

////////////// Settings for PWM
const int COOL = 44; //ORANGEPIN
const int HEAT = 45; //GULPIN

////////////// Multiplex Control pins
// Mux control pins
const int s0 = 31;   // Digital pin1
const int s1 = 29;   // Digital pin2
const int s2 = 27;   // Digital pin3
const int s3 = 25;   // Digital pin4
// Input pin
const int SIG_pin = 15; // Input pin
