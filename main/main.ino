/*  Version 1.1.0
 * This program is for operating the AUBIE Cart, and was developed for
 * the AUBIE Cart senior design project.
 */

// ----- Libraries -----
#include "Defines.h"
#include "Joystick.h"
#include "Motor.h"
#include "Wire.h"
#include "TxRx.h" // replace with an HC12 library or an EPS library
#include "Encoder.h"
#include <MPU9250.h>

// ----- Definitions -----
#define delayTime 100
#define maxRuns 30

// ----- Main Variables -----
bool errorLEDstate = LOW;
bool runDiagnostics = true;
//bool joystickActive = false;
uint16_t runCount = 0;
uint16_t x = 512, y;

// ----- Object Declerations -----
Joystick joystick(vrx,vry,swi);
Motor motorR(enA,in1,in2,false);
Motor motorL(enB,in3,in4,false);
MPU9250 frontIMU(Wire,MPUF);
//MPU9250 rearIMU(Wire,MPUR); // not implemented
Encoder encoderL(LEFT_ENCODER_CHA,LEFT_ENCODER_CHB);
Encoder encoderR(RIGHT_ENCODER_CHA,RIGHT_ENCODER_CHB);

// ----- Functions -----

void blinkErrorLED(){
  /* - Function to change the state of an LED then wait a half second. This function is typically used in a while loop that
          runs indefinitely. */
  errorLEDstate = !errorLEDstate;
  delay(500);
}

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
  uint16_t xAxisP = map(xAxis,0,1023,1023,0);
  uint8_t tempSpeed = 0;
  uint8_t speedLeft = 0;
  uint8_t speedRight = 0;
  uint8_t xMapped = 0;

  if(runDiagnostics){
    Serial1.print("X: ");
    Serial1.print(xAxisP);
    Serial1.print(", Y: ");
    Serial1.println(yAxis);
  }
  
  // Get the direction and speed for the motors.
  // Forward
  if(((xAxisP>lowThresh)&&(xAxisP<highThresh))&&(yAxis>highThresh)){
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
      Serial1.println("Driving forward...");
      Serial1.print("Speed: ");
      Serial1.println(tempSpeed);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
    
  
  }
  //Backward
  else if(((xAxisP>lowThresh)&&(xAxisP<highThresh))&&(yAxis<lowThresh)){
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
      Serial1.println("Driving backward...");
      Serial1.print("Speed: ");
      Serial1.println(tempSpeed);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
  }
  // Left
  else if(((yAxis>lowThresh)&&(yAxis<highThresh))&&(xAxisP<lowThresh)){
    motorL.setDirection(-1);
    motorR.setDirection(1);
    tempSpeed = map(xAxisP,lowThresh,minThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
      Serial1.println("Rotating left...");
      Serial1.print("Speed: ");
      Serial1.println(tempSpeed);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
  }
  // Right
  else if(((yAxis>lowThresh)&&(yAxis<highThresh))&&(xAxisP>highThresh)){
    motorL.setDirection(1);
    motorR.setDirection(-1);
    tempSpeed = map(xAxisP,highThresh,maxThresh,pwmThresh,pwmMax);
    if(runDiagnostics == true){
      Serial1.println("Rotating right...");
      Serial1.print("Speed: ");
      Serial1.println(tempSpeed);
    }
    motorL.setPWM(tempSpeed);
    motorR.setPWM(tempSpeed);
  }
  // Forward & Left
  else if((xAxisP<lowThresh)&&(yAxis>highThresh)){
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxisP,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed - xMapped;
    speedRight = tempSpeed + xMapped;
    if(speedLeft < 0){
      speedLeft = 0;
    }
    if(speedRight > pwmMax){
      speedRight = pwmMax;
    }
    if(runDiagnostics == true){
      Serial1.println("Driving left...");
      Serial1.print("Speed L: ");
      Serial1.print(speedLeft);
      Serial1.print(", Speed R: ");
      Serial1.println(speedRight);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
  }
  // Forward & Right
  else if((xAxisP>highThresh)&&(yAxis>highThresh)){
    motorL.setDirection(1);
    motorR.setDirection(1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxisP,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed + xMapped;
    speedRight = tempSpeed - xMapped;
    if(speedLeft > pwmMax){
      speedLeft = pwmMax;
    }
    if(speedRight < 0){
      speedRight = 0;
    }
    if(runDiagnostics == true){
      Serial1.println("Driving right...");
      Serial1.print("Speed L: ");
      Serial1.print(speedLeft);
      Serial1.print(", Speed R: ");
      Serial1.println(speedRight);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
  }
  // Backward & Left
  else if((xAxisP<lowThresh)&&(yAxis<lowThresh)){
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxisP,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed - xMapped;
    speedRight = tempSpeed + xMapped;
    if(speedLeft < 0){
      speedLeft = 0;
    }
    if(speedRight > pwmMax){
      speedRight = pwmMax;
    }
    if(runDiagnostics == true){
      Serial1.println("Backing left...");
      Serial1.print("Speed L: ");
      Serial1.print(speedLeft);
      Serial1.print(", Speed R: ");
      Serial1.println(speedRight);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
  }
  // Backward & Right
  else if((xAxisP>highThresh)&&(yAxis<lowThresh)){
    motorL.setDirection(-1);
    motorR.setDirection(-1);
    tempSpeed = map(yAxis,highThresh,maxThresh,pwmThresh,pwmMax);
    xMapped = map(xAxisP,lowThresh,minThresh,pwmThresh,pwmMax);
    speedLeft = tempSpeed + xMapped;
    speedRight = tempSpeed - xMapped;
    if(speedLeft > pwmMax){
      speedLeft = pwmMax;
    }
    if(speedRight < 0){
      speedRight = 0;
    }
    if(runDiagnostics == true){
      Serial1.println("Backing right...");
      Serial1.print("Speed L: ");
      Serial1.print(speedLeft);
      Serial1.print(", Speed R: ");
      Serial1.println(speedRight);
    }
    motorL.setPWM(speedLeft);
    motorR.setPWM(speedRight);
  }
  // Not moving
  else{
    if(runDiagnostics==true){
      Serial1.println("Stopping..."); 
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
  
  if(from == CONSOLE_CODE){ // if it is from console
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
        case FRONT_IMU_CODE:
          Serial.println("Front IMU...");
          break;
        case BACK_IMU_CODE:
          Serial.println("Back IMU...");
          break;
        case LEFT_ENCODER_CODE:
          Serial.println("Left encoder...");
          break;
        case RIGHT_ENCODER_CODE:
          Serial.println("Right encoder...");
          break;
        default:
          Serial.println("No device given...");
          break;
      }
    }
  }
}

void setup(){
  Serial1.begin(9600);
  if(runDiagnostics){
    Serial1.println("-------------------------------");
    Serial1.println("Starting...");
    Serial1.print("Time: ");
    Serial1.println(millis());
  }

  // Start the front gyroscope, reporting the status to the console
  if(frontIMU.begin() < 0){ // if it failed to start
    char message[] = {FRONT_IMU_CODE,ERROR_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(true){blinkErrorLED();} // stops the program from continuing
  }else{ // if it didn't fail
    char message[] = {FRONT_IMU_CODE,SUCCESS_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // Start the left encoder, reporting the status to the console
  if(encoderL.beginEncoder() < 0){ // if it failed to start
    char message[] = {LEFT_ENCODER_CODE,ERROR_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(1){blinkErrorLED();}
  }else{
    char message[] = {LEFT_ENCODER_CODE,SUCCESS_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // start the right encoder, reporting the status to the console
  if(encoderR.beginEncoder() < 0){ // if it failed to start
    char message[] = {RIGHT_ENCODER_CODE,ERROR_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(1){blinkErrorLED();}
  }else{
    char message[] = {RIGHT_ENCODER_CODE,SUCCESS_CODE,'\0'};
    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // timer setup
  noInterrupts();
  TCCR5A = 0;
  TCCR5B = 0;
  TCNT5 = 0;
  interrupts();
  TCCR5B |= (1<<CS50);

  
  // left encoder ISR setup
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_CHA),leftEncoderISR,RISING);
  // right encoder ISR setup
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_CHA),rightEncoderISR,RISING);
  
  if(runDiagnostics){
    Serial1.println("\nStartup complete...");
    Serial1.print("Time: ");
    Serial1.println(millis());
    Serial1.println("-------------------------------");
  }
}

// test code block selector
uint8_t block = 3;
void loop(){
  if(block == 0){ // drive test w/ reducing speed
    
  }
  else if(block == 1){ // gyro testing
    // read and print data
    frontIMU.readSensor();

    // old method - replace
    Serial1.print(runCount);
    Serial1.print(",");
    Serial1.print(millis());
    Serial1.print(",");
    Serial1.print(frontIMU.getGyroX_rads(),6);
    Serial1.print(",");
    Serial1.print(frontIMU.getGyroY_rads(),6);
    Serial1.print(",");
    Serial1.println(frontIMU.getGyroZ_rads(),6);
  }
  else if(block == 2){ // encoder testing
    Serial1.print(millis());
    Serial1.print(", L Count: ");
    Serial1.print(encoderL.getLastCount());
    Serial1.print(", L Period: ");
    Serial1.print(encoderL.getLastPeriod());
    Serial1.print(", R Count: ");
    Serial1.print(encoderR.getLastCount());
    Serial1.print(", R Period: ");
    Serial1.println(encoderR.getLastCount());
    delay(100);
  }
  else if(block == 3){
    motorL.setPWM(230);
    motorR.setPWM(255);
    motorR.setDirection(1);
    motorL.setDirection(1);
    for(uint8_t i = 0; i < 20; i++){
      Serial1.print(millis());
      Serial1.print(", L Count: ");
      Serial1.print(encoderL.getLastCount());
      Serial1.print(", L Period: ");
      Serial1.print(encoderL.getLastPeriod());
      Serial1.print(", R Count: ");
      Serial1.print(encoderR.getLastCount());
      Serial1.print(", R Period: ");
      Serial1.println(encoderR.getLastPeriod());
      delay(50);
    }
    motorR.halt();
    motorL.halt();
    while(1){} // stop from going any further
  }
}

void leftEncoderISR(){
  encoderL.measureISR();
}

void rightEncoderISR(){
  encoderR.measureISR();
}
