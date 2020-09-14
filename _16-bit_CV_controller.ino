
//uint16_t note[13] ={0,80,160,244,324,408,488,572,652,732,812,888,1020};
//uint16_t note[13] ={0,32,49,68,89,112,129,150,171,190,210,227,255};
uint16_t CVnote[13] ={0,5381,10506,15439,20692,25891,31070,36131,41358,46253,51314,56210,61884};

uint16_t currentnoteArray[8];
uint16_t dom7[8] = {CVnote[0],CVnote[0],CVnote[4],CVnote[4],CVnote[7],CVnote[7],CVnote[10],CVnote[12]};
uint16_t min7[8] = {CVnote[0],CVnote[0],CVnote[3],CVnote[3],CVnote[7],CVnote[10],CVnote[12],CVnote[12]};
uint16_t maj7[8] = {CVnote[0],CVnote[0],CVnote[4],CVnote[4],CVnote[7],CVnote[7],CVnote[11],CVnote[12]};
uint16_t majpent[8] = {CVnote[0],CVnote[0],CVnote[2],CVnote[4],CVnote[4],CVnote[7],CVnote[9],CVnote[12]};
uint16_t minpent[8] = {CVnote[0],CVnote[0],CVnote[3],CVnote[3],CVnote[5],CVnote[7],CVnote[10],CVnote[12]};
uint16_t octavefifth[8] = {CVnote[12],CVnote[12],CVnote[5],CVnote[5],CVnote[5],CVnote[0],CVnote[0],CVnote[0]};
uint16_t octavebounce[8] = {CVnote[12],CVnote[12],CVnote[12],CVnote[12],CVnote[12],CVnote[0],CVnote[0],CVnote[0]};
uint16_t modeSelect = A1;
uint16_t icr = 0xffff;
uint16_t inputPin = A0;

void setupPWM16() {
  DDRB  |= _BV(PB5) | _BV(PB2);       /* set pins as outputs */
 TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);  // Enable PWM outputs for OC1A and OC1B on digital pins 9, 10
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);     // Set fast PWM and prescaler of 8 on timer 1
    TCCR1C = 0;
  ICR1 = icr;                         /* TOP counter value (freeing OCR1A*/
}
uint16_t multiMap(uint16_t val, uint16_t* _in, uint16_t* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val)
{
  switch (pin) {
    case  9: OCR1A = val; break;
    case 10: OCR1B = val; break;
  }
}

void setup() {
  Serial.begin(9600);
  setupPWM16();
}


void loop() {
uint16_t inputnote = analogRead(inputPin);
//int arpmode = analogRead(arpSelect);
//int scaledinput = log(input) / log(1000) * 1015;

//uint16_t out[] = {0, 128, 256, 384, 512, 640, 768, 896, 1024};
//uint16_t in[]  = {0, 100, 170, 240, 303, 407, 540, 725, 1024};
//uint16_t currentnotetemp = multiMap(inputnote, in, out, 9);
uint16_t currentnote = (8*(inputnote+1)/1023);
  //  int input = analogRead(A0);
 
int currentmode = analogRead(modeSelect);
int i=0;
   
    for(int i; i<12;i++){
    if(currentmode >= 1000){
    currentnoteArray[i] = dom7[i];
    }
    else if(currentmode >= 900){
    currentnoteArray[i] = min7[i];
    }
    else if(currentmode >= 700){
    currentnoteArray[i] = maj7[i];
    }
    else if(currentmode >= 600){
    currentnoteArray[i] = majpent[i];
    }
    else if(currentmode >= 500){
    currentnoteArray[i] = minpent[i];
    }
    else if(currentmode >= 400){
    currentnoteArray[i] = octavefifth[i];
    }
    else if(currentmode >= 300){
    currentnoteArray[i] = octavebounce[i];
    }
    else if(currentmode >= 200){
    for (int j = 0; j < 5; j=j+1) 
    {
//    spi_out(CS_signal, cmd_byte2, octavebounce[j]); 
    }
    }

     //  Serial.println(input); 
         
   Serial.println(inputnote);
    Serial.println(currentnote);    
    Serial.println(currentmode); 
 // for (uint16_t i = 0; i < 0xffff; i++)
  {
    analogWrite16(9, currentnoteArray[currentnote]);
    delay(2);
  }}  }


