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

	uint16_t wheelRevolutions;
	bool isGoingForward;
	static Encoder* current_obj;

	
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
};
#else
	#include "WProgram.h"
#endif


#endif
