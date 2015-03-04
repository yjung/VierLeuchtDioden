#include <avr/interrupt.h>

int LONE_GREEN = 5;
int RED = 11;
int YELLOW = 10;
int GREEN = 9;
int BTN = 2;

int state = 0;
volatile bool on = false;

char buf[16], str[80];
int cpos = 0;
bool first = true;


// Interrupt Service Routine attached to INT0 vector
void pin2ISR() {
    on = !on;
    
    //Serial.println(on);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LONE_GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BTN, INPUT);
  
  // Most 8-bit AVR’s like the ATMega328 have 2 hardware interrupts, INT0 and INT1.
  // If you’re using a standard Arduino board, these are tied to digital pins 2 and 3.
  attachInterrupt(0, pin2ISR, RISING);
}

void loop() {
  if (on) {
    analogWrite(LONE_GREEN, 0);
    
    switch(state) {
      case 0: setLights(HIGH, LOW, LOW, 2000); break;
      case 1: setLights(HIGH, HIGH, LOW, 900); break;
      case 2: setLights(LOW, LOW, HIGH, 3000); break;
      case 3: setLights(LOW, HIGH, LOW, 1000); break;
    }
    state = ++state % 4;
  }
  else {
    state = 0;
    setLights(LOW, LOW, LOW, 1);
   
    int val = analogRead(0);
    int value = (val >> 2) & 0xFF;
    
    //
    if (first) {
        first = false;
        sprintf(str, "0000, %04d: %03d\n", val, value);
        Serial.print(str);
    }
    else
    // send data only when you receive data
    while (Serial.available() > 0) {
      buf[cpos++] = Serial.read();
      
      if (cpos == 4) {
        buf[cpos] = '\0';
        cpos = 0;     
        
        sprintf(str, "%s, %04d: %03d\n", buf, val, value);
        Serial.print(str);
      }
    }
    //
    
    analogWrite(LONE_GREEN, value);
    delay(150);
  }
}

void setLights(int r, int y, int g, int dur) {
  digitalWrite(RED, r);
  digitalWrite(YELLOW, y);
  digitalWrite(GREEN, g);
  delay(dur);
}

