// 
// 
// 

#include "Encoder_Lib.h"
Encoder* Encoder::current_obj;
void Encoder::init()
{
	pinMode(pin1, INPUT);
	pinMode(pin2, INPUT);
	pinMode(pin3, INPUT);
	pinMode(pin4, INPUT);

	attachInterrupt(pin1, leftPinChangeISR, RISING);
	attachInterrupt(pin3, rightPinChangeISR, RISING);
}

void Encoder::leftPinChangeISR()
{
	current_obj->processLeftPinChangeISR();
}

void Encoder::rightPinChangeISR()
{
	current_obj->processRightPinChangeISR();
}

int16_t Encoder::getLeftTicks()
{
	return numberOfTicksLeft;
}

int16_t Encoder::getRightTicks()
{
	return numberOfTicksRight;
}


void Encoder::processLeftPinChangeISR()
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
		numberOfTicksLeft++;
	}
	else
	{
		numberOfTicksLeft--;
	}

	if (numberOfTicksLeft < prevNumberOfTicksLeft)
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicksLeft);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicksLeft);
			Serial.print(" Pin ");
			Serial.print(pin1);
			Serial.print(": ");
			Serial.print(pin1High);
			Serial.print(" Encoder 1 Direction: FWD \n");
		}
		isGoingForwardLeft = true;

	}
	else
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicksLeft);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicksLeft);
			Serial.print(" Pin ");
			Serial.print(pin1);
			Serial.print(": ");
			Serial.print(pin1High);
			Serial.print(" Encoder 1 Direction: REV \n");
		}
		isGoingForwardLeft = false;
	}

	prevNumberOfTicksLeft = numberOfTicksLeft;
}

void Encoder::processRightPinChangeISR()
{
	if (digitalReadFast(pin3) == HIGH)
	{
		pin3High = true;
	}
	else
	{
		pin3High = false;
	}

	if (digitalReadFast(pin4) == HIGH)
	{
		pin4High = true;
	}
	else
	{
		pin4High = false;
	}

	if (pin3High == pin4High)
	{
		numberOfTicksRight++;
	}
	else
	{
		numberOfTicksRight--;
	}

	if (numberOfTicksRight < prevNumberOfTicksRight)
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicksRight);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicksRight);
			Serial.print(" Pin ");
			Serial.print(pin3);
			Serial.print(": ");
			Serial.print(pin3High);
			Serial.print(" Encoder 2 Direction: FWD \n");
		}
		isGoingForwardRight = true;

	}
	else
	{
		if (useSerialDebug)
		{
			Serial.print("Count: ");
			Serial.print(numberOfTicksRight);
			Serial.print(" Prev Count: ");
			Serial.print(prevNumberOfTicksRight);
			Serial.print(" Pin ");
			Serial.print(pin3);
			Serial.print(": ");
			Serial.print(pin3High);
			Serial.print(" Encoder 2 Direction: REV \n");
		}
		isGoingForwardRight = false;
	}

	prevNumberOfTicksRight = numberOfTicksRight;
}

void Encoder::reset()
{
	numberOfTicksLeft = 0;
	numberOfTicksRight = 0;
}


