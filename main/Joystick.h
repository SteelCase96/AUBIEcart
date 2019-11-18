#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick{
	public:
		Joystick(byte xAxisPin, byte yAxisPin, byte switchPin);
		void read(); // unused!
		uint16_t getX();
		uint16_t getY();
	private:
		byte _xAxisPin;
		byte _yAxisPin;
		byte _switchPin;
		uint16_t _xAxis;
		uint16_t _yAxis;
};

#endif
