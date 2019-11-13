void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void generatePacket(char dataSet[]){
  char packet[MAX_LEN];
}

void txPacket(){
  
}

void rxCheck(){
  // --- Function Variables ---
  char incomingByte;
  //char headingBuffer[];

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

bool rxToMeCheck(){
  
}

void rxPacket(){
  // --- Function Variables ---
  boolean done = false;
  char incomingByte;
  uint8_t index = 0;
}

void txPacket(){
  
}
