// 
// 
// 

#include "Position.h"

int Position::GetEstimatedPosition()
{
	
}

void Position::Update()
{
	calcRevolutions();
	calcTravelDistance();
}

void Position::calcRevolutions()
{
	int16_t leftEncoderTicks = leftEncoder->getTicks();
	int16_t rightEncoderTicks = rightEncoder->getTicks();

	prevLeftWheelPosition = leftWheelPosition;
	prevRightWheelPosition = rightWheelPosition;

	leftWheelPosition = 1 * leftEncoderTicks;
	rightWheelPosition = 1 * leftEncoderTicks;

	if(leftWheelPosition > prevLeftDistanceTraveled)
	{
		leftMovingForward = true;
	}
	else
	{
		leftMovingForward = false;
	}


	if (rightWheelPosition > prevRightDistanceTraveled)
	{
		rightMovingForward = true;
	}
	else
	{
		rightMovingForward = false;
	}
}

void Position::calcTravelDistance()
{
	prevLeftDistanceTraveled = leftDistanceTraveled;
	prevRightDistanceTraveled = rightDistanceTraveled;

	leftDistanceTraveled = 2 * PI * wheelRadius;
	rightDistanceTraveled = 2 * PI * wheelRadius;
}

int16_t Position::LW_GetEstimatedPosition()
{
	return leftWheelPosition;
}

int16_t Position::RW_GetEstimatedPosition()
{
	return rightWheelPosition;
}







