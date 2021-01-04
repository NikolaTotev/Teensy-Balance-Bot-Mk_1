/*
 Name:		Teensy_Balancing_Bot_Mk_1.ino
 Created:	12/28/2020 2:56:05 PM
 Author:	Nikola
*/

// the setup function runs once when you press reset or power the board
#include "AngleMeasurement.h"
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SSD1306.h>
#include "IMU.h"
#include <Wire.h>
#include "i2c_utils.h"
#include <CytronMotorDriver.h>

#define P_Gain = 0;
#define D_Gain = 0;
#define I_Gain = 0;

void PIDInit();
void PIDUpdate(float currentAngle);

float pidSetpoint;
float pidError;
float pidPrevError;
float pidPrevDPS;

float pidProp;

float pidDeriv;
float pidInteg;

float pidIntegState;
float pidOutput;
float requiredMotorSpeed;

byte measuredAngleIsNegative;

CytronMD motor1(PWM_DIR, 2, 3);
CytronMD motor2(PWM_DIR, 4, 5);


void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
