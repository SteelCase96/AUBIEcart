
#include "Arduino.h"
#include "Defines.h"
#include "TxRx.h"

void tx(char to, char from, char type, uint8_t len, char payload[]){
  // - Function to send some data. The funciton must be given a destination character, a recipient character, the length of the data being 
  //    sent (max 8 bit unsigned number), and a char array payload (or data array, max 256 bytes including the null char). The maximum
  //    packet size is the max payload size (256), plus the header data (4), plus all of the extra characters (6), for a total of 265 bytes.
  //    Prior to sending the packet, a null character is attached to the packet char array.


  // prep packet
  char packet[packetMax+1];
  char packEnd[] = {char(3),char(4),char(0)};

  // form packet
  packet[0] = char(1);
  packet[1] = to;
  packet[2] = from;
  packet[3] = type;
  packet[4] = len;
  packet[5] = char(2);
  packet[6] = char(0);
  strcat(packet,payload);
  strcat(packet,packEnd);

  Serial1.write(packet); // send packet
}

char * rx(){
  /* - Function to recieve some data. Watches for the start of heading character (a.k.a. S0H or char(1)), then begins recording characters
        until the end of transmission character (a.k.a. E0T or char(4)) is read. If there is no character ready but E0T has not been reached,
        the function delays for ~ 100 ms. If the character that triggered the fuction call was NOT S0H, that character is dumped and the 
        function returns. */
  
  char packet[packetMax];
  char incoming;
  uint8_t i = 0; // index
  if(Serial1.peek() == char(1)){ // if a packet is detected
    packet[i] = Serial1.read();
    i++;
    bool fin = false;
    while(!fin){ // while packet is ongoing
      if(Serial1.available() == 0){ // if no data is ready
        delay(100);
      }else{ // if data is ready
        if(Serial1.peek() == char(4)){ // if reached end of packet
          packet[i] = Serial1.read();
          packet[(i+1)] = '\0';
          fin = true;
        }else{ // if not reached end of packet
          packet[i] = Serial1.read();
        }
        i++;
      }
    }
  }else{ // if a packet is NOT detected
      Serial1.read(); // destroy the incoming data 
      return;
  }

  char * buf = (char*)malloc(packetMax); // packet buffer to catch incoming data
  strcpy(buf,packet);
  
  if(packet[1] == myName){ // if packet is to me
    return buf;
  }else{ // if packet is NOT to me
    // dumps the packet
  }
}
