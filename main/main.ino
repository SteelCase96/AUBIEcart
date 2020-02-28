#define diagnostics

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
bool runDiagnostics = false;
bool joystickActive = false;
uint16_t runCount = 0;
uint16_t x = 512, y;

// encoder stuff
uint32_t leftEncoderPeriodSUM = 0;
uint16_t leftEncoderPeriodAVG = 0;
uint32_t rightEncoderPeriodSUM = 0;
uint16_t rightEncoderPeriodAVG = 0;

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

void setup(){
  Serial1.begin(9600);
  if(runDiagnostics){
    Serial1.println("-------------------------"); // 25 dashes
    Serial1.println("Starting cart...");
    Serial1.print("\tInitial time: ");
    Serial1.println(millis());
  }

  #ifdef diagnostics
  Serial.begin(9600);
  Serial.println("-------------------------"); // 25 dashes
  Serial.println("Starting cart...");
  Serial.print("\tInitial time: ");
  Serial.println(millis());
  #endif

  // clear the timer 5 control register to prepare it for use by the encoders
  TCCR5A = 0;
  TCCR5B = 0;

  // Start the front gyroscope, reporting the status to the console
  if(frontIMU.begin() < 0){ // if it failed to start
    char message[] = {FRONT_IMU_CODE,ERROR_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(true){blinkErrorLED();} // stops the program from continuing
  }else{ // if it didn't fail
    char message[] = {FRONT_IMU_CODE,SUCCESS_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // Start the left encoder, reporting the status to the console
  if(encoderL.beginEncoder() < 0){ // if it failed to start
    char message[] = {LEFT_ENCODER_CODE,ERROR_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(1){blinkErrorLED();}
  }else{
    char message[] = {LEFT_ENCODER_CODE,SUCCESS_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // start the right encoder, reporting the status to the console
  if(encoderR.beginEncoder() < 0){ // if it failed to start
    char message[] = {RIGHT_ENCODER_CODE,ERROR_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
    while(1){blinkErrorLED();}
  }else{
    char message[] = {RIGHT_ENCODER_CODE,SUCCESS_CODE,'\0'};
//    tx(CONSOLE_CODE,MY_NAME,STATUS_CODE,sizeof(message),message);
  }

  // left encoder ISR setup
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_CHA),leftEncoderISR,RISING);
  // right encoder ISR setup
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_CHA),rightEncoderISR,RISING);

  #ifdef diagnostics
  Serial.print("\tSetup time: ");
  Serial.println(millis());
  Serial.println("-------------------------"); // 25 dashes
  #endif
  
  if(runDiagnostics){
    Serial1.println("Startup complete...");
    Serial1.print("\tTime: ");
    Serial1.println(millis());
    Serial1.println("-------------------------------");
  }
}

// test code block selector
uint8_t block = 4;
void loop(){
  if(joystickActive){ // joystick control section
    motorSet(joystick.getX(),joystick.getY());
    delay(delayTime);
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
  else if(block == 3){ // an encoder test
    motorL.setPWM(229);
    motorR.setPWM(255);
    motorR.setDirection(1);
    motorL.setDirection(1);
    for(uint8_t i = 0; i < 40; i++){
      Serial1.print(millis());
      Serial1.print(", L Count: ");
      Serial1.print(encoderL.getLastCount());
      Serial1.print(", L Period: ");
      uint16_t leftPeriod = encoderL.getLastPeriod();
      leftEncoderPeriodSUM += leftPeriod;
      Serial1.print(leftPeriod);
      Serial1.print(", R Count: ");
      Serial1.print(encoderR.getLastCount());
      uint16_t rightPeriod = encoderR.getLastPeriod();
      rightEncoderPeriodSUM += rightPeriod;
      Serial1.print(", R Period: ");
      Serial1.println(rightPeriod);
      delay(50);
    }
    motorR.halt();
    motorL.halt();
    leftEncoderPeriodAVG = leftEncoderPeriodSUM / 40;
    rightEncoderPeriodAVG = rightEncoderPeriodSUM / 40;
    Serial1.println("-------------------------------");
    Serial1.print("L AVG: ");
    Serial1.print(leftEncoderPeriodAVG);
    Serial1.print(", R AVG: ");
    Serial1.println(rightEncoderPeriodAVG);
    Serial1.println("-------------------------------");
    while(1){} // stop from going any further
  }
  else if(block == 4){ // drive forward test
    driveForward(15); // drive 5.5 feet, or 66 inches
    Serial.println("Done...");
    Serial.println("-------------------------"); // 25 dashes
    while(1){} // do not let the cart proceed
  }
}

void driveForward(float distance){
 /* - Function to drive the cart forward by the amount distance.
  */
  // diagnostics opening report
  #ifdef diagnostics
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("Driving forward ");
  Serial.print(distance);
  Serial.println(" feet.\n");
  Serial.print("\tStart time: ");
  Serial.println(millis());
  #endif

  // function variables
  bool fin = false; // loop token
  bool started = false; // motors started token
  float distanceTraveled = 0;
  uint16_t newLCount = 0;
  uint16_t lastLCount = encoderL.getLastCount();
  uint16_t deltaLCount = 0;
  uint16_t newRCount = 0;
  uint16_t lastRCount = encoderR.getLastCount();
  uint16_t deltaRCount = 0;
  uint16_t avgDeltaCount = 0;

  // loop
  while(!fin){ // while not finished
    if(distanceTraveled >= distance){ // if you've traveled the distance
      // halt the motors
      // reverse them for 300 ms first to prevent it from going to far
      motorR.setDirection(-1);
      motorL.setDirection(-1);
      delay(300);
      motorR.halt();
      motorL.halt();
      fin = !fin; // flip loop token
    }
    else{ // else you've not traveled the distance
      if(!started){ // if motors have not been started
        // to get to a destination or angle, use drive or turn, respectively
        // perhaps add functions in here to:
        // * start then go to max - how long does it take to 
        // * run for some time 
        // * slow to stop - how long does it take to slow down while approaching the destination?
        motorR.setPWM(255);
        motorL.setPWM(255);
        motorR.setDirection(1);
        motorL.setDirection(1);
        started = !started;
      }
      // calculate distanceTraveled
      // 1. get the change (or delta) of the average encoder count
      // 2. distance traveled = delta avg count / COUNTS_PER_FOOT
      newLCount = encoderL.getLastCount();
      newRCount = encoderR.getLastCount();
      if(lastLCount > newLCount){ // if there was an overflow
        deltaLCount = (65535 - lastLCount) + newLCount;
      }
      else{ // else no overflow, calculate delta in normal manner
        deltaLCount = newLCount - lastLCount;
      }
      if(lastRCount > newRCount){ // if there was an overflow
        deltaRCount = (65535 - lastRCount) + newRCount;
      }
      else{ // else no overflow, calculate delta in normal manner
        deltaRCount = newRCount - lastRCount;
      }
      avgDeltaCount = (deltaRCount + deltaLCount)/2; // average left & right counts
      // now calculate distance traveled
      distanceTraveled += (float)avgDeltaCount / COUNTS_PER_FOOT; // distance traveled in feet
      lastLCount = newLCount;
      lastRCount = newRCount;
    }
  }

  // diagnostics ending report
  #ifdef diagnostics
  Serial.print("\nI think I've traveled ");
  Serial.print(distanceTraveled);
  Serial.println(" feet.");
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("\tEnd time: ");
  Serial.println(millis());
  #endif

  return;
}

void driveBackward(float distance){
  // diagnostics opening report
  #ifdef diagnostics
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("Driving backward ");
  Serial.print(distance);
  Serial.println(" feet.\n");
  Serial.print("\tStart time: ");
  Serial.println(millis());
  #endif

  // function variables
  bool fin = false; // loop token
  bool started = false; // motors started token
  float distanceTraveled = 0;
  uint16_t newLCount = 0;
  uint16_t lastLCount = encoderL.getLastCount();
  uint16_t deltaLCount = 0;
  uint16_t newRCount = 0;
  uint16_t lastRCount = encoderR.getLastCount();
  uint16_t deltaRCount = 0;
  uint16_t avgDeltaCount = 0;

  // loop
  while(!fin){ // while not finished
    if(distanceTraveled >= distance){ // if you've traveled the distance
      // halt the motors
      // reverse them for 300 ms first to prevent it from going to far
      motorR.setDirection(1);
      motorL.setDirection(1);
      delay(300);
      motorR.halt();
      motorL.halt();
      fin = !fin; // flip loop token
    }
    else{ // else you've not traveled the distance
      if(!started){ // if motors have not been started
        // to get to a destination or angle, use drive or turn, respectively
        // perhaps add functions in here to:
        // * start then go to max - how long does it take to 
        // * run for some time 
        // * slow to stop - how long does it take to slow down while approaching the destination?
        motorR.setPWM(255);
        motorL.setPWM(255);
        motorR.setDirection(-1);
        motorL.setDirection(-1);
        started = !started;
      }
      // calculate distanceTraveled
      // 1. get the change (or delta) of the average encoder count
      // 2. distance traveled = delta avg count / COUNTS_PER_FOOT
      newLCount = encoderL.getLastCount();
      newRCount = encoderR.getLastCount();
      if(lastLCount > newLCount){ // if there was an overflow
        deltaLCount = (65535 - lastLCount) + newLCount;
      }
      else{ // else no overflow, calculate delta in normal manner
        deltaLCount = newLCount - lastLCount;
      }
      if(lastRCount > newRCount){ // if there was an overflow
        deltaRCount = (65535 - lastRCount) + newRCount;
      }
      else{ // else no overflow, calculate delta in normal manner
        deltaRCount = newRCount - lastRCount;
      }
      avgDeltaCount = (deltaRCount + deltaLCount)/2; // average left & right counts
      // now calculate distance traveled
      distanceTraveled += (float)avgDeltaCount / COUNTS_PER_FOOT; // distance traveled in feet
      lastLCount = newLCount;
      lastRCount = newRCount;
    }
  }

  // diagnostics ending report
  #ifdef diagnostics
  Serial.print("\nI think I've traveled ");
  Serial.print(distanceTraveled);
  Serial.println(" feet.");
  Serial.println("-------------------------"); // 25 dashes
  Serial.print("\tEnd time: ");
  Serial.println(millis());
  #endif
  
  return;
}

void turnLeft(float angle){
  // function variables
  bool fin = false; // loop token
  bool started = false; // motors started token
  float angleTurned = 0;
  float rate = 0;

  while(!fin){
    if(angleTurned >= angle){
      // halt the motors
    }
    else{
      if(!started){
        // start the motors
      }
    }
  }
}

void leftEncoderISR(){
  encoderL.measureISR();
}

void rightEncoderISR(){
  encoderR.measureISR();
}
