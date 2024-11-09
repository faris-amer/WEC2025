#include <Arduino.h>
#include <IRremote.h>
#include <motors.hpp>
// put function declarations here:

#define DEBUG //serial print outputs

#define BOOMSPEED 10
#define BOOMPIN1 15
#define BOOMPIN2 16
#define IRPIN 8
#define LEFT1 2
#define LEFT2 4
#define LEFTSPEED 9
#define RIGHT1 7
#define RIGHT2 5
#define RIGHTSPEED 6
#define MAGNETPIN 12

int currentcommand;
Motors rover(LEFT1, LEFT2, LEFTSPEED, RIGHT1, RIGHT2, RIGHTSPEED, BOOMPIN1, BOOMPIN2, BOOMSPEED);
int magnetState = 0;
int magnetPin = MAGNETPIN;

long long timer;
long long boomTimer;
int inputTimeout = 100;


void setup() {
  Serial.begin(9600);
  rover.setSpeed(255);
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  pinMode(magnetPin, OUTPUT);
  timer = millis();
  boomTimer = millis();
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
      //rover.setBoomSpeed(rover.getSpeed() / 1.5);
      case 22:  currentcommand = 11; rover.lowerBoom(); timer = millis(); break; // Lower Boom
      case 13:  currentcommand = 12;
      Serial.println(rover.getBoomSpeed());
      rover.raiseBoom(); timer = millis(); break; // Raise Boom

      // Directional Control
      case 24:  currentcommand = 13;   rover.moveForward(); timer = millis(); break; // Up
      case 82:  currentcommand = 14;   rover.moveBackward(); timer = millis(); break; // Down
      case 8:   currentcommand = 15;   rover.turnLeft(); timer = millis(); break; // Left
      case 90:  currentcommand = 16;   rover.turnRight(); timer = millis(); break; // Right

      // Magnet Control
      case 28:
        currentcommand = 17;
        if(magnetState == 0){
          digitalWrite(magnetPin,HIGH);
          magnetState=1;
        }
        else{
          digitalWrite(magnetPin,LOW);
          magnetState=0;
        }
        break; // OK

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
