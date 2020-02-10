#include "Arduino.h"
#include "Joystick.h"

/* - This is a library for using a two axis, one switch joystick, and was developed by S.Casey on Tuesday, November 12th, 2019 for the 
      AUBIE Cart senior design project. */

// Constuctor
Joystick::Joystick(uint8_t xAxisPin, uint8_t yAxisPin, uint8_t switchPin){
  _xAxisPin = xAxisPin;
  _yAxisPin = yAxisPin;
  _switchPin = switchPin;
  _xAxis; // unsigned 16-bit integer
  _yAxis; // unsigned 16-bit integer
  _switch; // boolean
}

// Unused Method
void Joystick::read(){
  _xAxis = analogRead(_xAxisPin);
  _yAxis = analogRead(_yAxisPin);
  _switch;
}

// Method to read the switch of a joystick.
bool Joystick::getSwitch(){
  // not yet developed!
}

// Method to read the x axis of a joystick.
uint16_t Joystick::getX(){
  _xAxis = analogRead(_xAxisPin);
  return _xAxis;
}

// Method to read the y axis of a joystick.
uint16_t Joystick::getY(){
  _yAxis = analogRead(_yAxisPin);
  return _yAxis;
}
