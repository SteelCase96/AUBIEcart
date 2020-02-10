
bool state = 0;

void setup() {
  pinMode(2,OUTPUT);
  
  noInterrupts();
  TCCR1A = 0; // clear the control register
  TCCR1B = 0; // clear the control register
  TCNT1 = 0;
  OCR1A = 31250;
  TCCR1B |= (1<<WGM12); // CTC mode
  TIMSK1 |= (1<<OCIE1A); // enable timer compare interrupts
  interrupts();
  TCCR1B |= (1<<CS12); // 256 prescalar
//  TCCR0B = TCCR0B & 0b11111000 | 0b001;
}

void loop() {
//  digitalWrite(2,state);
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = 0;
  state = !state;
  digitalWrite(2,state);
}
