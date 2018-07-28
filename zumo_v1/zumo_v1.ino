/*
   This example uses the ZumoMotors library to drive each motor on the Zumo
   forward, then backward. The yellow user LED is on when a motor should be
   running forward and off when a motor should be running backward. If a
   motor on your Zumo has been flipped, you can correct its direction by
   uncommenting the call to flipLeftMotor() or flipRightMotor() in the setup()
   function.
*/

#include <Wire.h>
#include <ZumoShield.h>

#define LED_PIN 13
Pushbutton button(ZUMO_BUTTON); // psuhbutton pin 12

ZumoMotors motors;

// Sound Effects
ZumoBuzzer buzzer;
const char sound_effect[] PROGMEM = "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2"; // "charge" melody
// use V0 to suppress sound effect; v15 for max volume
bool finished_run = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  buzzer.playMode(PLAY_AUTOMATIC);
  waitForButtonAndCountDown(false);
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
  buzzer.playFromProgramSpace(sound_effect);
  delay(1000);
}

void loop()
{
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
//    button.waitForRelease();
    waitForButtonAndCountDown(true);
    finished_run = false;
  }

  if (finished_run == false)
  {
    int  l_gain = 1;
    int  r_gain = 1;
    int v_max = 100;

    delay(1500);
    // run both motors forward

    digitalWrite(LED_PIN, LOW);

    for (int speed = 0; speed <= 400; speed += 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(speed * 0.95);
      delay(2);
    }

    delay(400);
    for (int speed = v_max; speed >= 0; speed -= 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(speed * l_gain);
      delay(2);
    }
    // end forward after 1s

    delay(200);

    // 540° turn

    for (int speed = 0; speed <= v_max; speed += 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(-speed * l_gain);
      delay(2);
    }
    delay(2700);

    for (int speed = v_max; speed >= 0; speed -= 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(-speed * l_gain);
      delay(2);
    }
    // end turn

    delay(200);


    // run both motors forward

    

    for (int speed = 0; speed <= v_max; speed += 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(speed * l_gain);
      delay(2);
    }

    delay(1700);
    for (int speed = v_max; speed >= 0; speed -= 5)
    {
      motors.setRightSpeed(speed * r_gain);
      motors.setLeftSpeed(speed * l_gain);
      delay(2);
    }

    delay(200);

    // 540° turn

    for (int speed = 0; speed <= v_max; speed += 5)
    {
      motors.setRightSpeed(-speed * r_gain);
      motors.setLeftSpeed(speed * l_gain);
      delay(2);
    }
    delay(900);

    for (int speed = v_max; speed >= 0; speed -= 5)
    {
      motors.setRightSpeed(-speed * r_gain);
      motors.setLeftSpeed(speed * l_gain);
      delay(2);
    }
    finished_run = true;
    digitalWrite(LED_PIN, HIGH);
  }
}
