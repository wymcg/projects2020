#include <ESP8266WiFi.h>
#include "ChangeMac.hpp"

void setup() {
  Serial.begin(9600);
  delay(10);

  uint8_t mac[6];
  
  makeRandomMac(mac);
  changeMac(mac);
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());

  setRandomMac(mac);
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());

  
  mac[0] = 0xFC;
  mac[1] = 0xFF;
  mac[2] = 0xAA;
  changeMac(mac);
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}
