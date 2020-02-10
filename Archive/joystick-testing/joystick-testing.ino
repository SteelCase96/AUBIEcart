#include "Joystick.h"

char buffer[50];
Joystick joystick(A0,A1,8);

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint16_t xAxis = joystick.getX();
  uint16_t yAxis = joystick.getY();
  sprintf(buffer,"X: %d, Y: %d",xAxis,yAxis);
  Serial.println(buffer);
}
