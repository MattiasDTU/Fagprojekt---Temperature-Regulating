#pragma once
#include "Lib.h"

void PWMON(int pin, int value) {
  // Bruges til at tænde for PWM-signalet
  analogWrite(pin, value);
}

void PWMOFF(int pin,int value) {
  // Bruges til at slukke for PWM-signalet
  analogWrite(pin, value);
}