//www.elegoo.com
//2016.12.9

int ledPin = 13;  // LED on Pin 13 of Arduino
int pirPin = 7; // Input for HC-S501

int pirValue; // Place to store read PIR Value


void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
  
}

void loop() {
  pirValue = digitalRead(pirPin);
  if (pirValue == HIGH)
  {
    for (int i = 0; i < 50; i++)
    {    
      digitalWrite(ledPin, HIGH);
      delay(50);
      digitalWrite(ledPin, LOW);
      delay(50);
    }
  }
  else
  {
    digitalWrite(ledPin, LOW);  
  }
}
