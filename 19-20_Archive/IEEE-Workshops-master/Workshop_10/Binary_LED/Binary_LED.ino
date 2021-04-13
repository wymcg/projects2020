// LED Binary Guessing Game

// Digital 6 to shift register data pin.
#define DATA 6
// Digital 8 to shift register latch pin.
#define LATCH 8
// Digital 10 to shift register clock pin.
#define CLOCK 10

// Initialize variables.
int number = 0;
int answer = 0;

void setup()
{
  // Set the shift register pins to output.
  pinMode(LATCH,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(DATA,OUTPUT);
  // Set the baud rate (bits/second).
  Serial.begin(9600);
  // Initialize the random number generator.
  randomSeed(analogRead(0));
  // Turn off all LEDs.
  displayNumber(0);
}

void displayNumber(byte a)
{
  // Sends 8-bit binary number to be displayed on LEDs.
  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,a);
  digitalWrite(LATCH,HIGH);
}

void getAnswer()
{
  // Receive an answer from the player.
  int x = 0;
  Serial.flush();
  while (Serial.available() == 0)
  {
    // Do nothing until something comes into the serial.
  }
  while (Serial.available() > 0)
  {
    if (Serial.available() > 1);
      answer = answer * 10;
    x = Serial.read() - 48;
    answer = answer + x;
    delay(5);
  }
  // Print the player's input.
  Serial.print("You entered: ");
  Serial.println((answer + 38) / 10);
}

void checkAnswer()
{
  // Compare the answer to the random number.
  if (((answer + 38) / 10) == number)
  {
    // Player is correct, print statement.
    Serial.print("Correct! ");
    Serial.print(number,BIN);
    Serial.print(" equals ");
    Serial.println(number);
    Serial.println();
  }
  else
  {
    // Player is incorrect, print statement.
    Serial.print("Incorrect, ");
    Serial.print(number,BIN);
    Serial.print(" equals ");
    Serial.println(number);
    Serial.println();
  }
  answer = 0;
  number = 0;
  // Pause for 6 seconds before starting next round.
  delay(6000);
}

// Main loop, calls each function.
void loop()
{
  number = random(256);
  displayNumber(number);
  Serial.println("What is the binary number in base-10? ");
  getAnswer();
  checkAnswer(); 
}
