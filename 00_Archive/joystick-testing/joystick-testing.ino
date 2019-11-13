char buffer[50];

void setup() {
  Serial.begin(9600);

}

void loop() {
  int xAxis = analogRead(A0);
  int yAxis = analogRead(A1);
  sprintf(buffer,"X: %d, Y: %d",xAxis,yAxis);
  Serial.println(buffer);
  
}
