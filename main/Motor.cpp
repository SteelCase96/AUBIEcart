#include "Arduino.h"
#include "Motor.h"
#include "Defines.h"

/* - This is a library for using a 12 VDC motor with the L298N dual H-bridge motor driver, and was developed by S.Casey on Thursday, 
      November 14th, 2019 for the AUBIE Cart senior design project. */

// Constructor
Motor::Motor(uint8_t pwmPin, uint8_t redPin, uint8_t bluePin, bool flip){
	_pwmPin = pwmPin;
	pinMode(_pwmPin,OUTPUT);
	_redPin = redPin;
	pinMode(_redPin,OUTPUT);
	_bluePin = bluePin;
	pinMode(_bluePin,OUTPUT);
	_flip = flip;
	_speed = 0;
	_direction = noDirection;
}

// Method to set the speed of the motor.
void Motor::setPWM(uint8_t PWMspeed){
	_speed = PWMspeed;
	analogWrite(_pwmPin,_speed);
}

// Method to set the direction of the motor.
void Motor::setDirection(int8_t direct){
	_direction = direct;
	if((_direction == forwardDirection && _flip == false)||
      (_direction == backwardDirection && _flip == true)){
		digitalWrite(_redPin,HIGH);
		digitalWrite(_bluePin,LOW);
	}else if((_direction == backwardDirection && _flip == false)||
      (_direction == forwardDirection && _flip == true)){
		digitalWrite(_redPin,LOW);
		digitalWrite(_bluePin,HIGH);
	}else{
		digitalWrite(_redPin,LOW);
		digitalWrite(_bluePin,LOW);
	}
}

void Motor::halt(){
  analogWrite(_pwmPin,0);
  digitalWrite(_redPin,LOW);
  digitalWrite(_bluePin,LOW);
}
