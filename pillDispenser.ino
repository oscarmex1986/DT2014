#include <Servo.h>

Servo servoOne, servoTwo, servoThree, servoFour; 

int openingDelay = 70;

long timeOfDay = 0;
long secondsInADay = 86400;
int timeStep = 900; // Time step in actual milliseconds

int pinOne = 8;
int pinTwo = 9;
int pinThree = 10;
int pinFour = 11;
int angleOne = 90; 
int angleTwo = 90; 
int angleThree = 90;
int angleFour = 90;



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
  servoOne.attach(pinOne);
  servoTwo.attach(pinTwo);
  servoThree.attach(pinThree);
  servoFour.attach(pinFour);
  servoOne.write(90); servoTwo.write(90); servoThree.write(90); servoFour.write(90);
}

void loop() {
  
  //For Demo purposes, we equate one minute to one second
  long h = (timeOfDay/3600); 
  long m = (timeOfDay -(3600*h))/60;
  long s = (timeOfDay -(3600*h)-(m*60));

  Serial.print(timeOfDay);Serial.print(" - ");Serial.print(h);Serial.print(":");Serial.print(m);Serial.print(":");Serial.println(s);

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
  timeOfDay = timeOfDay + timeStep;
  if (timeOfDay >= secondsInADay) {timeOfDay = 0;}
  delay(timeStep);
}
