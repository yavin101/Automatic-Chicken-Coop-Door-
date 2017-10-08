/*Light sensor Automatic Chicken Coop Door
Jean-baptiste LeConte Sept 20, 2017
*/
#include <Metro.h>
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
	if ((manualOverrideState == true) && (lightstate1 == HIGH) && (lightstate2 == HIGH))
	{
		Metro doorDelayClose = Metro(3600000); // 60 mins wait
		Serial.print("The door will close in 60 mins: ");
		if ((doorDelayClose.check()) && (manualOverrideState == true) && (lightstate1 == HIGH) && (lightstate2 == HIGH))
		{
			Serial.print("The door is closing ");
			closeDoor();
		}
	}
	if ((manualOverrideState == true) && (lightstate1 == LOW) && (lightstate2 == LOW))
	{
		Metro doorDelayOpen = Metro(600000); // 10 mins wait
		Serial.print(" The door is will be Opening in 10 mins: ");
		if ((doorDelayOpen.check()) && (manualOverrideState == true) && (lightstate1 == LOW) && (lightstate2 == LOW))
		{
			Serial.print(" The door is Opening ");
			openDoor();
		}
	}
	if ((doorSwitch_Open_SwitchState == LOW) && (manualOverrideState == false))
	{
		Metro manualOverrideDoorDelayOpen = Metro(1000);
		if ((doorSwitch_Open_SwitchState == LOW) && (manualOverrideState == false))
		{
			manualoverrideopenDoor();
			Serial.print("Manual override Engaged; The door is Opening ");
		}
	}
	if ((doorSwitch_Close_SwitchState == LOW) && (manualOverrideState == false))
	{
		Metro manualOverrideDoorDelayClose = Metro(1000);
		if ((doorSwitch_Close_SwitchState == LOW) && (manualOverrideState == false))
		{
			manualOverridecloseDoor();
			Serial.print("Manual override Engaged; The door is closing ");
		}
	}
	// DEBUG CODE
	/*
	Serial.print("light Sensor 1 is  :");
	Serial.println(lightValue1);
	delay(2000);
	Serial.print("light Sensor 2 is  :");
	Serial.println(lightValue2);
	delay(2000);
	Serial.print("light State 1 is  :");
	Serial.println(lightstate1);
	delay(2000);
	Serial.print("light State 2 is  :");
	Serial.println(lightstate2);
	delay(2000);
	Serial.print("manualOverrideState is   :");
	Serial.println(manualOverrideState);
	delay(2000);
	Serial.print("doorSwitch_Open_SwitchState is   :");
	Serial.println(doorSwitch_Open_SwitchState);
	delay(2000);
	Serial.print("doorSwitch_Close_SwitchState is   :");
	Serial.println(doorSwitch_Close_SwitchState);
	delay(2000);
	*/
}

void closeDoor()
{
	// wait 2 seconds
	delay(1000);
	// turn on motor and set speed to 255
	analogWrite(en1, 255);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

void openDoor()
{
	// wait 2 seconds
	delay(1000);
	// turn on motor and set speed to 255
	analogWrite(en1, 255);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
}

void manualOverridecloseDoor()
{
	// wait 2 seconds
	delay(1000);
	// turn on motor and set speed to 255
	analogWrite(en1, 255);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
}

void manualoverrideopenDoor()
{
	// wait 2 seconds
	delay(1000);
	// turn on motor and set speed to 255
	analogWrite(en1, 255);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}
