#ifndef HC12Lib_h
#define HC12Lib_h

#include "Arduino.h"
#include "Definitions.h"

class HC12Lib{
  public:
    HC12Lib(char deviceName); // constructor
    void begin();
    void enquiry();
    void acknowledge(char to);
    char establishConnection(bool isConsole);
    uint8_t available();
    void txPacket(char to, char type, char * payload);
    char * rxData();
    char * findPacket();
    void clearPacket();
  private:
    char peek();
    char read();
    void write(char * pack);
    bool _connectionEstablished;
    bool _isConsole;
    char _clientName;
    char _deviceName;
    char _packet[MAX_PACKET_SIZE];
};

#endif
