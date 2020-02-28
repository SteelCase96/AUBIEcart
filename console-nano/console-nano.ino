// Libraries
#include "Definitions.h"
#include "HC12Lib.h"

#define console
#define diagnostics

#ifdef tester
const char MyName = 'C';
#endif

#ifdef cart
const char MyName = 'R';
#endif

#ifdef console
const char MyName = 'C';
#endif

// Objects
HC12Lib HC12(MyName);

// Variables
static bool JoystickActive = false;
static bool ConnectionEstablished = false;
static bool CommandAvailable = false;
static char ConnectedDeviceName;
static char CommandBuffer[COMMAND_BUF_MAX_SIZE];

void setup(){
  #ifdef tester
  HC12.begin();
  Serial.begin(9600);
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Test starting...");
  Serial.println("-------------------------"); // 25 dashes
  activityMenu();
  #endif
  
  #ifdef cart
  HC12.begin();
  ConnectedDeviceName = HC12.establishConnection(false);
  #ifdef diagnostics
  Serial.begin(9600);
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Cart starting...");
  Serial.print("Connection established with device: ");
  Serial.println(ConnectedDeviceName);
  Serial.println("-------------------------"); // 25 dashes
  #endif
  #endif

  #ifdef console
  HC12.begin();
  ConnectedDeviceName = HC12.establishConnection(true);
  #ifdef diagnostics
  Serial.begin(9600); // Serial port to computer
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Console starting...");
  Serial.print("Connection established with device: ");
  Serial.println(ConnectedDeviceName);
  #endif
  activityMenu();
  #endif
} 

void loop(){
  #ifdef tester
  activitySelection();
  delay(1000);
  #endif
  
  #ifdef cart
  if(HC12.available() > 0){ // if there's data to be read
    char * address = HC12.rxData();
    if(address[0] != NULL){ // if some data was received
      packetReader(address); // read the packet, and take whatever action is needed
    }
    else{
      cartActivity();
    }
  }
  else{
    cartActivity();
  }
  #endif

  #ifdef console
  activitySelection();
  delay(1000);
  #endif
}

#ifdef cart
void cartActivity(){
  if(JoystickActive){ // else if in joystick mode
    // call motorSet function here
  }
  else if(CommandAvailable){ // else if in command mode
    runCommandBuffer();
  }
  else{ // do nothing
    delay(1000);
  }
}
#endif

void activityMenu(){
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Commands Available:");
  Serial.println("\t- Toggle Joystick Mode (J)"); // TOGGLE_JOYSTICK_CMD
  Serial.println("\t- Halt (H)"); // HALT_CMD
  Serial.println("\t- Drive Forward (F)"); // DRIVE_FORWARD_CMD
  Serial.println("\t- Drive Backward (B)"); // DRIVE_BACKWARD_CMD
  Serial.println("\t- Turn Left (L)"); // TURN_LEFT_CMD
  Serial.println("\t- Turn Right (R)"); // TURN_RIGHT_CMD
  Serial.println("\t- Command Sequence (C) !!! DO NOT USE"); // COMMAND_SEQUENCE_CMD
  Serial.println("-------------------------"); // 25 dashes
  return;
}

void activitySelection(){
  Serial.println("Select a command.");
  
  char buf[6];
  char commandToSend = NULL;
  while(commandToSend == NULL){
    if(Serial.available() > 0){
      commandToSend = Serial.read();
      delay(10);
      Serial.read();
    }
  }
  buf[0] = commandToSend;
  
  if(commandToSend == TOGGLE_JOYSTICK_CMD || commandToSend == HALT_CMD){
    buf[1] = NULL;
  }
  else if(commandToSend == DRIVE_FORWARD_CMD || commandToSend == DRIVE_BACKWARD_CMD){
    bool fin = false; // loop token
    Serial.println("How far to drive in feet? (max = 999)");
    while(!fin){
      if(Serial.available()){
        uint8_t i = 1;
        while(Serial.available() > 0){
          char incoming = Serial.read();
          if(incoming != '\n'){
            buf[i] = incoming;
            ++i;
            delay(10);
          }
        }
        fin = true;
        buf[i] = '.';
        buf[i+1] = NULL;
        delay(10);
        Serial.read();
      }
    }
  }
  else if(commandToSend == TURN_LEFT_CMD || commandToSend == TURN_RIGHT_CMD){
    bool fin = false; // loop token
    Serial.println("How far to drive in feet? (max = 999)");
    while(!fin){
      if(Serial.available()){
        uint8_t i = 1;
        while(Serial.available() > 0){
          char incoming = Serial.read();
          if(incoming != '\n'){
            buf[i] = incoming;
            ++i;
            delay(10);
          }
        }
        fin = true;
        buf[i] = '.';
        buf[i+1] = NULL;
        delay(10);
        Serial.read();
      }
    }
  }
  else if(commandToSend == COMMAND_SEQUENCE_CMD){
    Serial.println("Nothing to do here yet...");
  }
  else{ // else error
    Serial.println("Something went wrong here...");
  }

  Serial.print("Sending command: ");
  Serial.println(buf);
  Serial.println("-------------------------"); // 25 dashes

  HC12.txPacket(ConnectedDeviceName,COMMAND_CODE,buf);
  
  return;
}

void packetReader(char * address){
  /* - Function to read a packet of data. It looks at the first character of the data, and will 
   *    automatically call the next necessary function that is needed to deal with the data. 
   */
  
  char to = address[1];
  char from = address[2];
  char type = address[3];
  uint8_t len = (int)address[4];
  char cmd = address[6];

  #ifdef diagnostics
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("The packet was to: ");
  Serial.println(address[1]);
  Serial.print("The packet was from: ");
  Serial.println(address[2]);
  Serial.print("The type of packet was: ");
  Serial.println(address[3]);
  Serial.print("The length of the data was: ");
  Serial.println((int)address[4]);
  Serial.print("The command was to: ");
  Serial.println(cmd);
  if(cmd == COMMAND_SEQUENCE_CMD){
    uint8_t cmdLen = 1;
    Serial.print("Command sequence length was: ");
    Serial.println(cmdLen);
  }
  Serial.println("-------------------------"); // 25 dashes
  #endif
  
  commandTree(address+6);
  HC12.clearPacket();
  
  return;
}

void commandTree(char * address){
  /* - This function takes as an argument the address of the command string to be read,
   *    reads the first character, calls the appropriate function, handing an offset
   *    address if needed.
   */
  char cmd = address[0];
  switch(cmd){
    case TOGGLE_JOYSTICK_CMD:
      toggleJoystick();
      break;
    case HALT_CMD:
      haltAll();
      break;
    case DRIVE_FORWARD_CMD:
      driveForward(makeFloat(address+1));
      break;
    case DRIVE_BACKWARD_CMD:
      driveBackward(makeFloat(address+1));
      break;
    case TURN_LEFT_CMD:
      turnLeft(makeFloat(address+1));
      break;
    case TURN_RIGHT_CMD:
      turnRight(makeFloat(address+1));
      break;
    case COMMAND_SEQUENCE_CMD:
      readIntoCommandBuffer(address+1);
      break;
    default:
      #ifdef diagnostics
      Serial.println("Something is missing here...");
      #endif
      break;
  }
  return;
}

void runCommandBuffer(){ // does nothing - work in progress
  delay(1000);
}

float makeFloat(char * address){
  /* - Function to calculate a floating point number from its string representation.
   *    Takes a pointer to the char array containing the number and the starting position
   *    of the number as arguments. Works by first looping through the char array to find
   *    the location of the decimal and the end of the number. The end of the number is 
   *    signified by encountering a character having a decimal representation that is
   *    outside the range of the numbers (48 to 57).
   */
  
  #ifdef diagnostics
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Function makeFloat called");
  Serial.println("-------------------------"); // 25 dashes
  #endif
  
  // function varablies
  float number = 0;
  uint8_t endLocation = 0;
  uint8_t decimalLocation = 0;

  // find number bounds
  // loop variables
  bool fin = false; // loop token
  uint8_t i = 0; // index
  // loop
  while(!fin){
    uint8_t nextChar = (uint8_t)address[i];
    #ifdef diagnostics
    Serial.print("\t");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(nextChar);
    #endif
    if(nextChar == 46){ // 46 is the ascii representation of the period character
      decimalLocation = i;
      ++i;
    }
    else if(nextChar < 48 || nextChar > 57){ // the decimal numbers 0 - 9 ascii representations fall within the range of 48 - 57
      fin = true;
      endLocation = i-1;
    }
    else{
      ++i;
    }
  }

  // constuct number
  if(decimalLocation == 0){
    for(uint8_t i = 1; i < endLocation+1; i++){
      number += (address[i]-48)*pow(0.1,i-decimalLocation);
    }
  }
  else{
    for(uint8_t i = 0; i < decimalLocation; i++){
      number += (address[i]-48)*pow(10,decimalLocation-i-1);
    }
    for(uint8_t i = decimalLocation+1; i <= endLocation; i++){
      number += (address[i]-48)*pow(0.1,i-decimalLocation);
    }
  }
  
  #ifdef diagnostics
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("\tNumber = ");
  Serial.println(number);
  Serial.println("-------------------------"); // 25 dashes
  #endif
  
  // return
  return number;
}

void readIntoCommandBuffer(char * address){
  bool fin = false; // loop token
  uint8_t i = 0; // index
  const uint8_t offset = 7; // the location of the first character in the sequence of commands
  while(!fin){
    if(address[i+offset] == ETX){
      fin = true; 
    }
    CommandBuffer[i] = address[i+offset];
  }
  return;
}

void driveForward(float distance){
  #ifdef diagnostics
  Serial.print("The distance to drive forward is ");
  Serial.println(distance);
  #endif
  return;
}

void driveBackward(float distance){
  #ifdef diagnostics
  Serial.print("The distance to drive backward is ");
  Serial.println(distance);
  Serial.println("-------------------------"); // 25 dashes
  #endif
  return;
}

void turnLeft(float angle){
  #ifdef diagnostics
  Serial.print("The angle to turn left is ");
  Serial.println(angle);
  Serial.println("-------------------------"); // 25 dashes
  #endif
  return;
}

void turnRight(float angle){
  #ifdef diagnostics
  Serial.print("The angle to turn right is ");
  Serial.println(angle);
  Serial.println("-------------------------"); // 25 dashes
  #endif
  return;
}

void haltAll(){
  #ifdef diagnostics
  Serial.println("Halting the cart.");
  Serial.println("-------------------------"); // 25 dashes
  #endif
  return;
}

void toggleJoystick(){
  JoystickActive = !JoystickActive;
  #ifdef diagnostics
  Serial.print("Joystick Mode ");
  if(JoystickActive){
    Serial.println("on");
  }else{
    Serial.println("off");
  }
  Serial.println("-------------------------"); // 25 dashes
  #endif
  return;
}
