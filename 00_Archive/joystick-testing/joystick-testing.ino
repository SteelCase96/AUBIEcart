char buffer[50];

void setup() {
  Serial.begin(9600);

}

void loop() {
  int xAxis = analogRead(A1);
  int yAxis = analogRead(A0);
  sprintf(buffer,"X: %d, Y: %d",xAxis,yAxis);
  Serial.println(buffer);
  
}
