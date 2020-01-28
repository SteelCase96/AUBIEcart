/*  Version 1.1.0
 * This program is for operating the AUBIE Cart, and was developed for
 * the AUBIE Cart senior design project.
 */

// ----- Libraries -----
#include "Defines.h"
#include "Joystick.h"
#include "Motor.h"
#include "Wire.h"
#include "TxRx.h"
#include <MPU9250.h>

// ----- Definitions -----
#define encoderLpin 25
#define encoderRpin 24
#define timeout 300
#define delayTime 100

// ----- Main Variables -----
bool runDiagnostics = false;
bool joystickActive = false;
uint16_t runCount = 0;
uint16_t maxRuns = 20;
uint8_t x,y;

// ----- Object Declerations -----
Joystick joystick(A1,A0,8);
Motor motorR(enA,in1,in2,false);
Motor motorL(enB,in3,in4,false);
MPU9250 frontIMU(Wire,MPUF);
//MPU9250 rearIMU(Wire,MPUR); // not implemented

// ----- Functions -----

// - Function to take an angle, determine the correct motor directions, then drive the motors appropriately until the
//    gyroscope readings indicate that the angle has been covered.
void turnDegrees(float angle){ // unimplemented
  if(angle<0){
    // turn right
  }else if(angle>0){
    // turn left
  }else{
    // no turn
  }
}

// - Function to take a distance, determine the correct motor directions, then drive the motors appropriately until the 
//    encoder readings indicate that the distance has been covered.
void driveDistance(char direct, float distance){ // unimplemented
  // if the cart is in a hallway, the distance to each wall can be used
  // accelerometer data might also be applicable
  if(direct == 'F'){
    motorR.setDirection(1);
    motorL.setDirection(0);
    motorR.setPWM(255);
    motorL.setPWM(255);
    delay(int(distance));
    motorR.halt();
    motorL.halt();
  }
}

// - Function to take the state of the joystick, then determine and set the speed and direction of the motors.
void motorSet(uint16_t xAxis, uint16_t yAxis){
  uint8_t tempSpeed = 0;
  uint8_t speedLeft = 0;
  uint8_t speedRight = 0;
  uint8_t xMapped = 0;

  if(runDiagnostics == true){
//    sprintf(buf,"X: %d, Y: %d",xAxis,yAxis);
//    Serial.println(buf);
  }
  
  // Get the direction and speed for the motors.
  // Forward
  if(((xAxis>lowThresh)&&(xAxis<highThresh))&&(yAxis>highThresh)){
    if(runDiagnostics == true){
      Serial.println("Driving forward...");
    }
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
//      sprintf(buf,"Speed: %d",tempSpeed);
//      Serial.println(buf);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
    
  //Backward
  }else if(((xAxis>lowThresh)&&(xAxis<highThresh))&&(yAxis<lowThresh)){
    if(runDiagnostics==true){
      Serial.println("Driving backward...");
    }
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
//      sprintf(buf,"Speed: %d",tempSpeed);
//      Serial.println(buf);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
    
  // Left
  }else if(((yAxis>lowThresh)&&(yAxis<highThresh))&&(xAxis<lowThresh)){
    if(runDiagnostics==true){
      Serial.println("Rotating left...");
    }
    motorL.setDirection(-1);
    motorR.setDirection(1);
    tempSpeed = map(xAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
//      sprintf(buf,"Speed: %d",tempSpeed);
//      Serial.println(buf);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
    
  // Right
  }else if(((yAxis>lowThresh)&&(yAxis<highThresh))&&(xAxis>highThresh)){
    if(runDiagnostics==true){
      Serial.println("Rotating right...");
    }
    motorL.setDirection(1);
    motorR.setDirection(-1);
    tempSpeed = map(xAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
//      sprintf(buf,"Speed: %d",tempSpeed);
//      Serial.println(buf);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
    
  // Forward & Left
  }else if((xAxis<lowThresh)&&(yAxis>highThresh)){
    if(runDiagnostics==true){
      Serial.println("Driving left...");
    }
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed - xMapped;
    speedRight = tempSpeed + xMapped;
    if(speedLeft < 0){
      speedLeft = 0;
    }
    if(speedRight > pwmMax){
      speedRight = pwmMax;
    }
    if(runDiagnostics == true){
//      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
//      Serial.println(buf);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
    
  // Forward & Right
  }else if((xAxis>highThresh)&&(yAxis>highThresh)){
    if(runDiagnostics==true){
      Serial.println("Driving right...");
    }
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed + xMapped;
    speedRight = tempSpeed - xMapped;
    if(speedLeft > pwmMax){
      speedLeft = pwmMax;
    }
    if(speedRight < 0){
      speedRight = 0;
    }
    if(runDiagnostics == true){
//      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
//      Serial.println(buf);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
    
  // Backward & Left
  }else if((xAxis<lowThresh)&&(yAxis<lowThresh)){
    if(runDiagnostics==true){
      Serial.println("Backing left...");
    }
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed - xMapped;
    speedRight = tempSpeed + xMapped;
    if(speedLeft < 0){
      speedLeft = 0;
    }
    if(speedRight > pwmMax){
      speedRight = pwmMax;
    }
    if(runDiagnostics == true){
//      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
//      Serial.println(buf);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
    
  // Backward & Right
  }else if((xAxis>highThresh)&&(yAxis<lowThresh)){
    if(runDiagnostics==true){
      Serial.println("Backing right...");
    }
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxis,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed + xMapped;
    speedRight = tempSpeed - xMapped;
    if(speedLeft > pwmMax){
      speedLeft = pwmMax;
    }
    if(speedRight < 0){
      speedRight = 0;
    }
    if(runDiagnostics == true){
//      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
//      Serial.println(buf);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
    
  // Not moving
  }else{
    if(runDiagnostics==true){
      Serial.println("Stopping..."); 
    }
    motorL.setDirection(0);
    motorR.setDirection(0);
    
  }
}

void packetReader(char * address){
  // - Function to read/interpret a packet of data, requiring only the complete packet as a char array. This function is automatically called 
  //    upon successfully recieving a packet, and will automatically call the next necessary function that is needed to deal with the packet.

  
  char packet[packetMax];
  strcpy(packet,address);
  Serial.print("Packet: ");
  Serial.println(packet);
  free(address);
  char to = packet[1];
  char from = packet[2];
  char type = packet[2];
  uint8_t len = int(packet[4]);
  char data[dataMax];
  uint8_t headerOffset = 0;
  while(packet[headerOffset] != char(2)){
    headerOffset++;
  }
  headerOffset++;
  Serial.println(headerOffset);
  for(int i = 0; i < dataMax; i++){
    if(packet[i+headerOffset] == char(3)){
      i = dataMax;
      data[i] = '\0';
    }else{
      data[i] = packet[i+headerOffset];
    }
  }
  data[len-1] = '\0';

  Serial.print("Data is: ");
  Serial.println(data);
  
  if(from == consoleCode){ // if it is from console
    Serial.println("Is from the console...");
    if(type == commandCode){ // if is of type command
      Serial.println("Is a command...");
      char code = data[0];
      char number[10];
      for(uint8_t i = 0; i < len; i++){
        number[i] = data[i+1];
      }
      float dist = 1;
      Serial.print(number);
      Serial.print("Command is:...");
      Serial.print(code);
      Serial.print("...\n");
      switch(code){
        case forwardCode:
          driveDistance('F',dist);
          break;
        case backwardCode:
          Serial.println("Driving backward...");
          break;
        case leftCode:
          Serial.println("Rotating left...");
          break;
        case rightCode:
          Serial.println("Rotating right...");
          break;
        default:
          Serial.println("No command given...");
          break;
      }
//      Serial.println(number);
    }else if(type == infoCode){
      char code = data[0];
      switch(code){
        case frontIMUcode:
          Serial.println("Front IMU...");
          break;
        case backIMUcode:
          Serial.println("Back IMU...");
          break;
        case leftEncoderCode:
          Serial.println("Left encoder...");
          break;
        case rightEncoderCode:
          Serial.println("Right encoder...");
          break;
        default:
          Serial.println("No device given...");
          break;
      }
    }
  }
}

unsigned long encoderCheck(){
  unsigned long pulseR = pulseIn(encoderRpin,HIGH,timeout);
  unsigned long pulseL = pulseIn(encoderLpin,HIGH,timeout);
  return (pulseR + pulseL) / 2; // cast the calculated average to an unsigned long then return it
}

void setup(){
  Serial1.begin(9600);
  Serial1.println("Starting...");

  // Start the front gyroscope, reporting the success or failure to the console
  if(frontIMU.begin() < 0){ // if it failed
    char message[] = {errorCode,frontIMUcode,'\0'};
    tx(consoleCode,myName,infoCode,sizeof(message),message);
    // add an LED that can be activated when there is an error
    while(true){} // stops the program from continuing
  }else{ // if it didn't fail
    char message[] = {successCode,frontIMUcode,'\0'};
    tx(consoleCode,myName,infoCode,sizeof(message),message);
  }

  Serial1.print("Time: ");
  Serial1.println(millis());
  
  pinMode(encoderLpin,INPUT_PULLUP);
  pinMode(encoderRpin,INPUT_PULLUP);
  motorL.setDirection(1);
  motorR.setDirection(1);
  motorL.setPWM(255);
  motorR.setPWM(255);
}

void loop(){
  x = joystick.getX();
  y = joystick.getY();
  motorSet(x,y);
  Serial1.print(millis());
  Serial1.print(",");
  Serial1.print(x);
  Serial1.print(",");
  Serial1.print(y);
  Serial1.print(",");
  Serial1.print(pulseIn(24,HIGH,300));
  Serial1.print(",");
  Serial1.println(pulseIn(25,HIGH,300));
  delay(delayTime);
  
//    // read and print data
//    frontIMU.readSensor();
//
//    // old method - replace
//    Serial1.print(runCount);
//    Serial1.print(",");
//    Serial1.print(millis());
//    Serial1.print(",");
//    Serial1.print(frontIMU.getGyroX_rads(),6);
//    Serial1.print(",");
//    Serial1.print(frontIMU.getGyroY_rads(),6);
//    Serial1.print(",");
//    Serial1.println(frontIMU.getGyroZ_rads(),6);

}
