#include "Arduino.h"
#include "Motor.h"

/*
*/

// Constructor
Motor::Motor(uint8_t pwmPin, uint8_t redPin, 
				uint8_t bluePin, bool reverse){
	_pwmPin = pwmPin;
	pinMode(_pwmPin,OUTPUT);
	_redPin = redPin;
	pinMode(_redPin,OUTPUT);
	_bluePin = bluePin;
	pinMode(_bluePin,OUTPUT);
	_reverse = reverse;
	_speed = 0;
	_direction = 0;
}

// Method to set the speed of the motor.
void Motor::setPWM(uint8_t PWMspeed){
	_speed = PWMspeed;
	analogWrite(_pwmPin,_speed);
}

// Method to set the direction of the motor.
void Motor::setDirection(int8_t direct){
	_direction = direct;
	if((_direction == 1 && _reverse == false)||
      (_direction == -1 && _reverse == true)){
		digitalWrite(_redPin,HIGH);
		digitalWrite(_bluePin,LOW);
	}else if((_direction == -1 && _reverse == false)||
      (_direction == 1 && _reverse == true)){
		digitalWrite(_redPin,LOW);
		digitalWrite(_bluePin,HIGH);
	}else{
		digitalWrite(_redPin,LOW);
		digitalWrite(_bluePin,LOW);
	}
}
