/*
  IR Transmitter Demonstration 1
  IR-Xmit-Demo1.ino
  Control TV using IR Library
  IR LED must use Pin #3
*/

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

// Create IR Send Object
IRsend irsend;

void setup() {
}

void loop() {
    irsend.sendNEC(0x20DF10EF, 32); // TV power code
    irsend.sendNEC(0xFFFFFFFF, 32);
    irsend.sendNEC(0xFFFFFFFF, 32);
    delay(5000);
}
