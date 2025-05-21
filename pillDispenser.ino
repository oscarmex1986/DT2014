#include <Servo.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

Servo servoOne; 
Servo servoTwo; 
Servo servoThree;
Servo servoFour; 
Servo servoLock;

int openingDelay = 140;

long timeOfDay = 0;
long secondsInADay = 86400;
int timeStep = 900; // Time step in actual milliseconds

int pinLock = 5;
int pinButton = 6;
int pinBuzzer = 7;
int pinOne = 8;
int pinTwo = 9;
int pinThree = 10;
int pinFour = 11;
int pinSensor = 12;
int angleOne = 90; 
int angleTwo = 90; 
int angleThree = 90;
int angleFour = 90;
int angleLock = 0;
bool buttonToggle = false;

bool arePillsIn(){
  bool r = false;
  VL53L0X_RangingMeasurementData_t measure;
  double average = 0.0;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
   if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    //Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    for(int i = 0; i < 10; i++){
      average += measure.RangeMilliMeter;
      delay(10);
    }
    average = average/10;
    if(average < 104.0){
      r = true;
    }
  } else {
    Serial.println(" out of range ");
  }
  Serial.print("Sensor detects: ");Serial.println(r);
  return r;
}

void beeper(){
  for(int i = 0; i < 3; i++){
    digitalWrite(pinBuzzer,HIGH);
    delay(100);
    digitalWrite(pinBuzzer,LOW);
    delay(100);
  }
}

void toggleLock(){
  if(angleLock == 180){
    angleLock = 0;
  } else {
    angleLock = 180;
  }
  servoLock.write(angleLock);
  delay(110);
}

void openA(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening A");
    servoOne.write(0);
    delay(openingDelay);
    Serial.println("Closing A");
    servoOne.write(angleOne);
    delay(openingDelay*2);
  }
}

void openB(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening B");
    servoOne.write(180);
    delay(openingDelay);
    Serial.println("Closing B");
    servoOne.write(angleOne);
    delay(openingDelay*2);
  }
}

void openC(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening C");
    servoTwo.write(180);
    delay(openingDelay);
    Serial.println("Closing C");
    servoTwo.write(90);
    delay(openingDelay*2);
  }
}

void openD(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening D");
    servoFour.write(0);
    delay(openingDelay);
    Serial.println("Closing D");
    servoFour.write(angleFour);
    delay(openingDelay*2);
  }
}

void openE(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening E");
    servoTwo.write(0);
    delay(openingDelay);
    Serial.println("Closing E");
    servoTwo.write(90);
    delay(openingDelay*2);
  }
}

void openF(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening F");
    servoFour.write(180);
    delay(openingDelay);
    Serial.println("Closing F");
    servoFour.write(angleFour);
    delay(openingDelay*2);
  }
}

void openG(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening G");
    servoThree.write(180);
    delay(openingDelay);
    Serial.println("Closing G");
    servoThree.write(angleThree);
    delay(openingDelay*2);
  }
}

void openH(int n){
  for(int i = 0; i < n; i++){
    Serial.println("Opening H");
    servoThree.write(0);
    delay(openingDelay);
    Serial.println("Closing H");
    servoThree.write(90);
    delay(openingDelay*2);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("Pill sensor in range\n\n")); 
  servoOne.attach(pinOne);
  servoTwo.attach(pinTwo);
  servoThree.attach(pinThree);
  servoFour.attach(pinFour);
  servoLock.attach(pinLock);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinSensor,INPUT);
  pinMode(pinButton,INPUT);
  servoOne.write(90); servoTwo.write(90); servoThree.write(90); servoFour.write(90);servoLock.write(angleLock);

  //Initialize display
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Pill dispenser");
  lcd.setCursor(2,1);
  lcd.print("Initalizing...");
   lcd.setCursor(0,2);
  lcd.print("...");
   lcd.setCursor(2,3);
  lcd.print("Initializing...");
  lcd.clear();
}

void loop() {
  
  //For Demo purposes, we equate one minute to one second
  long h = (timeOfDay/3600); 
  long m = (timeOfDay -(3600*h))/60;
  long s = (timeOfDay -(3600*h)-(m*60));
  
  // For demo purposes only
  // Doses occur every 8 or 12 hours, and at 9:00 pm
  int timeToEight = 8 - h%8;
  int timeToTwelve = 12 - h%12;
  int timeToNine = 21 - h;
  
  Serial.print(min(timeToNine,min(timeToEight,timeToTwelve)));Serial.println(" for the next dose");

  Serial.print(timeOfDay);Serial.print(" - ");Serial.print(h);Serial.print(":");Serial.print(m);Serial.print(":");Serial.println(s);
  if(m==0) {
    lcd.clear();
    lcd.setCursor(0, 0);lcd.print(h);lcd.print(":");lcd.print("0");lcd.print(m);lcd.print(" ");lcd.print(min(timeToNine,min(timeToEight,timeToTwelve)));
    lcd.print("t kvar");  
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);lcd.print(h);lcd.print(":");lcd.print(m);lcd.print(" ");lcd.print(min(timeToNine,min(timeToEight,timeToTwelve)));
    lcd.print("t kvar");  
  }
  
  //Pills for every 8 hours: A, C, H
  int doseEight[] = {1,3,8};
  //Pills for every 12 hours: D, G
  int doseTwelve[] = {4,7};
  //Pills for before sleeping: B, E
  int doseSleep[] = {2,5};
  //Save if we shall serve a pill
  int dose[] = {0,0,0,0,0,0,0,0};
  // Check if time is multiple for each dose
  if(h % 8 == 0 && m == 0){
    Serial.println("Dose for Eight Hours");
    for(int i = 0; i < 3; i++){
      for (int j = 1; j <= 8; j++){
        if(doseEight[i] == j) {
          dose[j-1]++;
          Serial.print(j);Serial.print(": ");Serial.println(dose[j-1]);
        }
      }
    }
  }
  if(h % 12 == 0 && m == 0){
    Serial.println("Dose for Twelve Hours");
    for(int i = 0; i < 2; i++){
      for (int j = 1; j <= 8; j++){
        if(doseTwelve[i] == j) {
          dose[j-1]++;
          Serial.print(j);Serial.print(": ");Serial.println(dose[j-1]);
        }
      }
    }
  }
  if(h == 21 && m == 0){
    Serial.println("Dose for Before Sleep");
    for(int i = 0; i < 2; i++){
      for (int j = 1; j <= 8; j++){
        if(doseSleep[i] == j) {
          dose[j-1]++;
          Serial.print(j);Serial.print(": ");Serial.println(dose[j-1]);
        }
      }
    }
  }

  //Serve the pills
  for(int i = 1; i <= 8; i++){
      switch (i){
        case 1:
          openA(dose[i-1]);
          break;
        case 2:
          openB(dose[i-1]);
          break;
        case 3:
          openC(dose[i-1]);
          break;
        case 4:
          openD(dose[i-1]);
          break;
        case 5:
          openE(dose[i-1]);
          break;
        case 6:
          openF(dose[i-1]);
          break;
        case 7:
          openG(dose[i-1]);
          break;
        case 8:
          openH(dose[i-1]);
          break;
      }
  }
  if(arePillsIn()) {
    Serial.println("Pills are in... beeping...");
    lcd.setCursor(0, 1);
    lcd.print("Pills are in!");
    beeper();
  } 
  timeOfDay = timeOfDay + timeStep;
  if (timeOfDay >= secondsInADay) {timeOfDay = 0;lcd.clear();}
  if(digitalRead(pinButton) == LOW){
    Serial.println("Button Pressed...");
    toggleLock();
  }
  delay(timeStep);
}
