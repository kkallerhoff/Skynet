/*
 * Die Testfunktion 'zumoSetSpeeds' testet die Ansteuerung der beiden Motoren. Die Motoren werden
 * sowohl einzeln als auch zusammen angesprochen. Die Motoren werden für jeweils 1 Sekunde auf
 * 25%, 50% und 100% Leistung in beide Richtungen angesteuert.
 * 
 * Die Funktion'zumoSetSpeeds' erhält folgende Parameter:
 * 
 * int speedLeftMotor: Geschwindigkeit des linken Motors
 * int speedRightMotor: Geschwindigkeit des rechten Motors
 * int driveDuration: Dauer der Motoransteuerung (Default ist der Wert von DRIVE_DURATION)
 * int pauseDuration: Dauer der Pause nach der Motoransteuerung (Default ist der Wert von PAUSE_DURATION)
 */

#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

#define MAX_SPEED       400
#define DRIVE_DURATION  1000 // Millisekunden
#define PAUSE_DURATION  500  // Millisekunden

// helper functions


void zumoSetSpeeds(int speedLeftMotor, int speedRightMotor, int driveDuration = DRIVE_DURATION, int pauseDuration = PAUSE_DURATION){
  motors.setSpeeds(speedLeftMotor, speedRightMotor);
  delay(driveDuration);
  motors.setSpeeds(0,0);
  delay(pauseDuration);
}

void setup() {

}

void loop() {

  button.waitForButton();

  // 100% Geschwindigkeit vorwärts auf linkem und rechtem Motor
  zumoSetSpeeds(MAX_SPEED, MAX_SPEED);

  // 100% Geschwindigkeit rückwärts auf linkem und rechtem Motor
  zumoSetSpeeds(-MAX_SPEED, -MAX_SPEED);

  // 50% Geschwindigkeit vorwärts auf linkem und rechtem Motor
  zumoSetSpeeds(MAX_SPEED * 0.5, MAX_SPEED * 0.5);

  // 50% Geschwindigkeit rückwärts auf linkem und rechtem Motor
  zumoSetSpeeds(-MAX_SPEED * 0.5, -MAX_SPEED * 0.5);

  // 25% Geschwindigkeit vorwärts auf linkem und rechtem Motor
  zumoSetSpeeds(MAX_SPEED * 0.25, MAX_SPEED * 0.25);

  // 25% Geschwindigkeit rückwärts auf linkem und rechtem Motor
  zumoSetSpeeds(-MAX_SPEED * 0.25, -MAX_SPEED * 0.25);

  // 100% Geschwindigkeit vorwärts linker Motor
  //   0% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(MAX_SPEED, 0);

  // 50% Geschwindigkeit vorwärts linker Motor
  //   0% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(MAX_SPEED * 0.5, 0);

  // 25% Geschwindigkeit vorwärts linker Motor
  //   0% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(MAX_SPEED * 0.25, 0);

  // 25% Geschwindigkeit rückwärts linker Motor
  //   0% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(-MAX_SPEED * 0.25, 0);

  // 50% Geschwindigkeit rückwärts linker Motor
  //   0% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(-MAX_SPEED * 0.5, 0);

  // 100% Geschwindigkeit rückwärts linker Motor
  //   0% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(-MAX_SPEED, 0);

  //  0% Geschwindigkeit vorwärts linker Motor
  // 100% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(0, MAX_SPEED);
  
  //  0% Geschwindigkeit vorwärts linker Motor
  // 50% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(0, MAX_SPEED * 0.5);

  //  0% Geschwindigkeit vorwärts linker Motor
  // 25% Geschwindigkeit vorwärts rechter Motor
  zumoSetSpeeds(0, MAX_SPEED * 0.25);

  //  0% Geschwindigkeit rückwärts linker Motor
  // 25% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(0, -MAX_SPEED * 0.25);

  //  0% Geschwindigkeit rückwärts linker Motor
  // 50% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(0, -MAX_SPEED * 0.5);

  //   0% Geschwindigkeit rückwärts linker Motor
  // 100% Geschwindigkeit rückwärts rechter Motor
  zumoSetSpeeds(0, -MAX_SPEED);
}
