//HC-S501 PIR Bewegungssensor: Blau:P7  Schwarz:GND  Lila:5V

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int photoPin = A0; // Analog Input Photosensor with 1k resistor
int ledPin = 2;  // LED strip Data pin
int pirPin = 10; // Input HC-S501 PIR Bewegungssensor

int pirValue; // Place to store read PIR Value

// How many LEDs are attached to the Arduino?
#define NUMPIXELS 100

//Neopixels:
Adafruit_NeoPixel pixels(NUMPIXELS, ledPin, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 30 // Time (in milliseconds) to pause between pixels


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  //Neopixels:
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);
  int photoValue = analogRead(photoPin);
  Serial.println(photoValue);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  if (pirValue == HIGH && photoValue < 1)
  {
    Serial.println("Lights going on");
    digitalWrite(LED_BUILTIN, HIGH);
    //Ramp up to Red
    for(int j=0; j<150; j++) {
      pixels.fill(pixels.Color(j, 0, 0));
      delay(40);  //1000=slow ramp
      pixels.show();
    }
    Serial.println("Lights on full power, wait for x seconds:");
    delay(900000);  //Light on for x Milliseconds  3600000 = 1h, 
    //delay(30);
    Serial.println("Lights going out");
    for(int j=250; j>1; j--) {
      pixels.fill(pixels.Color(j, j/8, j/8));
      delay(40);
      pixels.show();
    }
  }
  else
  {
    Serial.println("OFF");
    digitalWrite(LED_BUILTIN, LOW);
    pixels.clear();
    pixels.show();
  }
  
  /*
  if (pirValue == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    //Ramp up to Red
    for(int j=0; j<250; j++) {
      pixels.fill(pixels.Color(j, j/2, j/4));
      delay(j);
      pixels.show();
    }
    delay(5000);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    pixels.clear();
    pixels.show();
  }
  */
}
