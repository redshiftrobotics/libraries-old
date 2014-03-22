#include "drivers/common.h"
#include "I2C.h"

tSensors Sensors[100];
int Motors_Length = 0;
int Motors_DaisyChainLevel[100];
int Motors_Number[100];
int Motors_Speed[100];
int Motors_Encoder[100];
bool Motors_MovingToPosition[100];
bool Motors_UpdateMotorsInitialized = false;
task Motors_UpdateMotors;

/*
 * Motor movement mode of 0 is setting an encoder position
 * Motor movement mode of 1 is setting a motor speed
 */

int Motors_MotorMovementMode[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long Motors_MotorMovementSpeed[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long Motors_MotorMovementEncoders[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* public API */

void Motors_SetSpeed(tSensors Sensor, int DaisyChain, int MNumber, int MSpeed)
{
	
}

void Motors_SetPosition(tSensors Sensor, int DaisyChain, int MNumber, int Encoder, int MSpeed)
{
	int id = _Motors_GetCanonicalMotorId(Sensor, DaisyChain, MNumber);
	_Motors_MotorMovementMode[id] = 0;
	_Motors_MotorMovementSpeed[id] = MSpeed;
	_Motors_MotorMovementEncoder[id] = Encoder;
}

/* utility functions */
int _Motors_GetCanonicalMotorId(tSensors SensorPort, int DaisyChainLevel, int MotorNumber)
{
	// initially assume the id is 0. it will be manipulated from here.
	int id = 0;

	// get a port id that we can work with
	int port = _I2C_GetIntFromPort(SensorPort);

	// add in the daisychain level information
	id += (DaisyChainLevel-1)*2;

	// add in the motor information
	id += MotorNumber-1;

	// add in the port information
	id += (port-1)*8;
}

/* bus update task */

task _Motors_UpdateMotors()
{
	while(true)
	{
		for(int i = 0; i < Motors_Length; i++)
		{
			if(Motors_MovingToPosition[i] == false)
			{
				I2C_SetMotorSpeed(Sensors[i], Motors_DaisyChainLevel[i], Motors_Number[i], Motors_Speed[i]);
			}
			else if(Motors_MovingToPosition[i] == true)
			{
				I2C_SetEncoderPosition(Sensors[i], Motors_DaisyChainLevel[i], Motors_Number[i], Motors_Encoder[i], Motors_Speed[i]);
			}
		}
	}
}
