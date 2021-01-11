// 
// 
// 

#include "Position.h"

float Position::GetLeftEstimagedDistance()
{
	return leftDistanceTraveled;
}

float Position::GetRighttEstimagedDistance()
{
	return rightDistanceTraveled;
}


void Position::Update()
{
	calcRevolutions();
	calcTravelDistance();
}

void Position::calcRevolutions()
{
	int16_t leftEncoderTicks = encoders->getLeftTicks();
	int16_t rightEncoderTicks = encoders->getRightTicks();

	if(leftEncoderTicks >= 5||rightEncoderTicks >= 5)
	{
		encoders->reset();
	}

	prevLeftWheelPosition = leftWheelPosition;
	prevRightWheelPosition = rightWheelPosition;

	leftWheelPosition = 1 * leftEncoderTicks;
	rightWheelPosition = 1 * rightEncoderTicks;

	if(leftWheelPosition > prevLeftWheelPosition)
	{
		leftMovingForward = true;
	}
	else
	{
		leftMovingForward = false;
	}

	//Set direction of right wheel.
	if (rightWheelPosition > prevRightWheelPosition)
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







