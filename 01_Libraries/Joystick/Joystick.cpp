
#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick(byte xAxisPin, byte yAxisPin, byte switchPin){
	_xAxisPin = xAxisPin;
	_yAxisPin = yAxisPin;
	_switchPin = switchPin;
	int _xAxis;
	int _yAxis;
}

void Joystick::read(){
	_xAxis = analogRead(_xAxisPin);
	_yAxis = analogRead(_yAxisPin);
}

int Joystick::getX(){
	return _xAxis;
}

int Joystick::getY(){
	return _yAxis;
}
