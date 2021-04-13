
#define adcMax 1023
#define poll 1000

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int percent = map(analogRead(A0), 0, adcMax, 0, 100);
  Serial.println(String(percent) + '%');
  delay(poll);
}
