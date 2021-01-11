// MDD3A_Lib.h

#ifndef _MDD3A_LIB_h
#define _MDD3A_LIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"

enum Direction
{
	FWD,
	REV
};

class MDD3A
{
private:
	uint8_t pinA;
	uint8_t pinB;

public:
	MDD3A(uint8_t pA, uint8_t pB)
	{
		pinA = pA;
		pinB = pB;

		pinMode(pinA, OUTPUT);
		pinMode(pinB, OUTPUT);
	}
	void setSpeed(int16_t speed, Direction direction);
};

#else
#include "WProgram.h"
#endif


#endif

