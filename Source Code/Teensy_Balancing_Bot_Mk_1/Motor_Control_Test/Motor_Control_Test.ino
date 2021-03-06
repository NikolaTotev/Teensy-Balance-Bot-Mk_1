/*
 Name:		Motor_Control_Test.ino
 Created:	12/28/2020 6:52:21 PM
 Author:	Nikola
*/

// the setup function runs once when you press reset or power the board
#include "MDD3A_Lib.h"
#include <WireKinetis.h>
#include <WireIMXRT.h>
#include <Wire.h>
#include "i2c_utils.h"
#include <CytronMotorDriver.h>


MDD3A motor1(2, 3);
MDD3A motor2(4, 5);

bool pin9High = false;
bool pin10High = false;

int16_t encoder1Count = 0;
int16_t prevEncoder1Count = 0;

bool pin11High = false;
bool pin12High = false;
int16_t encoder2Count = 0;
int16_t prevEncoder2Count = 0;

void pinChanceEncoder1ISR()
{
	if (digitalReadFast(9) == HIGH)
	{
		pin9High = true;
	}
	else
	{
		pin9High = false;
	}

	if (digitalReadFast(10) == HIGH)
	{
		pin10High = true;
	}
	else
	{
		pin10High = false;
	}

	if (pin9High == pin10High)
	{
		encoder1Count++;
	}
	else
	{
		encoder1Count--;
	}

	if (encoder1Count < prevEncoder1Count)
	{
		Serial.print("Count: ");
		Serial.print(encoder1Count);
		Serial.print(" Prev Count: ");
		Serial.print(prevEncoder1Count);
		Serial.print(" Pin 9:");
		Serial.print(pin9High);
		Serial.print(" Pin 10:");
		Serial.print(pin10High);
		Serial.print(" Encoder 1 Direction: FWD \n");

	}
	else
	{
		Serial.print("Count: ");
		Serial.print(encoder1Count);
		Serial.print(" Prev Count: ");
		Serial.print(prevEncoder1Count);
		Serial.print(" Pin 9:");
		Serial.print(pin9High);
		Serial.print(" Pin 10:");
		Serial.print(pin10High);
		Serial.println("Encoder 1 Direction: REV\n");
	}

	prevEncoder1Count = encoder1Count;
}

void pinChanceEncoder2ISR()
{
	if (digitalReadFast(12) == HIGH)
	{
		pin11High = true;
	}
	else
	{
		pin11High = false;
	}

	if (digitalReadFast(12) == HIGH)
	{
		pin12High = true;
	}
	else
	{
		pin12High = false;
	}

	if (pin11High == pin12High)
	{
		encoder2Count++;
	}
	else
	{
		encoder2Count--;
	}

	if (encoder1Count < prevEncoder1Count)
	{
		Serial.println("Encoder 2 Direction: FWD");
	}
	else
	{
		Serial.println("Encoder 2 Direction: REV");
	}


}


void setup() {
	pinMode(9, INPUT);
	pinMode(10, INPUT);


	pinMode(11, INPUT);
	pinMode(12, INPUT);

	Serial.begin(9600);
	//attachInterrupt(10, pinChanceEncoder1ISR, RISING);
	//attachInterrupt(12, pinChanceEncoder2ISR, CHANGE);
}

int speed = 100;
// the loop function runs over and over again until power down or reset
void loop() {
	//for (int i = 0; i < 100; ++i)
	//{
	//	speed++;
	//	motor1.setSpeed(-speed);
	//	delay(500);// Motor 1 runs forward at 50% speed.
	//}
	//delay(2000);
	//motor1.setSpeed(0);   // Motor 1 runs forward at 50% speed.
	////motor2.setSpeed(-250);  // Motor 2 runs backward at 50% speed.
	//delay(1000);
	//speed = 0;

	motor1.setSpeed(1, FWD);   // Motor 1 runs forward at 50% speed.
	//motor2.setSpeed(-100);  // Motor 2 runs backward at 50% speed.
	//delay(1000);
}
