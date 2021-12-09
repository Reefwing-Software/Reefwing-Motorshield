/******************************************************************
  @file    buzzer.ino
  @brief   Test the piezo buzzer on the Nexgen Carrier Board
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        08/12/21

  1.0 Original Release          08/12/21

******************************************************************/

#include <NexgenMotorShield.h>

NexgenMotorShield motorShield;

/******************************************************************
   Piezo BUZZER

   Note frequencies: are defined below e.g., NOTE_C4 = 262 Hz
   Note durations: 4 = quarter note, 8 = eighth note, etc.
 ******************************************************************/

#define REST     0
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

const int noteNumber = 8;
const int tune[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4};
const int durations[] = {4, 8, 8, 4, 4, 4, 4, 4};

void playNotes(const int notes[], const int noteDurations[], const int noteNumber) {

  for (int note = 0; note < noteNumber; note++) {

    int noteDuration = 1000 / noteDurations[note];
    int space = noteDuration * 1.30;

    digitalWrite(LED_BUILTIN, HIGH);
    tone(BUZZER, notes[note], noteDuration);
    delay(space);
    digitalWrite(LED_BUILTIN, LOW);
    noTone(BUZZER);
  }
}

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  playNotes(tune, durations, noteNumber);
  delay(1000);
}