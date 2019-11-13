#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick{
	public:
		Joystick(byte xAxisPin, byte yAxisPin, byte switchPin);
		void read();
		int getX();
		int getY();
	private:
		byte _xAxisPin;
		byte _yAxisPin;
		byte _switchPin;
		int _xAxis;
		int _yAxis;
};

#endif