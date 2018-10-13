/*
 * Folgender Code testet die Startfunktion nach betätigen des User Pushbuttons.
 * Das Programm wird durch Drücken des User Pushbuttons gestartet. Der Buzzer ertönt 
 * 5 Mal für die Dauer von 250ms, jeweils mit einer anschließenden Pause von 1s (1000ms). 
 * Nach dem erfolgreichen Durchlaufen der Buzzer-Schleife leuchtet die User LED auf.
 * Durch Drücken des User Pushbuttons schaltet sich die User LED aus. 
 * Ein erneutes Drücken startet das Programm von vorn.
 */

#include <Wire.h>
#include <ZumoShield.h>

#define LED_PIN 13

Pushbutton button(ZUMO_BUTTON);
ZumoBuzzer buzzer;

unsigned char i;

void setup() {
}

void loop() {
  // Durch Drücken des User Pushbuttons wird das Programm gestartet
  button.waitForButton();

  // Buzzer ertönt 5
  for(i=0; i<5; i++){ 
    delay(1000);
    buzzer.playNote(NOTE_G(3), 250, 7);    
  }
 
  delay(1000);

  // User LED leuchtet auf
  digitalWrite(LED_PIN, HIGH);
  button.waitForButton();
  digitalWrite(LED_PIN, LOW);
  
}
