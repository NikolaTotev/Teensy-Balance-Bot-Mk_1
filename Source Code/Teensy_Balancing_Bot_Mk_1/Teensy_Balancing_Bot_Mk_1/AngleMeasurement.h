// AngleMeasure.h

#ifndef _ANGLEMEASURE_h
#define _ANGLEMEASURE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"

#include "IMU.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include  "Receiver.h"

#define GyroPart 0.98
#define AccelPart 0.02

#define ComplementaryGryoPart 0.99
#define ComplementaryAccelPart 0.02




class AngleM
{

private:
	int prevTime;

	float* currentAccelVals;
	float* currentGyroVals;
	float* currentVals;

	float gyroAngleEstimateX;
	float gyroAngleEstimateY;
	float gyroAngleEstimateZ;

	float accelAngleEstimateX;
	float accelAngleEstimateY;
	float accelAngleEstimateZ;

	float finalAngleEstimateX;
	float finalAngleEstimateY;
	float totalGravityVector;
	float currentAngles[3];
	byte useDisplay;

	Adafruit_SSD1306* currentDisplay;
	IMU currentIMU = IMU(currentDisplay, useDisplay);	

public:
	AngleM(byte useDisp,Adafruit_SSD1306* disp)
	{
		useDisplay = useDisp;
		currentDisplay = disp;
		currentIMU.SetDisp(disp);
	}

	void AngleCtor();
	void SetInitialAngle();
	float* GetCurrentAngles();
	float GetCurrentXRate();
	float GetCurrentYRate();
	void DrawValue(uint16_t m1ThrottleVal, uint16_t m2ThrottleVal);
};


#else
#include "WProgram.h"
#endif


#endif

