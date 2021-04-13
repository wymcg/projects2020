#define adcMax 1023
#define poll 1

/*
Very similar to the pot to % code, but maps adc from 0-(number of leds defined in ledPins) instead of 0-100
Output of map gives number of leds that will light up
Had to add '-1' in the map function so that all leds will light up
poll time also reduced above
*/

int ledPins[] = {8,9,10,11,12};

void setup(){
}

void loop(){
  int led = map(analogRead(A0), 20, adcMax-23, 0, 5);
  for(int i = 0; i <= sizeof(ledPins)/sizeof(ledPins[0]); i++){ 
    if(led > i){
      //if it is bigger we can turn on the LED
      digitalWrite(ledPins[i], HIGH);
    }else{
      //if it is smaller we can turn the LED off
      digitalWrite(ledPins[i], LOW);
           }
    }
  delay(poll);
}
