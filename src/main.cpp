#include <Arduino.h>
#include <IRremote.h>

#define IRPIN 7

int currentcommand;

Motors rover;

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
}

void loop() {

  if (IrReceiver.decode()) {
    // Serial.println(IrReceiver.decodedIRData.command);
    //IrReceiver.printIRResultShort(&Serial);

    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

    switch (IrReceiver.decodedIRData.command) {

      // Speed Control
      case 69:  currentcommand = 0;    rover.setSpeed(0);     break;
      case 70:  currentcommand = 1;    rover.setSpeed(25.5);  break;
      case 71:  currentcommand = 2;    rover.setSpeed(51);    break;
      case 68:  currentcommand = 3;    rover.setSpeed(76.5);  break;
      case 64:  currentcommand = 4;    rover.setSpeed(102);   break;
      case 67:  currentcommand = 5;    rover.setSpeed(127.5); break;
      case 7:   currentcommand = 6;    rover.setSpeed(153);   break;
      case 21:  currentcommand = 7;    rover.setSpeed(178.5); break;
      case 9:   currentcommand = 8;    rover.setSpeed(204);   break;
      case 25:  currentcommand = 9;    rover.setSpeed(229.5); break;

      // Boom Arm Control
      case 22:  currentcommand = 11;   rover.lowerBoom();     break; // Asterisk
      case 13:  currentcommand = 12;   rover.raiseBoom();     break; // Hashtag

      // Directional Control
      case 24:  currentcommand = 13;   rover.moveForward();   break; // Up
      case 82:  currentcommand = 14;   rover.moveBackward();  break; // Down
      case 8:   currentcommand = 15;   rover.turnLeft();      break; // Left
      case 90:  currentcommand = 16;   rover.turnRight();     break; // Right

      // Stop Control
      case 28:  currentcommand = 17;   rover.stop();          rover.stopBoom(); break; // OK

      default:
        Serial.println("Unknown Command.");
        rover.stop();
        break;
    }

    Serial.println(currentcommand);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
