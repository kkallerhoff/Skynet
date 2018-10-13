/*
 * Folgender Code liest die Sensordaten des 'IR refelctance sensor array' aus
 * und gibt sie über die serielle Schnittstelle aus.
 * Je höher der Wert, desto niedriger ist die Reflektion des Lichtes.
 * 0 = maximale Reflektion
 * 2000 = minimale Reflektion (entspricht schwarzem Untergrund)
 */

#include <Wire.h>
#include <ZumoShield.h>

ZumoReflectanceSensorArray sensors (QTR_NO_EMITTER_PIN);

#define NUM_SENSORS 6

unsigned int sensor_values[NUM_SENSORS];

void write_sensor_values_to_serial(){
  int i;
  for(i=0; i<=5; i++){
    Serial.print(sensor_values[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // die Sensordaten werden ausgelesen und in dem Array 'sensor_values' gespeichert
  sensors.read(sensor_values);

  // die Sensordaten werden über den serial Monitor ausgegeben
  write_sensor_values_to_serial();
  
  delay(10);
}
