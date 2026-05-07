#include "HX711.h"
// All lines commented with R shall be removed for final prototype

// Establish the pins for sensors
int pinBloodA = A0;
int pinBloodB = A1;
int pinPressure = A3;


#define DOUT  3
#define CLK  2
#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

// Establish the pins for LEDs
int ledRed = 4;
int ledGreen = 5;
int ledBlue = 6;

HX711 scale;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // R
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  digitalWrite(ledBlue,HIGH);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int bloodBefore = analogRead(pinBloodA);
  int bloodAfter = analogRead(pinBloodB);
  bool bloodDiff = bloodBefore != bloodAfter;
  float pressure = scale.get_units();

  if(pressure >= 10.0 || pressure <= -10.0) {
    digitalWrite(ledBlue,LOW);
    digitalWrite(ledRed,LOW);
    digitalWrite(ledGreen,HIGH);
  } else {
    digitalWrite(ledBlue,LOW);
    digitalWrite(ledRed,HIGH);
    digitalWrite(ledGreen,LOW);
  }
  Serial.println(pressure); // R

  delay(100);
}
