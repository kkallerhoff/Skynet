/*
 * Folgender Code testet die ordungsgemäße Funktion des ZumoBuzzers und der User LED.
 * Das Programm wird durch Drücken des User Pushbuttons gestartet. Der Buzzer ertönt 
 * 3 Mal für die Dauer von 250ms, jeweils mit einer anschließenden Pause von 1s (1000ms). 
 * Nach dem erfolgreichen Durchlaufen der Buzzer-Schleife leuchtet die User LED für 
 * 3 Sekunden auf, blinkt anschließend 3 mal und geht aus.
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

  // Buzzer-Schleife
  for(i=0; i<3; i++){ 
    delay(1000);
    buzzer.playNote(NOTE_G(3), 250, 7);    
  }
 
  delay(1000);

  // User LED leuchtet auf
  digitalWrite(LED_PIN, HIGH);
  delay(3000);
  digitalWrite(LED_PIN,LOW);
  delay(500);

  for(i=0; i<3; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
  
}
