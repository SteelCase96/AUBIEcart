#ifndef HC12Lib_h
#define HC12Lib_h

#include "Arduino.h"
#include "Definitions.h"

class HC12Lib{
  public:
    HC12();
    void begin(char deviceName);
    void runBeacon();
    void lookForNode();
    void establishConnection();
    uint8_t available();
    void txPacket(char to, char type, char * payload, uint8_t payloadLen);
    char * rxPacket();
    void clearPacket();
  private:
    char _deviceName;
    char packet[MAX_PACKET_SIZE];
};

#endif
