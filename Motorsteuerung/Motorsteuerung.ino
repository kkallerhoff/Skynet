/*
 * Der Roboter fährt für eine Sekunde geradeaus, führt eine 180 Grad Drehung durch und
 * fährt wieder eine Sekunde geradeaus mit einer anschließenden 180 Grad Drehung.
 * 
 */

#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
ZumoBuzzer buzzer;

#define SPEED 200

unsigned char i;


void drive(int geschwindigkeit, int dauer){
  motors.setSpeeds(geschwindigkeit, geschwindigkeit);
  delay(dauer);
}

/* die Sollwerte für die Geschwindigkeit der Motoren und
 * die Dauer der Drehung müssen durch Tests noch genau ermittelt werden.
 */
void turn180deg(){
  motors.setSpeeds(180,-180);
  delay(835);
  motors.setSpeeds(0,0);
  delay(1000);  
}

void setup() {

}

void loop() {

  button.waitForButton();
  delay(1000);

  // Roboter fährt 1s geradeaus
  drive(SPEED, 1000);

  // stop for 250ms
  //motors.setSpeeds(0,0);
  //delay(250);
  
  // 180° Drehung
  turn180deg();

  // Roboter fährt 1s geradeaus
  drive(SPEED, 1000);

  // 180° Drehung
  turn180deg();

  // stop
  motors.setSpeeds(0,0);  

}
