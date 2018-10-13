/*
 * Folgender Code testet die korrekte Funktion des L3GD20H 3-axis gyroscope.
 * Das Ergebnis eines Testdurchlaufes ist die Winkelbeschleunigung in x, y und z-Richtung
 * in dps (degrees per second).
 * 
 * Trotz Stillstands des Roboters werden von den Sensoren Werte erfasst welche ungleich 0 sind.
 * Um eine möglichst genaue Richtungsangabe in Grad machen zu können, sollte der Roboter
 * kalibriert werden. Während des Kalibrierungsvorgangs darf der Roboter nicht bewegt werden.
 * 
 */

#include <Wire.h>
#include <ZumoShield.h>

Pushbutton button(ZUMO_BUTTON);
L3G gyro;


#define LED_PIN                 13
#define L3G_CONVERSION_FACTOR   8.75
#define CALIBRATE               false
#define CALIBRATION_SAMPLES      100

short int i; // index für 'for-Schleifen'

double calibration_values[3]; // kalibrierte Werte für x, y und z [x,y,z]

double gyroGetDps(double gyroRawValue, double conversionFactor = L3G_CONVERSION_FACTOR){
  return (gyroRawValue * conversionFactor) / 1000;
}

void calibrate(int num_samples = CALIBRATION_SAMPLES){
  long start;
  long dauer;

  double sum_x, sum_y, sum_z;
  
  start = millis();
  for(i=0; i<num_samples; i++){
    
    gyro.read();
    double gyro_g_z = gyroGetDps((double)gyro.g.z);
    //Serial.println(gyro_g_z);
    
    sum_x = sum_x + gyroGetDps((double)gyro.g.x);
     
    sum_y = sum_y + gyroGetDps((double)gyro.g.y);
    
    sum_z = sum_z + gyroGetDps((double)gyro.g.z);
    
    delay(10);
  }
  dauer = millis() - start;

  calibration_values[0] = sum_x / num_samples;
  calibration_values[1] = sum_y / num_samples;
  calibration_values[2] = sum_z / num_samples;

  Serial.print("X: ");
  Serial.print(calibration_values[0]);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Y: ");
  Serial.print(calibration_values[1]);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Z: ");
  Serial.print(calibration_values[2]);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Dauer: ");
  Serial.print((double)dauer/1000);
  Serial.println(" s");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();

  button.waitForButton();
  Serial.println("Kalibrierung...");
  for(i=0; i<3; i++){
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
  }
  if(CALIBRATE)
    calibrate();
}

void loop() {
  double gyro_g_x, gyro_g_y, gyro_g_z;

  gyro.read();
  
  gyro_g_x = gyroGetDps((double)gyro.g.x);
  gyro_g_y = gyroGetDps((double)gyro.g.y);
  gyro_g_z = gyroGetDps((double)gyro.g.z);

  //Unkalibrierte Werte
  Serial.print("Nicht kalibriert: ");
  Serial.print("\t");
  Serial.print("X: ");
  Serial.print(gyro_g_x);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Y: ");
  Serial.print(gyro_g_y);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Z: ");
  Serial.print(gyro_g_z);
  Serial.println(" dps");

  //Kalibrierte Werte
  if (gyro_g_x - calibration_values[0] != gyro_g_x){
  Serial.print("Kalibriert: ");
  Serial.print("\t\t");
  Serial.print("X: ");
  Serial.print(gyro_g_x - calibration_values[0]);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Y: ");
  Serial.print(gyro_g_y - calibration_values[1]);
  Serial.print(" dps");
  Serial.print("\t");

  Serial.print("Z: ");
  Serial.print(gyro_g_z - calibration_values[2]);
  Serial.println(" dps");
  }
  Serial.println();

  delay(100);

}
