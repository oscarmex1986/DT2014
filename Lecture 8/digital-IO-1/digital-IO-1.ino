int buttonState = 0; // See slides to learn why we use int
int lastButtonState = 0; 
int ledState = LOW; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT); // Set pin 2 as input
  pinMode(LED_BUILTIN, OUTPUT); // Setup the built-in led
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(2); // We see if the button is pressed
  if(buttonState == LOW){
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    if (ledState == LOW) { //Button pressed, led is off
      Serial.println("LED OFF");
    } else if (ledState == HIGH) { //Button pressed, led is ON
      Serial.println("LED ON");
    }
  }
  
  delay(150);

}
