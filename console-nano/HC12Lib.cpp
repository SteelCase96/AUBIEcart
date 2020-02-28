#define nano // nano or mega

#ifdef nano
#define TXP 10
#define RXP 11
#include <SoftwareSerial.h> // for the nano 
SoftwareSerial ThisDev(TXP,RXP); // HC-12 TX Pin, HC-12 RX Pin
#endif

#include "HC12Lib.h"

HC12Lib::HC12Lib(char deviceName){ // constructor
  #ifdef mega
//  Serial2.write("Starting a mega...");
  #endif

  #ifdef nano
//  ThisDev.write("Starting a nano...");
  #endif
  
  _connectionEstablished = false;
  _isConsole;
  _clientName;
  _deviceName = deviceName;
  _packet[MAX_PACKET_SIZE];
//  clearPacket();
  return;
}

char HC12Lib::establishConnection(bool isConsole){
  _isConsole = isConsole;
  
  if(_isConsole == true){
    while(!_connectionEstablished){ // while not connected
      enquiry(); // enquire if there is a device to connect to
      delay(1000); // wait for a response -- perhaps shorter?
      if(available() > 0){ // if there's data, it might be an acknowledge!
        char * address = rxData(); // receive the data
        if(address[3] == ACK){ // if it was an acknowledge!
          _clientName = address[2];
          acknowledge(_clientName);
          clearPacket();
          _connectionEstablished = true;
          return _clientName;
        }
      }
    }
  }
  else{
    while(!_connectionEstablished){ // while not connected
      if(available() > 0){ // if there's data - might be a beacon!
        char * address = rxData();
        if(address[1] == ENQ){ // if it's a beacon packet
          _clientName = address[2];
          clearPacket();
          acknowledge(_clientName);
        }
        else if(address[3] == ACK){
          clearPacket();
          _connectionEstablished = true;
          return _clientName;
        }
      }
      delay(10);
    }
  }
}

void HC12Lib::begin(){
  #ifdef mega
  Serial2.begin(9600);
  #endif
  #ifdef nano
  ThisDev.begin(9600);
  #endif
}

void HC12Lib::enquiry(){
  char buf[5];
  buf[0] = SOH;
  buf[1] = ENQ;
  buf[2] = _deviceName;
  buf[3] = EOT;
  buf[4] = NULL;
  
  write(buf);
}

void HC12Lib::acknowledge(char to){
  char buf[6];
  buf[0] = SOH;
  buf[1] = to;
  buf[2] = _deviceName;
  buf[3] = ACK;
  buf[4] = EOT;
  buf[5] = NULL;
  
  write(buf);
}

uint8_t HC12Lib::available(){
  #ifdef mega
  return Serial2.available();
  #endif
  
  #ifdef nano
  return ThisDev.available();
  #endif

  return;
}

void HC12Lib::txPacket(char to, char type, char * payload){
  /* - Function to send some data. The funciton must be given a destination character, a type character, and a char array payload 
   *    (or data array, max 256 bytes including the null char). The maximum packet size is the max payload size (256), plus the 
   *    header data (4), plus all of the extra characters (6), for a total of 265 bytes. Prior to sending the packet, a null 
   *    character is attached to the packet char array.
   */
  
  char buf[MAX_PACKET_SIZE];
  uint8_t payloadLen = 0;
  while(*(payload+payloadLen) != NULL){
    ++payloadLen;
  }
  
  buf[0] = SOH; // start of heading character
  buf[1] = to; // who the packet is to
  buf[2] = _deviceName; // who the packet is from
  buf[3] = type; // what type of packet it is
  buf[4] = payloadLen; // how long the payload is
  buf[5] = STX; //  start of text character
  buf[6] = NULL; // NULL terminating the array so it can be used by the strcat function
  strcat(buf,payload);
  char endStr[] = {ETX,EOT,NULL}; // end of text character, end of transmission character, NULL terminating the array so it can be used by the strcat function
  strcat(buf,endStr);

  write(buf);
}

char * HC12Lib::rxData(){
  /*
   * This function returns a uint8_t, with values meaning:
   *  - 0 no packet, packet wasn't to this device, or something went wrong
   *  - 1 successfully recieved a packet
   *  - 2 for an enquiry
   */
  while(available() > 0){
    if(read() == SOH){ // if a packet is discovered
      while(available() == 0){ // while no data is ready to be read
        delay(10); // delay for 10 milliseconds
      }
      char incoming = read();
      if(incoming == _deviceName){ // if the packet is to me
        char buf[MAX_PACKET_SIZE]; // allocate memory space to save the packet
        bool fin = false; // loop token
        uint8_t i = 2; // index variable
        buf[0] = SOH;
        buf[1] = incoming;
        while(!fin){ // while not finished recieving the packet
          // loop through waiting data
          if(available() == 0){ // if no data is ready to be read
            delay(10);
          }
          else{ // else data is ready to read
            incoming = read();
            if(incoming == EOT){ // if reached the end of transmission character
              buf[i] = incoming;
              buf[(i+1)] = NULL;
              fin = true;
            }
            else{ // else not reached the EOT character
              buf[i] = incoming;
              ++i;
            }
          }
        }
        strcpy(_packet,buf);
        return _packet;
      }
      else if(incoming == ENQ){ // if it's a beacon's signal
        char buf[5]; // data buffer
        bool fin = false; // loop token
        uint8_t i = 2; // index
        buf[0] = SOH;
        buf[1] = incoming;
        while(!fin){ // while not finished with the packet
          // loop through packet data
          if(available() == 0){ // if no data is ready to be read
            delay(10);
          }
          else{ // else data is ready to be read
            incoming = read();
            if(incoming == EOT){ // if reached the end of transmission character
              buf[i] = incoming;
              buf[(i+1)] = NULL;
              fin = true;
            }
            else{ // else not reached the EOT character
              buf[i] = incoming;
              ++i;
            }
          }
        }
        strcpy(_packet,buf);
        return _packet;
      }
      else{ // else dump the byte and return
        // do nothing
      }
      // recieve the rest of the packet
    }
    else{ // else dump the byte and return
      // dump the byte
    }
  }
  _packet[0] = NULL;
  return _packet;
}

char * HC12Lib::findPacket(){
  return _packet;
}

void HC12Lib::clearPacket(){
  uint8_t i = 0;
  while(_packet[i] != NULL){
    _packet[i] = NULL;
    if(i == MAX_PACKET_SIZE){ // if reached end of packet
      return;
    }
    i++;
  }
}

char HC12Lib::peek(){ // private function
  #ifdef mega
  return Serial2.peek();
  #endif

  #ifdef nano
  return ThisDev.peek();
  #endif
}

char HC12Lib::read(){ // private function
  #ifdef mega
  return Serial2.read();
  #endif

  #ifdef nano
  return ThisDev.read();
  #endif
}

void HC12Lib::write(char * pack){ // private function
  #ifdef mega
  Serial2.write(pack);
  #endif

  #ifdef nano
  ThisDev.write(pack);
  #endif
}
