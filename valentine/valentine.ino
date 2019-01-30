/* code for max 7219 from maxim,
reduced and optimised for using more than one 7219 in a row,
______________________________________

 Code History:
 --------------

The original code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmÃ¶ hÃ¶gskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/

This version is by:
 * Jaycar Electronics / Feb 2019

 * @acknowledgements: eric f.

-----------------------------------

General notes:

-if you are only using one max7219, then use the function maxSingle to control
 the little guy ---maxSingle(register (1-8), collum (0-255))

-if you are using more than one max7219, and they all should work the same,
then use the function maxAll ---maxAll(register (1-8), collum (0-255))

-if you are using more than one max7219 and just want to change something
at one little guy, then use the function maxOne
---maxOne(Max you want to control (1== the first one), register (1-8),
column (0-255))

During initiation, be sure to send every part to every max7219 and then
upload it.
For example, if you have five max7219's, you have to send the scanLimit 5 times
before you load it-- otherwise not every max7219 will get the data. the
function maxInUse keeps track of this, just tell it how many max7219 you are
using.
*/

int dataIn = 2;
int load = 3;
int clock = 4;

int maxInUse = 4;    //change this variable to set how many MAX7219's you'll use

int e = 0;           // just a variable

int n=0;
// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
    }else{
      digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}

void maxSingle( byte reg, byte col) {
//maxSingle is the "easy"  function to use for a single max7219

  digitalWrite(load, LOW);       // begin
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
  digitalWrite(load, LOW);       // and load da stuff
  digitalWrite(load,HIGH);
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {
//maxOne is for addressing different MAX7219's,
//while having a couple of them cascaded

  int c = 0;
  digitalWrite(load, LOW);  // begin

  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data

  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  digitalWrite(load, LOW); // and load da stuff
  digitalWrite(load,HIGH);
}


void setup () {

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  digitalWrite(13, HIGH);

//initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                                                  // range: 0x00 to 0x0f
}

void loop () {

  // Slide 1

  maxAll(1,24);          // ---@@---
  maxAll(2,60);          // --@@@@--
  maxAll(3,124);         // -@@@@@--
  maxAll(4,248);         // @@@@@---
  maxAll(5,248);         // @@@@@---
  maxAll(6,124);         // -@@@@@--
  maxAll(7,60);          // --@@@@--
  maxAll(8,24);          // ---@@---
  delay(500);
  maxAll(1,0);           // --------
  maxAll(2,0);           // --------
  maxAll(3,0);           // --------
  maxAll(4,0);           // --------
  maxAll(5,0);           // --------
  maxAll(6,0);           // --------
  maxAll(7,0);           // --------
  maxAll(8,0);           // --------
  delay(500);

  // Slide 2

  maxOne(1,1,24);          // ---@@---
  maxOne(1,2,60);          // --@@@@--
  maxOne(1,3,124);         // -@@@@@--
  maxOne(1,4,248);         // @@@@@---
  maxOne(1,5,248);         // @@@@@---
  maxOne(1,6,124);         // -@@@@@--
  maxOne(1,7,60);          // --@@@@--
  maxOne(1,8,24);          // ---@@---

  maxOne(2,1,0);           // --------
  maxOne(2,2,124);         // -@@@@@--
  maxOne(2,3,84);          // -@-@-@--
  maxOne(2,4,40);          // --@-@---
  maxOne(2,5,0);           // --------
  maxOne(2,6,124);         // -@@@@@--
  maxOne(2,7,84);          // -@-@-@--
  maxOne(2,8,0);           // --------

  maxOne(3,1,0);           // --------
  maxOne(3,2,124);         // -@@@@@--
  maxOne(3,3,8);           // ----@---
  maxOne(3,4,124);         // -@@@@@--
  maxOne(3,5,0);           // --------
  maxOne(3,6,28);          // ---@@@--
  maxOne(3,7,112);         // -@@@----
  maxOne(3,8,28);          // ---@@@--

  maxOne(4,1,24);          // ---@@---
  maxOne(4,2,60);          // --@@@@--
  maxOne(4,3,124);         // -@@@@@--
  maxOne(4,4,248);         // @@@@@---
  maxOne(4,5,248);         // @@@@@---
  maxOne(4,6,124);         // -@@@@@--
  maxOne(4,7,60);          // --@@@@--
  maxOne(4,8,24);          // ---@@---
  delay(1000);

  // Slide 3

  maxOne(1,1,0);           // --------
  maxOne(1,2,60);          // --@@@@--
  maxOne(1,3,64);          // -@------
  maxOne(1,4,60);          // --@@@@--
  maxOne(1,5,0);           // --------
  maxOne(1,6,120);         // -@@@@---
  maxOne(1,7,20);          // ---@-@--
  maxOne(1,8,120);         // -@@@@---

  maxOne(2,1,124);         // -@@@@@--
  maxOne(2,2,64);          // -@------
  maxOne(2,3,0);           // --------
  maxOne(2,4,124);         // -@@@@@--
  maxOne(2,5,84);          // -@-@-@--
  maxOne(2,6,0);           // --------
  maxOne(2,7,124);         // -@@@@@--
  maxOne(2,8,4);           // -----@--

  maxOne(3,1,124);         // -@@@@@--
  maxOne(3,2,0);           // --------
  maxOne(3,3,4);           // -----@--
  maxOne(3,4,124);         // -@@@@@--
  maxOne(3,5,4);           // -----@--
  maxOne(3,6,0);           // --------
  maxOne(3,7,124);         // -@@@@@--
  maxOne(3,8,0);           // --------

  maxOne(4,1,0);           // --------
  maxOne(4,2,124);         // -@@@@@--
  maxOne(4,3,4);           // -----@--
  maxOne(4,4,124);         // -@@@@@--
  maxOne(4,5,0);           // --------
  maxOne(4,6,124);         // -@@@@@--
  maxOne(4,7,84);          // -@-@-@--
  maxOne(4,8,0);           // --------
  delay(1000);

  // Slide 4

  maxOne(1,1,24);          // ---@@---
  maxOne(1,2,60);          // --@@@@--
  maxOne(1,3,124);         // -@@@@@--
  maxOne(1,4,248);         // @@@@@---
  maxOne(1,5,248);         // @@@@@---
  maxOne(1,6,124);         // -@@@@@--
  maxOne(1,7,60);          // --@@@@--
  maxOne(1,8,24);          // ---@@---

  maxOne(2,1,0);           // --------
  maxOne(2,2,0);           // --------
  maxOne(2,3,0);           // --------
  maxOne(2,4,0);           // --------
  maxOne(2,5,0);           // --------
  maxOne(2,6,0);           // --------
  maxOne(2,7,0);           // --------
  maxOne(2,8,0);           // --------

  maxOne(3,1,24);          // ---@@---
  maxOne(3,2,60);          // --@@@@--
  maxOne(3,3,124);         // -@@@@@--
  maxOne(3,4,248);         // @@@@@---
  maxOne(3,5,248);         // @@@@@---
  maxOne(3,6,124);         // -@@@@@--
  maxOne(3,7,60);          // --@@@@--
  maxOne(3,8,24);          // ---@@---

  maxOne(4,1,0);           // --------
  maxOne(4,2,0);           // --------
  maxOne(4,3,0);           // --------
  maxOne(4,4,0);           // --------
  maxOne(4,5,0);           // --------
  maxOne(4,6,0);           // --------
  maxOne(4,7,0);           // --------
  maxOne(4,8,0);           // --------
  delay(250);

  // Slide 5

  maxOne(1,1,0);           // --------
  maxOne(1,2,0);           // --------
  maxOne(1,3,0);           // --------
  maxOne(1,4,0);           // --------
  maxOne(1,5,0);           // --------
  maxOne(1,6,0);           // --------
  maxOne(1,7,0);           // --------
  maxOne(1,8,0);           // --------

  maxOne(2,1,24);          // ---@@---
  maxOne(2,2,60);          // --@@@@--
  maxOne(2,3,124);         // -@@@@@--
  maxOne(2,4,248);         // @@@@@---
  maxOne(2,5,248);         // @@@@@---
  maxOne(2,6,124);         // -@@@@@--
  maxOne(2,7,60);          // --@@@@--
  maxOne(2,8,24);          // ---@@---

  maxOne(3,1,0);           // --------
  maxOne(3,2,0);           // --------
  maxOne(3,3,0);           // --------
  maxOne(3,4,0);           // --------
  maxOne(3,5,0);           // --------
  maxOne(3,6,0);           // --------
  maxOne(3,7,0);           // --------
  maxOne(3,8,0);           // --------

  maxOne(4,1,24);          // ---@@---
  maxOne(4,2,60);          // --@@@@--
  maxOne(4,3,124);         // -@@@@@--
  maxOne(4,4,248);         // @@@@@---
  maxOne(4,5,248);         // @@@@@---
  maxOne(4,6,124);         // -@@@@@--
  maxOne(4,7,60);          // --@@@@--
  maxOne(4,8,24);          // ---@@---
  delay(250);

  // Slide 6

  maxOne(1,1,24);          // ---@@---
  maxOne(1,2,60);          // --@@@@--
  maxOne(1,3,124);         // -@@@@@--
  maxOne(1,4,248);         // @@@@@---
  maxOne(1,5,248);         // @@@@@---
  maxOne(1,6,124);         // -@@@@@--
  maxOne(1,7,60);          // --@@@@--
  maxOne(1,8,24);          // ---@@---

  maxOne(2,1,0);           // --------
  maxOne(2,2,0);           // --------
  maxOne(2,3,0);           // --------
  maxOne(2,4,0);           // --------
  maxOne(2,5,0);           // --------
  maxOne(2,6,0);           // --------
  maxOne(2,7,0);           // --------
  maxOne(2,8,0);           // --------

  maxOne(3,1,24);          // ---@@---
  maxOne(3,2,60);          // --@@@@--
  maxOne(3,3,124);         // -@@@@@--
  maxOne(3,4,248);         // @@@@@---
  maxOne(3,5,248);         // @@@@@---
  maxOne(3,6,124);         // -@@@@@--
  maxOne(3,7,60);          // --@@@@--
  maxOne(3,8,24);          // ---@@---

  maxOne(4,1,0);           // --------
  maxOne(4,2,0);           // --------
  maxOne(4,3,0);           // --------
  maxOne(4,4,0);           // --------
  maxOne(4,5,0);           // --------
  maxOne(4,6,0);           // --------
  maxOne(4,7,0);           // --------
  maxOne(4,8,0);           // --------
  delay(250);

  // Slide 7

  maxOne(1,1,0);           // --------
  maxOne(1,2,0);           // --------
  maxOne(1,3,0);           // --------
  maxOne(1,4,0);           // --------
  maxOne(1,5,0);           // --------
  maxOne(1,6,0);           // --------
  maxOne(1,7,0);           // --------
  maxOne(1,8,0);           // --------

  maxOne(2,1,24);          // ---@@---
  maxOne(2,2,60);          // --@@@@--
  maxOne(2,3,124);         // -@@@@@--
  maxOne(2,4,248);         // @@@@@---
  maxOne(2,5,248);         // @@@@@---
  maxOne(2,6,124);         // -@@@@@--
  maxOne(2,7,60);          // --@@@@--
  maxOne(2,8,24);          // ---@@---

  maxOne(3,1,0);           // --------
  maxOne(3,2,0);           // --------
  maxOne(3,3,0);           // --------
  maxOne(3,4,0);           // --------
  maxOne(3,5,0);           // --------
  maxOne(3,6,0);           // --------
  maxOne(3,7,0);           // --------
  maxOne(3,8,0);           // --------

  maxOne(4,1,24);          // ---@@---
  maxOne(4,2,60);          // --@@@@--
  maxOne(4,3,124);         // -@@@@@--
  maxOne(4,4,248);         // @@@@@---
  maxOne(4,5,248);         // @@@@@---
  maxOne(4,6,124);         // -@@@@@--
  maxOne(4,7,60);          // --@@@@--
  maxOne(4,8,24);          // ---@@---
  delay(250);
}
