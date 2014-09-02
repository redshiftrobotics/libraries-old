#include "I2C.h"

//sets globals
bool Arm_Initialized = false;
long Arm_BottomEncoderLimit = 0;
long Arm_TopEncoderLimit = 0;
long Arm_Encoder = 0;
int Arm_Speed = 0;

void Arm_Reinitialize()
{
	hogCPU();
	Arm_Initialized = false;
	Arm_BottomEncoderLimit = 0;
	Arm_TopEncoderLimit = 0;
	Arm_Encoder = 0;
	Arm_Speed = 0;
	releaseCPU();
}

void Arm_SetSpeed(int Speed)
{
	hogCPU();
	if(Arm_Initialized)
	{
		Arm_Speed = Speed;
	}
	releaseCPU();
}

void Arm_Update()
{
	Arm_Encoder = I2C_GetEncoderPosition(S1, 1, 1);
	//if the arm isn't initialized yet
	if(!Arm_Initialized)
	{
		//set the speed to 10
		I2C_SetMotorSpeed(S1, 1, 1, 25);

		//if the lower limit is triggered, set the upper and lower encoder bounds
		if(SensorValue[S4] == 1)
		{
			Arm_Initialized = true;
			Arm_BottomEncoderLimit = Arm_Encoder + (-.2 * 1440); //the amount of distance from the buttom press down. This lets it go below the button press.
			Arm_TopEncoderLimit = Arm_Encoder - (10 * 1440);
		}
	}

	//if the arm is initialized
	else
	{
		//if the arm is with in the encoder range
		if(Arm_Encoder > Arm_TopEncoderLimit && Arm_Encoder < Arm_BottomEncoderLimit)
		{
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is below the bottom encoder and trying to go up
		else if(Arm_Encoder > Arm_BottomEncoderLimit && Arm_Speed < 0)
		{
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is above the top encoder and trying to go down
		else if(Arm_Encoder < Arm_TopEncoderLimit && Arm_Speed > 0)
		{
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is out of the encoder range and trying to go the wrong direction
		else
		{
			I2C_SetMotorSpeed(S1, 1, 1, 0);
		}
	}
}
