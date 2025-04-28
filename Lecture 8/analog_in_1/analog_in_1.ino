int anaPin = A0; // Analog pin A0 is specified here  
int value = 0; // variable declared to store the value we read  
int threshold = 512;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // We simulate a lamp that turns on
}

void loop()
{
  value = analogRead(anaPin); // It reads the input pin    
  Serial.print("Illumination: ");
  Serial.print(value);
  if (value > threshold){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(" LAMP ON");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println(" LAMP OFF");
  }

  delay(500);
}

