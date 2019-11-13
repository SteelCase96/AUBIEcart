
// ----- Libraries -----
#include <Joystick.h>

// ----- Pin Definitions -----
#define enA 9
#define enB 10
#define in1 4
#define in2 5
#define in3 6
#define in4 7

// ----- Main Variables -----
char buffer[50];
byte motorSpeedA = 0;
byte motorSpeedB = 0;

Joystick joystick(A0,A1,8);

void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);

//  // Pin Setup
//  pinMode(enA,OUTPUT);
//  pinMode(enB,OUTPUT);
//  pinMode(in1,OUTPUT);
//  pinMode(in2,OUTPUT);
//  pinMode(in3,OUTPUT);
//  pinMode(in4,OUTPUT);

  // Object Declerations
  
}

void loop() {
  joystick.read();
  sprintf(buffer,"X: %d, Y: %d",joystick.getX(),joystick.getY());
  Serial.println(buffer);
//  Serial.print("X Axis: ");
////  Serial.print(joystick.getX());
//  Serial.print(", ");
//  Serial.println(analogRead(A0));
//  Serial.print("Y Axis: ");
////  Serial.print(joystick.getY());
//  Serial.print(", ");
//  Serial.println(analogRead(A1));
  delay(200);
}

void sendReport(){
  
}
