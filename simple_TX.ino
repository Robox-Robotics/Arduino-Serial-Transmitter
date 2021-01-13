/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(PA0, PA1); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(PB8,OUTPUT);
}
void loop() {
  digitalWrite(PB8,HIGH);
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
    digitalWrite(PB8,LOW);
  delay(1000);  
}
