#include <Arduino.h>

class Motors{
  private:
  int leftpin1;
  int leftpin2;
  int leftspeedpin;
  int rightpin1;
  int rightpin2;
  int rightspeedpin;

  int boomPin1;
  int boomPin2;
  int boomSpeedPin;

  int speed = 100 ;
  int boomSpeed = 120;

  public:

  Motors(int lpin1, int lpin2, int lspeedpin, int rpin1, int rpin2, int rspeedpin, int bPin1, int bPin2, int bSpeedPin) {
    leftpin1 = lpin1;
    leftpin2 = lpin2;
    leftspeedpin = lspeedpin;
    rightpin1 = rpin1;
    rightpin2 = rpin2;
    rightspeedpin = rspeedpin;
    boomPin1 = bPin1;
    boomPin2 = bPin2;
    boomSpeedPin = bSpeedPin;

    pinMode(leftpin1, OUTPUT);
    pinMode(leftpin2, OUTPUT);
    pinMode(leftspeedpin, OUTPUT);
    pinMode(rightpin1, OUTPUT);
    pinMode(rightpin2, OUTPUT);
    pinMode(rightspeedpin, OUTPUT);
    pinMode(boomPin1, OUTPUT);
    pinMode(boomPin2, OUTPUT);
    pinMode(boomSpeedPin, OUTPUT);
  }

  void setSpeed(int s){
    speed = s;
  }

  // void setBoomSpeed(int s){
  //   boomSpeed = 100;
  // }

  int getBoomSpeed() const {
    return boomSpeed;
  }

  int getSpeed() const {
    return speed;
  }

  void moveForward(){
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,HIGH);
    digitalWrite(rightpin2,LOW);
    analogWrite(rightspeedpin,speed);
  }
  void moveBackward(){
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,HIGH);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,HIGH);
    analogWrite(rightspeedpin,speed);
  }
  void turnLeft(){
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,HIGH);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,HIGH);
    digitalWrite(rightpin2,LOW);
    analogWrite(rightspeedpin,speed);
  }
  void turnRight(){
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,HIGH);
    analogWrite(rightspeedpin,speed);
  }


  void stop(){
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,LOW);
    analogWrite(leftspeedpin,0);
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,LOW);
    analogWrite(rightspeedpin,0);
  }
  
  void lowerBoom(){
    digitalWrite(boomPin1, HIGH);
    digitalWrite(boomPin2, LOW);
    analogWrite(boomSpeedPin, boomSpeed);
  }

  void raiseBoom(){
    digitalWrite(boomPin1, LOW);
    digitalWrite(boomPin2, HIGH);
    analogWrite(boomSpeedPin, boomSpeed);
  }

  void stopBoom(){
    digitalWrite(boomPin1, LOW);
    digitalWrite(boomPin2, LOW);
    analogWrite(boomSpeedPin, 0);
  }
};