/*
 Name:		Teensy_Balancing_Bot_Mk_1.ino
 Created:	12/28/2020 2:56:05 PM
 Author:	Nikola
*/

// the setup function runs once when you press reset or power the board
#include "Encoder .h"
#include "Position.h"
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


float Angle_P_Gain = 0.0f;
float Angle_D_Gain = 0.0f;
float Angle_I_Gain = 0.0f;

float Pos_P_Gain = 0;
float Pos_D_Gain = 0;
float Pos_I_Gain = 0;

//Integrator anti-windup limits
#define p_integMax 10
#define p_integMin -10


//PID time constants
#define pidSampleTime 0.0032f //0.5 //In seconds
#define pidSampleTimeMircos 3200 //500000

void PIDInit();
void AnglePIDUpdate(float currentAngle);
void PositionPIDUpdate(float currentPosition);

//Angle PID variables
float p_pidSetpoint = 0;
float p_pidError = 0;
float p_pidPrevError = 0;
float p_pidPrevDPS = 0;

float p_pidProp = 0;

float p_pidDeriv = 0;
float p_pidInteg = 0;

float p_pidIntegState = 0;
float p_pidOutput = 0;

//Position PID variables
float p_pidSetpoint = 0;
float p_pidError = 0;
float p_pidPrevError = 0;
float p_pidPrevDPS = 0;

float p_pidProp = 0;

float p_pidDeriv = 0;
float p_pidInteg = 0;

float p_pidIntegState = 0;
float p_pidOutput = 0;



float requiredMotorSpeed = 0;


uint16_t currentPosition = 0;
float currentAngle = 0;

byte measuredAngleIsNegative;

CytronMD motor1(PWM_DIR, 2, 3);
CytronMD motor2(PWM_DIR, 4, 5);

Adafruit_SSD1306 currentDisplay = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
IMU currentIMU = IMU(&currentDisplay, true);

void setup() {
	currentIMU.Init();
}

// the loop function runs over and over again until power down or reset
void loop() {

}

void AnglePIDUpdate(float currentAngle)
{
	//Calculate the current error.
	p_pidError = abs(p_pidSetpoint - abs(currentAngle));

	//Calculate proportional response.
	p_pidProp = Angle_P_Gain * p_pidError;

	//Calculate integral response.
	p_pidIntegState = p_pidIntegState + 0.5 * Angle_I_Gain * pidSampleTime * (p_pidError + p_pidPrevError);


	if (p_pidIntegState > p_integMax)
	{
		p_pidIntegState = p_integMax;
	}
	else if (p_pidIntegState < p_integMin)
	{
		p_pidIntegState = p_integMin;
	}

	//Calculate derivative response. (0.5 comes from the formula for the derivative. 
	p_pidDeriv = Angle_D_Gain * ((p_pidError - p_pidPrevError) / 0.5);

	//Calculate final pid output.
	p_pidOutput = p_pidProp + p_pidIntegState + p_pidDeriv;

	//Remember previous values.
	p_pidPrevError = p_pidError;
	p_pidPrevDPS = currentAngle;
}

void PositionPIDUpdate(float currentPosition)
{
	//Calculate the current error.
	p_pidError = abs(p_pidSetpoint - abs(currentAngle));

	//Calculate proportional response.
	p_pidProp = Angle_P_Gain * p_pidError;

	//Calculate integral response.
	p_pidIntegState = p_pidIntegState + 0.5 * Angle_I_Gain * pidSampleTime * (p_pidError + p_pidPrevError);


	if (p_pidIntegState > p_integMax)
	{
		p_pidIntegState = p_integMax;
	}
	else if (p_pidIntegState < p_integMin)
	{
		p_pidIntegState = p_integMin;
	}

	//Calculate derivative response. (0.5 comes from the formula for the derivative. 
	p_pidDeriv = Angle_D_Gain * ((p_pidError - p_pidPrevError) / 0.5);

	//Calculate final pid output.
	p_pidOutput = p_pidProp + p_pidIntegState + p_pidDeriv;

	//Remember previous values.
	p_pidPrevError = p_pidError;
	p_pidPrevDPS = currentAngle;
}

