/*
 * Der Roboter fährt auf einem schwarzen Untergrund (mit verschiedenen Geschwindigkeiten
 * unt unter verschiedenen Winkeln) auf eine weiße Linie zu. Beim Erkennen der weißen
 * Linie stoppt der Roboter und gibt ein akustisches Signal.
 */
#include <stdlib.h>
#include <Wire.h>
#include <ZumoShield.h>

ZumoReflectanceSensorArray sensors (QTR_NO_EMITTER_PIN);
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
ZumoBuzzer buzzer;

#define NUM_SENSORS 6
#define REFLECTANCE_THRESHOLD 1500

unsigned int sensor_values[NUM_SENSORS];

// helper functions

int randomNumber(){
  // erzeugt eine Zufallszahl zwischen 0 und 499
  int rnd = rand() % 500;

  int rndPosNeg = rand() % 2;

  if(rndPosNeg == 0){
    return -1;
  }
  else{
    return 1;
  }
}


void turnaround(){
  int randNumber = randomNumber();
  
  motors.setSpeeds(-150, -150);
  delay(250);
  
  motors.setSpeeds(-200, 200);
  delay(805 + randNumber);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  button.waitForButton();
  delay(1000);
  
  motors.setSpeeds(300,300);
  
  sensors.read(sensor_values);
  
  if(sensor_values[0] < REFLECTANCE_THRESHOLD){  
    turnaround();    
  }
  else if(sensor_values[5] < REFLECTANCE_THRESHOLD){
    turnaround();
  }
}
