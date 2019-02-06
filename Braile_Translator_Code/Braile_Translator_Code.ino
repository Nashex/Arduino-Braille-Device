//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//holders for infromation you're going to pass to shifting function
byte data;
byte dataArray[10];
boolean row[3] = {0,0,0};
boolean col[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);

  //Binary notation as comment
  dataArray[0] = 0xFF; //0b11111111
  dataArray[1] = 0xFE; //0b11111110
  dataArray[2] = 0xFC; //0b11111100
  dataArray[3] = 0xF8; //0b11111000
  dataArray[4] = 0xF0; //0b11110000
  dataArray[5] = 0xE0; //0b11100000
  dataArray[6] = 0xC0; //0b11000000
  dataArray[7] = 0x80; //0b10000000
  dataArray[8] = 0x00; //0b00000000
  dataArray[9] = 0xE0; //0b11100000

}

void loop() {
  
  clearReg();

  letterA(1);
  delay(2500);

}



// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

void clearReg() {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
}

byte boolArrayToByte(bool boolArray[8])
{
  byte result = 0; 

  for(int i = 0; i < 8; i++)
  {
    if(boolArray[i])
    {
      result = result | (1 << i);
    }
  }

  return result;
}

//Code for letter A
void letterA(int cell) {
  //Clears bools  
  bool regOne[8] = {0,0,0,0,0,0,0,0}; 
  bool regTwo[8] = {0,0,0,0,0,0,0,0}; 
  
  //Sets latch LOW
  digitalWrite(latchPin, LOW);
  //Sends data for letterA out
  shiftOut(dataPin, clockPin, 12); //Turns Rows 2 and 3 off
    
    switch(cell) {
      case 1:
      regOne[1] = 1;
      break;
      
      case 2:
      regOne[3] = 1;
      break;
      
      case 3:
      regOne[5] = 1;
      break;

      case 4:
      regOne[7] = 1;
      break;

      case 5:
      regTwo[2] = 1;
      break;

      case 6:
      regTwo[4] = 1;
      break;

      case 7:
      regTwo[6] = 1;
      break;
      
    }
    
    byte byteOne = boolArrayToByte(regOne);
    byte byteTwo = boolArrayToByte(regTwo);
    Serial.print(byteOne);
    shiftOut(dataPin, clockPin, byteTwo);
    shiftOut(dataPin, clockPin, byteOne);
    digitalWrite(latchPin, HIGH);

}
