int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  
  Serial.begin(9600);
  delay(1000);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.println("AT+NAME<COWS>");
  delay(1000);
  Serial.println("AT+PIN<COWS>");
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  //delay(100);     
  Serial.println(sensorValue);     
  // turn the ledPin off:   
  if(sensorValue < 10)
  {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);  
    Serial.println("YO BITCH WATER IS LOW");   
  }
  //digitalWrite(ledPin, LOW);  
  else
  {
    delay(1000);
  } 
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);                  
}
