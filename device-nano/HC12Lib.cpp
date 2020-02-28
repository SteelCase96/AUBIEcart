#define nano // nano or mega

#ifdef nano
#define TXP 10
#define RXP 11
#include <SoftwareSerial.h> // for the nano 
SoftwareSerial ThisDev(TXP,RXP); // HC-12 TX Pin, HC-12 RX Pin
#endif

#include "HC12Lib.h"

HC12Lib::HC12(){ // constructor
  #ifdef mega
  Serial2.write("Starting a mega...");
  #endif

  #ifdef nano
  ThisDev.write("Starting a nano...");
  #endif

  
  char _deviceName;
  char packet[MAX_PACKET_SIZE];
  clearPacket();
}

void HC12Lib::begin(char deviceName){
  #ifdef mega
  Serial2.begin(9600);
  #endif
  #ifdef nano
  ThisDev.begin(9600);
  #endif

  _deviceName = deviceName;
}

void HC12Lib::runBeacon(){
  char buf[5];
  buf[0] = SOH;
  buf[1] = ENQ;
  buf[2] = _deviceName;
  buf[3] = EOT;
  buf[4] = NULL;

  #ifdef mega
  Serial2.write(buf);
  #endif

  #ifdef nano
  ThisDev.write(buf);
  #endif
}

uint8_t HC12Lib::available(){
  #ifdef mega
  return Serail2.available();
  #endif
  
  #ifdef nano
  return ThisDev.available();
  #endif
}

void HC12Lib::txPacket(char to, char type, char * payload, uint8_t payloadLen){
  packet[0] = SOH; // start of heading character
  packet[1] = to; // who the packet is to
  packet[2] = type; // what type of packet it is
  
}

void HC12Lib::clearPacket(){
  uint8_t i = 0;
  while(packet[i] != NULL){
    packet[i] = NULL;
    i++;
    if(i == MAX_PACKET_SIZE){ // if reached end of packet
      return;
    }
  }
}
