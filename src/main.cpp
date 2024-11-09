#include <Arduino.h>
#include <IRremote.h>
#include <motors.hpp>
// put function declarations here:

#define DEBUG //serial print outputs

#define IRPIN 10
#define LEFT1 4
#define LEFT2 2
#define LEFTSPEED 9
#define RIGHT1 7
#define RIGHT2 5
#define RIGHTSPEED 6

int currentcommand;
Motors rover(LEFT1,LEFT2,LEFTSPEED,RIGHT1,RIGHT2,RIGHTSPEED);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    #ifdef DEBUG

    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

    #endif
    switch(IrReceiver.decodedIRData.command){
      case 69:
        currentcommand = 1 ;
      break;
      case 70:
        currentcommand = 2 ;
      break;
      case 71:
        currentcommand = 3;
      break;
      case 68:
        currentcommand = 4;
      break;
      case 64:
        currentcommand = 5;
      break;
      case 67:
        currentcommand = 6;
      break;
      case 21:
        currentcommand = 8;
      break;
      case 7:
        currentcommand = 7;
      break;
      case 9:
        currentcommand = 9;
      break;
      case 25:
        currentcommand = 0;
      break;
      case 22:
        currentcommand = 11; // Asterix
      break;
      case 13:
        currentcommand = 12; // Hashtag
      break;
      case 24:
        currentcommand = 13; // Up
      break;
      case 82:
        currentcommand = 14; // Down
      break;
      case 8:
        currentcommand = 15; // Left
      break;
      case 90:
        currentcommand = 16; // Right
      break;
      case 28:
        currentcommand = 17; // Ok
      break;
    }

    #ifdef DEBUG
    Serial.println(currentcommand);
    #endif

    IrReceiver.resume(); // Enable receiving of the next value
  }
  Serial.println("forwards");
  rover.forwards(200);
  delay(3000);
  Serial.println("backwards");
  rover.backwards(200);
  delay(3000);
  Serial.println("right");
  rover.right(200);
  delay(3000);
  Serial.println("left");
  rover.left(200);
  delay(3000);


}
