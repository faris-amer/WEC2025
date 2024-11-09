#include <Arduino.h>

class Motors{
  private:
  int leftpin1;
  int leftpin2;
  int leftspeedpin;
  int rightpin1;
  int rightpin2;
  int rightspeedpin;
  int speed;
  public:

  Motors(int lpin1, int lpin2, int lspeedpin,int rpin1, int rpin2, int rspeedpin){
    leftpin1 = lpin1;
    leftpin2 = lpin2;
    leftspeedpin = lspeedpin;
    rightpin1 = rpin1;
    rightpin2 = rpin2;
    rightspeedpin = rspeedpin;
  }

  void setSpeed(int s){
    speed = s;
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
  
  void lowerBoom(){}
  void raiseBoom(){}
  void stopBoom(){}
};