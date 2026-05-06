#include <Servo.h> 

Servo myservo; 

const int potensioPin = A0;   
const int servoPin = 9;      

int pos = 0; 
int val = 0; 

void setup() {
  myservo.attach(servoPin); 
  Serial.begin(9600); 
}

void loop() {
  val = analogRead(potensioPin); 
  pos = map(val, 0, 1023, 0, 180);  
  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); 
  delay(50); 
}