/*
HC-SR04 Ping distance sensor
VCC to arduino 5v, GND to arduino GND
Echo to Arduino pin 13, Trig to Arduino pin 12
Red POS to Arduino pin 11, Green POS to Arduino pin 10
*/

#define trigPin 13
#define echoPin 12
#define ledRed 11
#define ledGreen 10

void setup() {
  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Schallgeschwindigkeit 340 m/s (15 Grad) u. 343 m/s (20)
  long distance = float(duration / 2) / 29.2f;
  //long distance = duration / 58;

  // This is where the LED On/Off happens
  // When the Red condition is met, the Green LED should turn off
  if (distance <= 2 || distance >= 400) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  }
  else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
  }

  //String str = String(distance) + " cm";
  Serial.println(distance);

  delay(62);
}

