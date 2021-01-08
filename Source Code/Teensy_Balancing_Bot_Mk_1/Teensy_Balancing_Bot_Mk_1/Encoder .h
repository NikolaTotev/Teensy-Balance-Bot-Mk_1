// Encoder .h

#ifndef _ENCODER _h
#define _ENCODER _h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
class Encoder
{
private:
	uint16_t pin1;
	uint16_t pin2;
	
	bool pin1High;
	bool pin2High;

	int16_t numberOfTicks = 0;
	int16_t prevNumberOfTicks = 0;

	bool isGoingForward;
	static Encoder* current_obj;

	//ToDo: Set this flag to false;
	byte useSerialDebug = true;

	
public:

	Encoder(uint16_t encPin1, uint16_t encPin2)
	{
		pin1 = encPin1;
		pin2 = encPin2;
		current_obj = this;
	}

	void init();
	void processPinChangeISR();
	static void pinChangeISR();
	int16_t getTicks();
};
#else
	#include "WProgram.h"
#endif


#endif

