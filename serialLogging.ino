// Variables to keep control of the time
long step = 100;
long timeCounter = 0;
long timeLimit = 30000;

// Variable to add headers to the csv file
bool firstTime = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7) == HIGH && timeCounter <= timeLimit){
    if(firstTime == true){
      Serial.println("time,light,temp");
      firstTime = false;
    }
    Serial.print(timeCounter);
    Serial.print(",");
    Serial.print(analogRead(0));
    Serial.print(",");
    Serial.println(analogRead(1));
    timeCounter += step;
  }
  delay(step);
}
