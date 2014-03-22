#include "drivers/hitechnic-gyro.h"

float rotSpeed;
float heading;
task UpdateGyro;

task UpdateGyro()
{
	while(true)
	{
	  while (time1[T1] < 20)
	  {
	    wait1Msec(1);
	  }
	  time1[T1]=0;
	  rotSpeed = HTGYROreadRot(Gyro);
	  heading += rotSpeed * 0.02;
	}
}

void StartGyro()
{
	float rotSpeed = 0;
  float heading = 0;
  HTGYROstartCal(Gyro);
  time1[T1] = 0;
  StartTask(UpdateGyro);
}

float GyroDegrees()
{
		return heading;
}

void ResetGyro()
{
	heading = 0;
}
