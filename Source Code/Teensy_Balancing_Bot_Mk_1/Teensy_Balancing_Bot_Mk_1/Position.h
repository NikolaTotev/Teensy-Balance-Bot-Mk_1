// Position.h

#ifndef _POSITION_h
#define _POSITION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
class Position
{

	const int ticksPerRevolution = 3;
	const int wheelRadius = 50; //Unit is mm


	int16_t prevLeftWheelPosition = 0;
	int16_t prevRightWheelPosition = 0;

	int16_t leftWheelPosition = 0;
	int16_t rightWheelPosition = 0;

	float prevLeftDistanceTraveled = 0;
	float prevRightDistanceTraveled = 0;

	float leftDistanceTraveled = 0;
	float rightDistanceTraveled = 0;

	//ToDo implement this.
	bool rightMovingForward = false;
	bool leftMovingForward = false;

	Encoder* leftEncoder;
	Encoder* rightEncoder;


	Position(Encoder* lEncoder, Encoder* rEncoder)
	{
		leftEncoder = lEncoder;
		rightEncoder = rEncoder;
	}


	void calcRevolutions();
	void calcTravelDistance();
public:
	//This void is called by the main program loop.
	void Update();
	float GetEstimatedPosition();
	int16_t RW_GetEstimatedPosition();
	int16_t LW_GetEstimatedPosition();

};
#else
#include "WProgram.h"
#endif


#endif

