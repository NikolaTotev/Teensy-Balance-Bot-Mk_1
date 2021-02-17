#include <Wire.h>
#include <Arduino.h>
#include "IMU.h"
#include "i2c_utils.h"

IMU::IMU(Adafruit_SSD1306* disp, byte useDisp)
{
	display = disp;
	useDisplay = useDisp;
}

void IMU::Ctor()
{

}

void IMU::TestIMU()
{
	//Check if sensor hardware is working;
	uint8_t sensorReadCheck;
	i2c_requestRegisters(Reg_Who_Am_I, 1, I2C_Addr);
	while (i2c_poll() < 1)
	{
		Serial.println("Waiting for IMU");
		delay(500);
	}

	sensorReadCheck = i2c_readByte();

	if (sensorReadCheck != 0x69)
	{


		display->clearDisplay();
		display->setCursor(0, 0);
		display->setTextSize(1); // Draw 2X-scale text
		display->setTextColor(SSD1306_WHITE);
		display->println("Sensor check failed");
		display->display();

		Serial.println("Sensor check failed!");
		delay(500);
	}
	else
	{


		display->clearDisplay();
		display->setCursor(0, 0);
		display->setTextSize(1); // Draw 2X-scale text
		display->setTextColor(SSD1306_WHITE);
		display->println("Sensor check pass");
		display->display();
		Serial.println("Sensor check passed!");
		delay(500);
	}
}

//Initialize the IMU registers.
void IMU::Init()
{

	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Starting");
	display->println("IMU");
	display->display();
	Serial.println("Starting IMU");
	delay(1000);



	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Starting");
	display->println("I2C");
	display->display();
	Serial.println("Starting i2c");
	delay(500);
	i2c_begin();



	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Testing");
	display->println("IMU");
	display->display();

	Serial.println("Testing IMU");
	delay(500);
	TestIMU();

	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Register");
	display->println("init.");
	display->display();
	RegisterInit();
	Serial.println("Register init.");

	delay(500);

	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Starting");
	display->println("gyro calib");
	display->display();

	Serial.println("Starting gyro calibration.");
	delay(500);
	GyroCalib();
	
	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(2); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("IMU Started");
	display->println("Ready for use");
	display->display();

	Serial.println("IMU Started!");
	delay(500);

}

void IMU::RegisterInit()
{
	i2c_registerWrite(Reg_Ctrl2_G, Gyro_ODR, I2C_Addr);
	i2c_registerWrite(Reg_Ctrl1_XL, Accel_ODR, I2C_Addr);
	i2c_registerWrite(Reg_Ctrl3_C, BDU_Setup, I2C_Addr);
}

float IMU::convertRawGyro(int16_t input)
{
	/*
	uint8_t gyroRangeDivisor = 250 / 125;
	if (250 == 250)
	{
	  gyroRangeDivisor = 2;
	}*/

	uint8_t gyroRangeDivisor = 4;
	float output = (float)input * 4.375 * (gyroRangeDivisor) / 1000;
	return output;
}

float IMU::convertRawAccel(int16_t input)
{
	float output = (float)input * 2 * 0.061 / 1000;
	return output;
}

void IMU::finalGyroCalc()
{
	finalGyroX = convertRawGyro(rawGyroX) - xCalibration;
	finalGyroY = convertRawGyro(rawGyroY) - yCalibration;
	finalGyroZ = convertRawGyro(rawGyroZ) - zCalibration;
}

void IMU::finalAccelCalc()
{
	finalAccelX = convertRawAccel(rawAccelX);
	finalAccelY = convertRawAccel(rawAccelY);
	finalAccelZ = convertRawAccel(rawAccelZ);
}

//Calculate the calibration value for the gyro. This is used to avoid excessive.
void IMU::GyroCalib()
{
	//Serial.print("Calibration starting");

	{  display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(1); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->display();

	for (int i = 0; i < 2000; i++)
	{
		readRawGyro();
		xCalibration += convertRawGyro(rawGyroX);
		yCalibration += convertRawGyro(rawGyroY);
		zCalibration += convertRawGyro(rawGyroZ);
		if (i % 100 == 0)
		{


			display->print("=");
			display->display();

			delay(5);
		}
	}



	display->clearDisplay();
	display->setCursor(0, 0);
	display->setTextSize(1); // Draw 2X-scale text
	display->setTextColor(SSD1306_WHITE);
	display->println("Gyro calib done!");
	display->display();

	delay(1000);

	xCalibration /= 2000;
	yCalibration /= 2000;
	zCalibration /= 2000;
	calibrationComplete = 1;
	}
}
//Read raw data from the gyro.
void IMU::readRawGyro()
{
	i2c_requestRegisters(Reg_G_OUT_X_L, 6, I2C_Addr);
	while (i2c_poll() < 6)
		;

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroX = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroY = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroZ = ((highByte << 8) | lowByte);
}

//Read raw data from the gyro.
void IMU::readRawAccel()
{
	i2c_requestRegisters(Reg_XL_OUT_X_L, 6, I2C_Addr);
	while (Wire.available() < 6)
		;

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelX = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelY = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelZ = ((highByte << 8) | lowByte);
}

void IMU::readRawIMU()
{
	i2c_requestRegisters(Reg_G_OUT_X_L, 12, I2C_Addr);
	while (i2c_poll() < 12)
		;

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroX = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroY = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawGyroZ = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelX = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelY = ((highByte << 8) | lowByte);

	lowByte = i2c_readByte();
	highByte = i2c_readByte();
	rawAccelZ = ((highByte << 8) | lowByte);
}

void IMU::printAccel()
{
	readRawAccel();
	finalAccelCalc();
	Serial.print("AccelX:");
	Serial.print(finalAccelX, 3);
	Serial.print("\n");

	Serial.print("AccelY:");
	Serial.print(finalAccelY, 3);
	Serial.print("\n");

	Serial.print("AccelZ:");
	Serial.print(finalAccelZ, 3);
	Serial.print("\n");
	Serial.print("\n");
}

void IMU::printGyro()
{
	readRawGyro();
	finalGyroCalc();
	Serial.print("GyroX:");
	Serial.print(finalGyroX, 0);
	Serial.print("\n");

	Serial.print("GyroY:");
	Serial.print(finalGyroY, 0);
	Serial.print("\n");

	Serial.print("GyroZ:");
	Serial.print(finalGyroZ, 0);
	Serial.print("\n");
	Serial.print("\n");
}

float* IMU::getAccelVals()
{
	readRawAccel();
	finalAccelCalc();
	finalAccelVals[0] = finalAccelX;
	finalAccelVals[1] = finalAccelY;
	finalAccelVals[2] = finalAccelZ;
	return finalAccelVals;
}

float* IMU::getGyroVals()
{
	readRawGyro();
	finalGyroCalc();
	finalGyroVals[0] = finalGyroX;
	finalGyroVals[1] = finalGyroY;
	finalGyroVals[2] = finalGyroZ;
	return finalGyroVals;
}

float* IMU::getIMUVals()
{
	readRawIMU();
	finalGyroCalc();
	finalAccelCalc();

	finalVals[0] = finalGyroX;
	finalVals[1] = finalGyroY;
	finalVals[2] = finalGyroZ;

	finalVals[3] = finalAccelX;
	finalVals[4] = finalAccelY;
	finalVals[5] = finalAccelZ;
	return finalVals;
}