#ifndef TxRx_h
#define TxRx_h

#include "Arduino.h"
#include "Defines.h"

void tx(char to, char from, char type, uint8_t len, char payload[]);

char * rx();

#endif
