#include <Servo.h>

Servo myservo;
Servo myservo2;

int EnA = 2;
int in1 = 22;
int in2 = 24;

int EnB = 3;
int in3 = 26;
int in4 = 28;

int Ena = 4;
int in11 = 38;
int in22 = 40;

int Enb = 5;
int in33 = 42;
int in44 = 44;

int button1 = 32;
int button2 = 34;

void setup() {
  pinMode(EnA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(EnB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(EnA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(EnB, 0);

  pinMode(Ena, OUTPUT);
  pinMode(in11, OUTPUT);
  pinMode(in22, OUTPUT);

  pinMode(Enb, OUTPUT);
  pinMode(in33, OUTPUT);
  pinMode(in44, OUTPUT);

  digitalWrite(in11, LOW);
  digitalWrite(in22, LOW);
  analogWrite(Ena, 0);

  digitalWrite(in33, LOW);
  digitalWrite(in44, LOW);
  analogWrite(Enb, 180);

  myservo.attach(48);
  myservo.write(50);

  myservo2.attach(50);
  myservo2.write(50);
  
}
void loop() {
  int value1 = digitalRead(button1);
  int value2 = digitalRead(button2);

  if (value1 == HIGH) {
    oneforward();
    motorAforward();
    myservo.write(110);
    delay(5000);
    onestop();
    motorAstop();
    myservo.write(50);
  }

  if (value2 == HIGH) {
    oneforward();
    motorBforward();
    myservo2.write(110);
    delay(5000);
    motorBstop();
    onestop();
    myservo2.write(50);
  }
}

void onestop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(EnA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(EnB, 0);
}

void oneforward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(EnA, 200);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EnB, 190);
}

void motorAstop() {
  digitalWrite(in11, LOW);
  digitalWrite(in22, LOW);
  analogWrite(Ena, 0);
}

void motorAforward() {
  digitalWrite(in11, HIGH);
  digitalWrite(in22, LOW);
  analogWrite(Ena, 200);
}

void motorBstop() {
  digitalWrite(in33, LOW);
  digitalWrite(in44, LOW);
  analogWrite(Enb, 0);
}

void motorBforward() {
  digitalWrite(in33, HIGH);
  digitalWrite(in44, LOW);
  analogWrite(Enb, 200);
}
