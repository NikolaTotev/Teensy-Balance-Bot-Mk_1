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
void AnglePIDUpdate();
void PositionPIDUpdate();

//Angle PID variables
float a_pidSetpoint = 0;
float a_pidError = 0;
float a_pidPrevError = 0;
float a_pidPrevDPS = 0;

float a_pidProp = 0;

float a_pidDeriv = 0;
float a_pidInteg = 0;

float a_pidIntegState = 0;
float a_pidOutput = 0;

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


int16_t currentPosition = 0;
float currentAngle = 0;

int16_t prevTime = 0;
byte measuredAngleIsNegative;

CytronMD motor1(PWM_DIR, 2, 3);
CytronMD motor2(PWM_DIR, 4, 5);

Adafruit_SSD1306 currentDisplay = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
IMU currentIMU = IMU(&currentDisplay, true);
AngleM currentAngleMeasurment = AngleM(1, &currentDisplay);
Encoder leftEncoder = Encoder(9, 10);
Encoder rightEncoder = Encoder(11, 12);

void UpdateMotorSpeed(int16_t motor1Speed, int16_t motor2Speed);
void setup() {
	currentIMU.Init();
	leftEncoder.init();
	rightEncoder.init();
}

// the loop function runs over and over again until power down or reset
void loop() {
	prevTime = micros();

	a_pidSetpoint = 0;
	currentAngle = currentAngleMeasurment.GetCurrentAngles()[1];
	AnglePIDUpdate();
	UpdateMotorSpeed(a_pidOutput, a_pidOutput);
	
}

void AnglePIDUpdate()
{
	//Calculate the current error.
	a_pidError = abs(a_pidSetpoint - abs(currentAngle));

	//Calculate proportional response.
	a_pidProp = Angle_P_Gain * p_pidError;

	//Calculate integral response.
	a_pidIntegState =a_pidIntegState + 0.5 * Angle_I_Gain * pidSampleTime * (a_pidError + a_pidPrevError);


	if (p_pidIntegState > p_integMax)
	{
		p_pidIntegState = p_integMax;
	}
	else if (a_pidIntegState < p_integMin)
	{
		a_pidIntegState = p_integMin;
	}

	//Calculate derivative response. (0.5 comes from the formula for the derivative. 
	a_pidDeriv = Angle_D_Gain * ((a_pidError - a_pidPrevError) / 0.5);

	//Calculate final pid output.
	a_pidOutput = a_pidProp + a_pidIntegState + a_pidDeriv;

	//Remember previous values.
	a_pidPrevError = a_pidError;
	a_pidPrevDPS = currentAngle;
}

void PositionPIDUpdate()
{
	//Calculate the current error.
	p_pidError = abs(p_pidSetpoint - abs(currentPosition));

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

void UpdateMotorSpeed(int16_t motor1Speed, int16_t motor2Speed)
{
	motor1.setSpeed(motor1Speed);
	motor2.setSpeed(motor2Speed);
}

