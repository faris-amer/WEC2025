#include <Arduino.h>
#include <IRremote.h>
// put function declarations here:

#define IRPIN 7

int currentcommand;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    //IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
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
    }
    Serial.println(currentcommand);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
