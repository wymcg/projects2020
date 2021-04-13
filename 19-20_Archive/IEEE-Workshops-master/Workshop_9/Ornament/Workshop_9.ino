#include "pitches.h"

#define melodyPin 3
#define buttonPin 4
#define rPin 9
#define gPin 10
#define bPin 11

#define wait 100
#define sit 1000

// 'Slow' can be redifined to change how long
// it takes to change from one color to the
// next while idling

// 'Sit' can be redefined to change how long
// it stays on one color after reaching it
// while idling

// Transition table follow this pattern:
// 1 = blink to next color
// 0 = fade to next color
// Transition table is n - 1 to any song

// Available colors (You can add your own)
// Stored as {% Red, % Green, % Blue}
int black[3] = {0, 0, 0}; // off
int white[3] = {100, 100, 100};
int red[3] = {100, 0, 0};
int green[3] = {0, 100, 0};
int blue[3] = {0, 0, 100};
int lightGreen[3] = {0, 80, 40};
int cyan[3] = {0, 55, 55};
int purple[3] = {33, 10, 55};

// Jingle Bells

int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int tempo[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};
int colors [] = {
  red, white, blue,
  red, white, blue,
  red, white, green, blue,
  green,
  red, white, red, white,
  red, blue, red, green, green,
  blue, red, red, blue,
  green, white
};

int trans[] = {
  0,
  1, 1, 1,
  1, 1, 1,
  1, 1, 1, 0,
  1,
  1, 1, 1, 1,
  1, 1, 1, 1, 1,
  0, 1, 0, 1,
  1
};

// We wish you a merry Christmas

//int melody[] = {
//  NOTE_B3, 
//  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
//  NOTE_D4, NOTE_D4, NOTE_D4,
//  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
//  NOTE_E4, NOTE_E4, NOTE_E4,
//  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
//  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
//  NOTE_D4, NOTE_G4, NOTE_E4,
//  NOTE_F4
//};
//
//int tempo[] = {
//  4,
//  4, 8, 8, 8, 8,
//  4, 4, 4,
//  4, 8, 8, 8, 8,
//  4, 4, 4,
//  4, 8, 8, 8, 8,
//  4, 4, 8, 8,
//  4, 4, 4,
//  2
//};
//
//int colors[] = {
//  blue,
//  green, cyan, blue, purple, red,
//  white, red, green,
//  lightGreen, green, cyan, blue, purple,
//  white, red, green,
//  white, lightGreen, green, cyan, blue,
//  white, red, green, blue,
//  white, red, green,
//  white
//};
//
//int trans[] = {
//  0,
//  0,
//  0, 0, 0, 0, 1,
//  1, 1, 1,
//  0, 0, 0, 0, 1,
//  1, 1, 1,
//  0, 0, 0, 0, 1,
//  1, 1, 0, 1,
//  1, 1, 1,
//};

// Santa Claus is coming to town
//
//int melody[] = {
//  NOTE_G4,
//  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
//  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
//  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
//  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
//  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
//  NOTE_D4, NOTE_F4, NOTE_B3,
//  NOTE_C4
//};
//
//int tempo[] = {
//  8,
//  8, 8, 4, 4, 4,
//  8, 8, 4, 4, 4,
//  8, 8, 4, 4, 4,
//  8, 8, 4, 2,
//  4, 4, 4, 4,
//  4, 2, 4,
//  1
//};
//
//int colors[] = {
//  white,
//  red, green, blue, blue, blue,
//  purple, green, blue, blue, blue,
//  red, green, blue, blue, blue,
//  purple, blue, green, green,
//  red, blue, red, red,
//  white
//};
//
//int trans[] = {
//  0,
//  0,
//  0, 0, 1, 1, 1,
//  0, 0, 1, 1, 1,
//  0, 0, 1, 1, 1,
//  0, 0, 1, 1,
//  0, 0, 0, 0
//};

int rVal = black[0];
int gVal = black[1];
int bVal = black[2];

int prevR = rVal;
int prevG = gVal;
int prevB = bVal;

void setup(void) {
  // Initialize the pins
  pinMode(buttonPin, INPUT);
  pinMode(melodyPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

/* Helper Functions */

// To figure out how big a step there should be between one up- or
// down-tick of one of the LED values, we call calculateStep(), 
// which calculates the absolute gap between the start and end values, 
// and then divides that gap by 1020 to determine the size of the step  
// between adjustments in the value.

float calculateStep(int prevValue, int endValue, long frames) {
  float step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = frames/step;              //   divide by 1020
  } 
  return step;
}

// The next function is calculateVal. When the loop value, i,
// reaches the step size appropriate for one of the
// colors, it increases or decreases the value of that color by 1. 
// (R, G, and B are each calculated separately.)

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

// This function calculates the value for the buzz loop
// Different from the one above since this does a step in
// the color for each loop of the tone play

int calculateValBuzz(float step, int val) {
  val = val + (1/step);
  if (val > 255) {
    return 255;
  }
  if (val < 0) {
    return 0;
  }
  return val;
}

/* Audio producing function */

// Buzz is the code that plays the note while coloring the LEDs
// Combines both playing a note with the crossfade to combination
// change both the LED and the audio

void buzz(long frequency, int color[3], int trans, long length) {
  // calculate the number of cycles for proper timing
  // multiply frequency, which is really cycles per second, by the number of seconds to
  // get the total number of cycles to produce
  long numCycles = frequency * length / 1000;

  // calculate the delay value between transitions
  // 1 second's worth of microseconds, divided by the frequency, then split in half since
  // there are two phases to each cycle
  long delayValue = 1000000 / frequency / 2;

  // Convert color to 0-255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;
 
  if (trans) {
    // Map the steps to the number of cycles to play the tone
    // Only necesary on a fade transition
    float stepR = calculateStep(prevR, R, numCycles);
    float stepG = calculateStep(prevG, G, numCycles); 
    float stepB = calculateStep(prevB, B, numCycles);
    for (long i = 0; i < numCycles; i++) {
      // Calculate the new value for the RGB
      rVal = calculateValBuzz(stepR, rVal);
      gVal = calculateValBuzz(stepG, gVal);
      bVal = calculateValBuzz(stepB, bVal);
      // Write current values to LED pins
      analogWrite(rPin, rVal);
      analogWrite(gPin, gVal);      
      analogWrite(bPin, bVal);
      
      digitalWrite(melodyPin, HIGH);
      delayMicroseconds(delayValue);
      digitalWrite(melodyPin, LOW);
      delayMicroseconds(delayValue);
    }
  } else {
    // Blink the LED to the color
    // First set everything to black, then to color
    analogWrite(rPin, 0);
    analogWrite(gPin, 0);
    analogWrite(bPin, 0);
    delay(10);
    analogWrite(rPin, R);
    analogWrite(gPin, G);
    analogWrite(bPin, B);
    for (long i = 0; i < numCycles; i++) {  
      digitalWrite(melodyPin, HIGH);
      delayMicroseconds(delayValue);
      digitalWrite(melodyPin, LOW);
      delayMicroseconds(delayValue);
    }
  }
  prevR = rVal; 
  prevG = gVal; 
  prevB = bVal;
}

/* Main Drive Code */

// Start Melody() run whenever the button is pressed
// the button press acts as an interrupt on the fade
// main purpose is to loop through the notes

void startMelody() {
  prevR = rVal; 
  prevG = gVal; 
  prevB = bVal;
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / tempo[thisNote];

    buzz(melody[thisNote], colors[thisNote], trans[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    digitalWrite(melodyPin, LOW);
  }
}

//  crossFade() converts the percentage colors to a 
//  0-255 range, then loops 1020 times, checking to see if  
//  the value needs to be updated each time, then writing
//  the color values to the correct pins.

void crossFade(int color[3]) {
  // Convert to 0-255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R, 1020);
  int stepG = calculateStep(prevG, G, 1020); 
  int stepB = calculateStep(prevB, B, 1020);

  for (int i = 0; i <= 1020; i++) {
    if (digitalRead(buttonPin) == HIGH) {
      startMelody();
    }
    rVal = calculateVal(stepR, rVal, i);
    gVal = calculateVal(stepG, gVal, i);
    bVal = calculateVal(stepB, bVal, i);

    // Write current values to LED pins
    analogWrite(rPin, rVal);
    analogWrite(gPin, gVal);      
    analogWrite(bPin, bVal); 

    // Pause for 'wait' microseconds before resuming the loop
    delayMicroseconds(wait);
  }
  // Update current values for next loop
  prevR = rVal; 
  prevG = gVal; 
  prevB = bVal;
  // Pause for 'sit' microseconds before continuing to the next color
  delayMicroseconds(sit);
}

// Here is the main loop

void loop() {
  crossFade(red);
  crossFade(green);
  crossFade(blue);
  crossFade(white);
  if (digitalRead(buttonPin) == HIGH) {
    startMelody();
  }
}

/* This part of the code is the color cross fade
*  The program works like this:
*  Imagine a crossfade that moves the red LED from 0-10, 
*   the green from 0-5, and the blue from 10 to 7, in
*   ten steps.
*   We'd want to count the 10 steps and increase or 
*   decrease color values in evenly stepped increments.
*   Imagine a + indicates raising a value by 1, and a -
*   equals lowering it. Our 10 step fade would look like:
* 
*   1 2 3 4 5 6 7 8 9 10
* R + + + + + + + + + +
* G   +   +   +   +   +
* B     -     -     -
* 
* The red rises from 0 to 10 in ten steps, the green from 
* 0-5 in 5 steps, and the blue falls from 10 to 7 in three steps.
* 
* In the real program, the color percentages are converted to 
* 0-255 values, and there are 1020 steps (255*4).
*/
