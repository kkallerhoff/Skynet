/*
 * Der Roboter fährt auf einem schwarzen Untergrund (mit verschiedenen Geschwindigkeiten
 * unt unter verschiedenen Winkeln) auf eine weiße Linie zu. Beim Erkennen der weißen
 * Linie stoppt der Roboter und gibt ein akustisches Signal.
 */

#include <Wire.h>
#include <ZumoShield.h>

ZumoReflectanceSensorArray sensors (QTR_NO_EMITTER_PIN);
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
ZumoBuzzer buzzer;

#define NUM_SENSORS 6
#define REFLECTANCE_THRESHOLD 1500

unsigned int sensor_values[NUM_SENSORS];

void stopAndBuzz(){
  motors.setSpeeds(0,0);
  buzzer.playNote(NOTE_G(4), 500, 12);
}

void turnaround(){
  motors.setSpeeds(-150, -150);
  delay(250);
  motors.setSpeeds(-200, 200);
  delay(805);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  button.waitForButton();
  delay(1000);
  
  //motors.setSpeeds(300,300);
  
  sensors.read(sensor_values);
  
  if(sensor_values[0] < REFLECTANCE_THRESHOLD){  
    stopAndBuzz();
    //turnaround();
    
  }
  else if(sensor_values[5] < REFLECTANCE_THRESHOLD){
    stopAndBuzz();
    //turnaround();
  }
}
