#include "pitches.h"
#include "button.h"
#include "buzzer.h"


#define PIN_BUZZER 6
#define PIN_BUTTON 5

Button button(PIN_BUTTON);
Buzzer buzzer(PIN_BUZZER);


int notes[] = {NOTE_G4,NOTE_SILENCE,NOTE_G4,NOTE_SILENCE,NOTE_G4,NOTE_SILENCE,NOTE_DS4,NOTE_SILENCE,NOTE_AS5,NOTE_SILENCE,NOTE_G4,NOTE_SILENCE,NOTE_DS4,NOTE_SILENCE,NOTE_AS5,NOTE_SILENCE,NOTE_G4,NOTE_SILENCE,  NOTE_D5,NOTE_SILENCE,NOTE_D5,NOTE_SILENCE,NOTE_D5,NOTE_DS5,NOTE_AS5,NOTE_FS4,NOTE_DS4,NOTE_AS5,NOTE_G4, NOTE_G5,NOTE_G4,NOTE_G5,NOTE_FS5,NOTE_F5,NOTE_E5,NOTE_DS5,NOTE_E5, NOTE_GS4,NOTE_GS5,NOTE_GS4,NOTE_C5,NOTE_B5,NOTE_AS5,NOTE_A5,NOTE_AS5 ,NOTE_DS4,NOTE_FS4,NOTE_DS4,NOTE_AS5,NOTE_G4,NOTE_DS4,NOTE_AS5,NOTE_G4};
double durations[] = {4,1,4,1,4,1,2,1,4,1,2,1,1,1,4,1,2, 4,1,4,1,4,2,1,4,2,1,8,4,2,1,4,2,1,1,1,2,2,4,2,1,1,1,2,2,4,2,1,4,2,1,8};
int melodyLength = 52;

bool buttonWasPressed = false;
uint64_t startTiming = millis();
uint64_t screamTiming = millis();
//uint64_t screamTiming = millis();
bool isScreaming = false;

void setup() {
    buzzer.setMelody(notes, durations, melodyLength);
    buzzer.turnSoundOn();
}

void loop() {
  
    if (button.wasPressed())
    {
      startTiming = millis();
      screamTiming = millis();
      buttonWasPressed = true;
     }
    if (buttonWasPressed){
      if(millis() - startTiming<30000){
        if (!isScreaming && millis()-screamTiming > 4950) {
          tone(PIN_BUZZER,NOTE_G4);
          screamTiming=millis();
          isScreaming = true;
        }
        else if (millis()-screamTiming>50){
          isScreaming = false;
          noTone(PIN_BUZZER);
        }
      }
      else {
        buzzer.playSound();
      }
    }
}
