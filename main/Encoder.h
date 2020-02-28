#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"
//#include "Wire.h"
//#include "Defines.h"

/* - This library is for 2-channel optical encoders. Note: this library presently only measures channel A.*/

class Encoder{
  public:
    Encoder(uint8_t CHApin, uint8_t CHBpin); // constructor
    int8_t beginEncoder();
    uint16_t getLastCount();
    uint16_t getLastPeriod();
    uint16_t getLastTime();
    uint16_t getLastPeriodAVG();
    void resetPeriodAVG();
    void findPeriodAVG(uint16_t lastPeriod); // intended to only be called in the measureISR function
    void measureISR();
  private:
    volatile uint16_t _lastPeriod;
    volatile uint16_t _lastCount;
    volatile uint16_t _lastTime;
    volatile uint16_t _lastPeriodAVG;
    volatile uint16_t _periodSUM;
    volatile uint16_t _periodCount;
    uint8_t _CHApin;
    uint8_t _CHBpin;
};

#endif
