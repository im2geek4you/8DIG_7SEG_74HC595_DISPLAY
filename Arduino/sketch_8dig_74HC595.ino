/*
 * Project name:
 8 Digit 7 Segment Display - Aliexpress 8-digit w/ IC 74HC595 from WAVGAT)
     Arduino File: sketch_8dig_74HC595.ino
  * Revision History:
     20191102:
  * Description:
      This 7 segmet, 8 digit LED Display uses 75HC595 to be driven
      by an MCU using only 3 IO pins.
 * MCU:                Arduino - @16MHz   http://www.arduino.cc/
 * IC Chip:            74HC595 - 8-bit serial-in/parallel-out shift register 
 * Connections:        DIO=3; SCLK=5; RCLK=4
 * Based on giljr @ https://github.com/giljr/Ardu_Serie/tree/master/_02_7Seg/_8Digit_00  
 */


#define LATCH  4  //Serial Output to Shift Register Pin- RCLK
#define CLOCK  5  //Shift Register Clock Pin - SCLK
#define DATA   3  //Serial data output/input - DIO

//array to store display digits to show
byte DISPLAYBUF[8]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

// array to activate particular digit on the 8x7segment module
// it is the common anode of 7 segment
byte POS[8] = { 
  0b00000001,  //digit 1 from right
  0b00000010,  //digit 2 from right
  0b00000100,  //digit 3 from right
  0b00001000,  //digit 4 from right
  0b00010000,  //digit 5 from right
  0b00100000,  //digit 6 from right
  0b01000000,  //digit 7 from right
  0b10000000   //digit 8 from right
};

//array for decimal number, it is the cathode.
//logic low will activate the particular segment
//led to bit position : DP,G,F,E,D,C,B,A
byte NUM[13] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000,  // 9
  0b01111111,  //dot
  0b10111111,  //minus
  0b11111111  //blank
};

//function to send the serial data out to two 74HC595 serial to parallel shift register and activate the 7 segment.
void display8x7segment(byte datapin, byte clockpin, byte latchpin, byte POS, byte NUM)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, NUM); // array for decimal number 
  shiftOut(DATA, CLOCK, MSBFIRST, POS); // Particular digit position
  digitalWrite(LATCH, HIGH);
}

//function to show number on display
void displaynumber(unsigned int value){
  unsigned int index=0;
  while (value > 0) {
  int digit = value % 10;
  DISPLAYBUF[index] = NUM[digit];
  value /= 10;
  index++;
  }
  for (byte e = 0; e <= 7 ; e ++) {
    display8x7segment(DATA, CLOCK, LATCH, POS[e], DISPLAYBUF[e]);
    //delay(1000);
  }
}


void setup()
{
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  digitalWrite(LATCH, HIGH); //Wake Up Display
  delay(500);  //delay for startup


}

void loop()
{

  //This is just an example. A better way to use this display is to use interrupts to refresh the number being displayed, since the display needs to be continuosly updated for persistence of view.
  for (unsigned int i =0; i<999999; i++){
    for (int t=0; t<300;t++){
          displaynumber(i);
    }
    //delay(200);
  }    
}
