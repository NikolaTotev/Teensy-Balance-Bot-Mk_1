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


//Display constants 

// OLED display width, in pixels
#define SCREEN_WIDTH 128
// OLED display height, in pixels
#define SCREEN_HEIGHT 32 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_RESET 4 



#define Angle_P_Gain = 0;
#define Angle_D_Gain = 0;
#define Angle_I_Gain = 0;

#define Pos_P_Gain = 0;
#define Pos_D_Gain = 0;
#define Pos_I_Gain = 0;

void PIDInit();
void AnglePIDUpdate(float currentAngle);
void PositionPIDUpdate(float currentPosition);

//Angle PID variables
float a_pidSetpoint;
float a_pidError;
float a_pidPrevError;
float a_pidPrevDPS;

float a_pidProp;

float a_pidDeriv;
float a_pidInteg;

float a_pidIntegState;
float a_pidOutput;


//Position PID variables
float p_pidSetpoint;
float p_pidError;
float p_pidPrevError;
float p_pidPrevDPS;

float p_pidProp;

float p_pidDeriv;
float p_pidInteg;

float pidIntegState;
float pidOutput;

float requiredMotorSpeed;


uint16_t currentPosition = 0;
float currentAngle = 0;

byte measuredAngleIsNegative;

CytronMD motor1(PWM_DIR, 2, 3);
CytronMD motor2(PWM_DIR, 4, 5);

Adafruit_SSD1306 currentDisplay = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
IMU currentIMU = IMU(&currentDisplay, true);

void setup() {
	
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
