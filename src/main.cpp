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

long long timer;
int inputTimeout = 100;


void setup() {
  Serial.begin(9600);
  rover.setSpeed(255);
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  timer = millis();
}

void loop() {

  if (IrReceiver.decode()) {
    #ifdef DEBUG

    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    #endif
    switch (IrReceiver.decodedIRData.command) {

      // Speed Control
      case 69:  currentcommand = 0;    rover.setSpeed(0);     break;
      case 70:  currentcommand = 1;    rover.setSpeed(25);  break;
      case 71:  currentcommand = 2;    rover.setSpeed(51);    break;
      case 68:  currentcommand = 3;    rover.setSpeed(77);  break;
      case 64:  currentcommand = 4;    rover.setSpeed(102);   break;
      case 67:  currentcommand = 5;    rover.setSpeed(128); break;
      case 7:   currentcommand = 6;    rover.setSpeed(153);   break;
      case 21:  currentcommand = 7;    rover.setSpeed(175); break;
      case 9:   currentcommand = 8;    rover.setSpeed(204);   break;
      case 25:  currentcommand = 9;    rover.setSpeed(225); break;

      // Boom Arm Control
      case 22:  currentcommand = 11;   rover.lowerBoom();     break; // Asterisk
      case 13:  currentcommand = 12;   rover.raiseBoom();     break; // Hashtag

      // Directional Control
      case 24:  currentcommand = 13;   rover.moveForward(); timer = millis(); break; // Up
      case 82:  currentcommand = 14;   rover.moveBackward(); timer = millis(); break; // Down
      case 8:   currentcommand = 15;   rover.turnLeft(); timer = millis(); break; // Left
      case 90:  currentcommand = 16;   rover.turnRight(); timer = millis(); break; // Right

      // Stop Control
      case 28:  currentcommand = 17;   rover.stop();          rover.stopBoom(); break; // OK

      default:
        Serial.println("Unknown Command.");
        rover.stop();
        break;
    }

    #ifdef DEBUG
    Serial.println(currentcommand);
    #endif

    IrReceiver.resume(); // Enable receiving of the next value
  }

  if(millis()-timer>inputTimeout){
    rover.stop();
    rover.stopBoom();
  }
}
