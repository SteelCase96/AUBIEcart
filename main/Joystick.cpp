#include "Arduino.h"
#include "Joystick.h"

/* - This is a library for using a two axis, one switch joystick, and was developed by S.Casey on Tuesday, November 12th, 2019 for the 
      AUBIE Cart senior design project. */

// Constuctor
Joystick::Joystick(byte xAxisPin, byte yAxisPin, byte switchPin){
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
  uint16_t temp = analogRead(_xAxisPin);
  _xAxis = map(temp,0,1023,1023,0);
	return temp;
}

// Method to read the y axis of a joystick.
uint16_t Joystick::getY(){
  uint16_t temp = analogRead(_yAxisPin);
  _yAxis = map(temp,0,1023,1023,0);
	return temp;
}
