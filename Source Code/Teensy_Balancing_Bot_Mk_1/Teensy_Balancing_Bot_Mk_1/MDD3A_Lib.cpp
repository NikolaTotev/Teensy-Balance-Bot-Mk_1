// 
// 
// 

#include "MDD3A_Lib.h"


void MDD3A::setSpeed(int16_t speed, Direction direction)
{
	int16_t finalSpeed = 0;

	if (speed > 175) { speed = 175; }
	if (speed < 0) { speed = 0; }

	if (speed == 0)
	{
		finalSpeed = 0;
	}
	else
	{
		switch (direction) {
		case FWD:
			finalSpeed = map(speed, 0, 175, 79, 255);
			break;
		case REV:
			finalSpeed = map(speed, 0, 175, -176, 0);
			break;
		default:;

		}
	}

	switch (direction) {
	case FWD:
		//Serial.println(finalSpeed);
		analogWrite(pinA, finalSpeed);
		digitalWriteFast(pinB, LOW);
		break;
	case REV:
		//Serial.println(finalSpeed);
		analogWrite(pinA, -finalSpeed);
		digitalWriteFast(pinB, HIGH);
		break;
	default:;
	}
}

