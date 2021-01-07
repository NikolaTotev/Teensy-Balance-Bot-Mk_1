// IMU.h

#ifndef _IMU_h
#define _IMU_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <Wire.h>
#include "Adafruit_SSD1306.h"


#define I2C_Addr 0x6B

//Misc registers
#define Reg_Who_Am_I 0x0F

//Control registers
#define Reg_Ctrl1_XL 0x10
#define Reg_Ctrl2_G 0x11
#define Reg_Ctrl3_C 0x12

//Control register values
#define Accel_ODR 0x88
#define Gyro_ODR 0x88
#define BDU_Setup 0x44

//Output registers

//X Accel Axis
#define Reg_XL_OUT_X_L 0x28
#define Reg_XL_OUT_X_H 0x29

//Y Accel Axis
#define Reg_XL_OUT_Y_L 0x2A
#define Reg_XL_OUT_Y_H 0x2B

//Z Accel Axis
#define Reg_XL_OUT_Z_L 0x2C
#define Reg_XL_OUT_Z_H 0x2D

//X Gyro Axis
#define Reg_G_OUT_X_L 0x22
#define Reg_G_OUT_X_H 0x23

//Y Gyro Axis
#define Reg_G_OUT_Y_L 0x24
#define Reg_G_OUT_Y_H 0x25

//Z Gyro Axis
#define Reg_G_OUT_Z_L 0x26
#define Reg_G_OUT_Z_H 0x27

class IMU
{
private:
	uint16_t rawGyroX;
	uint16_t rawGyroY;
	uint16_t rawGyroZ;
	float finalGyroX;
	float finalGyroY;
	float finalGyroZ;

	uint16_t rawAccelX;
	uint16_t rawAccelY;
	uint16_t rawAccelZ;
	float finalAccelX;
	float finalAccelY;
	float finalAccelZ;

	float finalAccelVals[3];
	float finalGyroVals[3];
	float finalVals[6];

	float xCalibration = 0;
	float yCalibration = 0;
	float zCalibration = 0;

	int calibCounter = 0;
	byte highByte, lowByte;

	byte calibrationComplete = 0;

	Adafruit_SSD1306* display;
	byte useDisplay;

public:
	IMU(Adafruit_SSD1306* disp, byte useDisp);
	void Ctor();
	void Init();
	void RegisterInit();
	void GyroCalib();
	void readRawGyro();
	void readRawAccel();
	void readRawIMU();
	float convertRawGyro(int16_t input);
	float convertRawAccel(int16_t input);
	void finalAccelCalc();
	void finalGyroCalc();
	void TestIMU();
	void printAccel();
	void printGyro();
	float* getAccelVals();
	float* getGyroVals();
	float* getIMUVals();
	void SetDisp(Adafruit_SSD1306* disp) { display = disp; }
};

#else
	//#include "WProgram.h"
#endif


#endif

