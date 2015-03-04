#include "pitches.h"

int ledPin = 12;
int ls = 11;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4 };

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  pinMode(ledPin, OUTPUT);
  pinMode(ls, OUTPUT);
  
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  #if 0
  sos();
  
  #else
  
  tone(ls, 440, 500);
  delay(300);
  tone(ls, 585, 900);
  delay(600);
  
  /*
  digitalWrite(ls, HIGH); 
  delayMicroseconds(1000);
  digitalWrite(ls, LOW);
  delayMicroseconds(1000);
  */
  #endif
}

void sos() {
  flash(ledPin, 100);
  delay(150);
  flash(ledPin, 200);
  flash(ledPin, 100);
  delay(300);
}

void flash(int pin, int dur) {
  for (int i=0; i<3; i++) {
    digitalWrite(pin, HIGH);
    delay(dur);
    digitalWrite(pin, LOW);
    delay(dur);
  }
}

