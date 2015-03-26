/*
HC-SR04 Ping distance sensor
VCC to arduino 5v, GND to arduino GND
Echo to Arduino pin 13, Trig to Arduino pin 12
Red POS to Arduino pin 11, Green POS to Arduino pin 10
*/

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10

void setup() {
  Serial.begin (9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;
  
  // This is where the LED On/Off happens
  // When the Red condition is met, the Green LED should turn off
  if (distance < 4 || distance >= 200) {  
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
  }
  else {
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
  }
  
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500);
}

