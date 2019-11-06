// ----- Main Variables -----
const char sys = 'A'; // '' for console, '' for cart

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void rxCheck(){
  // --- Function Variables ---
  char incomingByte;

  // --- Function Body ---
  while(true){
    if(Serial1.available()>0){
      incomingByte = char(Serial1.read());
      if(incomingByte == 'S'){
        incomingByte = char(Serial1.read());
        if(incomingByte == 'S'){
          if(rxToMeCheck() == true){
            rxPacket();
          }
          else{return;}
        }
      }
    }
  }
}

void rxToMeCheck(){
  
}

void rxPacket(){
  // --- Function Variables ---
  boolean done = false;
  char incomingByte;
  uint8_t index = 0;
}

void txPacket(){
  
}
