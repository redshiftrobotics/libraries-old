#include "../libraries/Gyro.c"
#include "../libraries/Motors.h"

float FinalX = 5;
float FinalY = 0;
float Heading = 0;
float ChangePerSecond = 0;
float TotalDrift = 0;

task UpdateHeading;

void Move(int RightPower, int LeftPower)
{
	Motors_SetSpeed(S1, 2, 1, RightPower);
	Motors_SetSpeed(S1, 2, 2, -LeftPower);
}

void Calibrate()
{
	Gyro_Start();

	//calibration phase
	sleep(5000);
	FinalY = Gyro_Heading();

	//finds drift slope
	ChangePerSecond = abs(FinalY) / FinalX;

	Gyro_Reset();

	StartTask(UpdateHeading);
}

//biggest amount you can turn is +/- 180 degrees
void Turn(int Degrees)
{
	hogCPU();

	Gyro_Reset();
	TotalDrift = 0;

	releaseCPU();

	while(abs(-Degrees + Heading) > 1)
	{
		Move((-Degrees + Heading) / 2, (Degrees - Heading) / 2)
	}

	Move(0, 0);
}

void Straight(int Power, int  Miliseconds)
{
	hogCPU();

	Gyro_Reset();
	TotalDrift = 0;

	releaseCPU();
	Time1[T4] = 0;

	while(Time1[T4] < Miliseconds)
	{
		Move(Power + Heading, Power - Heading);
	}
	Move(0, 0);
}

task UpdateHeading()
{
	while(true)
	{
		TotalDrift -= ChangePerSecond * Time1[T3] / 1000;
		Time1[T3] = 0;
		Heading = Gyro_Heading() + TotalDrift;
	}
}
