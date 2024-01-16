#include "Arduino.h"
#include "BlinkLED.h"

/**
Written by: MCzapp 16.01.2024
Release: 1.1.0
Version: 1.0.0

Lets the LED Blink in the givin interval

Input:
  int Pin = Pin where your LED is located at.
  int onTime = Time in ms that the LED is on HIGH
  int offTime = Time in ms that the LED is on LOW

Output:
  void
**/

void blink (int pin, int onTime, int offTime)
{

  if(millis() - privousMilli > onTime) {
    digitalWrite(pin, HIGH);
  }

  if(millis() - privousMilli > offTime) {
    privousMilli = millis();
    digitalWrite(pin,LOW);
  }
}
