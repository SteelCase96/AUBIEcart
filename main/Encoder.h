#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"
//#include "Wire.h"
//#include "Defines.h"

class Encoder{
  public:
    Encoder(uint8_t CHApin, uint8_t CHBpin); // constructor
    int8_t beginEncoder();
    uint16_t getLastCount();
    uint16_t getLastPeriod();
    uint16_t getLastTime();
    void measureISR();
  private:
    volatile uint16_t _lastPeriod;
    volatile uint16_t _lastCount;
    volatile uint16_t _lastTime;
    uint8_t _CHApin;
    uint8_t _CHBpin;
};

#endif
