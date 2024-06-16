#pragma once
#include "Lib.h"

void PWMON(int pin, int value) {
  analogWrite(pin, value);  // Set the pin HIGH
}

void PWMOFF(int pin,int value) {
  analogWrite(pin, value);   // Set the pin LOW
}