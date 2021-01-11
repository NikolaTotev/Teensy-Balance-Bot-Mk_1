// Encoder_Lib.h

#ifndef _ENCODER_LIB_h
#define _ENCODER_LIB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
class Encoder
{
private:
	uint16_t pin1;
	uint16_t pin2;

	uint16_t pin3;
	uint16_t pin4;

	bool pin1High = false;
	bool pin2High = false;

	bool pin3High = false;
	bool pin4High = false;

	int16_t numberOfTicksLeft = 0;
	int16_t numberOfTicksRight = 0;

	int16_t prevNumberOfTicksLeft = 0;
	int16_t prevNumberOfTicksRight = 0;

	bool isGoingForwardLeft = false;;
	bool isGoingForwardRight = false;;
	static Encoder* current_obj;

	//ToDo: Set this flag to false;
	byte useSerialDebug = true;

public:
	Encoder(uint16_t encPin1, uint16_t encPin2, uint16_t encPin3, uint16_t encPin4)
	{
		pin1 = encPin1;
		pin2 = encPin2;
		pin3 = encPin3;
		pin4 = encPin4;
		current_obj = this;
	}

	void init();
	void processLeftPinChangeISR();
	void processRightPinChangeISR();
	static void leftPinChangeISR();
	static void rightPinChangeISR();
	int16_t getLeftTicks();
	int16_t getRightTicks();
};
#else
	#include "WProgram.h"
#endif


#endif

