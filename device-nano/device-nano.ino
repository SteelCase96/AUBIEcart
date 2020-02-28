// Libraries

#include "Definitions.h"
#include "HC12Lib.h"

// Objects
HC12Lib HC12;

// Variables
bool diagnostics = false;
bool connectionEstablished = true;
char MyName = NULL;
uint8_t DevicesAvailable = 0;
//static char CommandBuffer[];

//void tx(char to, char type, uint8_t len, char payload[]){
//  /* - Function to send some data. The funciton must be given a destination character, the length of the data being sent (max 
//   *    8 bit unsigned number), and a char array payload (or data array, max 256 bytes including the null char). The maximum
//   *    packet size is the max payload size (256), plus the header data (4), plus all of the extra characters (6), for a total 
//   *    of 265 bytes. Prior to sending the packet, a null character is attached to the packet char array.
//   */
//
//  // prepare memory space for the packet
//  char packet[packetMax+1];
//  char packEnd[] = {char(3),char(4),char(0)};
//
//  // form packet
//  packet[0] = SOH; // 
//  packet[1] = to;
//  packet[2] = MY_NAME;
//  packet[3] = type;
//  packet[4] = len;
//  packet[5] = STX;
//  packet[6] = char(0);
//  strcat(packet,payload);
//  strcat(packet,packEnd);
//
//  HC12.write(packet); // send packet
//}
//
//char * rx(){
//  /* - Function to recieve some data. Watches for the start of heading character (a.k.a. S0H or char(1)), then begins recording 
//   *    characters until the end of transmission character (a.k.a. E0T or char(4)) is read. If there is no character ready but 
//   *    E0T has not been reached, the function delays for ~ 100 ms. If the character that triggered the fuction call was NOT S0H, 
//   *    that character is dumped and the function returns. 
//   */
//  
//  char packet[packetMax];
//  char incoming;
//  uint8_t i = 0; // index
//  if(HC12.peek() == SOH){ // if a packet is detected
//    packet[i] = HC12.read();
//    i++;
//    bool fin = false; // finish token
//    while(!fin){ // while packet is ongoing (i.e. NOT finished)
//      if(HC12.available() == 0){ // if no data is ready
//        delay(100); // wait for the rest of the data
//        // perhaps there needs to be a timeout here?
//      }else{ // if data is ready
//        if(HC12.peek() == EOT){ // if reached end of packet
//          packet[i] = HC12.read();
//          packet[(i+1)] = '\0';
//          fin = true; // finished
//        }else{ // if not reached end of packet
//          packet[i] = HC12.read();
//        }
//        i++;
//      }
//    }
//  }else{ // if a packet is NOT detected
//      HC12.read(); // destroy the incoming data 
//      return;
//  }
//
//  char * buf = (char*)malloc(packetMax); // packet buffer to catch incoming data
//  strcpy(buf,packet);
//  
//  if(packet[1] == MY_NAME){ // if packet is to me
//    return packet;
//  }else{ // if packet is NOT to me
//    return 0;
//  }
//}
//
//void packetReader(char * address){
//  
//  char packet[packetMax];
//  strcpy(packet,address);
//  free(address);
//
//  // pick out important parts of the packet
//  char to = packet[1]; // identify the packet destination
//  char from = packet[2]; // identify the packet source
//  char type = packet[3]; // identify the packet data type
//  uint8_t len = int(packet[4]); // identify the packet data length
//  char data[dataMax]; // create the data buffer
//  if(len > 0){ // if it's a regular transmission
//    uint8_t headerOffset = 0;
//    while(packet[headerOffset] != STX){ // loop until STX is reached
//      headerOffset++;
//    }
//    headerOffset++;
//    for(int i = 0; i < dataMax; i++){ // copy the data into the data buffer
//      if(packet[i+headerOffset] == ETX){
//        i = dataMax;
//        data[i] = NULL;
//      }else{
//        data[i] = packet[i+headerOffset];
//      }
//    }
//    data[len-1] = NULL; // null terminate the buffer !!! - is this needed?
//  }
//  else{ // else it's an irregular transmission 
//    
//  }
//  
//  if(from == CONSOLE_CODE){ // if it is from console
//    if(type == COMMAND_CODE){ // if is of type command
//      if(data[0] == COMMAND_SEQUENCE_CMD){ // if there is a sequence of commands
//        // place the commands in the command buffer
//      }
//      else{ // if these is NOT a sequence of commands, i.e. there is only one command
//        char commandType = data[0];
//        if(commandType == DRIVE_FORWARD_CMD){
//          char distanceStr[];
//          uint8_t i = 1;
//          while(data[i] != ETX){
//            
//          }
//          distance = makeFloat(data);
//          Serial.print("The number is: ");
//          Serial.println(distance);
//        }
//      }
//    }
//  }
//}

float makeFloat(char * data){
  float number = 0;
  uint8_t len = 0;
  uint8_t decimalLocation = 0;
  while(data[len] != NULL){
    len++;
  }
  
  for(uint8_t i = 1; i < len; i++){ // loop thru the number to find the decimal
    if(data[i] == '.'){
      decimalLocation = i;
    }
  }
  if(decimalLocation > 0){ // if there is a decimal
    for(uint8_t i = 1; i < decimalLocation; i++){ // left of decimal
      number = number + (data[i]-48)*pow(10,decimalLocation-i-2);
    }
    for(uint8_t i = decimalLocation+1; i < len; i++){ // right of decimal
      number = number + (data[i]-48)*pow(0.1,(i-decimalLocation));
    }
  }
  else{ // else there is no decimal
    for(uint8_t i = 1; i < len; i++){
      number = number + (data[i]-48)*pow(10,len-i-2);
    }
  }
  
  return number;
}

void setup() {
  Serial.begin(9600); // Serial port to computer
  Serial.println("Console starting...");
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("What is this devices code?");
  while(MyName == NULL){
    if(Serial.available()){
      MyName = Serial.read();
    }
  }
  Serial.print("This devices code has been set to: ");
  Serial.println(MyName);
  Serial.println("-------------------------"); // 25 dashes
  HC12.begin(MyName);
  while(DevicesAvailable == 0){
    // search for a device
    HC12.runBeacon();
    delay(1000); // wait for a response
    if(HC12.available() > 0){
      // read the data
    }
    
  }

//  // run the establish connection stuff here!
//  // attempt to establish a connection with the cart
//    char message[] = {ENQUIRY,'\n'};
//    tx(ROBOT_CODE,MY_NAME,ESTABLISH_CONNECTION_CODE,sizeof(message),message);
}

void loop(){
  HC12.runBeacon();
//  if(diagnostics){
//    while (HC12.available()) {        // If HC-12 has data
//      Serial.write(HC12.read());      // Send the data to Serial monitor
//    }
//    while (Serial.available()) {      // If Serial monitor has data
//      HC12.write(Serial.read());      // Send that data to HC-12
//    }
//  }
//  else{
//    while(HC12.available() > 0){
//      tempAddress = rx();
//      if(tempAddress != 0){
//        packetReader(tempAddress);
//      }
//    }
//  }
  delay(1000);
  
}
