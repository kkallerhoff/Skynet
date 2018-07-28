#include <Wire.h>
#include <ZumoShield.h>
#define LED_PIN 13

Pushbutton button(ZUMO_BUTTON); // psuhbutton pin 12
ZumoMotors motors;
LSM303 compass; //compass.a.x (accel x) | compass.m.x (magnet x)
L3G gyro; // gyro.g.x = gyro angular vel x
// Sound Effects
ZumoBuzzer buzzer;
const char sound_effect[] PROGMEM = "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2"; // "charge" melody
// use V0 to suppress sound effect; v15 for max volume
bool finished_run = false;
int collision_cnt = 0;
bool charge = false;

void setup() {
  Wire.begin();
  pinMode(LED_PIN, OUTPUT);
  buzzer.playMode(PLAY_AUTOMATIC);
  waitForButtonAndCountDown(false);
  if (!compass.init())
  {
    while (1);
  }
  if (!gyro.init())
  {
    while (1);
  }
  compass.enableDefault();
  gyro.enableDefault();
}

void waitForButtonAndCountDown(bool restarting)
{
  digitalWrite(LED_PIN, HIGH);
  button.waitForButton();
  digitalWrite(LED_PIN, LOW);

  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 50, 12);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(3), 50, 12);
  //buzzer.playFromProgramSpace(sound_effect);
  delay(1000);
}

void loop() {
  static int set_speed;
  static int ax_last;
  static int ay_last;
  static int ax;
  static int ay;

  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    //    button.waitForRelease();
    waitForButtonAndCountDown(true);
    finished_run = false;
    collision_cnt = 0;
  }

  if (finished_run == false) {

    // Read Sensors
    compass.read();
    //
    ax = compass.a.x / 1000;
    ay = compass.a.y / 1000;

    //int dax = (ax - ax_last);
    //int day = (ay - ay_last );

    // impact threshold
    if (abs(ax) >= 10 || abs(ay) >= 10) {
      gyro.read();
      int current_ang = 0;
      current_ang += gyro.g.z / 1000;
      //select sector
      int target_ang = select_sector(ax, ay);
      tracking_turn(current_ang, target_ang);
      collision_cnt ++;
      if (collision_cnt == 5) {
        finished_run = true;
      }
    }

    /*
      if (ax <= -3) {//detect front collision and turn away from obstacle
      set_speed = 0;
      if (ay < 0) {
        turning(2600);
      }
      else {
        turning(-2600);
      }
      charge = false;
      collision_cnt ++;
      if (collision_cnt == 5) {
        finished_run = true;
      }
      }
      else if (ax >= 10) { //detect attack from back, turn around and charge
      if (ay < 0) {
        turning(3900);
      }
      else {
        turning(-3900);
      }
      charge = true;
      }
      else { // drive straight
      if (charge) {
        set_speed = 300;
      }
      else {
        set_speed = 150;
      }
      } */

  }
  else {
    drive(0);
    digitalWrite(LED_PIN, HIGH);
  }
  //ax_last = ax;
  //ay_last = ay;
  drive(set_speed);
  delay(10);
}

//select sector
int  select_sector(int ax, int ay) {
  int target_ang;
  int thresh = 10;
  if (ax <= -thresh && abs(ay) <= 4) { //front center
    //sector = 0;
    target_ang = 0;
  }
  else if (ax <= -thresh && ay >= thresh) { //front right
    //sector = 1;
    target_ang = 1300;
  }
  else if (abs(ax) <= 4 && ay >= thresh) { //center right
    //sector = 2;
    target_ang = 2600;
  }
  else if (ax >= thresh && ay >= thresh) { //rear right
    //sector = 3;
    target_ang = 3900;
  }
  else if (ax >= thresh && abs(ay) <= 4) { //rear center
    //sector = 4;
    target_ang = 5200;
  }
  else if (ax >= thresh && ay <= -thresh) { //rear left
    //sector = 5;
    target_ang = -3900;
  }
  else if (abs(ax) <= 4 && ay <= -thresh) { //center left
    //sector = 6;
    target_ang = -2600;
  }
  else if (ax <= -thresh && ay <= -thresh) { //front left
    //sector = 7;
    target_ang = -1300;
  }
  return target_ang;
}

// drive straight
void drive(int speed_set) {
  static int speed_actual;
  if (speed_actual < speed_set) {
    speed_actual += 10;
  }
  else if (speed_actual > speed_set) {
    speed_actual -= 10;
  }
  motors.setSpeeds(speed_actual, speed_actual);
}

// track turn
void tracking_turn(int current_ang, int target_ang) {
  int turn_speed = 200;
  while ( abs(current_ang - target_ang) > 5) { // turn slowest when close to target angle
    while (abs(current_ang - target_ang) > 200) { // turn slower nearing target angle
      while (abs(current_ang - target_ang) > 1000) { //turn fastest when target angle is >1000 away
        if (current_ang < target_ang) { // turn right
          motors.setSpeeds(turn_speed, -turn_speed);
        }
        else if (current_ang > target_ang) { // turn left
          motors.setSpeeds(-turn_speed, turn_speed);
        }
        gyro.read();
        current_ang = current_ang - gyro.g.z / 1000;
        delay(2);
      }
      if (current_ang < target_ang) { // turn right
        motors.setSpeeds(turn_speed / 2, -turn_speed / 2);
      }
      else if (current_ang > target_ang) { // turn left
        motors.setSpeeds(-turn_speed / 2, turn_speed / 2);
      }
      gyro.read();
      current_ang = current_ang - gyro.g.z / 1000;
      delay(2);
    }
    if (current_ang < target_ang) { // turn right
      motors.setSpeeds(turn_speed / 4, -turn_speed / 4);
    }
    else if (current_ang > target_ang) { // turn left
      motors.setSpeeds(-turn_speed / 4, turn_speed / 4);
    }
    gyro.read();
    current_ang = current_ang - gyro.g.z / 1000;
    delay(2);
  }
  delay(20);
  motors.setSpeeds(0, 0);
  delay(100);
}

// turn 2600~ +90deg
void turning(int target_ang) {
  motors.setSpeeds(-100, -100);
  delay(200);
  motors.setSpeeds(0, 0);
  delay(100);
  int current_ang = 0;
  int turn_speed = 200;
  while ( abs(current_ang - target_ang) > 5) { // turn slowest when close to target angle
    while (abs(current_ang - target_ang) > 200) { // turn slower nearing target angle
      while (abs(current_ang - target_ang) > 1000) { //turn fastest when target angle is >1000 away
        if (current_ang < target_ang) { // turn right
          motors.setSpeeds(turn_speed, -turn_speed);
        }
        else if (current_ang > target_ang) { // turn left
          motors.setSpeeds(-turn_speed, turn_speed);
        }
        gyro.read();
        current_ang = current_ang - gyro.g.z / 1000;
        delay(2);
      }
      if (current_ang < target_ang) { // turn right
        motors.setSpeeds(turn_speed / 2, -turn_speed / 2);
      }
      else if (current_ang > target_ang) { // turn left
        motors.setSpeeds(-turn_speed / 2, turn_speed / 2);
      }
      gyro.read();
      current_ang = current_ang - gyro.g.z / 1000;
      delay(2);
    }
    if (current_ang < target_ang) { // turn right
      motors.setSpeeds(turn_speed / 4, -turn_speed / 4);
    }
    else if (current_ang > target_ang) { // turn left
      motors.setSpeeds(-turn_speed / 4, turn_speed / 4);
    }
    gyro.read();
    current_ang = current_ang - gyro.g.z / 1000;
    delay(2);
  }
  delay(20);
  motors.setSpeeds(0, 0);
}

