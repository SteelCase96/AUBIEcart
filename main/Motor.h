#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

/* - This is a library for using a 12 VDC motor with the L298N dual H-bridge motor driver, and was developed by S.Casey on Thursday, 
      November 14th, 2019 for the AUBIE Cart senior design project. */

class Motor{
	private:
		uint8_t _pwmPin; // the pin used to output a PWM
		uint8_t _redPin;
		uint8_t _bluePin;
		uint8_t _speed;
		int8_t _direction;
		bool _flip;
	public:
		// Constructor
		Motor(uint8_t speedPin, uint8_t redPin, 
			uint8_t bluePin, bool flip);
		// Methods
		void setPWM(uint8_t PWMspeed);
    void setDirection(int8_t direct);
    void halt();
		
};

#endif
