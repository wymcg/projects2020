// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
 
// Define sensor pin
#define RECV_PIN 4
 
// Define LED pin constants
#define bluePin 10
#define greenPin 11
#define yellowPin 12 
#define redPin 13
 
// Define integer to remember toggle state
int togglestate = 0;

float blueClock = 0;
float greenClock = 0;
float yellowClock = 0;
float redClock = 0;

// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
 
 
void setup(){
  // Enable the IR Receiver
  irrecv.enableIRIn();
  // Set LED pins as Outputs
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}
 
 
void loop(){
    blueClock--;
    if (blueClock == 0) {
      digitalWrite(bluePin, LOW);
    }
    greenClock--;
    if (greenClock == 0) {
      digitalWrite(greenPin, LOW);
    }
    yellowClock--;
    if (yellowClock == 0) {
      digitalWrite(yellowPin, LOW);
    }
    redClock--;
    if (redClock == 0) {
      digitalWrite(redPin, LOW);
    }
    if (irrecv.decode(&results)){
 
        switch(results.value){
          case 0x20DF4EB1: //Blue Keypad Button
        // Turn on LED for 2 Seconds
        digitalWrite(bluePin, HIGH);
        blueClock = 25000;
        break;

          case 0x20DF8E71: //Green Keypad Button
        // Turn on LED for 2 Seconds
        digitalWrite(greenPin, HIGH);
        greenClock = 25000;
        break;
        
          case 0x20DFC639: //Yellow Keypad Button
        // Turn on LED for 2 Seconds
        digitalWrite(yellowPin, HIGH);
        yellowClock = 25000;
        break;
        
          case 0x20DF8679: //Red Keypad Button
        // Turn on LED for 2 Seconds
        digitalWrite(redPin, HIGH);
        redClock = 25000;
        break;
        
      /*    case 0xFE8A75: //Yellow Keypad Button
        // Toggle LED On or Off
        if(togglestate==0){
        digitalWrite(yellowPin, HIGH);
        togglestate=1;
        }
        else {
        digitalWrite(yellowPin, LOW);
        togglestate=0;
        }
        break;
        */
    }
    irrecv.resume(); 
  }
 
}
