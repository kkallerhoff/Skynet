/*
 * Folgender Code liest die Stellung des Pushbuttons aus und gibt sie über 
 * die serielle Schnittstelle wieder. Die User LED zeigt zusätzlich den
 * aktuellen Status des Pushbuttons an.
 * Pushbutton gedrückt: LED an
 * Pushbutton nicht gedrückt: LED aus
 */

#include <Wire.h>
#include <ZumoShield.h>

Pushbutton button(ZUMO_BUTTON);

#define LED_PIN 13

void setup() {
  Serial.begin(9600);
}

void loop() {

  do
    {
      if(button.isPressed()){
        Serial.println("Button pressed: true");
        digitalWrite(LED_PIN, HIGH);
      }
      else{
        Serial.println("Button pressed: false");
        digitalWrite(LED_PIN, LOW);
      }
     }
  while(!button.isPressed());
}
