/*  Version 1.0.9
 * This program is for operating the AUBIE Cart, and was developed for
 * the AUBIE Cart senior design project.
 */


// ----- Libraries -----
#include "Joystick.h"
#include "Motor.h"

// ----- Definitions -----
// - Speed/PWM Threshold -
#define pwmThresh 0
#define pwmMax 255
// - Joystick Thresholds -
#define lowThresh 470
#define highThresh 553
#define minThresh 0
#define maxThresh 1023
// --- Pin Definitions ---
// - Left Motor -
#define enB 10
#define in3 6
#define in4 7
// - Right Motor -
#define enA 9
#define in1 4
#define in2 5


// ----- Main Variables -----
char buf[50];
bool runDiagnostics = true;
uint16_t runCount = 0;

// ----- Object Declerations -----
Joystick joystick(A1,A0,8);
Motor motorR(enA,in1,in2,false);
Motor motorL(enB,in3,in4,false);
// ----- Functions -----

// - From the joystick axis values, determine and set the speed and direction of the motors.
void motorSet(uint16_t xAxis, uint16_t yAxis){
  uint8_t tempSpeed = 0;
  uint8_t speedLeft = 0;
  uint8_t speedRight = 0;
  uint8_t xMapped = 0;

  if(runDiagnostics == true){
    sprintf(buf,"X: %d, Y: %d",xAxis,yAxis);
    Serial.println(buf);
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
      sprintf(buf,"Speed: %d",tempSpeed);
      Serial.println(buf);
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
      sprintf(buf,"Speed: %d",tempSpeed);
      Serial.println(buf);
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
      sprintf(buf,"Speed: %d",tempSpeed);
      Serial.println(buf);
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
      sprintf(buf,"Speed: %d",tempSpeed);
      Serial.println(buf);
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
      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
      Serial.println(buf);
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
      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
      Serial.println(buf);
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
      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
      Serial.println(buf);
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
      sprintf(buf,"L: %d, R: %d",speedLeft,speedRight);
      Serial.println(buf);
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

void setup() {
  Serial.begin(9600);
  if(runDiagnostics==true){
    Serial.println("Starting program...");
  }
}

void loop() {
  if(runDiagnostics==true){
    sprintf(buf,"Run Counter: %d",runCount);
    Serial.println(buf);
  }
  motorSet(joystick.getX(),joystick.getY());
  runCount++;
  delay(200);
}
