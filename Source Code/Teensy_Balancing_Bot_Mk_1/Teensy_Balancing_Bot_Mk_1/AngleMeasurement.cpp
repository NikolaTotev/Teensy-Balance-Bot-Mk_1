// 
// 
// 

#include "AngleMeasurement.h"
#include "i2c_utils.h"

void AngleM::AngleCtor()
{

    Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally

    delay(2000); // Pause for 2 seconds

    currentDisplay->clearDisplay();
    currentDisplay->setCursor(0, 0);
    currentDisplay->setTextSize(2); // Draw 2X-scale text
    currentDisplay->setTextColor(SSD1306_WHITE);
    currentDisplay->println("Welcome!");
    currentDisplay->println("Starting...");
    currentDisplay->display();
    delay(2000);

    currentDisplay->clearDisplay();
    currentDisplay->display();

    // Clear the buffer

    delay(1000);
    i2c_begin();
    currentIMU.Ctor();

    accelAngleEstimateX = 0;
    accelAngleEstimateY = 0;
    accelAngleEstimateZ = 0;

    gyroAngleEstimateX = 0;
    gyroAngleEstimateY = 0;
    gyroAngleEstimateZ = 0;

    finalAngleEstimateX = 0;
    finalAngleEstimateY = 0;
    SetInitialAngle();

}

void AngleM::SetInitialAngle()
{
    currentAccelVals = currentIMU.getAccelVals();
    totalGravityVector = sqrt((currentAccelVals[0] * currentAccelVals[0]) + (currentAccelVals[1] * currentAccelVals[1]) + (currentAccelVals[2] * currentAccelVals[2]));
    accelAngleEstimateX = asin(currentAccelVals[1] / totalGravityVector) * 57.296;
    accelAngleEstimateY = asin(currentAccelVals[0] / totalGravityVector) * 57.296;
    gyroAngleEstimateX = accelAngleEstimateX;
    gyroAngleEstimateY = accelAngleEstimateY;
}

float* AngleM::GetCurrentAngles()
{

    prevTime = micros();
    currentVals = currentIMU.getIMUVals();

    totalGravityVector = sqrt((currentVals[3] * currentVals[3]) + (currentVals[4] * currentVals[4]) + (currentVals[5] * currentVals[5]));
    accelAngleEstimateX = asin(currentVals[4] / totalGravityVector) * 57.296;
    accelAngleEstimateY = asin(currentVals[3] / totalGravityVector) * 57.296;

    gyroAngleEstimateX += (currentVals[0] * 0.0012) * 10;
    gyroAngleEstimateY += (currentVals[1] * 0.0012) * 10;

    gyroAngleEstimateX = GyroPart * gyroAngleEstimateX + AccelPart * accelAngleEstimateX;
    gyroAngleEstimateY = GyroPart * gyroAngleEstimateY + AccelPart * accelAngleEstimateY;

    finalAngleEstimateX = gyroAngleEstimateX;
    finalAngleEstimateY = gyroAngleEstimateY;

    currentAngles[0] = finalAngleEstimateX;
    currentAngles[1] = finalAngleEstimateY;

    return currentAngles;
}

void AngleM::DrawValue(uint16_t m1ThrottleVal, uint16_t m2ThrottleVal)
{
    currentDisplay->clearDisplay();
    currentDisplay->setCursor(0, 0);
    currentDisplay->setTextSize(2); // Draw 2X-scale text
    currentDisplay->setTextColor(SSD1306_WHITE);
    //currentDisplay->print("X:");
    //currentDisplay->print(finalAngleEstimateX, 0);
    currentDisplay->print(" Y:");
    currentDisplay->print(currentAngles[1], 0);
    currentDisplay->print("\n");
    currentDisplay->setTextSize(1);


    currentDisplay->print(m1ThrottleVal);
    currentDisplay->print(" ");
    currentDisplay->print(m2ThrottleVal);
    currentDisplay->display();
}

//Remove after testing.
float AngleM::GetCurrentXRate()
{
    return currentIMU.getIMUVals()[1];
}

float AngleM::GetCurrentYRate()
{
    return currentIMU.getIMUVals()[1];
}
