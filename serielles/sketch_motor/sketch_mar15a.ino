int motor1_A=11;
int motor1_B=10;
int motor1_Speed=9;
  
int motor2_A=6;
int motor2_B=5;
int motor2_Speed=3;
  
void setup(){
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);
}
  
void loop(){
    digitalWrite(motor1_B,LOW);
    digitalWrite(motor2_B,LOW);
    digitalWrite(motor1_A,HIGH);
    digitalWrite(motor2_A,HIGH);
    
    analogWrite(motor1_Speed,255);
    analogWrite(motor2_Speed,255);
    
    delay(2000);
    analogWrite(motor1_Speed,0);
    analogWrite(motor2_Speed,0);
    
    digitalWrite(motor1_A,LOW);
    digitalWrite(motor2_A,LOW);
    digitalWrite(motor1_B,HIGH);
    digitalWrite(motor2_B,HIGH);
    analogWrite(motor2_Speed,255);
    analogWrite(motor1_Speed,255);
    
    delay(2000);
    analogWrite(motor1_Speed,0);
    analogWrite(motor2_Speed,0);
    
    digitalWrite(motor1_A,LOW);
    digitalWrite(motor1_B,LOW);
    digitalWrite(motor2_A,LOW);
    digitalWrite(motor2_B,LOW);
  
#if 0
  // motor1
  for (int i=0; i>256; i+=5){
    digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor1_B,LOW);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor1_B,LOW);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  // motor2
  for (int i=0; i<256; i+=5){
    digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor2_B,LOW);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
    digitalWrite(motor2_B,LOW);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  
  // turn vice versa
  
  // motor1
  for (int i=0; i<256; i+=5){
    digitalWrite(motor1_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor1_B,HIGH);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor1_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor1_B,HIGH);
    analogWrite(motor1_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  // motor2
  for (int i=0; i<256; i+=5){
    digitalWrite(motor2_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor2_B,HIGH);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
  for (int i=255; i>0; i-=5){
    digitalWrite(motor2_A,LOW); // A = LOW and B = HIGH means the motor will turn left
    digitalWrite(motor2_B,HIGH);
    analogWrite(motor2_Speed,i); // speed counts from 0 to 255
    delay(20);
  }
#endif
}

