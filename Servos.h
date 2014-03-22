#include "drivers/common.h"
#include "I2C.h"

void Servos_SetPosition(tSensors Port, int DaisyChainLevel, int MotorNumber, int Position)
{
	I2C_WritePMW(Port, DaisyChainLevel, 0);
	I2C_MoveServo(Port, DaisyChainLevel, MotorNumber, Position);
}

void Servos_StopAll()
{
	// assumes 360 servos, otherwise this will just move them
	for (int port = 1; port <= 4; port++) {
		for (int daisychain = 1; daisychain <= 4; daisychain++) {
			for (int motor = 1; motor <= 2; motor++) {
				Servos_SetPosition(S1, daisychain, motor, 128);
				Servos_SetPosition(S2, daisychain, motor, 128);
				Servos_SetPosition(S3, daisychain, motor, 128);
				Servos_SetPosition(S4, daisychain, motor, 128);
			}
		}
	}
}
