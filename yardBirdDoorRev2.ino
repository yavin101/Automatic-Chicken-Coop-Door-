/*Light sensor Automatic Chicken Coop Door
Jean-baptiste LeConte Sept 20, 2017
*/
#include <Arduino.h>
// Initialize the H-Brigde
// pins 11, 12, 13 for Ch 1
// pins 8, 9, 10 for Ch 2
/*-----( Declare Constants )-----*/
// Ch 1 Main Door Linear actuator
#define en1 13
#define in1 12
#define in2 11
// manual override
#define doorSwitchOpen 7
#define doorSwitchClose 6
#define manualOverride 5
// This is the photoresistors.
#define lightSensor1 A0
#define lightSensor2 A1
#define digitalLightSensor1 2
#define digitalLightSensor2 3
/*-----( Declare Variables )-----*/
// The lightValue1 and lightValue2 is the lightsensor(s) variables
int lightValue1;
int lightValue2;
int lightstate1;
int lightstate2;
bool manualOverrideState;
bool doorSwitch_Open_SwitchState;
bool doorSwitch_Close_SwitchState;
const int doorCloseWaitTimeDuration = 3600000; // 60 mins wait
const int doorOpenWaitTimeDuration = 600000; // 10 mins wait
unsigned long currentMillisCloseWait = 0; // stores the value of millis() in each iteration of loop()
unsigned long previousMillisCloseWait = 0; // will store last time the LED was updated
unsigned long currentMillisOpenWait = 0; // stores the value of millis() in each iteration of loop()
unsigned long previousMillisOpenWait = 0; // will store last time the LED was updated
bool closeWaitTimeCheck;
bool openWaitTimeCheck;

void updateTimeCloseWaitTime() {
  // check if 60 minutes have passed
  if (currentMillisCloseWait - previousMillisCloseWait >= doorCloseWaitTimeDuration) {
    previousMillisCloseWait = currentMillisCloseWait;
    closeWaitTimeCheck = true;
  } else {
    closeWaitTimeCheck = false;
  }
}

void updateTimeOpenWaitTime() {
  // check if 10 minutes have passed
  if (currentMillisOpenWait - previousMillisOpenWait >= doorOpenWaitTimeDuration) {
    previousMillisOpenWait = currentMillisOpenWait;
    openWaitTimeCheck = true;
  } else {
    openWaitTimeCheck =
