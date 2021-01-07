// 
// 
// 

#include "Encoder .h"

void Encoder::init()
{
	pinMode(pin1, INPUT);
	pinMode(pin2, INPUT);

	attachInterrupt(pin1, pinChangeISR, CHANGE);
}

void Encoder::pinChangeISR()
{
	current_obj->processPinChangeISR();
}

void Encoder::processPinChangeISR()
{
	//Implement logic based on info from oscilloscope.
}


