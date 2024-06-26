#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

HX711_ADC LoadCell(8, 9);            // Parameters: dt pin 6, sck pin 7;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

int enPin = 3;
int in1Pin = 2;
int in2Pin = 4;

int enPin2 = 6;
int in3Pin = 7;
int in4Pin = 5;

int irsensor = A0;
int irsensor2 = A1;

const long interval = 6000;
unsigned long stoptime = 0;
bool isMotorStopped = false;
bool irdetected = false;
bool motorstart = false;

void setup() {
  pinMode(enPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(enPin2, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, 100);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 100);

  Serial.begin(9600);  // Initialize serial communication
  lcd.begin(16, 2);    // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();
  LoadCell.begin();               // Start connection to HX711
  LoadCell.start(2000);           // Allow 2000ms for the load cell to stabilize
  LoadCell.setCalFactor(1000.0);  // Calibration factor for load cell; adjust as needed
}

void loop() {
  LoadCell.update();                          
  long rawValue = 10 * (LoadCell.getData());  

  int sensorValue = analogRead(irsensor);
  int sensorValue2 = analogRead(irsensor2);

  if (sensorValue2 < 600) {
    motorforward();
    motorstart = true;
  } else {
    if (motorstart) {

    } else {
      motorstop();
    }
  }

  
    // Motor is moving forward continuously until sensor1 detects an object
    if (sensorValue < 600 && !irdetected) {
      irdetected = true;
      motorstart = false;
      motorstop();
      stoptime = millis();
    } else if (irdetected && (millis() - stoptime >= interval)) {
      if (rawValue > 40) {
        motorbackward();
        delay(3000);  // Run backward for 3 seconds
      } else {
        motorforward();
        delay(4000);  // Run forward for 4 seconds
      }
      motorstop();
      irdetected = false;
    }
  

  lcd.clear();                
  lcd.setCursor(0, 0);        
  lcd.print("Weight [g]: ");  
  lcd.setCursor(0, 1);        
  lcd.print(rawValue);        

  delay(100);  
}




void motoron() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, 190);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 190);
}

void motorstop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, 0);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 0);
}

void motorforward() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, 190);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 190);
}

void motorbackward() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enPin, 190);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enPin2, 190);
}