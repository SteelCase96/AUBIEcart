#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

/*
  This is a library for using a two axis, one switch 
  joystick, and was developed by S.Casey on Tuesday,
  November 12th, 2019 for the AUBIE Cart senior design
  project.
*/

class Joystick{
	public:
		Joystick(byte xAxisPin, byte yAxisPin, byte switchPin); // constuctor
		void read(); // unused!
		uint16_t getX(); // returns an unsigned 16-bit integer
		uint16_t getY(); // returns an unsigned 16-bit integer
    bool getSwitch(); // returns a boolean
	private:
		byte _xAxisPin;
		byte _yAxisPin;
		byte _switchPin;
		uint16_t _xAxis;
		uint16_t _yAxis;
    bool _switch;
};

#endif
