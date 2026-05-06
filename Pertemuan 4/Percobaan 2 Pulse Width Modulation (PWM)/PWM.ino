#include <Arduino.h> 

const int potPin = A0;   
const int ledPin = 9;   

int nilaiADC = 0; 
int pwm = 0;       

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  nilaiADC = analogRead(potPin); 
  pwm = map(nilaiADC, 0, 1023, 0, 255); 

  analogWrite(ledPin, pwm); 
  Serial.print("ADC: ");
  Serial.print(nilaiADC); 

  Serial.print(" | PWM: ");
  Serial.println(pwm); 
  delay(50); 
}