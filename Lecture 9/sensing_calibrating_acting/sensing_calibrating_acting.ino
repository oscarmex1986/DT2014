/*
This program shows you how to sense a variable (distance)
and use an actuator (piezoelectric) to represent the level
of complexity we expect from your final project.

This represents, e.g., the crash sensor in a vehicle when
you are backing up and vision is limited.
*/

#include <afstandssensor.h> // Library with the software for SR04

AfstandsSensor afstandssensor(3, 2);  // Starts SR04 on pins 3 and 2.
// If you read the .h class, you see that the constructor for a distance sensor
// in this class is Afstandssensor(int triggerPin, int echoPin)

#define BUZZER_PIN 12 // We are using an active buzzer like the one in your box
int potPin =  A0; // We are using a potentiometer like the one in your box

void setup() {
  Serial.begin(9600); //To write to the console and perform some debugging
  pinMode(BUZZER_PIN, OUTPUT); // We configure the buzzer pin as output
  pinMode(potPin, INPUT); // We configure the buzzer pin as input
}

void buzz(double d, double th){
  digitalWrite(BUZZER_PIN, HIGH);
  delay((int)((d/th)*1000));
  digitalWrite(BUZZER_PIN, LOW);
  delay((int)((d/th)*1000));
}

void loop() {
  // We acquire the distamce
  double distance = afstandssensor.afstandCM(); // Requests for the SR04 Distance in CM
  double thDistance = (analogRead(potPin)/1023.0)*400;
  Serial.print("Threshold Distance: "); Serial.print(thDistance,2); Serial.print(" Measured Distance: "); 
  int buzzerDelay = 1000;
  if(distance < thDistance) buzz(distance,thDistance);
  Serial.println(distance);
  delay(10);
}
