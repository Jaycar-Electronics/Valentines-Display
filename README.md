# Valentines Display
Show someone you care this Valentines Day by creating an LED Display of affection.

## Bill of Materials
| Qty | Code | Description |
| --- | --- | ---|
|4 | [XC4499](http://jaycar.com.au/p/XC4499) | Arduino Compatible 8x8 LED Dot Matrix
|1 | [XC4414](http://jaycar.com.au/p/XC4414) | Duinotech Nano
|1 | [WC7710](http://jaycar.com.au/p/WC7710) | USB A to Mini-B Cable
|1 | [WC6027](http://jaycar.com.au/p/WC6027) | Jumper Lead Mixed Pack 100 Pieces
|1 | [PB8815](http://jaycar.com.au/p/PB8815) | Arduino Compatible Breadboard

* While a prototyping board is not required it will make the job significantly easier, while providing mounting for the display.

## Connection Table

| Nano | First Matrix IN |
| --- | ---|
| 5V | VCC
| GND | GND
| D2 | DIN
| D3 | CS
| D4 | CLK

For Each addtional matrix (in this case a total of 4), you will need to link from the output of the first display to the input of the next display. You can either link them using jumper wires direct to each display, or by mounting them on the prototyping boards as pictured below.

![LED Matrix Display](https://github.com/Jaycar-Electronics/Valentines_Display/blob/master/LED%20Matrix%20Display.jpg)

![LED Matrix Display](https://github.com/Jaycar-Electronics/Valentines_Display/blob/master/LED%20Matrix%20Display%20Board.jpg)

We found by mounting the last board at the very edge of the prototyping board made it easier to fit the Nano & route the jumper wires.

## Programming

Download the source code, extract into a new folder, open the .ino file in the Arduino IDE and press upload.

## Use

Turn it on & show it to that special someone.
