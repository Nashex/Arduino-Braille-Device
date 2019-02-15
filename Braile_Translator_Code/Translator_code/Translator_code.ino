//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

byte regOne;
byte regTwo;
byte regThree;

bool cell1;
bool cell2;
bool cell3;
bool cell4;
bool cell5;
bool cell6;
bool cell7;

bool row[3] = {0,0,0};
bool col[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

bool onScreen = 1;

String inString;
int str_len;

bool a[6] = {1,0,0,0,0,0};
bool b[6] = {1,0,1,0,0,0};
bool c[6] = {1,1,0,0,0,0};
bool d[6] = {1,1,0,1,0,0};
bool e[6] = {1,0,0,1,0,0};
bool f[6] = {1,1,1,0,0,0};
bool g[6] = {1,1,1,1,0,0};
bool h[6] = {1,0,1,1,0,0};
bool i[6] = {0,1,1,0,0,0};
bool j[6] = {0,1,1,1,0,0};
bool k[6] = {1,0,0,0,1,0};
bool l[6] = {1,0,1,0,1,0};
bool m[6] = {1,1,0,0,1,0};
bool n[6] = {1,1,0,1,1,0};
bool o[6] = {1,0,0,1,1,0};
bool p[6] = {1,1,1,0,1,0};
bool q[6] = {1,1,1,1,1,0};
bool r[6] = {1,0,1,1,1,0};
bool s[6] = {0,1,1,0,1,0};
bool t[6] = {0,1,1,1,1,0};
bool u[6] = {1,0,0,0,1,1};
bool v[6] = {1,0,1,0,1,1};
bool w[6] = {0,1,1,1,0,1};
bool x[6] = {1,1,0,0,1,1};
bool y[6] = {1,1,0,1,1,1};
bool z[6] = {1,0,0,1,1,1};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println ("What word would you like to display?");         //Prints the line "What word would you like to display?" in the Serial console
  while (Serial.available() == 0) { }           //Waits until the user inputs a word or character
  inString = Serial.readString();           //Once a word in taken in as an input, it stores the input in the variable/string named "inString"
  str_len = inString.length() + 1;          //This calculates the length of the word and takes into account the null, hence the "+ 1"
  char charArray[str_len];          //This creates the character array called "charArray" and makes it the length of the word/message, hence the str_len integer located in the square brackets
  inString.toCharArray(charArray, str_len);         //This converts the string "inString" to a character array named "charArray" which is the size of the word/message
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

void displayLetter(int cell, char charArray[]) {
  while(onScreen != 0) {
    for (int i = 0; i < str_len; i++) {
      char inChar = charArray[i];
      String letterArray = inChar + "[j]";
      double presentLetter[7];
      presentLetter[i] = letterArray;
      for (j = 0; j < 6; j++) {
        if (presentLetter[0] == 1) {
          
        }
      }
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, regOne);
      shiftOut(dataPin, clockPin, regTwo);
      shiftOut(dataPin, clockPin, regThree);
      digitalWrite(latchPin, HIGH);
    }
      
  }
  
  
}
