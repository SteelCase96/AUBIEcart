
#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick(byte xAxisPin, byte yAxisPin, byte switchPin){
	_xAxisPin = xAxisPin;
	_yAxisPin = yAxisPin;
	_switchPin = switchPin;
	_xAxis;
	_yAxis;
}

void Joystick::read(){
  // unused!
}

uint16_t Joystick::getX(){
  _xAxis = analogRead(_xAxisPin);
	return _xAxis;
}

uint16_t Joystick::getY(){
  _yAxis = analogRead(_yAxisPin);
	return _yAxis;
}
