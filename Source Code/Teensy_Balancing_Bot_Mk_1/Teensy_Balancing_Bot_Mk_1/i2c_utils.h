// i2c_utils.h

#ifndef _I2C_UTILS_h
#define _I2C_UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	// i2c_utils.h

#ifndef _i2c_utils_h
#define _i2c_utils_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <Wire.h>

void i2c_begin();
void i2c_registerWrite(uint16_t targetRegister, uint16_t registerData, uint16_t I2CAddr);
void i2c_registerSelect(uint16_t targetRegister, uint16_t I2CAddr);
int i2c_poll();
byte i2c_readByte();
void i2c_requestRegisters(uint16_t startRegister, uint16_t length, uint16_t I2CAddr);

#else
#include "WProgram.h"
#endif


#endif


#else
//#include "WProgram.h"
#endif


#endif

