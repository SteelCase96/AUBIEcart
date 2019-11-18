#ifndef Motor_h
#define Motor_h

/*
	This is a library for a 12 V DC motor
*/

#include "Arduino.h"

class Motor{
	private:
		uint8_t _pwmPin; // the pin used to output a PWM
		uint8_t _redPin;
		uint8_t _bluePin;
		uint8_t _speed;
		int8_t _direction;
		bool _reverse;
	public:
		// Constructor
		Motor(uint8_t speedPin, uint8_t redPin, 
			uint8_t bluePin, bool reverse);
		// Methods
		void setPWM(uint8_t PWMspeed);
		void setDirection(int8_t direct);
		
};

#endif
