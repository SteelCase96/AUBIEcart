#include "Encoder.h"

Encoder::Encoder(uint8_t CHApin, uint8_t CHBpin){ // constructor
  /* - Function to construct the object, alloting memory spaces*/
  volatile uint16_t _lastPeriod = 0;
  volatile uint16_t _lastCount = 0;
  volatile uint16_t _lastTime = 0;
  uint8_t _CHApin = CHApin;
  uint8_t _CHBpin = CHBpin;
};

int8_t Encoder::beginEncoder(){
  /* - Function to start the timer and ISR that measures the state of this encoder. This funciton returns -1 
        if it fails to start the encoder.*/
  pinMode(_CHApin,INPUT_PULLUP);
  
//  // Counter Setup -- needs condition to check if timer is already running!
//  if(!((TCCR5B & 0x01)|(TCCR5B & 0x02)|(TCCR5B & 0x04))){ // if timer has NOT already been started
//    noInterrupts();
//    TCCR5A = 0;
//    TCCR5B = 0;
//    TCNT5 = 0;
//    interrupts();
//    TCCR5B |= (1<<CS50);
//  }
//  else{ // if timer has already been started
    noInterrupts();
    _lastTime = TCNT5;
    interrupts();
//  }
  
  return 1; // indicates success
}

void Encoder::measureISR(){
  uint16_t newTime = TCNT5;
  if(newTime > _lastTime){
    _lastPeriod = newTime - _lastTime;
  }
  else{
    _lastPeriod = (65535 - _lastTime) + newTime;
  }
  _lastTime = newTime;

  if(_lastCount == 65535){
    _lastCount = 0;
  }
  else{
    _lastCount++;
  }
}

uint16_t Encoder::getLastCount(){
  noInterrupts();
  uint16_t temp = _lastCount;
  interrupts();
  return temp;
}

uint16_t Encoder::getLastPeriod(){
  noInterrupts();
  uint16_t temp = _lastPeriod;
  interrupts();
  return temp;
}

uint16_t Encoder::getLastTime(){
  noInterrupts();
  uint16_t temp = _lastTime;
  interrupts();
  return temp;
}
