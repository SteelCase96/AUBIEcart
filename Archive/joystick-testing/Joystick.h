#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

/* - This is a library for using a two axis, one switch joystick, and was developed by S.Casey on Tuesday, November 12th, 2019 for the 
      AUBIE Cart senior design project. */

class Joystick{
  public:
    Joystick(uint8_t xAxisPin, uint8_t yAxisPin, uint8_t switchPin); // constuctor
    void read(); // unused!
    uint16_t getX(); // returns an unsigned 16-bit integer
    uint16_t getY(); // returns an unsigned 16-bit integer
    bool getSwitch(); // returns a boolean
  private:
    uint8_t _xAxisPin;
    uint8_t _yAxisPin;
    uint8_t _switchPin;
    uint16_t _xAxis;
    uint16_t _yAxis;
    bool _switch;
};

#endif
