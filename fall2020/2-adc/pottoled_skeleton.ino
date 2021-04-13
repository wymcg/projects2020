
#define adcMax 1023
#define poll 1

int ledPins[] = {8,9,10,11,12};

void setup(){
}

void loop(){
  //map the analogRead value from to the number of lit leds

  for(int i = 0; i <= sizeof(ledPins)/sizeof(ledPins[0]); i++){ 
    if(led > i){
      //if it is bigger we can turn on the LED

    }else{
      //if it is smaller we can turn the LED off

           }
    }
    //wait until we want to update the leds again
    
}
