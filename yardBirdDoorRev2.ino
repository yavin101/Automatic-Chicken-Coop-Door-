/* Light sensor Automatic Chicken Coop Door
Jean-baptiste LeConte Sept 20, 2017
*/

#include <Arduino.h>

// Initialize the H-Bridge
// pins 11, 12, 13 for Ch 1
// pins 8, 9, 10 for Ch 2

/* -----( Declare Constants )----- */

// Ch 1 Main Door Linear actuator
const int en1 = 13;
const int in1 = 12;
const int in2 = 11;

// manual override
const int doorSwitchOpen = 7;
const int doorSwitchClose = 6;
const int manualOverride = 5;

// This is the photoresistors.
const int lightSensor1 = A0;
const int lightSensor2 = A1;
const int digitalLightSensor1 = 2;
const int digitalLightSensor2 = 3;

/* -----( Declare Variables )----- */

// The lightValue1 and lightValue2 is the lightsensor(s) variables
int lightValue1;
int lightValue2;
int lightstate1;
int lightstate2;
bool manualOverrideState;
bool doorSwitch_Open_SwitchState;
bool doorSwitch_Close_SwitchState;
const int doorCloseWaitTimeDuration = 3600000; // 60 mins wait
const int doorOpenWaitTimeDuration = 600000;   // 10 mins wait
unsigned long currentMillisCloseWait = 0; // stores the value of millis() in each iteration of loop()
unsigned long previousMillisCloseWait = 0; // will store last time the LED was updated
unsigned long currentMillisOpenWait = 0;   // stores the value of millis() in each iteration of loop()
unsigned long previousMillisOpeneWait = 0; // will store last time the LED was updated
bool closeWaitTimeCheck;
bool openWaitTimeCheck;

void setup()
{
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(manualOverride, INPUT_PULLUP);
  pinMode(doorSwitchOpen, INPUT_PULLUP);
  pinMode(doorSwitchClose, INPUT_PULLUP);
  pinMode(digitalLightSensor1, INPUT);
  pinMode(digitalLightSensor2, INPUT);
  Serial.begin(9600); // open the serial port
  // Check light and door state
  lightstate1 = digitalRead(digitalLightSensor1);
  lightstate2 = digitalRead(digitalLightSensor2);
  if (lightstate1 == HIGH && lightstate2 == HIGH)
  {
    closeDoor();
    Serial.print(" It is NightTIME ");
  }
  else if (lightstate1 == LOW && lightstate2 == LOW)
  {
    openDoor();
    Serial.print(" It is DayTIME ");
  }
}

void loop()
{
  lightstate1 = digitalRead(digitalLightSensor1);
  lightstate2 = digitalRead(digitalLightSensor2);
  lightValue1 = analogRead(lightSensor1);
  lightValue2 = analogRead(lightSensor2);
  manualOverrideState = digitalRead(manualOverride);
  doorSwitch_Open_SwitchState = digitalRead(doorSwitchOpen);
  doorSwitch_Close_SwitchState = digitalRead(doorSwitchClose);
  currentMillisCloseWait = millis(); // capture the latest value of millis()
  currentMillisOpenWait = millis();  // capture the latest value of millis()      // this is equivalent to noting the time from a clock
  updateTimeCloseWaitTime();         // run clock
  updateTimeOpenWaitTime();
  if (closeWaitTimeCheck && manualOverrideState && lightstate1 != HIGH && lightstate
