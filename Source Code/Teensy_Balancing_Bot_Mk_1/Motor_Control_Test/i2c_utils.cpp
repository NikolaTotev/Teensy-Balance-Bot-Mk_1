#include "i2c_utils.h"

void i2c_begin()
{
    delay(1000);
    Serial.println("Starting i2C");
    Wire.begin();
    Serial.println("i2c Started");
}

void i2c_registerWrite(uint16_t targetRegister, uint16_t registerData, uint16_t I2CAddr)
{
    Wire.beginTransmission(I2CAddr);
    Wire.write(targetRegister);
    Wire.write(registerData);
    Wire.endTransmission();
}

void i2c_registerSelect(uint16_t targetRegister, uint16_t registerData, uint16_t I2CAddr)
{
    Wire.beginTransmission(I2CAddr);
    Wire.write(targetRegister);
    Wire.endTransmission();
}

int i2c_poll()
{
    return Wire.available();
}

byte i2c_readByte()
{
    return Wire.read();
}

void i2c_requestRegisters(uint16_t startRegister, uint16_t length, uint16_t I2CAddr)
{
    Wire.beginTransmission(I2CAddr);
    Wire.write(startRegister);
    Wire.endTransmission();
    Wire.requestFrom(I2CAddr, length);
}
