#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)
//#pragma config(Sensor, S4,     ,               sensorHiTechnicTouchMux)

#include "I2C.h"

//sets globals
bool Arm_Initialized = false;
int Arm_BottomEncoderLimit = 0;
int Arm_TopEncoderLimit = 0;
int Arm_Encoder = 0;
int Arm_Speed = 0;
int nMux = 0;

void Arm_SetSpeed(int Speed)
{
	//only lets you change the speed if the robot is initialized
	if(Arm_Initialized)
	{
		Arm_Speed = Speed;
	}
}

void Arm_Update()
{
	Arm_Encoder = I2C_GetEncoderPosition(S1, 1, 1);

	//if the arm isn't initialized yet
	if(!Arm_Initialized)
	{
		nMux = SensorValue[S4]; //Values from sensorHitechnicTouchMux is a 4-bit map for each of possible four touch sensors
		//set the speed to 10
		Arm_Speed = 10;

		//if the lower limit is triggered, set the upper and lower encoder bounds
		//nMux should be bitwise added to 0x01 for sensor 1, use 0x02 for sensor 2, use 0x04 for sensor 3, use 0x08 for sensor 4
		//if(nMux & 0x01) //make sure to plug the lower sensor into port 1
		if(SensorValue[S4] == 1) //replace this if line with the if line above (uncommented obviously)
		{
			Arm_Initialized = true;
			Arm_Speed = 0;

			Arm_BottomEncoderLimit = Arm_Encoder;
			Arm_TopEncoderLimit = Arm_Encoder - (5 * 1440);
		}
	}

	//if the arm is initialized
	else
	{
		nMux = SensorValue[S4];
		//if the arm is with in the encoder range
		if(Arm_Encoder < Arm_TopEncoderLimit && Arm_Encoder > Arm_BottomEncoderLimit)
		{
			//And the arm is within the upper bound
			//if(nMux & 0x02) //make sure to plug the top limit switch into port #2
			//{
				I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
			//}
		}

		//if the arm is out of the encoder range
		else
		{
			I2C_SetMotorSpeed(S1, 1, 1, 0);
		}
	}
}
