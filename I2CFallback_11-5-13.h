//This is the new I2C.h to fall back upon
//This code provides functions to replace the standard RobotC motorPower[] and Servo[] functions:
//	MotorSpeed(port, daisy chain lvl, motor #, speed);
//	MotorPosition(port, daisy chain lvl, motor #, speed, encoder change);
//	ServoPosition(port, daisy chain lvl, servo #, new position);
#include "drivers/common.h"

void MotorSpeed(tSensors port, int DaisyChainLevel, int MotorNumber, sbyte Speed)
{
	tByteArray I2Crequest;
	I2Crequest[0] = 4;
	I2Crequest[1] = 0x02*DaisyChainLevel;
	switch MotorNumber:
		case 1:
			I2Crequest[2] = 0x44;
			I2Crequest[3] = 0b00000001;
			I2Crequest[4] = Speed;
		case 2:
			I2Crequest[2] = 0x46;
			I2Crequest[3] = Speed;
			I2Crequest[4] = 0b00000001;
		default:
			break;
		//nxtDisplayString(0,"
	writeI2C(port, I2Crequest);
}

long CurrentEncoderPosition(tSensor port, int DaisyChainLevel, int MotorNumber)
{
	tByteArray I2Crequest;
	tByteArray I2Cresponse;
	I2Crequest[0] = 2;
	I2Crequest[1] = 0x02*DaisyChainLevel;
	switch MotorNumber:
		case 1:
			I2Crequest[2] = 0x4C;
		case 2:
			I2Crequest[2] = 0x50;
		default:
			break;
	writeI2C(port, I2Crequest, I2Cresponse, 4);
	/*
	int x[] = {0,0,0,0}
	for (int i = 1; i<5; i++)
	{
		x[i] = I2Cresponce[i];
	}
	return x;
	//using this code means that the function becomes an array. BUT I decided not to use this, because in the later function we take
	//human input as our encoder variables and need to translate those anyways.*/
	
	long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0); /*This takes the
	four bits and creates a single base 10 number that is readable for people.*/
	return EncoderValue
{

void MotorPosition(tSensor port, int DaisyChainLevel, int MotorNumber, sbyte Speed, long DesiredEncoderChange)
{
	tByteArray I2Crequest;
	I2Crequest[0] = 8;
	I2Crequest[1] = 0x02*DaisyChainLevel;
	switch MotorNumber:
		case 1:
			I2Crequest[2] = 0x40H;
			I2Crequest[3] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 24) & 0x000000ff);
			I2Crequest[4] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 16) & 0x000000ff);
			I2Crequest[5] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 8) & 0x000000ff);
			I2Crequest[6] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) & 0x000000ff);
			I2Crequest[7] = 0b00000010;
			I2Crequest[8] = Speed;
		case 2:
			I2Crequest[2] = 0x48;
			I2Crequest[3] = Speed;
			I2Crequest[4] = 0b00000010;
			I2Crequest[5] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 24) & 0x000000ff);
			I2Crequest[6] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 16) & 0x000000ff);
			I2Crequest[7] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) >> 8) & 0x000000ff);
			I2Crequest[8] = (byte)(((CurrentEncoderPosition(port,DaisyChainLevel,MotorNumber) - DesiredEncoderChange) & 0x000000ff);
		default:
			break;
	writeI2C(port, I2Crequest);
}

void ServoPosition(tSensors port, int DaisyChainLevel, int ServoNumber, byte Position)
{
	tByteArray I2Crequest;
	I2Crequest[0] = 3;
	I2Crequest[1] = 0x02 * DaisyChainLevel;
	I2Crequest[2] = 0x41 + ServoNumber;
	I2Crequest[3] = Position;

	writeI2C(port, I2Crequest);
}
