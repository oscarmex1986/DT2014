/*
This program shows you how to sense two variables (temperature, luminosity)
and use actuators (PWM) to represent the level
of complexity we expect from your final project.

This represents, e.g., the automation of a light and temperature
that reacts to the amount of perceived light and the difference
in temperature.
*/

int potPin = A0; // We connect our potentiometer to A0
int ldrPin = A2; // We connect our light sensor to A2
int tempPin = A3; // Our temperature sensor pin
int redLedPin = 5; // Set a PWM pin for heating
int greenLedPin = 6; // Set a PWM pin for cooling
int ledPin = 3; // Set a PWM pin for a illumination


void setup() {
  Serial.begin(9600); // To monitor and debug
  pinMode(potPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

float desiredTemperature(){
  // Read sensor and return desired temperature between 10 and 30 Celsius
  int v = analogRead(potPin);
  return max(10.0, (1.0 - (v / 1023.0)) * 30.0);
}

float tempInCelsius(){
  // Read sensor and calculate temperature
  int Vo = analogRead(tempPin);
  float logR2 = log(1000 * (1023.0 / (float)Vo - 1.0)); // For a 10kOhm resistor
  float temp = (1.0 / (1.009249522e-03 + 2.37840544e-04 * logR2 + 2.019202697e-07 * logR2 * logR2 * logR2));
  return temp - 273.15; // Temp in Celsius
}

float relativeLuminosity(){
  // Read sensor and return percentage of luminosity
  int v = analogRead(ldrPin);
  return 1.0 - (v / 1023.0);
}


void controlTemperature(float t, float lim){
  if(t > lim){
    // t is higher than lim, turn on cooling
    int difference = (t - lim) / 20 * 255;
    analogWrite(greenLedPin, difference); // Here, you can have a motor controlling a fan
    analogWrite(redLedPin, 0);
  } else {
    // t is lower than lim, turn on heating
    int difference = (lim - t) / 20 * 255;
    analogWrite(redLedPin, difference); // Here, you can have a relay controlling a heater
    analogWrite(greenLedPin, 0);
  }
}

void controlLights(float r){
  // Complement the relative luminosity with what is left to make a full PWM cycle
  int lampLevel = 255 - 255 * r;
  analogWrite(ledPin, lampLevel);
}

void loop() {
  float temperature = tempInCelsius();
  float luminosity = relativeLuminosity();
  float thTemp = desiredTemperature();
  controlTemperature(temperature, thTemp);
  controlLights(luminosity);
  Serial.print("Temp: ");Serial.print(temperature);Serial.print(" Desired:");Serial.print(thTemp);
  Serial.print(" Rel. Lum: ");Serial.println(luminosity);
  
  delay(1000);

}
