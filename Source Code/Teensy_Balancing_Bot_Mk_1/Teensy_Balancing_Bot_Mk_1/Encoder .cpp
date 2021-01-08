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

int16_t Encoder::getTicks()
{
	return numberOfTicks;
}


void Encoder::processPinChangeISR()
{
	if (digitalReadFast(pin1) == HIGH)
	{
		pin1High = true;
	}
	else
	{
		pin1High = false;
	}

	if (digitalReadFast(pin2) == HIGH)
	{
		pin2High = true;
	}
	else
	{
		pin2High = false;
	}

	if (pin1High == pin2High)
	{
		numberOfTicks++;
	}
	else
	{
		numberOfTicks--;
	}

	if (numberOfTicks < prevNumberOfTicks)
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicks);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicks);
			Serial.print(" Pin 9:");
			Serial.print(pin1High);
			Serial.print(" Pin 10:");
			Serial.print(pin2High);
			Serial.print(" Encoder 1 Direction: FWD \n");
		}
		isGoingForward = true;

	}
	else
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicks);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicks);
			Serial.print(" Pin 9:");
			Serial.print(pin1High);
			Serial.print(" Pin 10:");
			Serial.print(pin2High);
			Serial.println("Encoder 1 Direction: REV\n");
		}
		isGoingForward = false;
	}

	prevNumberOfTicks = numberOfTicks;
}


