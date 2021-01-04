/*
 Name:		Motor_Control_Test.ino
 Created:	12/28/2020 6:52:21 PM
 Author:	Nikola
*/

// the setup function runs once when you press reset or power the board
#include <WireKinetis.h>
#include <WireIMXRT.h>
#include <Wire.h>
#include "i2c_utils.h"
#include <CytronMotorDriver.h>
CytronMD motor1(PWM_DIR, 2, 3);
CytronMD motor2(PWM_DIR, 4, 5);
void setup() {
	pinMode(2, OUTPUT);
	digitalWrite(2, LOW);
}

// the loop function runs over and over again until power down or reset
void loop() {	
	motor1.setSpeed(0);   // Motor 1 runs forward at 50% speed.
	motor2.setSpeed(0);  // Motor 2 runs backward at 50% speed.
	delay(1000);
}
