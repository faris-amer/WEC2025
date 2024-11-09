#include <Arduino.h>

class Motors{
  private:
  int leftpin1;
  int leftpin2;
  int leftspeedpin;
  int rightpin1;
  int rightpin2;
  int rightspeedpin;
  public:

  Motors(int lpin1, int lpin2, int lspeedpin,int rpin1, int rpin2, int rspeedpin){
    leftpin1 = lpin1;
    leftpin2 = lpin2;
    leftspeedpin = lspeedpin;
    rightpin1 = rpin1;
    rightpin2 = rpin2;
    rightspeedpin = rspeedpin;
  }

  void forwards(int speed){
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,HIGH);
    digitalWrite(rightpin2,LOW);
    analogWrite(rightspeedpin,speed);
  }

  void backwards(int speed){
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,HIGH);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,HIGH);
    analogWrite(rightspeedpin,speed);
  }

  void left(int speed){
    digitalWrite(leftpin1,LOW);
    digitalWrite(leftpin2,HIGH);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,HIGH);
    digitalWrite(rightpin2,LOW);
    analogWrite(rightspeedpin,speed);
  }
  void right(int speed){
    digitalWrite(leftpin1,HIGH);
    digitalWrite(leftpin2,LOW);
    analogWrite(leftspeedpin,speed);
    digitalWrite(rightpin1,LOW);
    digitalWrite(rightpin2,HIGH);
    analogWrite(rightspeedpin,speed);
  }

};